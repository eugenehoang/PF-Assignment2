#include "hcmcampaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
////////////////////////////////////////////////////////////////////////
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
   string str() {
      return "Infantry[infantryType=" + to_string(infantryType) +
      ", quantity= " + to_string(quantity) +
      ", weight=" + to_string(weight) +
      ", pos=" + to_string(pos) + "]";
     
  };
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

class LiberationArmy : Army
{
    private:
    public:
    LiberationArmy(const Unit** unitArray , int size , string name , BattleField* battleField);
    void fight(Army* enemy , bool defense = false)
    {
        if (defense == 0)
        {
            LF*=1.5;
            EXP*=1.5;

        }
    }

};

class ARVN : ArmyArmy
{

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
class Configuration
{


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

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////