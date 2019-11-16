#include "Main.h"

ProjectServer server;

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

extern "C" __declspec(dllexport) void GiveFnptrsToDll(enginefuncs_t* pengfuncsFromEngine, globalvars_t* pGlobals)
{
	memcpy(server.game.gEnginefuncs, pengfuncsFromEngine, sizeof(enginefuncs_t));
	server.game.gGlobals = pGlobals;
}
