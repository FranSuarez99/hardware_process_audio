#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Rotary Encoder Connections
#define ENC_A 2
#define ENC_B 3
#define ENC_BUTTON 4 // Optional

volatile int encoderPos = 0;
int lastEncoded = 0;
boolean direction;

void setup() {
  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display(); // Show initial display buffer contents (splashscreen)
  delay(2000); // Pause for 2 seconds
  display.clearDisplay(); // Clear the buffer

  // Rotary Encoder setup
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENC_A), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), updateEncoder, CHANGE);
  
  // If using button
  pinMode(ENC_BUTTON, INPUT_PULLUP);
}

void loop() {
  // Display current encoder position
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Encoder Value: ");
  display.println(encoderPos);
  display.display();

  // If using button
  checkButton();
}

void updateEncoder() {
  int MSB = digitalRead(ENC_A); // Read encoder pin A
  int LSB = digitalRead(ENC_B); // Read encoder pin B

  int encoded = (MSB << 1) | LSB; // Convert the 2 pin value to single number

  int sum  = (lastEncoded << 2) | encoded; // Adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) direction = true; // Clockwise
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) direction = false; // Counter-clockwise

  if(direction) encoderPos++;
  else encoderPos--;

  // Remember previous encoded value
  lastEncoded = encoded;
}

// If using button
void checkButton() {
  if(digitalRead(ENC_BUTTON) == LOW) {
    // Button pressed
    // Your action here (if any)
  }
}