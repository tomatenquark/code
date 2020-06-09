namespace integration {
    struct clientintegration {
        virtual int setup() { return 0; }

        virtual void cancelticket() {}
        virtual void getticket(char* ticket) {};
        virtual int getsteamid() { return 0; }
        virtual int getticketlength() { return 0; }

    };

    struct serverintegration {
        virtual int setup(int unIP, int usGamePort) { return 0; }
    };
}

