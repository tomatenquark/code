#ifdef STEAM_ENABLED
#include "steam_gameserver.h"

namespace integration {
    struct steamserver: serverintegration {
        int setup(int ip, int port) {
            if ( !SteamGameServer_Init(ip, port + 4, port, port + 3, eServerModeInvalid, "") ) return 1;
            return 0;
        }
    };
}
#endif
