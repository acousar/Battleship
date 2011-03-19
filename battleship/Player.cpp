#include <sstream>
#include "Player.h"

int Player::PositionFleet(Ship* ship, string position1, string position2) {
  return board.PlaceShip(ship, position1, position2);
}

AttackReport* Player::Shoot(Player* opponent, string target)
{
  AttackReport* attackReport = new AttackReport();

  // Test the player object is NOT shooting itself
	if (opponent == this) {
    attackReport->SetMessage("IMPROPER TARGET");
    attackReport->SetResult(INVALID_TARGET);
    return attackReport;
	}

	// Determine target coordinate is valid
	if( board.AreCoordinatesValid(target) == false) {
    attackReport->SetMessage("Invalid Coordinates, Please Try Again.");
    attackReport->SetResult(INVALID_TARGET_COORDINATE);
    return attackReport;
	}
	
	// Check that target coordinate is NOT own ship
	if(IsTargetInFleet(target) == true){
    attackReport->SetMessage("Don't shoot your own ship, Please Try Again.");
    attackReport->SetResult(INVALID_TARGET);
    return attackReport;
	}

  // Opponent (player shot at) should Process the Attack.
  //  Processing the attack should return an object containing:
  //    1) Result of the shot (HIT, MISS, or SUNK)
  //    2) Name of the ship, if it was HIT or SUNK
  //    3) coordinate for part of ship hit or all coordinates of ship if sunk
  DamageReport damageReport = opponent->ProcessAttack(target);
  string damageResult = damageReport.GetAttackResult();

  UpdateBoard(damageReport.GetShipCoordinates(), damageResult);

  numberOfShotsFired++;

  if (damageResult == "MISS") {
    attackReport->SetMessage("MISS");
    attackReport->SetResult(MISS);
    numberOfMisses++;
  } else { // otherwise it was a hit and we need to increment the times hit
    numberOfHits++;
  }

  string shipHit = (doShipHitNotification == false) ? "Ship" : damageReport.GetShipType();

  stringstream message;
  message << this->name << " " \
	   << damageResult << " " \
	   << opponent->GetName() << "'s " << shipHit
	   << endl;
  attackReport->SetMessage(message.str());

  if (damageResult == "HIT")
    attackReport->SetResult(HIT);
  else
    attackReport->SetResult(SUNK);

  attackReport->IsAttackComplete(true);

  bool isOpponentsFleetSunk = damageReport.GetFleetStatus();
  if(isOpponentsFleetSunk == true) {
    attackReport->SetOpponentsFleetStatus(!isOpponentsFleetSunk);
  }

  return attackReport;
}

DamageReport Player::ProcessAttack(string target)
{
  DamageReport damageReport = fleet.ProcessAttack(target);

  UpdateBoard(damageReport.GetShipCoordinates(), damageReport.GetAttackResult());

  return damageReport;
}

bool Player::IsTargetInFleet(string targetCoordinate)
{
	bool isTargetInFleet = true;
	Ship* shipFound = fleet.GetShipInPosition(targetCoordinate);
	
	if(shipFound == 0)
		isTargetInFleet = false;
	
	return isTargetInFleet;
}

int Player::ResolveConflict(vector<string> gridconflicts)
{
	// In the process of resolving the conflicted ship positions the player MUST not only accept
	// the sinking of their ship, but must also update his board....
	map<string, char> conflictedShipPositions = fleet.ResolveConflicts(gridconflicts);

	// conflictedShipPositions returns the position all ships were in that were conflicted.
	if(conflictedShipPositions.size() > 0)
		UpdateBoard(conflictedShipPositions, "SUNK");

	return fleet.GetShips().size();
}

void Player::UpdateBoard(map<string, char> damageCoordinates, string shotResult)
{
	map<string, char>::iterator iter;
		for(iter=damageCoordinates.begin(); iter!=damageCoordinates.end(); ++iter)
			board.MarkBoard(iter->first, shotResult);
}
