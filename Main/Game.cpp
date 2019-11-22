#include "shared/Main.h"

cvar_t* g_psv_gravity, * g_psv_aim;
cvar_t* g_footsteps;
cvar_t* g_psv_accelerate, * g_psv_friction, * g_psv_stopspeed;

cvar_t displaysoundlist = { "displaysoundlist", "0" };

cvar_t timelimit = { "mp_timelimit", "0", FCVAR_SERVER };
cvar_t friendlyfire = { "mp_friendlyfire", "0", FCVAR_SERVER };
cvar_t flashlight = { "mp_flashlight", "0", FCVAR_SERVER };

cvar_t decalfrequency = { "decalfrequency", "30", FCVAR_SERVER };

cvar_t allowmonsters = { "mp_allowmonsters", "0", FCVAR_SERVER };
cvar_t roundtime = { "mp_roundtime", "5", FCVAR_SERVER };
cvar_t buytime = { "mp_buytime", "1.5", FCVAR_SERVER };
#ifdef _DEBUG
cvar_t freezetime = { "mp_freezetime", "0", FCVAR_SERVER };
#else
cvar_t freezetime = { "mp_freezetime", "6", FCVAR_SERVER };
#endif
cvar_t c4timer = { "mp_c4timer", "45", FCVAR_SERVER };

cvar_t ghostfrequency = { "mp_ghostfrequency", "0.1", FCVAR_SERVER };
cvar_t autokick = { "mp_autokick", "1", FCVAR_SERVER };

cvar_t restartround = { "sv_restartround", "0", FCVAR_SERVER };
cvar_t sv_restart = { "sv_restart", "0", FCVAR_SERVER };

cvar_t limitteams = { "mp_limitteams", "2", FCVAR_SERVER };
cvar_t autoteambalance = { "mp_autoteambalance", "1", FCVAR_SERVER };
cvar_t tkpunish = { "mp_tkpunish", "0", FCVAR_SERVER };
cvar_t hostagepenalty = { "mp_hostagepenalty", "13", FCVAR_SERVER };
cvar_t mirrordamage = { "mp_mirrordamage", "0", FCVAR_SERVER };
cvar_t logmessages = { "mp_logmessages", "0", FCVAR_SERVER };
cvar_t forcecamera = { "mp_forcecamera", "0", FCVAR_SERVER };
cvar_t forcechasecam = { "mp_forcechasecam", "0", FCVAR_SERVER };
cvar_t mapvoteratio = { "mp_mapvoteratio", "0.66", FCVAR_SERVER };
cvar_t logdetail = { "mp_logdetail", "0", FCVAR_SERVER };
#ifdef _DEBUG
cvar_t startmoney = { "mp_startmoney", "16000", FCVAR_SERVER };
#else
cvar_t startmoney = { "mp_startmoney", "800", FCVAR_SERVER };
#endif
cvar_t maxrounds = { "mp_maxrounds", "0", FCVAR_SERVER };
cvar_t fadetoblack = { "mp_fadetoblack", "0", FCVAR_SERVER };
cvar_t windifference = { "mp_windifference", "1", FCVAR_SERVER };
cvar_t playerid = { "mp_playerid", "0", FCVAR_SERVER };
cvar_t winlimit = { "mp_winlimit", "0", FCVAR_SERVER };
cvar_t allow_spectators = { "allow_spectators", "1.0", FCVAR_SERVER };
cvar_t mp_chattime = { "mp_chattime", "10", FCVAR_SERVER };
cvar_t kick_percent = { "mp_kickpercent", "0.66", FCVAR_SERVER };

cvar_t fragsleft = { "mp_fragsleft", "0", FCVAR_SERVER | FCVAR_UNLOGGED };
cvar_t timeleft = { "mp_timeleft", "0", FCVAR_SERVER | FCVAR_UNLOGGED };

cvar_t humans_join_team = { "humans_join_team", "any", FCVAR_SERVER };

void GameDLLInit(void)
{
	g_psv_gravity = GetCvarPointer("sv_gravity");
	g_psv_aim = GetCvarPointer("sv_aim");
	g_footsteps = GetCvarPointer("mp_footsteps");
	g_psv_accelerate = GetCvarPointer("sv_accelerate");
	g_psv_friction = GetCvarPointer("sv_friction");
	g_psv_stopspeed = GetCvarPointer("sv_stopspeed");

	CvarRegister(&displaysoundlist);

	CvarRegister(&timelimit);
	CvarRegister(&friendlyfire);
	CvarRegister(&flashlight);

	CvarRegister(&decalfrequency);

	CvarRegister(&allowmonsters);
	CvarRegister(&roundtime);
	CvarRegister(&buytime);
	CvarRegister(&freezetime);
	CvarRegister(&c4timer);
	CvarRegister(&ghostfrequency);
	CvarRegister(&autokick);

	CvarRegister(&restartround);
	CvarRegister(&sv_restart);

	CvarRegister(&limitteams);
	CvarRegister(&autoteambalance);
	CvarRegister(&tkpunish);
	CvarRegister(&hostagepenalty);
	CvarRegister(&mirrordamage);
	CvarRegister(&logmessages);
	CvarRegister(&forcecamera);
	CvarRegister(&forcechasecam);

	CvarRegister(&mapvoteratio);
	CvarRegister(&maxrounds);
	CvarRegister(&winlimit);
	CvarRegister(&windifference);
	CvarRegister(&fadetoblack);
	CvarRegister(&logdetail);
	CvarRegister(&startmoney);
	CvarRegister(&playerid);
	CvarRegister(&allow_spectators);
	CvarRegister(&mp_chattime);

	CvarRegister(&kick_percent);
	CvarRegister(&fragsleft);
	CvarRegister(&timeleft);

	CvarRegister(&humans_join_team);

	ServerCommand("exec skill.cfg\n");
}