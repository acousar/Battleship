#include <iostream>
#include <vector>
#include <string>


#include "Player.h"
#include "DefinedErrors.h"

using namespace std;

void PositionTest();
void ShootingTests();
void ConflictTest();
void GamePlay();
void PlayerSinksOpponentsShip();

void BoardDisplay(string, Board*, Board*);

void PlayerTest()
{
	//PositionTest();
	//ShootingTests();
	//ConflictTest();
	//GamePlay();

	PlayerSinksOpponentsShip();

}

void PositionTest()
{
	// Test positioning
	Player player1;
	player1.SetName("one");
	player1.PositionFleet(); 
	
	Player player2;
	player2.SetName("two");
	player2.PositionFleet(); 

	return;
}

void ShootingTests()
{
	// Test positioning
	Player player1;
	player1.SetName("one");
	player1.PositionFleet(); 
	
	Player player2;
	player2.SetName("two");
	player2.PositionFleet(); 

	// Test Player Shooting own location
	player1.Shoot(&player2, "a1");
	player2.Shoot(&player1, "d5");

	//Test Misses
	player1.Shoot(&player2, "c3");
	player2.Shoot(&player1, "j10");
	
	// Test Hits (p1 @ a1, a2, a3, a4, a5)
	//           (p2 @ d5, e5, f5, g5, h5)
	player1.Shoot(&player2, "f5");
	player2.Shoot(&player1, "a1");
	

	//  Player one sinks player two
	player1.Shoot(&player2, "d8");
	player1.Shoot(&player2, "e8");
	player1.Shoot(&player2, "f8");
	player1.Shoot(&player2, "g8");
	player1.Shoot(&player2, "h8");

	return;
}

void ConflictTest()
{
	// Test positioning
	Player player1;
	player1.SetName("one");
	player1.PositionFleet(); 
	
	Player player2;
	player2.SetName("two");
	player2.PositionFleet(); 

	Board* board1 = player1.GetBoard();
	Board* board2 = player2.GetBoard();
	
	//vector<string> positionConflicts;
	//positionConflicts.clear();
	vector<string> testConflicts = board1->GetConflicts(board2);
	
  for(unsigned int i=0; i<testConflicts.size(); i++)
		cout << "Conflict at: " << testConflicts[i] << endl;

	player1.ResolveConflict(testConflicts);
	player2.ResolveConflict(testConflicts);
}

void GamePlay()
{
	// Position The Fleet
	Player player1;
	player1.SetName("one");
	player1.PositionFleet(); 
	
	Player player2;
	player2.SetName("two");
	player2.PositionFleet(); 

	// Resolve Board Conflicts
	Board* board1 = player1.GetBoard();
	Board* board2 = player2.GetBoard();
	
	vector<string> positionConflicts;
	positionConflicts.clear();
	vector<string> testConflicts = board1->GetConflicts(board2);

	for(unsigned int i=0; i<testConflicts.size(); i++)
		cout << "Conflict at: " << testConflicts[i] << endl;

	player1.ResolveConflict(testConflicts);
	player2.ResolveConflict(testConflicts);

	// Shoot out

	// Test Player Shooting own location
	player1.Shoot(&player2, "a1");
	player2.Shoot(&player1, "d5");

	//Test Misses
	player1.Shoot(&player2, "c3");
	player2.Shoot(&player1, "j10");
	
	// Test Hits (p1 @ a1, a2, a3, a4, a5)
	//           (p2 @ d5, e5, f5, g5, h5)
	player1.Shoot(&player2, "f5");
	player2.Shoot(&player1, "a1");
	

	//  Player one sinks player two
	player1.Shoot(&player2, "d8");
	player1.Shoot(&player2, "e8");
	player1.Shoot(&player2, "f8");
	player1.Shoot(&player2, "g8");
	player1.Shoot(&player2, "h8");

}

void PlayerSinksOpponentsShip()
{
	// GAME will player1 & player2
	Player player1;
	Player player2;

	/*
		GAME: Start of the game
				1) player 1
					a) set name
					b) position fleet
				2) player 2
					a) set name
					b) position fleet

				3) Resolve positioned ship conflict

	*/

	// NOTE: possibly have player enter their name
	player1.SetName("Player One");

	// Player 1 actually wants the name of the ship reported
	player1.SetShipHitNotification();

	// GAME: will have player 1 position their fleet
	player1.PositionFleet(); 
	// DEBUG: cout << "Player 1 Board: " << endl;	player1.GetBoard()->DisplayBoard();

	// NOTE: possibly have player enter thier name
	player2.SetName("Player Two");

	// GAME: will indicate have player 2 position their fleet
	player2.PositionFleet(); 
	//DEBUG: cout << "Player 2 Board: " << endl;	player2.GetBoard()->DisplayBoard();

	// GAME: get the boards of both players
	Board* board1 = player1.GetBoard();
	Board* board2 = player2.GetBoard();

	// GAME: This can go either way...board2->GetConflicts(&board1)
	//        It all gets resolved...returning all the conflicted positions found
	vector<string> boardConflicts = board1->GetConflicts(board2);
	
	// GAME: have each player resolve their conflicts from conflics found by the board.
	player1.ResolveConflict(boardConflicts);
	// DEBUG: cout << "Player 1 Resolved Board:" << endl; board1->DisplayBoard();

	player2.ResolveConflict(boardConflicts);
	// DEBUG: cout << "Player 2 Resolved Board:" << endl;	board2->DisplayBoard();


	/*
	*
	*  THIS IS WHERE THE GAME WILL BEGIN..PLAYER ONE GOES FIRST
	*
	*/
	
	// GAME BEGIN: We will loop here until the the first player with no ships left lasts

	// GAME: Player one picks a coordinate to shoot
	player1.Shoot(&player2, "k9");  // player 1 chooses an illegal coordinate
	                                //  TODO: Loop back and choose another coordinate
	// DEBUG:  BoardDisplay("PLAYER 1 SHOOTS", board1, board2);


	player1.Shoot(&player2, "a1");  // player 1 chooses to shoot empty spot of sunken ship
									// TODO: Loop back and choose another coordinate
	// DEBUG:  BoardDisplay("PLAYER 1 SHOOTS", board1, board2);
	

	player1.Shoot(&player2, "f10"); // player 1 misses
	// DEBUG:  BoardDisplay("PLAYER 1 SHOOTS", board1, board2);


	player2.Shoot(&player2, "a10");  // this is a code error should catch this.
	// DEBUG:  BoardDisplay("PLAYER 2 SHOOTS", board1, board2);

	player2.Shoot(&player1, "i9"); // player 2 hits player1's ptboat ;)
	//BoardDisplay("PLAYER 2 SHOOTS", board1, board2);

	player1.Shoot(&player2, "a6"); // player 1 hits players2's carrier
	//BoardDisplay("PLAYER 1 SHOOTS", board1, board2);

	//player2.Shoot(&player1, "i10"); // player 2 misses his attempt
	//BoardDisplay("PLAYER 2 SHOOTS: i10", board1, board2);

	//player1.Shoot(&player2, "b6"); // Player 1 does not miss next shoot
	//BoardDisplay("PLAYER 1 SHOOTS", board1, board2);

	player2.Shoot(&player1, "j9"); // Player 2 shoots and sinks player 1's ship
	BoardDisplay("PLAYER 2 SHOOTS", board1, board2);

	// GAME END
	return;
}

void BoardDisplay(string message, Board* b1, Board* b2)
{
	char pause;
	cout << message << endl;
  cout << "what player 1 sees:" << endl; b1->DisplayBoard();
	cout << "what player 2 sees:" << endl; b2->DisplayBoard();
	cin >> pause;
}