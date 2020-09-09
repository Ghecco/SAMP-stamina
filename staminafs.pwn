
// staminafs.pwn | Video: https://www.youtube.com/watch?v=lgWzeE5SLOk

// [Includes]

#include <a_samp>
#include <GH_Stamina>

// [Defines]
#define STAMINA_DEFAULT_MAX				(200)

#define FILTERSCRIPT

#if defined FILTERSCRIPT


public OnFilterScriptInit()
{
  	print("Stamina System Loaded.");
	for(new i, maxp = GetPlayerPoolSize(); i <= maxp; i++)
	{
		SetPlayerMaxStamina(i, STAMINA_DEFAULT_MAX);
		SetPlayerStamina(i, STAMINA_DEFAULT_MAX);
	}
    return 1;
}

#endif


public OnPlayerConnect(playerid)
{
	SetPlayerMaxStamina(playerid, -1);
	SetPlayerExhausted(playerid, true);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	SetPlayerStamina(playerid, GetPlayerMaxStamina(playerid));
	return 1;
}

public OnPlayerUpdate(playerid)
{
	if(IsPlayerRunning(playerid)) GivePlayerStamina(playerid, -1); // if the player run, it subtracts the player's stamina
	else if(GetPlayerStamina(playerid) < GetPlayerMaxStamina(playerid)) GivePlayerStamina(playerid, 1); // if the player is not running, he recovers the current stamina up to his MAX
	return 1;
}

public OnPlayerStaminaOver(playerid)
{
	SetPlayerExhausted(playerid, true);
	return 1;
}
