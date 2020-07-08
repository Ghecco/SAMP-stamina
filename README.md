![Image of Yaktocat](https://i.imgur.com/Tza7GaU.png)


# [Include] GH_Stamina

This simple include allows you to create and manage a stamina system.
## How does it work?


This includes bases the stamina system on 4 values.


 1. Player's max stamina. - Maximum achievable stamina level. ( Integar )
 2. Player's current stamina.  - Current stamina level. ( Integar )
 3. Exhausted. - Value assigned when the player performs the recovery animation.
 4. Sprint Velocity - You can set a speed per player. ( Float )

## Callbacks & Functions 
*New Callback:
`public OnPlayerStaminaOver(playerid)`*

*New Functions:*

    IsPlayerRunning(playerid); // Check if the player is running.
    IsPlayerExhausted(playerid); // Check if the player is exhausted.
    SetPlayerExhausted(playerid, bool:Exhausted) set the exhausted player (if is true the player will do the tired anim).
    
    GetPlayerStamina(playerid)	// Get the player's current stamina.
    GivePlayerStamina(playerid, value) // Add / Subtract the player's current stamina.
    SetPlayerStamina(playerid, value) // Set the player's current stamina.	 
    
    GetPlayerMaxStamina(playerid) // Get the player's maximum stamina.
    GivePlayerMaxStamina(playerid, Float:value) // Add / Subtract the player's maximum stamina.
    SetPlayerMaxStamina(playerid, Float:value) // Set the player's maximum stamina.
    
	GivePlayerSprintVelocity(playerid, Float:value) // Multiply / divide the player's sprint speed (exceeded (2.0) you will get a bad result).
	GetPlayerSprintVelocity(playerid) // Get the player's sprint velocity. 

      	
	
*New Define:*

    #define STAMINA_DEFAULT_RECOVERYTIME		(5000) // Time in milliseconds of tired anim (Exhausted).


## Installing

 - Download `GH_Stamina.inc`.
 - Move it in your **SA-MP Server Folder** --> pawno/include.
 - Include in your gamemode #include <GH_Stamina>.

## Example & Filterscript

 - [[Filterscript] Stamina System](https://github.com/Ghecco/GH_Stamina/blob/master/staminafs.pwn)

  

