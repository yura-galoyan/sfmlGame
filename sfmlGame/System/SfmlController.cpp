#include "SfmlController.hpp"

SfmlController::SfmlController(){
    initMouseButtons();
    longReleasedTime = 0.05f;
}

void SfmlController::setFlags(Window &window, Event &event)
{
    clearEvents();
        while(window.pollEvent(event)){
            switch (event.event().type)
            {
                case sf::Event::MouseButtonPressed:
                    checkMouseButtonPressed(mouseButtons['l'], event);
                    checkMouseButtonPressed(mouseButtons['r'], event);
                    break;
                case sf::Event::MouseButtonReleased:
                    checkMouseButtonReleased(mouseButtons['l'], event);
                    checkMouseButtonReleased(mouseButtons['r'], event);
                case sf::Event::MouseMoved:
                    break;

                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
}

void SfmlController::initMouseButtons(){
    mouseButtons['l'] = ButtonPair<char>{sf::Mouse::Button::Left,{}};
    mouseButtons['r'] = ButtonPair<char>{sf::Mouse::Button::Right,{}};
}

void SfmlController::checkMouseButtonPressed(ButtonPair<char>& buttonPair, Event &event){
    if(event.event().key.code == buttonPair.button){
        clockReleased.restart();
        buttonPair.state.clicked = true;
        buttonPair.state.onHold = true;
    }

}

void SfmlController::checkMouseButtonReleased(ButtonPair<char>& buttonPair, Event &event){
    if(event.event().key.code == buttonPair.button){
        if(clockReleased.elapsed() > longReleasedTime){
            buttonPair.state.longReleased = true;    
        }
        else{
            buttonPair.state.shortReleased = true;
        }
        buttonPair.state.onHold = false;
    }

}

void SfmlController::clearEvents(){
    for(auto& [key, mapped] : mouseButtons ){
        mapped.state.clicked = false;
        mapped.state.shortReleased = false;
        mapped.state.longReleased = false;
    }
}

auto SfmlController::atMouseButton(char button) -> ButtonPair<char> {
    return mouseButtons[button];
}