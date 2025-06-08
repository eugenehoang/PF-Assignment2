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
        this->c = c;
    }
    string str() const
    {
        return "(" + to_string(r) + "," + to_string(c) + ")";
    }; // Example: returns "(1,15)"
    int getDistance(const Position &pos) const
    {
        double radius = sqrt(pow((pos.getRow() - r), 2) + pow((pos.getCol() - c), 2));
        return ceil(radius);
    }
    double getRealDistance(const Position &pos) const
    {
        return sqrt(pow((pos.getRow() - r), 2) + pow((pos.getCol() - c), 2));
    }
    ~Position()
    {
    }
};

class TerrainElement
{
protected:
    Position pos;

public:
    TerrainElement(const Position &position) : pos(position) {};
    virtual ~TerrainElement() {};
    virtual void getEffect(Army *army) = 0;
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
    int attackScore;
    bool affectedForest;
    bool affectedRiver;
    bool affectedFortification;
    bool affectedUrban;

public:
    Unit(int quantity, int weight, Position pos) : quantity(quantity), weight(weight), pos(pos), attackScore(0), affectedForest(0), affectedRiver(0), affectedFortification(0), affectedUrban(0) {}
    Unit(const Unit &other) : quantity(other.quantity), weight(other.weight), pos(other.pos), attackScore(other.attackScore), affectedForest(other.affectedForest), affectedRiver(other.affectedRiver), affectedFortification(other.affectedFortification), affectedUrban(other.affectedUrban) {}
    virtual ~Unit() {}
    virtual int getAttackScore() = 0;
    Position getCurrentPosition() const
    {
        return pos;
    }
    virtual string str() const = 0;

    virtual Unit *clone() const = 0;
    virtual string getType() const = 0;
    virtual string getName() const = 0;
    virtual int getEnum() const = 0;
    void setquantity(int quantity)
    {
        this->quantity = quantity;
    }
    void addQuantity(int num)
    {
        this->quantity += num;
    }
    int getquantity() const
    {
        return quantity;
    }
    int getweight() const
    {
        return weight;
    }
    void setweight(int num)
    {
        this->weight = num;
    }
    virtual void setAttackScore(int score) = 0;
    int getAffectedATK() const
    {
        return attackScore;
    }
    bool wasAffected(string name) const
    {
        if (name == "FOREST")
            return affectedForest;

        if (name == "RIVER")
            return affectedRiver;

        if (name == "FORT")
            return affectedFortification;

        if (name == "URBAN")
            return affectedUrban;

        return 0;
    }
    void Affect(string name)
    {
        if (name == "FOREST")
            affectedForest = true;

        if (name == "RIVER")
            affectedRiver = true;

        if (name == "FORT")
            affectedFortification = true;

        if (name == "URBAN")
            affectedUrban = true;
    }
};
class Node
{
public:
    Unit *data;
    Node *next;
    Node() { next = nullptr; }
    Node(Unit *unit) : data(unit), next(nullptr) {}
    ~Node()
    {
    }
};

class Vehicle : public Unit
{
private:
    VehicleType vehicleType;

public:
    Vehicle(int quantity, int weight, Position pos, VehicleType vehicleType) : Unit(quantity, weight, pos), vehicleType(vehicleType)
    {
    }
    Vehicle(const Vehicle &other)
        : Unit(other), vehicleType(other.vehicleType) {}
    Unit *clone() const override
    {
        return new Vehicle(*this);
    }
    string getName() const override
    {
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
    int getEnum() const override
    {
        return vehicleType;
    }

    void setAttackScore(int num) override
    {
        attackScore = num;
    }

    int getAttackScore() override
    {
        auto score = ((vehicleType * 304 + (quantity * weight))) / 30.0;
        score = ceil(score);
        attackScore = score;
        return score;
    }
    string str() const override
    // vehicleType, quantity, weight, pos
    {
        string str = "Vehicle[vehicleType=" + getName() + ",quantity=" + to_string(quantity) + ",weight=" + to_string(weight) + ",position=" + pos.str() + "]";

        return str;
    }
    string getType() const override
    {
        return "VEHICLE";
    }
};

class Infantry : public Unit
{
private:
    InfantryType infantryType;

public:
    Infantry(int quantity, int weight, Position pos, InfantryType infantryType) : Unit(quantity, weight, pos), infantryType(infantryType) {};
    Infantry(const Infantry &other)
        : Unit(other), infantryType(other.infantryType) {}
    Unit *clone() const override
    {
        return new Infantry(*this);
    }
    string getName() const override
    {
        string array[6] = {
            "SNIPER",
            "ANTIAIRCRAFTSQUAD",
            "MORTARSQUAD",
            "ENGINEER",
            "SPECIALFORCES",
            "REGULARINFANTRY"};
        return array[infantryType];
    }
    int getEnum() const override
    {
        return infantryType;
    }

    void setAttackScore(int num) override
    {
        attackScore = num;
    }
    int getAttackScore() override
    {
        int score = infantryType * 56 + quantity * weight;

        if (infantryType == SPECIALFORCES && isPerfectSquare(weight))
        {
            score += 75;
        }
        int PersonalNumber = calculatePersonalNumber(1975, score);
        if (PersonalNumber > 7)
        {
            this->quantity = ceil(quantity * 1.2);
        }
        else if (PersonalNumber < 3)
        {
            this->quantity = ceil(quantity * 0.9);
        }
        score = infantryType * 56 + quantity * weight;
        attackScore = score;
        return score;
    }
    string str() const override
    {
        string s = "Infantry[infantryType=" + getName() +
                   ",quantity=" + to_string(quantity) +
                   ",weight=" + to_string(weight) +
                   ",position=" + pos.str() + "]";
        return s;
    };
    string getType() const override
    {
        return "INFANTRY";
    }
    bool isPerfectSquare(int a)
    {
        int x = sqrt(a);
        return x * x == a;
    }
    int breakNum(int a)
    {
        int temp = 0;
        while (a)
        {
            temp += a % 10;
            a /= 10;
        }
        return temp;
    }
    int calculatePersonalNumber(int a, int b)
    {
        int temp1 = breakNum(a);
        int temp2 = breakNum(b);
        int temp = temp1 + temp2;
        while (temp > 9)
        {
            temp = breakNum(temp);
        }
        return temp;
    }
};

class UnitList
{
private:
    int capacity;
    int countVehicle;
    int countInfantry;
    Node *head;

public:
    UnitList() : capacity(8), countInfantry(0), countVehicle(0), head(0) {}
    ~UnitList()
    {
        Node *current = head;
        while (current)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }

    void reverseUnitList()
    {
        Node *current = head;
        Node *prev = nullptr;
        Node *next = nullptr;

        while (current)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
    void deleteUnit(Node *node)
    {
        if (head == nullptr || node == nullptr)
        {
            return;
        }
        if (node->data->getType() == "INFANTRY")
        {
            countInfantry--;
        }
        else if (node->data->getType() == "VEHICLE")
        {
            countVehicle--;
        }
        if (node == head)
        {
            head = head->next;
            delete node;
            return;
        }
        Node *temp = head;
        while (temp->next != nullptr && temp->next != node)
        {
            temp = temp->next;
        }
        if (temp->next == node)
        {
            temp->next = node->next;
            delete node;
        }
    }

    bool insert(Unit *unit)
    {
        if ((countInfantry + countVehicle) >= capacity)
            return false;
        if (unit == nullptr)
            return false;

        Node *temp1 = head;
        while (temp1 != nullptr)
        {
            if (temp1->data->getName() == unit->getName())
            {
                temp1->data->addQuantity((unit->getquantity()));
                temp1->data->getAttackScore();
                return true;
            }
            temp1 = temp1->next;
        }
        Node *temp = new Node(unit->clone());

        if (unit->getType() == "VEHICLE")
        {
            // cuối danh sách
            if (head == nullptr)
            {

                head = temp;
            }
            else
            {
                Node *tails = head;
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
            // đầu danh sách

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
    bool isContain(VehicleType vehicleType)
    {
        Node *temp = head;
        while (temp)
        {
            if (temp->data->getEnum() == vehicleType && temp->data->getType() == "VEHICLE")
            {
                return true;
            }
            temp = temp->next;
        }

        return false;
    } // return true if it exists
    bool isContain(InfantryType infantryType)
    {
        Node *temp = head;
        while (temp)
        {
            if (temp->data->getEnum() == infantryType && temp->data->getType() == "INFANTRY")
            {
                return true;
            }
            temp = temp->next;
        }

        return false;
    } // return true if it exists
    string str() const
    {
        string s = "UnitList[count_vehicle=" + to_string(countVehicle) + ";" + "count_infantry=" + to_string(countInfantry);

        if (countInfantry > 0 || countVehicle > 0)
            s += ";";
        Node *temp = head;
        while (temp != nullptr)
        {
            s += temp->data->str();
            if (temp->next != nullptr)
                s += ",";
            temp = temp->next;
        }
        s += "]";
        return s;
    }

    Node *gethead() const
    {
        return head;
    }
    void setCapacity(int num)
    {
        capacity = num;
    }
    int getc() const { return capacity; }
};

class Army
{
protected:
    int LF, EXP;
    string name;
    UnitList *unitList;
    BattleField *battleField;

public:
    Army(Unit **unitArray, int size, string name, BattleField *battleField) : unitList(new UnitList()), LF(0), EXP(0), name(name), battleField(battleField)
    {
        calculateArmyScore(unitArray, size);

        int S = LF + EXP;

        for (int base : {2, 3, 5, 7})
        {
            if (isSpecialNumber(S, base))
                unitList->setCapacity(12);
        }

        for (int i = 0; i < size; i++)
        {
            unitList->insert(unitArray[i]);
        }
        getAllAttackScore();
    };

    virtual void fight(Army *enemy, bool defense = false) = 0;

    virtual string str() const = 0;
    virtual ~Army()
    {
        if (unitList)
        {

            delete unitList;
            unitList = nullptr;
        }
    }
    int getLF() const
    {
        return LF;
    }
    void setLF(int LF)
    {
        this->LF = LF;
        scaleIndices();
    }
    int getEXP() const
    {
        return EXP;
    }
    void setEXP(int EXP)
    {
        this->EXP = EXP;
        scaleIndices();
    }
    UnitList *getUnitList() const
    {
        return unitList;
    }

    void scaleIndices()
    {
        if (EXP > 500)
            EXP = 500;
        else if (EXP < 0)
            EXP = 0;

        if (LF > 1000)
            LF = 1000;
        else if (LF < 0)
            LF = 0;
    }

    virtual string recognizeArmy() const = 0;
    void calculateArmyScore(UnitList *u)
    {
        LF = 0;
        EXP = 0;
        if (u == 0 || u->gethead() == 0)
        {
            return;
        }
        Node *temp = u->gethead();
        for (; temp; temp = temp->next)
        {
            if (temp->data->getType() == "INFANTRY")
            {
                EXP += temp->data->getAttackScore();
            }
            else if (temp->data->getType() == "VEHICLE")
            {
                LF += temp->data->getAttackScore();
            }
        }

        scaleIndices();
    }
    void getAllAttackScore()
    {

        if (unitList == 0 || unitList->gethead() == 0)
        {
            return;
        }
        Node *temp = unitList->gethead();
        for (; temp; temp = temp->next)
        {
            temp->data->getAffectedATK();
        }
    }

    void addLF(int more)
    {
        LF += more;
        scaleIndices();
    }
    void addEXP(int more)
    {
        EXP += more;
        scaleIndices();
    }
    void subtractLF(int less)
    {
        LF -= less;
        scaleIndices();
    }
    void subtractEXP(int less)
    {
        EXP -= less;
        scaleIndices();
    }
    void cleanupUnit()
    {
        Node *current = unitList->gethead();
        Node *prev = 0;
        while (current)
        {
            Node *next = current->next;
            if (current->data->getAffectedATK() <= 5)
            {
                unitList->deleteUnit(current);
                if (prev)
                {
                    prev->next = next;
                }
                else
                    prev = current;
            }
            current = next;
        }
        calculateArmyScore(unitList);
    }
    void calculateArmyScore(Unit **array, int size)
    {
        LF = 0;
        EXP = 0;
        if (array == 0)
        {
            return;
        }

        for (int i = 0; i < size; i++)
        {
            if (array[i]->getType() == "INFANTRY")
            {
                EXP += array[i]->getAttackScore();
            }
            else if (array[i]->getType() == "VEHICLE")
            {
                LF += array[i]->getAttackScore();
            }
        }
        scaleIndices();
    }

    bool isSpecialNumber(int num, int base)
    {
        while (num > 0)
        {
            if (num % base > 1)
                return false;
            num /= base;
        }
        return true;
    }
};
class Combination
{
public:
    vector<Unit *> result;
    ;

private:
    vector<Unit *> current;

    int threshold;
    int bestScore;
    int CombinationgetScore(vector<Unit *> cur)
    {
        int score = 0;
        for (Unit *&temp : cur)
        {
            score += temp->getAffectedATK();
        }
        return score;
    }

    void findCombination(const vector<Unit *> &initial, int index, vector<Unit *> &current, vector<Unit *> &result, int score)
    {
        int currentScore = CombinationgetScore(current);
        if (currentScore >= bestScore)
            return;

        if (!current.empty() && currentScore > threshold && currentScore < bestScore)
        {
            if (currentScore > threshold && currentScore < score)
            {
                result = current;
                bestScore = currentScore;
            }
        }
        for (int i = index; i < initial.size(); i++)
        {
            current.push_back(initial[i]);
            if (CombinationgetScore(current) <= score)
            {
                findCombination(initial, i + 1, current, result, score);
            }
            current.pop_back();
        }
    }

public:
    Combination(vector<Unit *> type, int threshold) : current({}), result({}), threshold(threshold), bestScore(INT_MAX)
    {
        findCombination(type, 0, current, result, bestScore);
    }
    ~Combination()
    {
    }
};

class Road : public TerrainElement
{

public:
    Road(const Position &pos) : TerrainElement(pos)
    {
    }
    ~Road() {};
    void getEffect(Army *army) override
    {

        // No effect

        // Done.
    }
};
class Mountain : public TerrainElement
{
public:
    Mountain(const Position &pos) : TerrainElement(pos)
    {
    }
    ~Mountain() {};
    void getEffect(Army *army) override
    {

        Node *head = army->getUnitList()->gethead();
        while (head)
        {
            if (head->data->wasAffected("FOREST") == 0)
            {
                int distance = pos.getDistance(head->data->getCurrentPosition());
                if (army->recognizeArmy() == "Li")
                {
                    if (distance <= 2)
                    {
                        if (head->data->getType() == "INFANTRY")
                        {
                            army->addEXP(ceil(0.3 * (head->data->getAffectedATK())));
                        }
                        else if (head->data->getType() == "VEHICLE")
                        {
                            army->addLF(ceil(-0.1 * head->data->getAffectedATK()));
                        }
                    }
                }
                else if (army->recognizeArmy() == "Ar")
                {
                    if (distance <= 4)
                    {
                        if (head->data->getType() == "INFANTRY")
                        {
                            army->addEXP(ceil(0.2 * (head->data->getAffectedATK())));
                        }
                        else if (head->data->getType() == "VEHICLE")
                        {
                            army->addLF(ceil(-0.05 * head->data->getAffectedATK()));
                        }
                    }
                }
                head->data->Affect("FOREST");
            }
            head = head->next;
        }
    }
};
class River : public TerrainElement
{
public:
    River(const Position &pos) : TerrainElement(pos)
    {
    }
    ~River() {};
    void getEffect(Army *army) override
    {

        Node *head = army->getUnitList()->gethead();
        while (head)
        {
            Unit *unit = head->data;
            if (unit->wasAffected("RIVER") == 0)
            {
                int distance = pos.getDistance(unit->getCurrentPosition());

                if (distance <= 2)
                {
                    unit->setAttackScore(ceil(0.9 * unit->getAffectedATK()));
                }
                unit->Affect("RIVER");
            }
            head = head->next;
        }
    }
};
class Urban : public TerrainElement
{
public:
    Urban(const Position &pos) : TerrainElement(pos) {};
    ~Urban() {};
    void getEffect(Army *army) override
    {
        Node *head = army->getUnitList()->gethead();
        while (head)
        {
            Unit *unit = head->data;

            if (unit->wasAffected("URBAN") == 0)
            {

                int distance = pos.getDistance(unit->getCurrentPosition());
                double realDistance = pos.getRealDistance(unit->getCurrentPosition());
                if (army->recognizeArmy() == "Li")
                { // Liberation Army
                    if ((unit->getType() == "SPECIALFORCES" || unit->getType() == "REGULARINFANTRY") && distance <= 5)
                    {
                        double bonus = (2 * unit->getAffectedATK()) / realDistance;
                        unit->setAttackScore(unit->getAffectedATK() + ceil(bonus));
                    }
                    else if (unit->getType() == "ARTILLERY" && distance <= 2)
                    {
                        unit->setAttackScore(ceil(0.5 * unit->getAffectedATK()));
                    }
                }
                else if (army->recognizeArmy() == "Ar")
                { // ARVN
                    if (unit->getType() == "REGULARINFANTRY" && distance <= 3)
                    {
                        double bonus = (3 * unit->getAffectedATK()) / (2 * realDistance);
                        unit->setAttackScore(unit->getAffectedATK() + ceil(bonus));
                    }
                }
                unit->Affect("URBAN");
            }
            head = head->next;
        }
    }
};
class Fortification : public TerrainElement
{
public:
    Fortification(const Position &pos) : TerrainElement(pos) {}
    ~Fortification()
    {
    }
    void getEffect(Army *army) override
    {
        Node *head = army->getUnitList()->gethead();
        while (head)
        {
            Unit *unit = head->data;
            if (unit->wasAffected("FORT") == 0)
            {
                int distance = pos.getDistance(unit->getCurrentPosition());

                if (army->recognizeArmy() == "Li" && distance <= 2)
                { // Liberation Army
                    unit->setAttackScore(ceil(0.8 * unit->getAffectedATK()));
                }
                else if (army->recognizeArmy() == "Ar" && distance <= 2)
                { // ARVN
                    unit->setAttackScore(ceil(1.2 * unit->getAffectedATK()));
                }
                unit->Affect("FORT");
            }
            head = head->next;
        }
    }
};
class SpecialZone : public TerrainElement
{
public:
    SpecialZone(const Position &pos) : TerrainElement(pos) {}
    ~SpecialZone()
    {
    }
    void getEffect(Army *army) override
    {
        Node *head = army->getUnitList()->gethead();
        while (head)
        {
            Unit *unit = head->data;
            int distance = pos.getDistance(unit->getCurrentPosition());

            if (distance <= 1)
            {
                unit->setAttackScore(0);
            }

            head = head->next;
        }
    }
};

class BattleField
{
private:
    int n_rows, n_cols;
    TerrainElement ***terrain;
    vector<TerrainElement *> arrayForest;
    vector<TerrainElement *> arrayRiver;
    vector<TerrainElement *> arrayFortification;
    vector<TerrainElement *> arrayUrban;
    vector<TerrainElement *> arraySpecialZone;

public:
    BattleField(int n_rows, int n_cols, vector<Position *> arrayForest,
                vector<Position *> arrayRiver, vector<Position *> arrayFortification,
                vector<Position *> arrayUrban, vector<Position *> arraySpecialZone) : n_rows(n_rows), n_cols(n_cols), terrain(nullptr), arrayForest{}, arrayRiver{}, arrayFortification{}, arrayUrban{}, arraySpecialZone{}
    {

        terrain = new TerrainElement **[n_rows];
        for (int i = 0; i < n_rows; i++)
        {
            terrain[i] = new TerrainElement *[n_cols];
            for (int j = 0; j < n_cols; j++)
            {
                terrain[i][j] = nullptr;
            }
        }

        for (Position *&pos : arrayForest)
        {
            int r = pos->getRow();
            int c = pos->getCol();
            terrain[r][c] = new Mountain(*pos);
            this->arrayForest.push_back(terrain[r][c]);
        }
        for (Position *&pos : arrayRiver)
        {
            int r = pos->getRow();
            int c = pos->getCol();
            terrain[r][c] = new River(*pos);
            this->arrayRiver.push_back(terrain[r][c]);
        }
        for (Position *&pos : arrayUrban)
        {
            int r = pos->getRow();
            int c = pos->getCol();
            terrain[r][c] = new Urban(*pos);
            this->arrayUrban.push_back(terrain[r][c]);
        }
        for (Position *&pos : arrayFortification)
        {
            int r = pos->getRow();
            int c = pos->getCol();
            terrain[r][c] = new Fortification(*pos);
            this->arrayFortification.push_back(terrain[r][c]);
        }
        for (Position *&pos : arraySpecialZone)
        {
            int r = pos->getRow();
            int c = pos->getCol();
            terrain[r][c] = new SpecialZone(*pos);
            this->arraySpecialZone.push_back(terrain[r][c]);
        }

        for (int i = 0; i < n_rows; i++)
        {
            for (int j = 0; j < n_cols; j++)
            {
                if (terrain[i][j] == nullptr)
                {
                    terrain[i][j] = new Road(Position(i, j));
                }
            }
        }
    }

    ~BattleField()
    {

        if (terrain != nullptr)
        {
            for (int i = 0; i < n_rows; ++i)
            {
                if (terrain[i] != nullptr)
                {
                    for (int j = 0; j < n_cols; ++j)
                        delete terrain[i][j];

                    delete[] terrain[i];
                }
            }
            delete[] terrain;
            terrain = nullptr;
        }
    }

    void applyEffect(Army *army)
    {
        if (army == nullptr)
            return;
        for (TerrainElement *element : arrayForest)
        {
            element->getEffect(army);
        }

        for (TerrainElement *element : arrayRiver)
        {
            element->getEffect(army);
        }

        for (TerrainElement *element : arrayUrban)
        {
            element->getEffect(army);
        }

        for (TerrainElement *element : arrayFortification)
        {
            element->getEffect(army);
        }

        for (TerrainElement *element : arraySpecialZone)
        {
            element->getEffect(army);
        }
    }
    string str()
    {

        return "BattleField[n_rows=" + to_string(n_rows) + ",n_cols=" + to_string(n_cols) + "]";
    }
};

class LiberationArmy : public Army
{
private:
public:
    LiberationArmy(Unit **unitArray, int size, string name, BattleField *battleField) : Army(unitArray, size, name, battleField)
    {
    }
    string recognizeArmy() const override
    {
        return "Li";
    }
    int findNearestLargerFibo(int num)
    {
        int f0 = 0;
        int f1 = 1;
        int fn = 1;
        while (fn < num)
        {
            fn = f0 + f1;
            f0 = f1;
            f1 = fn;
        }
        return fn;
    }
    void notWinning()
    {
        Node *current = unitList->gethead();
        while (current)
        {
            double quantity = current->data->getquantity();
            quantity *= 0.9;
            current->data->setquantity(int(ceil(quantity)));
            current = current->next;
        }
        calculateArmyScore(unitList);
    }

    void fight(Army *enemy, bool defense = false) override
    {
        if (defense == false)
        {
            LF = ceil((double)LF * 1.5);
            EXP = ceil((double)EXP * 1.5);
            scaleIndices();

            vector<Unit *> Infantry(0);
            vector<Unit *> Vehicle(0);
            Node *temp = unitList->gethead();
            while (temp != nullptr)
            {
                if (temp->data->getType() == "INFANTRY")
                {
                    Infantry.push_back(temp->data);
                }
                if (temp->data->getType() == "VEHICLE")
                {
                    Vehicle.push_back(temp->data);
                }
                temp = temp->next;
            }

            Combination *A = new Combination(Infantry, enemy->getEXP());
            Combination *B = new Combination(Vehicle, enemy->getLF());

            int compareCombatIndices = 0;
            if (A->result.size() > 0)
                compareCombatIndices++;
            if (B->result.size() > 0)
                compareCombatIndices++;

            // If both combinations A and B are found,

            if (compareCombatIndices == 2)
            {

                removeCombinationfrom(A->result);
                removeCombinationfrom(B->result);

                confiscated(enemy);
            }

            // If only one of the two combinations meets the criteria
            else if (compareCombatIndices == 1)
            //
            {

                if (A->result.size() > 0) // A:
                {
                    if (LF > enemy->getLF())
                    {

                        removeCombinationfrom(A->result);
                        removeCombinationfrom(Vehicle);
                        confiscated(enemy);
                    }
                    else
                    {
                        // -10%
                        notWinning();
                    }
                }
                else if (B->result.size() > 0)
                {
                    if (EXP > enemy->getEXP())
                    {
                        removeCombinationfrom(B->result);
                        removeCombinationfrom(Infantry);
                        confiscated(enemy);
                    }
                    else
                    {
                        notWinning();
                        // recalculate
                    }
                }
                delete A;
                delete B;
            }
            //
            //
            else if (compareCombatIndices == 0)
            {
                // -10%
                notWinning();
                //
            }

            calculateArmyScore(unitList);
            scaleIndices();
        }
        if (defense == true)
        {
            LF = ceil((double)LF * 1.3);
            EXP = ceil((double)EXP * 1.3);
            scaleIndices();

            int compareCombatIndices = 0;
            if (LF > enemy->getLF())
                compareCombatIndices++;
            if (EXP > enemy->getEXP())
                compareCombatIndices++;
            switch (compareCombatIndices)
            {
            case 0: // boost fibo
            {
                Node *temp = unitList->gethead();
                while (temp != nullptr)
                {
                    temp->data->setquantity(findNearestLargerFibo(temp->data->getquantity()));
                    temp = temp->next;
                }
                calculateArmyScore(unitList);
                scaleIndices();
                break;
            }
            case 1: // win, -10% quantity
            {
                notWinning();
                break;
            }
            case 2: // win, do nothing
            {
            }
            }
        }
    }

    void confiscated(Army *enemy)
    {
        enemy->getUnitList()->reverseUnitList();
        Node *node = enemy->getUnitList()->gethead();

        while (node != 0)
        {
            bool found = 0;
            for (Node *temp = unitList->gethead(); temp != 0; temp = temp->next)
            {
                if (temp->data->getName() == node->data->getName())
                {
                    int newQuantity = temp->data->getquantity() + node->data->getquantity();
                    temp->data->setquantity(newQuantity);
                    if (node->data->getweight() > temp->data->getweight())
                    {
                        temp->data->setweight(node->data->getweight());
                    }
                    found = 1;
                    break;
                }
            }
            if (!found)
                unitList->insert(node->data->clone());

            node = node->next;
        }
        node = unitList->gethead();
        while (node)
        {
            Node *temp = enemy->getUnitList()->gethead();
            while (temp)
            {
                if (temp->data->getName() == node->data->getName())
                {
                    enemy->getUnitList()->deleteUnit(temp);
                    break;
                }
                temp = temp->next;
            }
            node = node->next;
        }

        enemy->getUnitList()->reverseUnitList();
        //
        Node *head = enemy->getUnitList()->gethead();
        while (head)
        {
            head->data->setquantity(ceil(0.8 * (head->data->getquantity())));
            head = head->next;
        }
        enemy->calculateArmyScore(enemy->getUnitList());
    }

    string str() const override
    {
        string battleFieldstr = "";
        string unitListstr = "";
        if (unitList)
        {
            unitListstr = unitList->str();
        }
        if (battleField)
            battleFieldstr = battleField->str();
        string s = "LiberationArmy[LF=" + to_string(LF) + "," +
                   "EXP" + "=" + to_string(EXP) + "," +
                   "unitList" + "=" + unitListstr + "," +
                   "battleField" + "=" + battleFieldstr + "]";
        return s;
    }
    void removeCombinationfrom(vector<Unit *> com)
    {
        for (Unit *&i : com)
        {
            Node *prev = 0;
            Node *current = unitList->gethead();
            while (current != 0)
            {
                if (current->data->getName() == i->getName() && current->data->getquantity() == i->getquantity() && current->data->getType() == i->getType())
                {
                    unitList->deleteUnit(current);
                    break;
                }

                current = current->next;
            }
        }
    }
};
class ARVN : public Army
{
private:
public:
    ARVN(Unit **unitArray, int size, string name, BattleField *battleField) : Army(unitArray, size, name, battleField)
    {
    }
    string recognizeArmy() const override
    {
        return "Ar";
    }
    void fight(Army *enemy, bool defense = false)
    {
        if (defense == false)
        {
            // quantity (quantity) of each military unit by 20%
            Node *temp = unitList->gethead();
            while (temp)
            {
                temp->data->setquantity(ceil(0.80 * (double)temp->data->getquantity()));
                temp = temp->next;
            }
            //  indices should be update
            calculateArmyScore(this->unitList);
            // quantity (quantity) of 1, remove
            temp = unitList->gethead();
            while (temp)
            {
                if (temp->data->getquantity() == 1)
                {
                    Node *temp2 = temp;
                    temp = temp->next;
                    unitList->deleteUnit(temp2);
                }
                else
                {
                    temp = temp->next;
                }
            }
            //  update the indices
            calculateArmyScore(unitList);
        }
        else if (defense == true)
        {
            // confiscate and repurpose ARVN’s military units  meaning these units should be removed from the ARVN

            // remaining military units will suffer a 20% reduction in weight (weight).
            // If no battle occurs, the ARVN forces remain intact.
        }
    }

    string str() const override
    {
        string battleFieldstr = "";
        string unitListstr = "";
        if (unitList)
        {
            unitListstr = unitList->str();
        }

        if (battleField)
            battleFieldstr = battleField->str();
        string s = "ARVN[LF=" + to_string(LF) + "," +
                   "EXP" + "=" + to_string(EXP) + "," +
                   "unitList" + "=" + unitListstr + "," +
                   "battleField" + "=" + battleFieldstr + "]";
        return s;
    }
};

class Configuration
{
private:
    int num_rows, num_cols;
    vector<Position *> arrayForest, arrayRiver, arrayFortification, arrayUrban, arraySpecialZone;
    Unit **liberationUnits;
    Unit **ARVNUnits;
    int eventCode;
    int sizeLib;
    int sizeARVN;

public:
    Configuration(const string &filepath)
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
                    {
                        num_cols = stoi(line.substr(9));
                    }
                    else if (line.find("ROWS=") != string::npos)
                    {
                        num_rows = stoi(line.substr(9));
                    }
                }
                else if (line.find("ARRAY_") != string::npos)
                {
                    if (line.find("FOREST=") != string::npos)
                    {
                        parsePositionA(line, arrayForest);
                    }
                    else if (line.find("RIVER=") != string::npos)
                    {
                        parsePositionA(line, arrayRiver);
                    }
                    else if (line.find("FORTIFICATION=") != string::npos)
                    {
                        parsePositionA(line, arrayFortification);
                    }
                    else if (line.find("URBAN=") != string::npos)
                    {
                        parsePositionA(line, arrayUrban);
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
                {
                    eventCode = stoi(line.substr(11));
                    if (eventCode < 0)
                        eventCode = 0;
                    eventCode %= 100;
                }
            }
        }
    }
    void parsePositionA(string line, vector<Position *> &x)
    {
        size_t ini = 0;
        size_t end = 0;
        while ((ini = line.find('(', end)) != string::npos)
        {
            ini = line.find('(', end);
            end = line.find(')', ini);
            string sub = line.substr(ini, end - ini + 1);
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
        for (char i : text)
        {
            ss << i;
            if (i == '(')
                flag++;
            if (i == ')')
                flag--;
            if (flag == 0 && i == ')')
            {

                unittext.push_back(ss.str());
                ss.str("");
                ss.clear();
            }
        }

        sizeLib = 0;
        sizeARVN = 0;
        for (const string &i : unittext)
        {
            if (i[i.size() - 2] == '0')
                sizeLib++;
            else if ((i[i.size() - 2] == '1'))
                sizeARVN++;
        }
        // worked

        liberationUnits = new Unit *[sizeLib]();
        ARVNUnits = new Unit *[sizeARVN]();

        for (const string &i : unittext)
        {
            string Type = extractWORD(i);
            int quantity, weight, X, Y, armybelong;
            size_t parenthesis = i.find('(');
            string data = i.substr(parenthesis + 1);
            stringstream ss(data);

            char ignore;
            ss >> quantity >> ignore >> weight >> ignore >> ignore >> X >> ignore >> Y >> ignore >> ignore >> armybelong;
            Position pos = Position(X, Y);

            Unit *unit;
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
    void push_up(Unit *unit, Unit **array, int sizeofArray)
    {
        int i = 0;
        while (i < sizeofArray)
        {
            if (array[i] == nullptr)
            {
                array[i] = unit;
                return;
            }
            i++;
        }
        array[i] = unit;
    }
    string extractWORD(string str)
    {
        string s = "";
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
            {
                s += str[i];
            }
        }
        return s;
    }
    VehicleType VConvertfromString(string str)
    {
        if (str == "TRUCK")
            return TRUCK;
        else if (str == "MORTAR")
            return MORTAR;
        else if (str == "ANTIAIRCRAFT")
            return ANTIAIRCRAFT;
        else if (str == "ARMOREDCAR")
            return ARMOREDCAR;
        else if (str == "APC")
            return APC;
        else if (str == "ARTILLERY")
            return ARTILLERY;
        else
            return TANK;
    }
    InfantryType IConvertfromString(string str)
    {
        if (str == "SNIPER")
            return SNIPER;
        else if (str == "ANTIAIRCRAFTSQUAD")
            return ANTIAIRCRAFTSQUAD;
        else if (str == "MORTARSQUAD")
            return MORTARSQUAD;
        else if (str == "ENGINEER")
            return ENGINEER;
        else if (str == "SPECIALFORCES")
            return SPECIALFORCES;
        else
            return REGULARINFANTRY;
    }

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
            if (str == arr[i])
                return 1;
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
            "REGULARINFANTRY"};

        for (int i = 0; i < 6; i++)
            if (str == arr[i])
                return 1;
        return 0;
    }
    ~Configuration()
    {
        releaseArr(arrayForest);
        releaseArr(arrayRiver);
        releaseArr(arrayUrban);
        releaseArr(arraySpecialZone);
        for (int i = 0; i < sizeLib; i++)
        {
            delete liberationUnits[i];
        }
        for (int i = 0; i < sizeARVN; i++)
        {
            delete ARVNUnits[i];
        }
        delete[] liberationUnits;
        delete[] ARVNUnits;
    }
    void releaseArr(vector<Position *> x)
    {
        for (int i = 0; i < x.size(); i++)
            delete x[i];
    }
    string str() const
    {
        string s = "[num_rows=" + to_string(num_rows) + "," + "num_cols=" + to_string(num_cols) + ",";

        s += "arrayForest=[";
        for (size_t i = 0; i < arrayForest.size(); ++i)
        {
            s += arrayForest[i]->str();
            if (i != arrayForest.size() - 1)
            {
                s += ",";
            }
        }
        s += "],";

        s += "arrayRiver=[";
        for (size_t i = 0; i < arrayRiver.size(); ++i)
        {
            s += arrayRiver[i]->str();
            if (i != arrayRiver.size() - 1)
            {
                s += ",";
            }
        }
        s += "],";

        s += "arrayFortification=[";
        for (size_t i = 0; i < arrayFortification.size(); ++i)
        {
            s += arrayFortification[i]->str();
            if (i != arrayFortification.size() - 1)
            {
                s += ",";
            }
        }
        s += "],";

        s += "arrayUrban=[";
        for (size_t i = 0; i < arrayUrban.size(); ++i)
        {
            s += arrayUrban[i]->str();
            if (i != arrayUrban.size() - 1)
            {
                s += ",";
            }
        }
        s += "],";

        s += "arraySpecialZone=[";
        for (size_t i = 0; i < arraySpecialZone.size(); ++i)
        {
            s += arraySpecialZone[i]->str();
            if (i != arraySpecialZone.size() - 1)
            {
                s += ",";
            }
        }
        s += "],";

        s += "liberationUnits=[";
        for (int i = 0; i < sizeLib; ++i)
        {
            s += liberationUnits[i]->str();
            if (i != sizeLib - 1)
            {
                s += ",";
            }
        }
        s += "],";

        s += "ARVNUnits=[";
        for (int i = 0; i < sizeARVN; ++i)
        {
            s += ARVNUnits[i]->str();
            if (i != sizeARVN - 1)
            {
                s += ",";
            }
        }
        s += "],";

        s += "eventCode=" + to_string(eventCode);

        s += "]";

        return s;
    }
    BattleField getBattleField() const
    {
        return BattleField(num_rows, num_cols, arrayForest, arrayRiver, arrayFortification, arrayUrban, arraySpecialZone);
    }
    int getsizeARVN() const
    {
        return sizeARVN;
    }
    int getsizeLib() const
    {
        return sizeLib;
    }
    Unit **getARVNarmy() const
    {
        return ARVNUnits;
    }
    Unit **getLibarmy() const
    {
        return liberationUnits;
    }
    int getEventCode() const
    {
        return eventCode;
    }
};

class HCMCampaign
{
private:
    Configuration *config;
    BattleField *battleField;
    LiberationArmy *liberationArmy;
    ARVN *arvn;
    int eventCode;

public:
    HCMCampaign(const string &config_file_path) : config(nullptr), battleField(nullptr), liberationArmy(nullptr), arvn(nullptr), eventCode(0)
    {
        config = new Configuration(config_file_path);
        battleField = new BattleField(config->getBattleField());
        arvn = new ::ARVN(config->getARVNarmy(), config->getsizeARVN(), "ARVN", battleField);
        liberationArmy = new LiberationArmy(config->getLibarmy(), config->getsizeLib(), "liberationArmy", battleField);
        eventCode = config->getEventCode();
    }
    ~HCMCampaign()
    {
        if (config)
        {
            delete config;
            config = nullptr;
        }
        if (battleField)
        {
            delete battleField;
            battleField = nullptr;
        }
        if (liberationArmy)
        {
            delete liberationArmy;
            liberationArmy = nullptr;
        }
        if (arvn)
        {
            delete arvn;
            arvn = nullptr;
        }
    }
    void run()
    {

        if (arvn && liberationArmy)
        {
            battleField->applyEffect(arvn);
            battleField->applyEffect(liberationArmy);

            if (eventCode < 75)
            {
                liberationArmy->fight(arvn, false);
                arvn->fight(liberationArmy, true);
            }
            else
            {
                arvn->fight(liberationArmy, false);
                liberationArmy->fight(arvn, true);
                arvn->fight(liberationArmy, true);
                liberationArmy->fight(arvn, false);
            }

            arvn->cleanupUnit();
            liberationArmy->cleanupUnit();
        }
    }

    string printResult() { return "LIBERATIONARMY[LF=" + to_string(liberationArmy->getLF()) + ",EXP=" + to_string(liberationArmy->getEXP()) + "]-ARVN[LF=" + to_string(arvn->getLF()) + ",EXP=" + to_string(arvn->getEXP()) + "]"; }
};

#endif
