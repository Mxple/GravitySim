#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vec2D.h"
#include "Mass.h"
#include "Trail.h"
#include "Constants.h"

int main() {
    // initialization
    std::vector<Mass*> masses;

    sf::CircleShape circle;
    sf::Vertex line[2];
    int mouse_button_held_time = 0; // used to determine mass of new object

    // draw setup
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity Sim", sf::Style::None);
    window.setFramerateLimit(60);
    sf::FloatRect visibleArea(0, 0, WIDTH, HEIGHT);
    sf::View view(visibleArea);
    view.setCenter(0, 0);
    window.setView(view); 


    int CALCS = 0;
    int seed = 33;
    // game loop
    while (window.isOpen()) {
        window.clear();

        window.draw(sf::CircleShape(2));
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            //case sf::Event::KeyPressed:
            //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            //        masses.clear();
            //        std::cout << "seed: " << seed;
                   // srand(seed);
                   // for (int i = 0; i < 3; i++) {
                   //     masses.push_back(new Mass(rand() % 2000 - 1000, rand() % 2000 - 1000, 500));
                   // }
                   // seed++;
                   ///* masses[0]->pos.x += 0.001;*/
                   // printf("START VALUES\n");
                   // for (Mass*& m : masses) {
                   //     printf("pos x: %f, pos y: %f, vel x: %f, vel y: %f, acc x: %f, acc y: %f\n",
                   //         m->pos.x, m->pos.y, m->vel.x, m->vel.y, m->acc.x, m->acc.y);
                   // }
            //    }
            //    break;

            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized: 
                view.setSize(sf::Vector2f(event.size.width, event.size.height));
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button != sf::Mouse::Left) break;
                line[0].position = (sf::Vector2f) window.mapPixelToCoords(sf::Mouse::getPosition(window));
                mouse_button_held_time = 1;
                break;

            case sf::Event::MouseButtonReleased:
                // create a new mass
                if (mouse_button_held_time) {
                    Mass* m = new Mass(
                        line[0].position.x, line[0].position.y, // pos x, posy
                        .1 * (line[1].position.x - line[0].position.x), .1 * (line[1].position.y - line[0].position.y), // vel x, vel y
                        mouse_button_held_time * 10 // mass
                    );
                    masses.push_back(m);
                }
                mouse_button_held_time = 0;
                break;
            case sf::Event::MouseWheelMoved:
                if (event.mouseWheel.delta > 0)
                    view.zoom(.9f);
                else if (event.mouseWheel.delta < 0)
                    view.zoom(1.1f);
                window.setView(view);
                break;
            }
        }

        // draw connecting line and circle
        if (mouse_button_held_time) {
            line[1].position = (sf::Vector2f) window.mapPixelToCoords(sf::Mouse::getPosition(window));
            window.draw(line, 2, sf::Lines);
            double radius = sqrt(10 * mouse_button_held_time);
            circle.setRadius(radius);
            circle.setOutlineThickness(1);
            circle.setPosition(line[0].position - sf::Vector2f(radius, radius));
            circle.setFillColor(sf::Color::Transparent);
            window.draw(circle);
            circle.setOutlineThickness(0);

            mouse_button_held_time++;

        }

        // simulation 
        for (int i = 0; i < CALCULATIONS_PER_FRAME; i++) {
            CALCS++;
            for (Mass*& m : masses) {
                m->update_acceleration(masses);
                m->update_velocity();
            }
            for (Mass*& m : masses) {
                m->update_position();
                if (CALCS % (STEPS/50) == 0) m->update_trail();
            }
        }

        // draw masses
        for (Mass*& m : masses) {
            circle.setFillColor(m->color);
            circle.setPosition(m->pos.x - m->radius, m->pos.y - m->radius);
            circle.setRadius(m->radius);
            window.draw(circle);

            window.draw( *(m->trail) );
        }

        window.display();
    }
    //printf("END VALUES\n");
    //for (Mass*& m : masses) {
    //    printf("pos x: %f, pos y: %f, vel x: %f, vel y: %f, acc x: %f, acc y: %f\n",
    //        m->pos.x, m->pos.y, m->vel.x, m->vel.y, m->acc.x, m->acc.y);
    //}
    return 0;
}