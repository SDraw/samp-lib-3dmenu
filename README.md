This include allows you to create new type of menu instead of standart menus or dialogs.
* Creating of menu for each player.
* Custom rotaion for menu.
* Setting params for every box like for object.
* Auto-calculatting of new lines and box position.
* **Limits:** MAX_PLAYERS menus, one menu per player (if you want to create more menus per player, 
just change in #define MAX_3DMENUS from MAX_PLAYER to MAX_PLAYERS*N where N is number of menus 
per player) and manual limited boxes (default is 16).

### Requirements
* 0.3e or upper SA-MP server.
* Incognito's Streamer (0.3e and upper)

### Functions
* Create3DMenu(Float: x,Float:y,Float:z,Float:rotation,boxes,playerid);
  * Creating 3DMenu in position with number of boxes for player.
    * Note #1: Rotation should be equal from 0 to 360. Bigger or lower values will make menu works wrong.
    * Note #2: This function returns ID of created menu. It will return -1 if wrong player ID is setted.
* SetBoxText(MenuID,box,text[],materialsize,fontface[],fontsize,bold,fontcolor,selectcolor,unselectcolor ,textalignment);
  * Set box text, like object material text.
    * Note #1: This function looks like SetObjectMaterialText.
    * Note #2: If you set wrong box ID or menu ID, function will return -1.
    * Note #3: selectcolour - background of box when it is choosen. unselectcolor - if not.[/I][/B].
* Select3DMenu(playerid,MenuID);
  * Start player select menu. Keys - box change: Y,N ; select - Space.
    * Note #1: This function will return -1 if you set invalid menu ID.
* CancelSelect3DMenu(playerid);
  * Cancel player's selecting of menu.
    * Note #1: This function will return -1 if player isn't choosing any menu.
* Destroy3DMenu(MenuID);
  * Destroying of menu.
    * Note #1: This function will return -1 if menu doesn't exist.

### Callbacks
* OnPlayerChange3DMenuBox(playerid,MenuID,boxid);
  * This callback is called when player presses Y or N on selecting.
    * Note #1: Param boxid is equal ID of choosen box.
* OnPlayerSelect3DMenuBox(playerid,MenuID,selected);
  * This callback is called when player presses Space on selecting.
    * Note #1: Param selected is equal ID of selected box.

### Example code
```Pawn
//
new Float:p[4];
GetPlayerPos(playerid,p[0],p[1],p[2]);
GetPlayerFacingAngle(playerid,p[3]);
new menu = Create3DMenu(p[0],p[1],p[2],p[3],8,playerid);
for(new i = 0; i < 8; i++) SetBoxText(menu,i,"I'm a selectable box!",OBJECT_MATERIAL_SIZE_256x64,"Impact",12,false,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
Select3DMenu(playerid,menu);
//
public OnPlayerSelect3DMenuBox(playerid,MenuID,selected)
{
   PlayPlayerSound(playerid,1054,0,0,0);
   SetBoxText(MenuID,selected,"You've selected me!\nWheee!",OBJECT_MATERIAL_SIZE_256x64,"Impact",12,false,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
   return 1;
}
```
