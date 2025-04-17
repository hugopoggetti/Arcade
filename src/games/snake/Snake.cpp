#include "Snake.hpp"
#include "SnakeEvents.hpp"
#include <chrono>
#include <string>
#include <thread>

Snake::Snake() : _plugin(Plugin("snake", "1.0", "tkt", "")) {}
Snake::~Snake() {}

void Snake::init()
{
    reset(true);
}

std::pair<std::size_t, std::size_t> Snake::getGridSize()
{
    return {100,50};
}

std::map<Color::ColorID, Color::color_t> Snake::getColorPalette()
{
    return _colorPalette;
}

void Snake::run(IDisplayModule &dsp)
{
    _direction = _events.getDirection(); 
    dsp.setWindowSize(1920, 1080);

    moveSnake();
    drawGame(dsp);
    if (_speed >= 1 && _speed <= 50) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        _speed++;
    }
    else
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if (_speed >= 50)
        _speed = 0;
}

void Snake::changeDirection(Direction direction)
{
    _direction = direction; 
}

std::vector<Listener *> &Snake::getGameListeners()
{
    _listener.push_back({&_events});
    return _listener;
}

int Snake::getScore() const
{
    return _bestScore;
}

void Snake::setBestScore(int score)
{
    _bestScore = score;
}

void Snake::die()
{
    _lives--;
    if (_lives <= 0)
        reset(true);
    else {
        reset(false);
    }
}

void Snake::reset(bool live)
{
    _snake.clear();
    _snake.push_back({50, 25});
    _snake.push_back({49, 25});
    _snake.push_back({48, 25});
    _snake.push_back({47, 25});
    _direction = S_RIGHT;
    if (live)
        _lives = 3;
    _score = 0;
    _food.spawnFood();
    _gameover = false;
}

void Snake::speedUp()
{
    if (!_speed)
        _speed = 1;
}

void Snake::moveSnake()
{
    auto head = _snake.front();
    std::pair<int, int> next = head;

    if (_direction == UKN)
        _direction = S_RIGHT;
    switch (_direction) {
        case S_UP:    next.second--; break;
        case S_DOWN:  next.second++; break;
        case S_LEFT:  next.first--; break;
        case S_RIGHT: next.first++; break;
        default: break;
    }

    if (next.first < 25 
            || next.first >= 75
            || next.second < 12
            || next.second >= 37
            || checkCollision(next)) {
        die();
        return;
    }
    _snake.push_front(next);
    if (next == _food.getFoodPos()) {
        _food.spawnFood();
        _score += 100;
        if (_score >= _bestScore)
            _bestScore = _score;
    } else {
        _snake.pop_back();
    }
}

bool Snake::checkCollision(std::pair<int, int> pos)
{
    for (auto &segment : _snake) {
        if (segment == pos)
            return true;
    }
    return false;
}

void Snake::drawSnake(IDisplayModule &dsp)
{
    Rectangle rect;
    rect.fillRect(true);
    rect.getTransform().getSize().setPosition(1, 1);
    for (std::size_t i = 0; i < _snake.size(); i++) {
        if (i == 0) {
            rect.setColor(Color::ColorID::YELLOW);
        } else {
            rect.setColor(Color::ColorID::BLUE);
        }
        rect.getTransform().getPosition().setPosition(
                _snake[i].first, _snake[i].second);
        dsp.draw(rect);
    }
}

void Snake::displayGameOver(IDisplayModule &dsp)
{   
    Text text;
    text.setFontPath("./assets/font/Popstar.ttf");
    text.setColor(Color::ColorID::RED);
    text.getTransform().getSize().setPosition(10, 10);
    text.getTransform().getPosition().setPosition(17, 15);
    text.setText("Games over");
    dsp.draw(text);

    text.getTransform().getSize().setPosition(3, 3);
    text.getTransform().getPosition().setPosition(30, 35);
    text.setText("Press Enter to Replay");
    dsp.draw(text);
}

void Snake::drawGameInfo(IDisplayModule &dsp)
{
    std::string score = "Score  " +  std::to_string(_score);
    std::string lives = "Lives  " +  std::to_string(_lives);
    std::string best = "Best Score  " +  std::to_string(_bestScore);
    Text text;
    text.setFontPath("./assets/font/Popstar.ttf");
    text.setColor(Color::ColorID::BLUE);
    text.getTransform().getSize().setPosition(1, 1);
    text.getTransform().getPosition().setPosition(25, 8);
    text.setText(score);
    dsp.draw(text);

    text.getTransform().getPosition().setPosition(45, 8);
    text.setText(lives);
    dsp.draw(text);

    text.getTransform().getPosition().setPosition(65, 8);
    text.setText(best);
    dsp.draw(text);
}

void Snake::drawGame(IDisplayModule &dsp)
{
    wall.displayWall(dsp, 25, 12);
    _food.displayFood(dsp);
    this->drawGameInfo(dsp);
    this->drawSnake(dsp);
}

const Plugin &Snake::getPlugin() const
{
    return _plugin;
}
