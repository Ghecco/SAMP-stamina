// [Includes]

#include <a_samp>
#include <g_Stamina> 

// [Defines]
#define STAMINA_DEFAULT_MAX				(200)

#define FILTERSCRIPT

#if defined FILTERSCRIPT


public OnFilterScriptInit()
{
  print("Stamina System Loaded.");
	for(new i, maxp = GetPlayerPoolSize(); i <= maxp; ++i)
	{
		SetPlayerMaxStamina(playerid, STAMINA_DEFAULT_MAX);
		SetPlayerStamina(playerid, STAMINA_DEFAULT_MAX);
	}
    return 1;
}

#endif


public OnPlayerConnect(playerid)
{
	SetPlayerMaxStamina(playerid, STAMINA_DEFAULT_MAX);
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
