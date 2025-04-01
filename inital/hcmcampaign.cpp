#include "hcmcampaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
////////////////////////////////////////////////////////////////////////

class Unit
{
protected:
    int quantity;
    int weight;
    Position pos;

public:
    Unit(int quantity, int weight, Position pos) : quantity(quantity), weight(weight), pos(pos) {}
    virtual int getAttackScore() = 0;
    virtual string str() = 0;
    virtual Type getType() = 0;
    virtual ~Unit() {}
};
class additionalFunction {
public:
    bool isPerfectSquare(int num) {
        int sqrtNum = sqrt(num);
        return (sqrtNum * sqrtNum == num);
    }

    int calculatePersonalNumber(int year, int score) {
        int sum = year + score;
        while (sum >= 10) {
            int temp = 0;
            while (sum > 0) {
                temp += sum % 10;
                sum /= 10;
            }
            sum = temp;
        }
        return sum;
    }
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
    Vehicle();
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
    Army(Unit **unitArray, int size, string name, BattleField *battleField);
  
    virtual void fight(Army *enemy, bool defense = false) = 0;
    virtual string str() const = 0
    {
        string s ="ARVN[";
        s + "name="+name+"," "LF" + "=" + to_string(LF) + "," +
        "EXP" + "=" + to_string(EXP) + "," +
        "unitList" + "=" + unitList->str() + "," +
        "battleField" + "=" + battleField->str() + "]";
    }; 
     virtual ~Army();
};
 Army::Army(Unit **unitArray, int size, string name, BattleField *battleField) : LF(0), EXP(0), name(name), battleField(battleField)
 { 
    int S = LF + EXP;
    int capacity = 8;
    for (int base: {3, 5, 8})
    {
       UnitList unitListInstance;
       if (unitListInstance.isSpecialNumber(S, base))
       {
        capacity = 12;
       };
    }
    unitList = new UnitList(capacity); 
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
    if (EXP > 500) EXP = 500;
    else if (EXP < 0) EXP = 0;

    if (LF > 1000) LF = 1000;
    else if (LF < 0) LF = 0;
 }
 };
 Army::~Army() {
    delete unitList;
}
class LiberationArmy : public Army
{
    private:
    public:
    
    LiberationArmy(Unit** unitArray , int size , string name , BattleField* battleField) : Army (unitArray,  size,  name,  battleField)
    { }
    void fight(Army* enemy , bool defense = false) override
    {
        if (defense == false)
        {
            LF*=1.5;
            EXP*=1.5;
            if (EXP > 500) EXP = 500;
          else if (EXP < 0) EXP = 0;

          if (LF > 1000) LF = 1000;
          else if (LF < 0) LF = 0;

        }
    }
    string str() const override;
};

class ARVN : Army
{

};


class UnitList
{
private:
  int capacity;  
  int countVehicle;
  int countInfantry;
  Node* head;
 
public:

    UnitList();
    UnitList(int capacity);
    ~UnitList();
    bool insert(Unit *unit);
  
    // return true if insert successfully
    bool isContain(VehicleType vehicleType);   // return true if it exists
    bool isContain(InfantryType infantryType); // return true if it exists
    string str() const;
    // TODO 
    bool isSpecialNumber(int num, int base) ;
};

UnitList:: UnitList(int capacity):capacity(capacity), countVehicle(0), countInfantry(0), head(nullptr)  {}


UnitList:: ~UnitList()
{
    Node* current = head;
    while(current)
        {   Node* temp = current;
            current = current->next;
            delete temp->data;
            delete temp;
           
        }
}
bool UnitList:: isSpecialNumber (int num, int base)
{
    while (num>0)
    {   if (num%base > 1) return false;
        num/=base;
    }
    return true;
}
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
    int getDistance(Position pos1, Position pos2)
    {   double r = sqrt(pow((pos1.getRow()-pos2.getRow()),2)+pow((pos1.getCol()-pos2.getCol),2));
        return ceil(r);
    }
};

class TerrainElement : public BattleField
{
public:
    TerrainElement();
    ~TerrainElement();
    virtual void getEffect(Army *army) = 0;
};
class Road: public TerrainElement{

public:
void getEffect(Army *army)
{}

};
class Mountain : public TerrainElement{
    public:
    void getEffect(Army *army)
    {}

};
class River : public TerrainElement{
    public:
    void getEffect(Army *army)
    {}

};
class Urban : public TerrainElement{
    public:
    void getEffect(Army *army)
    {}

};
class Fortification : public TerrainElement{
    public:
    void getEffect(Army *army)
    {}

};
class SpecialZone : public TerrainElement{
    public:
    void getEffect(Army *army)
    {}

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
    private:
    int  num_rows, num_cols;
    vector<Position *> arrayForest, arrayRiver, arrayFortification, arrayUrban, arraySpecialZone;
    Unit*  liberationUnits;
    Unit* ARVNUnits;
    int eventCode;
    public:


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