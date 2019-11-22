#include "shared/Main.h"

HINSTANCE ProjectServer::LoadLib(const char* dllFileName)
{
	return LoadLibrary(dllFileName);
}

FARPROC ProjectServer::GetAddress(HINSTANCE handle, const char* string)
{
	return GetProcAddress(handle, string);
}

void ProjectServer::Init()
{
	// we need find mp.dll and load it.
	if (!LoadMP())
	{
		MessageBox(NULL, "Unable Find or Load DLL.", "LoadMP", 0);
		exit(0);
	}

	// after passing above LoadMP, we can give our func to engine, else not working.
	if (!HookMPFunc())
	{
		MessageBox(NULL, "Failed To Find Function.", "LoadMP", 0);
		exit(0);
	}

	if (_DEBUG)
		MessageBox(NULL, "If You See Me, Means That I'm Passed Above Function", "LoadMP", 0);
}

// True = continue, False = Show Message (Check Init)
bool ProjectServer::LoadMP()
{
	char gameDir[512];
	char buf[512];

	const char* knownPath = "dlls\\mp.dll";

	memset(&gameDir, 0, sizeof(gameDir));

	server.game.gEnginefuncs->pfnGetGameDir(gameDir);

	if (!getcwd(buf, sizeof(buf)))
		return FALSE;

	char comb[512];
	sprintf(comb, "%s\\%s\\%s", buf, gameDir, knownPath);

	if (!(mp = LoadLib(comb)))
		return false;

	return TRUE;
}

// True = continue, False = Show Message (Check Init)
bool ProjectServer::HookMPFunc()
{
	GiveToEngine giveToEngine;
	NEW_DLL_FUNCTIONS_FN newAPI;
	APIFUNCTION2 oldAPI2;
	APIFUNCTION oldAPI1;

	// GiveFnptrsToDll
	if ((giveToEngine = (GiveToEngine)GetAddress(mp, "GiveFnptrsToDll")))
		giveToEngine(server.game.gEnginefuncs, server.game.gGlobals);
	else return false;

	// GetNewDLLFunctions
	if ((newAPI = (NEW_DLL_FUNCTIONS_FN)GetAddress(mp, "GetNewDLLFunctions")))
		server.game.api.newAPI = (NEW_DLL_FUNCTIONS*)malloc(sizeof(NEW_DLL_FUNCTIONS));
	else return false;

	// Check API2 or API
	if ((oldAPI2 = (APIFUNCTION2)GetAddress(mp, "GetEntityAPI2")))
		server.game.api.oldAPI = (DLL_FUNCTIONS*)malloc(sizeof(DLL_FUNCTIONS));
	else
		if ((oldAPI1 = (APIFUNCTION)GetAddress(mp, "GetEntityAPI")))
			server.game.api.oldAPI = (DLL_FUNCTIONS*)malloc(sizeof(DLL_FUNCTIONS));
		else
			return false;

	return true;
}

// Test Fucking Macro
#define GET_FUNC_TABLE_FROM_GAME(gamedll, pfnGetFuncs, STR_GetFuncs, struct_field, API_TYPE, TABLE_TYPE, vers_pass, vers_int, vers_want, gotit) \
		if((pfnGetFuncs = (API_TYPE) DLSYM(gamedll.handle, STR_GetFuncs))) { \
			gamedll.funcs.struct_field = (TABLE_TYPE*) calloc(1, sizeof(TABLE_TYPE)); \
			if(!gamedll.funcs.struct_field) {\
				META_ERROR("malloc failed for gamedll struct_field: %s", STR_GetFuncs); \
			} \
			else if(pfnGetFuncs(gamedll.funcs.struct_field, vers_pass)) { \
				META_DEBUG(3, ("dll: Game '%s': Found %s", gamedll.name, STR_GetFuncs)); \
				gotit=1; \
			} \
			else { \
				META_ERROR("dll: Failure calling %s in game '%s'", STR_GetFuncs, gamedll.name); \
				free(gamedll.funcs.struct_field); \
				gamedll.funcs.struct_field=NULL; \
				if(vers_int != vers_want) { \
					META_ERROR("dll: Interface version didn't match; we wanted %d, they had %d", vers_want, vers_int); \
					/* reproduce error from engine */ \
					META_CONS("=================="); \
					META_CONS("Game DLL version mismatch"); \
					META_CONS("DLL version is %d, engine version is %d", vers_int, vers_want); \
					if(vers_int > vers_want) \
						META_CONS("Engine appears to be outdated, check for updates"); \
					else \
						META_CONS("The game DLL for %s appears to be outdated, check for updates", GameDLL.name); \
					META_CONS("=================="); \
					ALERT(at_error, "Exiting...\n"); \
				} \
			} \
		} \
		else { \
			META_DEBUG(5, ("dll: Game '%s': No %s", gamedll.name, STR_GetFuncs)); \
			gamedll.funcs.struct_field=NULL; \
		}
