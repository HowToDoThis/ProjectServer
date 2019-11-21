#include "shared/Main.h"

NEW_DLL_FUNCTIONS gNewDLLFunctions;

static DLL_FUNCTIONS gFunctionTable =
{
	GameDLLInit,
	DispatchSpawn,
	DispatchThink,
	DispatchUse,
	DispatchTouch,
	DispatchBlocked,
	DispatchKeyValue,
	DispatchSave,
	DispatchRestore,
	DispatchObjectCollsionBox,
	SaveWriteFields,
	SaveReadFields,
	SaveGlobalState,
	RestoreGlobalState,
	ResetGlobalState,
	ClientConnect,
	ClientDisconnect,
	ClientKill,
	ClientPutInServer,
	ClientCommand,
	ClientUserInfoChanged,
	ServerActivate,
	ServerDeactivate,
	PlayerPreThink,
	PlayerPostThink,
	StartFrame,
	ParmsNewLevel,
	ParmsChangeLevel,
	GetGameDescription,
	PlayerCustomization,
	SpectatorConnect,
	SpectatorDisconnect,
	SpectatorThink,
	Sys_Error,
	PM_Move,
	PM_Init,
	PM_FindTextureType,
	SetupVisibility,
	UpdateClientData,
	AddToFullPack,
	CreateBaseline,
	RegisterEncoders,
	GetWeaponData,
	CmdStart,
	CmdEnd,
	ConnectionlessPacket,
	GetHullBounds,
	CreateInstancedBaselines,
	InconsistentFile,
	AllowLagCompensation
};

extern "C"
{
	int GetEntityAPI(DLL_FUNCTIONS* pFunctionTable, int interfaceVersion)
	{
		if (developer->value)
			server.logSys.Console("GetEntityAPI: iVersion = %d", interfaceVersion);

		if (!pFunctionTable)
		{
			server.logSys.Console("GetEntityAPI: Null pFunctionTable");
			return 0;
		}

		if (interfaceVersion != INTERFACE_VERSION)
		{
			server.logSys.Console("GetEntityAPI: Version Mismatch. DLL=%d, API=%d", interfaceVersion, INTERFACE_VERSION);
			return 0;
		}

		memcpy(pFunctionTable, &gFunctionTable, sizeof(DLL_FUNCTIONS));

		return 1;
	}

	CBASE_DLLEXPORT int GetEntityAPI2(DLL_FUNCTIONS* pFunctionTable, int* interfaceVersion)
	{
		if (developer->value)
			server.logSys.Console("GetEntityAPI2: iVersion = %d", interfaceVersion);

		if (!pFunctionTable)
		{
			server.logSys.Console("GetEntityAPI2: Null pFunctionTable");
			return 0;
		}

		if (*interfaceVersion != INTERFACE_VERSION)
		{
			server.logSys.Console("GetEntityAPI2: Version Mismatch. DLL=%d, API=%d", interfaceVersion, INTERFACE_VERSION);
			*interfaceVersion = INTERFACE_VERSION;
			return 0;
		}

		memcpy(pFunctionTable, &gFunctionTable, sizeof(DLL_FUNCTIONS));

		return 1;
	}

}


int GetNewDLLFunctions(NEW_DLL_FUNCTIONS* pFunctionTable, int* interfaceVersion)
{
	if (developer->value)
		server.logSys.Console("GetNewDLL: iVersion = %d", interfaceVersion);

	if (!pFunctionTable)
	{
		server.logSys.Console("GetNewDLL: Null pFunctionTable");
		return 0;
	}

	if (*interfaceVersion != NEW_DLL_FUNCTIONS_VERSION)
	{
		server.logSys.Console("GetNewDLL: Version Mismatch. DLL=%d, API=%d", interfaceVersion, NEW_DLL_FUNCTIONS_VERSION);
		*interfaceVersion = NEW_DLL_FUNCTIONS_VERSION;
		return 0;
	}

	pFunctionTable->pfnOnFreeEntPrivateData = gNewDLLFunctions.pfnOnFreeEntPrivateData;
	pFunctionTable->pfnGameShutdown = gNewDLLFunctions.pfnGameShutdown;
	pFunctionTable->pfnShouldCollide = gNewDLLFunctions.pfnShouldCollide;
	return 1;
}
