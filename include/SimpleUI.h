#ifndef SIMPLEUI_H
#define SIMPLEUI_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button {
public:
    Button(float x, float y, float width, float height, std::string text, sf::Font& font);
    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2i mousePos);
    void setOnClick(std::function<void()> callback);
    void update(sf::Vector2i mousePos);

private:
    sf::RectangleShape shape;
    sf::Text label;
    std::function<void()> onClick;
    sf::Color idleColor;
    sf::Color hoverColor;
};

class InputBox {
public:
    InputBox(float x, float y, float width, float height, sf::Font& font, std::string placeholder = "");
    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event& event);
    std::string getValue();
    void setValue(std::string text);
    void setFocus(bool focus);
    bool isFocused() const;
    bool contains(sf::Vector2i mousePos);

private:
    sf::RectangleShape shape;
    sf::Text text;
    std::string value;
    bool focused;
    std::string placeholder;
};

class TextArea {
public:
    TextArea(float x, float y, float width, float height, sf::Font& font);
    void setText(std::string text);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
    void appendText(std::string text);
    void clear();

private:
    sf::Text text;
    sf::RectangleShape background;
};

#endif
