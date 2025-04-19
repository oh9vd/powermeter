#pragma once

#define ENCODER_USE_INTERRUPTS
#include <Encoder.h>
#include "model.h"

// Define pins for the encoder and button
#define ENC_B 2
#define ENC_A 3
#define ENC_BUTTON 4

class Enc
{
private:
  Model &m;  // Reference to the Model object
  Encoder e; // Encoder object

public:
  // Constructor initializes the encoder with specified pins and links model
  Enc(Model &model)
      : m(model), e(ENC_A, ENC_B)
  {
  }

  // Initialize function to set up encoder button as an input with pull-up resistor
  void init()
  {
    pinMode(ENC_BUTTON, INPUT_PULLUP);
  }

  /**
   * @brief Reads the encoder and button state
   *
   * This function reads the current state of the rotary encoder and
   * button. It stores the values in the model if they have changed.
   *
   * The encoder value is divided by 4 to get the correct step size
   * for the screen selection. Debouncing is assumed handled elsewhere.
   */
  inline void loop()
  {
    // Read encoder position and adjust by dividing to get the proper step size
    int32_t enc = e.read() >> 2;

    // Check if encoder position changed and is within valid range
    if (enc != m.enc && enc >= static_cast<int>(Screen::MAIN) && enc <= static_cast<int>(Screen::RAW))
    {
      // Update model encoder value and associated screen enumeration
      m.enc = enc;
      m.scr = static_cast<Screen>(enc);
      m.enc_changed = true; // Mark encoder change
    }
    else
    {
      m.enc_changed = false; // No change in encoder position
    }

    // Read button state (LOW when pressed)
    bool but = digitalRead(ENC_BUTTON) == LOW;

    // Check if button state has changed
    if (but != m.but)
    {
      // Update model button state
      m.but = but;
    }
  }
};
