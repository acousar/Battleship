#include <iostream>
#include "Fleet.h"
#include "DefinedErrors.h"

using namespace std;

void FleetTest()
{
	Fleet fleet;

	map<string, Ship*> test = fleet.GetShips();

	map<string, Ship*>::iterator itr;

	for(itr = test.begin(); itr != test.end(); ++itr)
	{
		cout << itr->first << endl;
	}

	AircraftCarrier* ship = (AircraftCarrier*)test["Aircraft Carrier"];
	cout << "symbol is" << ship->GetSymbol() << endl;
	return;

}