#pragma once
#ifndef DAMAGE_REPORT_H
#define DAMAGE_REPORT_H

#include <string>
#include <map>

using namespace std;

class DamageReport {

private:
	string AttackResult;
	string ShipType;
	map<string, char> ShipCoordinates;
  bool isFleetSunk;

public:
  DamageReport() : AttackResult(""), ShipType(""), isFleetSunk(false) { ShipCoordinates.clear(); }
	~DamageReport() {}

	void SetAttackResult(string attackResult) { AttackResult = attackResult; }
	string GetAttackResult() { return AttackResult; }

	void  SetShipType(string shipType) { ShipType = shipType; }
	string GetShipType() { return ShipType; }

	void SetShipCoordinates(map<string, char> coordinates) { ShipCoordinates = coordinates; }
	void SetShipCoordinates(string coordinate) { ShipCoordinates[coordinate] = 'D'; }
	map<string, char> GetShipCoordinates() { return ShipCoordinates; }

  void SetFleetStatus(bool hasFleetBeenDecimated) { isFleetSunk = hasFleetBeenDecimated; }
  bool GetFleetStatus() { return isFleetSunk; }
};

#endif