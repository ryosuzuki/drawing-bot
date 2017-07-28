#include <ArduinoJson.h>
#include <AccelStepper.h>

AccelStepper stepper1(5, 2, 3, 4, 5);
AccelStepper stepper2(5, 8, 9, 10, 11);

int calculateStep(int angle);

void setup() {
  Serial.begin(9600);

  //Motor A
  stepper1.setMaxSpeed(800.0);
  stepper1.setAcceleration(100.0);

  //Motor B
  stepper2.setMaxSpeed(800.0);
  stepper2.setAcceleration(100.0);
}

void loop() {
  String json = "";
  while (Serial.available() > 0) {
    json += (char) Serial.read();
    delay(5);
  }

  if (json != "") {
    Serial.println("received");
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(json);

    int id = root["id"];
    int angle = root["angle"];
    int step = calculateStep(angle);
    if (id == 1) {
      stepper1.moveTo(step);
    } else if (id == 2) {
      stepper2.moveTo(step);
    }
  }

  stepper1.run();
  stepper2.run();
}


int calculateStep(int angle){
  if(angle > 360 || angle < -360){
    Serial.println("valid angles are between -360 and 360");
    return 0;
  }
  Serial.println(angle);
  float steps = (float(2048/180)*angle);
  Serial.println("Expect to move: ");
  Serial.print(steps);
  Serial.print(" steps.");
  return int(steps);
}
