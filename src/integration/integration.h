namespace integration {
    struct clientintegration {
        virtual int setup() { return 0; }
        virtual void cleanup() {}
        virtual void update() {}
        virtual void getappdir(char *installdir) {};

        virtual void cancelticket() {}
        virtual void getticket(char* ticket) {};
        virtual void getsteamid(char* id) {};
        virtual int getticketlength() { return 0; }

        virtual void setachievement(const char* achievement) {}

        virtual void createmapid() {}
        virtual void updatemapbyid(const char* id, const char* title, const char* content, const char* desc = NULL, const char* preview = NULL) {}
        virtual bool downloadmap(int id, int *status) { return false; }
    };

    struct serverintegration {
        virtual int setup(int unIP, int usGamePort) { return 0; }
        virtual void cleanup() {}
        virtual void update() {}

        virtual bool answerticket(char* steamid, int length, const char * ticket) { return false; }
    };
}
