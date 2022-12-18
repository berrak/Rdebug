/*
 * File: Rdebug.cpp
 * The Arduino library provides a unique form of debugging.
 *
 * Copyright (c) 2021 Ralph Bacon
 * https://github.com/RalphBacon/224-Superior-Serial.print-statements
 *
 * Adapted and modified original code.
 * Copyright (C) 2022 Debinix Team
 * https://github.com/berrak/Rdebug
 *
 * The MIT License
 *
 */

#ifndef RDEBUG_H_
#define RDEBUG_H_

// User picks debugging level from this list in the Arduino sketch
//
// More information: https://github.com/berrak/Rdebug
//
// DEBUGLEVEL_OFF - all debug macros are disabled
// DEBUGLEVEL_ON - the non-traced macro (lazy mode) are enabled
// DEBUGLEVEL_DEBUG - traced debug messages
// DEBUGLEVEL_INFO - traced imnformation messages
// DEBUGLEVEL_WARN - traced warning messages
// DEBUGLEVEL_ERROR - traced error messages

// Then include the libray
// #include <Rdebug.h>

void debugNothing(...) {
    // This does nothing and will be zapped by the compiler
}

// By default we want a trace stamp output in the first instance
bool traceStampRequired = true;

String debugStr = "";
bool foundNL = false;

// The tracestamp looks like [xxx][mainfunction:45]
#define traceStamp(x, y, z)                                                    \
    if (traceStampRequired) {                                                  \
        Serial.print("[");                                                     \
        Serial.print(x);                                                       \
        Serial.print("]");                                                     \
        Serial.print("[");                                                     \
        Serial.print(__FUNCTION__);                                            \
        Serial.print(":");                                                     \
        Serial.print(__LINE__);                                                \
        Serial.print("] ");                                                    \
    }                                                                          \
    debugStr = y;                                                              \
    foundNL = debugStr.indexOf("\n") > -1;                                     \
    if (z || foundNL)                                                          \
        traceStampRequired = true;                                             \
    else                                                                       \
        traceStampRequired = false;

// Silence any screen output from the debug* macros!
#if defined(DEBUGLEVEL_OFF)
#define debug(x) debugNothing(x);
#define debugln(x) debugNothing(x);
#endif

#if defined(DEBUGLEVEL_ERROR)
#define DEBUGLEVEL_WARN
#define DEBUGLEVEL_INFO
#define DEBUGLEVEL_DEBUG
#define DEBUGLEVEL_ON
#define debugE(x)                                                              \
    traceStamp("ERR", x, false);                                               \
    Serial.print(x);
#define debuglnE(x)                                                            \
    traceStamp("ERR", x, true);                                                \
    Serial.println(x)
#else
#define debugE(x)   // Nothing to see here
#define debuglnE(x) // Or here
#endif

#if defined(DEBUGLEVEL_WARN)
#define DEBUGLEVEL_INFO
#define DEBUGLEVEL_DEBUG
#define DEBUGLEVEL_ON
#define debugW(x)                                                              \
    traceStamp("WRN", x, false);                                               \
    Serial.print(x);
#define debuglnW(x)                                                            \
    traceStamp("WRN", x, true);                                                \
    Serial.println(x)
#else
#define debugW(x)   // Nothing to see here
#define debuglnW(x) // Or here
#endif

#if defined(DEBUGLEVEL_INFO)
#define DEBUGLEVEL_DEBUG
#define DEBUGLEVEL_ON
#define debugI(x)                                                              \
    traceStamp("INF", x, false);                                               \
    Serial.print(x);
#define debuglnI(x)                                                            \
    traceStamp("INF", x, true);                                                \
    Serial.println(x);
#else
#define debugI(x)   // Nothing to see here
#define debuglnI(x) // Or here
#endif

// This is a macro that turns simple (one string)
// Serial.println statements with trace
#if defined(DEBUGLEVEL_DEBUG)
#define DEBUGLEVEL_ON
#define debugD(x)                                                              \
    traceStamp("DBG", x, false);                                               \
    Serial.print(x);
#define debuglnD(x)                                                            \
    traceStamp("DBG", x, true);                                                \
    Serial.println(x)
#else
#define debugD(x)   /* Nothing to see here */
#define debuglnD(x) // Or here
#endif

// Lazy replacement for Serial.print and Serial.println
#if defined(DEBUGLEVEL_ON)
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#endif

#endif /* RDEBUG_H_ */

/* EOF */
