#pragma once
#include <stdio.h>

#define GRID_SLICES 15

struct Circle
{
    bool placed = false;
    bool isBlack = true;
};

class Game
{
private:
    enum Direction
    {
        Row,
        Column,
        WestDiagonal,
        EastDiagonal
    };

    enum Rule
    {
        Rule33v1,
        Rule33v2,
        Rule6
    };

    enum Scene
    {
        Start,
        Room,
        InGame,
        Chat,
        Setting,
        GameOver
    };

    // check gameover
    bool check(int m, int n, Direction dir, int norm = 5);

    // check rule (33, 6)
    bool check(int m, int n, Rule rule);

public:
    Circle circles[GRID_SLICES][GRID_SLICES];

	Game() 
    {
        // @TODO make Game class as singletone
    }

    bool CheckGameOver(int m, int n)
    {
        //return check(m, n, Row) ||
        //    check(m, n, Column) ||
        //    check(m, n, WestDiagonal) ||
        //    check(m, n, EastDiagonal);
        bool res = check(m, n, Row) ||
            check(m, n, Column) ||
            check(m, n, WestDiagonal) ||
            check(m, n, EastDiagonal);
        if (res) printf("GameOver\n");

        return res;
    }

    bool CheckRule(int m, int n)
    {
        bool res33 = check(m, n, Rule33v1);
        if (res33) printf("Rule33\n");

        bool res6 = check(m, n, Rule6);
        if (res6) printf("Rule6\n");

        return res33 || res6;
        //return check(m, n, Rule33);
        //return check(m, n, Rule6); // gameover == Rule6 fail
        //return check(m, n, Rule33) || check(m, n, Rule6);
    }
};
