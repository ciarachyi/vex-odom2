#include "main.h"

#include "EZ-Template/tracking_wheel.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {-10, -6, -7},  // Left Chassis Ports (negative port will reverse it!)
    {20, 9, 8},     // Right Chassis Ports (negative port will reverse it!)

    17,    // IMU Port
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    450);  // WheelRPM = cartridge * (motor gear / wheel gear)

// Uncomment the trackers you're using here!
// - `8` and `9` are smart ports (making these negative will reverse the sensor)
//  - you should get positive values on the encoders going FORWARD and RIGHT
// - `2.75` is the wheel diameter
// - `4.0` is the distance from the center of the wheel to the center of the robot
ez::tracking_wheel horiz_tracker(18, 2, 4.60, 1);  // This tracking wheel is perpendicular to the drive wheels
ez::tracking_wheel vert_tracker(-11, 2, 0.16, 1);  // This tracking wheel is parallel to the drive wheels

ez::Piston tongue('D');
ez::Piston park('A');
ez::Piston descore('B');
ez::Piston pod('E');
ez::Piston pistintake('C');

pros::Distance frontDistance(15);
pros::Distance leftDistance(1);

// BE CAREFUL OF THIS

// pros::Motor intake1(10, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees);
// pros::Motor intake2(10, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();

  // ez::tracking_wheel horiz_tracker(12, 2, 0, 1);
  // ez::tracking_wheel vert_tracker(13, 2, 0, 1);

  // front left
  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Look at your horizontal tracking wheel and decide if it's in front of the midline of your robot or behind it
  //  - change `back` to `front` if the tracking wheel is in front of the midline
  //  - ignore this if you aren't using a horizontal tracker

  chassis.odom_tracker_front_set(&horiz_tracker);

  // Look at your vertical tracking wheel and decide if it's to the left or right of the center of the robot
  //  - change `left` to `right` if the tracking wheel is to the right of the centerline
  //  - ignore this if you aren't using a vertical tracker
  chassis.odom_tracker_right_set(&vert_tracker);

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true);   // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0.0);   // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0.0, 0.0);  // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // Set the drive to your own constants from autons.cpp!
  default_constants();

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  // SWITCH THE MIDDLE GOALLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
  ez::as::auton_selector.autons_add({

      {"SKILLS r5 manifesting 100 pts", skillsWR},
      {"reverse odom test", revOdom},
      
      
      {"gets long goal control, left side, 7 blocks", LeftControl},
      {"RIGHT 6+3, 9 ball 2 control right", RightTroy},
      {"gets long goal control, right side, 7 blocks", control},
      {"like a weird s", odom_pure_pursuit_example},
      {"Measure Offsets\n\nThis will turn the robot a bunch of times and calculate your offsets for your tracking wheels.", measure_offsets},
      
      {"solo sig wp", SoloSigWP},
      
      {"drive forward 2 inches", straight},
      
      {"6+3, 9 ball 2 control left", troy},
      
      
      
      
      
      
      {"arc test", odom_boomerang_injected_pure_pursuit_example},
      {"Simple Odom\n\nThis is the same as the drive example, but it uses odom instead!", odom_drive_example},
     
      
      
      
     
      
      
      {"Driving", square},
      
      {"Driving", driving},
     
     
      {"gets long goal control, right side, 7 blocks", control},
      

      
      
      

      {"testing the macro", whoo},

      

      {"testing the distance reset", practiceDistance},

      {"basic test", what},

      {"yay", driveBack},

      {"rushes right side blocks", rushRightYay},

     

      {"go in a square", drive_and_turn},

      {"skills", skills},
      {"solo wp for regional events", soloR},

      {"rush for the left side", rushLeft},

      {"scores 9 in the left long goal", leftNineBall},

      // {"rush left blocks", rush},

      

      // {"top middle goal and left long goal", topAndLeft},
      // {"clear stuff", skills},

      // {"bottom middle goal and right long goal", bottomAndRight},

      // {"blue solo", blueSolo},
      // {"solo wp", firstautoyay},
      // {"ride side long goal", rightSide},

      // {"Simple Odom\n\nThis is the same as the drive example, but it uses odom instead!", odom_drive_example},

      // {"pid solo", adjustedSolo},

      // {"use all blocks for long goal", longGoal},
      // {"score in both middle goals", middleGoals},

      // {"woohoo.", odometry_accuracy_test},
      // {"Turn\n\nTurn 3 times.", turn_example},

      // {"Pure Pursuit\n\nGo to (0, 30) and pass through (6, 10) on the way.  Come back to (0, 0)", odom_pure_pursuit_example},

      //

      // {"Boomerang\n\nGo to (0, 24, 45) then come back to (0, 0, 0)", odom_boomerang_example},
      // {"Turns based on angle degree measurements", angles},

      // {"Drive\n\nDrive forward and come back", drive_example},
      // {"odom test drive", testStuff},

      // {"Drive and Turn\n\nDrive forward, turn, come back", drive_and_turn},
      // {"Drive and Turn\n\nSlow down during drive", wait_until_change_speed},
      // {"Swing Turn\n\nSwing in an 'S' curve", swing_example},
      // {"Motion Chaining\n\nDrive forward, turn, and come back, but blend everything together :D", motion_chaining},
      // {"Combine all 3 movements", combining_movements},
      // {"Interference\n\nAfter driving forward, robot performs differently if interfered or not", interfered_example},

      // {"Pure Pursuit Wait Until\n\nGo to (24, 24) but start running an intake once the robot passes (12, 24)", odom_pure_pursuit_wait_until_example},

      // {"Boomerang Pure Pursuit\n\nGo to (0, 24, 45) on the way to (24, 24) then come back to (0, 0, 0)", odom_boomerang_injected_pure_pursuit_example},

  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(chassis.drive_imu_calibrated() ? "." : "---");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */

void disabled() {

  // pros::delay(50);
  // park.set(true);

  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset();   // Resets PID targets to 0
  chassis.drive_imu_reset();     // Reset gyro position to 0
  chassis.drive_sensor_reset();  // Reset drive sensors to 0

  chassis.odom_xyt_set(0_in, 0_in, 0_deg);  // Set the current position, you can start at a specific position with this

  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency

  /*
  Odometry and Pure Pursuit are not magic

  It is possible to get perfectly consistent results without tracking wheels,
  but it is also possible to have extremely inconsistent results without tracking wheels.
  When you don't use tracking wheels, you need to:
   - avoid wheel slip
   - avoid wheelies
   - avoid throwing momentum around (super harsh turns, like in the example below)
  You can do cool curved motions, but you have to give your robot the best chance
  to be consistent
  */

  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
  // printf("Gyro: %f \n", chassis.drive_imu_get());
}

/**
 * Simplifies printing tracker values to the brain screen
 */
void screen_print_tracker(ez::tracking_wheel *tracker, std::string name, int line) {
  std::string tracker_value = "", tracker_width = "";
  // Check if the tracker exists
  if (tracker != nullptr) {
    tracker_value = name + " tracker: " + util::to_string_with_precision(tracker->get());             // Make text for the tracker value
    tracker_width = "  width: " + util::to_string_with_precision(tracker->distance_to_center_get());  // Make text for the distance to center
  }
  ez::screen_print(tracker_value + tracker_width, line);  // Print final tracker text
}

/**
 * Ez screen task
 * Adding new pages here will let you view them during user control or autonomous
 * and will help you debug problems you're having
 */
void ez_screen_task() {
  pros::Motor motor(9);
  while (true) {
    // string odom_enabled = chassis.odom_enabled() ? "true" : "false";
    // string tuner_enabled = chassis.pid_tuner_enabled() ? "true" : "false";
    // string competition_connected = pros::competition::is_connected() ? "true" : "false";
    // ez::screen_print("Hi2 is odom enabled:" + odom_enabled + ", tuner enabled:" + tuner_enabled + ", competition connected:" + competition_connected);

    // Only run this when not connected to a competition switch

    // TODO: Comment below back in -- disabled for now to debug distance sensor during auton
    // if (!pros::competition::is_connected())

    // Blank page for odom debugging
    if (chassis.odom_enabled() && !chassis.pid_tuner_enabled()) {
      // If we're on the first blank page...
      if (ez::as::page_blank_is_on(0)) {
        // Display X, Y, and Theta
        ez::screen_print("x: " + util::to_string_with_precision(chassis.odom_x_get()) +
                             "\ny: " + util::to_string_with_precision(chassis.odom_y_get()) +
                             "\na: " + util::to_string_with_precision(chassis.odom_theta_get()) +
                             "\ntemp: " + util::to_string_with_precision(motor.get_temperature()),
                         1);  // Don't override the top Page line

        // Display all trackers that are being used
        screen_print_tracker(chassis.odom_tracker_left, "l", 4);
        screen_print_tracker(chassis.odom_tracker_right, "r", 5);
        screen_print_tracker(chassis.odom_tracker_back, "b", 6);
        screen_print_tracker(chassis.odom_tracker_front, "f", 7);
      }
    }
    // TODO: Comment below back in per comment above associated with if
    // }

    // Remove all blank pages when connected to a comp switch
    else {
      if (ez::as::page_blank_amount() > 0)
        ez::as::page_blank_remove_all();
    }

    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task ezScreenTask(ez_screen_task);

// void number_test() {
//    while (true) {
//     // Only run this when not connected to a competition switch
//     if (!pros::competition::is_connected()) {
//       // Blank page for odom debugging
//       if (chassis.odom_enabled() && !chassis.pid_tuner_enabled()) {
//         // If we're on the first blank page...
//         if (ez::as::page_blank_is_on(0)) {
//           // Display X, Y, and Theta
//           ez::screen_print("2 ",
//                            1);  // Don't override the top Page line
//         }
//       }
//     }

//     // Remove all blank pages when connected to a comp switch
//     else {
//       if (ez::as::page_blank_amount() > 0)
//         ez::as::page_blank_remove_all();
//     }

//     pros::delay(ez::util::DELAY_TIME);
//   }
// }
// pros::Task numberTest(ez_screen_task);

// void motor_temp() {
//   while (true) {
//     // Only run this when not connected to a competition switch
//     if (!pros::competition::is_connected()) {
//       // Blank page for odom debugging
//         // If we're on the first blank page...
//         if (ez::as::page_blank_is_on(3)) {
//           // Display X, Y, and Theta
//           ez::screen_print("Left 1: " + util::to_string_with_precision(double pros::Motor::get_temperature ( )) +
//                                  "\n Left 2: " + util::to_string_with_precision(chassis.odom_y_get()) +
//                                  "\n Left 3: " + util::to_string_with_precision(chassis.odom_y_get()) +
//                                  "\n Right 1: " + util::to_string_with_precision(chassis.odom_y_get()) +
//                                  "\n Right 2: " + util::to_string_with_precision(chassis.odom_y_get()) +
//                                  "\n Right 3: " + util::to_string_with_precision(chassis.odom_theta_get()),
//                            1);  // Don't override the top Page line

//           // Display all trackers that are being used

//         }
//       }

//     // Remove all blank pages when connected to a comp switch
//     else {
//       if (ez::as::page_blank_amount() > 0)
//         ez::as::page_blank_remove_all();
//     }

//     pros::delay(ez::util::DELAY_TIME);
//   }
// }

// pros::Task motorTemp(motor_temp);
/**
 * Gives you some extras to run in your opcontrol:
 * - run your autonomous routine in opcontrol by pressing DOWN and B
 *   - to prevent this from accidentally happening at a competition, this
 *     is only enabled when you're not connected to competition control.
 * - gives you a GUI to change your PID values live by pressing X
 */
void ez_template_extras() {
  // Only run this when not connected to a competition switch
  if (!pros::competition::is_connected()) {
    // PID Tuner
    // - after you find values that you're happy with, you'll have to set them in auton.cpp

    // Enable / Disable PID Tuner
    //  When enabled:
    //  * use A and Y to increment / decrement the constants
    //  * use the arrow keys to navigate the constants
    if (master.get_digital_new_press(DIGITAL_X))
      chassis.pid_tuner_toggle();

    // Trigger the selected autonomous routine
    if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
      pros::motor_brake_mode_e_t preference = chassis.drive_brake_get();
      autonomous();
      chassis.drive_brake_set(preference);
    }

    // Allow PID Tuner to iterate
    chassis.pid_tuner_iterate();
  }

  // Disable PID Tuner when connected to a comp switch
  else {
    if (chassis.pid_tuner_enabled())
      chassis.pid_tuner_disable();
  }
}

// if something goes wrong check this first it might be weird                                   I JUST COMMENTED THIS OUT BE CAREFUL
// void controllerButtons() {
//   while (true) {
//     if (master.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2)) {
//       intake.move(127);
//       // intake2.move(127);
//     }

//     else if (master.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1)) {
//       intake.move(-127);
//       // intake2.move(-127);

//     }

//     else {
//       intake.brake();
//       // intake2.brake();
//     }
//   }
// }

// bool lift_up = false;

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);
  intake2.set_brake_mode(MOTOR_BRAKE_COAST);

  pod.set(true);
  // pistintake.set(true);

  descore.set(false);
  bool descoreUp = false;

  while (true) {
    // Gives you some extras to make EZ-Template ezier
    ez_template_extras();

    // chassis.opcontrol_tank();  // Tank control
    chassis.opcontrol_arcade_standard(ez::SPLIT);  // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade

    // . . .
    // Put more user control code here!

    // . . .

    //  printf("Distance: %d mm\n", rightDistance.get());
    //             pros::delay(20);

    if (master.get_digital(DIGITAL_R2)) {  // outtake everything
      intake1.move(-95);
      intake3.move(-127);
      intake2.move(-20);
    } else if (master.get_digital(DIGITAL_R1)) {  // intake
      intake1.move(127);
      intake3.move(127);
      intake2.move(127);
    } else if (master.get_digital(DIGITAL_L1)) {  // middle
      // intake1.move(127);
      // intake2.move(-127);
      // intake3.move(127);
      intake1.move(65);
      intake2.move(-15);
      intake3.move(45);
    } else if (master.get_digital(DIGITAL_B)) {
      // intake.move(-70);
      intake1.move(-70);
      intake3.move(-70);
      intake2.move(-20);
      // } else if (master.get_digital_new_press(DIGITAL_L2)) {
      //     if (descoreUp == true) {
      //     descore.set(false);
      //     descoreUp = false;
      //   } else {
      //     intake.move(-127);  // Move the intake
      //     pros::delay(160);
      //     descore.set(true);
      //     intake.move(0);
      //     descoreUp = true;
      //   }
    } else {
      intake.move(0);
    }

    // if (master.get_digital_new_press(DIGITAL_L2)) {

    //   intake.move(-30);   // Move the intake
    //   pros::delay(20);

    //   descore.set(true);  // Actuate the piston

    //   intake.move(0);
    // }

    park.button_toggle(master.get_digital(DIGITAL_Y));
    descore.button_toggle(master.get_digital(DIGITAL_L2));

    tongue.button_toggle(master.get_digital(DIGITAL_RIGHT));
    pod.button_toggle(master.get_digital(DIGITAL_A));
    pistintake.button_toggle(master.get_digital(DIGITAL_DOWN));

    // if (master.get_digital_new_press(
    //         pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L1)) {
    //   lift_up = !lift_up;
    // }

    // lift.set_value(lift_up);

    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
