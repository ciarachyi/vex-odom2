#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
// extern pros::adi::DigitalOut middle;

inline pros::MotorGroup intake({3, 4, 5});

inline pros::Motor intake1(3);  //bottom
inline pros::Motor intake2(5);  //top
inline pros::Motor intake3(4);  //yay

// inline pros::Distance rightDistance(1);     
// inline pros::Distance frontDistance(7);     


// inline pros::MotorGroup intake ({17, 10});

// inline pros::Motor intakeTop(10);
// inline pros::Motor intakeBottom(17);

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');