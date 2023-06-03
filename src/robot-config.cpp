#include "vex.h"
#include "Timer.h"
#include <thread>

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor leftDrive = motor(PORT1, ratio18_1, false);
motor rightDrive = motor(PORT2, ratio18_1, true);
gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.D);
smartdrive Drivetrain = smartdrive(leftDrive, rightDrive,
                                   TurnGyroSmart, 319.19, 320, 130, mm, 1);

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */


static bool stopVexProgram = false;
long long currentTime = 0;
Timer checkErrors{"AAA"};
Timer programLoop{"Time to complete: "};
double totDegrees = 0;

void startSecondThread() {
  while(!stopVexProgram) {
    long long time = checkErrors.getTime() - currentTime;
    if(time >= 1000) {
      Brain.Screen.printAt(10, 20, "Main thread is stalling!");
    } else {
      Brain.Screen.printAt(10, 20, "Main thread is working! ");
    }
    this_thread::sleep_for(20);
  }
}

void multiDrive(double totDegrees) {
}

void vexcodeInit(void) {
  checkErrors.start();
  thread errorChecker{startSecondThread};
  programLoop.start();
  int tick = 0;
  while(!stopVexProgram) {
    if(tick >= 4) {
      stopVexProgram = true;
      break;
    }
    // Loop inside here
    // 30 * 3.14 * 1/4 = each wheel
    // 180 degrees = 10.5
    double randomAdjuster = 0;

    double distanceBetweenWheels = 29.5; // Centimeters
    double wheelDiameter = 10.5; // Centimeters
    double distance = distanceBetweenWheels * M_PI_2;
    double rotations = distance / wheelDiameter;
    totDegrees = (rotations * 180. / M_PI) + randomAdjuster; // The 5 is to adjust for some random offset

    Drivetrain.setDriveVelocity(75, percent);
    Drivetrain.driveFor(6*11, inches);
    Drivetrain.setDriveVelocity(20, percent);
    thread dd{[](){leftDrive.spinFor(-totDegrees, degrees);}};
    rightDrive.spinFor(totDegrees, degrees);
    currentTime = checkErrors.getTime();
    tick++;
   //rightDrive.spinFor(1.34159203, rev);
  }
  double totalTime = (((double) programLoop.getTime()) / 1000.);
  Brain.Screen.printAt(10, 40, "Total Time: %f", totalTime);
}