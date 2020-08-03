// hideandseek.h: client and server state for hide and seek gamemode
#ifndef PARSEMESSAGES

#define TEAM_HIDE "hide"
#define TEAM_SEEK "seek"

#ifdef SERVMODE
struct hideandseekservmode : servmode
#else
// VARP(showhideandseekrole, 0, 1, 1);
struct hideandseekclientmode : clientmode
#endif
{

#ifndef SERVMODE

#define ishider(ci) (strcmp(ci->team, TEAM_HIDE) == 0 && ci->state != CS_SPECTATOR ? true : false)

    void drawblip(fpsent *d, float x, float y, float s, const vec &pos, float size_factor) {
        float scale = calcradarscale();
        vec dir = d->o;
        dir.sub(pos).div(scale);
        float size = 0.03f * size_factor,
              xoffset = -size,
              yoffset = -size,
              dist = dir.magnitude2(), maxdist = 1 - 0.05f - 0.05f;
        if(dist >= maxdist) dir.mul(maxdist/dist);
        dir.rotate_around_z(-camera1->yaw*RAD);
        drawradar(x + s*0.5f*(1.0f + dir.x + xoffset), y + s*0.5f*(1.0f + dir.y + yoffset), size*s);
    }

    void drawhud(fpsent *d, int w, int h) {
        if(!ishider(d)) return;

        // minimap
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        int s = 1800/4, x = 1800*w/h - s - s/10, y = s/10;
        glColor4f(1, 1, 1, minimapalpha);
        if(minimapalpha >= 1) glDisable(GL_BLEND);
        bindminimap();
        drawminimap(d, x, y, s);
        if(minimapalpha >= 1) glEnable(GL_BLEND);
        glColor3f(1, 1, 1);
        float margin = 0.04f, roffset = s*margin, rsize = s + 2*roffset;
        settexture("packages/hud/radar.png", 3);
        drawradar(x - roffset, y - roffset, rsize);
        // show other players on minimap
        loopv(players) {
            fpsent *p = players[i];
            if(p == player1 || p->state!=CS_ALIVE || ishider(p)) continue;
            settexture("packages/hud/blip_red.png", 3);
            drawblip(d, x, y, s, p->o, 2.0f);
        }
    }

    void rendergame() {}

    /*void renderscoreboard(g3d_gui &g, game::scoregroup &sg, int fgcolor, int bgcolor) {

        if (showhideandseekrole) {
            g.pushlist();
            g.strut(4);
            g.text("rank", fgcolor);
            loopv(sg.players) {
                fpsent *d = sg.players[i];
                g.textf("%s", 0xFFFFDD, NULL, "");
            }
            g.poplist();
        }
    }*/

    void killed(fpsent *d, fpsent *actor) {}

    void respawned(fpsent *d) {}

    void pickspawn(fpsent *d) {
        findplayerspawn(player1);
    }

    bool hidefrags() {
        return true;
    }

#else

#define ishider(ci) (strcmp(ci->team, TEAM_HIDE) == 0 && ci->state.state != CS_SPECTATOR ? true : false)
#define isseeker(ci) (strcmp(ci->team, TEAM_SEEK) == 0 && ci->state.state != CS_SPECTATOR ? true : false)

    int lastupdatecheck;

    void setup() {
        lastupdatecheck = totalmillis;
        initplayers();
    }

    void sethider(clientinfo *ci) {
        copystring(ci->team, TEAM_HIDE, MAXTEAMLEN+1);
        sendf(-1, 1, "riisi", N_SETTEAM, ci->clientnum, ci->team, 1);
    }

    void setseeker(clientinfo *ci) {
        copystring(ci->team, TEAM_SEEK, MAXTEAMLEN+1);
        sendf(-1, 1, "riisi", N_SETTEAM, ci->clientnum, ci->team, 1);
    }

    vector<clientinfo*> getactiveclients() {
        vector<clientinfo*> activeclients;
        loopv(clients) if(clients[i]->state.state != CS_SPECTATOR) activeclients.add(clients[i]);
        return activeclients;
    }

    void initplayers() {
        loopv(clients) sethider(clients[i]);
        vector<clientinfo*> activeclients = getactiveclients();
        if(activeclients.length() < 2) return;
        int seeker = rnd(activeclients.length());
        setseeker(activeclients[seeker]);
    }

    void initclient(clientinfo *ci, packetbuf &p, bool connecting) {
        if (getnumseekers() == 0 && getnumhiders() > 0) {
            copystring(ci->team, TEAM_SEEK, MAXTEAMLEN+1);
        } else {
            copystring(ci->team, TEAM_HIDE, MAXTEAMLEN+1);
        }
        putint(p, N_SETTEAM);
        putint(p, ci->clientnum);
        sendstring(ci->team, p);
        putint(p, -1);
    }

    void cleanup() {
        loopv(clients) {
            copystring(clients[i]->team, rand() & 1 ? "evil" : "good", MAXTEAMLEN+1);
            sendf(-1, 1, "riisi", N_SETTEAM, clients[i]->clientnum, clients[i]->team, 1);
        }
    }

    int getnumseekers() {
        int numseekers = 0;
        vector<clientinfo*> activeclients = getactiveclients();
        loopv(activeclients) if (isseeker(activeclients[i])) numseekers++;
        return numseekers;
    }

    int getnumhiders() {
        int numhiders = 0;
        vector<clientinfo*> activeclients = getactiveclients();
        loopv(activeclients) if (ishider(activeclients[i])) numhiders++;
        return numhiders;
    }

    bool finished() {
        if(interm) return false;
        // check if no hider is alive
        return getnumhiders() == 0;
    }

    void update() {
        if (totalmillis > lastupdatecheck + 1000) {
            lastupdatecheck = totalmillis;
            if (finished()) startintermission();
        }
    }

    bool canspawn(clientinfo *ci, bool connecting) { return true; }

    bool canhit(clientinfo *target, clientinfo *actor) {
        // teamkills and suicides are disabled; hiders can't kill
        if (isteam(actor->team, target->team) || ishider(actor)) return false;
        return true;
    }

    void died(clientinfo *target, clientinfo *actor) {
        if (target && ishider(target)) {
            setseeker(target);
            int remaining = getnumhiders();
            if (!actor) {
                if (remaining > 0) {
                    defformatstring(msg, "%s suicided! %d Hiders remaining!", target->name, remaining);
                    sendservmsg(msg);
                } else {
                    defformatstring(msg, "%s suicided! All hiders eliminated!", target->name);
                    sendservmsg(msg);
                }
            } else {
                if (remaining > 0) {
                    defformatstring(msg, "%s killed %s! %d Hiders remaining!", actor->name, target->name, remaining);
                    sendservmsg(msg);
                } else {
                    defformatstring(msg, "%s killed %s! All hiders eliminated!", actor->name, target->name);
                    sendservmsg(msg);
                }
            }
        }
    }

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam) { return false; }

#endif

};

#ifndef SERVMODE
extern hideandseekclientmode hideandseekmode;
#endif

#elif SERVMODE

#else

#endif
