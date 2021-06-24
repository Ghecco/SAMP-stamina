#include <a_samp>
#include <stamina>

main(){}




public OnPlayerConnect(playerid) {
    SetPlayerMaxStamina(playerid, 20);  // FIRST - the first step is the setting of player's max stamina level
    //SetPlayerSetamina(playerid, GetPlayerMaxStamina(playerid)); Is a good practice setting actual player's stamina to max stamina but..
}

public OnPlayerSpawn(playerid)
{
    SetPlayerStamina(playerid, GetPlayerMaxStamina(playerid)); // but.. in this case just put it here. remember if you will change the player's maximum stamina.
}


public OnPlayerUpdate(playerid) // just add this 
{
	if(IsPlayerRunning(playerid)) GivePlayerStamina(playerid, -1); // if the player run, it subtracts the player's stamina
	else if(GetPlayerStamina(playerid) < GetPlayerMaxStamina(playerid)) GivePlayerStamina(playerid, 1); // if the player is not running, he recovers the current stamina up to his MAX
	return 1;
}

public OnPlayerStaminaOver(playerid) // stamina callback !
{
	SetPlayerExhausted(playerid, true); // tired anim
	return 1;
}
