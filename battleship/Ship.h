#pragma once
#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <map>

using namespace std;

class Ship  {

protected:
    map<string, char> position;
    map<string, char>::iterator map_iter;
    string name;
    char symbol;
    int size;
	string type;

public:
	//Ship() {}
	Ship(char sym, int sz, string t){ symbol = sym; size = sz; type = t; }
  virtual ~Ship() {}
  virtual char GetSymbol() = 0;
  virtual int GetSize() = 0;
  virtual string GetType() = 0;
		
  void SetName(string n){ name = n; }
	string GetName(){ return name; }

  void SetPosition(string pos) { position.insert(make_pair(pos, 'U')); }
	map<string, char> GetPosition() { return position; }
  
  string GetDamageReport(string targetCoordinate) {
      
    string Report;

    unsigned int  numberOfHits = 0;
    for(map_iter = position.begin(); map_iter != position.end(); ++map_iter)
    {
        if(map_iter->first == targetCoordinate) {
            map_iter->second = 'D';
				    Report = "HIT";
        }

        if(map_iter->second == 'D')
            numberOfHits++;
    }

    if (numberOfHits == position.size()) {
        Report = "SUNK";
    }

		return Report;
  }
	
};

#endif