#include "game.h"
#include <cassert>

bool Game::check(int m, int n, Direction dir, int norm)
{
    switch (dir)
    {
    case Game::Row:
    {
        int cnt = 1;
        int left = n - 1, right = n + 1;

        while (left >= 0 &&
            circles[m][left].placed &&
            circles[m][n].isBlack == circles[m][left].isBlack)
        {
            --left;
            ++cnt;
        }
        while (right < GRID_SLICES &&
            circles[m][right].placed &&
            circles[m][n].isBlack == circles[m][right].isBlack)
        {
            ++right;
            ++cnt;
        }

        return cnt == norm;
    }
    break;
    case Game::Column:
    {
        int cnt = 1;
        int top = m - 1, bottom = m + 1;

        while (top >= 0 &&
            circles[top][n].placed &&
            circles[m][n].isBlack == circles[top][n].isBlack)
        {
            --top;
            ++cnt;
        }
        while (bottom < GRID_SLICES &&
            circles[bottom][n].placed &&
            circles[m][n].isBlack == circles[bottom][n].isBlack)
        {
            ++bottom;
            ++cnt;
        }

        return cnt == norm;
    }
    break;
    case Game::WestDiagonal:
    {
        int cnt = 1;
        int mTopLeft = m - 1, nTopLeft = n - 1;
        int mBottomRight = m + 1, nBottomRight = n + 1;

        while (mTopLeft >= 0 &&
            nTopLeft >= 0 &&
            circles[mTopLeft][nTopLeft].placed &&
            circles[m][n].isBlack == circles[mTopLeft][nTopLeft].isBlack)
        {
            --mTopLeft; --nTopLeft;
            ++cnt;
        }
        while (mBottomRight < GRID_SLICES &&
            nBottomRight < GRID_SLICES &&
            circles[mBottomRight][nBottomRight].placed &&
            circles[m][n].isBlack == circles[mBottomRight][nBottomRight].isBlack)
        {
            ++mBottomRight; ++nBottomRight;
            ++cnt;
        }

        return cnt == norm;
    }
    break;
    case Game::EastDiagonal:
    {
        int cnt = 1;
        int mTopRight = m - 1, nTopRight = n + 1;
        int mBottomLeft = m + 1, nBottomLeft = n - 1;

        while (mTopRight >= 0 &&
            nTopRight < GRID_SLICES &&
            circles[mTopRight][nTopRight].placed &&
            circles[m][n].isBlack == circles[mTopRight][nTopRight].isBlack)
        {
            --mTopRight; ++nTopRight;
            ++cnt;
        }
        while (mBottomLeft < GRID_SLICES &&
            nBottomLeft >= 0 &&
            circles[mBottomLeft][nBottomLeft].placed &&
            circles[m][n].isBlack == circles[mBottomLeft][nBottomLeft].isBlack)
        {
            ++mBottomLeft; --nBottomLeft;
            ++cnt;
        }

        return cnt == norm;
    }
    break;
    default:
        break;
    }

    // @TODO  warning C4715:'Game::check': not all control paths return a value
    assert(false);
    return false;
}

bool Game::check(int m, int n, Rule rule)
{
    switch (rule)
    {
    case Game::Rule33v1:
    {
        bool placed, isBlack;
        int ruleVal = 0;

        // row
        for (int i = -3; i <= 0; ++i)
        {
            int cnt = 0;
            bool over = false;
            for (int j = 0; j < 4; ++j)
            {
                if (n + i + j < 0 || n + i + j >= GRID_SLICES)
                {
                    over = true;
                    break;
                }

                placed = circles[m][n + i + j].placed;
                isBlack = circles[m][n + i + j].isBlack;
                if (n + i + j == n || (placed && isBlack)) ++cnt;
                else if (placed && !isBlack) --cnt;
            }

            if (!over && cnt == 3)
            {
                bool t = false;
                switch (i)
                {
                case -3:
                {
                    bool b = circles[m][n - 3].placed &&
                        circles[m][n - 2].placed &&
                        n - 4 >= 0 &&
                        !circles[m][n - 4].placed &&
                        n + 1 < GRID_SLICES &&
                        !circles[m][n + 1].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m][n - 3].placed &&
                        circles[m][n - 1].placed &&
                        n - 4 >= 0 &&
                        !circles[m][n - 4].placed &&
                        n + 1 < GRID_SLICES &&
                        !circles[m][n + 1].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m][n - 2].placed &&
                        circles[m][n - 1].placed &&
                        n - 3 >= 0 &&
                        !circles[m][n - 3].placed &&
                        n + 1 < GRID_SLICES &&
                        !circles[m][n + 1].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                case -2:
                {
                    bool b = circles[m][n - 2].placed &&
                        circles[m][n - 1].placed &&
                        n - 3 >= 0 &&
                        !circles[m][n - 3].placed &&
                        n + 1 < GRID_SLICES &&
                        !circles[m][n + 1].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m][n - 2].placed &&
                        circles[m][n + 1].placed &&
                        n - 3 >= 0 &&
                        !circles[m][n - 3].placed &&
                        n + 2 < GRID_SLICES &&
                        !circles[m][n + 2].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m][n - 1].placed &&
                        circles[m][n + 1].placed &&
                        n - 2 >= 0 &&
                        !circles[m][n - 2].placed &&
                        n + 2 < GRID_SLICES &&
                        !circles[m][n + 2].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                case -1:
                {
                    bool b = circles[m][n - 1].placed &&
                        circles[m][n + 1].placed &&
                        n - 2 >= 0 &&
                        !circles[m][n - 2].placed &&
                        n + 2 < GRID_SLICES &&
                        !circles[m][n + 2].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m][n - 1].placed &&
                        circles[m][n + 2].placed &&
                        n - 2 >= 0 &&
                        !circles[m][n - 2].placed &&
                        n + 3 < GRID_SLICES &&
                        !circles[m][n + 3].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m][n + 1].placed &&
                        circles[m][n + 2].placed &&
                        n - 1 >= 0 &&
                        !circles[m][n - 1].placed &&
                        n + 3 < GRID_SLICES &&
                        !circles[m][n + 3].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                case 0:
                {
                    bool b = circles[m][n + 1].placed &&
                        circles[m][n + 2].placed &&
                        n - 1 >= 0 &&
                        !circles[m][n - 1].placed &&
                        n + 3 < GRID_SLICES &&
                        !circles[m][n + 3].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m][n + 1].placed &&
                        circles[m][n + 3].placed &&
                        n - 1 >= 0 &&
                        !circles[m][n - 1].placed &&
                        n + 4 < GRID_SLICES &&
                        !circles[m][n + 4].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m][n + 2].placed &&
                        circles[m][n + 3].placed &&
                        n - 1 >= 0 &&
                        !circles[m][n - 1].placed &&
                        n + 4 < GRID_SLICES &&
                        !circles[m][n + 4].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                default:
                    break;
                }

                if (t) break;
            }
        }

        // column
        for (int i = -3; i <= 0; ++i)
        {
            int cnt = 0;
            bool over = false;
            for (int j = 0; j < 4; ++j)
            {
                if (m + i + j < 0 || m + i + j >= GRID_SLICES)
                {
                    over = true;
                    break;
                }

                placed = circles[m + i + j][n].placed;
                isBlack = circles[m + i + j][n].isBlack;
                if (m + i + j == m || (placed && isBlack)) ++cnt;
                else if (placed && !isBlack) --cnt;
            }

            if (!over && cnt == 3)
            {
                bool t = false;
                switch (i)
                {
                case -3:
                {
                    bool b = circles[m - 3][n].placed &&
                        circles[m - 2][n].placed &&
                        m - 4 >= 0 &&
                        !circles[m - 4][n].placed &&
                        m + 1 < GRID_SLICES &&
                        !circles[m + 1][n].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m - 3][n].placed &&
                        circles[m - 1][n].placed &&
                        m - 4 >= 0 &&
                        !circles[m - 4][n].placed &&
                        m + 1 < GRID_SLICES &&
                        !circles[m + 1][n].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m - 2][n].placed &&
                        circles[m - 1][n].placed &&
                        m - 3 >= 0 &&
                        !circles[m - 3][n].placed &&
                        m + 1 < GRID_SLICES &&
                        !circles[m + 1][n].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                case -2:
                {
                    bool b = circles[m - 2][n].placed &&
                        circles[m - 1][n].placed &&
                        m - 3 >= 0 &&
                        !circles[m - 3][n].placed &&
                        m + 1 < GRID_SLICES &&
                        !circles[m + 1][n].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m - 2][n].placed &&
                        circles[m + 1][n].placed &&
                        m - 3 >= 0 &&
                        !circles[m - 3][n].placed &&
                        m + 2 < GRID_SLICES &&
                        !circles[m + 2][n].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m - 1][n].placed &&
                        circles[m + 1][n].placed &&
                        m - 2 >= 0 &&
                        !circles[m - 2][n].placed &&
                        m + 2 < GRID_SLICES &&
                        !circles[m + 2][n].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                case -1:
                {
                    bool b = circles[m - 1][n].placed &&
                        circles[m + 1][n].placed &&
                        m - 2 >= 0 &&
                        !circles[m - 2][n].placed &&
                        m + 2 < GRID_SLICES &&
                        !circles[m + 2][n].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m - 1][n].placed &&
                        circles[m + 2][n].placed &&
                        m - 2 >= 0 &&
                        !circles[m - 2][n].placed &&
                        m + 3 < GRID_SLICES &&
                        !circles[m + 3][n].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m + 1][n].placed &&
                        circles[m + 2][n].placed &&
                        m - 1 >= 0 &&
                        !circles[m - 1][n].placed &&
                        m + 3 < GRID_SLICES &&
                        !circles[m + 3][n].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                case 0:
                {
                    bool b = circles[m + 1][n].placed &&
                        circles[m + 2][n].placed &&
                        m - 1 >= 0 &&
                        !circles[m - 1][n].placed &&
                        m + 3 < GRID_SLICES &&
                        !circles[m + 3][n].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m + 1][n].placed &&
                        circles[m + 3][n].placed &&
                        m - 1 >= 0 &&
                        !circles[m - 1][n].placed &&
                        m + 4 < GRID_SLICES &&
                        !circles[m + 4][n].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m + 2][n].placed &&
                        circles[m + 3][n].placed &&
                        m - 1 >= 0 &&
                        !circles[m - 1][n].placed &&
                        m + 4 < GRID_SLICES &&
                        !circles[m + 4][n].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                default:
                    break;
                }

                if (t) break;
            }
        }
        if (ruleVal == 2) return true;

        // west diagonal
        for (int i = -3; i <= 0; ++i)
        {
            int cnt = 0;
            bool over = false;
            for (int j = 0; j < 4; ++j)
            {
                if ((m + i + j < 0 || m + i + j >= GRID_SLICES) ||
                    (n + i + j < 0 || n + i + j >= GRID_SLICES))
                {
                    over = true;
                    break;
                }

                placed = circles[m + i + j][n + i + j].placed;
                isBlack = circles[m + i + j][n + i + j].isBlack;
                if ((m + i + j == m && n + i + j == n) || (placed && isBlack)) ++cnt;
                else if (placed && !isBlack) --cnt;
            }

            if (!over && cnt == 3)
            {
                bool t = false;
                switch (i)
                {
                case -3:
                {
                    bool b = circles[m - 3][n - 3].placed &&
                        circles[m - 2][n - 2].placed &&
                        (m - 4 >= 0 && n - 4 >= 0) &&
                        !circles[m - 4][n - 4].placed &&
                        (m + 1 < GRID_SLICES && n + 1 < GRID_SLICES) &&
                        !circles[m + 1][n + 1].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m - 3][n - 3].placed &&
                        circles[m - 1][n - 1].placed &&
                        (m - 4 >= 0 && n - 4 >= 0) &&
                        !circles[m - 4][n - 4].placed &&
                        (m + 1 < GRID_SLICES && n + 1 < GRID_SLICES) &&
                        !circles[m + 1][n + 1].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m - 2][n - 2].placed &&
                        circles[m - 1][n - 1].placed &&
                        (m - 3 >= 0 && n - 3 >= 0) &&
                        !circles[m - 3][n - 3].placed &&
                        (m + 1 < GRID_SLICES && n + 1 < GRID_SLICES) &&
                        !circles[m + 1][n + 1].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                case -2:
                {
                    bool b = circles[m - 2][n - 2].placed &&
                        circles[m - 1][n - 1].placed &&
                        (m - 3 >= 0 && n - 3 >= 0) &&
                        !circles[m - 3][n - 3].placed &&
                        (m + 1 < GRID_SLICES && n + 1 < GRID_SLICES) &&
                        !circles[m + 1][n + 1].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m - 2][n - 2].placed &&
                        circles[m + 1][n + 1].placed &&
                        (m - 3 >= 0 && n - 3 >= 0) &&
                        !circles[m - 3][n - 3].placed &&
                        (m + 2 < GRID_SLICES && n + 2 < GRID_SLICES) &&
                        !circles[m + 2][n + 2].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m - 1][n - 1].placed &&
                        circles[m + 1][n + 1].placed &&
                        (m - 2 >= 0 && n - 2 >= 0) &&
                        !circles[m - 2][n - 2].placed &&
                        (m + 2 < GRID_SLICES && n + 2 < GRID_SLICES) &&
                        !circles[m + 2][n + 2].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                case -1:
                {
                    bool b = circles[m - 1][n - 1].placed &&
                        circles[m + 1][n + 1].placed &&
                        (m - 2 >= 0 && n - 2 >= 0) &&
                        !circles[m - 2][n - 2].placed &&
                        (m + 2 < GRID_SLICES && n + 2 < GRID_SLICES) &&
                        !circles[m + 2][n + 2].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m - 1][n - 1].placed &&
                        circles[m + 2][n + 2].placed &&
                        (m - 2 >= 0 && n - 2 >= 0) &&
                        !circles[m - 2][n - 2].placed &&
                        (m + 3 < GRID_SLICES && n + 3 < GRID_SLICES) &&
                        !circles[m + 3][n + 3].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m + 1][n + 1].placed &&
                        circles[m + 2][n + 2].placed &&
                        (m - 1 >= 0 && n - 1 >= 0) &&
                        !circles[m - 1][n - 1].placed &&
                        (m + 3 < GRID_SLICES && n + 3 < GRID_SLICES) &&
                        !circles[m + 3][n + 3].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                case 0:
                {
                    bool b = circles[m + 1][n + 1].placed &&
                        circles[m + 2][n + 2].placed &&
                        (m - 1 >= 0 && n - 1 >= 0) &&
                        !circles[m - 1][n - 1].placed &&
                        (m + 3 < GRID_SLICES && n + 3 < GRID_SLICES) &&
                        !circles[m + 3][n + 3].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m + 1][n + 1].placed &&
                        circles[m + 3][n + 3].placed &&
                        (m - 1 >= 0 && n - 1 >= 0) &&
                        !circles[m - 1][n - 1].placed &&
                        (m + 4 < GRID_SLICES && n + 4 < GRID_SLICES) &&
                        !circles[m + 4][n + 4].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m + 2][n + 2].placed &&
                        circles[m + 3][n + 3].placed &&
                        (m - 1 >= 0 && n - 1 >= 0) &&
                        !circles[m - 1][n - 1].placed &&
                        (m + 4 < GRID_SLICES && n + 4 < GRID_SLICES) &&
                        !circles[m + 4][n + 4].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                default:
                    break;
                }

                if (t) break;
            }
        }
        if (ruleVal == 2) return true;

        // east diagonal
        for (int i = -3; i <= 0; ++i)
        {
            int cnt = 0;
            bool over = false;
            for (int j = 0; j < 4; ++j)
            {
                if ((m - i + j < 0 || m - i + j >= GRID_SLICES) ||
                    (n + i + j < 0 || n + i + j >= GRID_SLICES))
                {
                    over = true;
                    break;
                }

                placed = circles[m - i + j][n + i + j].placed;
                isBlack = circles[m - i + j][n + i + j].isBlack;
                if ((m - i + j == m && n + i + j == n) || (placed && isBlack)) ++cnt;
                else if (placed && !isBlack) --cnt;
            }
            if (!over && cnt == 3)
            {
                bool t = false;
                switch (i)
                {
                case -3:
                {
                    bool b = circles[m + 3][n - 3].placed &&
                        circles[m + 2][n - 2].placed &&
                        (m + 4 < GRID_SLICES && n - 4 >= 0) &&
                        !circles[m + 4][n - 4].placed &&
                        (m - 1 >= 0 && n + 1 < GRID_SLICES) &&
                        !circles[m - 1][n + 1].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m + 3][n - 3].placed &&
                        circles[m + 1][n - 1].placed &&
                        (m + 4 < GRID_SLICES && n - 4 >= 0) &&
                        !circles[m + 4][n - 4].placed &&
                        (m - 1 >= 0 && n + 1 < GRID_SLICES) &&
                        !circles[m - 1][n + 1].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m + 2][n - 2].placed &&
                        circles[m + 1][n - 1].placed &&
                        (m + 3 < GRID_SLICES && n - 3 >= 0) &&
                        !circles[m + 3][n - 3].placed &&
                        (m - 1 >= 0 && n + 1 < GRID_SLICES) &&
                        !circles[m - 1][n + 1].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                case -2:
                {
                    bool b = circles[m + 2][n - 2].placed &&
                        circles[m + 1][n - 1].placed &&
                        (m + 3 < GRID_SLICES && n - 3 >= 0) &&
                        !circles[m + 3][n - 3].placed &&
                        (m - 1 >= 0 && n + 1 < GRID_SLICES) &&
                        !circles[m - 1][n + 1].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m + 2][n - 2].placed &&
                        circles[m - 1][n + 1].placed &&
                        (m + 3 < GRID_SLICES && n - 3 >= 0) &&
                        !circles[m + 3][n - 3].placed &&
                        (m - 2 >= 0 && n + 2 < GRID_SLICES) &&
                        !circles[m - 2][n + 2].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m + 1][n - 1].placed &&
                        circles[m - 1][n + 1].placed &&
                        (m + 2 < GRID_SLICES && n - 2 >= 0) &&
                        !circles[m + 2][n - 2].placed &&
                        (m - 2 >= 0 && n + 2 < GRID_SLICES) &&
                        !circles[m - 2][n + 2].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                case -1:
                {
                    bool b = circles[m + 1][n - 1].placed &&
                        circles[m - 1][n + 1].placed &&
                        (m + 2 < GRID_SLICES && n - 2 >= 0) &&
                        !circles[m + 2][n - 2].placed &&
                        (m - 1 >= 0 && n + 1 < GRID_SLICES) &&
                        !circles[m - 1][n + 1].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m + 1][n - 1].placed &&
                        circles[m - 2][n + 2].placed &&
                        (m + 2 < GRID_SLICES && n - 2 >= 0) &&
                        !circles[m + 2][n - 2].placed &&
                        (m - 3 >= 0 && n + 3 < GRID_SLICES) &&
                        !circles[m - 3][n + 3].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m - 1][n + 1].placed &&
                        circles[m - 2][n + 2].placed &&
                        (m + 1 < GRID_SLICES && n - 1 >= 0) &&
                        !circles[m + 1][n - 1].placed &&
                        (m - 3 >= 0 && n + 3 < GRID_SLICES) &&
                        !circles[m - 3][n + 3].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                case 0:
                {
                    bool b = circles[m - 1][n + 1].placed &&
                        circles[m - 2][n + 2].placed &&
                        (m + 1 < GRID_SLICES && n - 1 >= 0) &&
                        !circles[m + 1][n - 1].placed &&
                        (m - 3 >= 0 && n + 3 < GRID_SLICES) &&
                        !circles[m - 3][n + 3].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m - 1][n + 1].placed &&
                        circles[m - 3][n + 3].placed &&
                        (m + 1 < GRID_SLICES && n - 1 >= 0) &&
                        !circles[m + 1][n - 1].placed &&
                        (m - 4 >= 0 && n + 4 < GRID_SLICES) &&
                        !circles[m - 4][n + 4].placed;
                    if (b) { ++ruleVal; t = true; break; }

                    b = circles[m - 2][n + 2].placed &&
                        circles[m - 3][n + 3].placed &&
                        (m + 1 < GRID_SLICES && n - 1 >= 0) &&
                        !circles[m + 1][n - 1].placed &&
                        (m - 4 >= 0 && n + 4 < GRID_SLICES) &&
                        !circles[m - 4][n + 4].placed;
                    if (b) { ++ruleVal; t = true; break; }
                }
                break;
                default:
                    break;
                }

                if (t) break;
            }
        }
        if (ruleVal == 2) return true;

        return false;
    }
    break;
    case Game::Rule6:
    {
        return check(m, n, Row, 6) ||
            check(m, n, Column, 6) ||
            check(m, n, WestDiagonal, 6) ||
            check(m, n, EastDiagonal, 6);
    }
    break;
    case Game::Rule33v2:
    {
        return false;
    }
    break;
    default:
        break;
    }
    
    // @TODO  warning C4715:'Game::check': not all control paths return a value
    assert(false);
    return false;
}
