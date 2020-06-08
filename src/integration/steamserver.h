#ifdef STEAM_ENABLED
#include "steam_gameserver.h"

namespace game {
    struct steamserver: serverintegration {
        int setup(int ip, int port) {
            if ( !SteamGameServer_Init(ip, port + 3, port, port + 2, eServerModeInvalid, "") ) return 1;
            return 0;
        }
    };
}
#endif
