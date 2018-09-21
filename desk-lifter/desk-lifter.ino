// SETTINGS
const int stretch = 100;

// PINS
const int stepPin   = 11;
const int dirPin    = 10;
const int sleepPin  = 12;
const int switchPin = 13;

// STATE
bool sleeping = true;
int current_position = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(stepPin,     OUTPUT);
  pinMode(dirPin,      OUTPUT);
  pinMode(switchPin,   INPUT);
  pinMode(sleepPin,    OUTPUT);

  digitalWrite(sleepPin, LOW);

  delay(1000);

  if (getSwitch() == HIGH) {
    current_position = stretch/2;
  } else {
    current_position = -(stretch/2);
  }
}

void loop() {
  // Determine position based on switch
  int desired_position;
  if (getSwitch() == HIGH) {
    desired_position = stretch/2;
  } else {
    desired_position = -(stretch/2);
  }

  // If we aren't where we want to be...
  if (desired_position != current_position) {
    digitalWrite(LED_BUILTIN, HIGH); // light on

    if (sleeping) {
      sleeping = false;
      digitalWrite(sleepPin, HIGH);
      // "When emerging from Sleep mode provide a delay of 1 ms before issuing a Step command"
      delay(2);
    }

    // ... Issue one step in the correct direction
    if (desired_position > current_position) {
      // go up
      digitalWrite(dirPin, HIGH);
      current_position++;
    } else if (desired_position < current_position) {
      // go down
      digitalWrite(dirPin, LOW);
      current_position--;
    }

    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  } else {
    digitalWrite(LED_BUILTIN, LOW);  // light off
    digitalWrite(sleepPin, LOW); // Sleep.
    sleeping = true;
  }

  delayMicroseconds(500);
}

int getSwitch() {
  return digitalRead(switchPin);
}
