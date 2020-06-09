#ifdef STEAM_ENABLED
#include "steam_api.h"

namespace integration {
    struct steamclient: clientintegration {
        HAuthTicket authTicket = k_HAuthTicketInvalid;
        uint32 ticketLength;
        char * ticketBuffer;

        ~steamclient() {
            // TODO: Add 'cleanupintegration' function because this throws issues
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

        void getticket(char * ticket)
        {
            cancelticket();
            authTicket = SteamUser()->GetAuthSessionTicket( ticket, 512, &ticketLength );
        }

        int getticketlength() {
            return (int)ticketLength;
        }
    };
}
#endif
