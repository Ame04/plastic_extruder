/**
 * @file plastic_extruder.ino
 * @brief Includes, defines and function signatures
 * @author CAMUS Armand
 * @date 17/02/2024
 * @version A1
*/

/*******************************************************************************
 * Includes
********************************************************************************/
#include <Wire.h>
#include <Ramp.h>
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

/* DC motor defines */
#define DC_PIN_FW 5
#define DC_PIN_BW 6
#define DC_RAMP_DURATION 1000

/* LCD defines */
#define LCD_ADDR  0x27
#define LCD_ROW 2
#define LCD_COLLUMN 16

/*******************************************************************************
 * Type definitions
********************************************************************************/
/* DC type definitions */
typedef enum dc_rotation_way {DC_FORWARD, DC_BACKWARD};

/*******************************************************************************
 * Global variables
********************************************************************************/
ContinuousStepper<FourWireStepper, TimerOneTicker> winding_stepper;
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLLUMN, LCD_ROW);
rampUnsignedInt dc_ramp;

/*******************************************************************************
 * Function signatures
********************************************************************************/
/* Stepper functions */

/* DC motor functions */
void dc_init(void);
bool dc_set_target_speed(uint8_t speed);
void dc_set_target_rotation_way(dc_rotation_way rotation_way);
void dc_update_current_speed(void);

/* LCD functions */