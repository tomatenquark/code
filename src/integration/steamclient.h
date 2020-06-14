#ifdef STEAM_ENABLED
#include "steam_api.h"
#include "achievements.h"

namespace integration {
    struct CSteamAchievements
    {
    private:
        int64 m_iAppID; // Our current AppID
        Achievement_t *m_pAchievements; // Achievements data
        int m_iNumAchievements; // The number of Achievements
        bool m_bInitialized; // Have we called Request stats and received the callback?

    public:
        CSteamAchievements(Achievement_t *Achievements, int NumAchievements);

        bool RequestStats();
        bool SetAchievement(const char* ID);

        STEAM_CALLBACK( CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t,
                        m_CallbackUserStatsReceived );
        STEAM_CALLBACK( CSteamAchievements, OnUserStatsStored, UserStatsStored_t,
                        m_CallbackUserStatsStored );
        STEAM_CALLBACK( CSteamAchievements, OnAchievementStored,
                        UserAchievementStored_t, m_CallbackAchievementStored );
    };

    CSteamAchievements::CSteamAchievements(Achievement_t *Achievements, int NumAchievements):
            m_iAppID( 0 ),
            m_bInitialized( false ),
            m_CallbackUserStatsReceived( this, &CSteamAchievements::OnUserStatsReceived ),
            m_CallbackUserStatsStored( this, &CSteamAchievements::OnUserStatsStored ),
            m_CallbackAchievementStored( this, &CSteamAchievements::OnAchievementStored )
    {
        m_iAppID = SteamUtils()->GetAppID();
        m_pAchievements = Achievements;
        m_iNumAchievements = NumAchievements;
        RequestStats();
    }

    bool CSteamAchievements::RequestStats()
    {
        // Is Steam loaded? If not we can't get stats.
        if ( NULL == SteamUserStats() || NULL == SteamUser() )
        {
            return false;
        }
        // Is the user logged on?  If not we can't get stats.
        if ( !SteamUser()->BLoggedOn() )
        {
            return false;
        }
        // Request user stats.
        return SteamUserStats()->RequestCurrentStats();
    }

    bool CSteamAchievements::SetAchievement(const char* ID)
    {
        // Have we received a call back from Steam yet?
        if (m_bInitialized)
        {
            SteamUserStats()->SetAchievement(ID);
            return SteamUserStats()->StoreStats();
        }
        // If not then we can't set achievements yet
        return false;
    }

    void CSteamAchievements::OnUserStatsReceived( UserStatsReceived_t *pCallback )
    {
        // we may get callbacks for other games' stats arriving, ignore them
        if ( m_iAppID == pCallback->m_nGameID )
        {
            if ( k_EResultOK == pCallback->m_eResult )
            {
                m_bInitialized = true;

                // load achievements
                for ( int iAch = 0; iAch < m_iNumAchievements; ++iAch )
                {
                    Achievement_t &ach = m_pAchievements[iAch];

                    SteamUserStats()->GetAchievement(ach.m_pchAchievementID, &ach.m_bAchieved);
                    _snprintf( ach.m_rgchName, sizeof(ach.m_rgchName), "%s",
                               SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
                                                                                "name"));
                    _snprintf( ach.m_rgchDescription, sizeof(ach.m_rgchDescription), "%s",
                               SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
                                                                                "desc"));
                }
            }
            else
            {
                char buffer[128];
                _snprintf( buffer, 128, "RequestStats - failed, %d\n", pCallback->m_eResult );
            }
        }
    }

    void CSteamAchievements::OnUserStatsStored( UserStatsStored_t *pCallback )
    {
        // we may get callbacks for other games' stats arriving, ignore them
        if ( m_iAppID == pCallback->m_nGameID )
        {
            if ( k_EResultOK == pCallback->m_eResult )
            {
                //OutputDebugString( "Stored stats for Steam\n" );
            }
            else
            {
                char buffer[128];
                _snprintf( buffer, 128, "StatsStored - failed, %d\n", pCallback->m_eResult );
                //OutputDebugString( buffer );
            }
        }
    }

    void CSteamAchievements::OnAchievementStored( UserAchievementStored_t *pCallback )
    {
        // we may get callbacks for other games' stats arriving, ignore them
        if ( m_iAppID == pCallback->m_nGameID )
        {
            //OutputDebugString( "Stored Achievement for Steam\n" );
        }
    }

    // Achievement array which will hold data about the achievements and their state
    Achievement_t g_Achievements[] =
            {
                    _ACH_ID( ACH_EDIT_ENTER, "How do you fly?" ),
            };

    // Global access to Achievements object
    CSteamAchievements*	g_SteamAchievements = NULL;

    struct steamclient: clientintegration {
        bool api_Initialized = false;
        HAuthTicket authTicket = k_HAuthTicketInvalid;
        uint32 ticketLength;

        int setup() override {
            if ( SteamAPI_RestartAppIfNecessary( k_uAppIdInvalid ) ) return 1; // Replace with your App ID
            if ( !SteamAPI_Init() ) return 1;
            g_SteamAchievements = new CSteamAchievements(g_Achievements, 1);
            api_Initialized = true;
            return 0;
        }

        void cleanup() override
        {
            SteamAPI_Shutdown();
            //if (g_SteamAchievements) delete g_SteamAchievements;
        }

        void update() override
        {
            SteamAPI_RunCallbacks();
        }

        void cancelticket() override
        {
            if (!api_Initialized) return;
            if ( authTicket != k_HAuthTicketInvalid ) SteamUser()->CancelAuthTicket( authTicket );
        }

        void getticket(char * ticket) override
        {
            if (!api_Initialized) return;
            cancelticket();
            authTicket = SteamUser()->GetAuthSessionTicket( ticket, 1024, &ticketLength );
        }

        int getticketlength() override
        {
            return (int)ticketLength;
        }

        int getsteamid() override
        {
            if (!api_Initialized) return 0;
            return SteamUser()->GetSteamID().ConvertToUint64();
        }

        void setachievement(const char* achievement) override
        {
            if (g_SteamAchievements)
            {
                g_SteamAchievements->SetAchievement(achievement);
            }
        }

    };
}
#endif
