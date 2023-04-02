#ifndef MASS_H
#define MASS_H
#include "Vec2D.h"
#include "Trail.h"
#include "Constants.h"
#include <SFML/Graphics/Color.hpp>

class Mass {
public:
    Vec2D pos, vel, acc;
    Vec2D verlet_last;
    double mass;
    double radius;
    Trail* trail;
    sf::Color color;

    void update_acceleration(std::vector<Mass*>& targets) {
        acc = Vec2D(0., 0.);
        for (Mass* t : targets) {
            Vec2D dist_vec = pos - t->pos; // distance vector between positions
            double dist2 = dist_vec.len2(); // squared distance

            // if too close, or is self, don't simulate
            if (dist2 < DAMPING_CUTOFF) continue;

            // F = G M m / r^2 -> a = G M / r^2
            double accel = (GRAV_CONSTANT * t->mass) / dist2;
            acc -= dist_vec.normalize() * accel;
        }
    }

    void update_velocity() {
        vel += acc;
    }

    void update_position() {
        pos += vel * (1. / STEPS);
    }

    void update_position_verlet() {
        Vec2D temp = pos;
        pos = (pos*2) - (verlet_last) + (acc * (1./(STEPS)));
        verlet_last = temp;
    }

    void update_trail() {
         trail->push(pos);
    }

    Mass(double px, double py, double m) :
        pos(Vec2D(px, py)), vel(Vec2D(0., 0.)), acc(Vec2D(0., 0.)), verlet_last(Vec2D(px, py)), mass(m), radius(sqrt(m)) {
        srand(reinterpret_cast<std::uintptr_t>(this));
        color = sf::Color(155 + rand() % 100, 155 + rand() % 100, 155 + rand() % 100);
        trail = new Trail(TRAIL_LENGTH, Vec2D(px, py), color);
    }

    Mass(double px, double py, double dx, double dy, double m) :
        pos(Vec2D(px, py)), vel(Vec2D(dx, dy)), acc(Vec2D(0., 0.)), verlet_last(Vec2D(px, py)), mass(m), radius(sqrt(m)) {
        srand(reinterpret_cast<std::uintptr_t>(this));
        color = sf::Color(155 + rand() % 100, 155 + rand() % 100, 155 + rand() % 100);
        trail = new Trail(TRAIL_LENGTH, Vec2D(px, py), color);
    }

};

#endif