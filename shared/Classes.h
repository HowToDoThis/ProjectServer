#ifndef Classes_H
#define Classes_H

class LogSystem
{
public:
	void Console(const char* msg, ...);
	void DevCon(const char* msg, ...);
};

class Engine
{
	// Custom
public:
	API api;

public:
	enginefuncs_t* gEnginefuncs;
	globalvars_t* gGlobals;
};

class ProjectServer
{
	// Custom Class or Function
public:
	LogSystem logSys;

	// Engine
public:
	Engine game;

	// Function
public:
	HINSTANCE LoadLib(const char* dllFileName);
	FARPROC GetAddress(HINSTANCE handle, const char* string);

	void Init();
	bool LoadMP();
	bool HookMPFunc();

private:
	HINSTANCE mp;
};

#endif // !Classes_H
