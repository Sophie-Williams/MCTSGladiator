#pragma once
#include <BWAPI.h>
#include <vector>
#include "State.h"
#include "Action.h"

namespace MCTSG
{
	// the type of the node in sequence
	enum UCTNodeTypes
	{
		FIRST, // first node of simultaneous moves; wait for second node to update together (ally)
		SECOND, // second node of sumultaneous moves (enemy)
		SOLO // the only player can move at this time
	};

	class UCTNode
	{

		UCTNodeTypes _type; // the type of the node in sequence
		Move _move; // action vector; the move which generates this node from parent node

		int _visits, _wins; // number of visits and wins
		double _score; // score of this node (evaluation)

		std::vector<UCTNode*> _vecChildren; // children nodes
		UCTNode *_parent; // parent node

	public:

		UCTNode();
		UCTNode(UCTNodeTypes type, Move move);

		void visit() { _visits++; };
		void addChild(UCTNode *child);
		void updateWin(const int result) { _wins += result; };
		void updateScore(const double result) { _score = result; };

		std::string toString() const; // convert node type to string

		// condition
		bool isRoot() const { return _parent == NULL ? true : false; };

		// getters
		Move getMove() const { return _move; };
		UCTNodeTypes getNodeType() const { return _type; };

		int getNumVisits() const { return _visits; };
		int getNumWins() const { return _wins; };
		double getWinRate() const { return _visits > 0 ? (double)_wins / _visits : 0; };
		double getScore() const { return _score; };

		bool hasChildren() const { return _vecChildren.empty() ? false : true; };
		std::vector<UCTNode*> getChildren() const { return _vecChildren; };
		UCTNode* getParent() const { return _parent; };
	};
}