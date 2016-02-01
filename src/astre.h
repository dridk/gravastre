#pragma once


#include <iostream>
#include <string>
#include <assert.h>
#include <cmath>
#include <QColor>
#include <QVector2D>
#include "converters.h"


namespace eng {

    class Astre {

    public:
        Astre(double, double, double, double, double, double, std::string, QColor);
        void update();
        void accelerateTo(Astre* const, const double);
        void absorbs(Astre* const);
        void nullify();
        double distTo(const Astre* const) const;

        std::string getName() const { return this->name; }
        double getX() const { return this->position_x; }
        double getY() const { return this->position_y; }
        double getRadius() const { return this->radius; }
        QColor getColor() const { return this->color; }

        bool collide(const Astre* const, const double) const;
        bool bigger(const Astre* const othr) const { return this->mass > othr->mass; }
        bool updatable() const { return not this->nullified; }

        static double mass_to_radius(double mass) {
            double log_mass = log10(mass/10e22);
            return (log_mass >=0 ? log_mass : 0) + 1;
        }

    private:
        double mass, radius; // mass in kg, radius in pixel

//Tout remplacer par QVector2D

        double position_x, position_y; // position in astronomic unit
        double speed_x, speed_y; // speed in meter per second
        double accel_x, accel_y;
 // isVisible , isNullified
        bool visible;
        bool nullified;
 //QString
        std::string name;
        double dist_to_sun_min, dist_to_sun_max; // debug
        QColor color;

    };

} // namespace view
