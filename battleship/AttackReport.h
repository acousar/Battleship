#pragma once
#ifndef ATTACK_RESULT_H
#define ATTACK_RESULT_H

#include <string>

using namespace std;

enum {
  INVALID_TARGET_COORDINATE = 0,
  INVALID_TARGET = 1,
  MISS = 2,
  HIT = 3,
  SUNK = 4
};

class AttackReport {
private:
  int Result;
  string Message;
  bool isAttackComplete;
  bool doesOpponentHaveShipsLeft;

public:
  AttackReport() { isAttackComplete = false; Result = 0; Message = ""; doesOpponentHaveShipsLeft = true; }
  ~AttackReport() {}

  void SetResult(int result) { Result = result; }
  int GetResult() { return Result; }

  void SetMessage(string msg) { Message = msg; }
  string GetMessage() { return Message; }

  void IsAttackComplete(bool isComplete) { isAttackComplete = isComplete; }
  bool IsAttackComplete() { return isAttackComplete; }

  void SetOpponentsFleetStatus(bool status) { doesOpponentHaveShipsLeft = status; }
  bool GetOpponentsFleetStatus() { return doesOpponentHaveShipsLeft; }
};

#endif