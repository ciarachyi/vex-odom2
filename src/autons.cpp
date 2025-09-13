#include "main.h"
#include "subsystems.hpp"

extern pros::adi::DigitalOut middle;
extern pros::adi::DigitalOut matchload;
/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 127;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;
// Was slew the issue??
///
// Constants
///
// 162
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 155.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 55);      // Angular control for odom motions
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
  chassis.odom_boomerang_dlead_set(0.4);       // This handles how aggressive the end of boomerang motions are **TRY THIS

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there **EXPERIMENT WITH THIS MAYBE
}

// void firstautoyay() {
//   default_constants();
//   chassis.odom_xyt_set(-52_in, -13_in, 146_deg);
//   intake1.move(127);
//   chassis.pid_odom_set({
//                           {{-38_in, -28_in, 146_deg}, fwd, 50}, //set up in front of blocks
//                            {{-15_in, -14_in, 50_deg}, fwd, DRIVE_SPEED},  // Middle goal
//                            // {{6.63_in, 18.42_in, 44.7_deg}, fwd, DRIVE_SPEED},
//                           //  {{-12_in, -15_in}, fwd, DRIVE_SPEED}  // THIS IS THE MIDDLE GOAL
//                        },
//                        true);
//   chassis.pid_wait();
//   chassis.pid_turn_set(50_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();
//   chassis.pid_drive_set(1, DRIVE_SPEED, true);
//   chassis.pid_wait_quick_chain();

//   pros::delay(600);
//   chassis.pid_wait_quick_chain();

//   intake.move(-115);
//   pros::delay(1200);
//   chassis.pid_drive_set(-6, DRIVE_SPEED, true);
//   chassis.pid_wait_quick_chain();
//   intake1.move(127);

//   chassis.pid_odom_set({{{-12_in, 18_in}, fwd, DRIVE_SPEED}},  // SECOND FUCKING BLOCKS
//                        true);

//   chassis.pid_wait_quick_chain();
//   pros::delay(700);
//   chassis.pid_odom_set({{{-3_in, 8_in, 340_deg}, rev, 65}},  // THE TOP MIDDLE GOAL
//                        true);

//   chassis.pid_wait_quick_chain();
//   middle.set_value(1);
//   intake.move(127);

// }

void firstautoyay() {
  default_constants();
  chassis.odom_xyt_set(8.2_in, -2_in, 40_deg);
  intake1.move(127);
  chassis.pid_odom_set({
                           {{20_in, 14_in, 40_deg}, fwd, DRIVE_SPEED},  // set up in front of blocks

                           {{16_in, 24_in, -65_deg}, fwd, 50},

                           // TURN TO NEGATIVE 40
                           {{9_in, 30_in, -55_deg}, fwd, DRIVE_SPEED},  // Middle goal
                                                                        // DRIVE FORWARD 11

                           // {{6.63_in, 18.42_in, 44.7_deg}, fwd, DRIVE_SPEED},
                           //  {{-12_in, -15_in}, fwd, DRIVE_SPEED}  // THIS IS THE MIDDLE GOAL
                       },
                       true);

  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-50_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(9, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  pros::delay(500);
  chassis.pid_wait_quick_chain();

  intake.move(-127);
  pros::delay(200);
  intake.move(-95);
  pros::delay(1700);
  chassis.pid_drive_set(-4, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set({-38, 40}, fwd, 100, true);
  intake1.move(127);
  chassis.pid_odom_set({{{-38_in, 40_in, -45_deg}, fwd, 85}}, true);  // SECOND BLOCKS
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-2, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-130_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-21_in, 56_in, -130_deg}, rev, DRIVE_SPEED}}, true);  // TOP GOAL
  middle.set_value(1);
  chassis.pid_wait_quick_chain();
  intake1.move(127);

  pros::delay(1300);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{-48_in, 18_in, 190_deg}, fwd, DRIVE_SPEED}}, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(6, DRIVE_SPEED, true);

  //  {{-48_in, 8_in, 190_deg}, fwd, DRIVE_SPEED}}, true);

  matchload.set_value(1);

  // chassis.pid_wait_quick_chain();
  // intake1.move(127);

  // chassis.pid_odom_set({{{36_in, 18_in}, fwd, DRIVE_SPEED}},  // SECOND FUCKING BLOCKS
  //                      true);

  // chassis.pid_wait_quick_chain();
  // pros::delay(700);h
  // chassis.pid_odom_set({{{45_in, 8_in, 250_deg}, rev, 65}},  // THE TOP MIDDLE GOAL
  //                      true);

  // chassis.pid_wait_quick_chain();
  // middle.set_value(1);
  // intake.move(127);
}

void topAndLeft() {
  default_constants();
  chassis.odom_xyt_set(-14_in, -4_in, -25_deg);

  intake1.move(127);
  chassis.pid_odom_set({
                           {{-29_in, 20_in, -25_deg}, fwd, 45},  // set up in front of blocks

                       },
                       true);
  chassis.pid_wait_quick_chain();
  pros::delay(200);
  chassis.pid_drive_set(-2, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  intake.move(0);

  chassis.pid_turn_set(-130_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-11_in, 39_in, -130_deg}, rev, 40}}, true);  // middle goal
  chassis.pid_wait();

  // chassis.pid_drive_set(-2, DRIVE_SPEED, true);
  // chassis.pid_wait();

  middle.set_value(1);
  chassis.pid_wait_quick_chain();
  intake1.move(100);
  pros::delay(10);
  intake1.move(127);
  pros::delay(1500);
  chassis.pid_wait();

  
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-44_in, -2_in, 178_deg}, fwd, 90}}, true);
  chassis.pid_wait_quick_chain();

  matchload.set_value(1);
  middle.set_value(0);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-180_deg, TURN_SPEED);
  pros::delay(400);
  chassis.pid_drive_set(8, DRIVE_SPEED, true);
  // chassis.pid_odom_set({{{-43_in, -12_in, 182_deg}, fwd, 100}}, true);
  chassis.pid_wait();
  pros::delay(400); 
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-44_in, 14_in, 182_deg}, rev, 90}}, true);
  chassis.pid_wait();
  intake.move(127);
}

void bottomAndRight() {
  default_constants();
  chassis.odom_xyt_set(8.2_in, -2_in, 40_deg);
  intake1.move(127);
  chassis.pid_odom_set({
                           {{20_in, 14_in, 40_deg}, fwd, 90},  // set up in front of blocks

                           {{16_in, 24_in, -65_deg}, fwd, 50},

                           // TURN TO NEGATIVE 40
                           {{9_in, 30_in, -55_deg}, fwd, 60},  // Middle goal
                                                               // DRIVE FORWARD 11

                           // {{6.63_in, 18.42_in, 44.7_deg}, fwd, DRIVE_SPEED},
                           //  {{-12_in, -15_in}, fwd, DRIVE_SPEED}  // THIS IS THE MIDDLE GOAL
                       },
                       true);

  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-50_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(9, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  pros::delay(500);
  chassis.pid_wait_quick_chain();

  intake.move(-127);
  pros::delay(200);
  intake.move(-95);
  pros::delay(1700);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{39_in, 0_in, -55_deg}, rev, DRIVE_SPEED}}, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  matchload.set_value(1);
  intake1.move(127);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{48_in, -24_in, 180_deg}, fwd, 50}}, true);
  chassis.pid_wait_quick_chain();
  pros::delay(1500);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-10, DRIVE_SPEED, true);
  matchload.set_value(0);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{48_in, 20_in, 0_deg}, rev, 85}}, true);  // Long Goal
  chassis.pid_wait_quick_chain();
  intake.move(127);
}

void longGoal() {
}

void middleGoals() {
}

void odometry_accuracy_test() {
  // Reset odometry to the starting position
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);

  // Test driving forward and backward
  chassis.pid_odom_set({{{0_in, 48_in}, fwd, DRIVE_SPEED}}, true);  // Drive forward 24 inches
  chassis.pid_wait();
  chassis.pid_odom_set({{{0_in, 0_in}, rev, DRIVE_SPEED}}, true);  // Drive backward to start
  chassis.pid_wait();

  // Test turning in place
  chassis.pid_turn_set(90_deg, TURN_SPEED);  // Turn 90 degrees clockwise
  chassis.pid_wait();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);  // Turn 90 degrees counterclockwise
  chassis.pid_wait();

  // Test driving in a square pattern
  chassis.pid_odom_set({{{24_in, 0_in}, fwd, DRIVE_SPEED}}, true);  // Move right 24 inches
  chassis.pid_wait();
  chassis.pid_turn_set(0_deg, TURN_SPEED);  // Turn 90 degrees clockwise
  chassis.pid_wait();
  chassis.pid_odom_set({{{24_in, 24_in}, fwd, DRIVE_SPEED}}, true);  // Move forward 24 inches
  chassis.pid_wait();
  chassis.pid_turn_set(90_deg, TURN_SPEED);  // Turn 90 degrees clockwise
  chassis.pid_wait();
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED}}, true);  // Move left 24 inches
  chassis.pid_wait();
  chassis.pid_turn_set(180_deg, TURN_SPEED);  // Turn 90 degrees clockwise
  chassis.pid_wait();
  chassis.pid_odom_set({{{0_in, 0_in}, fwd, DRIVE_SPEED}}, true);  // Move backward to start
  chassis.pid_wait();

  // Final turn to face the original direction
  chassis.pid_turn_set(90_deg, TURN_SPEED);  // Turn 90 degrees clockwise to face original direction
  chassis.pid_wait();
}

void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at
  default_constants();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);

  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED}}, true);
  chassis.pid_odom_set({{{0_in, 48_in}, fwd, DRIVE_SPEED}}, true);

  chassis.pid_turn_set({-2000_in, 0_in}, fwd, 90);
  pros::delay(1000);

  chassis.pid_odom_set({{{24_in, 48_in}, fwd, DRIVE_SPEED}}, true);
  chassis.pid_odom_set({{{48_in, 48_in}, fwd, DRIVE_SPEED}}, true);

  chassis.pid_turn_set({2000_in, 0_in}, fwd, 90);
  pros::delay(1000);

  chassis.pid_turn_set({0_in, -2000_in}, fwd, 90);
  pros::delay(1000);

  chassis.pid_odom_set({{{48_in, 24_in}, fwd, DRIVE_SPEED}}, true);
  chassis.pid_odom_set({{{48_in, 0_in}, fwd, DRIVE_SPEED}}, true);

  chassis.pid_turn_set({0_in, 0_in}, fwd, 90);
  pros::delay(1000);
}

void odom_boomerang_injected_pure_pursuit_example() {
  chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

void odom_drive_example() {
  // This works the same as pid_drive_set, but it uses odom instead!
  // You can replace pid_drive_set with pid_odom_set and your robot will
  // have better error correction.

  // default_constants();

  chassis.odom_xyt_set(0_in, 0_in, 0_deg);

  chassis.pid_odom_set({{{0_in, 96_in, 0_deg}, fwd, DRIVE_SPEED}}, true);
  chassis.pid_wait();

  chassis.pid_odom_set({{{0_in, 48_in, 0_deg}, rev, DRIVE_SPEED}}, true);
  chassis.pid_wait();

  chassis.pid_odom_set({{{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED}}, true);
  chassis.pid_wait();
}

//***faulty rotation sensor???
void odom_boomerang_example() {
  // Drive forward to (0, 36) forward, end at 45 degrees

  chassis.pid_odom_set({
                           {0_in, 30_in},
                           fwd,
                           110,
                       },
                       true);
  chassis.pid_wait();
  chassis.pid_turn_set(135_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_odom_set({{30_in, 0_in}, fwd, 110}, true);
  chassis.pid_wait();

  // Drive back to (0, 0) backward, end at 0 degrees
  // chassis.pid_odom_set({{0, 0, 0}, rev, 110});
  // chassis.pid_wait();

  // pros::delay(1000);

  // chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
  //                      true);
  // chassis.pid_wait();
}

void testStuff() {
  chassis.pid_turn_set({10, 26}, fwd, 20);
  chassis.pid_wait();
  chassis.pid_odom_set({{10_in, 26_in}, fwd, 20});
  chassis.pid_wait();
}

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches
  chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(135_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Turn Example
///

void angles() {
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // chassis.pid_turn_set(180_deg, TURN_SPEED);
  // chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Odom Drive PID
///

///
// Odom Pure Pursuit
///
void odom_pure_pursuit_example() {
  // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
  chassis.pid_odom_set({{{6_in, 10_in}, fwd, 80},
                        {{0_in, 40_in}, fwd, 80},
                        {{0_in, 50_in}, fwd, 80}},
                       true);
  chassis.pid_wait();

  pros::delay(1500);

  // Drive to 0, 0 backwards
  chassis.pid_odom_set({{0_in, 0_in}, rev, 80},
                       true);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit Wait Until
///
void odom_pure_pursuit_wait_until_example() {
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
  // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
  chassis.pid_wait();
  // Intake.move(0);  // Turn the intake off
}

///
// Odom Boomerang
///

///
// Odom Boomerang Injected Pure Pursuit
///

///
// Calculate the offsets of your tracking wheels
///
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
    chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
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

// . . .
// Make your own autonomous functions here!
// . . .