#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <bits/stdc++.h>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "My first game");
    optional<sf::Event> event;

    // Game loop
    while (window.isOpen()){

        //Event polling
        while (const optional event = window.pollEvent()){
            
            if (event->is<sf::Event::Closed>()){ //when close button is clicked
                window.close();
            }
        }
   
        window.clear(sf::Color(127, 127, 127));

        window.display();
    }
    

    return 0;
}