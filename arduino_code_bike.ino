
int led = 13; // LED pin
int sensor = 3; // Sensor pin
int val; // Numeric variable to store sensor state
int counter = 0; // Counter for magnetic field detection events
bool shouldCount = true; // Control variable to count once per event
unsigned long lastTime = 0; // Time of the last revolution
unsigned long currentTime; // Current time snapshot

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud
  pinMode(led, OUTPUT); // Set LED pin as output
  pinMode(sensor, INPUT); // Set sensor pin as input
}

void loop() {
  val = digitalRead(sensor); // Read the sensor
  if (val == LOW) { // When magnetic field is detected, turn LED on
    digitalWrite(led, HIGH);
    if (shouldCount) {
      currentTime = millis(); // Get current time in milliseconds
      if (lastTime != 0) {
        unsigned long timeInterval = currentTime - lastTime; // Calculate time interval between current and last revolution
        float rpm = 60000.0 / timeInterval; // Convert time interval to RPM
        Serial.print(counter);
        Serial.print(","); // Separating values by commas for easier parsing
        Serial.print(rpm);
        Serial.print("\n");
      }
      counter++;
      lastTime = currentTime; // Update last time to current time
      shouldCount = false; // Prevent further counting until state changes
    }
    delay(100); // Short delay to debounce
  } else {
    digitalWrite(led, LOW);
    shouldCount = true; // Re-enable counting when sensor state is not LOW
  }
}
