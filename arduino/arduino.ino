#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Rotary Encoder Connections
#define ENC_A 2
#define ENC_B 3

Adafruit_SSD1306 display(128, 32, &Wire, -1);

volatile int encoderPos = 0;
int lastEncoded = 0;
boolean direction;

void setup() {
  Serial.begin(9600);

  Serial.println("OLED FeatherWing test");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  Serial.println("IO test");

  // Rotary Encoder setup
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);

  // text display tests
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Connecting to SSID\n'adafruit':");
  display.print("connected!");
  display.println("IP: 10.0.1.23");
  display.println("Sending val #0");
  display.setCursor(0,0);
  display.display(); // actually display all of the above
}

void loop() {
  // Read encoder position
  updateEncoder();

  // Display current encoder position
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Encoder Value: ");
  display.println(encoderPos);
  display.display();
}

void updateEncoder() {
  int MSB = digitalRead(ENC_A); // Read encoder pin A
  int LSB = digitalRead(ENC_B); // Read encoder pin B

  int encoded = (MSB << 1) | LSB; // Convert the 2 pin value to single number

  int sum = (lastEncoded << 2) | encoded; // Adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    if (!direction) {
      encoderPos++;
      direction = true; // Clockwise
    }
  }
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    if (direction) {
      encoderPos--;
      direction = false; // Counter-clockwise
    }
  }

  // Remember previous encoded value
  lastEncoded = encoded;
}