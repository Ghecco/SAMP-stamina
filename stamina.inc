
		/*																																								*\
																	*[SAMP_Stamina] Version: 1.0* 



											|		This simple include allows you to create and manage a stamina system.		|
	
			Utils:
		__________________________________________________________________________________________________________________________________________________________________
		/																																								/
																		[Utils]

		[+]PVAR: "Stamina"	-	"MAX_Stamina"	-	"Exhausted"-	-	"Sprint_Velocity"	



	-	[+] Define:

			*- #define STAMINA_DEFAULT_RECOVERYTIME		(5000)    		// Default value of Recovery time in milliseconds (tired anim)
			

	-	[+] Callback:

			*- public OnPlayerStaminaOver(playerid) 				 	// When the player is exhausted

	-	[+] Functions:

			*- IsPlayerRunning(playerid) 								// Check If the player is running

			*- IsPlayerExhausted(playerid) 								// Check If the player is exhausted

			*- SetPlayerExhausted(playerid, bool:Exhausted) 			// set the exhausted player (tired anim timing = STAMINA_DEFAULT_RECOVERYTIME)


			*- GetPlayerStamina(playerid)								// Get the player's current stamina  													(INTEGAR)
			*- GetPlayerMaxStamina(playerid) 							// Get the player's maximum stamina  													(INTEGAR)

			*- GivePlayerStamina(playerid, value) 						// Add / Subtract the player's current stamina   										(INTEGAR)
			*- GivePlayerMaxStamina(playerid, value) 					// Add / Subtract the player's maximum stamina   										(INTEGAR)

			*- SetPlayerStamina(playerid, value) 						// Set the player's current stamina 													(INTEGAR)
			*- SetPlayerMaxStamina(playerid, Float:value)						// Set the player's maximum stamina 													(INTEGAR)

			*- GivePlayerSprintVelocity(playerid, Float:value)         	// multiply / divide the player's sprint speed (exceeded (2.0) you will get a bad result) (FLOAT)
			*_ GetPlayerSprintVelocity(playerid) 						// Get the player's sprint velocity 													  (FLOAT)

		__________________________________________________________________________________________________________________________________________________________________
		/																																								*/
																																										
// [Includes]

#include <a_samp>

// [Defines]

#if defined include_g_Stamina
    #endinput
#else
	#define include_g_Stamina
#endif




#if !defined STAMINA_DEFAULT_RECOVERYTIME
	#define STAMINA_DEFAULT_RECOVERYTIME    (4000)
#endif

// [Callback]

forward OnPlayerStaminaOver(playerid);


// [Functions]

stock IsPlayerRunning(playerid) // Check if the player is running
{
    if(!IsPlayerConnected(playerid) || IsPlayerInAnyVehicle(playerid) || IsPlayerExhausted(playerid)) return 0;

    new keys, updown, leftright;
    GetPlayerKeys(playerid, keys, updown, leftright);
    if(keys & KEY_SPRINT && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_USEJETPACK) return 1;
    else return 0;
}


stock IsPlayerExhausted(playerid) // Check if the player is exhausted
{
	if(GetPVarInt(playerid, "Exhausted") == 1) return true;
	else return false;
}


forward SetPlayerExhausted(playerid, bool:Exhausted);
public SetPlayerExhausted(playerid, bool:Exhausted)  // If true the player will do the recovery animation for the time set by #define STAMINA_DEFAULT_RECOVERYTIME
{
	if(Exhausted) 
	{
		TogglePlayerControllable(playerid,0);
		TogglePlayerControllable(playerid,1);

		ApplyAnimation(playerid, "FAT", "IDLE_tired", 4.1, 0, 1, 1, 0, STAMINA_DEFAULT_RECOVERYTIME, 1);

		SetPVarInt(playerid, "Exhausted", 1);
		SetTimerEx("SetPlayerExhausted", STAMINA_DEFAULT_RECOVERYTIME, false, "ib", playerid, false);
	}
	else SetPVarInt(playerid, "Exhausted", 0), ClearAnimations(playerid);
	return 1;
}


stock GetPlayerStamina(playerid) // Get the player's current stamina (integar)
{
	if(!IsPlayerConnected(playerid) || GetPVarType(playerid, "MAX_Stamina") == PLAYER_VARTYPE_NONE) return -1;
	new stamina = GetPVarInt(playerid, "Stamina");
	return stamina;
}


stock GetPlayerMaxStamina(playerid) // Set the player's maximum stamina (integar)
{
	if(!IsPlayerConnected(playerid) || GetPVarType(playerid, "MAX_Stamina") == PLAYER_VARTYPE_NONE) return -1;
	new maxstamina = GetPVarInt(playerid, "MAX_Stamina");
	return maxstamina;
}


stock GivePlayerStamina(playerid, value) // Add / Subtract the player's current stamina (integar)
{
	new stamina = GetPVarInt(playerid, "Stamina");

	if(stamina == -1) return 1;
	if(stamina + value == 0) return CallLocalFunction("OnPlayerStaminaOver", "i", playerid);
	if(stamina + value <= GetPVarInt(playerid, "MAX_Stamina")) 
	{
		stamina = stamina+value;
		SetPVarInt(playerid, "Stamina", stamina);
		return 1;
	}
	else return 0;
}


stock GivePlayerMaxStamina(playerid, value) // Add / Subtract the player's MAX stamina (integar)
{
	new maxstamina = GetPVarInt(playerid, "MAX_Stamina"), stamina = GetPVarInt(playerid, "Stamina");

	maxstamina = maxstamina + value;
	SetPVarInt(playerid, "MAX_Stamina", maxstamina);

	if(stamina > maxstamina)stamina = maxstamina, SetPVarInt(playerid, "Stamina", stamina);

	return 1;
}


stock SetPlayerStamina(playerid, value) // Set the player's current stamina (the current stamina cannot be higher than MAX_STAMINA )
{
	if(value > GetPVarInt(playerid, "MAX_Stamina")) return SetPVarInt(playerid, "Stamina", GetPVarInt(playerid, "MAX_Stamina")); //if the current stamina exceeds the MAX_STAMINA, set the player's MAX_STAMINA directly to avoid bugs
	else if(value == 0) OnPlayerStaminaOver(playerid);
	SetPVarInt(playerid, "Stamina", value);
	return 1;
}


stock SetPlayerMaxStamina(playerid, value) //set the player's maximum stamina 
{
	new stamina = GetPlayerStamina(playerid), max_stamina = value;

	if(stamina > max_stamina) stamina = max_stamina, SetPVarInt(playerid, "Stamina", stamina);
	SetPVarInt(playerid, "MAX_Stamina", max_stamina);
	return 1;
}

stock GivePlayerSprintVelocity(playerid, Float:value) // multiply / divide the player's sprint speed (Recommended not to exceed 2.0 to avoid a bad result) (float)
{
	if(value == 0.0) return 1;
	else if(value > 0.0)
	{
		new Float:x, Float:y, Float:Z;

		GetPlayerVelocity(playerid, x, y, z);
		SetPlayerVelocity(playerid, x*value, y*value, z*value);
	}
	else if(value < 0.0) // if Subtract
	{
		GetPlayerVelocity(playerid, x, y, z);
		SetPlayerVelocity(playerid, x/value, y/value, z/value);
	}
	SetPVarFloat(playerid, "Sprint_Velocity", value);
		return 1;
}

stock GetPlayerSprintVelocity(playerid) // Get the player's sprint velocity (float)
{
	if(!IsPlayerConnected(playerid)) return -1;
	new Float:velocity = GetPVarFloat(playerid, "Sprint_Velocity");
	return Float:velocity;
}

