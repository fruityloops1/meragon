#pragma once

#include "al/LiveActor/LiveActor.h"
#include "sead/math/seadVector.h"

class PlayerActor : public al::LiveActor {
    u8 unk[0x16];

public:
    struct Player {
        struct PlayerProperty {
            sead::Vector3f trans;
        } * mPlayerProperty;
    } * mPlayer;

private:
    u8 unk2[0xe4];
};