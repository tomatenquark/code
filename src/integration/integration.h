namespace integration {
    struct clientintegration {
        virtual int setup() { return 0; }
        virtual void cleanup() {}
        virtual void update() {}

        virtual void cancelticket() {}
        virtual void getticket(char* ticket) {};
        virtual int getsteamid() { return 0; }
        virtual int getticketlength() { return 0; }

        virtual void setachievement(const char* achievement) {}

        virtual void createmapid() {}
    };

    struct serverintegration {
        virtual int setup(int unIP, int usGamePort) { return 0; }
        virtual void cleanup() {}
        virtual void update() {}

        virtual bool answerticket(int steamid, int length, const char * ticket) { return false; }
    };
}

