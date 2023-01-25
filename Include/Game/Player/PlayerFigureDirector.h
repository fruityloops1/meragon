#pragma once

enum EPlayerFigure {
    EPlayerFigure_Normal,
    EPlayerFigure_Mini,
    EPlayerFigure_Fire,
    EPlayerFigure_RaccoonDog,
    EPlayerFigure_Boomerang,
    EPlayerFigure_RaccoonDogSpecial,
    EPlayerFigure_RaccoonDogWhite

};

class PlayerFigureDirector {
    int _0;
    EPlayerFigure mFigure;
    void* _8;
    void* _C;
    int _10;
    void* _14;

public:
    void change(const EPlayerFigure&);
    void lose();

    EPlayerFigure getFigure() const { return mFigure; }
};
