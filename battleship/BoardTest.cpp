#include <iostream>
#include "Board.h"
#include "Ship.h"
#include "DefinedErrors.h"

using namespace std;
using namespace game;

class TestShip : public Ship {
    public:
        TestShip() { position.clear();}
        char GetSymbol(){ return 'X'; }
        int GetSize() { return 3; }
/*
    private:
        map<string,string> position;
        map<string, string>::iterator map_iter;
        string status;
*/
};

void BoardTest()
{
	Board *board = new Board();
	//board->DisplayBoard();

    TestShip* testShip = new TestShip();
    TestShip* duoShip = new TestShip();

    int result = board->PlaceShip(testShip, "f2", "d2");
    if ( result == ShipPlacement::INVALID_COORDINATES )
        cout << "Co-ordinates are invalid" << endl;
    if ( result == ShipPlacement::SHIP_PLACEMENT_INVALID )
        cout << "Placement is invalid" << endl;
    if (result == ShipPlacement::SPACE_OCCUPIED )
        cout << "Space is occupied" << endl;

    board->DisplayBoard();

    int result2 = board->PlaceShip(duoShip, "f3", "f5");
    if ( result2 == ShipPlacement::INVALID_COORDINATES )
        cout << "Co-ordinates are invalid" << endl;
    if ( result2 == ShipPlacement::SHIP_PLACEMENT_INVALID )
        cout << "Placement is invalid" << endl;
    if (result2 == ShipPlacement::SPACE_OCCUPIED )
        cout << "Space is occupied" << endl;

    cout << board->DisplayBoard();

    board->MarkBoard("e9", "MISS");
    board->MarkBoard("f2", "HIT");

    cout << board->DisplayBoard();
}
