#pragma once
#include "model.h"

// Class to manage time-related operations and updates for a Model.
class Time
{
private:
  Model &m; // Reference to a Model object to update its timing information.

public:
  // Constructor that initializes the Time object with a reference to a Model.
  explicit Time(Model &model) : m(model) {}

  /**
   * @brief Initializes the current time in the model.
   *
   * Sets the model's time to the current time from the millis function.
   * This should be called to establish an initial time reference.
   */
  void init()
  {
    m.time = millis();
  }

  /**
   * @brief Updates the loop time and current time in the model.
   *
   * Calculates the elapsed time since the last call to this function
   * and updates the model's loopTime with this duration. Also updates
   * the model's time with the current time from the millis function.
   */
  void loop()
  {
    unsigned long currentMillis = millis(); // Capture the current time once for efficiency.
    m.loopTime = currentMillis - m.time;    // Calculate the elapsed time since the last update.
    m.time = currentMillis;                 // Update the model's time to the current time.
  }
};
