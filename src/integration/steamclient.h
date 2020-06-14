#ifdef STEAM_ENABLED
#include "steam_api.h"

namespace integration {
    struct steamclient: clientintegration {
        HAuthTicket authTicket = k_HAuthTicketInvalid;
        uint32 ticketLength;

        int setup() override {
            if ( SteamAPI_RestartAppIfNecessary( k_uAppIdInvalid ) ) return 1; // Replace with your App ID
            if ( !SteamAPI_Init() ) return 1;
            return 0;
        }

        void cleanup() override
        {
            SteamAPI_Shutdown();
        }

        void cancelticket() override
        {
            if ( authTicket != k_HAuthTicketInvalid ) SteamUser()->CancelAuthTicket( authTicket );
        }

        void getticket(char * ticket) override
        {
            cancelticket();
            authTicket = SteamUser()->GetAuthSessionTicket( ticket, 1024, &ticketLength );
        }

        int getticketlength() override
        {
            return (int)ticketLength;
        }

        int getsteamid() override
        {
            return SteamUser()->GetSteamID().ConvertToUint64();
        }
    };
}
#endif
