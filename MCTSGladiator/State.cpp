#include "State.h"

using namespace MCTSG;

State::State()
{
	clear();
}

void State::clear()
{
	time = 0;
	allyUnits.clear();
	enemyUnits.clear();
}

void State::set(const int t, const BWAPI::Unitset &allies, const BWAPI::Unitset &enemies)
{
	// reset
	clear();

	// time frame
	time = t;

	// convert BWAPI units to MCTSG units
	setUnits(allyUnits, allies);
	setUnits(enemyUnits, enemies);
}

void State::setUnits(std::vector<Unit> &vecUnits, const BWAPI::Unitset &unitset)
{
	for(auto &u : unitset) // enemy
	{
		if(u->exists()
			&& !u->getType().isWorker()
			&& !(u->getType() == BWAPI::UnitTypes::Special_Map_Revealer))
		{
			// convert and append
			Unit unit = Unit(u);
			vecUnits.push_back(unit);
		}
	}
}

void State::update(const int t, const BWAPI::Unitset &allies, const BWAPI::Unitset &enemies)
{
	// new time frame
	time = t;

	// update unitsets
	updateUnits(allyUnits, allies);
	updateUnits(enemyUnits, enemies);
}

void State::updateUnits(std::vector<Unit> &vecUnits, const BWAPI::Unitset &unitset)
{
	// update new units status from real state (except for tAttack, tMove)
	for(std::vector<Unit>::iterator itr = vecUnits.begin();
		itr != vecUnits.end();
		itr++)
	{
		bool isFound = false;
		for(auto &real_u : unitset)
		{
			if(real_u->getID() == itr->ID)
			{
				itr->update(real_u);
				isFound = true;
				break;
			}
		}

		// not found, this unit is dead
		if(!isFound)
		{
			// remove it from the vector
			//vecUnits.erase(itr); // TODO: bug
		}
	}
}