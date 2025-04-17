#include "Menu.hpp"
#include <regex>

void Menu::displayTitle(Text &text)
{
    text.setColor(Color::ColorID::ORANGE);
    text.getTransform().getPosition().setPosition(20,7);
    text.getTransform().getSize().setPosition(2, 2);
    text.setText("Graphics Libraries");
    _dsp->draw(text);

    text.getTransform().getPosition().setPosition(70,7);
    text.getTransform().getSize().setPosition(2, 2);
    text.setText("Games Libraries");
    _dsp->draw(text);
}

void Menu::displayLib(Text &text)
{
    text.setColor(Color::ColorID::PURPLE);
    for (std::size_t i = 0; i < _core.getGraphicsPath().size(); i++) {
        text.getTransform().getPosition().setPosition(12, 12 + (double)i);
        text.getTransform().getSize().setPosition(1, 1);
        text.setText(_core.getGraphicsPath()[i]);
        _dsp->draw(text);
    }
    for (std::size_t i = 0; i < _core.getGamesPath().size(); i++) {
        text.getTransform().getPosition().setPosition(62, 12 + (double)i);
        text.getTransform().getSize().setPosition(1, 1);
        text.setText(_core.getGamesPath()[i]);
        _dsp->draw(text);
    }
}

void Menu::displaySelectedItem(Text &text)
{
    text.setColor(Color::ColorID::GREEN);
    text.getTransform().getPosition().setPosition(37, 12 + (double)_SelectGraphic);
    text.getTransform().getSize().setPosition(1, 1);
    text.setText("**");
    _dsp->draw(text);

    text.getTransform().getPosition().setPosition(87, 12 + (double)_SelectGame);
    text.getTransform().getSize().setPosition(1, 1);
    text.setText("**");
    _dsp->draw(text);

}

void Menu::displayBorder(Rectangle &rectangle)
{
    rectangle.setColor(Color::ColorID::YELLOW);
    rectangle.fillRect(false);
    rectangle.getTransform().getPosition().setPosition(10, 10);
    rectangle.getTransform().getSize().setPosition(30, 30);
    _dsp->draw(rectangle);

    rectangle.setColor(Color::ColorID::BLUE);
    rectangle.fillRect(false);
    rectangle.getTransform().getPosition().setPosition(60, 10);
    rectangle.getTransform().getSize().setPosition(30, 30);
    _dsp->draw(rectangle);
 
}

void Menu::displayMenu()
{
    Text text;
    Rectangle rectangle;

    text.setColor(Color::ColorID::BLUE);
    text.setFontPath("./assets/font/Popstar.ttf");
    
    displayTitle(text);
    displayLib(text);
    displaySelectedItem(text);
    displayBorder(rectangle);
}
