#include <cstdlib>
#include <cctype>
#include <sstream>
#include "Board.h"
#include "ShipPlacementEnum.h"

Board::Board(void) {
    InitializeBoard();
}

Board::~Board(void) {
}

void Board::InitializeBoard() {
    for(int x=0; x<BOARD_COLUMNS; x++)
        for(int y=0; y<BOARD_ROWS; y++)
            field[x][y] = '~';
}

int Board::PlaceShip(Ship* ship, std::string bow, std::string stern) {
    // NOTE:  bow and stern are arbitrary for the endpoints of ship.

    int x1=0; int x2=0;
    int y1=0; int y2=0;

    // Translate the Bow Position
    if ( TranslateToMultiDimensionalValue(bow, x1, y1) == false )
        return ShipPlacement::INVALID_COORDINATES;

    // Translate the Stern Position
    if ( TranslateToMultiDimensionalValue(stern, x2, y2) == false )
        return ShipPlacement::INVALID_COORDINATES;

    // Validate placing ship on board doesn't attempt to occupy a space
    // already claimed by ship within fleet.
    // Validate the distance between the coordinates are equal to size 
    // of the ship.
	int shipPlacementResult = ValidateShipPlacementCoordinate(ship->GetSize(), x1, y1, x2, y2);
    if ( shipPlacementResult != ShipPlacement::VALID_SPACE )
        return shipPlacementResult;

    // Place ship on the board as well as update Ships positional coverage
    AddShipToField(ship, x1, y1, x2, y2);

    return ShipPlacement::SHIP_PLACEMENT_SUCCESSFULL; 
}

string Board::DisplayBoard() {
    stringstream boardDisplay;
    boardDisplay << "     A B C D E F G H I J " << std::endl;
    boardDisplay << "    ---------------------" << std::endl;
   
    for(int x=0; x<BOARD_COLUMNS; x++) { 
        if( x < (BOARD_COLUMNS -1) ) { boardDisplay << " "; }
        boardDisplay << (x+1) << " | ";
        for(int y=0; y<BOARD_ROWS; y++) {
            boardDisplay << field[x][y] << " ";
            if( y == (BOARD_ROWS -1) )
                boardDisplay << "|" << std::endl;
        }
    }

    boardDisplay << "    ---------------------" << std::endl;
    
    return boardDisplay.str();
}

bool Board::AreCoordinatesValid(std::string coordinates) {
    int x, y;
    
    // Are the coordinates valid in accord to the board?
    if(TranslateToMultiDimensionalValue(coordinates, x, y) == false) {
        return false;
    }

    // Has this coordinate been previously targeted?
    char positionstatus = field[y][x];
    if (positionstatus == 'M' || positionstatus =='*' || positionstatus == 'H')
        return false;

    return true;
}

// Validate and Translate the alphanumeric board position.
bool Board::TranslateToMultiDimensionalValue(std::string coordinate, int &row, int &column) {

  // Convert position to lower case (to support upper case entry)
  // Subtract the value of 97 to translate to alphabetical decimal equivalent, base 0
  row = (int)std::tolower(coordinate[0]) - 97;

  // Get the substring after the first character to the end, supporting two digits (i.e. 10)
  // convert the numerical string to its ineteger equivalent
  // subtract 1 to obtain the base 0 equivalent
  column = atoi(coordinate.substr(1).c_str()) - 1;

  // if the values of x and y are not within between [0,9] then we will
  // be out of bounds return false to handle
  if ( (row < 0 || row > 9) || (column < 0 || column > 9) )
      return false;

  return true;
}

std::string Board::TranlateToGridCoodinates(int x, int y)
{
    std::stringstream alphanumeric;

    char alpha = (char)(x + 97);
    int numeric = y + 1;

    alphanumeric << alpha << numeric;

    return alphanumeric.str();
}

// Validate the placement of the ship will fall within horizontal or vertical alignment
// Successfull Ship Placement validation will result in the ships size return
// otherwise 
int Board::ValidateShipPlacementCoordinate(int shipSize, int x1, int y1, int x2, int y2) {
    int placementSize = 0;
    int x = abs(x1 - x2); // Validate Horizontal Alignment (e.g. = 0)
    int y = abs(y1 - y2); // Validate Vertical Alignment (e.g. = 0)

    if ( (x == 0) && (y != 0) )
        placementSize = y + 1;  // Ship to be placed vertically

    if( (x != 0) && (y == 0) )
        placementSize = x + 1; // Ship to be placed horizontally

    // if placementSize not set (e.g. = 0) then coordinates called aren't adjacent
    // if the placement size does not match the ships size then coordinates are too long / or too short
    if (placementSize <= 0 || placementSize != shipSize)
        return ShipPlacement::INVALID_SHIP_PLACEMENT_SIZE;

    // Testing that all columns and rows are not occupied.
    for(int column=x1; column<=x2; column++)
        for(int row=y1; row<=y2; row++)
            if( field[row][column] != '~')
                return ShipPlacement::SPACE_OCCUPIED;

	return ShipPlacement::VALID_SPACE;
}

void Board::AddShipToField(Ship* ship, int x1, int y1, int x2, int y2) {
    
  // Need to position ship in ascending order
    Swap(x1, x2);
    Swap(y1, y2);

    // Testing that all columns and rows are not occupied.
    /*for(int column=x1; column<=x2; column++)
        for(int row=y1; row<=y2; row++)
            if( field[row][column] != '~')
                return false;*/
    
    // Placing ship on the battle field
    // NOTE:
    // In a Cartesion Grid we describe a point as (column, row)
    // in programming the two-dimenstional array the point is  [row][column]

    for(int column=x1; column<=x2; column++)
        for(int row=y1; row<=y2; row++)
    {
        // DEBUG std::cout << column << "," << row << std::endl;
        std::string position = TranlateToGridCoodinates(column, row);
        ship->SetPosition(position);

        // Update Field
        field[row][column] = ship->GetSymbol(); 
    }
}

void Board::Swap(int &t1, int &t2) {
    int temp;
    if(t1 < t2)
        return;

    temp = t1;
    t1 = t2;
    t2 = temp;
}

void Board::MarkBoard(std::string square, std::string damageIndicator) {
    int x=0; int y=0;
    char mark = '~';

    TranslateToMultiDimensionalValue(square, x, y);
    
    if(damageIndicator == "MISS")
        mark = 'M';
    else if (damageIndicator == "HIT")
        mark = 'H';
    else if (damageIndicator == "SUNK")
        mark = '*';
   
    field[y][x] = mark;
}

 vector<string> Board::GetConflicts(Board* opponentBoard) {

   if(opponentBoard == this) {
     // Invalid to get conflicts with self, will always result in  all ships being sunk
     throw opponentBoard;
   }

    vector<string> conflicts; 
    conflicts.clear();

    for(int row=0; row<10; row++) 
        for(int column=0; column<10; column++)
            if( (field[row][column] != '~') && (opponentBoard->field[row][column] != '~') ) {
                string conflict = TranlateToGridCoodinates(column, row);
                conflicts.push_back(conflict);
            }

    return conflicts;
}