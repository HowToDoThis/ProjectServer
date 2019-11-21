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
};

#endif // !Classes_H
