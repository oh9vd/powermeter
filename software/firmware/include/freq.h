
#include <FreqCount.h>
#include "model.h"

#define FREQUENCY_COUNT_INTERVAL_MS (40L)

/**
 * @brief Class to manage frequency measurement using the FreqCount library.
 *
 * This class uses the FreqCount library to measure the frequency of a signal
 * connected to the Arduino's digital pin 5 (Timer 0). The measured frequency
 * is stored in a Model instance for further processing or display.
 */
class Freq
{
private:
  Model &m; // Reference to the model object where the measured frequency will be stored

public:
  /**
   * @brief Constructor for the Freq class.
   *
   * Initializes with a reference to a Model, linking frequency measurements
   * to the model's storage.
   *
   * @param model The model that stores the frequency data.
   */
  Freq(Model &model)
      : m(model) {}

  /**
   * @brief Initializes the FreqCount library for frequency measurement.
   *
   * Sets up the FreqCount library to begin measuring frequency signals from
   * digital pin 5. The counting interval is set as specified by
   * FREQUENCY_COUNT_INTERVAL_MS.
   */
  inline void init()
  {
    FreqCount.begin(FREQUENCY_COUNT_INTERVAL_MS);
  }

  /**
   * @brief Reads and updates frequency values from the FreqCount library.
   *
   * Checks if new frequency data is available, retrieves it, scales appropriately,
   * and updates the model's frequency storage. Scales the raw frequency count
   * to match the actual frequency being measured.
   */
  inline void loop()
  {
    if (FreqCount.available())
    {
      // Scale the read frequency count appropriately (adjust division factor as needed)
      m.freq = FreqCount.read() / 5L;
      m.freq_squared = m.freq * m.freq; // Store the square of the frequency for later use
    }
  }
};
