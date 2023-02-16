/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\amadden                                          */
/*    Created:      Tue Nov 08 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// left_front           motor         11              
// right_front          motor         2               
// left_back            motor         18              
// right_back           motor         20              
// roller               motor         1               
// cata                 motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

const int SCALE = 120;
void set_tank(int left, int right) {
  left_front.spin(fwd, left*SCALE, voltageUnits::mV);
  left_back.spin(fwd, left*SCALE, voltageUnits::mV);
  right_front.spin(fwd, right*SCALE, voltageUnits::mV);
  right_back.spin(fwd, right*SCALE, voltageUnits::mV);
}
//This sets the tank to a spin determined by the amount the 
//joystick is moved multipled by a predetermined scalar, the SCALE

void set_roller(int input) {
  roller.spin(forward, input*SCALE, voltageUnits::mV);
}

void cata_spin(int input) {
  cata.spin(forward, input*SCALE, voltageUnits::mV);
}
double clipnum(double input, double max, double min) {
  if (input > max) {
    return max;
  }
  else if (input < min) {
    return min;
  }
  return input;
}

void move(double target, int speed) {
  double kP = 0.5; // kP (scaling number)
  int x = 0; // Timer for exit condition
  while (true) {
    double error = target - left_front.rotation(deg); // error = (target - current)
    int output = clipnum(error * kP, speed, -speed);
    set_tank(output, output); // Set motors to (error * kP) and clip it to speed

    // If the velocity of the left and right motors are 0...
    if (left_back.velocity(pct) == 0 && right_back.velocity(pct) == 0) {
      x+=10; // Increase x by 10
      if (x >= 50) { // If x is 50 (meaning the motors were at 0 velocity for 50ms)...
        break; // Break the while loop
      }
    } 
    // If the velocity of the left and right motors are not 0...
    else {
      x = 0; // Set the timer to 0
    }

    wait(10, msec);
  }
  set_tank(0, 0); // Make sure motors are off before leaving this function
}
//This sets the Rollar to spin the amount of an input

int AutonNumber = 1; // Current Autonomous

void pre_auton() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // . . .
  wait(2, sec); // Give the IMU time to calibrate
  Controller1.rumble(".");
  // . . .

  // Variables 
  int x1 = 5;
  int y1 = 50;
  int x2 = 50;
  int y2 = 175;
  int spacing = 60;
  int rect_amount = 8;
  color selected = red;
  color unselected = blue;

  // Print 8 rectangles 
  for (int i = 0; i < rect_amount; i++) {
    color current_color;
    // Check if i is AutonNumber to change current_color
    if (i+1 == AutonNumber) {
      current_color = selected;
    } else {
      current_color = unselected;
    }
    Brain.Screen.setPenColor(current_color);
    Brain.Screen.drawRectangle(x1+(spacing*i), y1, x2, y2, current_color);
  }

  // Set font to monoM
  Brain.Screen.setFont(monoM); 

  while (true) {

    // Selected position
    int x = Brain.Screen.xPosition(); // X position of finger
    int y = Brain.Screen.yPosition(); // Y position of finger

    // Check if finger is within vertical selection of the boxes
    if (y1 < y && y < y1+y2) {
      for (int i = 0; i < rect_amount; i++) {
        // Check which x value the finger is within
        if (x1+(spacing*i) < x && x < (spacing*(i+1))-x1) {
          // Change color of previously selected box to unselected
          Brain.Screen.setPenColor(unselected);
          Brain.Screen.drawRectangle(x1+(spacing*(AutonNumber-1)), y1, x2, y2, unselected);
          AutonNumber = i+1; // Update AutonNumber
          // Change color of new box to selected
          Brain.Screen.setPenColor(selected);
          Brain.Screen.drawRectangle(x1+(spacing*(AutonNumber-1)), y1, x2, y2, selected);
        }
      }
    }

    // Print AutonNumber to brain
    Brain.Screen.setPenColor(selected);
    Brain.Screen.printAt(5, 30, "Current Auto: %d", AutonNumber); // %d is a formatting character that gets replaced with AutonNumber
    wait(20, msec);
    Brain.Screen.clearLine(1);
  }
}
//Auton code
void autonomous(void) {
  left_front.setPosition(0,deg);

  if (AutonNumber == 1) {
    set_tank(20,30);
    wait(500, msec);
    set_tank(0,0);
    set_roller(125);
    wait(75,msec);
    set_roller(0);
  }
  else if (AutonNumber == 2) {
    set_tank(100,100);
    wait(250,msec);
    set_tank(0,100);
    wait(400,msec);
    set_tank(20,20);
    wait(75,msec);
    set_tank(0,0);
    set_roller(125);
    wait(75,msec);
    set_roller(0);
  }
  else if (AutonNumber == 3) {
    move(60,100);
    set_roller(125);
    wait(75,msec);
    set_roller(0);

  }
  else if (AutonNumber == 4) {
    // Call Auton 
  }
  else if (AutonNumber == 5) {
    // Call Auton 
  }
  else if (AutonNumber == 6) {
    // Call Auton 
  }
  else if (AutonNumber == 7) {
    // Call Auton 
  }
  else if (AutonNumber == 8) {
    // Call Auton 
  }
}

void usercontrol(void) {
  while(true) {
    int left_joy = Controller1.Axis3.position();
    int right_joy = Controller1.Axis2.position();
    //sets variables left_joy and right_joy to joystick position
    if (abs(left_joy) < 5) {
      left_joy = 0;
    }
    //top and bottom both allow the joysticks to return to 0 quicker
    if (abs(right_joy) < 5) {
      right_joy=0;
    }

    set_tank(left_joy,right_joy);
    //sets the robot spin to the joystick values
    

    if(Controller1.ButtonL2.pressing()) {
      set_roller(100);
    }
    else {
      set_roller(0);
    }
    if(Controller1.ButtonL1.pressing()) {
      cata_spin(25);
    }
    else if(Controller1.ButtonR1.pressing()) {
      cata_spin(-25);
    }
    else {
      cata_spin(1);
    }
    //if button is pressed rollars moves forward, else its off
    wait(20,msec);
    //sleeps Zzzzzzz.... good night robot!
}
}
int main() {
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  
  pre_auton();

 
  while (true) {
    wait(100, msec);
  }
}
