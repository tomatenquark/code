#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }

struct Achievement_t
{
    int m_eAchievementID;
    const char *m_pchAchievementID;
    char m_rgchName[128];
    char m_rgchDescription[256];
    bool m_bAchieved;
    int m_iIconImage;
};

// Defining our achievements
enum EAchievements
{
    ACH_EDIT_ENTER = 0,
    ACH_EDIT_FLOATSPEED = 1,
    ACH_FIRST_BLOOD = 2,
    ACH_DOUBLE_KILL = 3,
    ACH_TRIPLE_KILL = 4,
    ACH_CATCH_ME_IF_YOU_CAN = 5,
    ACH_FLY_ME_TO_THE_MOON = 6
};