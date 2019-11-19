#ifndef Classes_H
#define Classes_H

class LogSystem
{
public:
	void Console(const char* msg, ...);
};

class Engine
{
public:
	enginefuncs_t* gEnginefuncs;
	globalvars_t* gGlobals;
};

class ProjectServer
{
public:
	Engine game;
};

#endif // !Classes_H
