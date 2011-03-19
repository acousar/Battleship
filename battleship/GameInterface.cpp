#include <iostream>
#include <sstream>

#include "GameInterface.h"
#include "ShipPlacementEnum.h"
#include "AttackReport.h"

GameInterface::GameInterface(void)
{
  // Create the two players that will play the game 
  player.push_back(new Player);
  player.push_back(new Player);
}

GameInterface::~GameInterface(void)
{
  // Delete the players
  for(unsigned int i=0; i<player.size(); i++) {
    delete player[i];
  }
}

void GameInterface::Start()
{
  for(unsigned int i=0; i<player.size(); i++) {
      PlayerSetup(player[i]);
      FleetPositioning(player[i]);
  }

  ResolveConflicts();
  Player* winningPlayer = PlayGame();
  ProcessWinner(winningPlayer);
}

void GameInterface::PlayerSetup(Player* player) {

      // Player Enters name
    string playerName;
    cout << "Enter name: ";
    cin >> playerName;
    player->SetName(playerName);

    // Player decides if he/she would like name of ship hit reported
    char doDisplayNameOfShipHit;
    do {
      cout << "Display the Name of the ship when hit? (y/n) ";
      cin >> doDisplayNameOfShipHit;
    } while ( doDisplayNameOfShipHit != 'y' && doDisplayNameOfShipHit != 'n');

    if(doDisplayNameOfShipHit == 'y')
      player->SetShipHitNotification();
}

void GameInterface::FleetPositioning(Player* player) {

    cout << endl;
    cout << player->GetBoard()->DisplayBoard();
    cout << endl;

    map<string, Ship*> playersFleet =  player->GetFleet();
    map<string, Ship*>::iterator fleet_itr;

    for(fleet_itr=playersFleet.begin(); fleet_itr != playersFleet.end(); ++fleet_itr) {
      int result = -1;
      do {
		    string position1, position2;
		    cout << " Position Ship:  " << fleet_itr->first;
		    cout << ", Ship Size = " << fleet_itr->second->GetSize() << endl;

            cout << "from: ";  cin >> position1;
		    cout << "  to: ";  cin >> position2;
		
		    result = player->PositionFleet(fleet_itr->second, position1, position2);

            switch(result) {
              case ShipPlacement::INVALID_COORDINATES:
                cout << " Coordinates are invalid, try again" << endl;
                break;
              case ShipPlacement::SHIP_PLACEMENT_INVALID:
			  case ShipPlacement::INVALID_SHIP_PLACEMENT_SIZE:
                cout << "Spread of coordinates do not match ship length" << endl;
                break;
              case ShipPlacement::SPACE_OCCUPIED:
                cout << "A ship within your fleet already occupies that spot" << endl;
                break;
            }
      
      } while( result != ShipPlacement::SHIP_PLACEMENT_SUCCESSFULL );

      cout << endl;
      cout << player->GetBoard()->DisplayBoard();
      cout << endl;
	}
}

void GameInterface::ResolveConflicts() {
  
  // Get the board of both players
  Board* board1 = player[0]->GetBoard();
  Board* board2 = player[1]->GetBoard();
  
  // This can go either way...board2->GetConflicts(&board1)
  //   It all gets resolved...returning all the conflicted positions found
  vector<string> boardConflicts = board1->GetConflicts(board2);

  if (boardConflicts.empty()) {
	  cout << "No conflicts found...GAME ON!!!" << endl;
	  return;
  }
  
  cout << "Found conflicting Player ships in play, (player ships found occupying the same space) ";
  cout << "All conflicting ships are sunk and designated by '*' on player respective boards." << endl << endl;

  // have each player resolve their conflicts from conflicts found on the board.
  int shipsLeftForPlayer1 = player[0]->ResolveConflict(boardConflicts);
  int shipsLeftForPlayer2 = player[1]->ResolveConflict(boardConflicts);

  if(shipsLeftForPlayer1 == 0 && shipsLeftForPlayer2 != 0) {
    cout << "While resolving ship placement conflicts, " << player[0]->GetName() << ", your entire fleet is wiped out...You've lost" << endl;
    ProcessWinner(player[1]);
  }
  else if(shipsLeftForPlayer1 != 0 && shipsLeftForPlayer2 == 0) {
    cout << "While resolving ship placement conflicts, " << player[1]->GetName() << ", your entire fleet is wiped out...You've lost" << endl;
    ProcessWinner(player[0]);
  }
  else if(shipsLeftForPlayer1 == 0 && shipsLeftForPlayer2 == 0) {
    cout << "While resolving ship placement conflicts, " << player[0]->GetName() << ", your entire fleet is wiped out...You've lost" << endl;
    cout << "While resolving ship placement conflicts, " << player[1]->GetName() << ", your entire fleet is wiped out...You've lost" << endl;
    cout << "No ships left for either player." << endl;
    ProcessWinner(0);
  }
  else {
    return;
  }

  cout << "GAME OVER." << endl;
}

Player* GameInterface::PlayGame() {

  unsigned int playerIndex = 0;
  unsigned int opponentIndex = playerIndex^1;
  bool gameOver = false;
  do{
      // Display Board for Active Player
      cout << player[playerIndex]->GetBoard()->DisplayBoard();

      // Ask Player for Coordinates for Shooting Opponent
      AttackReport* attackReport;
      do {
            string coordinate;
            cout << player[playerIndex]->GetName() << " pick target coordinate to shoot: ";
            cin >> coordinate;
            
            attackReport = player[playerIndex]->Shoot(player[opponentIndex], coordinate);

            // Display results from the attack
            cout << attackReport->GetMessage() << endl;

      } while( attackReport->IsAttackComplete() == false );

      // Determine if game is over?
      if(attackReport->GetOpponentsFleetStatus() == false) {
          gameOver = true;
      }
      else { // Toggle player/opponent index to swap turns
          playerIndex ^= 1;
          opponentIndex ^= 1;
      }

  } while (gameOver == false);

  return player[playerIndex];
}

void GameInterface::ProcessWinner(Player* player) {

  if(player == 0)
    return;

  stringstream winner;
  winner << "Player " << player->GetName() << " Wins!" << endl;
  winner << "Number of shots fired: " << player->GetNumberOfShotsFired() << endl;
  winner << "Number of hits: " << player->GetNumberOfHits() << endl;
  winner << "Numberof misses: " << player->GetNumberOfMisses() << endl;

  if(player->GetNumberOfShotsFired() != 0)
    winner << "Percentage of shots that were hits: " << player->GetHitsPercentage() << "%" << endl;

  cout << winner.str();
}