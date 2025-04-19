#pragma once

#include "model.h"


// The Calc class is responsible for calculating power metrics such as incident power,
// reflection coefficient, SWR (Standing Wave Ratio), and return loss using measurement data.
class Calc
{
private:
  Model &m; // Reference to the Model object containing measurement values

  /**
   * @brief Converts power from dBm to watts.
   *
   * This function converts a given power value in dBm into its equivalent in watts.
   * The conversion formula used is: W = 10^(dBm/10) / 1000.
   *
   * @param dbm Power level in dBm.
   * @return Corresponding power in watts.
   */
  inline double dbm2w(double dbm)
  {
    return pow(10, dbm / 10.0 - 3.0);
  }

public:
  /**
   * @brief Constructor for the Calc class.
   *
   * Initializes an instance of Calc with a reference to a Model object.
   *
   * @param model Reference to a Model object.
   */
  Calc(Model &model) : m(model) {}

  /**
   * @brief Placeholder for any initialization logic.
   *
   * Currently does nothing; provided for potential future use where additional
   * setup might be necessary.
   */
  void init() {}

  /**
   * @brief Calculates various power metrics like incident power, reflection coefficient, SWR,
   * and return loss based on the current readings from the model.
   *
   * The calculations consider whether the readings are based on an AD8307 logarithmic amplifier
   * or a diode detector. Adjustments for signal presence and probe attenuation are also made.
   *
   * @note This function should be called after updating the model with the latest readings.
   */
  void loop()
  {
    if(m.enc_changed)
      return;

    double fwdV = m.fwdV; // Forward voltage reading
    double refV = m.refV; // Reflected voltage reading

    // make frequency corrections to the voltage readings
    fwdV -= -0.6282E-3 * static_cast<double>(m.freq) + 8.9;
    refV -= -0.6473E-3 * static_cast<double>(m.freq) + 8.09;

    // Calculate incident 
    m.fwdp = 0.02452 * fwdV - 71.469;
    m.refp = 0.024750 * refV - 72.722;

    // coupler attenuations to be added to the power readings
    m.fwdp += m.coupling();
    m.refp += m.directivity();

    // extra 20 dB attenuators to be added to the power readings
    m.fwdp += 20.2;
    m.refp += 20.2;

    // Convert powers from dBm to watts
    m.fwdw = dbm2w(m.fwdp);
    m.refw = dbm2w(m.refp);

    // Calculate reflection coefficient, SWR, and return loss
    m.gamma = sqrt(m.refw / m.fwdw);       // Reflection coefficient
    m.swr = (1 + m.gamma) / (1 - m.gamma); // Standing Wave Ratio
    m.rl = -20 * log10(m.gamma);           // Return Loss in dB
    // Calculate loss of power in watts
    // Loss = Forward Power * ((SWR - 1) / (SWR + 1))^2
    m.loss = m.fwdw * ((m.swr - 1)*(m.swr - 1)) / ((m.swr + 1)*(m.swr + 1));
  }
};
