#include "SdlLib.hpp"

#include "../../../events/Events.hpp"
#include "../../../error/Error.hpp"
#include "../../../error/ErrorMessages.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

SdlLib::SdlLib() : _width(0), _height(0), _window(nullptr), _windowRenderer(nullptr),
    _libPlugin(Plugin("Sdl Library", "1.0", "Leykoum", "")) {}

SdlLib::~SdlLib() {}

void SdlLib::init(int width, int height)
{
    _width = width;
    _height = height;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::CANNOT_INIT)->second);
    }
    if (TTF_Init() == -1) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::CANNOT_INIT)->second);
    }
    _window = SDL_CreateWindow("ARCADE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    _width, _height, 0);
    if (_window == nullptr) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::CANNOT_OPEN_WINDOW)->second);
    }
    _windowRenderer = SDL_CreateRenderer(_window, -1, 0);
    if (_windowRenderer == nullptr) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::CANNOT_INIT_RENDERER)->second);
    }
}

void SdlLib::clear()
{
    if (_window == nullptr || _windowRenderer == nullptr) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::NOT_INIT)->second);
    }
    SDL_RenderClear(_windowRenderer);
}

void SdlLib::draw(const Sprite &sprite)
{
    if (_window == nullptr || _windowRenderer == nullptr) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::NOT_INIT)->second);
    }
    auto spritePng = sprite.getAssetPath() + ".png";
    SDL_Surface *spriteSurface = IMG_Load(spritePng.c_str());
    if (spriteSurface == nullptr) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::SPRITE_NOT_LOAD)->second);
    }
    SDL_Texture *spriteTexture = SDL_CreateTextureFromSurface(_windowRenderer, spriteSurface);
    if (spriteTexture == nullptr) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::SPRITE_NOT_LOAD)->second);
    }
    SDL_FreeSurface(spriteSurface);
    SDL_Rect rect = {};

    int scaleX = _width / (int)_grid.first;
    int scaleY = _height / (int)_grid.second;
    rect.x = (int)(sprite.getTransform().getPosition().getX() * scaleX);
    rect.y = (int)(sprite.getTransform().getPosition().getY() * scaleY);
    rect.w = (int)(sprite.getTransform().getSize().getX() * scaleX);
    rect.h = (int)(sprite.getTransform().getSize().getY() * scaleY);
    SDL_RenderCopy(_windowRenderer, spriteTexture, nullptr, &rect);
    SDL_DestroyTexture(spriteTexture);
}

void SdlLib::draw(const Text &text)
{
    int scaleX = _width / (int)_grid.first;
    int scaleY = _height / (int)_grid.second;

    int fontSize = static_cast<int>(text.getTransform().getSize().getY() * scaleY);
    TTF_Font *font = TTF_OpenFont(text.getFontPath().c_str(), fontSize);
    if (font == nullptr) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::TEXT_NOT_LOAD)->second);
    }
    SDL_Color color = {_colors[text.getColor()].r, _colors[text.getColor()].g,
        _colors[text.getColor()].b, _colors[text.getColor()].a};
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.getText().c_str(), color);
    if (textSurface == nullptr) {
        TTF_CloseFont(font);
        throw GraphicLibraryError(Graphic::messages.find(Graphic::TEXT_NOT_LOAD)->second);
    }
    TTF_CloseFont(font);

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(_windowRenderer, textSurface);
    if (textTexture == nullptr) {
        SDL_FreeSurface(textSurface);
        throw GraphicLibraryError(Graphic::messages.find(Graphic::TEXT_NOT_LOAD)->second);
    }
    SDL_FreeSurface(textSurface);
    SDL_Rect rect;
    rect.x = static_cast<int>(text.getTransform().getPosition().getX() * scaleX);
    rect.y = static_cast<int>(text.getTransform().getPosition().getY() * scaleY);
    SDL_QueryTexture(textTexture, nullptr, nullptr, &rect.w, &rect.h);
    SDL_RenderCopy(_windowRenderer, textTexture, nullptr, &rect);
    SDL_DestroyTexture(textTexture);
}

void SdlLib::draw(const Rectangle &rectangle)
{
    if (_window == nullptr || _windowRenderer == nullptr) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::NOT_INIT)->second);
    }
    SDL_Rect rect = {};
    Color::color_t color = {};
    
    int scaleX = _width / (int)_grid.first;
    int scaleY = _height / (int)_grid.second;
    rect.x = (int)(rectangle.getTransform().getPosition().getX() * scaleX);
    rect.y = (int)(rectangle.getTransform().getPosition().getY() * scaleY);
    rect.w = (int)(rectangle.getTransform().getSize().getX() * scaleX);
    rect.h = (int)(rectangle.getTransform().getSize().getY() * scaleY);
    color = _colors[rectangle.getColor()];
    SDL_SetRenderDrawColor(_windowRenderer, color.r, color.g, color.b, color.a);
    int thickness = 5;
    if (rectangle.isFilled()) {
        SDL_RenderFillRect(_windowRenderer, &rect);
    } else {
        for (int i = 0; i < thickness; ++i) {
            SDL_Rect outlineRect = {
                rect.x + i,
                rect.y + i,
                rect.w - 2 * i,
                rect.h - 2 * i
            };
            if (outlineRect.w <= 0 || outlineRect.h <= 0) break;
            SDL_RenderDrawRect(_windowRenderer, &outlineRect);
        }
    }
    SDL_RenderDrawRect(_windowRenderer, &rect);
    color = _colors[Color::BACKGROUND];
    SDL_SetRenderDrawColor(_windowRenderer, color.r, color.g, color.b, color.a);
}

void SdlLib::display()
{
    if (_window == nullptr || _windowRenderer == nullptr) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::NOT_INIT)->second);
    }
    SDL_RenderPresent(_windowRenderer);
}

void SdlLib::destroy()
{
    if (_window == nullptr || _windowRenderer == nullptr) {
        throw GraphicLibraryError(Graphic::messages.find(Graphic::NOT_INIT)->second);
    }
    SDL_DestroyRenderer(_windowRenderer);
    SDL_DestroyWindow(_window);
    _windowRenderer = nullptr;
    _window = nullptr;
}

void SdlLib::setColorPalette(const std::map<Color::ColorID, Color::color_t> &colorPalette)
{
    _colors = colorPalette;
}

void SdlLib::setGridSize(size_t x, size_t y)
{
    _grid.first = x;
    _grid.second = y;
}

std::queue<IEvent *> SdlLib::pollEvents()
{
    std::queue<IEvent *> events;
    SDL_Event event = {};

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                events.push(new KeyPressedEvent(getArcadeKey(event)));
                continue;
            case SDL_KEYUP:
                events.push(new KeyReleasedEvent(getArcadeKey(event)));
                continue;
            case SDL_MOUSEBUTTONDOWN:
                events.push(new MouseButtonPressedEvent
                        (getArcadeMouseButton(event), (double)event.button.x  * (double)_grid.first / (double)_width, 
                            (double)event.button.y * (double)_grid.second / (double)_height));
                continue;
            case SDL_MOUSEBUTTONUP:
                events.push(new MouseButtonReleasedEvent
                        (getArcadeMouseButton(event), (double)event.button.x * (double)_grid.first / (double)_width, 
                            (double)event.button.y *(double)_grid.second /(double)_height));
                continue;
            case SDL_MOUSEMOTION:
                events.push(new MouseMoveEvent(Position((double)event.button.x * (double)_grid.first / (double)_width,
                            (double)event.button.y * (double) _grid.second / (double)_height)));
                continue;
        }
    }
    return events;
}

const Plugin &SdlLib::getPlugin() const
{
    return _libPlugin;
}

ArcadeKey SdlLib::getArcadeKey(SDL_Event event)
{
    switch (event.key.keysym.sym) {
        case SDLK_UP:
            return ArcadeKey::UP;
        case SDLK_DOWN:
            return ArcadeKey::DOWN;
        case SDLK_LEFT:
            return ArcadeKey::LEFT;
        case SDLK_RIGHT:
            return ArcadeKey::RIGHT;
        case SDLK_ESCAPE:
            return ArcadeKey::ESCAPE;
        case SDLK_o:
            return ArcadeKey::O;
        case SDLK_p:
            return ArcadeKey::P;
        case SDLK_m:
            return ArcadeKey::M;
        case SDLK_SPACE:
            return ArcadeKey::SPACE;
        case SDLK_r:
            return ArcadeKey::R;
        case SDLK_d:
            return ArcadeKey::D;
        case SDLK_q:
            return ArcadeKey::Q;
        case SDLK_s:
            return ArcadeKey::S;
        case SDLK_z:
            return ArcadeKey::Z;
        case SDLK_RETURN:
            return ArcadeKey::RETURN;
        case SDLK_F1:
            return ArcadeKey::F1;
        case SDLK_F2:
            return ArcadeKey::F2;
        case SDLK_BACKSPACE:
            return ArcadeKey::BACKSPACE;
    }
    return ArcadeKey::UNKNOWN;
}

ArcadeMouseButton SdlLib::getArcadeMouseButton(SDL_Event event)
{
    switch (event.button.button) {
        case 1:
            return ArcadeMouseButton::MOUSE1;
        case 3:
            return ArcadeMouseButton::MOUSE2;
        default:
            break;
    }
    return ArcadeMouseButton::UNKNOW;
}

void SdlLib::setWindowSize(int x, int y)
{
    if (this->_width == x && this->_height == y)
        return;
    SDL_SetWindowSize(this->_window, x, y);
    SDL_SetWindowPosition(this->_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    this->_width = x;
    this->_height = y;
}
