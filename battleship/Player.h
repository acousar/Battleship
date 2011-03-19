#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Board.h"
#include "Fleet.h"
#include "AttackReport.h"

using namespace std;
//using namespace game;

class Player {

private:
  bool doShipHitNotification;
  int numberOfShotsFired;
  int numberOfMisses;
  int numberOfHits;
	string name; 
	Board board;
	Fleet fleet;

public:
	Player() : numberOfShotsFired(0), numberOfMisses(0), numberOfHits(0), doShipHitNotification(false)  {}
	~Player() {}

	void SetName(string n) { name = n; }
	
  string GetName() { return name; }

 	void SetShipHitNotification() { doShipHitNotification = true; }

 	Board* GetBoard() { return &board; }

  int ResolveConflict(vector<string> gridconflicts);

  map<string, Ship*> GetFleet() { return fleet.GetShips(); }

	int PositionFleet(Ship* ship, string position1, string position2);

  AttackReport* Shoot(Player* player, string target);  // Shoot opponent (Player*) at target (string)

  int GetNumberOfShotsFired() { return numberOfShotsFired; }

  int GetNumberOfMisses() { return numberOfMisses; }

  int GetNumberOfHits() { return numberOfHits; }

  float GetHitsPercentage() { return ( (float(numberOfHits)) / (float(numberOfShotsFired)) * 100);  }

private:
	bool IsTargetInFleet(string targetCoordinate);
	void UpdateBoard(map<string, char>, string);
  DamageReport ProcessAttack(string);   // Process attack at target position
};

#endif