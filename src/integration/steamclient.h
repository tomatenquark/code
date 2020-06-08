#ifdef STEAM_ENABLED
#include "steam_api.h"

namespace game {
    struct steamclient: clientintegration {
        ~steamclient() {
            SteamAPI_Shutdown();
        }

        int setup() {
            if ( SteamAPI_RestartAppIfNecessary( k_uAppIdInvalid ) ) return 1; // Replace with your App ID
            if ( !SteamAPI_Init() ) return 1;
            return 0;
        }
    };
}
#endif
