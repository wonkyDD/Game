#ifndef GAME_H
#define GAME_H

#define GRID_SLICES 15

struct Circle
{
    bool placed = false;
    bool isBlack = true;
};

class Game
{
public:
    Circle circles[GRID_SLICES][GRID_SLICES];

	Game() 
    {
        // @TODO make Game class as singletone
    }

    void checkGameOver()
    {

    }

    void checkRule()
    {
        // @TODO research what is renzurule exactly
    }
};

#endif // GAME_H