//
// Created by DiaLight on 11.10.2022.
//
#include <Windows.h>
#include <Strings.h>
#include <MenuIdentifiers.h>
#include <Menus.h>

BOOL AppendMenu2(HMENU hmenu, UINT fMask, UINT fType, UINT fState, UINT wID, HMENU hSubMenu, ULONG_PTR dwItemData, LPSTR dwTypeData) {
  MENUITEMINFO MenuItemInfo;
  ZeroMemory(&MenuItemInfo, sizeof(MenuItemInfo));
  MenuItemInfo.cbSize = sizeof(MenuItemInfo);
  MenuItemInfo.fMask = fMask;
  MenuItemInfo.fType = fType;
  MenuItemInfo.fState = fState;
  MenuItemInfo.wID = wID;
  MenuItemInfo.hSubMenu = hSubMenu;
  MenuItemInfo.dwItemData = dwItemData;
  MenuItemInfo.dwTypeData = dwTypeData;
  MenuItemInfo.cch = -1;
  return InsertMenuItemA(hmenu, -1, TRUE, &MenuItemInfo);
}

BOOL SimpleAddMenu(HMENU hmenu, LPCSTR dwTypeData, UINT wID, UINT fState) {
  return AppendMenu2(hmenu,
                     MIIM_STATE | MIIM_ID | MIIM_STRING | MIIM_FTYPE,
                     0, fState, wID, 0, 0, dwTypeData
  );
}

BOOL SimpleAddPopup(HMENU hmenu, LPCSTR dwTypeData, UINT wID, UINT fState, HMENU popup) {
  return AppendMenu2(hmenu,
                     MIIM_STATE | MIIM_ID | MIIM_SUBMENU | MIIM_STRING | MIIM_FTYPE,
                     0, fState, wID, popup, 0, dwTypeData
  );
}

BOOL SimpleAddSeparator(HMENU hmenu) {
  return AppendMenu2(hmenu,
                     MIIM_STATE | MIIM_ID | MIIM_FTYPE,
                     0, 0, 0, 0, 0, 0
  );
}

HMENU CreateMenu_MAINMENU() {
  HMENU MENUEX_MAINMENU = CreateMenu();

  /* *** MENUFILE *** */
  HMENU POPUP_DIALOG_MENUFILE = CreatePopupMenu();
  if(!SimpleAddPopup(MENUEX_MAINMENU, DIALOG_MENUFILE, 0, 0, POPUP_DIALOG_MENUFILE)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUFILE, " ", IDM_NEW, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUFILE, " ", IDM_DISK, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUFILE, " ", IDM_OPEN, 0)) return NULL;

  HMENU POPUP_RECENT = CreatePopupMenu();
  if(!SimpleAddPopup(POPUP_DIALOG_MENUFILE, " ", IDM_RECENT, 0, POPUP_RECENT)) return NULL;
  if(!SimpleAddSeparator(POPUP_RECENT)) return NULL;
  if(!SimpleAddMenu(POPUP_RECENT, MENU_SAFEFILE, IDM_SAFEFILE, 0)) return NULL;
  if(!SimpleAddSeparator(POPUP_RECENT)) return NULL;
  if(!SimpleAddMenu(POPUP_RECENT, MENU_REMOVEOBSOLETE, IDM_RECENTREMOVEOBSOLETE, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_RECENT, MENU_REMOVEALL, IDM_RECENTREMOVEALL, 0)) return NULL;

  if(!SimpleAddMenu(POPUP_DIALOG_MENUFILE, " ", IDM_SAVE, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUFILE, " ", IDM_SAVEAS, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUFILE, " ", IDM_COMPILATION, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUFILE, " ", IDM_COMPILE, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUFILE, " ", IDM_TEST, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUFILE, " ", IDM_EXECUTE, 0)) return NULL;
  if(!SimpleAddSeparator(POPUP_DIALOG_MENUFILE)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUFILE, " ", IDM_QUIT, 0)) return NULL;

  /* *** MENUEDIT *** */
  HMENU POPUP_DIALOG_MENUEDIT = CreatePopupMenu();
  if(!SimpleAddPopup(MENUEX_MAINMENU, DIALOG_MENUEDIT, 0, 0, POPUP_DIALOG_MENUEDIT)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_UNDO, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_UNDOLAST, MFS_GRAYED)) return NULL;

  HMENU POPUP_UNDOMNU = CreatePopupMenu();
  if(!SimpleAddPopup(POPUP_DIALOG_MENUEDIT, " ", IDM_UNDOMNU, 0, POPUP_UNDOMNU)) return NULL;
  if(!SimpleAddMenu(POPUP_UNDOMNU, " ", IDM_UNDOHISTORY, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_UNDOMNU, " ", IDM_UNDOFREE, MFS_GRAYED)) return NULL;
  if(!SimpleAddSeparator(POPUP_UNDOMNU)) return NULL;
  if(!SimpleAddMenu(POPUP_UNDOMNU, " ", IDM_UNDOCOUNT, 0)) return NULL;

  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_SELRECT, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_COPY, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_CUT, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_PASTE, MFS_GRAYED)) return NULL;

  HMENU POPUP_LOADBRUSH = CreatePopupMenu();
  if(!SimpleAddPopup(POPUP_DIALOG_MENUEDIT, " ", IDM_LOADBRUSH, 0, POPUP_LOADBRUSH)) return NULL;
  if(!SimpleAddMenu(POPUP_LOADBRUSH, " ", IDM_LOADBRUSHINSEL, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_LOADBRUSH, " ", IDM_LOADBRUSHINCOPY, 0)) return NULL;

  HMENU POPUP_SAVEBRUSH = CreatePopupMenu();
  if(!SimpleAddPopup(POPUP_DIALOG_MENUEDIT, " ", IDM_SAVEBRUSH, 0, POPUP_SAVEBRUSH)) return NULL;
  if(!SimpleAddMenu(POPUP_SAVEBRUSH, " ", IDM_SELECTION, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_SAVEBRUSH, " ", IDM_COPYZONE, MFS_GRAYED)) return NULL;

  HMENU POPUP_TRANSFORM = CreatePopupMenu();
  if(!SimpleAddPopup(POPUP_DIALOG_MENUEDIT, " ", IDM_TRANSFORM, 0, POPUP_TRANSFORM)) return NULL;
  if(!SimpleAddMenu(POPUP_TRANSFORM, " ", IDM_ROTATEP90, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_TRANSFORM, " ", IDM_ROTATEM90, MFS_GRAYED)) return NULL;
  if(!SimpleAddSeparator(POPUP_TRANSFORM)) return NULL;
  if(!SimpleAddMenu(POPUP_TRANSFORM, " ", IDM_SYMHORZ, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_TRANSFORM, " ", IDM_SYMVERT, MFS_GRAYED)) return NULL;

  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_SELECTCHANGE, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_SELECTALL, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_SELECTNONE, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_SEARCH, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_FIND, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_WORLDELEMENTS, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_CREATURES, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_DOORSTRAPS, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_OBJECTS, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_OTHERS, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_HEROS, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_AREAS, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_GATES, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_EFFECTS, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_PATHS, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_EVENTS, 0)) return NULL;
  if(!SimpleAddSeparator(POPUP_DIALOG_MENUEDIT)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_CREATURESPROPERTIES, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_GAMEPROPERTIES, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUEDIT, " ", IDM_MAPPROPERTIES, 0)) return NULL;

  /* *** MENUPAINT *** */
  HMENU POPUP_DIALOG_MENUPAINT = CreatePopupMenu();
  if(!SimpleAddPopup(MENUEX_MAINMENU, DIALOG_MENUPAINT, 0, 0, POPUP_DIALOG_MENUPAINT)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUPAINT, " ", IDM_PAINTBRUSH, MFS_GRAYED)) return NULL;

  HMENU POPUP_WORLDELEM = CreatePopupMenu();
  if(!SimpleAddPopup(POPUP_DIALOG_MENUPAINT, " ", IDM_WORLDELEM, MFS_CHECKED, POPUP_WORLDELEM)) return NULL;
  if(!SimpleAddMenu(POPUP_WORLDELEM, " ", IDM_MAPWORLDLIMIT, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_WORLDELEM, " ", IDM_MAPWORLDWATER, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_WORLDELEM, " ", IDM_MAPWORLDLAVA, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_WORLDELEM, " ", IDM_MAPWORLDGOLD, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_WORLDELEM, " ", IDM_MAPWORLDGEMS, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_WORLDELEM, " ", IDM_MAPWORLDSOLID, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_WORLDELEM, " ", IDM_MAPWORLDROCK, MFS_CHECKED)) return NULL;
  if(!SimpleAddMenu(POPUP_WORLDELEM, " ", IDM_MAPWORLDUNCLAIMED, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_WORLDELEM, " ", IDM_MAPWORLDHEROREST, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_WORLDELEM, " ", IDM_MAPWORLDMANACLOSED, 0)) return NULL;
  if(!SimpleAddSeparator(POPUP_WORLDELEM)) return NULL;

  HMENU POPUP_MAPWORLDHEROPORTALS = CreatePopupMenu();
  if(!SimpleAddPopup(POPUP_WORLDELEM, " ", IDM_MAPWORLDHEROPORTALS, 0, POPUP_MAPWORLDHEROPORTALS)) return NULL;
  if(!SimpleAddMenu(POPUP_MAPWORLDHEROPORTALS, " ", IDM_MAPWORLDHEROSGATE1, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_MAPWORLDHEROPORTALS, " ", IDM_MAPWORLDHEROSGATE2, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_MAPWORLDHEROPORTALS, " ", IDM_MAPWORLDHEROSGATE3, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_MAPWORLDHEROPORTALS, " ", IDM_MAPWORLDHEROSGATE4, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_MAPWORLDHEROPORTALS, " ", IDM_MAPWORLDHEROSGATE6, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_MAPWORLDHEROPORTALS, " ", IDM_MAPWORLDHEROSGATE7, 0)) return NULL;


  HMENU POPUP_ROOMS = CreatePopupMenu();
  if(!SimpleAddPopup(POPUP_DIALOG_MENUPAINT, " ", IDM_ROOMS, 0, POPUP_ROOMS)) return NULL;

  HMENU POPUP_PLAYERS = CreatePopupMenu();
  if(!SimpleAddPopup(POPUP_ROOMS, " ", IDM_PLAYERS, 0, POPUP_PLAYERS)) return NULL;
  if(!SimpleAddMenu(POPUP_PLAYERS, " ", IDM_PLAYERS1, MFS_CHECKED)) return NULL;
  if(!SimpleAddMenu(POPUP_PLAYERS, " ", IDM_PLAYERS2, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_PLAYERS, " ", IDM_PLAYERS3, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_PLAYERS, " ", IDM_PLAYERS4, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_PLAYERS, " ", IDM_PLAYERS5, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_PLAYERS, " ", IDM_PLAYERS6, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_PLAYERS, " ", IDM_PLAYERS7, 0)) return NULL;

  if(!SimpleAddSeparator(POPUP_ROOMS)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDWALL, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDCLAIMED, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDHEART, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDLAIR, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDLIBRARY, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDTREASURY, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDCASINO, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDWOODENBRIDGEWATER, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDWOODENBRIDGELAVA, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDTORTURE, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDGRAVEYARD, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDTEMPLE, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDHEROSBRIDGEWATER, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDHEROSBRIDGELAVA, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDMERCENARIES, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDPORTAL, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDHATCHERY, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDTRAINING, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDWORKSHOP, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDGUARD, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDPRISON, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDSTONEBRIDGEWATER, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDSTONEBRIDGELAVA, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDPIT, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_ROOMS, " ", IDM_MAPWORLDMANAOPENED, 0)) return NULL;

  if(!SimpleAddMenu(POPUP_DIALOG_MENUPAINT, " ", IDM_PAINTMODE, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUPAINT, " ", IDM_RECT, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUPAINT, " ", IDM_RECTFILL, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUPAINT, " ", IDM_CIRCLE, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUPAINT, " ", IDM_CIRCLEFILL, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUPAINT, " ", IDM_LINE, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUPAINT, " ", IDM_PEN, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUPAINT, " ", IDM_FILL, 0)) return NULL;
  if(!SimpleAddSeparator(POPUP_DIALOG_MENUPAINT)) return NULL;

  HMENU POPUP_PUTELEM = CreatePopupMenu();
  if(!SimpleAddPopup(POPUP_DIALOG_MENUPAINT, " ", IDM_PUTELEM, 0, POPUP_PUTELEM)) return NULL;
  if(!SimpleAddMenu(POPUP_PUTELEM, " ", IDM_PUTCREATURE, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_PUTELEM, " ", IDM_PUTDOOR, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_PUTELEM, " ", IDM_PUTTRAP, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_PUTELEM, " ", IDM_PUTOBJECT, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_PUTELEM, " ", IDM_PUTMAGICALOBJECT, 0)) return NULL;
  if(!SimpleAddSeparator(POPUP_PUTELEM)) return NULL;
  if(!SimpleAddMenu(POPUP_PUTELEM, " ", IDM_MODIFYCREATURE, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_PUTELEM, " ", IDM_MODIFYDOOR, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_PUTELEM, " ", IDM_MODIFYTRAP, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_PUTELEM, " ", IDM_MODIFYOBJECT, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_PUTELEM, " ", IDM_MODIFYMAGICALOBJECT, 0)) return NULL;

  /* *** MENUDISPLAY *** */
  HMENU POPUP_DIALOG_MENUDISPLAY = CreatePopupMenu();
  if(!SimpleAddPopup(MENUEX_MAINMENU, DIALOG_MENUDISPLAY, 0, 0, POPUP_DIALOG_MENUDISPLAY)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_WINDOWS, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_THUMBNAIL, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_FULLSCREEN, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_MAPSTATS, 0)) return NULL;
  if(!SimpleAddSeparator(POPUP_DIALOG_MENUDISPLAY)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_TOOLBAR, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_MINIMAP, 0)) return NULL;

  HMENU POPUP_MINIMAPPARAMS = CreatePopupMenu();
  if(!SimpleAddPopup(POPUP_DIALOG_MENUDISPLAY, " ", IDM_MINIMAPPARAMS, 0, POPUP_MINIMAPPARAMS)) return NULL;
  if(!SimpleAddMenu(POPUP_MINIMAPPARAMS, " ", IDM_KEEPPROPS, MFS_CHECKED)) return NULL;
  if(!SimpleAddSeparator(POPUP_MINIMAPPARAMS)) return NULL;
  if(!SimpleAddMenu(POPUP_MINIMAPPARAMS, " ", IDM_DISPLAYCREATURES, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_MINIMAPPARAMS, " ", IDM_DISPLAYDOORS, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_MINIMAPPARAMS, " ", IDM_DISPLAYTRAPS, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_MINIMAPPARAMS, " ", IDM_DISPLAYMAGICS, MFS_GRAYED)) return NULL;

  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_MAP, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_FLAGTERRAIN, MFS_CHECKED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_FLAGCREATURES, MFS_CHECKED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_FLAGDOORS, MFS_CHECKED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_FLAGTRAPS, MFS_CHECKED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_FLAGMAGICALS, MFS_CHECKED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_FLAGOBJECTS, MFS_CHECKED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_FLAGAREAS, MFS_CHECKED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_FLAGPATHS, MFS_CHECKED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_FLAGGATES, MFS_CHECKED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_FLAGEFFECTS, MFS_CHECKED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_FLAGCAMERAS, MFS_CHECKED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_OPTIONS, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_MOREDETAILS, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_EXPANDGATES, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_OBJECTSCOLOR, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUDISPLAY, " ", IDM_MAGICSCOLOR, 0)) return NULL;

  /* *** MENUDISPLAY *** */
  HMENU POPUP_DIALOG_MENUPROPERTIES = CreatePopupMenu();
  if(!SimpleAddPopup(MENUEX_MAINMENU, DIALOG_MENUPROPERTIES, 0, 0, POPUP_DIALOG_MENUPROPERTIES)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUPROPERTIES, " ", IDM_PROPERTIES, MFS_GRAYED)) return NULL;
  if(!SimpleAddSeparator(POPUP_DIALOG_MENUPROPERTIES)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUPROPERTIES, " ", IDM_PROPERTIESSAVE, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUPROPERTIES, " ", IDM_PROPERTIESSAVENOW, MFS_GRAYED)) return NULL;

  /* *** MENUHELP *** */
  HMENU POPUP_DIALOG_MENUHELP = CreatePopupMenu();
  if(!SimpleAddPopup(MENUEX_MAINMENU, DIALOG_MENUHELP, 0, 0, POPUP_DIALOG_MENUHELP)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUHELP, " ", IDM_HELPCONTENT, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUHELP, " ", IDM_HELPFIRSTRUN, MFS_GRAYED)) return NULL;
  if(!SimpleAddSeparator(POPUP_DIALOG_MENUHELP)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUHELP, " ", IDM_HELPVERSIONS, 0)) return NULL;
  if(!SimpleAddSeparator(POPUP_DIALOG_MENUHELP)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_MENUHELP, " ", IDM_ABOUT, MFS_GRAYED)) return NULL;

  return MENUEX_MAINMENU;
}

HMENU CreateMenu_CTXMENU() {
  HMENU MENUEX_CTXMENU = CreateMenu();

  HMENU POPUP_DIALOG_0 = CreatePopupMenu();
  if(!SimpleAddPopup(MENUEX_CTXMENU, "0", 0, 0, POPUP_DIALOG_0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_0, " ", IDM_PLAYERS, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_0, " ", IDM_PLAYERS1, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_0, " ", IDM_PLAYERS2, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_0, " ", IDM_PLAYERS3, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_0, " ", IDM_PLAYERS4, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_0, " ", IDM_PLAYERS5, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_0, " ", IDM_PLAYERS6, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_0, " ", IDM_PLAYERS7, 0)) return NULL;
  if(!SimpleAddSeparator(POPUP_DIALOG_0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_0, " ", IDM_MENUCANCEL, 0)) return NULL;

  HMENU POPUP_DIALOG_1 = CreatePopupMenu();
  if(!SimpleAddPopup(MENUEX_CTXMENU, "1", 0, 0, POPUP_DIALOG_1)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_1, " ", IDM_MAPWORLDHEROPORTALS, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_1, " ", IDM_MAPWORLDHEROSGATE1, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_1, " ", IDM_MAPWORLDHEROSGATE2, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_1, " ", IDM_MAPWORLDHEROSGATE3, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_1, " ", IDM_MAPWORLDHEROSGATE4, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_1, " ", IDM_MAPWORLDHEROSGATE6, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_1, " ", IDM_MAPWORLDHEROSGATE7, 0)) return NULL;
  if(!SimpleAddSeparator(POPUP_DIALOG_1)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_1, " ", IDM_MENUCANCEL, 0)) return NULL;

  HMENU POPUP_DIALOG_2 = CreatePopupMenu();
  if(!SimpleAddPopup(MENUEX_CTXMENU, "2", 0, 0, POPUP_DIALOG_2)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOM, MFS_GRAYED)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOMM5, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOMM4, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOMM3, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOMM2, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOMM1, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOMM0, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOMP1, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOMP2, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOMP3, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOMP4, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOMP5, 0)) return NULL;
  if(!SimpleAddSeparator(POPUP_DIALOG_2)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOMUSER1, 0)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_ZOOMUSER2, MFS_GRAYED)) return NULL;
  if(!SimpleAddSeparator(POPUP_DIALOG_2)) return NULL;
  if(!SimpleAddMenu(POPUP_DIALOG_2, " ", IDM_MENUCANCEL, 0)) return NULL;

  return MENUEX_CTXMENU;
}
