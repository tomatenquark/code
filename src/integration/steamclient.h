#ifdef STEAM_ENABLED
#include "steam_api.h"

namespace game {
    struct steamclient: clientintegration {
        HAuthTicket authTicket = k_HAuthTicketInvalid;
        uint32 ticketLength;
        char * ticketBuffer;

        ~steamclient() {
            SteamAPI_Shutdown();
        }

        int setup() {
            if ( SteamAPI_RestartAppIfNecessary( k_uAppIdInvalid ) ) return 1; // Replace with your App ID
            if ( !SteamAPI_Init() ) return 1;
            return 0;
        }

        void cancelticket() {
            if ( authTicket != k_HAuthTicketInvalid ) SteamUser()->CancelAuthTicket( authTicket );
        }

        char * getticket() {
            cancelticket();
            authTicket = SteamUser()->GetAuthSessionTicket( ticketBuffer, 512, &ticketLength );
            return ticketBuffer;
        }

        int getticketlength() {
            return (int)ticketLength;
        }
    };
}
#endif
