namespace integration {
    struct clientintegration {
        int setup() { return 0; }
        void cleanup() {}
        void update() {}
        void getappdir(char *installdir) {};

        void cancelticket() {}
        void getticket(int* ticket) {};
        void getsteamid(char* id) {};
        int getticketlength() { return 0; }

        void setachievement(const char* achievement) {}

        void createmapid() {}
        void updatemapbyid(const char* id, const char* title, const char* content, const char* desc = NULL, const char* preview = NULL) {}
        bool downloadmap(const char* id, int *status) { return false; }
    };

    struct serverintegration {
        virtual void setup(int unIP, int usGamePort) { }
        virtual void cleanup() {}
        virtual void update() {}

        virtual bool answerticket(int clientnum, char* steamid, int length, int* ticket) { return false; }
        virtual void endsession(int clientnum) {}
    };
}
