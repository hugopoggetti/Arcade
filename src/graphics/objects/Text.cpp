#include "Text.hpp"

Text::Text(const std::string &text,
        const std::string &fontPath,
        Color::ColorID color)
    : _text(text),_fontPath(fontPath), _colorID(color) {}

Text::Text(const Text &other)
{
    _text = other._text;
    _fontPath = other._fontPath;
    _transform = other._transform;
    _colorID = other._colorID;
}

void Text::setText(const std::string &text)
{
    _text = text;
}

const std::string &Text::getText() const
{
    return _text;
}

void Text::setFontPath(const std::string &fontPath)
{
    _fontPath = fontPath;
}

const std::string &Text::getFontPath() const
{
    return _fontPath;
}

Transform &Text::getTransform()
{
    return _transform;
}

const Transform &Text::getTransform() const
{
    return _transform;
}

void Text::setColor(Color::ColorID color)
{
    _colorID = color;
}

Color::ColorID Text::getColor() const
{
    return _colorID;
}

void Text::operator=(const Text &other)
{
    _text = other._text;
    _fontPath = other._fontPath;
    _transform = other._transform;
    _colorID = other._colorID;
}
