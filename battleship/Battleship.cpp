#include "Ship.h"

class Battleship : public Ship {
    public:
        Battleship() : Ship('B', 4, "Battleship" ) { position.clear(); }
        char GetSymbol() { return symbol; }
        int GetSize() { return size; }
		string GetType() { return type; }
};
