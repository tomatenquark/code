namespace integration {
    struct clientintegration {
        virtual int setup() { return 0; }

        virtual void cancelticket() {}
        virtual char * getticket() { return nullptr; }
        virtual int getticketlength() { return 0; }

    };

    struct serverintegration {
        virtual int setup(int unIP, int usGamePort) { return 0; }
    };
}

