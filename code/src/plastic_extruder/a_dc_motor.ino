/**
 * @file a_dc_motor.ino
 * @brief Function to handle the DC motor of the project
 * @author CAMUS Armand
 * @date 17/02/2024
 * @version A1
*/

/*******************************************************************************
 * Global variables of module
********************************************************************************/

rotation_way dc_current_rotation_way;
rotation_way dc_target_rotation_way;
uint8_t dc_current_speed;
uint8_t dc_target_speed;

/*******************************************************************************
 * Functions of module
********************************************************************************/
/**
 * Initialyse DC motor pins and way of rotation
*/
void dc_init(void){
    winding_stepper.begin(STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);
    dc_current_rotation_way = FWD;
    dc_target_rotation_way = FWD;
    dc_current_speed = 0;
    dc_target_speed = 0;
}

/**
 * Set the speed of the motor
 * @param speed the wanted speed in %
 * @return A bool equal to 0 if no error and 1 if an error occured (speed too high)
*/
bool dc_set_target_speed(uint8_t speed){
    bool error = false;

    if (speed > 100){
        speed = 0;
        error = true;
    }
    dc_target_speed = speed;
    // Set the ramp for smooth transitions only if no change in direction is ongoing
    if (dc_current_rotation_way == dc_target_rotation_way){
        dc_ramp.go(speed, DC_RAMP_DURATION);
    }

    return error;
}

/**
 * Set the DC motor rotation way
 * @param rotation_way the wanted rotation way
*/
void dc_set_target_rotation_way(rotation_way rotation_way){
    if (rotation_way != dc_current_rotation_way){
        dc_ramp.go(0, DC_RAMP_DURATION);
    }
    dc_target_rotation_way = rotation_way;
}

/**
 * Update the actual speed of the motor until the target way and speed is achieved
*/
void dc_update_current_speed(void){
    bool error = false;
    uint8_t mapped_speed;
    uint8_t ramp_speed;

    // Update the ramp and get the new value
    dc_ramp.update();
    ramp_speed = dc_ramp.getValue();

    // If a change in direction was ongoing, reset the ramp
    if (dc_ramp.isFinished() && dc_current_speed==0 && dc_target_speed != 0){
        dc_ramp.go(dc_target_speed, DC_RAMP_DURATION);
        dc_current_rotation_way = dc_target_rotation_way;
    }
    // Map the speed on 0-255 backward because of hardware implementation
    mapped_speed = map(ramp_speed, 0, 100, 255, 0);
    if (dc_current_rotation_way == FWD) {
        digitalWrite(DC_PIN_BW, HIGH);
        analogWrite(DC_PIN_FW, mapped_speed);
    }
    else if (dc_current_rotation_way == BWD){
        digitalWrite(DC_PIN_FW, HIGH);
        analogWrite(DC_PIN_BW, mapped_speed);
    }
    else {
        error = true;
    }
    dc_current_speed = ramp_speed;
}