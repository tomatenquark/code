#ifdef STEAM_ENABLED
#include "steam_gameserver.h"

#include <string>
#include <map>

#define TOMATENQUARK_SERVER_VERSION "1.0.0.0"

#define SPACEWAR_AUTHENTICATION_PORT 8766

#define TOMATENQUARK_QUERY_PORT 8767

namespace integration {
    struct steamserver: serverintegration {
    private:
        bool api_initialized = false;
        std::map<int, uint64> citosteamid;

    public:
        steamserver();

        void setup(int port) override
        {
            api_initialized = SteamGameServer_Init(INADDR_ANY, SPACEWAR_AUTHENTICATION_PORT, port, TOMATENQUARK_QUERY_PORT,
                                                   static_cast<EServerMode>(server::getserverprotection() + 1), TOMATENQUARK_SERVER_VERSION);
            if (!api_initialized) {
                conoutf("Failed to initialize Steam API");
            }
        }

        void cleanup() override
        {
            SteamGameServer_Shutdown();
        }

        void update() override
        {
            if (!api_initialized) return;
            SteamGameServer()->SetGameDescription(server::getservermodt());
            SteamGameServer()->SetServerName(server::getserverdesc());
            SteamGameServer()->SetMapName(server::getservermap());
            SteamGameServer()->SetMaxPlayerCount(server::getservermaxclients());
            SteamGameServer()->SetBotPlayerCount(server::getservernumbots());
            SteamGameServer()->SetKeyValue("mode", server::modename(server::getservermode()));
            SteamGameServer()->SetPasswordProtected( strlen(server::getserverpass() ));
            SteamGameServer_RunCallbacks();
        }

        bool answerticket(int clientnum, char* id, int length, int * ticket) override
        {
            if (!api_initialized) return false;
            uint64 value = std::stoull( id );
            CSteamID steamId = CSteamID{ value };
            EBeginAuthSessionResult authSessionResult = SteamGameServer()->BeginAuthSession( ticket, length, steamId );
            bool valid = authSessionResult == k_EBeginAuthSessionResultOK;
            citosteamid[clientnum] = value;
            return valid;
        }

        void endsession(int clientnum) override
        {
            if (!api_initialized) return;
            if (citosteamid.find(clientnum) == citosteamid.end()) return;
            CSteamID steamId = CSteamID{ citosteamid[clientnum] };
            SteamGameServer()->EndAuthSession( steamId );
            citosteamid.erase(clientnum);
        }

        STEAM_CALLBACK( steamserver, OnValidateAuthTicketResponseReceived, ValidateAuthTicketResponse_t,
                        m_CallbackValidateAuthTicketResponseReceived );
    };

    steamserver::steamserver():
        m_CallbackValidateAuthTicketResponseReceived( this, &steamserver::OnValidateAuthTicketResponseReceived )
    {

    }

    void steamserver::OnValidateAuthTicketResponseReceived(ValidateAuthTicketResponse_t *pParam) {
        if (pParam->m_eAuthSessionResponse == k_EAuthSessionResponseOK)
        {
            for (auto it: citosteamid)
            {
                if (it.second == pParam->m_SteamID.ConvertToUint64())
                {
                    disconnect_client(it.first, DISC_PROTECTED);
                }
            }
        }
    }
}
#endif
