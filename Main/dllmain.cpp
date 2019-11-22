#include "shared/Main.h"

cl_enginefunc_t gEngfuncs;
ProjectServer server;
cvar_s* developer = NULL;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
	}

	return TRUE;
}

extern "C" EXPORT void GiveFnptrsToDll(enginefuncs_t * pengfuncsFromEngine, globalvars_t * pGlobals)
{
	server.game.gEnginefuncs = pengfuncsFromEngine;
	server.game.gGlobals = pGlobals;

	developer = server.game.gEnginefuncs->pfnCVarGetPointer("developer");

	server.Init();
}
