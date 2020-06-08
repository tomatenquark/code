namespace game {
    struct clientintegration {
        virtual int setup() { return 0; }
    };

    struct serverintegration {
        virtual int setup(int unIP, int usGamePort) { return 0; }
    };
}

