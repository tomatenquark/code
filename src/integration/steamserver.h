#ifdef STEAM_ENABLED
#include "steam_gameserver.h"

#include <string>

namespace integration {
    struct steamserver: serverintegration {
    private:
        bool api_initialized = false;

    public:
        steamserver();

        void setup(int ip, int port) override
        {
            api_initialized = SteamGameServer_Init(ip, port + 4, port, port + 3,
                                                   static_cast<EServerMode>(server::getserverprotection() + 1), "1");
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

        bool answerticket(char* id, int length, int * ticket) override
        {
            if (!api_initialized) return false;
            uint64 value = std::stoull( id );
            CSteamID steamId = CSteamID{ value };
            EBeginAuthSessionResult authSessionResult = SteamGameServer()->BeginAuthSession( ticket, length, steamId );
            bool valid = authSessionResult == k_EBeginAuthSessionResultOK;
            if (valid) server::setauthenticated(id);
            return valid;
        }

        void endsession(char* steamid) override
        {
            if (!api_initialized) return;
            uint64 value = std::stoull( steamid );
            CSteamID steamId = CSteamID{ value };
            SteamGameServer()->EndAuthSession( steamId );
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
            server::setauthenticated(std::to_string(pParam->m_SteamID.ConvertToUint64()).c_str(), false);
        }
    }
}
#endif
