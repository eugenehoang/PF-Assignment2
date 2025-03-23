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
enum Type
{
    VEHICLE,
    INFANTRY
};
class LinkedLists{


};
 class Node 
 {  public:
    Unit* data;
    Node* next;
    Node(){next = nullptr;};
    Node(Unit* unit) : data(unit), next(nullptr){}
    // constr
 };
 class LinkedList
 {  private:
    Node* head = new Node();
    public:
    Node* getHead() {return head;}

    LinkedList();
    ~LinkedList()
    {
        Node* now = head;
        while (now)
        {
            Node* temp = now;
            now = now->next;
            delete temp; 
        }
        delete now;
        void add(Unit *uInfantry);
        void add(Unit *uVehicle);
    }

     
 };
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