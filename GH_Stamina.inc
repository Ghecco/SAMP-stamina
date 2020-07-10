stock MyLib_CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0);(playerid, amount)
{
    // Call the old version, no need to check if it exists.
    Iter_Add(StreamerObject, value)
    return 1;
}
// Has this been hooked already?
#if defined _ALS_GivePlayerMoney
    #undef GivePlayerMoney
#else
    #define _ALS_GivePlayerMoney
#endif
// Reroute future calls to our function.
#define GivePlayerMoney MyLib_GivePlayerMoney
