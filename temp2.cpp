#include "ARVN.h"
#include <sstream>
#include <algorithm>

// Constructor
ARVN::ARVN(const Unit** unitArray, int size, std::string name, BattleField* battleField)
    : name(name), LF(0), EXP(0), battleField(battleField) {
    for (int i = 0; i < size; ++i) {
        unitList.push_back(const_cast<Unit*>(unitArray[i]));
    }
    updateCombatIndices();
}

// Helper method: Update combat indices (LF and EXP)
void ARVN::updateCombatIndices() {
    LF = 0;
    EXP = 0;
    for (Unit* unit : unitList) {
        LF += unit->getAttackScore();
        EXP += unit->getExperience();
    }
}

// Helper method: Remove units with quantity = 1
void ARVN::removeUnitsWithQuantityOne() {
    unitList.erase(std::remove_if(unitList.begin(), unitList.end(),
        [](Unit* unit) { return unit->getQuantity() <= 1; }),
        unitList.end());
}

// Helper method: Reduce unit quantities by a percentage
void ARVN::reduceUnitQuantitiesByPercentage(double percentage) {
    for (Unit* unit : unitList) {
        unit->reduceQuantityByPercentage(percentage);
    }
    removeUnitsWithQuantityOne();
    updateCombatIndices();
}

// Helper method: Reduce unit weights by a percentage
void ARVN::reduceUnitWeightsByPercentage(double percentage) {
    for (Unit* unit : unitList) {
        unit->reduceWeightByPercentage(percentage);
    }
    updateCombatIndices();
}

// Fight method
void ARVN::fight(Army* enemy, bool defense) {
    if (defense) {
        // Defense case
        if (enemy->getLF() > LF || enemy->getEXP() > EXP) {
            // Liberation Army wins, confiscate ARVN units
            enemy->confiscateUnits(this);

            // Remaining ARVN units suffer a 20% reduction in weight
            reduceUnitWeightsByPercentage(20);
        }
    } else {
        // Attack case
        // ARVN loses the battle
        reduceUnitQuantitiesByPercentage(20);
    }
}

// String representation
std::string ARVN::str() const {
    std::ostringstream oss;
    oss << "ARVN["
        << "name=" << name << ", "
        << "LF=" << LF << ", "
        << "EXP=" << EXP << ", "
        << "unitList=" << unitListToString() << ", "
        << "battleField=" << battleField->str()
        << "]";
    return oss.str();
}