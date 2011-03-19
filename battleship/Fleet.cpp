#include "Fleet.h"
#include <sstream>

Fleet::Fleet()
{
  // Aircraft Carriers - 1 total
	aircraftCarrier.SetName("Aircraft Carrier");
	ships[aircraftCarrier.GetName()] = &aircraftCarrier;


  // Battle Ships - 2 total
  for(int i = 0; i<1; i++) {
    stringstream name;
    name << "Battleship " << (i+1);
    battleShip[i].SetName(name.str());
    ships[battleShip[i].GetName()] = &battleShip[i];
  }
/*
  // Destroyers - 3 total
  for(int i=0; i<3; i++) {
    stringstream name;
    name << "Destroyer " << (i+1);
	  destroyer[i].SetName(name.str());
	  ships[destroyer[i].GetName()] = &destroyer[i];
  }
	
  // PT Boats - 4 total
  for (int i=0; i<4; i++) {
    stringstream name;
    name << "PT Boat " << (i+1);
	  ptBoat[i].SetName(name.str());
	  ships[ptBoat[i].GetName()] = &ptBoat[i];
  }
  */

  isFleetSunk = false;
}

Ship* Fleet::GetShipInPosition(string coordinate)
{
	// For every ship in the fleet find the one whose position matches the target
	for(ship_itr = ships.begin(); ship_itr != ships.end(); ++ship_itr)
	{
		map<string, char> position = ship_itr->second->GetPosition();
		map<string, char>::iterator pos_itr = position.find(coordinate);
		
		if(pos_itr != position.end())
			return ship_itr->second;
	}
	
	return 0;
}

map<string, char> Fleet::ResolveConflicts(vector<string> conflictedCoordinates)
{
	map<string, char> conflictedShipPositions;
	conflictedShipPositions.clear();

	for(unsigned int i=0; i<conflictedCoordinates.size(); i++)
	{
		Ship* ship = GetShipInPosition(conflictedCoordinates[i]);
		if(ship != 0) {

      map<string, char> position = ship->GetPosition();
      ReportShipSunk(ship);

			map<string, char>::iterator positionBegin = position.begin();
			map<string,char>::iterator positionEnd = position.end();
			
      // insert the mapped range of values
			conflictedShipPositions.insert(positionBegin, positionEnd);
		}
	}

	return conflictedShipPositions;
}

void Fleet::ReportShipSunk(Ship* ship)
{
	ships.erase(ship->GetName());

  // if no ships are left, then there's no fleet, thus fleet is sunk
  isFleetSunk = ships.empty();
}

DamageReport Fleet::ProcessAttack(string targetCoordinate)
{
  DamageReport report;
  string shipDamage = "MISS";
  Ship* ship = GetShipInPosition(targetCoordinate);
  
  // if no ship is returned at this position, it was a miss
  if(ship == 0) {
    report.SetAttackResult(shipDamage);
    report.SetShipCoordinates(targetCoordinate);
    report.SetShipType("Ship");  // Generic designation so that report will say "missed ship"
	return report;
  }

  shipDamage = ship->GetDamageReport(targetCoordinate);
  report.SetAttackResult(shipDamage);
  report.SetShipType(ship->GetType());
  
  if(shipDamage == "HIT") {
	  report.SetShipCoordinates(targetCoordinate);
	  return report;
  }
  
  // Report the coordinates that sunk the ship
  report.SetShipCoordinates(ship->GetPosition());

  // this ship is reported SUNK and is removed from the game.
  ReportShipSunk(ship);

  // One final check made checking the condition of the fleet
  report.SetFleetStatus(isFleetSunk);
  return report;
}

bool Fleet::IsFleetSunk() {
  return isFleetSunk;
}

map<string, Ship*> Fleet::GetShips() {
  return ships;
}