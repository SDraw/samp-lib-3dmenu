This library allows you to create new type of menu instead of standart menus or dialogs.
* Creating of menu for each player.
* Custom rotaion for menu.
* Setting params for every box like for object.
* Auto-calculatting of new lines and box position.

### Requirements
* 0.3e or upper SA-MP server.
* [Streamer Plugin](https://github.com/samp-incognito/samp-streamer-plugin)

### Functions
* Create3DMenu(playerid,Float: x,Float:y,Float:z,Float:rotation,boxes);
  * Creating 3DMenu in position with number of boxes for player.
    * Returns _true_ if menu has been created, or _false_.
* SetBoxText(playerid,box,text[],materialsize,fontface[],fontsize,bold,fontcolor,selectcolor,unselectcolor ,textalignment);
  * Set box text, like object material text.
    * Returns _true_ if text has been changed, or _false_.
* Select3DMenu(playerid);
  * Start player select menu. Keys - box change: Y,N ; select - Space.
    * Returns _true_ if menu has been selected, or _false_.
* CancelSelect3DMenu(playerid);
  * Cancel player's selecting of menu.
    * Returns _true_ if selection has been canceled, or _false_.
* Destroy3DMenu(playerid);
  * Destroying of menu.
    * Returns _true_ if menu has been destroyed, or _false_.

### Callbacks
* OnPlayerChange3DMenuBox(playerid,boxid);
  * This callback is called when player presses _MENU3D_KEY_UP_ or _MENU3D_KEY_DOWN_ on selecting.
    * Note #1: Param boxid is equal ID of choosen box.
* OnPlayerSelect3DMenuBox(playerid,boxid);
  * This callback is called when player presses _MENU3D_KEY_SELECT_ in selecting mode.
    * Note #1: Param selected is equal ID of selected box.
