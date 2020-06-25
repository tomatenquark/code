#ifdef STEAM_ENABLED
#include "steam_gameserver.h"

namespace integration {
    struct steamserver: serverintegration {
        int setup(int ip, int port) override
        {
            if ( !SteamGameServer_Init(ip, port + 4, port, port + 3, eServerModeInvalid, "1") ) return 1;
            return 0;
        }

        void cleanup() override
        {
            SteamGameServer_Shutdown();
        }

        void update() override
        {
            SteamGameServer()->SetGameDescription(server::getservermodt());
            SteamGameServer()->SetServerName(server::getserverdesc());
            SteamGameServer()->SetMapName(server::getservermap());
            SteamGameServer()->SetMaxPlayerCount(server::getservermaxclients());
            SteamGameServer()->SetBotPlayerCount(server::getservernumbots());
            SteamGameServer()->SetKeyValue("mode", server::modename(server::getservermode()));
            SteamGameServer_RunCallbacks();
        }

        bool answerticket(int id, int length, const char * ticket) override
        {
            CSteamID steamId = CSteamID{ (uint64)id };
            EBeginAuthSessionResult authSessionResult = SteamGameServer()->BeginAuthSession( ticket, length, steamId );
            return authSessionResult != k_EBeginAuthSessionResultInvalidTicket;
        }
    };
}
#endif
