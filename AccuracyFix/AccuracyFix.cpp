#include "precompiled.h"

CAccuracyFix gAccuracyFix;

void CAccuracyFix::ServerActivate()
{
	// Spread multiplier for all weapons, >= 0 overrides the per weapon values, -1 = use per weapon
	this->m_af_spread_all = gAccuracyUtil.CvarRegister("af_spread_all", "-1.0");

	// Spread multiplier (0.0 - 1.0) per player state, multiplied with the weapon value
	this->m_af_spread_state[STATE_STAND] = gAccuracyUtil.CvarRegister("af_spread_stand", "1.0");
	this->m_af_spread_state[STATE_MOVE] = gAccuracyUtil.CvarRegister("af_spread_move", "1.0");
	this->m_af_spread_state[STATE_DUCK] = gAccuracyUtil.CvarRegister("af_spread_duck", "1.0");
	this->m_af_spread_state[STATE_AIR] = gAccuracyUtil.CvarRegister("af_spread_air", "1.0");

	if (g_ReGameApi)
	{
		char cvarName[32] = { 0 };

		for (int WeaponID = WEAPON_P228; WeaponID <= WEAPON_P90; WeaponID++)
		{
			auto SlotInfo = g_ReGameApi->GetWeaponSlot((WeaponIdType)WeaponID);

			if (SlotInfo && ((SlotInfo->slot == PRIMARY_WEAPON_SLOT) || (SlotInfo->slot == PISTOL_SLOT)))
			{
				if (SlotInfo->weaponName && SlotInfo->weaponName[0u] != '\0')
				{
					Q_snprintf(cvarName, sizeof(cvarName), "af_spread_%s", SlotInfo->weaponName);

					this->m_af_spread[WeaponID] = gAccuracyUtil.CvarRegister(cvarName, "0.55");
				}
			}
		}
	}

	auto Path = gAccuracyUtil.GetPath();

	if (Path)
	{
		if (Path[0u] != '\0')
		{
			gAccuracyUtil.ServerCommand("exec %s/accuracyfix.cfg", Path);
		}
	}
}

// Post hook: the bullet trace already has the vanilla spread in it (vEnd), so we only scale
// how far vEnd is from the exact aim direction. Traces without spread (status bar, etc) are left untouched.
void CAccuracyFix::TraceLine(const float* vStart, const float* vEnd, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr)
{
	if ((fNoMonsters != dont_ignore_monsters) || (gpGlobals->trace_flags == FTRACE_FLASH) || FNullEnt(pentToSkip))
	{
		return;
	}

	auto EntityIndex = g_engfuncs.pfnIndexOfEdict(pentToSkip);

	if (EntityIndex < 1 || EntityIndex > gpGlobals->maxClients)
	{
		return;
	}

	auto Player = UTIL_PlayerByIndexSafe(EntityIndex);

	if (!Player || !Player->IsAlive() || !Player->m_pActiveItem)
	{
		return;
	}

	auto WeaponID = Player->m_pActiveItem->m_iId;

	if (WeaponID < 0 || WeaponID > MAX_WEAPONS || !this->m_af_spread[WeaponID])
	{
		return;
	}

	// No-scope AWP keeps its vanilla spread
	if (WeaponID == WEAPON_AWP && Player->m_iFOV >= DEFAULT_FOV)
	{
		return;
	}

	auto Scale = (this->m_af_spread_all->value >= 0.0f) ? this->m_af_spread_all->value : this->m_af_spread[WeaponID]->value;

	// ponytail: one state wins (air > move > duck > stand), no separate duck+move value
	auto State = STATE_STAND;

	if (!(Player->pev->flags & FL_ONGROUND))
	{
		State = STATE_AIR;
	}
	else if (Player->pev->velocity.Length2D() > 10.0f)
	{
		State = STATE_MOVE;
	}
	else if (Player->pev->flags & FL_DUCKING)
	{
		State = STATE_DUCK;
	}

	auto StateScale = this->m_af_spread_state[State]->value;

	Scale *= (StateScale < 0.0f) ? 0.0f : ((StateScale > 1.0f) ? 1.0f : StateScale);

	if (Scale < 0.0f)
	{
		Scale = 0.0f;
	}

	if (Scale == 1.0f)
	{
		return;
	}

	Vector Start = vStart;

	Vector Delta = Vector(vEnd) - Start;

	auto Length = Delta.Length();

	if (Length <= 0.0f)
	{
		return;
	}

	// Aim direction as the weapon code sees it: view angle + recoil (AngleVectors does not touch gpGlobals)
	Vector Forward;

	g_engfuncs.pfnAngleVectors(Player->pev->v_angle + Player->pev->punchangle, Forward, NULL, NULL);

	// Same ray length as the original, so range and damage falloff stay correct
	Vector End = Start + (Forward + ((Delta / Length) - Forward) * Scale) * Length;

	g_engfuncs.pfnTraceLine(Start, End, fNoMonsters, pentToSkip, ptr);
}
