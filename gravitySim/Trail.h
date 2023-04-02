#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
#include "Vec2D.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Trail : public sf::Drawable , public sf::Transformable{
    std::vector<Vec2D> buffer;
    int head;
    int size;
    sf::Color color;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();

        int i = head;
        sf::VertexArray toDraw(sf::PrimitiveType::LinesStrip, size);
        for (int j = 0; j < size; j++) {
            i %= size;
            toDraw[j] = sf::Vertex( sf::Vector2f(buffer[i].x, buffer[i].y), sf::Color(color.r, color.g, color.b, std::min(255, 2 * j*255 / TRAIL_LENGTH)));
            i++;
        }

        target.draw(toDraw);
    }

public:
    Trail(int sz, Vec2D default_value, sf::Color col) {
        buffer.resize(sz, default_value);
        size = sz;
        head = 0;
        color = col;
    }

    void push(Vec2D toPush) {
        buffer[head++] = toPush;
        if (head >= size) head = 0;
    }

    Vec2D back() {
        return (buffer[head]);
    }

};
#endif // !CIRCULAR_BUFFER_H
