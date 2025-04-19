#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "model.h"

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // Screen I2C address for 128x32 display

class Display
{
private:
  const Model &m;     // Reference to the Model object containing measurement data
  Adafruit_SSD1306 d; // SSD1306 display object

  /**
   * @brief Displays a welcome message on the screen.
   *
   * Clears the display and sets the cursor to a specific position before
   * printing the welcome text "SWR METER OH8KVA".
   */
  void welcome()
  {
    d.clearDisplay();
    d.setCursor(0, 10);
    d.println(F("SWR METER OH8KVA"));
    d.display();
  }

  /**
   * @brief Prints the main screen with measured values such as forward power,
   * SWR, return loss, and gamma values.
   */
  void mainscr()
  {
    d.clearDisplay();
    d.setCursor(0, 0);

    // row 0: Forward Power
    d.print(F("FWD __: "));
    printPower(m.fwdw);
    d.print(" ");
    if (m.isSignalPresent())
      d.print(F("S"));
    d.println();

    // row 1: SWR
    d.print(F("SWR __: "));
    if (m.swr > 0)
      printFixedWidth(m.swr, 5, 1);
    d.println();

    // row 2: Return Loss
    d.print(F("RL ___: "));
    if (m.rl > 0)
    {
      printFixedWidth(m.rl, 4, 2);
      d.print(F(" dB"));
    }
    d.println();

    // row 3: Loss of Power
    d.print(F("LOSS _: "));
    if (m.loss > 0)
      printPower(m.loss);
    d.println();

    d.display();
  }

  /**
   * @brief Displays information about the system.
   */
  void info()
  {
    d.clearDisplay();
    d.setCursor(0, 0);
    d.println(F("Documents at github"));
    d.println(F("https://github.com/oh9vd/..."));
    d.println(F(".../hardware"));
    d.println(F(".../powermeter-firmware"));
    d.display();
  }

  /**
   * @brief Displays power measurements in dBm and Watts format.
   *
   * This function prints forward and reflected power in both dBm and Watts.
   */
  void dbm()
  {
    d.clearDisplay();
    d.setCursor(0, 0);

    // row 0: Forward dBm
    d.print(F("forward: "));
    d.print(m.fwdp, 1);
    d.print(F(" dBm "));
    d.println();

    // row 1: Reflected dBm
    d.print(F("reflected: "));
    d.print(m.refp, 1);
    d.print(F(" dBm "));
    d.println();

    // row 2: Forward Watts
    d.print(F("forward: "));
    printPower(m.fwdw);
    d.println();

    // row 3: Reflected Watts
    d.print(F("reflected: "));
    printPower(m.refw);
    d.println();

    d.display();
  }

  /**
   * @brief Displays raw values from the device such as frequency, voltages,
   * and RSSI value.
   */
  void raw()
  {
    d.clearDisplay();
    d.setCursor(0, 0);

    // Row 0: Frequency and Time
    d.print(F("f: "));
    d.print(m.freq);
    d.print(F(" t: "));
    d.print(m.loopTime);
    d.println();

    // Row 1: Forward and Reflected Voltage
    d.print(F("fw: "));
    d.print(m.fwdV);
    d.print(F(" rw: "));
    d.print(m.refV);
    d.println();

    d.print(F("cpl: "));
    double cpl = m.coupling();
    d.print(cpl, 1);
    d.print(F(" dir: "));
    double dir = m.directivity();
    d.print(dir);
    d.println();

    // Row 3: RSSI Value
    d.print(F("rs: "));
    d.print(m.rssiV);
    d.println();

    d.display();
  }

  /**
   * @brief Prints a power value in a readable format with appropriate units.
   *
   * @param powW The power value in Watts.
   * @param width Optional, the width of printed string. Default is 5.
   */
  void printPower(double powW, byte width = 5)
  {
    if (powW < 1E-12)
      return;

    else if (powW < 1E-9)
    {
      printFixedWidth(powW * 1E12, width, 1);
      d.print(F(" pW"));
    }
    else if (powW < 1E-6)
    {
      printFixedWidth(powW * 1E9, width, 1);
      d.print(F(" nW"));
    }
    else if (powW < 1E-3)
    {
      printFixedWidth(powW * 1E6, width, 1);
      d.print(F(" uW"));
    }
    else if (powW < 1)
    {
      printFixedWidth(powW * 1E3, width, 1);
      d.print(F(" mW"));
    }
    else if (powW < 1.6E3)
    {
      printFixedWidth(powW, width, 1);
      d.print(F(" W"));
    }
    else
    {
      printFixedWidth(powW / 1E3, width, 2);
      d.print(F(" kW"));
    }
  }

  /**
   * @brief Prints a double with fixed width and precision.
   *
   * Pads the number with spaces to match the specified width and prints it
   * with the specified number of digits after the decimal point.
   *
   * @param number Number to print.
   * @param width Total width of the printed number.
   * @param precision Digits to show after decimal.
   * @param filler Character used for padding. Default is a space.
   */
  void printFixedWidth(double number, byte width, byte precision = 2, char filler = ' ')
  {
    unsigned long integerPart = static_cast<unsigned long>(number);
    double fractionalPart = number - integerPart;
    byte digitsPrinted = 0;

    // Calculate integer space
    unsigned long temp = integerPart;
    while (temp > 0)
    {
      temp /= 10;
      digitsPrinted++;
    }

    // Account for fractional part
    if (precision > 0)
      digitsPrinted += precision + 1;

    // Print fillers
    while (digitsPrinted < width)
    {
      d.print(filler);
      digitsPrinted++;
    }

    // Print integer and fractional parts
    d.print(integerPart);
    if (precision > 0)
    {
      d.print('.');
      for (byte i = 0; i < precision; i++)
      {
        fractionalPart *= 10;
        byte digit = static_cast<byte>(fractionalPart);
        d.print(digit);
        fractionalPart -= digit;
      }
    }
  }

public:
  /**
   * @brief Constructs a Display object with the Model reference.
   *
   * Sets up the display dimensions and initializes the display interface.
   *
   * @param model Reference to a Model object.
   */
  Display(const Model &model)
      : m(model), d(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

  /**
   * @brief Initializes the display setup for SSD1306 OLED.
   *
   * Begins communication with specified screen address. Halts if allocation
   * fails. Configures text properties and shows a welcome message.
   */
  void init()
  {
    if (!d.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
      DEBUG_PRINTLN(F("SSD1306 allocation failed"));
      for (;;)
        ; // Halt execution
    }

    d.setTextColor(SSD1306_WHITE);
    d.setTextSize(1);

    welcome();
    delay(2000);
  }

  /**
   * @brief Updates the display based on selected screen type.
   *
   * Determines which screen (main, info, dBm, or raw) to display based on
   * current selection stored in the model.
   */
  void loop()
  {
    switch (m.scr)
    {
    case Screen::MAIN:
      mainscr();
      break;
    case Screen::INFO:
      info();
      break;
    case Screen::DBM:
      dbm();
      break;
    case Screen::RAW:
      raw();
      break;
    }
  }
};
