#ifdef STEAM_ENABLED
#include "steam_api.h"
#include "achievements.h"

#include <string>
#include <map>
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
                    _ACH_ID( ACH_EDIT_FLOATSPEED, "Starship surprise" ),
                    _ACH_ID( ACH_FIRST_BLOOD, "First blood" ),
                    _ACH_ID( ACH_DOUBLE_KILL, "Double kill" ),
                    _ACH_ID( ACH_TRIPLE_KILL, "Triple kill" ),
                    _ACH_ID( ACH_CATCH_ME_IF_YOU_CAN, "Catch me if you can" ),
                    _ACH_ID( ACH_FLY_ME_TO_THE_MOON, "Fly me to the moon" ),
            };

    // Global access to Achievements object
    CSteamAchievements*	g_SteamAchievements = NULL;

    struct steamclient: clientintegration {
    private:
        std::map<uint64, int*> downloads;
        bool api_Initialized;
        HAuthTicket authTicket;
        uint32 ticketLength;
    public:
        steamclient();

        int setup() override {
            if ( !SteamAPI_Init() ) return 0;
            g_SteamAchievements = new CSteamAchievements(g_Achievements, 1);
            api_Initialized = true;
            return 1;
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
            string pdir = "";
            int folderLength = 0;
            SteamApps()->GetAppInstallDir( SteamUtils()->GetAppID(), pdir, folderLength );
            fs::path workshopdir(pdir);
            workshopdir = workshopdir.parent_path().parent_path();
            workshopdir.append( "workshop" );
            workshopdir.append( "content" );
            workshopdir.append( std::to_string(SteamUtils()->GetAppID()) );
            copystring(installdir, workshopdir.string().c_str() , strlen(workshopdir.string().c_str()) + 1 );
        }

        void cancelticket() override
        {
            if (!api_Initialized) return;
            if ( authTicket != k_HAuthTicketInvalid ) SteamUser()->CancelAuthTicket( authTicket );
        }

        void getticket(int * ticket) override
        {
            if (!api_Initialized) return;
            cancelticket();
            authTicket = SteamUser()->GetAuthSessionTicket( ticket, 1024, &ticketLength );
        }

        int getticketlength() override
        {
            return (int)ticketLength;
        }

        void getsteamid(char* id) override
        {
            if (!api_Initialized) return;
            std::string userid = std::to_string(SteamUser()->GetSteamID().ConvertToUint64());
            copystring(id, userid.c_str(), userid.length() + 1);
        }

        void setachievement(const char* achievement) override
        {
            if (g_SteamAchievements)
            {
                g_SteamAchievements->SetAchievement(achievement);
            }
        }

        int getstat(const char* stat) {
            if (g_SteamAchievements) {
                int value = 0;
                SteamUserStats()->GetStat(stat, &value);
                return value;
            }
        }

        void setstat(const char* stat, int value) override {
            if (g_SteamAchievements)
            {
                SteamUserStats()->SetStat(stat, value);
            }
        }

        void incrementstat(const char* stat, int increment) override {
            if (g_SteamAchievements)
            {
                int value;
                SteamUserStats()->GetStat(stat, &value);
                SteamUserStats()->SetStat(stat, value + increment);
            }
        }

        void updateavgstat(const char* stat, float value, double sessionLength) override {
            if (g_SteamAchievements)
            {
                SteamUserStats()->UpdateAvgRateStat(stat, value, sessionLength);
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

        void updatemapbyid(const char* id, const char* title, const char* content, const char* desc = NULL, const char* preview = NULL) override
        {
            if (!api_Initialized) return;
            uint64 mid = std::stoull(id);
            UGCUpdateHandle_t updateHandle = SteamUGC()->StartItemUpdate(SteamUtils()->GetAppID(), mid);
            SteamUGC()->SetItemTitle( updateHandle, title );
            SteamUGC()->SetItemContent( updateHandle, content );
            if (desc != NULL) SteamUGC()->SetItemDescription( updateHandle, desc );
            if (preview != NULL) SteamUGC()->SetItemPreview( updateHandle, preview );
            SteamUGC()->SubmitItemUpdate( updateHandle, NULL );
            conoutf("Submitted item update for ID: %s", id);
        }

        bool downloadmap(const char* id, int *status) override
        {
            if (!api_Initialized) return false;
            uint64 mid = std::stoull(id);
            bool download = SteamUGC()->DownloadItem(mid, true);
            conoutf("Started download for collection ID: %s", id);
            downloads[mid] = status;
            return download;
        }

        STEAM_CALLBACK( steamclient, OnDownloadItemResultReceived, DownloadItemResult_t,
                        m_CallbackDownloadItemResultReceived );

        STEAM_CALLBACK( steamclient, OnGameServerChangeRequested, GameServerChangeRequested_t,
                m_CallbackGameServerChangeRequested );
    };

    steamclient::steamclient():
        api_Initialized( false ),
        authTicket( k_HAuthTicketInvalid ),
        ticketLength( 0 ),
        m_CallbackDownloadItemResultReceived( this, &steamclient::OnDownloadItemResultReceived ),
        m_CallbackGameServerChangeRequested( this, &steamclient::OnGameServerChangeRequested )
    {
    }

    void steamclient::OnGetItemCreateResult ( CreateItemResult_t *pParam, bool failure ) {
        if (pParam->m_eResult == k_EResultOK) {
            std::string mid = std::to_string(pParam->m_nPublishedFileId);
            copystring(mapid, mid.c_str(), mid.length() + 1);
            conoutf("Successfully created map ID: %s", mapid);
            if (identexists("mapidcreated")) execute("mapidcreated");
            if (pParam->m_bUserNeedsToAcceptWorkshopLegalAgreement)
            {
                string legalurl;
                formatstring(legalurl, "steam://url/CommunityFilePage/%s", mid.c_str());
                SteamFriends()->ActivateGameOverlayToWebPage(legalurl);
            }
        }
    }

    void steamclient::OnDownloadItemResultReceived ( DownloadItemResult_t *pParam )
    {
        if ( pParam->m_unAppID == SteamUtils()->GetAppID() )
        {
            if (downloads.find(pParam->m_nPublishedFileId) != downloads.end())
            {
                *downloads[pParam->m_nPublishedFileId] = pParam->m_eResult;
                downloads.erase(pParam->m_nPublishedFileId);
                if (pParam->m_eResult == k_EResultOK)
                {
                    uint64 workShopSize;
                    uint32 folderSize, timestamp;
                    SteamUGC()->GetItemInstallInfo( pParam->m_nPublishedFileId, &workShopSize, extensiondir, folderSize, &timestamp );
                    conoutf(CON_DEBUG, "Finished download for collection ID: %s", std::to_string(pParam->m_nPublishedFileId).c_str());
                    conoutf(CON_DEBUG, "Using content directory: %s", extensiondir);
                }
            }
        }
    }

    void steamclient::OnGameServerChangeRequested(GameServerChangeRequested_t *pParam) {
        std::string addr(pParam->m_rgchServer);
        int port = std::stoi(addr.substr(addr.find(':') + 1));
        connectserv(addr.substr(0, addr.find(':')).c_str(), port, strlen(pParam->m_rgchPassword) ? pParam->m_rgchPassword : "");
    }

}
#endif
