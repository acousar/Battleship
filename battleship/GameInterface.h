#pragma once
#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include "Player.h"

class GameInterface
{
private:
  vector<Player*> player;

public:
	GameInterface(void);
	~GameInterface(void);
  void Start();

private:
 
  void PlayerSetup(Player* player);
  void FleetPositioning(Player* player);
  void ResolveConflicts();
  Player* PlayGame();
  void ProcessWinner(Player*);
};

#endif