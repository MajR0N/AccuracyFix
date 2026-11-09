#pragma once

/**
* global_get(glb_trace_flags) values
* @note Custom flags that we can retrieve in pfnShouldCollide/TraceLine/TraceHull
*/
#define FTRACE_BULLET                   (1<<16)
#define FTRACE_FLASH                    (1<<17)
#define FTRACE_KNIFE                    (1<<18)

enum PlayerState { STATE_STAND, STATE_MOVE, STATE_DUCK, STATE_AIR, STATE_MAX };

class CAccuracyFix
{
public:
	void ServerActivate();
	void TraceLine(const float* vStart, const float* vEnd, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr);

	cvar_t* m_af_spread_all;
	cvar_t* m_af_spread[MAX_WEAPONS + 1];
	cvar_t* m_af_spread_state[STATE_MAX];
};

extern CAccuracyFix gAccuracyFix;
