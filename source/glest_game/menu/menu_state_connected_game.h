// ==============================================================
//	This file is part of Glest (www.glest.org)
//
//	Copyright (C) 2001-2005 Marti�o Figueroa
//
//	You can redistribute this code and/or modify it under
//	the terms of the GNU General Public License as published
//	by the Free Software Foundation; either version 2 of the
//	License, or (at your option) any later version
// ==============================================================

#ifndef _GLEST_GAME_MENUSTATECONNECTEDGAME_H_
#define _GLEST_GAME_MENUSTATECONNECTEDGAME_H_

#include "main_menu.h"
#include "chat_manager.h"

namespace Glest{ namespace Game{

// ===============================
// 	class MenuStateConnectedGame
// ===============================

class MenuStateConnectedGame: public MenuState{
private:
	GraphicButton buttonDisconnect;
	GraphicButton buttonPlayNow;
	GraphicLabel labelControl;
	GraphicLabel labelFaction;
	GraphicLabel labelTeam;
	GraphicLabel labelMap;
	GraphicLabel labelFogOfWar;
	GraphicLabel labelTechTree;
	GraphicLabel labelTileset;
	GraphicLabel labelMapInfo;
	GraphicLabel labelStatus;
	GraphicLabel labelInfo;

	GraphicListBox listBoxMap;
	GraphicListBox listBoxFogOfWar;
	GraphicListBox listBoxTechTree;
	GraphicListBox listBoxTileset;
	vector<string> mapFiles;
	vector<string> techTreeFiles;
	vector<string> tilesetFiles;
	vector<string> factionFiles;
	GraphicLabel labelPlayers[GameConstants::maxPlayers];
	GraphicListBox listBoxControls[GameConstants::maxPlayers];
	GraphicListBox listBoxFactions[GameConstants::maxPlayers];
	GraphicListBox listBoxTeams[GameConstants::maxPlayers];
	GraphicLabel labelNetStatus[GameConstants::maxPlayers];
	MapInfo mapInfo;

	bool needToSetChangedGameSettings;
	time_t lastSetChangedGameSettings;

	Console console;
	ChatManager chatManager;
	
	string currentFactionName;
	string currentMap;
	bool settingsReceivedFromServer;
	

public:
	MenuStateConnectedGame(Program *program, MainMenu *mainMenu, bool openNetworkSlots= false);

	void mouseClick(int x, int y, MouseButton mouseButton);
	void mouseMove(int x, int y, const MouseState *mouseState);
	void render();
	void update();

    virtual void keyDown(char key);
    virtual void keyPress(char c);

private:

    bool hasNetworkGameSettings();
	void reloadFactions();
	void loadFactions(const GameSettings *gameSettings);
};

}}//end namespace

#endif
