#include "Main.h"

CUtlVector<hash_item_t> stringsHashTable;
CMemoryPool hashItemMemPool(sizeof(hash_item_t), 64);

void EmptyEntityHashTable(void)
{
	int i;
	hash_item_t* item;
	hash_item_t* temp;
	hash_item_t* free;

	for (i = 0; i < stringsHashTable.Count(); i++)
	{
		item = &stringsHashTable[i];
		temp = item->next;
		item->pev = NULL;
		item->pevIndex = 0;
		item->lastHash = NULL;
		item->next = NULL;

		while (temp)
		{
			free = temp;
			temp = temp->next;
			hashItemMemPool.Free(free);
		}
	}
}

void RemoveEntityHashValue(struct entvars_s* pev, const char* value, hash_types_e fieldType)
{
	int hash = 0;
	hash_item_t* item;
	hash_item_t* last;
	int pevIndex;
	int count;

	count = stringsHashTable.Count();
	hash = CaseInsensitiveHash(value, count);
	pevIndex = ENTINDEX(ENT(pev));

	if (fieldType == CLASSNAME)
	{
		hash = hash % count;
		item = &stringsHashTable[hash];

		while (item->pev)
		{
			if (!strcmp(STRING(item->pev->classname), STRING(pev->classname)))
				break;

			hash = (hash + 1) % count;
			item = &stringsHashTable[hash];
		}

		if (item->pev)
		{
			last = item;

			while (item->next)
			{
				if (item->pev == pev)
					break;

				last = item;
				item = item->next;
			}

			if (item->pev == pev)
			{
				if (last == item)
				{
					if (item->next)
					{
						item->pev = item->next->pev;
						item->pevIndex = item->next->pevIndex;
						item->lastHash = NULL;
						item->next = item->next->next;
					}
					else
					{
						item->pev = NULL;
						item->lastHash = NULL;
						item->pevIndex = 0;
					}
				}
				else
				{
					if (stringsHashTable[hash].lastHash == item)
						stringsHashTable[hash].lastHash = NULL;

					last->next = item->next;
					hashItemMemPool.Free(item);
				}
			}
		}
	}
}

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

int GetEntityAPI(DLL_FUNCTIONS* pFunctionTable, int interfaceVersion)
{
	if (!pFunctionTable || interfaceVersion != INTERFACE_VERSION)
		return 0;

	memcpy(pFunctionTable, &gFunctionTable, sizeof(DLL_FUNCTIONS));

	stringsHashTable.SetSize(2048);

	for (int i = 0; i < stringsHashTable.Count(); i++)
		stringsHashTable[i].next = NULL;

	EmptyEntityHashTable();
	return 1;
}

void OnFreeEntPrivateData(edict_t* pEnt)
{
	CBaseEntity* pEntity = CBaseEntity::Instance(pEnt);

	if (!pEntity)
		return;

	pEntity->UpdateOnRemove();
	RemoveEntityHashValue(pEntity->pev, STRING(pEntity->pev->classname), CLASSNAME);
}

static NEW_DLL_FUNCTIONS gNewDLLFunctions =
{
	OnFreeEntPrivateData,
	NULL,
	NULL
};

int GetNewDLLFunctions(NEW_DLL_FUNCTIONS* pFunctionTable, int* interfaceVersion)
{
	if (!pFunctionTable || *interfaceVersion != NEW_DLL_FUNCTIONS_VERSION)
	{
		*interfaceVersion = NEW_DLL_FUNCTIONS_VERSION;
		return 0;
	}

	pFunctionTable->pfnOnFreeEntPrivateData = gNewDLLFunctions.pfnOnFreeEntPrivateData;
	pFunctionTable->pfnGameShutdown = gNewDLLFunctions.pfnGameShutdown;
	pFunctionTable->pfnShouldCollide = gNewDLLFunctions.pfnShouldCollide;
	return 1;
}
