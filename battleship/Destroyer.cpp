#include "Ship.h"

class Destroyer : public Ship {
    public:
        Destroyer() : Ship('D', 3, "Destroyer") { position.clear(); }
        char GetSymbol() { return symbol; }
        int GetSize() { return size; }
		string GetType() { return type; }
};
