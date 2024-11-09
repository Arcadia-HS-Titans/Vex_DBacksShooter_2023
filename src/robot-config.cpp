#include "vex.h"
#include "Timer.h"
#include <thread>

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor leftDrive = motor(PORT9, ratio18_1, false);
motor rightDrive = motor(PORT10, ratio18_1, true);
gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.D);
smartdrive Drivetrain = smartdrive(leftDrive, rightDrive,
                                   TurnGyroSmart, 319.19, 320, 130, mm, 1);
controller Controller = controller();
motor Intake = motor(PORT5, ratio18_1, false);
motor Intake2 = motor(PORT6, ratio18_1, false)

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */


static bool stopVexProgram = false; // Below below
long long currentTime = 0; // And below
Timer checkErrors{"AAA"}; // Outside since vex's thread implementation is a little less free than C++'s
double totDegrees = 0; // Outside for the same reason as above


void startSecondThread() {
  while(true) {
    long long time = checkErrors.getTime() - currentTime;
    if(time >= 5000) {
      Brain.Screen.printAt(10, 20, "Main thread is stalling!");
    } else {
      Brain.Screen.printAt(10, 20, "Main thread is working! ");
    }
    this_thread::sleep_for(20);
  }
}


void vexcodeInit(void) {
  checkErrors.start();
  thread errorChecker{startSecondThread};
  Timer programLoop{"Total runtime"};
  programLoop.start();
  int tick = 0;
  //InterialSensor.resetHeading();
  while(true) {
    Intake.setVelocity(abs(Controller.Axis2.value() * 100), percent);
    if(Controller.Axis2.value() < 0) {
      Intake.setReversed(true);
    } else {
      Intake.setReversed(false);
    }
    Intake.spin(forward);
  }
  double totalTime = (((double) programLoop.getTime()) / 1000.);
  Brain.Screen.printAt(10, 40, "Total time to run program: %f", totalTime);
}