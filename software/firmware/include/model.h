#pragma once

#include "screen.h"

class Model
{
private:


public:
  Model() {};
  void init() {};

  // current screen
  Screen scr = RAW;
  // current time
  unsigned long time = millis();
  // time elapsed in one loop round
  uint32_t loopTime = 0;
  // encoder value
  int32_t enc = -999;
  bool enc_changed = false;
  // button pressed?
  bool but = false;
  // the frequency
  uint32_t freq;
  // the freq^2
  uint32_t freq_squared;
  // the rssi voltage mV
  uint32_t rssiV;
  // voltage from fwd log detector
  uint16_t fwdV;
  // voltage from ref log detector
  uint16_t refV;

  /**
   * @brief Calculates the coupler's attenuation in dB as a function of the
   * frequency in kHz.
   *
   * This function uses a 2nd order polynomial fit to determine the coupler
   * attenuation value based on the measured frequency. The coefficients are
   * derived from measurements and are specific to the coupler used in the
   * device.
   * @return The coupler's attenuation in dB.
   */
  inline double coupling() const {
    return 4.389E-10 * static_cast<double>(freq_squared) - 2.397E-6 * static_cast<double>(freq) + 37.498;
  }

  inline void clear() {
    fwdV = 0;
    refV = 0;
    fwdw = 0;
    refw = 0;
    fwdp = 0;
    refp = 0;
    loss = 0;
    rl = 0;
    swr = 0;
    gamma = 0;
  };

/**
 * @brief Calculates the directivity of the coupler in dB as a function of the
 * frequency in kHz.
 *
 * This function uses a 2nd order polynomial fit to determine the directivity
 * value based on the measured frequency. The coefficients are derived from
 * experimental data specific to the coupler being used.
 *
 * @return Directivity in dB.
 */
  inline double directivity() const {
    return 1.354E-9 * static_cast<double>(freq_squared) - 1.858E-5 * static_cast<double>(freq) + 37.51;
  };
  
  // is there a signal present?
  inline bool isSignalPresent() const {
    return (rssiV > 19);
  };

  // Reflection coeficient
  double gamma;
  // standing wave ratio
  double swr;
  // return loss in dB
  double rl;
  // Forward power in W
  double fwdw;
  // Reflected power in W
  double refw;
  // Forward power in dBm 
  double fwdp;
  // Reflected power in dBm 
  double refp;
  // Loss of Power in Watts
  double loss;
};
