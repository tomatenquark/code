#ifdef STEAM_ENABLED
#include "steam_gameserver.h"

namespace integration {
    struct steamserver: serverintegration {
        int setup(int ip, int port) override
        {
            if ( !SteamGameServer_Init(ip, port + 4, port, port + 3, eServerModeInvalid, "") ) return 1;
            return 0;
        }

        void answerticket(int id, int length, const char * ticket) override
        {
            CSteamID steamId = CSteamID{ (uint64)id };
            SteamGameServer()->BeginAuthSession( ticket, length, steamId );
        }
    };
}
#endif
