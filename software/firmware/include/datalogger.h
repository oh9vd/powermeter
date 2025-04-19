#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <math.h>
#include "model.h"

class DataLogger
{
private:
  static const size_t capacity = JSON_OBJECT_SIZE(4) + 40;
  StaticJsonDocument<capacity> doc;
  Model &m; // Reference to the Model object containing measurement values

#include <math.h>

/**
 * @brief Rounds a given double value to three decimal places.
 *
 * This function takes a double value, multiplies it by 1000, rounds it,
 * and then divides by 1000 to achieve a precision of three decimal places.
 *
 * @param value The double value to be rounded.
 * @return The value rounded to three decimal places.
 */

  inline double roundToThreeDecimalPlaces(double value)
  {
    return round(value * 1000.0) / 1000.0;
  }

public: 
  DataLogger(Model &model) : m(model) {}

  void init() {
  }

  /**
   * @brief Logs measurement data to the serial console in JSON format.
   *
   * The loop function reads the latest measurement data from the model, creates
   * a JSON object with the data, and serializes it to the serial console. The
   * JSON object contains the timestamp in milliseconds, approximate frequency in kHz,
   * forward power in dBm, and reflected power in dBm. The power values are
   * rounded to three decimal places before being added to the JSON object.
   * A newline is printed after the JSON object to delimit each measurement.
   * The JSON document is cleared after each measurement to prepare it for the
   * next loop iteration.
   */
  void loop() {
    if (m.enc_changed)
      return;
    doc[F("t")] = millis(); // Timestamp in milliseconds
    doc[F("f")] = m.freq;   // Frequency in kHz
    doc[F("i")] = roundToThreeDecimalPlaces(m.fwdp); // Forward power in dBm, rounded to three decimal places 
    doc[F("r")] = roundToThreeDecimalPlaces(m.refp); // Reflected power in dBm, rounded to three decimal places 
    serializeJson(doc, Serial);
    Serial.println(); // Print a newline after the JSON object
    doc.clear(); // Clear the document for the next loop iteration
  }
};
