#pragma once
#include "model.h"
#include "global.h"
class Rssi
{
private:
  Model &m; // Reference to the Model object that stores RSSI values

  /**
   * @brief Reads the current RSSI value from the RSSI pin.
   *
   * Calculates RSSI voltage in millivolts based on ADC reading, avoiding floating-point arithmetic for efficiency.
   * Accumulates raw data from ADC over a defined window (AWG_WINDOW), and averages it
   *
   * @return The processed and averaged RSSI value.
   */
  uint16_t read()
  {
    uint32_t raw_data = 0;
    uint32_t rssi = analogRead(A0); // Read the raw analog value from pin A0

    // Calculate RSSI voltage in millivolts based on ADC reading, avoiding floating-point arithmetic for efficiency
    for (int i = 0; i < AWG_WINDOW; i++)
    {
      raw_data += rssi; // Accumulate raw data from ADC
      rssi = analogRead(A0);
    }
    return raw_data / AWG_WINDOW; // Scale down by shifting
  }

public:
  // Constructor initializes the RSSI model reference
  Rssi(Model &model) : m(model) {}

  /**
   * @brief Initializes the RSSI reader.
   *
   * Sets the initial RSSI value to zero, preparing it for future updates.
   */
  inline void init()
  {
    m.rssiV = 0L; // Initialize RSSI value to zero
  }


  /**
   * @brief Reads and updates the RSSI value from the RSSI pin.
   *
   * The loop function reads the RSSI value from the ADC and updates the model's RSSI voltage storage.
   *
   * @note This function should be called after updating the model with the latest readings.
   */
  inline void loop()
  {
    if (m.enc_changed)
      return;
    m.rssiV = read(); // Read the RSSI value from the ADC
  }
};
