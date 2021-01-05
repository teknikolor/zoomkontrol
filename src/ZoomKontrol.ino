/**
 * This project turns the ESP32 into a Bluetooth LE keyboard that writes the keyboard commands for Mute and Video On/Off in Zoom for iOS and Chrome.  Note that iOS users must manually re-map the OPTION (ALT) key to be COMMAND in iOS settings.
 */
#include <Arduino.h>
#include <BleKeyboard.h>


BleKeyboard bleKeyboard;
const int BUTTON_PIN1 = 15;     // set the number of the mute button pin
const int BUTTON_PIN2 = 2;     // set the number of the video button pin
const int LED_PIN =  5;      // the number of the LED pin (makes LED on pin 5 blink on button press)
int BUTTON_STATE1 = 0; // set initial state
int BUTTON_STATE2 = 0; // set initial state

void setup() {
  delay(500);
  pinMode(LED_PIN, OUTPUT); // set pin mode for LED pin
  pinMode(BUTTON_PIN1, INPUT_PULLUP); // set pin mode for mute button pin
  pinMode(BUTTON_PIN2, INPUT_PULLUP); // set pin mode for video button pin
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void loop() {
 // read the state of the pushbutton1 value:
  BUTTON_STATE1 = digitalRead(BUTTON_PIN1);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (BUTTON_STATE1 == LOW) {
    digitalWrite (LED_PIN, LOW);
    Serial.println("Sending 'Hello Button 1'...");
    // send Mac & iOS Keystrokes
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.press('a');
    delay(50);
    bleKeyboard.releaseAll();
     // send PC & Chromebook Keystrokes
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press('a');
    delay(50);
    bleKeyboard.releaseAll();
    //bleKeyboard.print("Hello Button2");
    delay(200);
  } else {
    digitalWrite (LED_PIN, HIGH);
    bleKeyboard.releaseAll();
  }
  delay(10);

// read the state of the pushbutton2 value:
  BUTTON_STATE2 = digitalRead(BUTTON_PIN2);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (BUTTON_STATE2 == LOW) {
    digitalWrite (LED_PIN, LOW);
    Serial.println("Sending 'Hello button 2'...");
    // send Mac & iOS Keystrokes
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.press('v');
    delay(50);
    bleKeyboard.releaseAll();
     // send PC & Chromebook Keystrokes
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press('v');
    delay(50);
    bleKeyboard.releaseAll();
    //bleKeyboard.print("Hello Button2");
    delay(200);
  } else {
    digitalWrite (LED_PIN, HIGH);
    bleKeyboard.releaseAll();
  }
  delay(10);
}
