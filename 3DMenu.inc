#define MAX_BOXES (16)
#define MENU3D_KEY_DOWN KEY_NO
#define MENU3D_KEY_UP KEY_YES
#define MENU3D_KEY_SELECT KEY_SPRINT

/*
native playerid,Float:x,Float:y,Float:z,Float:rotation,boxes);
native SetBoxText(playerid,box,text[],materialsize,fontface[],fontsize,bold,fontcolor,selectcolor,unselectcolor,textalignment);
native Select3DMenu(playerid);
native CancelSelect3DMenu(playerid);
native Destroy3DMenu(playerid);
*/

forward OnPlayerSelect3DMenuBox(playerid,boxid);
forward OnPlayerChange3DMenuBox(playerid,boxid);

new SelectedMenu[MAX_PLAYERS];
new SelectedBox[MAX_PLAYERS];
enum MenuParams
{
    Float:Rotation,Boxes,bool:IsExist,
    Objects[MAX_BOXES],Float:OrigPosX[MAX_BOXES],Float:OrigPosY[MAX_BOXES],Float:OrigPosZ[MAX_BOXES],
    Float:AddingX,Float:AddingY,SelectColor[MAX_BOXES],UnselectColor[MAX_BOXES]
};
new MenuData[MAX_PLAYERS][MenuParams];

stock Create3DMenu(playerid,Float:x,Float:y,Float:z,Float:rotation,boxes)
{
    if(boxes > MAX_BOXES || boxes <= 0 || playerid < 0 || !IsPlayerConnected(playerid)) return false;
    if(MenuData[playerid][IsExist]) return false;
    new Float:NextLineX,Float:NextLineY;
    new lineindx,binc;
    MenuData[playerid][Rotation] = rotation;
    MenuData[playerid][Boxes] = boxes;
    MenuData[playerid][AddingX] = 0.25*floatsin(rotation,degrees);
    MenuData[playerid][AddingY] = -floatcos(rotation,degrees)*0.25;
    NextLineX = floatcos(rotation,degrees)+0.05*floatcos(rotation,degrees);
    NextLineY = floatsin(rotation,degrees)+0.05*floatsin(rotation,degrees);
    for(new b = 0; b < boxes; b++)
    {
        if(b%4 == 0 && b != 0) lineindx++,binc+=4;
        MenuData[playerid][Objects][b] = CreateDynamicObject(2661,x+NextLineX*lineindx,y+NextLineY*lineindx,z+1.65-0.55*(b-binc),0,0,rotation,-1,-1,playerid,100.0);
        GetDynamicObjectPos(MenuData[playerid][Objects][b],MenuData[playerid][OrigPosX][b],MenuData[playerid][OrigPosY][b],MenuData[playerid][OrigPosZ][b]);
    }
    MenuData[playerid][IsExist] = true;
    Streamer_Update(playerid);
    return true;
}

stock SetBoxText(playerid,box,text[],materialsize,fontface[],fontsize,bold,fontcolor,selectcolor,unselectcolor,textalignment)
{
    if(!MenuData[playerid][IsExist]) return false;
    if(box == MenuData[playerid][Boxes] || box < 0) return false;
    if(MenuData[playerid][Objects][box] == INVALID_OBJECT_ID) return false;
    MenuData[playerid][SelectColor][box] = selectcolor;
    MenuData[playerid][UnselectColor][box] = unselectcolor;
    if(SelectedBox[playerid] == box) SetDynamicObjectMaterialText(MenuData[playerid][Objects][box],0,text,materialsize,fontface,fontsize,bold,fontcolor,selectcolor,textalignment);
    else SetDynamicObjectMaterialText(MenuData[playerid][Objects][box],0,text,materialsize,fontface,fontsize,bold,fontcolor,unselectcolor,textalignment);
    return true;
}

stock Select3DMenu(playerid)
{
    if(!IsPlayerConnected(playerid)) return false;
    if(!MenuData[playerid][IsExist]) return false;
    if(SelectedMenu[playerid] != -1) CancelSelect3DMenu(playerid);
    SelectedBox[playerid] = 0;
    new text[128],materialsize,fontface[128],fontsize,bold,fontcolor,backcolor,textalignment;
    GetDynamicObjectMaterialText(MenuData[playerid][Objects][0],0,text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
    SelectedMenu[playerid] = playerid;
    MoveDynamicObject(MenuData[playerid][Objects][0],MenuData[playerid][OrigPosX][0]+MenuData[playerid][AddingX],MenuData[playerid][OrigPosY][0]+MenuData[playerid][AddingY],MenuData[playerid][OrigPosZ][0],1.0);
    SetDynamicObjectMaterialText(MenuData[playerid][Objects][0],0,text,materialsize,fontface,fontsize,bold,fontcolor,MenuData[playerid][SelectColor][0],textalignment);
    return true;
}

#if defined FILTERSCRIPT
public OnFilterScriptInit()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        SelectedMenu[i] = -1;
        SelectedBox[i] = -1;
    }
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        for(new b = 0; b < MAX_BOXES; b++) MenuData[i][Objects][b] = INVALID_OBJECT_ID;
        MenuData[i][Boxes] = 0;
        MenuData[i][IsExist] = false;
        MenuData[i][AddingX] = 0.0;
        MenuData[i][AddingY] = 0.0;
    }
    if(funcidx("menu3d_OnFilterScriptInit") != -1) return CallLocalFunction("menu3d_OnFilterScriptInit", "");
    return 1;
}
#if defined _ALS_OnFilterScriptInit
#undef OnFilterScriptInit
#else
#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit menu3d_OnFilterScriptInit
forward menu3d_OnFilterScriptInit();

public OnFilterScriptExit()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(MenuData[i][IsExist]) Destroy3DMenu(i);
    }
    if(funcidx("menu3d_OnFilterScriptExit") != -1) return CallLocalFunction("menu3d_OnFilterScriptExit", "");
    return 1;
}
#if defined _ALS_OnFilterScriptExit
#undef OnFilterScriptExit
#else
#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit menu3d_OnFilterScriptExit
forward menu3d_OnFilterScriptExit();

#else
public OnGameModeInit()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        for(new b = 0; b < MAX_BOXES; b++) MenuData[i][Objects][b] = INVALID_OBJECT_ID;
        MenuData[i][Boxes] = 0;
        MenuData[i][IsExist] = false;
        MenuData[i][AddingX] = 0.0;
        MenuData[i][AddingY] = 0.0;
    }
    if(funcidx("menu3d_OnGameModeInit") != -1) return CallLocalFunction("menu3d_OnGameModeInit", "");
    return 1;
}
#if defined _ALS_OnGameModeInit
#undef OnGameModeInit
#else
#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit menu3d_OnGameModeInit
forward menu3d_OnGameModeInit();

public OnGameModeExit()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(MenuData[i][IsExist]) Destroy3DMenu(i);
    }
    if(funcidx("menu3d_OnGameModeExit") != -1) return CallLocalFunction("menu3d_OnGameModeExit", "");
    return 1;
}
#if defined _ALS_OnGameModeExit
#undef OnGameModeExit
#else
#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit menu3d_OnGameModeExit
forward menu3d_OnGameModeExit();

#endif
public OnPlayerConnect(playerid)
{
    SelectedMenu[playerid] = -1;
    SelectedBox[playerid] = -1;
    if(funcidx("menu3d_OnPlayerConnect") != -1) return CallLocalFunction("menu3d_OnPlayerConnect", "d",playerid);
    return 1;
}
#if defined _ALS_OnPlayerConnect
#undef OnPlayerConnect
#else
#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect menu3d_OnPlayerConnect
forward menu3d_OnPlayerConnect(playerid);

public OnPlayerDisconnect(playerid,reason)
{
    if(SelectedMenu[playerid] != -1) CancelSelect3DMenu(playerid);
    if(funcidx("menu3d_OnPlayerDisconnect") != -1) return CallLocalFunction("menu3d_OnPlayerDisconnect", "dd",playerid,reason);
    return 1;
}
#if defined _ALS_OnPlayerDisconnect
#undef OnPlayerDisconnect
#else
#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect menu3d_OnPlayerDisconnect
forward menu3d_OnPlayerDisconnect(playerid, reason);

public OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
    if(SelectedMenu[playerid] != -1)
    {
        if(newkeys == MENU3D_KEY_DOWN)
        {
            new text[128],materialsize,fontface[32],fontsize,bold,fontcolor,backcolor,textalignment;
            GetDynamicObjectMaterialText(MenuData[playerid][Objects][SelectedBox[playerid]],0,text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
            SetDynamicObjectMaterialText(MenuData[playerid][Objects][SelectedBox[playerid]],0,text,materialsize,fontface,fontsize,bold,fontcolor,MenuData[playerid][UnselectColor][SelectedBox[playerid]],textalignment);
            MoveDynamicObject(MenuData[playerid][Objects][SelectedBox[playerid]],MenuData[playerid][OrigPosX][SelectedBox[playerid]],MenuData[playerid][OrigPosY][SelectedBox[playerid]],MenuData[playerid][OrigPosZ][SelectedBox[playerid]],1.0);
            SelectedBox[playerid]++;
            if(SelectedBox[playerid] == MenuData[playerid][Boxes]) SelectedBox[playerid] = 0;
            MoveDynamicObject(MenuData[playerid][Objects][SelectedBox[playerid]],MenuData[playerid][OrigPosX][SelectedBox[playerid]]+MenuData[playerid][AddingX],MenuData[playerid][OrigPosY][SelectedBox[playerid]]+MenuData[playerid][AddingY],MenuData[playerid][OrigPosZ][SelectedBox[playerid]],1.0);
            GetDynamicObjectMaterialText(MenuData[playerid][Objects][SelectedBox[playerid]],0,text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
            SetDynamicObjectMaterialText(MenuData[playerid][Objects][SelectedBox[playerid]],0,text,materialsize,fontface,fontsize,bold,fontcolor,MenuData[playerid][SelectColor][SelectedBox[playerid]],textalignment);
            if(funcidx("OnPlayerChange3DMenuBox") != -1) CallLocalFunction("OnPlayerChange3DMenuBox","dd",playerid,SelectedBox[playerid]);
        }
        else if(newkeys == MENU3D_KEY_UP)
        {
            new text[128],materialsize,fontface[32],fontsize,bold,fontcolor,backcolor,textalignment;
            GetDynamicObjectMaterialText(MenuData[playerid][Objects][SelectedBox[playerid]],0,text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
            SetDynamicObjectMaterialText(MenuData[playerid][Objects][SelectedBox[playerid]],0,text,materialsize,fontface,fontsize,bold,fontcolor,MenuData[playerid][UnselectColor][SelectedBox[playerid]],textalignment);
            MoveDynamicObject(MenuData[playerid][Objects][SelectedBox[playerid]],MenuData[playerid][OrigPosX][SelectedBox[playerid]],MenuData[playerid][OrigPosY][SelectedBox[playerid]],MenuData[playerid][OrigPosZ][SelectedBox[playerid]],1.0);
            SelectedBox[playerid]--;
            if(SelectedBox[playerid] < 0) SelectedBox[playerid] = MenuData[playerid][Boxes]-1;
            MoveDynamicObject(MenuData[playerid][Objects][SelectedBox[playerid]],MenuData[playerid][OrigPosX][SelectedBox[playerid]]+MenuData[playerid][AddingX],MenuData[playerid][OrigPosY][SelectedBox[playerid]]+MenuData[playerid][AddingY],MenuData[playerid][OrigPosZ][SelectedBox[playerid]],1.0);
            GetDynamicObjectMaterialText(MenuData[playerid][Objects][SelectedBox[playerid]],0,text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
            SetDynamicObjectMaterialText(MenuData[playerid][Objects][SelectedBox[playerid]],0,text,materialsize,fontface,fontsize,bold,fontcolor,MenuData[playerid][SelectColor][SelectedBox[playerid]],textalignment);
            if(funcidx("OnPlayerChange3DMenuBox") != -1) CallLocalFunction("OnPlayerChange3DMenuBox","dd",playerid,SelectedBox[playerid]);
        }
        else if(newkeys == MENU3D_KEY_SELECT)
        {
            if(funcidx("OnPlayerSelect3DMenuBox") != -1) CallLocalFunction("OnPlayerSelect3DMenuBox","dd",playerid,SelectedBox[playerid]);
        }
    }
    if(funcidx("menu3d_OnPlayerKeyStateChange") != -1) return CallLocalFunction("menu3d_OnPlayerKeyStateChange", "ddd",playerid,newkeys,oldkeys);
    return 1;
}
#if defined _ALS_OnPlayerKeyStateChange
#undef OnPlayerKeyStateChange
#else
#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange menu3d_OnPlayerKeyStateChange
forward menu3d_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);

stock CancelSelect3DMenu(playerid)
{
    if(!IsPlayerConnected(playerid)) return false;
    if(SelectedMenu[playerid] == -1) return false;
    new text[128],materialsize,fontface[32],fontsize,bold,fontcolor,backcolor,textalignment;
    GetDynamicObjectMaterialText(MenuData[playerid][Objects][SelectedBox[playerid]],0,text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
    SetDynamicObjectMaterialText(MenuData[playerid][Objects][SelectedBox[playerid]],0,text,materialsize,fontface,fontsize,bold,fontcolor,MenuData[playerid][UnselectColor][SelectedBox[playerid]],textalignment);
    MoveDynamicObject(MenuData[playerid][Objects][SelectedBox[playerid]],MenuData[playerid][OrigPosX][SelectedBox[playerid]],MenuData[playerid][OrigPosY][SelectedBox[playerid]],MenuData[playerid][OrigPosZ][SelectedBox[playerid]],1.0);
    SelectedMenu[playerid] = -1;
    SelectedBox[playerid] = -1;
    return true;
}

stock Destroy3DMenu(playerid)
{
    if(!MenuData[playerid][IsExist]) return false;
    if(SelectedMenu[playerid] == playerid) CancelSelect3DMenu(playerid);
    for(new i = 0; i < MenuData[playerid][Boxes]; i++)
    {
        DestroyDynamicObject(MenuData[playerid][Objects][i]);
        MenuData[playerid][Objects][i] = INVALID_OBJECT_ID;
    }
    MenuData[playerid][Boxes] = 0;
    MenuData[playerid][IsExist] = false;
    MenuData[playerid][AddingX] = 0.0;
    MenuData[playerid][AddingY] = 0.0;
    return true;
}