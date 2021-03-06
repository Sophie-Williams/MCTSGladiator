#include "UCTNode.h"

using namespace MCTSG;

UCTNode::UCTNode()
	:_type(UCTNodeTypes::SOLO),
	_move(Move()),
	_visits(0),
	_wins(0),
	_score(-99999), // -Inf
	_parent(NULL)
{
	// to be root
}

UCTNode::UCTNode(UCTNodeTypes type, Move move)
	:_type(type),
	_move(move),
	_visits(0),
	_wins(0),
	_score(-99999), // -Inf
	_parent(NULL)
{
	
}

void UCTNode::addChild(UCTNode *child)
{
	// set this node as parent
	child->_parent = this;

	// add the child to this node
	_vecChildren.push_back(child);
}

std::string UCTNode::toString() const
{
	switch(_type)
	{
		case UCTNodeTypes::FIRST:
			return "FIRST";
			break;

		case UCTNodeTypes::SECOND:
			return "SECOND";
			break;

		case UCTNodeTypes::SOLO:
			return "SOLO";
			break;

		default:
			return "ERROR: Invalid node type!";
			break;
	}
}