// bomb.h: client and server state for bomb gamemode
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

#ifdef SERVMODE
    struct seekersinfo {
        int cn;
        bool freezed;
        seekersinfo(int cn_, bool freezed_): cn(cn_), freezed(freezed_) {}
    };
#endif

#ifndef SERVMODE

#define STARTINVISIBLESECS 30
#define ishider(ci) (strcmp(ci->team, TEAM_HIDE) == 0 && ci->state != CS_SPECTATOR ? true : false)

    void setup() {
    }

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

    bool isinvisible(fpsent *d) {
        if (ishider(d) && (totalmillis-maptime < STARTINVISIBLESECS*1000 || ishider(player1))) return true;
        return false;
    }

    void rendergame() {
    }

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

    void killed(fpsent *d, fpsent *actor) {
    }

    void respawned(fpsent *d) {
    }

    void pickspawn(fpsent *d) {
        findplayerspawn(player1);
    }

    bool hidefrags() {
        return true;
    }

#else

// #define ishider(d) (strcmp(d->team, TEAM_HIDE) == 0 ? true : false)
#define ishider(ci) (strcmp(ci->team, TEAM_HIDE) == 0 && ci->state.state != CS_SPECTATOR ? true : false)
#define isseeker(ci) (strcmp(ci->team, TEAM_SEEK) == 0 && ci->state.state != CS_SPECTATOR ? true : false)

    vector<seekersinfo*> seekersinfos;
    int lastupdatecheck;

    void setup() {
        lastupdatecheck = totalmillis;
        seekersinfos.deletecontents();
        initplayers();
    }

    void initplayers() {
        loopv(clients) initplayer(clients[i]);
        vector<clientinfo*> activeplayers = getactiveplayers();
        if(activeplayers.length() < 2) return;
        int seeker = rnd(activeplayers.length());
        setseeker(activeplayers[seeker]);
    }

    void initplayer(clientinfo *ci) {
        sethider(ci);
    }

    void initclient(clientinfo *ci, packetbuf &p, bool connecting) {
        setseeker(ci);
    }

    void connected(clientinfo *ci) {
        setseeker(ci);
    }

    void leavegame(clientinfo *ci, bool disconnecting) {
        loopv(seekersinfos) if(seekersinfos[i]->cn == ci->clientnum){
            seekersinfos[i]->cn = -1;
        }
    }

    void cleanup() {
        seekersinfos.deletecontents();
    }

    bool checkfinished() {
        if(interm) return false;
        // if all seekers are freezed and there are at least 2 players
        if (getactiveplayers().length() >= 2 && getnonfreezedseekers() == 0) return true;
        // check if no hider is alive
        loopv(clients) if (ishider(clients[i])) return false;
        return true;
    }

    void update() {
        if (totalmillis > lastupdatecheck + 1000) {
            lastupdatecheck = totalmillis;
            if(checkfinished()) game::forceintermission();
        }
    }

    void intermission() {
    }

    void spawned(fpsent *d) {
    }

    bool canspawn(clientinfo *ci, bool connecting) {
        return true;
    }

    bool canhit(clientinfo *target, clientinfo *actor) {
        // teamkills and suicides are disabled; hiders can't kill
        // defformatstring(msg)("sameplayer:%s sameteam:%s ishider(actor):%s", actor==target?"true":"false", isteam(actor->team, target->team)?"true":"false", ishider(actor)?"true":"false");
        // sendservmsg(msg);
        // if(!m_freeze && isteam(actor->team, target->team) || ishider(actor)) return false;
        if (!actor || !target || actor==target) return false;
        /*if (!m_freeze) {
            if (isteam(actor->team, target->team) || ishider(actor)) return false;
        } else {
            if (ishider(actor) && isseeker(target)) {
                if (isfreezed(target)) return false;
                // freeze seeker
                setfreezedstate(target, true);
                sendf(target->clientnum, 1, "rii", N_PAUSEGAME, 1);
                defformatstring(msg)("%s got freezed by %s!", target->name, actor->name);
                announceseekers(msg);
                return false;
            } else if (isseeker(actor) && isseeker(target)) {
                if (!isfreezed(target)) return false;
                // unfreeze seeker
                setfreezedstate(target, false);
                sendf(target->clientnum, 1, "rii", N_PAUSEGAME, 0);
                defformatstring(msg)("You got unfreezed by %s", actor->name);
                sendf(target->clientnum, 1, "ri3s ", N_HUDANNOUNCE, 3000, E_ZOOM_OUT, msg);
                defformatstring(msg2)("You unfreezed %s", target->name);
                sendf(actor->clientnum, 1, "ri3s ", N_HUDANNOUNCE, 3000, E_ZOOM_OUT, msg2);
                return false;
            }
        }*/
        conoutf("d");
        return true;
    }

    void died(clientinfo *target, clientinfo *actor) {
        if (target && ishider(target)) {
            setseeker(target);
            int remaining = getremaininghiders();
            if (!actor) {
                if (remaining > 0) {
                    defformatstring(msg, "%s suicided! %d Hiders remaining!", target->name, remaining);
                    //sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 3000, E_ZOOM_OUT, msg);
                } else {
                    defformatstring(msg, "%s suicided! All Hiders eliminated!", target->name);
                    //sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 3000, E_ZOOM_OUT, msg);
                }
            } else {
                if (remaining > 0) {
                    defformatstring(msg, "%s killed %s! %d Hiders remaining!", actor->name, target->name, remaining);
                    //sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 3000, E_ZOOM_OUT, msg);
                } else {
                    defformatstring(msg, "%s killed %s! All Hiders eliminated!", actor->name, target->name);
                    //sendf(-1, 1, "ri3s ", N_HUDANNOUNCE, 3000, E_ZOOM_OUT, msg);
                }
            }
        }
    }

    bool canchangeteam(clientinfo *ci, const char *oldteam, const char *newteam) {
          return false;
    }

    void setseeker(clientinfo *ci) {
        copystring(ci->team, TEAM_SEEK, MAXTEAMLEN+1);
        sendf(-1, 1, "riisi", N_SETTEAM, ci->clientnum, ci->team, 1);
        seekersinfos.add(new seekersinfo(ci->clientnum, false));
    }

    void sethider(clientinfo *ci) {
        copystring(ci->team, TEAM_HIDE, MAXTEAMLEN+1);
        sendf(-1, 1, "riisi", N_SETTEAM, ci->clientnum, ci->team, 1);
    }

    vector<clientinfo*> getactiveplayers() {
        vector<clientinfo*> activepl;
        loopv(clients){
            clientinfo* ci = clients[i];
            if(ci->state.state == CS_SPECTATOR) continue;
            activepl.add(ci);
        }
        return activepl;
    }

    int getremaininghiders() {
        int numhiders = 0;
        loopv(clients) if (ishider(clients[i])) numhiders++;
        return numhiders;
    }

    bool isfreezed(clientinfo *ci) {
        loopv(seekersinfos) if(seekersinfos[i]->cn == ci->clientnum && seekersinfos[i]->freezed) return true;
        return false;
    }

    void setfreezedstate(clientinfo *ci, bool state) {
        loopv(seekersinfos) if(seekersinfos[i]->cn == ci->clientnum) seekersinfos[i]->freezed = state;
    }

    int getnonfreezedseekers() {
        int numseekers = 0;
        loopv(seekersinfos) if(seekersinfos[i]->cn != -1 && !seekersinfos[i]->freezed) numseekers++;
        return numseekers;
    }

    void announceseekers(char* msg) {
        /*loopv(clients) if (isseeker(clients[i])) {
            sendf(clients[i]->clientnum, 1, "ri3s ", N_HUDANNOUNCE, 1000, E_STATIC_TOP, msg);
        }*/
    }

#endif

};

#ifndef SERVMODE
extern hideandseekclientmode hideandseekmode;
#endif

#elif SERVMODE

#else

#endif
