#include "EZ-Template/util.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include "subsystems.hpp"

extern pros::adi::DigitalOut tongue;
extern pros::adi::DigitalOut descore;
extern pros::adi::DigitalOut park;
extern pros::adi::DigitalOut pod;

extern pros::Distance frontDistance;
extern pros::Distance leftDistance;

// extern pros::adi::DigitalOut matchload;
// extern pros::adi::DigitalOut pod;
/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 127;
const int TURN_SPEED = 127;
const int SWING_SPEED = 127;
// Was slew the issue??
///
// Constants
///
// 162

void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(11, 0.0, 53.0);        // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(15.0, 0.0, 24.5);    // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(2, 0.05, 22, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);       // Swing constants
  chassis.pid_odom_angular_constants_set(7, 0.2, 90);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(7, 0.6, 90);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 150_ms, 3_in, 350_ms, 350_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 4_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.7);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are **TRY THIS

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there **EXPERIMENT WITH THIS MAYBE
}

// chassis.pid_odom_angular_constants_set(6.5, 0.0, 43);      // Angular control for odom motions
//  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

void orig_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 130.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 43);      // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

void score() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(16.0, 0.0, 130.0);      // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);     // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);  // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);        // Swing constants
  chassis.pid_odom_angular_constants_set(3, 0.0, 135);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(3, 0.0, 135);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(80_ms, 7_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(80_ms, 7_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 5_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(80_ms, 7_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(80_ms, 5_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(7_deg);
  chassis.pid_swing_chain_constant_set(7_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

void vroom() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 43);      // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(30_ms, 7_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(30_ms, 7_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(30_ms, 4_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(30_ms, 7_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(30_ms, 4_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(7_deg);
  chassis.pid_swing_chain_constant_set(7_deg);
  chassis.pid_drive_chain_constant_set(4_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

void RightControl() {
  orig_constants();

  chassis.odom_xy_set(-50, -12);
  chassis.drive_angle_set(115_deg);

  pros::delay(20);

  intake.move(127);
  descore.set_value(1);
  chassis.pid_odom_set({{{-23_in, -22_in}, fwd, 127}}, false);

  pros::delay(500);
  tongue.set_value(1);
  pros::delay(280);

  chassis.pid_turn_set(222_deg, TURN_SPEED);
  pros::delay(390);
  chassis.pid_odom_set({{{-55_in, -47.5_in, 246_deg}, fwd, 127}}, false);

  pros::delay(1350);
  chassis.pid_turn_set(270_deg, TURN_SPEED);
  pros::delay(150);
  chassis.pid_drive_set(15_in, 90, false);
  pros::delay(600);
  // chassis.pid_wait_until(5);
  // pros::delay(90);
  // chassis.pid_targets_reset();

  chassis.pid_drive_set(-6_in, DRIVE_SPEED, true);
  chassis.pid_turn_set(270_deg, TURN_SPEED);
  pros::delay(750);

  chassis.pid_odom_set({{{-22_in, -47_in, 270_deg}, rev, 127}}, false);
  pros::delay(750);
  chassis.pid_drive_set(-12_in, DRIVE_SPEED, true);
  intake.move(-100);
  pros::delay(150);
  // chassis.pid_wait_quick_chain();
  intake.move(127);
  // chassis.pid_odom_set({{{-48_in, -48_in, 270_deg}, rev, 127}}, false);
  descore.set_value(0);

  pros::delay(1750);

  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  tongue.set_value(0);
  pros::delay(450);
  descore.set_value(1);
  chassis.pid_drive_set(-10_in, 127, true);

  // chassis.pid_drive_set(13_in, 127, true);
  // intake.move(-127);
  // tongue.set_value(0);

  // pros::delay(400);
  // chassis.pid_turn_set(225_deg, TURN_SPEED);
  // pros::delay(450);

  // chassis.pid_odom_set({{{-21_in, -35.8_in}, rev, DRIVE_SPEED}}, false);
  // pros::delay(700);
  // chassis.pid_turn_set(272_deg, TURN_SPEED);

  // pros::delay(300);
  // chassis.pid_drive_set(-20_in, 127, true);
}

void good_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(10.5, 0.9, 96.0);      // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(15.0, 0.0, 24.5);    // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(2, 0.05, 22, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);       // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.2, 75);  // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(6, 0.6, 58);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 150_ms, 3_in, 350_ms, 350_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 4_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.7);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are **TRY THIS

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there **EXPERIMENT WITH THIS MAYBE
}

void straight() {
  chassis.pid_drive_set(4, 127, true);
}

void heading() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(10.5, 0, 96.0);        // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(15.0, 0.0, 30);      // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(2, 0.05, 22, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);       // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.2, 80);  // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(6, 0.6, 65);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 150_ms, 3_in, 350_ms, 350_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 4_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.7);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are **TRY THIS

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there **EXPERIMENT WITH THIS MAYBE
}

void odom_pure_pursuit_example() {
  // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
  orig_constants();
  chassis.pid_odom_set({{{6_in, 10_in}, fwd, DRIVE_SPEED},
                        {{0_in, 20_in}, fwd, DRIVE_SPEED},
                        {{0_in, 30_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  // Drive to 0, 0 backwards
  chassis.pid_odom_set({{0_in, 0_in}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

void odom_boomerang_injected_pure_pursuit_example() {
  default_constants();
  chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}
// 1255
void parkDistance() {
  double distance = frontDistance.get();  // Distance in millimeters

  // Check if the distance exceeds the threshold (e.g., 500 mm)
  if (distance > 1000) {
    // Drive forward if the distance is greater than the threshold
    chassis.pid_drive_set(20_in, 127, false);  // Drive forward 24 inches at full speed
    pros::delay(1850);
  }
}

// void tongueDistance(double target_distance_mm) {
//   // Get the current distance from the distance sensor
//   double distance = frontDistance.get();  // Distance in millimeters

//   // Check if the distance matches the target distance
//   if (distance == target_distance_mm) {
//     // Actuate the tongue mechanism
//     tongue.set_value(1);  // Extend the tongue mechanism
//     pros::delay(900);
//     tongue.set_value(0);  // Retract the tongue mechanism
//   }
// }

void revOdom() {
  chassis.drive_angle_set(-90_deg);
  orig_constants();
  pros::delay(20);
  chassis.pid_odom_set({{{-20_in, -10_in, 90_deg}, rev, 127}}, false);
}

void drive_until_distance(double threshold_mm) {
  // Continuously check the distance sensor
  while (frontDistance.get() > threshold_mm) {
    // Drive forward at a constant speed
    chassis.drive_set(90, 90);  // Set left and right motors to 60% power
    pros::delay(10);            // Small delay to prevent CPU overuse
  }

  // Stop the robot once the threshold is reached
  chassis.drive_set(0, 0);  // Stop the motors
}

void whoo() {
  drive_until_distance(500);
}

void right4p3() {
  orig_constants();
  chassis.odom_xy_set(-48_in, -12_in);
  chassis.drive_angle_set(180_deg);
  pros::delay(20);
  descore.set_value(1);
  intake.move(127);
  tongue.set_value(1);
  chassis.pid_drive_set(26, 127, true);
  pros::delay(650);
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  pros::delay(500);
  chassis.pid_drive_set(18, 50, false);

  // chassis.pid_wait_until(9);
  pros::delay(1090);

  // pros::delay(360);
  // chassis.pid_targets_reset();

  chassis.pid_odom_set({{{-31_in, -42_in, -90_deg}, rev, 127}}, true);  // first long goal
  pros::delay(650);
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  pros::delay(100);
  chassis.pid_drive_set(-21, 127, true);

  pros::delay(250);
  descore.set_value(0);
  intake.move(127);
  pros::delay(900);
  tongue.set_value(0);

  chassis.pid_swing_set(ez::LEFT_SWING, 45, 127, 0);

  pros::delay(900);
  chassis.pid_odom_set({{{-21_in, -12_in}, fwd, 127}}, true);
  pros::delay(500);
  tongue.set_value(1);
  pros::delay(700);
  tongue.set_value(0);
  pros::delay(350);
  chassis.pid_odom_set({{{-14.5_in, -5_in}, fwd, 127}}, true);
  intake.move(-95);
  pros::delay(1000);

  chassis.pid_odom_set({{{-36_in, -29.5_in}, rev, 127}}, true);  // push

  // chassis.pid_odom_set({{{-29_in, -37_in}, rev, 127}}, true);  // push
  // pros::delay(350);

  pros::delay(1150);
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  pros::delay(500);
  chassis.pid_drive_set(-25, 127, true);

  // descore.set_value(0);
  // pros::delay(400);
  // chassis.pid_drive_set(-20, 127, true);
  // pros::delay(1200);
  // chassis.pid_turn_set(-91_deg, TURN_SPEED);

  // pros::delay(250);
  // descore.set_value(0);
  // intake.move(127);
  // pros::delay(900);
  // tongue.set_value(0);

  // // chassis.pid_turn_set(0_deg, TURN_SPEED);

  // // pros::delay(450);

  // // chassis.pid_odom_set({{{-28_in, -13.5_in, 0_deg}, fwd, 127}}, true);

  // chassis.pid_drive_set(14, 127, true);
  // pros::delay(500);
  // descore.set_value(1);
  // chassis.pid_turn_set(45_deg, TURN_SPEED);
  // pros::delay(400);

  // chassis.pid_drive_set(26, 127, true);
  // intake2.move(0);
  // intake1.move(127);
  // intake3.move(127);
  // pros::delay(1000);
  // tongue.set_value(1);
  // pros::delay(400);
  // tongue.set_value(0);

  // // // chassis.pid_swing_set(ez::LEFT_SWING, 0, 127, 2);
  // // pros::delay(300);

  // // chassis.pid_drive_set(23, 127, true);
  // // pros::delay(900);

  // // {{-26_in, -12_in, 0_deg}, fwd, 127}

  // chassis.pid_odom_set({{{-13_in, -7_in}, fwd, 127}}, true);
  // pros::delay(1800);

  // chassis.pid_turn_set(45_deg, TURN_SPEED);

  // intake1.move(-127);
  // intake3.move(-127);
  // pros::delay(650);
  // chassis.pid_odom_set({{{-29_in, -28.3_in}, rev, 127}}, true);  // push
  // pros::delay(1000);

  // chassis.pid_turn_set(-90_deg, TURN_SPEED);

  // descore.set_value(0);
  // pros::delay(400);
  // chassis.pid_drive_set(-20, 127, true);
  // pros::delay(1200);
  // chassis.pid_turn_set(-91_deg, TURN_SPEED);
}

void newSolo() {
  orig_constants();
  chassis.odom_xy_set(-48_in, -12_in);
  chassis.drive_angle_set(180_deg);
  pros::delay(20);
  descore.set_value(1);
  intake.move(127);
  tongue.set_value(1);
  chassis.pid_drive_set(26, 127, true);
  pros::delay(650);
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  pros::delay(500);
  chassis.pid_drive_set(18, 50, false);

  chassis.pid_wait_until(9.5);
  pros::delay(425);
  // pros::delay(360);
  // chassis.pid_targets_reset();

  chassis.pid_odom_set({{{-31_in, -42.5_in, -90_deg}, rev, 127}}, true);  // first long goal
  pros::delay(650);
  chassis.pid_drive_set(-21, 127, true);
  pros::delay(250);
  descore.set_value(0);
  intake.move(127);
  pros::delay(900);
  tongue.set_value(0);

  // chassis.pid_turn_set(0_deg, TURN_SPEED);

  // pros::delay(450);

  // chassis.pid_odom_set({{{-28_in, -13.5_in, 0_deg}, fwd, 127}}, true);

  chassis.pid_drive_set(7, 127, true);
  pros::delay(300);
  descore.set_value(1);
  chassis.pid_turn_set(30_deg, TURN_SPEED);
  pros::delay(200);

  // // chassis.pid_swing_set(ez::LEFT_SWING, 0, 127, 2);
  // pros::delay(300);

  // chassis.pid_drive_set(23, 127, true);
  // pros::delay(900);

  // {{-26_in, -12_in, 0_deg}, fwd, 127}

  // blocks, intermediate, more blocks

  chassis.pid_odom_set({

                           {{-25_in, -20_in}, fwd, 127},

                           {{-26_in, 10_in, 0_deg}, fwd, 127},

                           {{-26_in, 30_in, 0_deg}, fwd, 127},
                       },  // park
                       true);

  pros::delay(1100);

  tongue.set_value(1);
  pros::delay(400);
  tongue.set_value(0);

  pros::delay(1250);  // was 1100
  tongue.set_value(1);

  pros::delay(300);  // was 300
  tongue.set_value(0);
  // chassis.pid_odom_set({{{-44_in, 51.4_in, -90_deg}, fwd, 127}}, true);

  chassis.pid_odom_set({
                           {{-40_in, 36_in}, fwd, 127},

                           {{-50_in, 59_in}, fwd, 127},
                       },  // park
                       true);

  pros::delay(1200);

  chassis.pid_turn_set(-90_deg, TURN_SPEED);

  chassis.pid_drive_set(-24, 127, true);
  pros::delay(800);
  descore.set_value(0);
  intake.move(127);
  pros::delay(1050);
  tongue.set_value(1);
  chassis.pid_turn_set(-88_deg, TURN_SPEED);
  // chassis.pid_odom_set({{{-75_in, 52_in, -90_deg}, fwd, 50}}, true);
  pros::delay(100);
  chassis.pid_drive_set(35, 127, true);

  chassis.pid_wait_until(13);
  chassis.pid_speed_max_set(50);
  descore.set_value(1);
  pros::delay(800);

  // pros::delay(1700);
  chassis.pid_drive_set(-12, 127, true);
  pros::delay(200);
  // chassis.pid_turn_set(-45_deg, TURN_SPEED);
  // pros::delay(100);
  chassis.pid_turn_set(-50_deg, TURN_SPEED);
  pros::delay(100);
  chassis.pid_drive_set(-40, 127, true);
  pros::delay(300);

  chassis.pid_odom_set({{{-14_in, 19.5_in}, rev, 127}}, true);
  pros::delay(1200);
  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  intake1.move(60);
  intake2.move(-40);
  intake3.move(60);
  tongue.set_value(0);
}

void parkTest() {
  chassis.odom_xy_set(72.2, 17.5);
  chassis.drive_angle_set(173_deg);
  orig_constants();
  pros::delay(20);
  intake.move(127);  // COMMENT THIS OUT LATER

  pod.set_value(1);
  descore.set_value(1);
  pros::delay(400);

  // chassis.pid_drive_set(93_in, 127, true);         //93 in was good
  // tongue.set_value(0);
  // pros::delay(1400);
  // chassis.pid_turn_set(175_deg, TURN_SPEED);
  tongue.set_value(1);
  pros::delay(500);
  tongue.set_value(0);
  chassis.pid_drive_set(36_in, 127, true);  // used to be 115
  pros::delay(1200);                        // 1350
  chassis.pid_drive_set(43_in, 95, true);
  // pros::delay(700);
  // chassis.pid_wait_until(19);
  // tongue.set_value(1);

  // pros::delay(200);
  // tongue.set_value(0);
  // pros::delay(1000);

  pros::delay(1700);

  chassis.odom_y_set(-68 + frontDistance.get() / 25.4);
  chassis.odom_x_set(72 - leftDistance.get() / 25.4);

  pros::delay(200);
  pod.set_value(0);

  pros::delay(450);

  chassis.pid_odom_set({{{16.6_in, -17_in}, rev, 127}}, true);  // y was 17
  pros::delay(2150);

  intake.move(-127);

  pros::delay(200);
  intake.move(0);
  chassis.pid_turn_set(115_deg, TURN_SPEED);
  pros::delay(200);

  intake1.move(65);
  intake2.move(-15);
  intake3.move(45);

  pros::delay(2600);

  chassis.pid_turn_set(128_deg, TURN_SPEED);
  pros::delay(100);
  chassis.pid_drive_set(-1, 127, false);
  pros::delay(300);

  intake.move(127);

  chassis.pid_odom_set({{{60_in, -49.5_in, 90_deg}, fwd, 90}}, true);  // 3rd match load
}

void skillsWR() {
  orig_constants();
  chassis.odom_xy_set(-50, 12);
  chassis.drive_angle_set(65_deg);

  // chassis.pid_drive_chain_constant_set(3_in);

  pros::delay(20);
  descore.set_value(1);
  intake.move(127);

  chassis.pid_odom_set({{{-10.5_in, 24_in, 75_deg}, fwd, 127}}, true);
  pros::delay(1600);
  // chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  pros::delay(500);

  chassis.pid_odom_set({{{-5_in, 12_in}, rev, 127}}, true);

  pros::delay(300);

  intake.move(-127);
  pros::delay(200);
  intake.move(0);
  pros::delay(100);
  chassis.pid_turn_set(-43_deg, TURN_SPEED);

  pros::delay(100);

  intake1.move(60);
  intake2.move(-35);
  intake3.move(60);

  pros::delay(900);

  intake.move(0);  // finished middle scoring

  // chassis.pid_drive_set(24, 127, true);

  // pros::delay(550);
  chassis.pid_odom_set({{{-54_in, 42_in, -90_deg}, fwd, 127}}, true);
  tongue.set_value(1);
  pros::delay(1000);

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  pros::delay(90);

  intake.move(127);
  chassis.pid_drive_set(17, 55, false);  // match load #1

  // chassis.pid_wait_until(16);
  pros::delay(2200);
  // chassis.pid_targets_reset();

  chassis.pid_drive_set(-8, 127, false);

  // pros::delay(350);
  // chassis.pid_turn_set(-135_deg, TURN_SPEED);
  // pros::delay(200);
  // chassis.pid_drive_set(-25, 127, true);

  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{-24_in, 59_in}, rev, 127}}, true);

  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-86.5_deg, TURN_SPEED);

  pros::delay(400);
  // chassis.odom_x_set(-68 + frontDistance.get() / 25.4);
  pros::delay(150);
  tongue.set_value(0);
  intake.move(0);

  // chassis.pid_odom_set({{{54_in, 59_in, -90_deg}, rev, 127}}, true);

  chassis.pid_drive_set(-74, 100, true);

  chassis.pid_wait_until(-58);
  // descore.set_value(1);
  chassis.pid_speed_max_set(50);

  chassis.pid_wait_quick_chain();
  score();
  pros::delay(50);

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  pros::delay(200);
  // chassis.pid_wait_quick_chain();

  // chassis.pid_wait_quick_chain();

  // pros::delay(700);

  // chassis.pid_odom_set({
  //                          {{48_in, 59_in, -89_deg}, rev, 127},

  //                          {{26_in, 49.5_in, 90_deg}, rev, 127},
  //                      },  // park
  //                      true);

  // pros::delay(4300);

  // chassis.pid_turn_set(45_deg, TURN_SPEED);
  // pros::delay(500);
  // chassis.pid_drive_set(-14, 127, false);
  // pros::delay(500);

  chassis.pid_odom_set({
                           {{30_in, 50_in}, rev, 127},

                           {{27_in, 50_in, 90_deg}, rev, 127},
                       },  // park
                       true);

  // chassis.pid_odom_set({{{29_in, 49_in, 90_deg}, rev, 127}}, false);  // first scoring

  pros::delay(2150);

  // pros::delay(2100);
  // chassis.pid_wait();

  chassis.pid_turn_set(90_deg, TURN_SPEED);

  chassis.pid_drive_set(-6, 127, true);
  pros::delay(300);

  // chassis.pid_turn_set(90_deg, TURN_SPEED);

  // pros::delay(200);
  // chassis.pid_drive_set(-9, 127, false);
  // pros::delay(250);

  orig_constants();
  intake2.move(100);
  intake1.move(-127);
  intake3.move(-127);

  pros::delay(150);

  chassis.odom_y_set(72 - leftDistance.get() / 25.4);
  descore.set_value(0);

  // chassis.odom_xy_set(29, 55);
  // chassis.drive_angle_set(90_deg);

  intake1.move(127);
  intake3.move(127);
  intake2.move(100);

  pros::delay(1300);
  chassis.pid_turn_set(88_deg, TURN_SPEED);
  pros::delay(200);
  tongue.set_value(1);

  pros::delay(100);

  // chassis.pid_odom_set({{{66_in, 50_in, 90_deg}, fwd, 127}}, true);

  // chassis.pid_drive_set(33, 127, true);

  // chassis.pid_wait_until(12);

  chassis.pid_odom_set({{{70_in, 52.5_in, 90_deg}, fwd, 100}}, true);

  pros::delay(300);
  descore.set_value(1);

  // chassis.pid_speed_max_set(45);
  pros::delay(2300);
  // chassis.odom_y_set(72 - leftDistance.get() / 25.4);

  chassis.pid_drive_set(-13, 127, true);

  pros::delay(450);

  chassis.pid_odom_set({{{29_in, 51_in, 90_deg}, rev, 127}}, true);  // second scoring
  pros::delay(1000);
  // chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-22, 127, false);
  tongue.set_value(0);
  pros::delay(300);  // USED TO BE 550
  intake.move(-127);

  pros::delay(100);
  descore.set_value(0);

  intake1.move(127);
  intake3.move(127);
  intake2.move(80);

  pros::delay(1400);

  // chassis.odom_xy_set(29, 51.6);
  // chassis.drive_angle_set(90_deg);

  // intake.move(127);       //comnment this out later

  chassis.pid_odom_set({
                           {{54.5_in, 34_in}, fwd, 127},

                           {{70.6_in, 12_in, 173_deg}, fwd, 127},  // 72.2
                       },                                          // park
                       true);

  chassis.pid_wait_until_index(0);

  descore.set_value(1);  // put this back in
  pros::delay(1550);

  chassis.pid_turn_set(175_deg, TURN_SPEED);

  // chassis.odom_xy_set(72.2, 17.5);
  // chassis.drive_angle_set(173_deg);
  // orig_constants();
  // pros::delay(20);
  // intake.move(127);  // COMMENT THIS OUT LATER

  pod.set_value(1);
  descore.set_value(1);
  pros::delay(400);

  // chassis.pid_drive_set(93_in, 127, true);         //93 in was good
  // tongue.set_value(0);
  // pros::delay(1400);
  // chassis.pid_turn_set(175_deg, TURN_SPEED);
  tongue.set_value(1);
  pros::delay(500);
  tongue.set_value(0);
  chassis.pid_drive_set(32_in, 127, true);  // used to be 115
  pros::delay(1200);                        // 1350
  chassis.pid_drive_set(44_in, 95, true);
  // pros::delay(700);
  // chassis.pid_wait_until(19);
  // tongue.set_value(1);

  // pros::delay(200);
  // tongue.set_value(0);
  // pros::delay(1000);

  pros::delay(1750);  // was 1700

  chassis.odom_y_set(-68 + frontDistance.get() / 25.4);
  chassis.odom_x_set(72 - leftDistance.get() / 25.4);

  pros::delay(200);
  pod.set_value(0);

  pros::delay(450);

  chassis.pid_odom_set({{{17_in, -12.5_in}, rev, 127}}, true);  // y was 17
  pros::delay(2150);

  intake.move(-127);

  pros::delay(200);
  intake.move(0);
  chassis.pid_turn_set(120_deg, TURN_SPEED);  // was 115
  pros::delay(200);

  intake1.move(65);
  intake2.move(-15);
  intake3.move(60);

  pros::delay(2600);

  chassis.pid_turn_set(128_deg, TURN_SPEED);
  pros::delay(100);
  chassis.pid_drive_set(-1, 127, false);
  pros::delay(300);

  intake.move(127);

  chassis.pid_odom_set({{{60_in, -48_in, 90_deg}, fwd, 90}}, true);  // 3rd match load

  pros::delay(1800);
  tongue.set_value(1);
  pros::delay(400);
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  pros::delay(200);

  intake.move(127);
  chassis.pid_drive_set(17, 70, false);

  chassis.pid_wait_until(11);
  pros::delay(1500);

  chassis.pid_drive_set(-6, 127, false);

  pros::delay(400);

  chassis.pid_odom_set({{{24_in, -65.5_in}, rev, 127}}, true);

  pros::delay(1750);
  chassis.pid_turn_set(92.5_deg, TURN_SPEED);
  pros::delay(600);

  tongue.set_value(0);
  intake.move(0);

  chassis.pid_drive_set(-72, 95, true);

  chassis.pid_wait_until(-52);
  // descore.set_value(1);
  chassis.pid_speed_max_set(50);
  // chassis.pid_wait_quick_chain();
  pros::delay(500);
  score();
  pros::delay(20);
  // chassis.pid_turn_set(-135_deg, TURN_SPEED);
  // pros::delay(450);
  // chassis.pid_drive_set(-14, 127, false);
  // pros::delay(500);

  chassis.pid_odom_set({
                           {{-30_in, -51_in}, rev, 127},

                           {{-20_in, -51_in, -90_deg}, rev, 127},
                       },  // park
                       true);

  // chassis.pid_odom_set({{{-20_in, -53.9_in, -90_deg}, rev, 127}}, true);  // 3rd scoring

  pros::delay(2400);

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  pros::delay(200);
  chassis.pid_drive_set(-12, 127, false);
  pros::delay(400);

  intake2.move(100);
  intake1.move(-127);
  intake3.move(-127);

  orig_constants();
  pros::delay(150);

  descore.set_value(0);
  chassis.odom_y_set(-72 + leftDistance.get() / 25.4);

  intake.move(127);

  pros::delay(1300);

  // chassis.odom_xy_set(-20, -55);
  // chassis.drive_angle_set(-90_deg);

  tongue.set_value(1);
  chassis.pid_odom_set({{{-44_in, -51_in, -90_deg}, fwd, 127}}, true);  // last match load
  pros::delay(1100);
  descore.set_value(1);
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  pros::delay(150);

  intake.move(127);
  chassis.pid_drive_set(21.5, 60, false);

  chassis.pid_wait_until(17.5);
  pros::delay(1400);

  chassis.pid_drive_set(-8, 127, true);
  pros::delay(200);

  chassis.pid_odom_set({{{-24_in, -51_in, -90_deg}, rev, 50}}, true);  // last long goal scoring

  pros::delay(1000);
  tongue.set_value(0);
  chassis.pid_drive_set(-21, 127, false);

  pros::delay(550);
  descore.set_value(0);

  intake2.move(100);
  intake1.move(127);
  intake3.move(127);

  pros::delay(1650);

  chassis.pid_odom_set({
                           {{-48_in, -38_in}, fwd, 127},
                           {{-58.5_in, -17_in, -2_deg}, fwd, 127},
                       },  // park
                       true);

  pros::delay(300);
  descore.set_value(1);
  pros::delay(1850);
  pod.set_value(1);
  chassis.pid_turn_set(-9_deg, TURN_SPEED);
  // descore.set_value(1);
  pros::delay(150);
  // chassis.pid_drive_set(52_in, 110, false);
  chassis.pid_drive_set(44_in, 127, false);
  // chassis.drive_set(110, 110);
}

// chassis.pid_turn_set(-135_deg, TURN_SPEED);

// chassis.pid_odom_set({{{-26_in, 44_in, -90_deg}, rev, 127}}, true);
// descore.set_value(0);

// chassis.pid_odom_set({{{-48_in, 46_in, -90_deg}, fwd, 127}}, true);

// pros::delay(600);

// chassis.odom_y_set(-72 + frontDistance.get() / 25.4);
// chassis.odom_x_set(72 - leftDistance.get() / 25.4);

void practiceDistance() {
  default_constants();

  chassis.odom_xy_set(-64, 24);
  chassis.drive_angle_set(180_deg);
  pod.set_value(1);
  // intake.move(127);

  chassis.pid_drive_set(76_in, 127, true);

  chassis.pid_wait();
  // pros::delay(10000);
  chassis.odom_y_set(-72 + frontDistance.get() / 25.4);
  chassis.odom_x_set(72 - leftDistance.get() / 25.4);
}

void what() {
  default_constants();
  chassis.odom_xy_set(12, 12);
  chassis.drive_angle_set(45_deg);
  chassis.pid_odom_set({{{36_in, 36_in, 45_deg}, fwd, 127}}, false);
}

void driveBack() {
  default_constants();
  chassis.pid_odom_set({{{0_in, -24_in, 0_deg}, rev, 127}}, false);
}

// printf("Odometry: X: %.2f, Y: %.2f, Theta: %.2f\n", chassis.odom_x_get(), chassis.odom_y_get(), chassis.odom_theta_get());

void LeftControl() {
  orig_constants();

  chassis.odom_xy_set(-50, 12);
  chassis.drive_angle_set(65_deg);

  pros::delay(20);

  intake.move(127);
  descore.set_value(1);
  chassis.pid_odom_set({{{-10_in, 31_in, 51_deg}, fwd, 127}}, false);

  pros::delay(450);
  tongue.set_value(1);
  pros::delay(340);  // was 180

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  pros::delay(390);
  chassis.pid_odom_set({{{-55_in, 48.5_in, -66_deg}, fwd, 127}}, false);

  pros::delay(1100);
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  pros::delay(200);
  chassis.pid_drive_set(19_in, 45, false);

  pros::delay(900);
  // chassis.pid_wait_until(6);
  // pros::delay(90);
  // chassis.pid_targets_reset();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED, true);
  // chassis.pid_turn_set(270_deg, TURN_SPEED);
  pros::delay(375);

  chassis.pid_odom_set({{{-14_in, 48_in, -90_deg}, rev, 127}}, false);
  pros::delay(750);
  chassis.pid_drive_set(-5_in, DRIVE_SPEED, true);
  intake.move(-100);
  pros::delay(150);
  // chassis.pid_wait_quick_chain();
  intake.move(127);
  // chassis.pid_odom_set({{{-48_in, -48_in, 270_deg}, rev, 127}}, false);
  descore.set_value(0);

  pros::delay(1650);

  chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
  tongue.set_value(0);
  pros::delay(300);
  descore.set_value(1);
  chassis.pid_drive_set(-7_in, DRIVE_SPEED, true);

  // chassis.pid_turn_set(-90_deg, TURN_SPEED);
  // pros::delay(100);
  // chassis.pid_drive_set(20_in, 127, true);
  // intake.move(0);
  // tongue.set_value(0);

  // pros::delay(400);
  // chassis.pid_turn_set(-135_deg, TURN_SPEED);
  // pros::delay(450);

  // chassis.pid_odom_set({{{-17_in, 60.9_in}, rev, DRIVE_SPEED}}, false);
  // pros::delay(1000);
  // chassis.pid_turn_set(268_deg, TURN_SPEED);

  // pros::delay(300);
  // chassis.pid_drive_set(-20_in, 127, true);
}

void RightTroy() {
  orig_constants();
  chassis.odom_xy_set(-50, -12);
  chassis.drive_angle_set(115_deg);

  pros::delay(20);
  descore.set_value(1);
  intake.move(127);

  chassis.pid_odom_set({{{-15_in, -31_in, 140_deg}, fwd, 127}}, true);
  pros::delay(550);
  tongue.set_value(1);
  pros::delay(350);
  chassis.pid_odom_set({{{-3_in, -51.5_in, 155_deg}, fwd, 127}}, true);
  pros::delay(200);
  tongue.set_value(0);
  pros::delay(1350);

  vroom();
  pros::delay(20);

  chassis.pid_odom_set({
                           {{-21_in, -34_in}, rev, 127},
                           //  {{-18_in, -35_in}, rev, 127},
                           {{-38_in, -47_in}, rev, 127},
                       },  // park
                       true);

  // chassis.pid_odom_set({{{-23.5_in, -34.5_in}, rev, 127}}, true);
  // pros::delay(1250);
  // chassis.pid_turn_set(2_deg, TURN_SPEED);
  // pros::delay(450);

  // heading();
  // chassis.pid_drive_set(-10.5, 127, true);

  // pros::delay(700);  // GO BACK TO 700
  // default_constants();
  // pros::delay(10);
  // chassis.pid_swing_set(ez::LEFT_SWING, -92, 127, 17);

  // pros::delay(750);

  chassis.pid_wait_quick_chain();
  orig_constants();

  // pros::delay(2900);
  // chassis.pid_turn_set(-90_deg, TURN_SPEED);

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  pros::delay(300);

  chassis.pid_drive_set(-14_in, 127, false);

  pros::delay(400);

  descore.set_value(0);
  intake2.move(127);
  intake3.move(-127);
  intake1.move(-127);

  pros::delay(150);
  intake.move(127);
  pros::delay(1200);
  tongue.set_value(1);
  chassis.pid_odom_set({{{-48_in, -45.5_in}, fwd, 127}}, true);  // match load

  pros::delay(700);
  chassis.pid_turn_set(-90_deg, TURN_SPEED);

  pros::delay(150);
  descore.set_value(1);
  chassis.pid_drive_set(19.5_in, 50, false);
  pros::delay(1050);

  chassis.pid_drive_set(-9, 127, false);
  pros::delay(300);
  chassis.pid_turn_set(45_deg, TURN_SPEED);
  pros::delay(500);

  tongue.set_value(0);
  // chassis.pid_drive_set(40, 127, false);
  // chassis.pid_wait_until(38_in);
  chassis.pid_odom_set({{{-8_in, -16_in, 55_deg}, fwd, 127}}, true);  // mid goal
  intake1.move(100);
  intake3.move(-127);
  intake2.move(-127);

  pros::delay(400);
  intake.move(0);
  pros::delay(550);
  intake.move(-127);
  pros::delay(200);

  // intake1.move(127);
  // intake3.move(-127);
  // intake2.move(-127);
  // pros::delay(200);
  // intake.move(0);
  chassis.pid_turn_set(47_deg, TURN_SPEED);
  // pros::delay(150);

  pros::delay(150);
  chassis.pid_drive_set(9_in, 127, false);
  // pros::delay(100);

  // chassis.pid_drive_set(-3.5_in, 127, false);
  // pros::delay(100);

  tongue.set_value(0);
  pros::delay(850);
  chassis.pid_drive_set(-30, 127, true);
  chassis.pid_wait_until(-26_in);
  descore.set_value(0);
  chassis.pid_odom_set({{{-29_in, -37_in}, rev, 127}}, true);  // push
  pros::delay(350);

  chassis.pid_turn_set(-90_deg, TURN_SPEED);

  descore.set_value(0);
  pros::delay(400);
  chassis.pid_drive_set(-20, 127, true);
  pros::delay(1200);
  chassis.pid_turn_set(-91_deg, TURN_SPEED);

  // pros::delay(750);
  // chassis.pid_turn_set(-115_deg, TURN_SPEED);
}

void troy() {
  orig_constants();
  chassis.odom_xy_set(-50, 12);
  chassis.drive_angle_set(65_deg);
  pros::delay(20);
  descore.set_value(1);
  intake.move(127);

  chassis.pid_odom_set({{{-14_in, 27_in, 50_deg}, fwd, 127}}, true);
  pros::delay(600);
  tongue.set_value(1);
  chassis.pid_odom_set({{{-3_in, 46_in, 20_deg}, fwd, 127}}, true);  // was 65
  pros::delay(300);
  tongue.set_value(0);
  pros::delay(1500);
  // tongue.set_value(1);
  // pros::delay(800);
  chassis.pid_odom_set({{{-34_in, 32.5_in, 90_deg}, rev, 127}}, true);

  pros::delay(1200);
  // chassis.pid_turn_set(178_deg, TURN_SPEED);
  // pros::delay(450);

  // chassis.pid_drive_set(-13, 127, true);

  // pros::delay(950);

  chassis.pid_swing_set(ez::RIGHT_SWING, -90, -127, 1);

  pros::delay(850);
  chassis.pid_drive_set(-10_in, 127, false);

  // chassis.pid_odom_set({{{-24_in, 32_in}, fwd, 127}}, true);
  // chassis.pid_odom_set({{{-16_in, 43.5_in}, rev, 127}}, true);
  // pros::delay(2000);
  // chassis.pid_turn_set(-90_deg, TURN_SPEED);
  // chassis.pid_drive_set(-7, 127, false);
  // pros::delay(900);
  // chassis.pid_drive_set(-4, 127, false);

  // chassis.pid_drive_set(-8, 127, true);

  // chassis.pid_odom_set({{{-32_in, 26_in}, rev, 127}}, true);
  pros::delay(750);
  // chassis.pid_odom_set({{{-34_in, 48_in, -90_deg}, rev, 127}}, true);
  // pros::delay(2100);
  // chassis.pid_odom_set({{{-26_in, 48_in, -90_deg}, rev, 127}}, true);
  // pros::delay(2000);
  // chassis.pid_drive_set(-8, 127, true);
  // pros::delay(500);

  // chassis.pid_turn_set(-87_deg, TURN_SPEED);

  descore.set_value(0);
  intake2.move(127);
  intake3.move(-127);
  intake1.move(-127);
  // chassis.pid_drive_set(-4, 127, false);
  pros::delay(150);
  intake.move(127);
  pros::delay(1200);
  tongue.set_value(1);
  chassis.pid_odom_set({{{-48_in, 42.5_in}, fwd, 127}}, true);  // match load

  pros::delay(650);
  chassis.pid_turn_set(-90_deg, TURN_SPEED);

  pros::delay(150);
  descore.set_value(1);
  chassis.pid_drive_set(18_in, 70, false);
  pros::delay(1000);

  // chassis.pid_wait_until(14.7_in);
  // pros::delay(20);

  chassis.pid_drive_set(-6, 127, false);
  pros::delay(300);
  // chassis.pid_odom_set({{{-27_in, 47_in, -90_deg}, rev, 127}}, true);
  heading();
  chassis.pid_odom_set({{{3_in, 6.5_in, -45_deg}, rev, 127}}, true);  // mid goal

  // chassis.pid_odom_set({
  //                          {{-20_in, 20_in}, rev, 127},
  //                          {{1_in, 5.5_in, -45_deg}, rev, 127},
  //                      },  // park
  //                      true);

  pros::delay(1200);
  default_constants();

  intake1.move(127);
  intake3.move(-127);
  intake2.move(-127);
  pros::delay(200);
  intake.move(0);
  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_drive_set(-3.5_in, 127, false);
  pros::delay(100);
  // pros::delay(500);

  // pros::delay(300);

  intake1.move(60);
  intake2.move(-50);
  intake3.move(60);
  tongue.set_value(0);
  pros::delay(1400);
  chassis.pid_drive_set(30, 127, true);
  chassis.pid_wait_until(26_in);
  chassis.pid_odom_set({{{-18_in, 35_in}, fwd, 127}}, true);  // push
  pros::delay(550);
  // chassis.pid_turn_set(84_deg, TURN_SPEED);
  // pros::delay(700);
  // chassis.pid_drive_set(6, 127, false);
  // pros::delay(300);
  chassis.pid_turn_set(85_deg, TURN_SPEED);

  descore.set_value(0);
  pros::delay(500);
  chassis.pid_drive_set(25, 127, true);
  // chassis.pid_wait_until(33);
  pros::delay(800);
  chassis.pid_turn_set(115_deg, TURN_SPEED);

  // pros::delay(700);
  // intake.move(0);

  // pros::delay(700);
  // intake.move(0);

  // chassis.pid_odom_set({
  //                          {{-24_in, 26_in, 45_deg}, rev, 127},          // set up in front of blocks
  //                          {{-44_in, 44_in, 180_deg}, fwd, DRIVE_SPEED},
  //                          {{-22_in, 44_in, -90_deg}, fwd, DRIVE_SPEED},
  //                      },
  //                      true);

  // chassis.pid_wait_quick_chain();
  // chassis.pid_turn_set(-90_deg, TURN_SPEED);
  // pros::delay(700);
  // chassis.pid_drive_set(-16, 127, true);
}

void SoloSigWP() {
  default_constants();
  chassis.odom_xy_set(-48_in, -12_in);
  chassis.drive_angle_set(180_deg);
  descore.set_value(1);
  intake.move(127);
  tongue.set_value(1);
  chassis.pid_drive_set(29, 127, true);
  pros::delay(570);
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  pros::delay(500);
  chassis.pid_drive_set(18, 50, false);

  chassis.pid_wait_until(9.5);
  pros::delay(600);
  // pros::delay(360);
  // chassis.pid_targets_reset();

  chassis.pid_odom_set({{{-31_in, -44.5_in, -90_deg}, rev, 127}}, true);  // first long goal
  pros::delay(700);
  chassis.pid_drive_set(-21, 127, true);
  pros::delay(300);
  descore.set_value(0);
  intake.move(127);
  pros::delay(1200);
  tongue.set_value(0);
  chassis.pid_turn_set(0_deg, TURN_SPEED);

  pros::delay(600);
  descore.set_value(1);
  chassis.pid_odom_set({{{-28_in, -13.5_in, 0_deg}, fwd, 127}}, true);
  pros::delay(600);

  tongue.set_value(1);
  pros::delay(250);
  tongue.set_value(0);
  chassis.pid_drive_set(31, 127, true);
  pros::delay(700);
  chassis.pid_odom_set({{{-24_in, 30_in, 0_deg}, fwd, 127}}, true);
  // chassis.pid_drive_set(39, 127, true);
  pros::delay(850);
  tongue.set_value(1);

  pros::delay(300);

  chassis.pid_turn_set(-55_deg, TURN_SPEED);
  pros::delay(400);

  chassis.pid_odom_set({{{-12_in, 15_in}, rev, 127}}, false);
  // tongue.set_value(1);
  pros::delay(450);
  chassis.pid_turn_set(-55_deg, TURN_SPEED);
  intake.move(-127);

  pros::delay(250);
  intake1.move(90);
  intake2.move(-80);
  intake3.move(90);
  pros::delay(700);
  intake.move(0);

  chassis.pid_drive_set(31, 127, true);
  pros::delay(700);
  intake.move(127);
  chassis.pid_odom_set({{{-63_in, 51.4_in, -90_deg}, fwd, 127}}, true);
  pros::delay(1000);
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  pros::delay(100);
  chassis.pid_drive_set(15, 50, false);
  pros::delay(1300);

  // chassis.pid_wait_until(4);
  // pros::delay(470);
  // chassis.pid_targets_reset();
  chassis.pid_odom_set({{{-30_in, 54_in, -90_deg}, rev, 127}}, true);

  pros::delay(600);
  chassis.pid_drive_set(-20, 127, false);
  pros::delay(350);
  descore.set_value(0);
  intake.move(127);
  pros::delay(1200);
  chassis.pid_drive_set(6, 127, true);
}

void square() {
  default_constants();
  chassis.odom_xyt_set(0_in, 0_in, -45_deg);

  chassis.pid_odom_set({
                           {{0_in, 48_in, 0_deg}, fwd, 127},
                           {{48_in, 50_in, 90_deg}, fwd, 127},
                           {{50_in, 0_in, 180_deg}, fwd, 127},
                           {{0_in, 0_in, -45_deg}, fwd, 127},
                       },  // park
                       true);
}

void odom_drive_example() {
  // This works the same as pid_drive_set, but it uses odom instead!
  // You can replace pid_drive_set with pid_odom_set and your robot will
  // have better error correction.

  // default_constants();

  chassis.odom_xyt_set(0_in, 0_in, -45_deg);
  // pod.set_value(1);

  chassis.pid_odom_set({{{0_in, 51_in, 0_deg}, fwd, DRIVE_SPEED}}, false);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{51_in, 51_in, 90_deg}, fwd, DRIVE_SPEED}}, false);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{51_in, 0_in, 180_deg}, fwd, DRIVE_SPEED}}, false);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{0_in, 0_in, 270_deg}, fwd, DRIVE_SPEED}}, false);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
}

void drive_and_turn() {
  default_constants();
  chassis.pid_drive_set(17_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(17_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(17_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(17_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
}

void driving() {
  default_constants();

  chassis.pid_odom_set({
                           {{0_in, 48_in}, fwd, 127},
                           {{0_in, 96_in}, fwd, 127},
                           {{0_in, 0_in}, rev, 127},
                       },  // park
                       true);

  // chassis.pid_wait_until_index(2);
  // chassis.pid_drive_set(4, 127, true);
  // chassis.pid_drive_set(48, 127, true);
  // chassis.pid_wait();

  // chassis.pid_drive_set(48, 127, true);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-96, 127, true);
  // chassis.pid_wait();
}

// void distanceTest(){

//   chassis.odom_xyt_set(-48_in, 2_in, 180_deg);

//   rightDistance.get();
// }

void soloR() {
  default_constants();
  chassis.odom_xyt_set(-48_in, -15_in, 180_deg);
  intake.move(127);
  tongue.set_value(1);
  chassis.pid_drive_set(30, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(20.7, 65, false);

  chassis.pid_wait_until(10);
  pros::delay(620);
  chassis.pid_targets_reset();

  // chassis.pid_odom_set({{{-60.5_in, -44_in, -91_deg}, fwd, 127}}, true);

  // chassis.pid_wait_quick_chain();
  // pros::delay(180);

  // chassis.pid_drive_set(-10.7, 127, true);

  // chassis.pid_wait_quick_chain();
  // chassis.pid_turn_set(90_deg, TURN_SPEED);
  // chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-30_in, -45_in, -91_deg}, rev, 127}}, false);  // first long goal

  intake2.move(-40);
  intake3.move(-40);
  pros::delay(10);
  chassis.pid_wait_quick_chain();
  descore.set_value(1);
  chassis.pid_drive_set(-2.5, DRIVE_SPEED, true);
  intake.move(127);
  pros::delay(700);
  chassis.pid_wait_quick_chain();  // finished scoring
  descore.set_value(0);
  chassis.pid_drive_set(18.5, 117, true);
  intake1.move(127);
  intake2.move(0);
  intake3.move(0);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(41_deg, TURN_SPEED);
  tongue.set_value(0);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-12_in, -8_in, 45_deg}, fwd, 75}}, true);  // low goal
  chassis.pid_wait_quick_chain();
  intake.move(-95);
  pros::delay(1100);
  chassis.pid_wait_quick_chain();
  intake.move(127);
  chassis.pid_drive_set(-14.5, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  // descore.set_value(0);

  chassis.pid_odom_set({{{-22.5_in, 25.5_in, 0_deg}, fwd, 110}}, true);  // second blocks
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-13.5, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  intake.move(-127);
  pros::delay(150);
  // chassis.pid_wait_quick_chain();

  // CHANGE THESE 3 BACK
  intake1.move(127);
  intake2.move(-127);
  intake3.move(127);

  // pros::delay(190);
  // chassis.pid_wait_quick_chain();
  // intake.move(0);

  // chassis.pid_odom_set({{{-48_in, 51_in, -92_deg}, fwd, 60}}, true);
  // tongue.set_value(1);
  // chassis.pid_wait_quick_chain();

  // chassis.pid_drive_set(12.5, DRIVE_SPEED, true);
  // pros::delay(380);
  // chassis.pid_wait_quick_chain();

  // chassis.pid_odom_set({{{-30_in, 52_in, -91_deg}, rev, 90}}, true); //last scoring

  // intake.move(-40);
  // pros::delay(10);
  // chassis.pid_wait_quick_chain();
  // descore.set_value(1);
  // chassis.pid_drive_set(-4, DRIVE_SPEED, true);
  // intake.move(127);

  // pros::delay(1575);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(8, 127, true);
  // chassis.pid_wait_quick_chain();

  // chassis.pid_drive_set(-11, DRIVE_SPEED, true);
}

void skills() {
  default_constants();
  chassis.odom_xyt_set(-48_in, -15_in, 180_deg);
  intake.move(127);
  tongue.set_value(1);
  chassis.pid_drive_set(30.2, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(14.6, 90, true);
  pros::delay(1500);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-10.7, 127, true);

  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-29_in, -44.5_in, -91_deg}, rev, 127}}, true);  // first long goal

  // pros::delay(10);
  chassis.pid_wait_quick_chain();

  intake.move(-127);
  pros::delay(10);
  descore.set_value(1);
  intake.move(0);
  // chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-2.5, 80, true);
  pros::delay(190);
  intake.move(127);
  chassis.pid_wait_quick_chain();

  pros::delay(1000);
  chassis.pid_wait_quick_chain();  // finished scoring

  chassis.pid_drive_set(12, 117, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-12, 127, true);
  chassis.pid_wait_quick_chain();

  // chassis.odom_xyt_set(-27_in, -43.2_in, -91_deg);

  intake.move(-50);
  chassis.pid_drive_set(22, 117, true);
  descore.set_value(0);
  chassis.pid_wait_quick_chain();
  intake.move(127);
  chassis.pid_turn_set(-135_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-17, 127, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-91_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // chassis.pid_odom_boomerang_set({{-19_in, -30_in, -91_deg}, rev, 127}, true);

  // chassis.pid_odom_set({{{-19_in, -30_in, -91_deg}, rev, 127}}, true);

  // chassis.pid_wait();
  tongue.set_value(0);
  chassis.pid_drive_set(-48.5, 120, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{47_in, -44.7_in, -50_deg}, rev, 127}}, true);  // coordinate before second tube
  chassis.pid_wait();

  chassis.pid_turn_set(88_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  tongue.set_value(1);
  intake.move(127);
  chassis.pid_drive_set(14.2, 110, true);
  chassis.pid_wait_quick_chain();
  pros::delay(1000);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{36_in, -44.5_in, -91_deg}, rev, 90}}, true);  // second scoring of long goal

  chassis.pid_wait_quick_chain();
  intake.move(-127);
  descore.set_value(1);
  pros::delay(10);
  intake.move(0);
  pros::delay(20);
  chassis.pid_wait_quick_chain();
  // intake.move(-127);
  // pros::delay(10);
  // chassis.pid_wait_quick_chain();
  // descore.set_value(1);
  chassis.pid_drive_set(-1.8, 80, true);
  pros::delay(100);
  intake.move(127);
  //
  chassis.pid_wait_quick_chain();
  pros::delay(80);
  // pros::delay(1575);
  chassis.pid_wait_quick_chain();

  // chassis.odom_xyt_set(34.2_in, -45.8_in, 91_deg);

  chassis.pid_drive_set(13.5, 127, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(2_deg, TURN_SPEED);
  descore.set_value(0);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{35_in, 51.5_in, 2_deg}, fwd, 127}}, true);  // coordinate before third tube
  chassis.pid_wait();
  chassis.pid_turn_set(88_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  intake.move(127);
  chassis.pid_drive_set(22.5, 110, true);
  chassis.pid_wait_quick_chain();
  pros::delay(1100);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{27.5_in, 50_in, 88_deg}, rev, 80}}, true);  // 3rd scoring
  chassis.pid_wait_quick_chain();

  intake.move(-127);
  pros::delay(10);
  descore.set_value(1);
  intake.move(0);
  pros::delay(10);
  // intake.move(-127);
  // pros::delay(10);
  // chassis.pid_wait_quick_chain();
  // descore.set_value(1);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-2, 80, true);
  pros::delay(220);
  intake.move(127);
  chassis.pid_wait_quick_chain();
  pros::delay(1600);
  chassis.pid_wait_quick_chain();

  // chassis.odom_xyt_set(28_in, 48_in, 88_deg);

  chassis.pid_drive_set(13, 117, true);

  // descore.set_value(0);

  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-18, 127, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(89_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // chassis.pid_odom_set({{{20_in, 36_in, 91_deg}, rev, 127}}, true);
  // chassis.pid_wait();
  tongue.set_value(0);
  chassis.pid_drive_set(-46, 120, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{-48_in, 49.5_in, 140_deg}, rev, 127}}, true);  // set up in front of 4th tube
  chassis.pid_wait();
  // chassis.pid_drive_set(4, DRIVE_SPEED, true);
  // chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-95_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  descore.set_value(0);
  tongue.set_value(1);
  intake.move(127);
  chassis.pid_drive_set(16.5, 100, true);
  chassis.pid_wait_quick_chain();
  pros::delay(1100);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-31_in, 51.5_in, -93_deg}, rev, 90}}, true);  // last scoring

  chassis.pid_wait_quick_chain();
  intake.move(-127);
  pros::delay(10);
  descore.set_value(1);
  intake.move(0);
  pros::delay(100);
  chassis.pid_wait_quick_chain();

  // intake.move(-127);
  // pros::delay(10);
  // chassis.pid_wait_quick_chain();
  // descore.set_value(1);
  chassis.pid_drive_set(-2.5, 80, true);
  pros::delay(160);
  intake.move(127);
  chassis.pid_wait_quick_chain();
  pros::delay(1575);
  chassis.pid_wait_quick_chain();

  // chassis.odom_xyt_set(-28.5_in, 51.5_in, -93_deg);
  intake.move(-127);

  chassis.pid_drive_set(8, 127, true);
  chassis.pid_wait_quick_chain();
  tongue.set_value(0);
  chassis.pid_odom_set({{{-65_in, 16.5_in, 179_deg}, fwd, 35}}, true);  // set up in front of park

  // tongue.set_value(1);

  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-18, DRIVE_SPEED, true);
  pod.set_value(1);
  chassis.pid_wait();
  chassis.pid_drive_set(45, 127, true);
  chassis.pid_wait_quick_chain();
  tongue.set_value(0);

  // chassis.pid_odom_set({{{-5_in, -48_in, -90_deg}, fwd, 50}}, true);
  // chassis.pid_wait_quick_chain();
  // pros::delay(400);
  // chassis.pid_drive_set(-6, DRIVE_SPEED, true);
}

void rushRightYay() {
  default_constants();
  chassis.odom_xyt_set(-35_in, -14.37_in, 90_deg);
  intake.move(127);
  chassis.pid_odom_set({{{-16_in, -19_in, 112_deg}, fwd, 127}}, true);

  chassis.pid_wait_quick_chain();
  intake.move(127);

  chassis.pid_odom_set({{{1.4_in, -40_in, 180_deg}, fwd, 127}}, true);
  chassis.pid_wait_quick_chain();
  tongue.set_value(1);
  chassis.pid_wait_quick_chain();
  // pros::delay(100);

  // chassis.pid_drive_set(-6, 127, true);

  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-14, DRIVE_SPEED, true);
  tongue.set_value(0);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{-16.5_in, -27_in, -95_deg}, rev, 127}}, true);

  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(45_deg, TURN_SPEED);

  chassis.pid_wait();
  chassis.pid_drive_set(19, 127, true);
  chassis.pid_wait_quick_chain();

  // chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(14.5, DRIVE_SPEED, true);
  // chassis.pid_wait_quick_chain();
  intake.move(-127);
  pros::delay(1050);

  intake.move(0);
  chassis.pid_drive_set(-47, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  tongue.set_value(1);
  chassis.pid_wait_quick_chain();
  intake.move(127);
  chassis.pid_drive_set(19, 65, true);

  chassis.pid_wait_until(10);
  pros::delay(680);
  chassis.pid_targets_reset();
  // pros::delay(445);
  // chassis.pid_wait_quick_chain();

  // chassis.pid_drive_set(-26, DRIVE_SPEED, true);
  chassis.pid_odom_set({{{-16_in, -48.5_in, -90_deg}, rev, 127}}, true);

  intake.move(-50);
  pros::delay(10);
  intake.move(0);

  descore.set_value(1);
  pros::delay(10);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-5, DRIVE_SPEED, true);
  intake.move(127);

  // intake.move(-127);
}

void leftNineBall() {
  default_constants();
  chassis.odom_xyt_set(-35_in, 14.37_in, 90_deg);
  intake.move(127);
  chassis.pid_odom_set({{{-18_in, 19_in, 22_deg}, fwd, 127}}, true);

  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{0.5_in, 45.5_in, -7_deg}, fwd, 127}}, true);
  chassis.pid_wait_quick_chain();
  tongue.set_value(1);

  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-14, 127, true);
  chassis.pid_wait_quick_chain();
  tongue.set_value(0);
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-12, 127, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  intake.move(0);
  chassis.pid_wait();

  chassis.pid_odom_set({{{-38_in, 52_in, -45_deg}, fwd, 127}}, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);

  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-20_in, 50.5_in, -92_deg}, rev, 127}}, true);
  descore.set_value(1);
  intake2.move(-120);
  intake3.move(-120);
  pros::delay(30);

  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-6, 127, true);
  intake.move(127);
  pros::delay(700);

  tongue.set_value(1);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{-38_in, 51_in, -90_deg}, fwd, 127}}, true);

  chassis.pid_wait_quick_chain();
  intake.move(127);
  descore.set_value(0);
  chassis.pid_drive_set(19, 127, true);

  chassis.pid_wait_until(13);
  pros::delay(625);
  chassis.pid_targets_reset();

  chassis.pid_odom_set({{{-21_in, 51_in, -90_deg}, rev, 70}}, true);

  descore.set_value(1);
  intake1.move(0);
  intake2.move(-120);
  intake3.move(-120);

  pros::delay(30);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-7, 127, true);
  intake.move(127);
}

void rushLeft() {
  default_constants();
  chassis.odom_xyt_set(-35_in, 14.37_in, 90_deg);
  intake.move(127);
  chassis.pid_odom_set({{{-18_in, 19_in, 22_deg}, fwd, 127}}, true);

  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{-0.5_in, 45_in, -8.5_deg}, fwd, 127}}, true);
  chassis.pid_wait_quick_chain();
  tongue.set_value(1);
  chassis.pid_wait_quick_chain();
  // pros::delay(100);

  // chassis.pid_drive_set(-6, 127, true);

  // chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-13, DRIVE_SPEED, true);
  tongue.set_value(0);
  chassis.pid_wait_quick_chain();

  intake.move(0);
  chassis.pid_odom_set({{{-13_in, 21.5_in, 40_deg}, rev, 127}}, true);

  // chassis.pid_wait_quick_chain();
  // chassis.pid_odom_set({{{-13_in, -25_in}, rev, 90}}, true);

  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  tongue.set_value(1);

  // tongue.set_value(0);
  chassis.pid_wait();
  chassis.pid_drive_set(-5, 40, true);
  chassis.pid_wait_quick_chain();
  intake.move(-127);
  pros::delay(110);
  intake.move(0);
  chassis.pid_wait_quick_chain();
  intake1.move(90);
  intake2.move(-90);
  intake3.move(90);
  pros::delay(190);
  chassis.pid_wait_quick_chain();
  intake.move(0);

  // intake.move(-127);
  // pros::delay(950);

  // intake.move(0);
  // chassis.pid_drive_set(54, 100, true);

  chassis.pid_odom_set({{{-38_in, 51.5_in, -45_deg}, fwd, 127}}, true);
  tongue.set_value(1);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);

  // tongue.set_value(1);
  chassis.pid_wait_quick_chain();
  intake.move(127);
  chassis.pid_drive_set(19, 127, true);

  chassis.pid_wait_until(13);
  pros::delay(550);
  chassis.pid_targets_reset();
  // chassis.pid_wait_quick_chain();
  // pros::delay(400);
  // chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-20_in, 50.7_in, -91_deg}, rev, 70}}, true);

  descore.set_value(1);
  intake2.move(-120);
  intake3.move(-120);
  pros::delay(30);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-6, DRIVE_SPEED, true);
  intake.move(127);
  // tongue.set_value(0);
}

void firstautoyay() {
  default_constants();
  chassis.odom_xyt_set(-52_in, -13_in, 146_deg);
  intake1.move(127);
  chassis.pid_odom_set({
                           {{-38_in, -28_in, 146_deg}, fwd, 50},          // set up in front of blocks
                           {{-15_in, -14_in, 50_deg}, fwd, DRIVE_SPEED},  // Middle goal
                                                                          // {{6.63_in, 18.42_in, 44.7_deg}, fwd, DRIVE_SPEED},
                                                                          //  {{-12_in, -15_in}, fwd, DRIVE_SPEED}  // THIS IS THE MIDDLE GOAL
                       },
                       true);
  chassis.pid_wait();
  chassis.pid_turn_set(50_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(1, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  pros::delay(600);
  chassis.pid_wait_quick_chain();

  intake.move(-115);
  pros::delay(1200);
  chassis.pid_drive_set(-6, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  intake1.move(127);

  chassis.pid_odom_set({{{-12_in, 18_in}, fwd, DRIVE_SPEED}},  // SECOND FUCKING BLOCKS
                       true);

  chassis.pid_wait_quick_chain();
  pros::delay(700);
  chassis.pid_odom_set({{{-3_in, 8_in, 340_deg}, rev, 65}},  // THE TOP MIDDLE GOAL
                       true);

  chassis.pid_wait_quick_chain();
  // middle.set_value(1);
  intake.move(127);
}

// void odom_boomerang_injected_pure_pursuit_example() {
//   chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
//                         {{12_in, 24_in}, fwd, DRIVE_SPEED},
//                         {{24_in, 24_in}, fwd, DRIVE_SPEED}},
//                        true);
//   chassis.pid_wait();

//   chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
//                        true);
//   chassis.pid_wait();
// }

// //***faulty rotation sensor???
// void odom_boomerang_example() {
//   // Drive forward to (0, 36) forward, end at 45 degrees

//   chassis.pid_odom_set({
//                            {0_in, 30_in},
//                            fwd,
//                            110,
//                        },
//                        true);
//   chassis.pid_wait();
//   chassis.pid_turn_set(135_deg, TURN_SPEED);
//   chassis.pid_wait();
//   chassis.pid_odom_set({{30_in, 0_in}, fwd, 110}, true);
//   chassis.pid_wait();

//   // Drive back to (0, 0) backward, end at 0 degrees
//   // chassis.pid_odom_set({{0, 0, 0}, rev, 110});
//   // chassis.pid_wait();

//   // pros::delay(1000);

//   // chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
//   //                      true);
//   // chassis.pid_wait();
// }

// void testStuff() {
//   chassis.pid_turn_set({10, 26}, fwd, 20);
//   chassis.pid_wait();
//   chassis.pid_odom_set({{10_in, 26_in}, fwd, 20});
//   chassis.pid_wait();
// }

// ///
// // Drive Example
// ///
// void drive_example() {
//   // The first parameter is target inches
//   // The second parameter is max speed the robot will drive at
//   // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
//   // for slew, only enable it when the drive distance is greater than the slew distance + a few inches
//   chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
//   chassis.pid_turn_set(135_deg, TURN_SPEED);
//   chassis.pid_wait();
//   chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
// }

// ///
// // Turn Example
// ///

// void angles() {
//   chassis.pid_turn_set(90_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   chassis.pid_turn_set(180_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   // chassis.pid_turn_set(180_deg, TURN_SPEED);
//   // chassis.pid_wait();
// }

// ///
// // Combining Turn + Drive
// ///

// ///
// // Wait Until and Changing Max Speed
// ///
// void wait_until_change_speed() {
//   // pid_wait_until will wait until the robot gets to a desired position

//   // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
//   chassis.pid_drive_set(24_in, 30, true);
//   chassis.pid_wait_until(6_in);
//   chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
//   chassis.pid_wait();

//   chassis.pid_turn_set(45_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_turn_set(-45_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_turn_set(0_deg, TURN_SPEED);
//   chassis.pid_wait();

//   // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
//   chassis.pid_drive_set(-24_in, 30, true);
//   chassis.pid_wait_until(-6_in);
//   chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
//   chassis.pid_wait();
// }

// ///
// // Swing Example
// ///
// void swing_example() {
//   // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
//   // The second parameter is the target in degrees
//   // The third parameter is the speed of the moving side of the drive
//   // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

//   chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
//   chassis.pid_wait();

//   chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
//   chassis.pid_wait();

//   chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
//   chassis.pid_wait();

//   chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
//   chassis.pid_wait();
// }

// ///
// // Motion Chaining
// ///
// void motion_chaining() {
//   // Motion chaining is where motions all try to blend together instead of individual movements.
//   // This works by exiting while the robot is still moving a little bit.
//   // To use this, replace pid_wait with pid_wait_quick_chain.
//   chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();

//   chassis.pid_turn_set(45_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   chassis.pid_turn_set(-45_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   chassis.pid_turn_set(0_deg, TURN_SPEED);
//   chassis.pid_wait();

//   // Your final motion should still be a normal pid_wait
//   chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
// }

// ///
// // Auto that tests everything
// ///
// void combining_movements() {
//   chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
//   chassis.pid_wait();

//   chassis.pid_turn_set(45_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
//   chassis.pid_wait();

//   chassis.pid_turn_set(0_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_drive_set(-12_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
// }

// ///
// // Interference example
// ///
// void tug(int attempts) {
//   for (int i = 0; i < attempts - 1; i++) {
//     // Attempt to drive backward
//     printf("i - %i", i);
//     chassis.pid_drive_set(-12_in, 127);
//     chassis.pid_wait();

//     // If failsafed...
//     if (chassis.interfered) {
//       chassis.drive_sensor_reset();
//       chassis.pid_drive_set(-2_in, 20);
//       pros::delay(1000);
//     }
//     // If the robot successfully drove back, return
//     else {
//       return;
//     }
//   }
// }

// // If there is no interference, the robot will drive forward and turn 90 degrees.
// // If interfered, the robot will drive forward and then attempt to drive backward.
// void interfered_example() {
//   chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();

//   if (chassis.interfered) {
//     tug(3);
//     return;
//   }

//   chassis.pid_turn_set(90_deg, TURN_SPEED);
//   chassis.pid_wait();
// }

// ///
// // Odom Drive PID
// ///

// ///
// // Odom Pure Pursuit
// ///
// void odom_pure_pursuit_example() {
//   // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
//   chassis.pid_odom_set({{{6_in, 10_in}, fwd, 80},
//                         {{0_in, 40_in}, fwd, 80},
//                         {{0_in, 50_in}, fwd, 80}},
//                        true);
//   chassis.pid_wait();

//   pros::delay(1500);

//   // Drive to 0, 0 backwards
//   chassis.pid_odom_set({{0_in, 0_in}, rev, 80},
//                        true);
//   chassis.pid_wait();
// }

// ///
// // Odom Pure Pursuit Wait Until
// ///
// void odom_pure_pursuit_wait_until_example() {
//   chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
//                         {{12_in, 24_in}, fwd, DRIVE_SPEED},
//                         {{24_in, 24_in}, fwd, DRIVE_SPEED}},
//                        true);
//   chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
//   // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
//   chassis.pid_wait();
//   // Intake.move(0);  // Turn the intake off
// }

// ///
// // Odom Boomerang
// ///

// ///
// // Odom Boomerang Injected Pure Pursuit
// ///

// ///
// // Calculate the offsets of your tracking wheels
// ///
void measure_offsets() {
  // Number of times to test
  int iterations = 10;

  // Our final offsets
  double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

  // Reset all trackers if they exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();

  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();
    chassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);
    chassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = chassis.odom_theta_get();
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

    // Turn to target at half power
    chassis.pid_turn_set(target, 63, ez::raw);
    chassis.pid_wait();
    pros::delay(250);

    // Calculate delta in angle
    double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));

    // Calculate delta in sensor values that exist
    double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
    double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
    double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
    double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;

    // Calculate the radius that the robot traveled
    l_offset += l_delta / t_delta;
    r_offset += r_delta / t_delta;
    b_offset += b_delta / t_delta;
    f_offset += f_delta / t_delta;
  }

  // Average all offsets
  l_offset /= iterations;
  r_offset /= iterations;
  b_offset /= iterations;
  f_offset /= iterations;

  // Set new offsets to trackers that exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
}

// // . . .
// // Make your own autonomous functions here!
// // . . .