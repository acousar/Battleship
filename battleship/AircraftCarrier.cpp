#include "Ship.h"

class AircraftCarrier : public Ship {

 public:
  AircraftCarrier() : Ship('A', 5, "Aircraft Carrier" ) { position.clear(); }
  char GetSymbol() { return symbol; }
  int GetSize() { return size; }
  string GetType() { return type; }
};