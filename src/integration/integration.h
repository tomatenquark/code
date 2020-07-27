namespace integration {
    struct clientintegration {
        virtual int setup() { return 0; }
        virtual void cleanup() {}
        virtual void update() {}
        virtual void getappdir(char *installdir) {};

        virtual void cancelticket() {}
        virtual void getticket(int* ticket) {};
        virtual void getsteamid(char* id) {};
        virtual int getticketlength() { return 0; }

        virtual void setachievement(const char* achievement) {}
        virtual int getstat(const char* stat) { return 0;  }
        virtual void setstat(const char* stat, int value) {}
        virtual void incrementstat(const char* stat, int increment) {}
        virtual void updateavgstat(const char* stat, float value, double sessionLength) {}

        virtual void createmapid() {}
        virtual void updatemapbyid(const char* id, const char* title, const char* content, const char* desc = NULL, const char* preview = NULL) {}
        virtual bool downloadmap(const char* id, int *status) { return false; }
    };

    struct serverintegration {
        virtual void setup(int usGamePort) { }
        virtual void cleanup() {}
        virtual void update() {}

        virtual bool answerticket(int clientnum, char* steamid, int length, int* ticket) { return false; }
        virtual void endsession(int clientnum) {}
    };

    namespace dummy {
        struct client: clientintegration {
            int setup() override { return 0; }
            void cleanup() override {}
            void update() override {}
            void getappdir(char *installdir) override {};

            void cancelticket() override {}
            void getticket(int* ticket) override {};
            void getsteamid(char* id) override {};
            int getticketlength() override { return 0; }

            void setachievement(const char* achievement) override {}
            int getstat(const char* stat) override { return 0; }
            void setstat(const char* stat, int value) override {}
            void incrementstat(const char* stat, int increment) override {}
            void updateavgstat(const char* stat, float value, double sessionLength) override {}

            void createmapid() override {}
            void updatemapbyid(const char* id, const char* title, const char* content, const char* desc = NULL, const char* preview = NULL) override {}
            bool downloadmap(const char* id, int *status) override { return false; }
        };

        struct server: serverintegration {
            void setup(int usGamePort) override { }
            void cleanup() override {}
            void update() override {}

            bool answerticket(int clientnum, char* steamid, int length, int* ticket) override { return false; }
            void endsession(int clientnum) override {}
        };
    }
}
