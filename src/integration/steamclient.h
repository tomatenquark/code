#ifdef STEAM_ENABLED
#include "steam_api.h"
#include "achievements.h"

#if defined(__clang__) || defined(_MSC_VER)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

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
    private:
        bool api_Initialized;
        HAuthTicket authTicket;
        uint32 ticketLength;
    public:
        steamclient();

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

        void getappdir(char *installdir) override
        {
            if (!api_Initialized) return;
            string pdir;
            int folderLength;
            SteamApps()->GetAppInstallDir( SteamUtils()->GetAppID(), pdir, folderLength );
            fs::path workshopdir(pdir);
            workshopdir = workshopdir.parent_path().parent_path();
            workshopdir.append( "workshop" );
            workshopdir.append( "content" );
            workshopdir.append( std::to_string(SteamUtils()->GetAppID()) );
            copystring(installdir, workshopdir.c_str() , workshopdir.string().length() );
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

        CCallResult< steamclient, CreateItemResult_t > m_GetItemCreateCallResult;

        void OnGetItemCreateResult ( CreateItemResult_t *pParam, bool failure );

        void createmapid() override
        {
            if (!api_Initialized) return;
            SteamAPICall_t steamApiCall = SteamUGC()->CreateItem(SteamUtils()->GetAppID(), k_EWorkshopFileTypeCommunity);
            m_GetItemCreateCallResult.Set( steamApiCall, this, &steamclient::OnGetItemCreateResult );
        }

        void updatemapbyid(int id, const char* title, const char* content, const char* desc = NULL, const char* preview = NULL) override
        {
            if (!api_Initialized) return;
            UGCUpdateHandle_t updateHandle = SteamUGC()->StartItemUpdate(SteamUtils()->GetAppID(), id);
            SteamUGC()->SetItemTitle( updateHandle, title );
            SteamUGC()->SetItemContent( updateHandle, content );
            if (desc != NULL) SteamUGC()->SetItemDescription( updateHandle, desc );
            if (preview != NULL) SteamUGC()->SetItemPreview( updateHandle, preview );
            SteamUGC()->SubmitItemUpdate( updateHandle, NULL );
        }
    };

    steamclient::steamclient():
        api_Initialized( false ),
        authTicket( k_HAuthTicketInvalid ),
        ticketLength( 0 )
    {
    }

    void steamclient::OnGetItemCreateResult ( CreateItemResult_t *pParam, bool failure ) {
        if (pParam->m_eResult == k_EResultOK) {
            setvar("mapid", pParam->m_nPublishedFileId, true, false);
            // TODO: Check m_bUserNeedsToAcceptWorkshopLegalAgreement
        }
    }
}
#endif