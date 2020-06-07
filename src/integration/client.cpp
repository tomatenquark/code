#include "steam_api.h"

namespace integration::steam {
    int init() {
        if ( SteamAPI_RestartAppIfNecessary( k_uAppIdInvalid ) ) // Replace with your App ID
        {
            return 1;
        }

        if ( !SteamAPI_Init() )
        {
            printf( "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n" );
            return 1;
        }

        return 0;
    }
}
