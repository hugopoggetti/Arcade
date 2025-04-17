#include "NcurseLib.hpp"
#include <functional>
#include <ncurses.h>
#include <thread>
#include <chrono>
// need this tu construct v table in shared lib not default
NcurseLib::NcurseLib() : _plugin(Plugin("Ncurse Library", "1.0", "Salam", "")) {}
NcurseLib::~NcurseLib() {}

void NcurseLib::init(int width, int height)
{
    (void)width;
    (void)height;
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    nodelay(stdscr, true);
    // handle mouse event 
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
    mouseinterval(0);
    start_color();
    setTermSize();
}

void NcurseLib::clear()
{
    ::clear();
}

void NcurseLib::display()
{
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
}

void NcurseLib::draw(const Sprite &sprite)
{
    const Position &pos = sprite.getTransform().getPosition();
    const Size size = sprite.getTransform().getSize();

    auto cachedSprite = _cache.cacheSprite(sprite);

    setTermSize();
    float cellWidth = (float)terminalWidth / (float)_grid.first;
    float cellHeight = (float)terminalHeight / (float)_grid.second;

    int startX = (int)(pos.getX() * cellWidth);
    int startY = (int)(pos.getY() * cellHeight);
    int width = (int)(size.getX() * cellWidth);
    int height = (int)(size.getY() * cellHeight);
   
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
                mvaddch(startY + i, startX + j, cachedSprite);
        }
    }
}

void NcurseLib::draw(const Text &text)
{
    const Position &pos = text.getTransform().getPosition();
    auto color = text.getColor();
    
    setTermSize();
    float cellWidth = (float)terminalWidth / (float)_grid.first;
    float cellHeight = (float)terminalHeight / (float)_grid.second;

    int startX = (int)(pos.getX() * cellWidth);
    int startY = (int)(pos.getY() * cellHeight);

    attron(COLOR_PAIR(color) | A_BOLD);
    mvprintw(startY
            ,startX
            ,"%s"
            ,text.getText().c_str());
    attroff(COLOR_PAIR(color) | A_BOLD);
}

void NcurseLib::draw(const Rectangle &rectangle)
{
    const Position pos = rectangle.getTransform().getPosition();
    const Size size = rectangle.getTransform().getSize();
    auto color = rectangle.getColor();

    setTermSize();
    float cellWidth = (float)terminalWidth / (float)_grid.first;
    float cellHeight = (float)terminalHeight / (float)_grid.second;

    int startX = (int)(pos.getX() * cellWidth);
    int startY = (int)(pos.getY() * cellHeight);
    int width = (int)(size.getX() * cellWidth);
    int height = (int)(size.getY() * cellHeight);

    attron(COLOR_PAIR(color) | A_BOLD);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!rectangle.isFilled()) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1)  {
                    mvaddch(startY + i, startX + j, ACS_CKBOARD);
                }
            } else {
                mvaddch(startY + i, startX + j, ACS_CKBOARD);
            }
        }
    }
    attroff(COLOR_PAIR(color) | A_BOLD);
}

void NcurseLib::setTermSize()
{
    terminalHeight = LINES;
    terminalWidth = COLS;
    // getmaxyx(stdscr, terminalHeight, terminalWidth);
}

void NcurseLib::setGridSize(size_t x, size_t y)
{
    _grid.first = x;
    _grid.second = y;
}

void NcurseLib::setColorPalette(const std::map<Color::ColorID, Color::color_t> &colorPalette)
{
    _colorpalette = colorPalette;
    for (const auto& entry : _colorpalette) {
        short colorID = (short)entry.first;
        const Color::color_t& color = entry.second;
        short r =(short)(color.r * 1000 / 255);
        short g =(short)(color.g * 1000 / 255);
        short b =(short)(color.b * 1000 / 255);
        init_color(colorID, r, g, b);
        init_pair(colorID, colorID, COLOR_BLACK);
    }
}

void NcurseLib::destroy()
{
    // destroy Ncurse window properly
    endwin();
}

std::queue<IEvent *> NcurseLib::pollEvents()
{
    std::queue<IEvent *> events;
    int ch = getch();
    
    KeyBoardEvents(ch, events);
    MouseEvents(ch, events);
    return events;
}

const Plugin &NcurseLib::getPlugin() const 
{
    return _plugin;
}

void NcurseLib::setWindowSize(int x, int y)
{
    _width = x;
    _height = y; 
    (void)x;
    (void)y;
}
