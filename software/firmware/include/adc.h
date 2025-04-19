#pragma once

#include <Arduino.h>
#include <LTC230x.hpp>
#include "global.h"
using namespace ltc230x;



#include "model.h"

// The Adc class manages the interaction with multiple ADCs, reading voltage values
// from RF detectors and diodes, and storing them in a Model instance.
class Adc
{
private:
  Model &m; // Reference to the model where ADC readings will be stored

  // Instances of LTC230x representing different ADC channels for data acquisition
  LTC230x ltc2309_ad0;
  LTC230x ltc2309_ad1;
  LTC230x ltc2309_ad2;
  LTC230x ltc2309_ad3;

  /**
   * @brief Reads averaged data from a specified ADC and shifts it to adjust precision.
   *
   * This function accumulates raw data from the ADC over a defined window (AWG_WINDOW),
   * averages it, and shifts the result right by 4 bits for consistent scaling.
   *
   * @param ltc2309 The ADC from which to read.
   * @return The processed and scaled data.
   */
  uint16_t read(ltc230x::LTC230x &ltc2309)
  {
    uint32_t raw_data = 0;
    for (int i = 0; i < AWG_WINDOW; i++)
    {
      raw_data += ltc2309.read_raw(); // Accumulate raw data from ADC
    }
    raw_data /= AWG_WINDOW; // Compute average
    raw_data >>= 4; // Scale down by shifting

    if (raw_data > 3300)
      raw_data = 3300; // Clamp to maximum ADC value

    if (raw_data < 400)
      raw_data = 0; // Clamp to minimum ADC value

    return raw_data;
  }

public:
  /**
   * @brief Constructor for the Adc class.
   *
   * Initializes an Adc instance with a reference to a Model object.
   *
   * @param model The model where ADC data will be stored.
   */
  Adc(Model &model) : m(model) {}

  /**
   * @brief Initializes all connected ADCs.
   *
   * Each ADC is configured to read voltages using unipolar mode and set
   * to wake mode with a specific channel configuration.
   */
  inline void init()
  {
    initializeADC(ltc2309_ad0, channel::POSITIVE_0_NEGATIVE_COM);
    initializeADC(ltc2309_ad1, channel::POSITIVE_1_NEGATIVE_COM);
  }

  /**
   * @brief Configures an ADC with specific operational settings.
   *
   * Sets the address, channel, mode, and sleep state for the provided ADC.
   *
   * @param adc The ADC to configure.
   * @param ch The channel configuration to apply.
   */
  inline void initializeADC(LTC230x &adc, channel::Channel ch)
  {
    constexpr auto addr = address::AD1_LOW_AD0_LOW;
    constexpr auto mode = uni_bi::UNIPOLAR;
    constexpr auto sleepMode = sleep::WAKE;

    adc.begin(Wire, addr);
    adc.set_channel(ch);
    adc.set_unipolar_bipolar_mode(mode);
    adc.set_sleep_mode(sleepMode);
  }

  /**
   * @brief Reads and stores ADC data into the model.
   *
   * Continuously reads data from each ADC channel and updates the model's forward
   * and reflected voltages, applying thresholds to filter noise.
   */
  void loop()
  {
    if (m.enc_changed)
      return;
      
    // Read forward detector voltage 
    m.fwdV = read(ltc2309_ad0);

    // Read reflected detector voltage
    m.refV = read(ltc2309_ad1);
  }
};
