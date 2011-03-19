#pragma once
#ifndef FLEET_H
#define FLEET_H

#include <map>
#include <string>
#include <vector>

#include "Ship.h"
#include "AircraftCarrier.cpp"
#include "Battleship.cpp"
#include "Destroyer.cpp"
#include "PtBoat.cpp"
#include "DamageReport.h"

using namespace std;

class Fleet {
private:
  map<string, Ship*> ships;
	map<string, Ship*>::iterator ship_itr;

  AircraftCarrier aircraftCarrier;      
  Battleship battleShip[1];
  //Destroyer destroyer[3];
  //PtBoat ptBoat[4];

  bool isFleetSunk;

public:
  Fleet();
  ~Fleet(){}
  
  DamageReport ProcessAttack(string targetCoordinate);
  map<string,char> ResolveConflicts(vector<string> conflicts);
  Ship* GetShipInPosition(string coordinate);
  map<string, Ship*> GetShips();
	void ReportShipSunk(Ship*);
  bool IsFleetSunk();
};

#endif
