#ifndef Main_H
#define Main_H

//#define EXPORT __declspec(dllexport)

#include <winsani_in.h>
#include <windows.h>
#include <winsani_out.h>
#include <stdio.h>
#include <direct.h>

#include <wrect.h>
#include <interface.h>
#include "extdll.h"

typedef int (*pfnUserMsgHook)(const char* pszName, int iSize, void* pbuf);

#include <cdll_int.h>
#include <cdll_dll.h>
#include "cdll_export.h"
#include <eiface.h>
#include "util.h"
#include "cbase.h"
#include <client.h>

#define VIDEOMODE_SOFTWARE 0
#define VIDEOMODE_OPENGL 1
#define VIDEOMODE_D3D 2

extern cl_enginefunc_t gEngfuncs;

#include <pm_shared.h>

#include <hlsdkext/UtlVector.h>
#include <hlsdkext/MemPool.h>

// Custom Class
#include "Classes.h"

extern ProjectServer server;

extern struct cvar_s* developer;

// Enginecallback
#include "NewEngineCallback.h"

void GameDLLInit(void);
#endif // !Main_H
