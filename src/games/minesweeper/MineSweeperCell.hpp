#pragma once

#include <vector>
#include <memory>

#define COLS 9
#define ROWS 9
#define MINES 10

class Cell {
    public:
        Cell() = default;
        Cell(int x, int y, bool mine) : _x(x), _y(y), _isMine(mine) {} ;
        ~Cell() = default;
        bool isHiden();
        void setMine(bool mine);
        bool isMine();
        void setMarked(bool mark);
        bool getMarked() const; 
        void countMineAround
            (const std::vector<std::vector<std::unique_ptr<Cell>>> 
            &cels);
        int getMineAround() { return _mines_around; };
        bool open
            (std::vector<std::vector<std::unique_ptr<Cell>>> 
            &cels);

    private:
        int _x;
        int _y;
        bool _hiden = true;
        bool _marked = false;
        bool _isMine = false;
        int _mines_around;
};
