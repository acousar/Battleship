#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <string>
#include <vector>
#include "Ship.h"

using namespace std;

 enum {
    BOARD_ROWS = 10, 
    BOARD_COLUMNS = 10
  };

class Board {

   private:
    char field[BOARD_COLUMNS][BOARD_ROWS];

  public:
	Board(void);
	~Board(void);
	
	int PlaceShip(Ship* ship, std::string shipBow, std::string shipStern);
    void MarkBoard(std::string square, std::string damageIndicator);
	bool AreCoordinatesValid(std::string coordinates);
	vector<string> GetConflicts(Board* opponentBoard);
	string DisplayBoard();

	//  All private methods used only by this class.
  private:
	  
    bool TranslateToMultiDimensionalValue(std::string coordinate, int& row, int& column);
    int ValidateShipPlacementCoordinate(int shipSize, int x1, int y1, int x2, int y2);
	void AddShipToField(Ship* ship, int x1, int y1, int x2, int y2);
	std::string TranlateToGridCoodinates(int x, int y);
    void InitializeBoard();
	void Swap(int& t1, int& t2);
  };

#endif