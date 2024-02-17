/**
 * @file plastic_extruder.ino
 * @author CAMUS Armand
 * @date 17/02/2024
 * @brief Includes, defines and function signatures
*/

/*******************************************************************************
 * Includes
********************************************************************************/
#include <Wire.h>
#include <ContinuousStepper.h>
#include <ContinuousStepper/Tickers/TimerOne.hpp>
#include <LiquidCrystal_I2C.h>
/*******************************************************************************
 * Defines
********************************************************************************/
/* Stepper defines */
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

/* LCD defines */
#define LCD_ADDR  0x27
#define LCD_ROW 2
#define LCD_COLLUMN 16

/*******************************************************************************
 * Global varibales
********************************************************************************/
ContinuousStepper<FourWireStepper, TimerOneTicker> winding_stepper;
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLLUMN, LCD_ROW);
