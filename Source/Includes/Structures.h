
#ifndef EDITORSTRUCTS_INCLUDES
#define EDITORSTRUCTS_INCLUDES

#include "CameraPaths.h"
#include "Global.h"
#include "GlobalVariables.h"
#include "LastError.h"
#include "Menus.h"
#include "Triggers.h"

extern DWORD		ASCII_Triggers[];
extern DWORD		ASCII_Actions[];
extern CAMERAPATHDESC	Description[];
extern ELEMENT		PathAreas[];
extern ELEMENT		Effects[];
extern ELEMENT		VarRooms[];
extern ELEMENT		Rewards[];
extern BYTE*		DefaultTerrain;
extern BYTE*		DefaultRooms;
extern BYTE*		DefaultDoors;
extern BYTE*		DefaultTraps;
extern BYTE*		DefaultKeeperSpells;
extern BYTE*		DefaultCreatures;
extern BYTE*		DefaultCreatureSpells;
extern DWORD*		GTOrder[];
extern DWORD*		GROrder[];
extern DWORD*		GDOrder[];
extern DWORD*		GAOrder[];
extern DWORD*		GSOrder[];
extern DWORD*		GCOrder[];
extern DWORD*		GOOrder[];
extern GLOBALATTRLIST	GAttribs[];
extern ELEMENT		GTerrains[];
extern ELEMENT		GRooms[];
extern ELEMENT		GDoors[];
extern ELEMENT		GDoorsMats[];
extern ELEMENT		GDoorsCrates[];
extern ELEMENT		GDoorsKeys[];
extern ELEMENT		GTraps[];
extern ELEMENT		GTrapsCrates[];
extern ELEMENT		GTrapsTypes[];
extern ELEMENT		GShots[];
extern ELEMENT		GSpells[];
extern ELEMENT		GSpellsHand[];
extern ELEMENT		GSpellsCast[];
extern ELEMENT		GSpellsTrget[];
extern ELEMENT		GCreatures[];
extern ELEMENT		GFightStyle[];
extern ELEMENT		GJobClass[];
extern ELEMENT		GBeds[];
extern ELEMENT		GARooms[];
extern ELEMENT		GCrSpells[];
extern ELEMENT		GCrMelee[];
extern ELEMENT		GCrRes[];
extern ELEMENT		GCrAbilities[];
extern ELEMENT		GCrSwipes[];
extern ELEMENT		GCrGammas[];
extern ELEMENT		GCrJobs[];
extern ELEMENT		GCrSpellsLst[];
extern ERRORTABLE	Compiler[];
extern char*		MngrSort[];
extern ELEMENT 		PvIcons[];
extern ELEMENT		CrIcons[];
extern ELEMENT		DtIcons[];
extern ELEMENT		ObIcons[];
extern char*		Versions[];
extern ELEMENT		NewMap[];
extern ELEMENT		World[];
extern ELEMENT		Rooms[];
extern ELEMENT		Gates[];
extern ELEMENT		Walls[];
extern ELEMENT		CPURooms[];
extern ELEMENT		MapVars[];
extern char*		TextFiles[];
extern FLAGARRAY	DisplayFlags[];
extern CUSTOMITEM 	MainMenu[];
extern CUSTOMITEM	PlayersMenu[];
extern CUSTOMITEM 	GatesMenu[];
extern CUSTOMITEM	ZoomMenu[];
extern ELEMENT		DrawingTools[];
extern ELEMENT		MiscTools[];
extern ELEMENT		BadCreatures[];
extern ELEMENT		BadElites[];
extern ELEMENT		Heros[];
extern ELEMENT		Doors[];
extern ELEMENT		Traps[];
extern ELEMENT		Spells[];
extern ELEMENT		Magics[];
extern ELEMENT		MagicsV17[];
extern ELEMENT		Objects[];
extern DWORD		WorldCols[];
extern DWORD		RoomsCols[][7];
extern DWORD		WallsCols[];
extern PLAYERINFO	Players[];
extern TRIGGERINFO	Triggers[];
extern TRIGGERINFO	Actions[];
extern ELEMENT		TrSpecial[];
extern ELEMENT		TrPlayers[];
extern ELEMENT		TrImages[];
extern ELEMENT		TrButtons0[];
extern ELEMENT		TrButtons1[];
extern ELEMENT		Interface[];
extern ELEMENT		Terrain[];
extern ELEMENT		TrCreatures[];
extern ELEMENT		TrRooms[];

#endif
