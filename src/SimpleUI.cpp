#include "SimpleUI.h"

// Button Implementation
Button::Button(float x, float y, float width, float height, std::string text, sf::Font& font) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    idleColor = sf::Color(70, 70, 70);
    hoverColor = sf::Color(100, 100, 100);
    shape.setFillColor(idleColor);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(18);
    label.setFillColor(sf::Color::White);
    
    // Center text
    sf::FloatRect textRect = label.getLocalBounds();
    label.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    label.setPosition(x + width/2.0f, y + height/2.0f);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(label);
}

bool Button::isClicked(sf::Vector2i mousePos) {
    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        if (onClick) onClick();
        return true;
    }
    return false;
}

void Button::setOnClick(std::function<void()> callback) {
    onClick = callback;
}

void Button::update(sf::Vector2i mousePos) {
    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        shape.setFillColor(hoverColor);
    } else {
        shape.setFillColor(idleColor);
    }
}

// InputBox Implementation
InputBox::InputBox(float x, float y, float width, float height, sf::Font& font, std::string placeholder) 
    : placeholder(placeholder), focused(false) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(50, 50, 50));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color(150, 150, 150));

    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setPosition(x + 5, y + 5);
    text.setString(placeholder);
    text.setFillColor(sf::Color(150, 150, 150)); // Placeholder color
}

void InputBox::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

void InputBox::handleEvent(sf::Event& event) {
    if (!focused) return;

    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8) { // Backspace
            if (!value.empty()) {
                value.pop_back();
            }
        } else if (event.text.unicode < 128 && event.text.unicode > 31) {
            value += static_cast<char>(event.text.unicode);
        }
        
        if (value.empty()) {
            text.setString(placeholder);
            text.setFillColor(sf::Color(150, 150, 150));
        } else {
            text.setString(value);
            text.setFillColor(sf::Color::White);
        }
    }
}

std::string InputBox::getValue() {
    return value;
}

void InputBox::setValue(std::string text) {
    value = text;
    if (value.empty()) {
        this->text.setString(placeholder);
        this->text.setFillColor(sf::Color(150, 150, 150));
    } else {
        this->text.setString(value);
        this->text.setFillColor(sf::Color::White);
    }
}

void InputBox::setFocus(bool focus) {
    focused = focus;
    if (focused) {
        shape.setOutlineColor(sf::Color::Blue);
    } else {
        shape.setOutlineColor(sf::Color(150, 150, 150));
    }
}

bool InputBox::isFocused() const {
    return focused;
}

bool InputBox::contains(sf::Vector2i mousePos) {
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

// TextArea Implementation
TextArea::TextArea(float x, float y, float width, float height, sf::Font& font) {
    background.setPosition(x, y);
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color(30, 30, 30));
    
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setPosition(x + 10, y + 10);
}

void TextArea::setText(std::string str) {
    text.setString(str);
}

void TextArea::setPosition(float x, float y) {
    background.setPosition(x, y);
    text.setPosition(x + 10, y + 10);
}

void TextArea::appendText(std::string str) {
    text.setString(text.getString() + str);
}

void TextArea::clear() {
    text.setString("");
}

void TextArea::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(text);
}
