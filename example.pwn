#include <a_samp>
#include <streamer>
#include <3DMenu>

public OnFilterScriptInit()
{
    new Float:p[4];
    GetPlayerPos(0,p[0],p[1],p[2]);
    GetPlayerFacingAngle(0,p[3]);
    if(Create3DMenu(0,p[0],p[1],p[2],p[3],8))
    {
        for(new i = 0; i < 8; i++) SetBoxText(0,i,"I'm a selectable box!",OBJECT_MATERIAL_SIZE_256x64,"Impact",32,false,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
        Select3DMenu(0);
    }
    return 1;
}

public OnPlayerSelect3DMenuBox(playerid,boxid)
{
   SetBoxText(playerid,boxid,"You've selected me!\nWheee!",OBJECT_MATERIAL_SIZE_256x64,"Impact",32,false,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
   return 1;
}

public OnPlayerChange3DMenuBox(playerid,boxid)
{
    new str[16];
    format(str,64,"Box id is %d",boxid);
    SendClientMessage(playerid,-1,str);
    return 1;
}