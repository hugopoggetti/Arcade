#include "SfmlLib.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../../../events/Events.hpp"
#include "../../../error/Error.hpp"
#include "../../../error/ErrorMessages.hpp"
#include <thread>
#include <chrono>

SfmlLib::SfmlLib() : _width(1920), _height(1080), _windowInitialized(false),
    _libPlugin(Plugin("SFML Library", "1.0", "tota", "")) {}

SfmlLib::~SfmlLib() {}

void SfmlLib::init(int width, int height)
{
    _window.create(sf::VideoMode((unsigned int)width, (unsigned int)height),
    "Arcade");
    _windowInitialized = true;
}

void SfmlLib::clear()
{
    if (!_windowInitialized) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::NOT_INIT)->second);
    }
    Color::color_t backgroundColor = _colors[Color::BACKGROUND];
    _window.clear(sf::Color(backgroundColor.r, backgroundColor.g,
        backgroundColor.b, backgroundColor.a));
}

void SfmlLib::draw(const Sprite &sprite)
{
    if (!_windowInitialized) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::NOT_INIT)->second);
    }
    auto texture = _cache.cacheSprite(sprite);
    sf::Sprite sp;
    sp.setTexture(*texture);
    int scaleX = _width / (int)_gridRatio.first;
    int scaleY = _height / (int)_gridRatio.second;
    sf::Vector2f size((float)(sprite.getTransform().getSize().getX() * scaleX),
        (float)(sprite.getTransform().getSize().getY() * scaleY));
    sf::Vector2f position((float)(sprite.getTransform().getPosition().getX() * scaleX),
        (float)(sprite.getTransform().getPosition().getY() * scaleY));
    // sp.setScale(size);
    sf::FloatRect bounds = sp.getLocalBounds();
    if (bounds.width > 0 && bounds.height > 0) {
        sf::Vector2f scale(size.x / bounds.width, size.y / bounds.height);
        sp.setScale(scale);
    }
    sp.setPosition(position);
    _window.draw(sp);
}

void SfmlLib::draw(const Text &text)
{
    if (!_windowInitialized) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::NOT_INIT)->second);
    }
    sf::Font font = _cache.cacheFont(text);
    int scaleX = _width / (int)_gridRatio.first;
    int scaleY = _height / (int)_gridRatio.second;
    sf::Vector2f size((float)(text.getTransform().getSize().getX() * scaleX),
        (float)(text.getTransform().getSize().getY() * scaleY));
    sf::Vector2f position((float)(text.getTransform().getPosition().getX() * scaleX),
        (float)(text.getTransform().getPosition().getY() * scaleY));
    sf::Text txt(text.getText(), font, 25);
    // txt.setScale(size);
    Color::color_t colorRect = _colors[text.getColor()];

    sf::Color col(colorRect.r, colorRect.g, colorRect.b);
    txt.setPosition(position);
    txt.setFillColor(col);
    _window.draw(txt);
}

void SfmlLib::draw(const Rectangle &rectangle)
{
    if (!_windowInitialized) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::NOT_INIT)->second);
    }
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Red);

    // sf::RectangleShape rect;
    int scaleX = _width / (int)_gridRatio.first;
    int scaleY = _height / (int)_gridRatio.second;
    sf::Vector2f size((float)(rectangle.getTransform().getSize().getX() * scaleX),
    (float)(rectangle.getTransform().getSize().getY() * scaleY));
    sf::Vector2f position((float)(rectangle.getTransform().getPosition().getX() * scaleX),
        (float)(rectangle.getTransform().getPosition().getY() * scaleY));
    rect.setSize(size);
    rect.setPosition(position);
    Color::color_t colorRect = _colors[rectangle.getColor()];

    sf::Color col(colorRect.r, colorRect.g, colorRect.b);
    
    if (!rectangle.isFilled()) {
        rect.setFillColor(sf::Color(0, 0, 0, 0));
        rect.setOutlineThickness(5.f);
        rect.setOutlineColor(col);
    } else {
        rect.setFillColor(col);
    }
    _window.draw(rect);
}

void SfmlLib::display()
{
    if (!_windowInitialized) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::NOT_INIT)->second);
    }
    _window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
}

void SfmlLib::destroy()
{
    if (!_windowInitialized) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::NOT_INIT)->second);
    }
    _cache.clearCahce();
    _window.close();
}

void SfmlLib::setColorPalette(const std::map<Color::ColorID, Color::color_t> &colorPalette)
{
    _colors = colorPalette;
}

void SfmlLib::setGridSize(std::size_t x, std::size_t y)
{
    _gridRatio.first = x;
    _gridRatio.second = y;
}

std::queue<IEvent *> SfmlLib::pollEvents()
{
    std::queue<IEvent *> events;
    sf::Event event;

    while (_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                events.push(new KeyPressedEvent(getArcadeKey(event)));
                continue;
            case sf::Event::MouseButtonPressed:
                events.push(new MouseButtonPressedEvent
                        (getArcadeButton(event),event.mouseButton.x * (double)_gridRatio.first / (double)_width,
                         event.mouseButton.y * (double)_gridRatio.second / (double) _height));
                continue;
            case sf::Event::MouseMoved:
                events.push(new MouseMoveEvent(Position(event.mouseMove.x  * (double)_gridRatio.first / (double)_width,
                                event.mouseMove.y * (double)_gridRatio.second / (double) _height)));
                continue;
            default:
                continue;
        }
    }
    return events;
}

const Plugin &SfmlLib::getPlugin() const
{
    return _libPlugin;
}

ArcadeKey SfmlLib::getArcadeKey(const sf::Event &event)
{
    switch (event.key.code) {
        case sf::Keyboard::Key::Up:
            return ArcadeKey::UP;
        case sf::Keyboard::Key::Down:
            return ArcadeKey::DOWN;
        case sf::Keyboard::Key::Right:
            return ArcadeKey::RIGHT;
        case sf::Keyboard::Key::Left:
            return ArcadeKey::LEFT;
        case sf::Keyboard::Key::Escape:
            return ArcadeKey::ESCAPE;
        case sf::Keyboard::Enter:
            return ArcadeKey::RETURN;
        case sf::Keyboard::O:
            return ArcadeKey::O;
        case sf::Keyboard::P:
            return ArcadeKey::P;
        case sf::Keyboard::M:
            return ArcadeKey::M;
        case sf::Keyboard::Space:
            return ArcadeKey::SPACE;
        case sf::Keyboard::R:
            return ArcadeKey::R;
        case sf::Keyboard::D:
            return ArcadeKey::D;
        case sf::Keyboard::Q:
            return ArcadeKey::Q;
        case sf::Keyboard::Z:
            return ArcadeKey::Z;
        case sf::Keyboard::S:
            return ArcadeKey::S;
        case sf::Keyboard::F1:
            return ArcadeKey::F1;
        case sf::Keyboard::F2:
            return ArcadeKey::F2;
        case sf::Keyboard::BackSpace:
            return ArcadeKey::BACKSPACE;
        default:
            break;
    }
    return ArcadeKey::UNKNOWN;
}

ArcadeMouseButton SfmlLib::getArcadeButton(const sf::Event &event)
{
    switch (event.mouseButton.button) {
        case sf::Mouse::Left:
            return ArcadeMouseButton::MOUSE1;
        case sf::Mouse::Right:
            return ArcadeMouseButton::MOUSE2;
        default:
            break;
    }
    return ArcadeMouseButton::UNKNOW;
}

void SfmlLib::setWindowSize(int x, int y)
{
    if (_width == x && _height == y)
        return;
    if (_window.isOpen()) {
        _window.create(sf::VideoMode(x, y), "Arcade", sf::Style::Titlebar | sf::Style::Close);
        sf::View view(sf::FloatRect(0, 0,(float) x,(float) y));
        _window.setView(view);
    }
    this->_width = x;
    this->_height = y;
}
