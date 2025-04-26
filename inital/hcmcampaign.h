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

class TerrainElement 
 {
 public:
     TerrainElement()
     { };
     ~TerrainElement()
     {};
     virtual void getEffect(Army *army) = 0;
 };
 class Road: public TerrainElement{
 
 public:
 void getEffect(Army *army) override
 {}
 
 };
 class Mountain : public TerrainElement{
     public:
     void getEffect(Army *army) override
     {}
 
 };
 class River : public TerrainElement{
     public:
     River()
     {
     }
     ~River(){};
     void getEffect(Army *army) override
     {}
 
 };
 class Urban : public TerrainElement{
     public:
     void getEffect(Army *army) override
     {}
 
 };
 class Fortification : public TerrainElement{
     public:
     void getEffect(Army *army) override
     {}
 
 };
 class SpecialZone : public TerrainElement{
     public:
     void getEffect(Army *army) override
     {}
 
 };
 
 

class BattleField;
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
        {   double r = sqrt(pow((pos1.getRow()-pos2.getRow()),2)+pow((pos1.getCol()-pos2.getCol()),2));
            return ceil(r);
        }
        ~Position()
        {}
};

class BattleField
 {
 private:
     int n_rows, n_cols;
     TerrainElement*** terrain;
 public:
    
     BattleField(int n_rows, int n_cols, vector<Position*> arrayForest,
                 vector<Position *> arrayRiver, vector<Position *> arrayFortification,
                 vector<Position *> arrayUrban, vector<Position *> arraySpecialZone) :n_rows(n_rows), n_cols(n_cols){
                   
                  terrain  = new TerrainElement**[n_cols];
                  for (int i = 0; i < n_cols; i++)
                  {
                     terrain[i] = new TerrainElement*[n_rows];
                     for (int j = 0; j < n_rows; j++)
                     {
                         terrain[i][j] = nullptr;
                     }
                  }
                  for (Position* &i: arrayRiver)
                  {
                    terrain[i->getCol()][i->getRow()] = new River;
                  }
 
                 }
     ~BattleField(){
        if (terrain != nullptr)
        {
        for (int i = 0; i < n_cols; i++)
        {
           if (terrain[i] != nullptr)
           {
           for (int j = 0; j < n_rows; j++)
           {   if (terrain[i][j] != nullptr)
               delete terrain[i][j]; 
           }
           }
           delete terrain[i];
        }
     }
        delete[] terrain;
     };
     string str() {
        return "";
     }
 };
 
 
class HCMCampaign;
class Configuration;


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

class Unit
{
protected:
    int quantity;
    int weight;
    Position pos;

public:
    Unit(int quantity, int weight, Position pos) : quantity(quantity), weight(weight), pos(pos) {}
   
    virtual int getAttackScore()  = 0;
    virtual string str() = 0;
    virtual string getType()  = 0;
    virtual string getName() = 0;
    virtual int getEnum() = 0;
    void setquantity(int quantity)
    {
        this->quantity = quantity;
    }
    int getquantity()
    {return quantity;}
    virtual ~Unit() {}

};
class Node 
 {  public:
    Unit* data;
    Node* next;
    Node(){next = nullptr;}
    Node(Unit* unit) : data(unit), next(nullptr){}
    ~Node()
    {delete data;
    }
  
 };

 class Vehicle : public Unit
 {
     private:
     VehicleType vehicleType;
     public:
     string getName() override{
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
     int getEnum() override{
       return vehicleType;
    }
     Vehicle(int quantity, int weight, Position pos, VehicleType vehicleType) :  Unit(quantity, weight,pos), vehicleType(vehicleType)
     {
     }
 
    int getAttackScore() override
     {
         double attackScore = vehicleType*304+(quantity*weight)/30.00;
         return (ceil(attackScore));
     }
     string str() override
     // vehicleType, quantity, weight, pos 
     {   string str = "Vehicle[vehicleType=" +  getName()
            +  ",quantity=" + to_string(quantity)
            +  ",weight=" + to_string(weight)
            + ",position=" + pos.str() + "]";
                 
        //  str +="quantity=" + to_string(quantity)
        //      + 
        //      + 
        //      + ",vehicleType=" + getName() 
         return str;
     }
     string getType() override
     {
         return "VEHICLE";
     }
     
 };
 
 class Infantry: public Unit{
   private:
   InfantryType infantryType;
   public:
   string getName() override
   {
     string array[6] = {
         "SNIPER",
         "ANTIAIRCRAFTSQUAD",
         "MORTARSQUAD",
         "ENGINEER",
         "SPECIALFORCES",
         "REGULARINFANTRY"
     };
     return array[infantryType];
   }
   int getEnum() override{
    return infantryType;
 }
   Infantry(int quantity, int weight, Position pos, InfantryType infantryType) : Unit(quantity, weight, pos), infantryType(infantryType)
   {
    
   };
  
   int getAttackScore() override
   {
       int score = infantryType*56 + quantity*weight;
       
       if (infantryType == SPECIALFORCES && isPerfectSquare(weight))
       {
          score+=75; 
       }
       int PersonalNumber = calculatePersonalNumber(YEAR , score);
       if (PersonalNumber > 7)
       {
           quantity = ceil(quantity*1.2);
       }
       else if (PersonalNumber < 3)
       {
           quantity = ceil(quantity*0.9);
       }
       score = infantryType*56 + quantity*weight;
       return score;
   }
    string str() override {
       string s = "Infantry[infantryType=" + getName() +
       ",quantity=" + to_string(quantity) +
       ",weight=" + to_string(weight) +
       ",position=" + pos.str() + "]";
       return s;
      
   };
   string getType() override
   {
     return "INFANTRY";
   }
   bool isPerfectSquare(int a)
    {   
        int x = sqrt(a);
        return x*x == a;
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
      temp =  breakNum(temp);
    }
    return temp;
   }
 };  
 
 class UnitList
{
private:
  int capacity ;
  int countVehicle;
  int countInfantry;  
  Node* head;
 
public:

    UnitList() :capacity(0), head(nullptr){ }
    ~UnitList()
    {
    Node* current = head;
    while(current)
        {   Node* temp = current;
            current = current->next;
            delete temp->data;
            delete temp;
        }
        delete head;
       }
       

    void deleteUnit(Node* node)
    {    if (head == nullptr || node == nullptr) {
        return;
    }
        if (node == head)
        {
            head = head->next;
            delete node;

        }
        Node* temp = head;
        while (temp->next != nullptr && temp->next != node)
        {
            temp = temp->next;
        }
        if (temp->next == node) {
        temp->next = node->next;
        delete node;
        }
    }
    bool insert(Unit *unit)
    {  
        Node* temp = new Node(unit);
        Node* temp1 = head;
        while(temp1 != nullptr)
        {   
            if (temp1->data->getName()==unit->getName())
            {   temp1->data->setquantity(unit->getquantity());
                delete temp;
                return true;
            }
            temp1 = temp1->next;
        }
        if (unit->getType() == "VEHICLE")
        {
            // cuối danh sách
            if (head == nullptr)
            {
                head = temp;
            }
            else {
                Node* tails = head;
            while (tails->next != nullptr)
            {
                tails = tails->next;
            }
            tails->next = temp;
            
        }
        countVehicle++;
        return true; 
        }
        else if (unit->getType() == "INFANTRY")
        {
            //đầu danh sách
           
            temp->next = head;
            head = temp;
            countInfantry++;
            return true;
        }
        else 
        {
        delete temp;
        return false;
        }
    }
  
    // return true if insert successfully
    bool isContain(VehicleType vehicleType){
        Node* temp =  head;
        while (temp)
        {       if (temp->data->getEnum() == vehicleType && temp->data->getType()== "VEHICLE")
            {delete temp;
             return true;}
                temp = temp->next;
        }
        delete temp;
        return false;
    }   // return true if it exists
    bool isContain(InfantryType infantryType)
    {
        Node* temp = head;
        while (temp)
        {       if (temp->data->getEnum() == infantryType && temp->data->getType()== "INFANTRY")
            {delete temp;
             return true;}
                temp = temp->next;
        }
        delete temp;
        return false;
    } // return true if it exists
    string str() const{
        string s = "count_vehicle=" + to_string(countVehicle) + ";"
        + "count_infantry=" +to_string(countInfantry) + ";";
        Node* temp = head;
        while (temp != nullptr)
        {
            s += temp->data->str();
            if (temp->next != nullptr)
            s += ",";
        }
        return s;
      
    }
    // TODO 
    bool isSpecialNumber(int num, int base)
    {
        while (num>0)
        {   if (num%base > 1) return false;
            num/=base;
        }
        return true;
    }
    Node* gethead()
    {
        return head;
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
     Army( Unit **unitArray, int size, string name, BattleField *battleField) : LF(0), EXP(0), name(name), battleField(battleField)
  { 
    for (int i=0; i<size; i++) unitList->insert(*unitArray+i);
     calculateArmyScore();
  };
 
 
     virtual void fight(Army *enemy, bool defense = false) = 0;
     
     virtual string str() const = 0; 
      virtual ~Army() {
        
     }
      int getLF()
      {
         return LF;
      }
      int getEXP()
     {
         return EXP;
     }
     UnitList* getUnitList() const
     {
        return unitList;
     }
     void scaleIndices()
 {
     if (EXP > 500) EXP = 500;
     else if (EXP < 0) EXP = 0;
 
     if (LF > 1000) LF = 1000;
     else if (LF < 0) LF = 0;
 }
    void calculateArmyScore()
    {   LF = 0;
        EXP = 0;
        Node* temp = unitList->gethead();
        for (; temp->next; temp=temp->next )
        {
        if (temp->data->getType() == "INFANTRY" )
        {   
             EXP += temp->data->getAttackScore();
        }
        else if(temp->data->getType()  == "VEHICLE")
        {
             LF +=temp->data->getAttackScore();        }
       
    }    
    scaleIndices();
    
    }
 };
 class Combination
 {  vector<Unit*> unit;
    vector<bool> used;
    vector<Unit*> current;
    int n;
    int min = INT_MAX;
    int score;
    int CombinationgetScore(vector<Unit*>& cur)
    {   int score = 0;
        for (Unit* temp: cur)
        {
           score += temp->getAttackScore();
        }
        return score;
    }
    
    void findCombination(int condition) // aka backtrack
    {
        if (current.size() == n )
        {
            return;
        }
        for (int i = 0; i < n; i++)
        {
            if (!used[i])
            {
                used[i] = true;
                current.push_back(unit[i]);
                if (CombinationgetScore(current) > condition && CombinationgetScore(result) < min)
                {   
                    result = current;
                    min = CombinationgetScore(result);
                }
                findCombination(condition);
                
                current.pop_back();
                used[i]= false;
            }
        }
     score = CombinationgetScore(result);
    }
    public:
    vector<Unit*> result;
    Combination(vector<Unit*> unit, int condition) : unit(unit), used(unit.size(), false){
       findCombination(condition);
       } 
    int getScore()
    {
        return score;
    }

 };
  class LiberationArmy : public Army
 {
     private:
     
     public:
     
     LiberationArmy( Unit** unitArray , int size , string name , BattleField* battleField) : Army (unitArray,  size,  name,  battleField)
     { cout << "naevis, calling ae";}
     int findNearestLargerFibo(int num)
     {int f0 = 0;
      int f1 = 1;
      int fn = 1;
      while (fn<num)
      { fn = f0+f1;
        f0 = f1;
        f1 = fn;
      }
      return fn;
    }
    void notWinning()
    {
        Node* current = unitList->gethead();
         while (current)
            {   
                double quantity = current->data->getquantity();
                quantity *= 0.9;
                current->data->setquantity(int(ceil(quantity)));
                current = current->next;
            }
        
    }
  
    
     void fight(Army* enemy , bool defense = false) override
     {
         if (defense == false)
         {
             LF=ceil((double)LF*1.5);
             EXP=ceil((double)EXP*1.5);
             scaleIndices();

            vector<Unit*> Infantry;
            Node* head = unitList->gethead();
            while (head != nullptr)
            {
                    if (head->data->getType() == "INFANTRY")
                    {
                        Infantry.push_back(head->data);
                    }
                  head = head->next;  
            }
            Combination A = Combination(Infantry, enemy->getEXP());

            head = unitList->gethead();
            vector<Unit*> Vehicle;
            while (head != nullptr)
            {
                if (head->data->getType() == "VEHICLE")
                {
                        Vehicle.push_back(head->data);
                }
                head = head->next;
            }

            Combination B = Combination(Infantry, enemy->getLF());
            int compareCombatIndices = 0;
            if (A.result.size() > 0) compareCombatIndices++;
            if (B.result.size() > 0) compareCombatIndices++;
            // If both combinations A and B are found,
            if (compareCombatIndices == 2){ 

                removeCombinationfrom(A.result);
                removeCombinationfrom(B.result);
                confiscated(enemy);
                calculateArmyScore();
                scaleIndices();

            // for (Unit* i :A.result)
            // {   Node* head = unitList->gethead();
            //     while (head != nullptr)
            //     {
            //         if (head->data->getName() == i->getName()
            //             && head->data->getquantity() == i->getquantity()
            //             && head->data->getType() == i->getType()
            //             )
            //             {
            //                 unitList->deleteUnit(head);
            //             }
            //     }
            // }
        //    for (Unit* i :B.result)
        //     {   Node* head = unitList->gethead();
        //         while (head != nullptr)
        //         {
        //             if (head->data->getName() == i->getName()
        //                 && head->data->getquantity() == i->getquantity()
        //                 && head->data->getType() == i->getType()
        //                 )
        //                 {
        //                     unitList->deleteUnit(head);
        //                 }
        //         }
        //     }
           }
           // If only one of the two combinations meets the criteria
           else if (compareCombatIndices == 1)
              //
                {

                    if (A.result.size() > 0) //A:
                    {
                      if (LF > enemy->getLF())
                      {

                        removeCombinationfrom(A.result);
                        removeCombinationfrom(Vehicle);
                        confiscated(enemy);
                        calculateArmyScore();
                        scaleIndices();
                      }
                      else {
                        // -10%
                        notWinning();
                        // recalculate
                        calculateArmyScore();
                        scaleIndices();
                        return;
                      }
                    }
                    else if (B.result.size() > 0)
                    {
                        if (EXP > enemy->getEXP())
                        {
                            removeCombinationfrom(B.result);
                            removeCombinationfrom(Infantry);
                            confiscated(enemy);
                            calculateArmyScore();
                            scaleIndices();
                        }
                        else
                        {
                             notWinning();
                             calculateArmyScore();
                             scaleIndices();
                        // recalculate
                        return;
                        }
                    }
                    
                }
              //
           //
           else if (compareCombatIndices == 0)
           {
               // -10%
               notWinning();
               calculateArmyScore();
               scaleIndices();
               //
           }

         }
         if (defense == true)
         {
            LF=ceil((double)LF*1.3);
            EXP=ceil((double)EXP*1.3);
            scaleIndices();
         
           int compareCombatIndices =0;
           if (LF > enemy->getLF()) compareCombatIndices++;
           if (EXP > enemy->getEXP())
           compareCombatIndices++;
         switch (compareCombatIndices){
         case 0: // boost fibo
         {
            Node* temp =  unitList->gethead();
            while (temp!=nullptr)
            {
              temp->data->setquantity(findNearestLargerFibo(temp->data->getquantity()));
              temp=temp->next;
            }
            break;
         }
         case 1: // win, -10% quantity
         {
           notWinning();
            break;
         }
         case 2: //win, do nothing
         {
                
         }
     }
     calculateArmyScore();
     scaleIndices();
     }
    }

    void confiscated (Army* enemy)
    {   Node* head = enemy->getUnitList()->gethead();
        while (head)
        {   unitList->insert(head->data);
            head = head->next;
        }
    }

     string str() const override
     {
         string s ="LiberationArmy[";
         s += "name="+name+"," "LF" + "=" + to_string(LF) + "," +
         "EXP" + "=" + to_string(EXP) + "," +
         "unitList" + "=" + unitList->str() + "," +
         "battleField" + "=" + battleField->str() + "]";
         return s;
     }
     void removeCombinationfrom(vector<Unit*> com)
     {
        for (Unit* i :com)
        {   Node* head = unitList->gethead();
            while (head != nullptr)
            {
                if (head->data->getName() == i->getName()
                    && head->data->getquantity() == i->getquantity()
                    && head->data->getType() == i->getType()
                    )
                    {
                        unitList->deleteUnit(head);
                    }
            }
        }
     }
 };
 class ARVN :public Army
 {
 private:
 public:
 ARVN( Unit** unitArray, int size, string name , BattleField* battleField) :Army(unitArray, size, name, battleField){
    cout << "ningning, calling ae";
 }
 
 void fight(Army* enemy , bool defense = false)
 {
 if (defense == false)
 {
     // quantity (quantity) of each military unit by 20%
     Node* temp = unitList->gethead();
     while (temp)
     {
        temp->data->setquantity(ceil(0.80*(double)temp->data->getquantity()));
        temp = temp->next;
     }
     //  indices should be update
     calculateArmyScore();
     // quantity (quantity) of 1, remove
        temp = unitList->gethead();
        while (temp)
        {   if(temp->data->getquantity() == 1)
            {
                Node* temp2 = temp;
                temp = temp->next;
                unitList->deleteUnit(temp2);
                
            }
            else
            {temp= temp->next;}
        }
     //  update the indices
     calculateArmyScore();
 
 }
 else if(defense == true)
 {
   // confiscate and repurpose ARVN’s military units  meaning these units should be removed from the ARVN
    // remaining military units will suffer a 20% reduction in weight (weight).
    // If no battle occurs, the ARVN forces remain intact.
 
 }
 
 
 }
 
 string str() const override {
     string s ="ARVN[";
     s += "name="+name+"," "LF" + "=" + to_string(LF) + "," +
     "EXP" + "=" + to_string(EXP) + "," +
     "unitList" + "=" + unitList->str() + "," +
     "battleField" + "=" + battleField->str() + "]";
     return s;
 }
 };
 
 
 
 
class Configuration
{ 
    private:
    int  num_rows, num_cols;
    vector<Position *> arrayForest, arrayRiver, arrayFortification, arrayUrban, arraySpecialZone;
    Unit**  liberationUnits;
    Unit** ARVNUnits;
    int eventCode;
    int sizeLib;
    int sizeARVN;
    public:
    Configuration(const string & filepath)
    {
        fstream file(filepath, ios::in);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                if (line.find("NUM_") != string::npos)
                {
                    if (line.find("COLS=") != string::npos)
                    {num_cols = stoi(line.substr(9));}
                    else if (line.find("ROWS=") != string::npos)
                    {num_rows = stoi(line.substr(9));}
                }
                else if (line.find("ARRAY_") != string::npos)
                {
                    if (line.find("FOREST=") != string::npos)
                    {
                        parsePositionA( line, arrayForest);
                    }
                    else if (line.find("RIVER=") != string::npos)
                    {
                        parsePositionA( line, arrayRiver);
                    }
                    else if (line.find("FORTIFICATION=") != string::npos)
                    {
                        parsePositionA( line, arrayFortification);
                    }
                    else if (line.find("URBAN=") != string::npos)
                    {
                        parsePositionA( line, arrayUrban);

                    }
                    else if (line.find("SPECIAL_ZONE=") != string::npos)
                    {
                        parsePositionA(line, arraySpecialZone);
                    }
                }
                else if (line.find("UNIT_LIST") != string::npos)
                {
                    parseArmyInfo(line);
                }
                else if (line.find("EVENT_CODE") != string::npos)
                {eventCode = stoi(line.substr(11));
                    if (eventCode<0) eventCode = 0;
                    eventCode%=100;
                }
            }
    
        }
    }
    void parsePositionA(string line, vector<Position*> &x)
    {   size_t ini = 0;
        size_t end = 0;
        while ((ini = line.find('(', end)) != string::npos)
        {
       ini = line.find('(', end);
       end = line.find(')', ini);
       string sub = line.substr(ini,end-ini+1);
       Position *s = new Position(sub);
       x.push_back(s);
    }
    }
    void parseArmyInfo(string line)
    {
        size_t begin = line.find('[');
        size_t end = line.find(']');
        string text = line.substr(begin + 1, end - begin - 1);
        vector<string> unittext;
        int flag = 0;
        stringstream ss;
        for (char i: text)
        {   ss << i;
            if (i == '(') flag++;
            if (i == ')') flag--;
            if (flag == 0 && i == ')' )
            {
                
                unittext.push_back(ss.str());
                ss.str("");
                ss.clear();
            }
         
        }
       
       
        sizeLib = 0;
        sizeARVN = 0;
        for (const string& i:unittext)
        {
            if (i[i.size()-2] == '0') sizeLib++;
            else if ((i[i.size()-2] == '1')) sizeARVN++;
        }
        // worked
       
        liberationUnits = new Unit*[sizeLib]();
        ARVNUnits = new Unit*[sizeARVN]();
    
        for (const string& i:unittext)
        {   string Type = extractWORD(i);
            int quantity, weight, X, Y, armybelong;
            size_t parenthesis = i.find('(');
            string data = i.substr(parenthesis+1);
            stringstream ss(data);
            
         
            char ignore;
            ss >> quantity >> ignore >> weight >> ignore >> ignore >> X >> ignore >> Y >> ignore >> ignore >> armybelong;
            Position pos = Position(X, Y);

          
            Unit* unit;
            if (isVehicle(Type))
            {
                unit = new Vehicle(quantity, weight, pos, VConvertfromString(Type));
               
              
            }
            else if (isInfantry(Type))
            {
                 unit = new Infantry(quantity, weight, pos, IConvertfromString(Type));
            }
            if (armybelong == 0)
            {
                push_up(unit, liberationUnits, sizeLib);
            }
            else if (armybelong == 1)
            {
                push_up(unit, ARVNUnits, sizeARVN);
            }
        }
      

    }
    void push_up(Unit* unit, Unit** array, int sizeofArray)
    {
        int i = 0;
        while (i<sizeofArray)
        {
            if (array[i]== nullptr)
            {
                array[i] = unit;
                return;
            }
            i++;
        }
        array[i] = unit;
    }
    string extractWORD(string str)
    {   string s = "";
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
            {
                s+=str[i];
            }
        }
        return s;
    }
    VehicleType VConvertfromString(string str)
    {
        if (str == "TRUCK") return TRUCK;
        else if (str == "MORTAR") return MORTAR;
        else if (str == "ANTIAIRCRAFT") return ANTIAIRCRAFT;
        else if (str == "ARMOREDCAR") return ARMOREDCAR;
        else if (str == "APC") return APC;
        else if (str == "ARTILLERY") return ARTILLERY;
        else  return TANK;
       
    }
    InfantryType IConvertfromString(string str)
    { if (str == "SNIPER") return SNIPER;
        else if (str == "ANTIAIRCRAFTSQUAD") return ANTIAIRCRAFTSQUAD;
        else if (str == "MORTARSQUAD") return MORTARSQUAD;
        else if (str == "ENGINEER") return ENGINEER;
        else if (str == "SPECIALFORCES") return SPECIALFORCES;
        else return REGULARINFANTRY;}

    bool isVehicle(string str)
    {
            string arr[7] = 
                {"TRUCK",
                "MORTAR",
                "ANTIAIRCRAFT",
                "ARMOREDCAR",
                "APC",
                "ARTILLERY",
                "TANK"};
            for (int i = 0; i < 7; i++)
            if (str == arr[i]) return 1;
                return 0;
    
    }
    bool isInfantry(string str)
    {
        string arr[6] = {
            "SNIPER",
            "ANTIAIRCRAFTSQUAD",
            "MORTARSQUAD",
            "ENGINEER",
            "SPECIALFORCES",
            "REGULARINFANTRY"
        };
          
            for (int i = 0; i < 6; i++)
            if (str == arr[i]) return 1;
                return 0;
    
    }
    ~Configuration(){
        releaseArr(arrayForest);
        releaseArr(arrayRiver);
        releaseArr(arrayUrban);
        releaseArr(arraySpecialZone);
        for (int i = 0; i < sizeLib; i++)
        {    
             delete liberationUnits[i];
        }
        for (int i = 0; i < sizeARVN; i++)
        {   delete ARVNUnits[i];
        }
        delete[] liberationUnits;
        delete[] ARVNUnits;
    }
    void releaseArr(vector<Position*> x)
    {
        for (int i = 0; i < x.size(); i++)
        delete x[i];
    }
    string str() const{
    string s = "[num_rows=" + to_string(num_rows) + ","
    + "num_cols=" + to_string(num_cols) + ",";
   
    s += "arrayForest=[";
    for (size_t i = 0; i < arrayForest.size(); ++i) {
        s += arrayForest[i]->str();
        if (i != arrayForest.size() - 1) {
            s += ",";
        }
    }
    s += "],";

   
    s += "arrayRiver=[";
    for (size_t i = 0; i < arrayRiver.size(); ++i) {
        s+= arrayRiver[i]->str();
        if (i != arrayRiver.size() - 1) {
            s += ",";
        }
    }
    s += "],";

    s += "arrayFortification=[";
    for (size_t i = 0; i < arrayFortification.size(); ++i) {
        s += arrayFortification[i]->str();
        if (i != arrayFortification.size() - 1) {
            s += ",";
        }
    }
    s += "],";

   
    s += "arrayUrban=[";
    for (size_t i = 0; i < arrayUrban.size(); ++i) {
        s += arrayUrban[i]->str();
        if (i != arrayUrban.size() - 1) {
            s += ",";
        }
    }
    s +=  "],";

    
    s +=  "arraySpecialZone=[";
    for (size_t i = 0; i < arraySpecialZone.size(); ++i) {
        s +=  arraySpecialZone[i]->str();
        if (i != arraySpecialZone.size() - 1) {
            s +=  ",";
        }
    }
    s +=  "],";

    
    s +=  "liberationUnits=[";
    for (int i = 0;  i < sizeLib; ++i) {
        s +=  liberationUnits[i]->str();
        if (i != sizeLib - 1) {
            s +=  ",";
        }
    }
    s +=  "],";

    
    s +=  "ARVNUnits=[";
    for (int i = 0; i < sizeARVN; ++i) {
        s +=  ARVNUnits[i]->str();
        if (i != sizeARVN - 1) {
            s +=  ",";
        }
    }
    s +=  "],";

   
    s +=  "eventCode=" + to_string(eventCode);

   
    s += "]";

    return s;
}
    
};

class HCMCampaign
 {
 private:
     Configuration *config;
     BattleField *battleField;
     LiberationArmy *liberationArmy;
     ARVN *arvnArmy;
 
 public:
     HCMCampaign(const string &config_file_path) : config(nullptr), battleField(nullptr), liberationArmy(nullptr), arvnArmy(nullptr) {};
     void run(){};
     string printResult(){ return "";};
 };
   
#endif