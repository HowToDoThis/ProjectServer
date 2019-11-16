#ifndef Main_H
#define Main_H

#include <Windows.h>

#include <extdll.h>
#include <cbase.h>
//#include <eiface.h>

#include <client.h>
#include <pm_shared.h>

#include <util.h>
#include <hlsdkext/UtlVector.h>
#include <hlsdkext/MemPool.h>

// Custom Class
#include "Classes.h"

extern ProjectServer server;

typedef enum
{
	CLASSNAME
}
hash_types_e;

typedef struct hash_item_s
{
	entvars_t* pev;
	struct hash_item_s* next;
	struct hash_item_s* lastHash;
	int pevIndex;
}
hash_item_t;

extern CUtlVector<hash_item_t> stringsHashTable;

// Enginecallback
#include "NewEngineCallback.h"

extern void GameDLLInit(void);
#endif // !Main_H
