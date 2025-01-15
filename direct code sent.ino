#include <AccelStepper.h>

// Define stepper motors
AccelStepper motorX1(1, 3, 6); // Step, Dir for X1
AccelStepper motorX2(1, 8, 9); // Step, Dir for X2 (synchronous with X1)
AccelStepper motorY(1, 10, 11); // Step, Dir for Y
AccelStepper motorZ(1, 12, 13); // Step, Dir for Z

// Steps per mm for motion (adjust as needed)
const float stepsPerMM = 50;

void setup() {
  Serial.begin(9600);

  // Set maximum speed and acceleration for all motors
  motorX1.setMaxSpeed(5000);  // Maximum speed (steps per second)
  motorX1.setAcceleration(1000); // Smooth acceleration
  motorX2.setMaxSpeed(5000);
  motorX2.setAcceleration(1000);
  motorY.setMaxSpeed(3000);
  motorY.setAcceleration(800);
  motorZ.setMaxSpeed(2000);
  motorZ.setAcceleration(500);

  Serial.println("Gantry System Ready with Smooth Motion!");

  // Move the gantry to a specific position
  moveGantry(50, 50, -30); // Move X to 50mm, Y to 50mm, Z to -30mm
  delay(2000); // Wait for 2 seconds

  // Return to the initial position
  moveGantry(0, 0, 0); // Move back to X=0, Y=0, Z=0
  delay(2000); // Wait for 2 seconds

  Serial.println("Motion Complete!");
}

// Function to move gantry synchronously
void moveGantry(float x, float y, float z) {
  // Convert mm to steps
  long stepsX = x * stepsPerMM;
  long stepsY = y * stepsPerMM;
  long stepsZ = z * stepsPerMM;

  // Set target positions for all motors
  motorX1.moveTo(stepsX);
  motorX2.moveTo(stepsX); // X2 moves synchronously with X1
  motorY.moveTo(stepsY);
  motorZ.moveTo(stepsZ);

  // Run all motors until they reach their targets
  while (motorX1.distanceToGo() != 0 || motorX2.distanceToGo() != 0 || 
         motorY.distanceToGo() != 0 || motorZ.distanceToGo() != 0) {
    motorX1.run();
    motorX2.run();
    motorY.run();
    motorZ.run();
  }

  Serial.print("Moved to X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" Z: ");
  Serial.println(z);
}

void loop() {
  // Intentionally left empty as no repeated actions are required.
}
