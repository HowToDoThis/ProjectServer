#include "shared/Main.h"

void ProjectServer::ProjectServerInit()
{

}

HINSTANCE ProjectServer::LoadLib(const char* dllFileName)
{
	return LoadLibrary(dllFileName);
}

FARPROC ProjectServer::GetAddress(HINSTANCE handle, const char* string)
{
	return GetProcAddress(handle, string);
}

bool ProjectServer::LoadMP()
{
	char gameDir[512];
	char buf[512];

	const char* knownPath = "dlls/mp.dll";

	memset(&gameDir, 0, sizeof(gameDir));

	server.game.gEnginefuncs->pfnGetGameDir(gameDir);

	if (!getcwd(buf, sizeof(buf)))
	{
		server.game.gEnginefuncs->pfnAlertMessage(at_error, "Unable To Find Directory.");
		return FALSE;
	}

	char comb[512];
	sprintf(comb, "%s/%s/%s", buf, gameDir, knownPath);

	if (LoadLib(comb))
	{
		server.game.gEnginefuncs->pfnAlertMessage(at_error, "Unable To Load DLL.");
		return FALSE;
	}

	return TRUE;
}