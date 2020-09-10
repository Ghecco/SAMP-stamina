#include <a_samp>
#include <GH_stamina>

main(){}

public OnGameModeInit()
{
    SendRconCommand("loadfs staminafs");
    return 1;
}