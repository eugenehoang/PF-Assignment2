#include "LiberationArmy.h"
#include <sstream>
#include <cmath>
#include <algorithm>

// Constructor
LiberationArmy::LiberationArmy(const Unit** unitArray, int size, std::string name, BattleField* battleField)
    : name(name), LF(0), EXP(0), battleField(battleField) {
    for (int i = 0; i < size; ++i) {
        unitList.push_back(const_cast<Unit*>(unitArray[i]));
    }
    updateCombatIndices();
}

// Helper method: Find the smallest combination of units with a total score greater than the target
std::vector<Unit*> LiberationArmy::findCombination(const std::vector<Unit*>& units, double targetScore) {
    std::vector<Unit*> bestCombination;
    double bestScore = std::numeric_limits<double>::max();

    int n = units.size();
    for (int i = 1; i < (1 << n); ++i) { // Iterate through all subsets
        std::vector<Unit*> combination;
        double totalScore = 0;

        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) { // If j-th bit is set, include the unit
                combination.push_back(units[j]);
                totalScore += units[j]->getAttackScore();
            }
        }

        if (totalScore > targetScore && totalScore < bestScore) {
            bestCombination = combination;
            bestScore = totalScore;
        }
    }

    return bestCombination;
}

// Helper method: Update combat indices (LF and EXP)
void LiberationArmy::updateCombatIndices() {
    LF = 0;
    EXP = 0;
    for (Unit* unit : unitList) {
        LF += unit->getAttackScore();
        EXP += unit->getExperience();
    }
}

// Helper method: Confiscate enemy units
void LiberationArmy::confiscateUnits(Army* enemy) {
    for (Unit* unit : enemy->getUnitList()) {
        auto it = std::find_if(unitList.begin(), unitList.end(), [&](Unit* u) {
            return u->getType() == unit->getType();
        });

        if (it != unitList.end()) {
            (*it)->increaseQuantity(unit->getQuantity());
        } else {
            unitList.push_back(unit);
        }
    }
    updateCombatIndices();
}

// Fight method
void LiberationArmy::fight(Army* enemy, bool defense) {
    if (defense) {
        // Defense case
        LF *= 1.3;
        EXP *= 1.3;

        if (LF >= enemy->getLF() && EXP >= enemy->getEXP()) {
            // Victory
            confiscateUnits(enemy);
        } else if (LF < enemy->getLF() || EXP < enemy->getEXP()) {
            // Suffer 10% reduction in quantity
            for (Unit* unit : unitList) {
                unit->reduceQuantityByPercentage(10);
            }
            updateCombatIndices();
        } else {
            // Reinforcements: Increase quantity to nearest Fibonacci number
            for (Unit* unit : unitList) {
                unit->increaseQuantityToNearestFibonacci();
            }
            updateCombatIndices();
        }
    } else {
        // Attack case
        LF *= 1.5;
        EXP *= 1.5;

        auto infantryUnits = filterUnitsByType(unitList, INFANTRY);
        auto vehicleUnits = filterUnitsByType(unitList, VEHICLE);

        auto combinationA = findCombination(infantryUnits, enemy->getEXP());
        auto combinationB = findCombination(vehicleUnits, enemy->getLF());

        if (!combinationA.empty() && !combinationB.empty()) {
            // Victory
            removeUnits(combinationA);
            removeUnits(combinationB);
            confiscateUnits(enemy);
        } else if (!combinationA.empty() || !combinationB.empty()) {
            // Stalemate
            if (!combinationA.empty()) {
                if (calculateCombatIndex(vehicleUnits) > enemy->getLF()) {
                    removeUnits(combinationA);
                    removeUnits(vehicleUnits);
                    confiscateUnits(enemy);
                }
            } else if (!combinationB.empty()) {
                if (calculateCombatIndex(infantryUnits) > enemy->getEXP()) {
                    removeUnits(combinationB);
                    removeUnits(infantryUnits);
                    confiscateUnits(enemy);
                }
            }
        } else {
            // No battle occurs
            for (Unit* unit : unitList) {
                unit->reduceWeightByPercentage(10);
            }
            updateCombatIndices();
        }
    }
}

// String representation
std::string LiberationArmy::str() const {
    std::ostringstream oss;
    oss << "LiberationArmy["
        << "name=" << name << ", "
        << "LF=" << LF << ", "
        << "EXP=" << EXP << ", "
        << "unitList=" << unitListToString() << ", "
        << "battleField=" << battleField->str()
        << "]";
    return oss.str();
}