/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 2
* Programming Fundamentals Spring 2025
* Date: 02.02.2025
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "hcmcampaign.h"


using namespace std;

void g_satc_01() {
    cout << "----- Sample Testcase 03 -----" << endl;
    HCMCampaign* campaign = new HCMCampaign("config.txt");
    cout << "** Before the fight" << endl;
    
    cout << campaign->printResult() << endl;
    cout << "** After the fight" << endl;
    campaign->run();
    cout << campaign->printResult() << endl;
    delete campaign;

}

void tc0()
{
   
        // Create positions for terrain elements
        vector<Position*> arrayForest = {new Position(1, 1), new Position(2, 2)};
        vector<Position*> arrayRiver = {new Position(0, 0)};
        vector<Position*> arrayFortification = {new Position(3, 3)};
        vector<Position*> arrayUrban = {new Position(4, 4)};
        vector<Position*> arraySpecialZone = {new Position(5, 5)};
    
        // Create a battlefield
        BattleField battlefield(6, 6, arrayForest, arrayRiver, arrayFortification, arrayUrban, arraySpecialZone);
    
        // Create armies
        Unit* liberationUnits[] = {
            new Infantry(10, 5, Position(1, 1), SPECIALFORCES),
            new Vehicle(5, 10, Position(2, 2), TANK)
        };
        Unit* arvnUnits[] = {
            new Infantry(8, 4, Position(3, 3), REGULARINFANTRY),
            new Vehicle(3, 15, Position(4, 4), ARTILLERY)
        };
    
        LiberationArmy liberationArmy(liberationUnits, 2, "LiberationArmy", &battlefield);
        ARVN arvn(arvnUnits, 2, "ARVN", &battlefield);
    
        // Apply terrain effects
        battlefield.applyEffect(&liberationArmy);
        battlefield.applyEffect(&arvn);
    
        // Print results
        cout << liberationArmy.str() << endl;
        cout << arvn.str() << endl;
    
        // Clean up
        for (Position* pos : arrayForest) delete pos;
        for (Position* pos : arrayRiver) delete pos;
        for (Position* pos : arrayFortification) delete pos;
        for (Position* pos : arrayUrban) delete pos;
        for (Position* pos : arraySpecialZone) delete pos;
        delete liberationUnits[0];
        delete liberationUnits[1];
        delete arvnUnits[0];
        delete arvnUnits[1];
    
        return ;
    
}
void tc2()
{cout << "----- Sample Testcase 01 -----" << endl;
    Configuration* config = new Configuration("config.txt");
    cout << config->str() << endl;
    delete config;}
void tc4()
{
    cout << "----- Sample Testcase 02 -----" << endl;
    Vehicle tankOfLiber(20, 20, Position(1, 2), MORTAR);
    Vehicle truckOfLiber(15, 10, Position(2, 2), TRUCK);
    Infantry sniperOfLiber(10, 20, Position(1, 1), SNIPER);

    Vehicle tankOfAr(5, 20, Position(3, 2), MORTAR);
    Vehicle truckOfAr(1, 10, Position(3, 1), TRUCK);
    Infantry sniperOfAr(7, 20, Position(3, 3), SNIPER);

    Unit** unitArrayOfLiber = new Unit*[3];
    unitArrayOfLiber[0] = &tankOfLiber;
    unitArrayOfLiber[1] = &truckOfLiber;
    unitArrayOfLiber[2] = &sniperOfLiber;

    Unit** unitArrayOfAr = new Unit*[3];
    unitArrayOfAr[0] = &tankOfAr;
    unitArrayOfAr[1] = &truckOfAr;
    unitArrayOfAr[2] = &sniperOfAr;

    LiberationArmy* liberationArmy = new LiberationArmy(unitArrayOfLiber, 3, "LiberationArmy", 0);
    cout << liberationArmy->str() << endl;
    ARVN* arvn = new ARVN(unitArrayOfAr, 3, "ARVN", 0);
    cout << arvn->str() << endl;

    Army* enemyLiber = arvn;
    liberationArmy->fight(enemyLiber, false);
    Army* enemyAr = liberationArmy;
    arvn->fight(enemyAr, false);

    cout << "* After the fight" << endl;
    cout << liberationArmy->str() << endl;
    cout << arvn->str() << endl;

    delete liberationArmy;
    delete arvn;
    delete[] unitArrayOfLiber;
    delete[] unitArrayOfAr;
}

void tc3()
{
    cout << "----- Sample Testcase 02 -----" << endl;
    Vehicle tankOfLiber(20, 20, Position(1, 2), MORTAR);
  
    Vehicle truckOfLiber(15, 10, Position(2, 2), TRUCK);
    Infantry sniperOfLiber(10, 20, Position(1, 1), SNIPER);

    Vehicle tankOfAr(5, 20, Position(3, 2), MORTAR);
    Vehicle truckOfAr(1, 10, Position(3, 1), TRUCK);
    Infantry sniperOfAr(7, 20, Position(3, 3), SNIPER);

    Unit** unitArrayOfLiber = new Unit*[3];
    unitArrayOfLiber[0] = &tankOfLiber;
    unitArrayOfLiber[1] = &truckOfLiber;
    unitArrayOfLiber[2] = &sniperOfLiber;

    Unit** unitArrayOfAr = new Unit*[3];
    unitArrayOfAr[0] = &tankOfAr;
    unitArrayOfAr[1] = &truckOfAr;
    unitArrayOfAr[2] = &sniperOfAr;
    
    LiberationArmy* liberationArmy = new LiberationArmy(unitArrayOfLiber, 3, "LiberationArmy", 0); cout << "oo";
    
    cout << liberationArmy->str() << endl;
    cout << 55;
    ARVN* arvn = new ARVN(unitArrayOfAr, 3, "ARVN", 0);
    cout << arvn->str() << endl;

    Army* enemyLiber = arvn;
    liberationArmy->fight(enemyLiber, false);
    Army* enemyAr = liberationArmy;
    arvn->fight(enemyAr, false);

    cout << "* After the fight" << endl;
    cout << liberationArmy->str() << endl;
    cout << arvn->str() << endl;

    delete liberationArmy;
    delete arvn;
    delete[] unitArrayOfLiber;
    delete[] unitArrayOfAr;
}
 void tc7()
 {
    cout << "----- Sample Testcase 07 -----" << endl;
    Vehicle tankOfLiber1(20, 20, Position(1, 2), MORTAR);
    Vehicle tankOfLiber2(5, 20, Position(3, 2), MORTAR);
    Infantry sniperOfLiber1(10, 20, Position(1, 0), SNIPER);
    Infantry sniperOfLiber2(10, 20, Position(1, 1), SNIPER);
    Unit** unitArrayOfLiber8 = new Unit*[4];
    unitArrayOfLiber8[0] = &tankOfLiber1;
    unitArrayOfLiber8[1] = &tankOfLiber2;
    unitArrayOfLiber8[2] = &sniperOfLiber1;
    unitArrayOfLiber8[3] = &sniperOfLiber2;
    LiberationArmy* liberationArmy8 = new LiberationArmy(unitArrayOfLiber8, 4, "LiberationArmy", 0);
    cout << liberationArmy8->str() << endl;
 }
 void testUnitclass()
 {
    cout << "----- test unit class -----\n";
    Vehicle tankOfLiber(20, 20, Position(1, 2), MORTAR);
    Vehicle truckOfLiber(15, 10, Position(2, 2), TRUCK);
    Infantry sniperOfLiber(10, 20, Position(1, 1), SNIPER);
 
    Position p1 = tankOfLiber.getCurrentPosition();
    Position p2 = truckOfLiber.getCurrentPosition();
    Position p3 = sniperOfLiber.getCurrentPosition();

    cout << p1.str() << " " << p2.str() << " " << p3.str() << endl;

 }
 
   void testUnitListclass()
{
    cout << "----- test unitlistlist class -----\n";

    // Vehicles
    Vehicle tankOfLiber1(20, 20, Position(1, 2), MORTAR);
    Vehicle tankOfLiber2(5, 20, Position(3, 2), ARTILLERY);
    Vehicle tankOfLiber3(20, 20, Position(1, 2), ARMOREDCAR);
    Vehicle tankOfLiber4(20, 20, Position(1, 2), APC);
    Vehicle tankOfLiber5(5, 20, Position(3, 2), TRUCK);
    Vehicle tankOfLiber6(5, 20, Position(3, 2), ANTIAIRCRAFT);
    Vehicle tankOfLiber7(20, 20, Position(1, 2), MORTAR);
    Vehicle tankOfLiber8(5, 20, Position(3, 2), TANK);
    // More vehicles can be added if needed

    // Infantry
    Infantry sniperOfLiber1(10, 20, Position(1, 0), SNIPER);
    Infantry sniperOfLiber2(15, 24, Position(1, 1), ANTIAIRCRAFTSQUAD);
    Infantry sniperOfLiber3(10, 20, Position(1, 0), MORTARSQUAD);
    Infantry sniperOfLiber4(15, 24, Position(1, 1), ENGINEER);
    Infantry sniperOfLiber5(10, 20, Position(1, 0), SPECIALFORCES);
    Infantry sniperOfLiber6(15, 24, Position(1, 1), REGULARINFANTRY);

    // Create array of Unit pointers (up to 14 in this example)
    Unit** unitArrayOfLiber13 = new Unit*[14];
    unitArrayOfLiber13[0] = &tankOfLiber1;
    unitArrayOfLiber13[1] = &tankOfLiber2;
    unitArrayOfLiber13[2] = &tankOfLiber3;
    unitArrayOfLiber13[3] = &tankOfLiber4;
    unitArrayOfLiber13[4] = &tankOfLiber5;
    unitArrayOfLiber13[5] = &tankOfLiber6;
    unitArrayOfLiber13[6] = &tankOfLiber7;
    unitArrayOfLiber13[7] = &tankOfLiber8;
    unitArrayOfLiber13[8] = &sniperOfLiber1;
    unitArrayOfLiber13[9] = &sniperOfLiber2;
    unitArrayOfLiber13[10] = &sniperOfLiber3;
    unitArrayOfLiber13[11] = &sniperOfLiber4;
    unitArrayOfLiber13[12] = &sniperOfLiber5;
    unitArrayOfLiber13[13] = &sniperOfLiber6;

    // Create the LiberationArmy with 14 units
    LiberationArmy* liberationArmy8 = new LiberationArmy(unitArrayOfLiber13, 14, "LiberationArmy", 0);

    // Print the army's string representation
    cout << liberationArmy8->str() << endl;

    // Clean up dynamically allocated array (not the units themselves, as they are stack-allocated)
    delete[] unitArrayOfLiber13;
    delete liberationArmy8;
}
void tcvt()
{
   //! data ------------------------------------
     UnitList ul;
     cout << 1;
    bool allInserted = true;
    Vehicle* listveh[8];
    for (int i = 0; i < 7; ++i) {
        listveh[i] = new Vehicle(1, 1, Position(), (VehicleType)i);
        if (!ul.insert(listveh[i])) {
            allInserted = false;
            break;
        }
    }
    Vehicle* veh9 = new Vehicle(1, 1, Position(), APC);
    bool insert13 = ul.insert(veh9);
    delete veh9;
    bool result = allInserted && !veh9;
    cout << 15;
    for (int i = 0; i < 8; ++i) {
       delete listveh[i];
    }
}
 
void tcvt2()
{

  
    string name = "Task208";
    //! data ------------------------------------
    // Công thức Vehicle: score = (typeValue ∗ 304 + quantity ∗ weight) / 30
    Vehicle v1(9, 1, Position(1,1), APC); // attackScore = (4*304 + 9*1)/30 = 40.8(3) -> ceil = 41

    // Công thức Infantry: score = typeValue ∗ 56 + quantity ∗ weight
    Infantry i1(4, 4, Position(1,2), ANTIAIRCRAFTSQUAD); 
    /*
        attackScore = 1*56 + 4*4 = 72
        Số cá nhân: 7 + 2 + 1 + 9 + 7 + 5 = 31, 3 + 1 = 4
        Số cá nhân không thoả điều kiện cập nhật => attackScore = 72
    */
    
    Infantry i2(10, 2, Position(1,3), MORTARSQUAD);
    /*
        attackScore = 2*56 + 10*2 = 132
        Số cá nhân: 1 + 3 + 2 + 1 + 9 + 7 + 5 = 28, 2 + 8 = 10, 1 + 0 = 1
        Số cá nhân thoả điều kiện cập nhật (1 < 3) => quantity giảm 10\% => quantity = 90\% quantity = 10 * 90\% = 9 => ceil = 9
        Cập nhật attackScore: attackScore = 2*56 + 10*2 = 130
    */

    Unit* unitArray1[3];
    unitArray1[0] = &v1;
    unitArray1[1] = &i1;
    unitArray1[2] = &i2;
    LiberationArmy* attacker = new LiberationArmy(unitArray1, 3, "TestArmy208",0);
    /*
    Khởi tạo Liberation Army từ unitList có 3 phần tử với AttackScore lần lượt là:
    LF = 41
    EXP = 72 + 130 = 202
    */
    Vehicle v2(5, 3, Position(3,1), MORTAR);// attackScore = (1*304 + 5*3)/30 = 10.6(3) -> ceil = 11
    
    Infantry i3(3, 5, Position(3,2), SNIPER);
    /*
        attackScore = 0*56 + 3*5 = 15
        Số cá nhân: 1 + 5 + 1 + 9 + 7 + 5 = 28, 2 + 8 = 1=, 1 + 0 = 1
        Số cá nhân thoả điều kiện cập nhật (1 < 3) => quantity giảm 10\% => quantity = 90\% quantity = 3 * 90\% = 2.7 => ceil = 3
        Cập nhật attackScore = 0*56 + 3*5 = 15
    */
    
    Infantry i4(1, 1, Position(3,3), SPECIALFORCES);
    /*
        attackScore = 4 * 56 + 1 * 1 = 225
        Đơn vị SPECIALFORCES và weight = 1 là số chính phương => chỉ số xét = 225 + 75 = 300
        Số cá nhân: 3 + 0 + 0 + 1 + 9 + 7 + 5 = 25, 2 + 5 = 7
        Số cá nhân không thoả điều kiện cập nhật ( 7 không bé hơn 7) => attackScore = 225
    */

    Unit* unitArray2[3];
    unitArray2[0] = &v2;
    unitArray2[1] = &i3;
    unitArray2[2] = &i4;
    Army* enemy = new ARVN(unitArray2, 3, "EnemyArmy208",0);
    /*
    Khởi tạo ARVN Army từ unitList có 3 phần tử với AttackScore lần lượt là:
    LF = 11
    EXP = 15 + 225 = 240
    */
    //! process ---------------------------------
    attacker->fight(enemy, false);
    // Liberation Army Tấn công
    // LF = LF * 1.5 = 41 * 1.5 = 61.6 -> ceil = 62
    // EXP = EXP * 1.5 = 202 * 1.5 = 303
    // Tìm được tổ hợp A của Liber > tổng attackScore của ARVN
    // Không tim thấy tổ hợp B, tuy nhiên EXP sau khi nhân 1.5 > EXP của ARVN => Giao tranh thắng
    // B1: Xoá tổ hợp trong A: Xoá tổ hợp A và toàn bộ Infantry => unitList của Liber đang rỗng
    // B2: chèn các đơn vị từ enemy vào: => UnitList của Liber bao gồm: TANK, SNIPER và SPECIALFORCE. UnitList của ARVN là rỗng
    //  B3: cập nhật 2 quân: 
    //     Liber: LF = 11, EXP = 240
    //     ARVN: LF = 0, EXP = 0
    string result = attacker->str() + "\n" + enemy->str();

    //! expect ----------------------------------
    string expect = "LiberationArmy[LF=11,EXP=240,unitList=UnitList[count_vehicle=1;count_infantry=2;Infantry[infantryType=SPECIALFORCES,quantity=1,weight=1,position=(3,3)],Infantry[infantryType=SNIPER,quantity=3,weight=5,position=(3,2)],Vehicle[vehicleType=MORTAR,quantity=5,weight=3,position=(3,1)]],battleField=]\n"
                    "ARVN[LF=0,EXP=0,unitList=UnitList[count_vehicle=0;count_infantry=0],battleField=]";

    //! output ----------------------------------
  cout << result;
    
    //! remove data -----------------------------
    delete attacker;
    delete enemy;
        
      
    
}
void tcvt3()
{
     string name = "Task319";
    

    // Tạo một đơn vị bộ binh nằm trong bán kính 2 của River
    Infantry* infantry = new Infantry(100, 5, Position(1, 1), SNIPER);
    Unit* unitArray[1] = { infantry };
    cout << infantry->getquantity();
    Army* army = new ARVN(unitArray, 1, "ARVN_Test", nullptr);
    cout << infantry->getAffectedATK();
     cout << infantry->getquantity();
army->str();
    River river(Position(1, 0));
    cout << infantry->getquantity();
    river.getEffect(army);
    cout << infantry->getquantity();
   
    cout << "ARVN Fort: " << army->str() << "\n";
        cout << infantry->getquantity();

    string expect = "ARVN Fort: ARVN[LF=0,EXP=500,unitList=UnitList[count_vehicle=0;count_infantry=1;Infantry[infantryType=SNIPER,quantity=120,weight=5,position=(1,1)]],battleField=]\n";

    delete infantry;
    delete army;
    
    
}
void tcvt4()
{
   string name = "Task330";
    stringstream output;

    // Test động: Mô phỏng tình huống di chuyển của Army và áp dụng hiệu ứng liên tục của BattleField.
    vector<Position*> arrayForest;          // Mountain
    vector<Position*> arrayRiver;           // River
    vector<Position*> arrayFortification;   // Fortification
    vector<Position*> arrayUrban;           // Urban
    vector<Position*> arraySpecialZone;     // SpecialZone

    // Định nghĩa một số vị trí đặc biệt trong một BattleField 5x5
    arrayForest.push_back(new Position(0, 0));
    arrayRiver.push_back(new Position(0, 1));
    arrayFortification.push_back(new Position(1, 0));
    arrayUrban.push_back(new Position(2, 2));
    arraySpecialZone.push_back(new Position(3, 3));

    int n_rows = 5, n_cols = 5;
    BattleField* bf = new BattleField(n_rows, n_cols, arrayForest, arrayRiver, arrayFortification, arrayUrban, arraySpecialZone);

    // Tạo Army ban đầu với các đơn vị đặt tại vị trí ban đầu chưa bị hiệu ứng đặc biệt.
    Infantry* inf = new Infantry(100, 5, Position(4, 4), REGULARINFANTRY);
    Vehicle* veh = new Vehicle(90, 5, Position(4, 3), TRUCK);
    Unit* units[2] = { inf, veh };
    Army* army = new ARVN(units, 2, "ARVN_230", nullptr);

    output << "Initial Army: " << army->str() << "\n";

    // Áp dụng hiệu ứng của toàn BattleField lần 1.
   
        
    output << "After 1st round effects: " << army->str() << "\n";

    // Áp dụng hiệu ứng lần 2 sau khi di chuyển.
    bf->applyEffect(army);
    output << "After 2nd round effects: " << army->str();

    string result = output.str();
    // Vì chuỗi kết quả phụ thuộc vào tính toán hiệu ứng liên tục, ta dùng giá trị thực thu được làm kỳ vọng.
    string expect = "Initial Army: ARVN[LF=15,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=1;Infantry[infantryType=REGULARINFANTRY,quantity=90,weight=5,position=(4,4)],Vehicle[vehicleType=TRUCK,quantity=90,weight=5,position=(4,3)]],battleField=]\nAfter 1st round effects: ARVN[LF=15,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=1;Infantry[infantryType=REGULARINFANTRY,quantity=90,weight=5,position=(4,4)],Vehicle[vehicleType=TRUCK,quantity=90,weight=5,position=(4,3)]],battleField=]\nAfter 2nd round effects: ARVN[LF=15,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=1;Infantry[infantryType=REGULARINFANTRY,quantity=90,weight=5,position=(4,4)],Vehicle[vehicleType=TRUCK,quantity=90,weight=5,position=(4,3)]],battleField=]";

    // Cleanup
    delete inf;
    delete veh;
    delete army;
    delete bf;
    for(auto p : arrayForest) delete p;
    for(auto p : arrayRiver) delete p;
    for(auto p : arrayFortification) delete p;
    for(auto p : arrayUrban) delete p;
    for(auto p : arraySpecialZone) delete p;

  cout << result;
}
void tcvt5()
{
  string name = "Task315";
    //! data ------------------------------------
    // Test TerrainElement base class constructor and position functionality
    int row = 7;
    int col = 5;

    TerrainElement*** map_element = new TerrainElement**[row];
    for (int i = 0; i < row; ++i) {
        map_element[i] = new TerrainElement*[col];
        for (int j = 0; j < col; ++j) {
            if (i % 2 == 0 && j % 3 == 0) {
                map_element[i][j] = new Road(Position(i, j));
            } else if (i % 2 == 0 && j % 3 == 1) {
                map_element[i][j] = new Mountain(Position(i, j));
            } else if (i % 2 == 0 && j % 3 == 2) {
                map_element[i][j] = new River(Position(i, j));
            } else if (i % 2 == 0 && j % 3 == 0) {
                map_element[i][j] = new SpecialZone(Position(i, j));
            } else if (i % 2 == 1 && j % 3 == 1) {
                map_element[i][j] = new Fortification(Position(i, j));
            } else if (i % 2 == 1 && j % 3 == 2) {
                map_element[i][j] = new Urban(Position(i, j));
            } else {
                map_element[i][j] = new Road(Position(i, j));
            }
        }
    }

    stringstream output;
    
    //! process ---------------------------------
    // Create a simple army to test basic functionality
    Infantry* sniper = new Infantry(10, 5, Position(3, 5), SNIPER); // Adjacent to element
    Infantry* antiarcraftsquad = new Infantry(8, 6, Position(3, 7), ANTIAIRCRAFTSQUAD); // Adjacent to element
    Vehicle* truck = new Vehicle(10, 5, Position(4, 4), TRUCK); // Adjacent to element
    Vehicle* mortar = new Vehicle(8, 6, Position(6, 4), MORTAR); // Adjacent to element
    Unit* unitArray[4] = {sniper, antiarcraftsquad, truck, mortar};
    Army* arvn = new ARVN(unitArray, 4, "TestArmy", nullptr);

    Infantry* engineer = new Infantry(5, 8, Position(0, 2), ENGINEER); // Within radius 2
    Infantry* specialforces = new Infantry(4, 9, Position(0, 3), SPECIALFORCES); // Within radius 2
    Infantry* regularinfantry = new Infantry(3, 10, Position(0, 3), REGULARINFANTRY); // Within radius 2
    Vehicle* apc = new Vehicle(4, 9, Position(0, 3), APC); // Within radius 2
    Vehicle* artillery = new Vehicle(3, 10, Position(0, 3), ARTILLERY);
    Vehicle* tank = new Vehicle(2, 11, Position(0, 4), TANK);
    Unit* unitArray2[6] = {engineer, specialforces, apc, regularinfantry, artillery, tank};
    Army* liber = new LiberationArmy(unitArray2, 6, "TestArmy", nullptr);
    
    output << "Initial Army: " << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    output << "Liberation attack ARVN: " << endl;
    liber->fight(arvn, false);
    output << "After Attack: " << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    output << "ARVN defends Liberation: " << endl;
    arvn->fight(liber, true);
    output << "After defends: " << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    output << "Terrain Elements get effect: " << endl;
 
    output << "After Base Effect: " << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    output << "ARVN attack Liberation: " << endl;
    arvn->fight(liber, false);
    output << "After Attack: " << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    output << "Liberation defends ARVN: " << endl;
    liber->fight(arvn, true);
    output << "After defends: " << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;
    
    //! expect ----------------------------------
    // Base TerrainElement shouldn't modify army stats
    string expect = "Initial Army: \n"
"1. LiberationArmy[LF=156,EXP=500,unitList=UnitList[count_vehicle=3;count_infantry=3;Infantry[infantryType=REGULARINFANTRY,quantity=4,weight=10,position=(0,3)],Infantry[infantryType=SPECIALFORCES,quantity=4,weight=9,position=(0,3)],Infantry[infantryType=ENGINEER,quantity=5,weight=8,position=(0,2)],Vehicle[vehicleType=APC,quantity=4,weight=9,position=(0,3)],Vehicle[vehicleType=ARTILLERY,quantity=3,weight=10,position=(0,3)],Vehicle[vehicleType=TANK,quantity=2,weight=11,position=(0,4)]],battleField=]\n"
"2. ARVN[LF=14,EXP=176,unitList=UnitList[count_vehicle=2;count_infantry=2;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=6,position=(3,7)],Infantry[infantryType=SNIPER,quantity=12,weight=5,position=(3,5)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(4,4)],Vehicle[vehicleType=MORTAR,quantity=8,weight=6,position=(6,4)]],battleField=]\n"
"Liberation attack ARVN: \n"
"After Attack: \n"
"1. LiberationArmy[LF=128,EXP=500,unitList=UnitList[count_vehicle=4;count_infantry=4;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=6,position=(3,7)],Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(3,5)],Infantry[infantryType=REGULARINFANTRY,quantity=5,weight=10,position=(0,3)],Infantry[infantryType=SPECIALFORCES,quantity=4,weight=9,position=(0,3)],Vehicle[vehicleType=ARTILLERY,quantity=3,weight=10,position=(0,3)],Vehicle[vehicleType=TANK,quantity=2,weight=11,position=(0,4)],Vehicle[vehicleType=MORTAR,quantity=8,weight=6,position=(6,4)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(4,4)]],battleField=]\n"
"2. ARVN[LF=0,EXP=0,unitList=UnitList[count_vehicle=0;count_infantry=0],battleField=]\n"
"ARVN defends Liberation: \n"
"After defends: \n"
"1. LiberationArmy[LF=128,EXP=500,unitList=UnitList[count_vehicle=4;count_infantry=4;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=6,position=(3,7)],Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(3,5)],Infantry[infantryType=REGULARINFANTRY,quantity=5,weight=10,position=(0,3)],Infantry[infantryType=SPECIALFORCES,quantity=4,weight=9,position=(0,3)],Vehicle[vehicleType=ARTILLERY,quantity=3,weight=10,position=(0,3)],Vehicle[vehicleType=TANK,quantity=2,weight=11,position=(0,4)],Vehicle[vehicleType=MORTAR,quantity=8,weight=6,position=(6,4)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(4,4)]],battleField=]\n"
"2. ARVN[LF=0,EXP=0,unitList=UnitList[count_vehicle=0;count_infantry=0],battleField=]\n"
"Terrain Elements get effect: \n"
"After Base Effect: \n"
"1. LiberationArmy[LF=105,EXP=500,unitList=UnitList[count_vehicle=4;count_infantry=4;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=6,position=(3,7)],Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(3,5)],Infantry[infantryType=REGULARINFANTRY,quantity=5,weight=10,position=(0,3)],Infantry[infantryType=SPECIALFORCES,quantity=4,weight=9,position=(0,3)],Vehicle[vehicleType=ARTILLERY,quantity=3,weight=10,position=(0,3)],Vehicle[vehicleType=TANK,quantity=2,weight=11,position=(0,4)],Vehicle[vehicleType=MORTAR,quantity=8,weight=6,position=(6,4)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(4,4)]],battleField=]\n"
"2. ARVN[LF=0,EXP=0,unitList=UnitList[count_vehicle=0;count_infantry=0],battleField=]\n"
"ARVN attack Liberation: \n"
"After Attack: \n"
"1. LiberationArmy[LF=105,EXP=500,unitList=UnitList[count_vehicle=4;count_infantry=4;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=6,position=(3,7)],Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(3,5)],Infantry[infantryType=REGULARINFANTRY,quantity=5,weight=10,position=(0,3)],Infantry[infantryType=SPECIALFORCES,quantity=4,weight=9,position=(0,3)],Vehicle[vehicleType=ARTILLERY,quantity=3,weight=10,position=(0,3)],Vehicle[vehicleType=TANK,quantity=2,weight=11,position=(0,4)],Vehicle[vehicleType=MORTAR,quantity=8,weight=6,position=(6,4)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(4,4)]],battleField=]\n"
"2. ARVN[LF=0,EXP=0,unitList=UnitList[count_vehicle=0;count_infantry=0],battleField=]\n"
"Liberation defends ARVN: \n"
"After defends: \n"
"1. LiberationArmy[LF=137,EXP=500,unitList=UnitList[count_vehicle=4;count_infantry=4;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=6,position=(3,7)],Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(3,5)],Infantry[infantryType=REGULARINFANTRY,quantity=5,weight=10,position=(0,3)],Infantry[infantryType=SPECIALFORCES,quantity=4,weight=9,position=(0,3)],Vehicle[vehicleType=ARTILLERY,quantity=3,weight=10,position=(0,3)],Vehicle[vehicleType=TANK,quantity=2,weight=11,position=(0,4)],Vehicle[vehicleType=MORTAR,quantity=8,weight=6,position=(6,4)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(4,4)]],battleField=]\n"
"2. ARVN[LF=0,EXP=0,unitList=UnitList[count_vehicle=0;count_infantry=0],battleField=]\n";
    
    //! cleanup ---------------------------------
    delete sniper;
    delete antiarcraftsquad;
    delete truck;
    delete mortar;
    delete engineer;
    delete specialforces;
    delete regularinfantry;
    delete apc;
    delete artillery;
    delete tank;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            delete map_element[i][j];
        }
        delete[] map_element[i];
    }
    delete[] map_element;
    delete arvn;
    delete liber;
    
    //! result ----------------------------------
    cout << output.str();
}

void tcvt6() {
    string name = "Task317";
    stringstream output;

    //! Data ------------------------------------
    // Tạo các vector chứa vị trí cho từng loại TerrainElement
    vector<Position*> arrayForest;        // Dành cho Mountain (rừng núi)
    vector<Position*> arrayRiver;         // River
    vector<Position*> arrayFortification; // Fortification
    vector<Position*> arrayUrban;         // Urban
    vector<Position*> arraySpecialZone;   // SpecialZone

    // Khởi tạo một số vị trí đặc trưng trong BattleField 5x5:
    // Ví dụ: (0,0) và (0,2) sẽ là Mountain, (1,1) là River, (2,3) là Fortification,
    // (3,2) là Urban, (4,4) là SpecialZone. Các vị trí còn lại mặc định sẽ là Road.
    arrayForest.push_back(new Position(0, 0));
    arrayForest.push_back(new Position(0, 2));
        arrayForest.push_back(new Position(0, 99));

    arrayRiver.push_back(new Position(1, 1));
    arrayFortification.push_back(new Position(2, 3));
    arrayUrban.push_back(new Position(3, 2));
    arraySpecialZone.push_back(new Position(4, 4));

    int n_rows = 10, n_cols = 4;
    // Tạo BattleField với các yếu tố địa hình được khởi tạo thông qua các vector trên
    BattleField* bf = new BattleField(n_rows, n_cols, arrayForest, arrayRiver, arrayFortification, arrayUrban, arraySpecialZone);

    //! Tạo hai đội quân ------------------------------------
    // Đội quân LiberationArmy với 3 đơn vị:
    // - 2 infantry đặt tại (0,0) và (0,2) (nằm trên vùng Mountain)
    // - 1 vehicle đặt tại (1,1) (nằm trên vùng River)
    Infantry* libInf1 = new Infantry(12, 6, Position(0, 0), SNIPER);
    Infantry* libInf2 = new Infantry(11, 5, Position(0, 2), REGULARINFANTRY);
    Vehicle* libVeh1 = new Vehicle(10, 5, Position(1, 1), TRUCK);
    Unit* unitsLib[3] = { libInf1, libInf2, libVeh1 };
    // Gán con trỏ BattleField vào Army nếu cần (để sử dụng trong việc cập nhật vị trí hoặc hiệu ứng riêng)
    Army* liber = new LiberationArmy(unitsLib, 3, "LibArmy", bf);

    // Đội quân ARVN với 3 đơn vị:
    // - 1 infantry đặt tại (3,2) (nằm trên vùng Urban)
    // - 1 infantry đặt tại (2,3) (nằm trên vùng Fortification)
    // - 1 vehicle đặt tại (4,4) (nằm trên vùng SpecialZone)
    Infantry* arvnInf1 = new Infantry(9, 6, Position(3, 2), SPECIALFORCES);
    Infantry* arvnInf2 = new Infantry(8, 7, Position(2, 3), ANTIAIRCRAFTSQUAD);
    Vehicle* arvnVeh1 = new Vehicle(11, 4, Position(4, 4), MORTAR);
    Unit* unitsArvn[3] = { arvnInf1, arvnInf2, arvnVeh1 };
    Army* arvn = new ARVN(unitsArvn, 3, "ARVN", bf);

    //! Process ---------------------------------
    output << "Initial State:" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    // Áp dụng hiệu ứng của toàn bộ BattleField (Round 1)
    output << "Applying Battlefield Effects (Round 1):" << endl;
   bf->applyEffect(liber);
   bf->applyEffect(arvn);
    output << "After Effects (Round 1):" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    // Giả lập trận chiến: LiberationArmy tấn công ARVN
    output << "Liberation attacks ARVN:" << endl;
    liber->fight(arvn, false);
    output << "After Attack:" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    // ARVN phản công (phòng thủ)
    output << "ARVN defends Liberation:" << endl;
    arvn->fight(liber, true);
    output << "After Defense:" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    // Áp dụng hiệu ứng của BattleField lần 2 (Round 2)
    output << "Applying Battlefield Effects (Round 2):" << endl;
    bf->applyEffect(liber);
   bf->applyEffect(arvn);
    output << "After Effects (Round 2):" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    //! Kết quả ---------------------------------
    string result = output.str();
    // Vì các hiệu ứng chồng lấn và tính toán theo bán kính làm cho chuỗi kết quả rất phức tạp, ta sử dụng giá trị thực thu được làm kỳ vọng.
    string expect = "Initial State:\n"
"1. LiberationArmy[LF=2,EXP=407,unitList=UnitList[count_vehicle=1;count_infantry=2;Infantry[infantryType=REGULARINFANTRY,quantity=11,weight=5,position=(0,2)],Infantry[infantryType=SNIPER,quantity=12,weight=6,position=(0,0)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(1,1)]],battleField=BattleField[n_rows=5,n_cols=5]]\n"
"2. ARVN[LF=12,EXP=404,unitList=UnitList[count_vehicle=1;count_infantry=2;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=7,position=(2,3)],Infantry[infantryType=SPECIALFORCES,quantity=9,weight=6,position=(3,2)],Vehicle[vehicleType=MORTAR,quantity=11,weight=4,position=(4,4)]],battleField=BattleField[n_rows=5,n_cols=5]]\n"
"Applying Battlefield Effects (Round 1):\n"
"After Effects (Round 1):\n"
"1. LiberationArmy[LF=2,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=2;Infantry[infantryType=REGULARINFANTRY,quantity=11,weight=5,position=(0,2)],Infantry[infantryType=SNIPER,quantity=12,weight=6,position=(0,0)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(1,1)]],battleField=BattleField[n_rows=5,n_cols=5]]\n"
"2. ARVN[LF=12,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=2;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=7,position=(2,3)],Infantry[infantryType=SPECIALFORCES,quantity=9,weight=6,position=(3,2)],Vehicle[vehicleType=MORTAR,quantity=11,weight=4,position=(4,4)]],battleField=BattleField[n_rows=5,n_cols=5]]\n"
"Liberation attacks ARVN:\n"
"After Attack:\n"
"1. LiberationArmy[LF=2,EXP=407,unitList=UnitList[count_vehicle=1;count_infantry=2;Infantry[infantryType=REGULARINFANTRY,quantity=11,weight=5,position=(0,2)],Infantry[infantryType=SNIPER,quantity=12,weight=6,position=(0,0)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(1,1)]],battleField=BattleField[n_rows=5,n_cols=5]]\n"
"2. ARVN[LF=12,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=2;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=7,position=(2,3)],Infantry[infantryType=SPECIALFORCES,quantity=9,weight=6,position=(3,2)],Vehicle[vehicleType=MORTAR,quantity=11,weight=4,position=(4,4)]],battleField=BattleField[n_rows=5,n_cols=5]]\n"
"ARVN defends Liberation:\n"
"After Defense:\n"
"1. LiberationArmy[LF=2,EXP=407,unitList=UnitList[count_vehicle=1;count_infantry=2;Infantry[infantryType=REGULARINFANTRY,quantity=11,weight=5,position=(0,2)],Infantry[infantryType=SNIPER,quantity=12,weight=6,position=(0,0)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(1,1)]],battleField=BattleField[n_rows=5,n_cols=5]]\n"
"2. ARVN[LF=12,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=2;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=7,position=(2,3)],Infantry[infantryType=SPECIALFORCES,quantity=9,weight=6,position=(3,2)],Vehicle[vehicleType=MORTAR,quantity=11,weight=4,position=(4,4)]],battleField=BattleField[n_rows=5,n_cols=5]]\n"
"Applying Battlefield Effects (Round 2):\n"
"After Effects (Round 2):\n"
"1. LiberationArmy[LF=2,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=2;Infantry[infantryType=REGULARINFANTRY,quantity=11,weight=5,position=(0,2)],Infantry[infantryType=SNIPER,quantity=12,weight=6,position=(0,0)],Vehicle[vehicleType=TRUCK,quantity=10,weight=5,position=(1,1)]],battleField=BattleField[n_rows=5,n_cols=5]]\n"
"2. ARVN[LF=12,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=2;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=10,weight=7,position=(2,3)],Infantry[infantryType=SPECIALFORCES,quantity=9,weight=6,position=(3,2)],Vehicle[vehicleType=MORTAR,quantity=11,weight=4,position=(4,4)]],battleField=BattleField[n_rows=5,n_cols=5]]\n";

    //! Cleanup ---------------------------------
    delete libInf1;
    delete libInf2;
    delete libVeh1;
    delete arvnInf1;
    delete arvnInf2;
    delete arvnVeh1;
    delete liber;
    delete arvn;
    delete bf;
    for (auto p : arrayForest) delete p;
    for (auto p : arrayRiver) delete p;
    for (auto p : arrayFortification) delete p;
    for (auto p : arrayUrban) delete p;
    for (auto p : arraySpecialZone) delete p;

   cout << result;
}

void tcvt7() {
    string name = "Task318";
    stringstream output;

    //! Data ------------------------------------
    // Khởi tạo các vector lưu vị trí của từng loại TerrainElement
    vector<Position*> arrayForest;        // Dành cho Mountain
    vector<Position*> arrayRiver;         // River
    vector<Position*> arrayFortification; // Fortification
    vector<Position*> arrayUrban;         // Urban
    vector<Position*> arraySpecialZone;   // SpecialZone

    // Định nghĩa các vị trí trên BattleField 6x6
    // Ví dụ: một vài vị trí cho mỗi loại được đặt rải rác
    arrayForest.push_back(new Position(0, 1));
    arrayForest.push_back(new Position(1, 4));
    
    arrayRiver.push_back(new Position(2, 2));
    arrayRiver.push_back(new Position(3, 3));
    
    arrayFortification.push_back(new Position(4, 0));
    arrayFortification.push_back(new Position(5, 5));
    
    arrayUrban.push_back(new Position(0, 5));
    arrayUrban.push_back(new Position(5, 0));
    
    arraySpecialZone.push_back(new Position(3, 0));
    arraySpecialZone.push_back(new Position(2, 5));

    int n_rows = 6, n_cols = 6;
    // Tạo BattleField với các yếu tố địa hình dựa trên các vector đã khởi tạo
    BattleField* bf = new BattleField(n_rows, n_cols, arrayForest, arrayRiver, arrayFortification, arrayUrban, arraySpecialZone);

    //! Tạo đội quân ------------------------------------
    // Đội quân LiberationArmy với 4 đơn vị:
    // - 2 Infantry đặt tại các vị trí thuộc vùng Mountain (arrayForest)
    // - 1 Vehicle đặt tại vị trí thuộc vùng River (arrayRiver)
    // - 1 Infantry đặt tại vị trí chưa có yếu tố đặc biệt (mặc định là Road)
    Infantry* libInf1 = new Infantry(15, 6, Position(0, 1), SPECIALFORCES);
    Infantry* libInf2 = new Infantry(14, 5, Position(1, 4), REGULARINFANTRY);
    Vehicle* libVeh1 = new Vehicle(12, 5, Position(2, 2), TRUCK);
    Infantry* libInf3 = new Infantry(10, 5, Position(4, 4), SNIPER);  // Vị trí Road
    Unit* unitsLib[4] = { libInf1, libInf2, libVeh1, libInf3 };
    Army* liber = new LiberationArmy(unitsLib, 4, "LibTeam", bf);

    // Đội quân ARVN với 4 đơn vị:
    // - 1 Infantry đặt tại vị trí thuộc Urban (arrayUrban)
    // - 1 Infantry đặt tại vị trí thuộc Fortification (arrayFortification)
    // - 1 Vehicle đặt tại vị trí thuộc SpecialZone (arraySpecialZone)
    // - 1 Vehicle đặt tại vị trí Road
    Infantry* arvnInf1 = new Infantry(13, 5, Position(0, 5), REGULARINFANTRY);
    Infantry* arvnInf2 = new Infantry(12, 6, Position(4, 0), ANTIAIRCRAFTSQUAD);
    Vehicle* arvnVeh1 = new Vehicle(14, 4, Position(3, 0), MORTAR);
    Vehicle* arvnVeh2 = new Vehicle(11, 5, Position(2, 3), TRUCK); // Road
    Unit* unitsArvn[4] = { arvnInf1, arvnInf2, arvnVeh1, arvnVeh2 };
    Army* arvn = new ARVN(unitsArvn, 4, "ARVN_Team", bf);

    //! Process ---------------------------------
    output << "Initial State:" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    // Round 1: Áp dụng hiệu ứng của toàn bộ BattleField
    output << "Applying Battlefield Effects (Round 1):" << endl;
      bf->applyEffect(liber);
   bf->applyEffect(arvn);
    output << "After Effects (Round 1):" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    // Round 2: Giao tranh
    output << "Liberation attacks ARVN (Round 2):" << endl;
    liber->fight(arvn, false);
    output << "After Liberation Attack:" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    output << "ARVN defends Liberation (Round 2):" << endl;
    arvn->fight(liber, true);
    output << "After ARVN Defense:" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    // Round 3: Áp dụng hiệu ứng lại toàn BattleField (có thể giả lập chuyển động hay thay đổi vị trí)
    output << "Applying Battlefield Effects (Round 3):" << endl;
    bf->applyEffect(liber);
   bf->applyEffect(arvn);
    output << "After Effects (Round 3):" << endl;
    output << "1. " << liber->str() << endl;
    output << "2. " << arvn->str() << endl;

    //! Kết quả ---------------------------------
    string result = output.str();
    // Do có tính chất phức tạp của hiệu ứng chồng lấn, sử dụng kết quả thu được làm golden value cho test.
    string expect = "Initial State:\n"
"1. LiberationArmy[LF=2,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=3;Infantry[infantryType=SNIPER,quantity=12,weight=5,position=(4,4)],Infantry[infantryType=REGULARINFANTRY,quantity=14,weight=5,position=(1,4)],Infantry[infantryType=SPECIALFORCES,quantity=15,weight=6,position=(0,1)],Vehicle[vehicleType=TRUCK,quantity=12,weight=5,position=(2,2)]],battleField=BattleField[n_rows=6,n_cols=6]]\n"
"2. ARVN[LF=14,EXP=473,unitList=UnitList[count_vehicle=2;count_infantry=2;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=12,weight=6,position=(4,0)],Infantry[infantryType=REGULARINFANTRY,quantity=13,weight=5,position=(0,5)],Vehicle[vehicleType=MORTAR,quantity=14,weight=4,position=(3,0)],Vehicle[vehicleType=TRUCK,quantity=11,weight=5,position=(2,3)]],battleField=BattleField[n_rows=6,n_cols=6]]\n"
"Applying Battlefield Effects (Round 1):\n"
"After Effects (Round 1):\n"
"1. LiberationArmy[LF=2,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=3;Infantry[infantryType=SNIPER,quantity=12,weight=5,position=(4,4)],Infantry[infantryType=REGULARINFANTRY,quantity=14,weight=5,position=(1,4)],Infantry[infantryType=SPECIALFORCES,quantity=15,weight=6,position=(0,1)],Vehicle[vehicleType=TRUCK,quantity=12,weight=5,position=(2,2)]],battleField=BattleField[n_rows=6,n_cols=6]]\n"
"2. ARVN[LF=14,EXP=500,unitList=UnitList[count_vehicle=2;count_infantry=2;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=12,weight=6,position=(4,0)],Infantry[infantryType=REGULARINFANTRY,quantity=13,weight=5,position=(0,5)],Vehicle[vehicleType=MORTAR,quantity=14,weight=4,position=(3,0)],Vehicle[vehicleType=TRUCK,quantity=11,weight=5,position=(2,3)]],battleField=BattleField[n_rows=6,n_cols=6]]\n"
"Liberation attacks ARVN (Round 2):\n"
"After Liberation Attack:\n"
"1. LiberationArmy[LF=2,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=3;Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(4,4)],Infantry[infantryType=REGULARINFANTRY,quantity=14,weight=5,position=(1,4)],Infantry[infantryType=SPECIALFORCES,quantity=15,weight=6,position=(0,1)],Vehicle[vehicleType=TRUCK,quantity=12,weight=5,position=(2,2)]],battleField=BattleField[n_rows=6,n_cols=6]]\n"
"2. ARVN[LF=14,EXP=500,unitList=UnitList[count_vehicle=2;count_infantry=2;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=12,weight=6,position=(4,0)],Infantry[infantryType=REGULARINFANTRY,quantity=13,weight=5,position=(0,5)],Vehicle[vehicleType=MORTAR,quantity=14,weight=4,position=(3,0)],Vehicle[vehicleType=TRUCK,quantity=11,weight=5,position=(2,3)]],battleField=BattleField[n_rows=6,n_cols=6]]\n"
"ARVN defends Liberation (Round 2):\n"
"After ARVN Defense:\n"
"1. LiberationArmy[LF=2,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=3;Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(4,4)],Infantry[infantryType=REGULARINFANTRY,quantity=14,weight=5,position=(1,4)],Infantry[infantryType=SPECIALFORCES,quantity=15,weight=6,position=(0,1)],Vehicle[vehicleType=TRUCK,quantity=12,weight=5,position=(2,2)]],battleField=BattleField[n_rows=6,n_cols=6]]\n"
"2. ARVN[LF=14,EXP=500,unitList=UnitList[count_vehicle=2;count_infantry=2;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=12,weight=6,position=(4,0)],Infantry[infantryType=REGULARINFANTRY,quantity=13,weight=5,position=(0,5)],Vehicle[vehicleType=MORTAR,quantity=14,weight=4,position=(3,0)],Vehicle[vehicleType=TRUCK,quantity=11,weight=5,position=(2,3)]],battleField=BattleField[n_rows=6,n_cols=6]]\n"
"Applying Battlefield Effects (Round 3):\n"
"After Effects (Round 3):\n"
"1. LiberationArmy[LF=2,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=3;Infantry[infantryType=SNIPER,quantity=11,weight=5,position=(4,4)],Infantry[infantryType=REGULARINFANTRY,quantity=14,weight=5,position=(1,4)],Infantry[infantryType=SPECIALFORCES,quantity=15,weight=6,position=(0,1)],Vehicle[vehicleType=TRUCK,quantity=12,weight=5,position=(2,2)]],battleField=BattleField[n_rows=6,n_cols=6]]\n"
"2. ARVN[LF=14,EXP=500,unitList=UnitList[count_vehicle=2;count_infantry=2;Infantry[infantryType=ANTIAIRCRAFTSQUAD,quantity=12,weight=6,position=(4,0)],Infantry[infantryType=REGULARINFANTRY,quantity=13,weight=5,position=(0,5)],Vehicle[vehicleType=MORTAR,quantity=14,weight=4,position=(3,0)],Vehicle[vehicleType=TRUCK,quantity=11,weight=5,position=(2,3)]],battleField=BattleField[n_rows=6,n_cols=6]]\n";

    //! Cleanup ---------------------------------
    delete libInf1;
    delete libInf2;
    delete libVeh1;
    delete libInf3;
    delete arvnInf1;
    delete arvnInf2;
    delete arvnVeh1;
    delete arvnVeh2;
    delete liber;
    delete arvn;
    delete bf;
    for (auto p : arrayForest) delete p;
    for (auto p : arrayRiver) delete p;
    for (auto p : arrayFortification) delete p;
    for (auto p : arrayUrban) delete p;
    for (auto p : arraySpecialZone) delete p;

   cout << result;
}

void tcvt8() {
    string name = "Task327";
    stringstream output;

    //! Data ------------------------------------
    // Tạo 2 đội quân với các đơn vị đặt ở vị trí khác nhau để thể hiện các trường hợp “gần – xa”

    // Đội ARVN: gồm 2 đơn vị Infantry
    // - inf_ARVN_close: đặt tại vị trí (1,1) → khá gần với một số yếu tố địa hình.
    // - inf_ARVN_far: đặt tại vị trí (5,5) → khá xa với các yếu tố tác động của vài yếu tố.
    Infantry* riNear1 = new Infantry(10, 5, Position(6, 6), REGULARINFANTRY); // Inside urban area
    Infantry* riNear2 = new Infantry(10, 5, Position(10, 6), REGULARINFANTRY); // ~1.4 units away
    Infantry* riFar = new Infantry(10, 5, Position(12, 6), REGULARINFANTRY); // ~2.8 units away
    Infantry* spNear = new Infantry(10, 5, Position(8, 8), SPECIALFORCES); // ~2.8 units away
    Infantry* spFar = new Infantry(10, 5, Position(11, 11), SPECIALFORCES); 
    Vehicle* vehicleInside = new Vehicle(10, 5, Position(6, 6), ARTILLERY); // Inside urban area
    Vehicle* vehicleNearby = new Vehicle(10, 5, Position(8, 6), ARTILLERY); // 2 units away
    Vehicle* vehicleFar = new Vehicle(10, 5, Position(10, 10), ARTILLERY); // ~5.7 units away

    Unit* unitsARVN[8] = { riNear1, riNear2, riFar, spNear, spFar, vehicleInside, vehicleNearby, vehicleFar };
    Army* arvn = new ARVN(unitsARVN, 8, "ARVN", nullptr);

    // Đội LiberationArmy: gồm 2 đơn vị Infantry
    // - inf_Lib_close: đặt tại vị trí (2,2) → gần với một số hiệu ứng đặc biệt.
    // - inf_Lib_far: đặt tại vị trí (6,6) → cách xa hơn so với hiệu ứng của một vài địa hình.
    Infantry* inf_Lib_close = new Infantry(90, 5, Position(2, 2), REGULARINFANTRY);
    Infantry* inf_Lib_far   = new Infantry(90, 5, Position(6, 6), REGULARINFANTRY);
    Infantry* sniper = new Infantry(10, 5, Position(0, 1), SNIPER); // Within radius 2
    Infantry* mortarsquad = new Infantry(6, 7, Position(0, 2), MORTARSQUAD); // Within radius 2
    Infantry* specialforces = new Infantry(4, 9, Position(0, 3), SPECIALFORCES);
    Infantry* regularinfantry = new Infantry(3, 10, Position(0, 3), REGULARINFANTRY);
    Vehicle* antiaircraft = new Vehicle(6, 7, Position(0, 2), ANTIAIRCRAFT); // Within radius 2
    Vehicle* artillery = new Vehicle(3, 10, Position(0, 3), ARTILLERY);
    Vehicle* tank = new Vehicle(2, 11, Position(0, 4), TANK);
    Unit* unitsLib[9] = { inf_Lib_close, inf_Lib_far, sniper, mortarsquad, specialforces, regularinfantry, antiaircraft, artillery, tank };
    Army* liber = new LiberationArmy(unitsLib, 9, "Liberation", nullptr);

    //! Process ------------------------------------
    // Tạo các đối tượng địa hình với vị trí cụ thể.
    // Những địa hình này sẽ được sử dụng để tác động lên các đội quân theo hiệu ứng riêng của từng loại.
    SpecialZone sz(Position(1, 1)); // Những đơn vị có tọa độ trong bán kính 1 tại (1,1) sẽ có attackScore được đặt về 0.
    Mountain mt(Position(2, 2));     // Hiệu ứng tăng EXP của infantry và giảm LF của phương tiện (ở khoảng cách ảnh hưởng).
    River rv(Position(3, 3));        // Hiệu ứng giảm 10% attackScore đối với infantry nếu ở trong bán kính 2.
    Urban ur(Position(4, 4));        // Hiệu ứng thay đổi attackScore tùy theo loại quân và khoảng cách.

    // Áp dụng hiệu ứng của tất cả các loại địa hình lên ARVN
    mt.getEffect(arvn);
    rv.getEffect(arvn);
    ur.getEffect(arvn);
    sz.getEffect(arvn);

    // Áp dụng hiệu ứng của tất cả các loại địa hình lên LiberationArmy
    mt.getEffect(liber);
    rv.getEffect(liber);
    ur.getEffect(liber);
    sz.getEffect(liber);

    // Ghi nhận thông tin kết quả sau khi các hiệu ứng được áp dụng
    output << "3Que: " << arvn->str() << "\n";
    output << "VietNam: " << liber->str() << "\n";

    string result = output.str();
    string expect = 
"3Que: ARVN[LF=159,EXP=500,unitList=UnitList[count_vehicle=1;count_infantry=2;Infantry[infantryType=SPECIALFORCES,quantity=24,weight=5,position=(8,8)],Infantry[infantryType=REGULARINFANTRY,quantity=27,weight=5,position=(6,6)],Vehicle[vehicleType=ARTILLERY,quantity=30,weight=5,position=(6,6)]],battleField=]\n"
"VietNam: LiberationArmy[LF=134,EXP=500,unitList=UnitList[count_vehicle=3;count_infantry=4;Infantry[infantryType=SPECIALFORCES,quantity=4,weight=9,position=(0,3)],Infantry[infantryType=MORTARSQUAD,quantity=6,weight=7,position=(0,2)],Infantry[infantryType=SNIPER,quantity=12,weight=5,position=(0,1)],Infantry[infantryType=REGULARINFANTRY,quantity=221,weight=10,position=(2,2)],Vehicle[vehicleType=ANTIAIRCRAFT,quantity=6,weight=7,position=(0,2)],Vehicle[vehicleType=ARTILLERY,quantity=3,weight=10,position=(0,3)],Vehicle[vehicleType=TANK,quantity=2,weight=11,position=(0,4)]],battleField=]\n";

    //! Cleanup ------------------------------------
    for (auto p : unitsARVN) delete p;
    for (auto p : unitsLib) delete p;
    delete arvn;
    delete liber;
    
  cout << result;
}
void Task4209()
{
    string name = "Task209";
    //! data ------------------------------------
    Vehicle v1(3, 10, Position(1,1), TRUCK);    
    Infantry i1(4, 12, Position(1,2), SNIPER);   

    Unit* unitArray1[2];
    unitArray1[0] = &v1;
    unitArray1[1] = &i1;
    LiberationArmy* attacker = new LiberationArmy(unitArray1, 2, "TestArmy209",0);
    
    Vehicle v2(3, 3, Position(3,1), TANK);  
    Infantry i3(3, 30, Position(3,2), SNIPER); 

    Unit* unitArray2[2];
    unitArray2[0] = &v2;
    unitArray2[1] = &i3;
    Army* enemy = new ARVN(unitArray2, 2, "EnemyArmy209",0);
    cout << attacker->getEXP();
    //! process ---------------------------------
    attacker->fight(enemy, false);
    string result = "New_LF = " + to_string(attacker->getLF()) + "\nNew_EXP = " + to_string(attacker->getEXP());

    //! expect ----------------------------------
    string expect = "New_LF = 1\nNew_EXP = 44";

    //! output ----------------------------------
    stringstream output;
    output << result;
    
    //! remove data -----------------------------
    delete attacker;
    delete enemy;
    
    //! result ----------------------------------
    cout << output.str();
}

int main(int argc, const char * argv[]) {
  //   testUnitclass();
   //  testUnitListclass();
   
   Task4209();
    return 0;
}
