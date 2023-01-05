#pragma once

#include "Game/Player/PlayerActionNode.h"

class PlayerActionGraph {
public:
    PlayerActionNode* mCurrentNode;

    PlayerActionNode* getCurrentNode() const { return mCurrentNode; }

    void move();
};
