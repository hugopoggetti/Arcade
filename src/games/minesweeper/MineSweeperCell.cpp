#include "MineSweeperCell.hpp"

bool Cell::isHiden() {return _hiden;};

void Cell::setMine(bool mine) {_isMine = mine; };
    
bool Cell::isMine() { return _isMine; };
    
void Cell::setMarked(bool mark) {_marked = mark;};
    
bool Cell::getMarked() const {return _marked;};

void Cell::countMineAround(const std::vector<std::vector<std::unique_ptr<Cell>>> &cels)
{
    _mines_around = 0;

    if (!_isMine) {
        for (char i = -1; i < 2; i ++) {
            for (char j = -1; j < 2; j++) {
                if ((0 == i && 0 == j) 
                        || (0 > i + _x || 0 > j + _y 
                        || COLS == i + _x || ROWS == j + _y))
				{
					continue;
				}
                if (cels[i + _x][j + _y]->isMine())
                    _mines_around++;
            }
        }
    }
}

bool Cell::open(std::vector<std::vector<std::unique_ptr<Cell>>> &cels)
{
    if (_hiden) {
        _hiden = 0;

        if (!_isMine && _mines_around == 0) {
            for (char i = -1; i < 2; i ++) {
            for (char j = -1; j < 2; j++) {
                if ((0 == i && 0 == j) 
                        || (0 > i + _x || 0 > j + _y 
                        || COLS == i + _x || ROWS == j + _y)) {
					continue;
				}
				cels[i + _x][j + _y]->open(cels);
				}
			}
        }
        return _isMine;
    }
    return false;
}
