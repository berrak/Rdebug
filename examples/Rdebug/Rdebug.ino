#include <Arduino.h>

// The heart of the library is the hierarchy. Set the log level
// to `WARN`, then the `lower` groups are also included. In this
// case, it enables `ON`, `DEBUG`, and `INFO`.

// ON < DEBUG < INFO < WARN < ERROR

// DEBUGLEVEL_OFF - all debug macros are disabled
// DEBUGLEVEL_ON - the non-traced macro (lazy mode) are enabled
// DEBUGLEVEL_DEBUG - traced debug messages
// DEBUGLEVEL_INFO - traced imnformation messages
// DEBUGLEVEL_WARN - traced warning messages
// DEBUGLEVEL_ERROR - traced error messages

#define DEBUGLEVEL_ERROR
#include <Rdebug.h>

void fadeLED(void);
int fadeDebug(int loop_counter);
int fadeInfo(int loop_counter);
int fadeWarn(int loop_counter);
int fadeError(int loop_counter);

int ledPin = LED_BUILTIN;

// ------------------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP
// ------------------------------------------------------------------
void setup() {
    Serial.begin(9600);
    do {
        delay(2000);
    } while (!Serial);

    Serial.println("Serial.println: Setup complete.");
}
// ------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// ------------------------------------------------------------------
void loop() {

    static int loop_counter = 0;

    Serial.println("Serial.println: In the loop");

    fadeDebug(loop_counter); // Uses Debug level macros only
    fadeInfo(loop_counter);  // Uses Info level macros only
    fadeWarn(loop_counter);  // Uses Warn level macros only
    fadeError(loop_counter); // Uses Error level macros only

    debugln("All four calls done!"); // no trace data added

    loop_counter++;
}
// ------------------------------------------------------------------
// HELPERS     HELPERS     HELPERS     HELPERS     HELPERS
// ------------------------------------------------------------------
void fadeLED(void) {
    for (int fadeValue = 0; fadeValue <= 255; fadeValue += 10) {
        analogWrite(ledPin, fadeValue);
        delay(30);
    }

    for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 10) {
        analogWrite(ledPin, fadeValue);
        delay(30);
    }
}
// ------------------------------------------------------------------
int fadeDebug(int loop_counter) {
    debugD("Received value:");
    debuglnD(loop_counter);

    fadeLED();

    debugD("Returning: ");
    debuglnD(loop_counter + 1);
    return loop_counter + 1;
}

// -----------------------------------------------------------------
int fadeInfo(int loop_counter) {
    debugI("Received value:");
    debuglnI(loop_counter);

    fadeLED();

    debugI("Returning: ");
    debuglnI(loop_counter + 1);
    return loop_counter + 1;
}
// ------------------------------------------------------------------
int fadeWarn(int loop_counter) {
    debugW("Received value:");
    debuglnW(loop_counter);

    fadeLED();

    debugW("Returning: ");
    debuglnW(loop_counter + 1);
    return loop_counter + 1;
}

// -----------------------------------------------------------------
int fadeError(int loop_counter) {
    debugE("Received value:");
    debuglnE(loop_counter);

    fadeLED();

    debugE("Returning: ");
    debuglnE(loop_counter + 1);
    return loop_counter + 1;
}

/* EOF */
