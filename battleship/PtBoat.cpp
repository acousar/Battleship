#include "Ship.h"

class PtBoat : public Ship {
    public:
        PtBoat() : Ship('P', 2, "PT Boat") { position.clear(); }
        char GetSymbol() { return symbol; }
        int GetSize() { return size; }
		string GetType() { return type; }
};
