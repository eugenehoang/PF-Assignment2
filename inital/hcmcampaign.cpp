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
    virtual Type getType() const;
};


class Vehicle : public Unit
{
    private:
    VehicleType vehicleType;
    public:
    string getVehicleType(){
        string arr[7] = 
            {"TRUCK",
            "MORTAR",
            "ANTIAIRCRAFT",
            "ARMOREDCAR",
            "APC",
            "ARTILLERY",
            "TANK"};
            return arr[vehicleType];
    }
    Vehicle(int quantity, int weight, Position pos, VehicleType vehicleType) : Unit(quantity, weight,pos)
    {
        this->vehicleType = vehicleType;
    }

   int getAttackScore()
    {
        double attackScore = vehicleType*304+(quantity*weight)/30.00;
        return (ceil(attackScore));
    }
    string str()
    {   string str = NULL;
        str + "Vehicle["
            + "quantity=" + to_string(quantity)
            + ",weight=" + to_string(weight)
            + ",pos=" + pos.str()
            + ",vehicleType=" + getVehicleType();
        return str;
    }
    Type getType()
    {
        return VEHICLE;
    }
};

class Infantry: public Unit{
  private:
  InfantryType infantryType;
  public:
  string getinfantryType()
  {
    string array[6] = {
        "SNIPER",
        "ANTIAIRCRAFTSQUAD",
        "MORTARSQUAD",
        "ENGINEER",
        "SPECIALFORCES",
        "REGULARINFANTRY"
    };
  }
  Infantry(int quantity, int weight, Position pos, InfantryType infantryType) : Unit(quantity, weight, pos)
  {
   infantryType= this->infantryType;
  };
 //Infantry(int quantity, int weight, Position pos, InfantryType infantryType) : Unit (quantity,weight, pos), infantryType(infantryType){

 
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
      return "Infantry[infantryType=" + getinfantryType() +
      ", quantity= " + to_string(quantity) +
      ", weight=" + to_string(weight) +
      ", pos=" + pos.str() + "]";
     
  };
  Type getType()
  {
    return INFANTRY;
  }
};  

class Army
{
protected:
    int LF, EXP;
    string name;
    UnitList *unitList;
    BattleField *battleField;

public:
    Army(Unit **unitArray, int size, string name, BattleField *battleField)
    {   LF = 0;
        EXP = 0;
       this->name = name;
       this->battleField = battleField; 
       for (int i=0; i<size; i++)
       {
       if ((*(unitArray))->getType() == INFANTRY )
       {
            EXP += (*(unitArray))->getAttackScore();
       }
       else if((*(unitArray))->getType() == VEHICLE)
       {
            LF +=  (*(unitArray))->getAttackScore();
       }
    }
    };
    virtual void fight(Army *enemy, bool defense = false) = 0
    {

    };
    virtual string str() const = 0
    {
        string s ="ARVN[";
        s + "name="+name+"," "LF" + "=" + to_string(LF) + "," +
        "EXP" + "=" + to_string(EXP) + "," +
        "unitList" + "=" + unitList->str() + "," +
        "battleField" + "=" + battleField->str() + "]";
    };
};

class LiberationArmy : Army
{
    private:
    public:
    
    LiberationArmy(const Unit** unitArray , int size , string name , BattleField* battleField)
    {
        
    }
    void fight(Army* enemy , bool defense = false)
    {
        if (defense == 0)
        {
            LF*=1.5;
            EXP*=1.5;

        }
    }

};

class ARVN : Army
{

};


class UnitList : public Vehicle, Infantry
{
private:

    
    int capacity;  
public:

    UnitList(int capacity): capacity(capacity)
    {};
    bool insert(Unit *unit)
    {


    }
    
    // return true if insert successfully
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
    Position(int r = 0, int c = 0)
    {
        this->r = r;
        this->c = c;
    }
    Position(const string &str_pos)
    {
        char ignore;
        std::stringstream ss(str_pos);
        ss >> ignore >> r >> ignore >> c >> ignore; // Parse format "(r,c)"
    }; // Example: str_pos = "(1,15)"
    int getRow() const
    {
        return r;
    }
    int getCol() const
    {
        return c;
    }
    void setRow(int r)
    {
        this->r = r;
    }
    void setCol(int c)
    {
        this->c=c;
    }
    string str() const
    {
        return "(" + to_string(r) + "," + to_string(c) + ")";
    }; // Example: returns "(1,15)"
};

class TerrainElement
{
public:
    TerrainElement();
    ~TerrainElement();
    virtual void getEffect(Army *army) = 0;
};
class Road;
class Mountain;
class River;
class Urban;
class Fortification;
class SpecialZone;
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