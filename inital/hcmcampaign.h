/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 2
 * Programming Fundamentals Spring 2025
 * Date: 02.02.2025
 */

// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_HCM_CAMPAIGN_H_
#define _H_HCM_CAMPAIGN_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
#define YEAR 1975
// Forward declaration
class Unit;
class UnitList;
class Army;
class TerrainElement;

class Vehicle;
class Infantry;

class LiberationArmy;
class ARVN;

class Position;

class Road;
class Mountain;
class River;
class Urban;
class Fortification;
class SpecialZone;

class BattleField;

class HCMCampaign;
class Configuration;
class additionalFunction;
enum VehicleType
{
    TRUCK,
    MORTAR,
    ANTIAIRCRAFT,
    ARMOREDCAR,
    APC,
    ARTILLERY,
    TANK
};
enum InfantryType
{
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY
};

class Army
{
protected:
    int LF, EXP;
    string name;
    UnitList *unitList;
    BattleField *battleField;

public:
    Army(Unit **unitArray, int size, string name, BattleField *battleField);
    virtual void fight(Army *enemy, bool defense = false) = 0;
    virtual string str() const = 0;
};

class Position
{
private:
    int r, c;

public:
    Position(int r = 0, int c = 0);
    Position(const string &str_pos); // Example: str_pos = "(1,15)"
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    string str() const; // Example: returns "(1,15)"
};

class Unit
{
protected:
    int quantity, weight;
    Position pos;

public:
    Unit(int quantity, int weight, Position pos)
    {
        quantity= this->quantity;
        weight = this->weight;
        pos = this->pos;
    }
    virtual ~Unit();
    virtual int getAttackScore() = 0;
    Position getCurrentPosition() const;
    virtual string str() const = 0;
};

class Vehicle  :Unit
{
    private:
    VehicleType vehicleType;
    public:
    Vehicle(int quantity, int weight, Position pos, VehicleType vehicleType)
    {
        quantity = this->quantity;
        weight = this->weight;
        pos = this->pos;
        vehicleType = this->vehicleType;
    }
   int getAttackScore()
    {
        double attackScore = vehicleType*304+(quantity*weight)/30.00;
        return (ceil(attackScore));
    }
    string str()
    {   string str = NULL;
        str += "Vehicle["
            += "quantity=" += quantity
            += ",weight=" += weight
            += ",pos=" += pos
            += ",vehicleType=" += vehicleType;
        return str;
    }
    
};
class Infantry: Unit{
private:
InfantryType infantryType;
public:
Infantry(int quantity, int weight, Position pos, InfantryType infantryType)
{
 quantity= this->quantity;
 weight = this->weight;
 pos = this->pos;
 infantryType= this->infantryType;
};
int getAttackScore()
{
    int score = infantryType*56 + quantity*weight;
    additionalFunction s;
    if (infantryType == SPECIALFORCES && s.isPerfectSquare(weight))
    {
       score+=75; 
    }
    int PersonalNumber = s.calculatePersonalNumber(YEAR , score);
    if (PersonalNumber > 7)
    {
        quantity = ceil(quantity*1.2);
    }
    else if (PersonalNumber < 3)
    {
        quantity = ceil(quantity*0.9);
    }
    score = infantryType*56 + quantity*weight;
}
};
class UnitList
{
private:
    int capacity;
    // TODO
public:
    UnitList(int capacity);
    bool insert(Unit *unit);                   // return true if insert successfully
    bool isContain(VehicleType vehicleType);   // return true if it exists
    bool isContain(InfantryType infantryType); // return true if it exists
    string str() const;
    // TODO
};

class TerrainElement
{
public:
    TerrainElement();
    ~TerrainElement();
    virtual void getEffect(Army *army) = 0;
};

class BattleField
{
private:
    int n_rows, n_cols;
    // TODO
public:
    BattleField(int n_rows, int n_cols, vector<Position *> arrayForest,
                vector<Position *> arrayRiver, vector<Position *> arrayFortification,
                vector<Position *> arrayUrban, vector<Position *> arraySpecialZone);
    ~BattleField();
};

class HCMCampaign
{
private:
    Configuration *config;
    BattleField *battleField;
    LiberationArmy *liberationArmy;
    ARVN *ARVN;

public:
    HCMCampaign(const string &config_file_path);
    void run();
    string printResult();
};

class additionalFunction
{public:
 bool isPerfectSquare(int a)
    {   
        double x = sqrt(a);
        if (ceil(x)==floor(x))
        {
            return 1;
        }
        return 0;
    }
int breakNum(int a)
{   int temp = 0;
    while (a)
    {
    temp += a%10;
    a/=10;
    }
    return temp;
}
int calculatePersonalNumber(int a, int b)
{   int temp1 = breakNum(a);
    int temp2 = breakNum(b);
    int temp = temp1 + temp2;
    while (temp>9)
    {
        breakNum(temp);
    }
    return temp;
}

};
#endif