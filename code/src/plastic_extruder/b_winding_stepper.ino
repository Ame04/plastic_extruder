/**
 * @file b_winding_stepper.ino
 * @brief Functions to handle the winding stepper motor of the project
 * @author CAMUS Armand
 * @date 17/02/2024
 * @version A1
*/

/*******************************************************************************
 * Global variables of module
********************************************************************************/

rotation_way stepper_current_rotation_way;
rotation_way stepper_target_rotation_way;
uint8_t stepper_current_speed;
uint8_t stepper_target_speed;

/*******************************************************************************
 * Functions of module
********************************************************************************/
/**
 * Initialyse stepper pins and way of rotation
*/
void stepper_init(void){
    pinMode(DC_PIN_FW, OUTPUT);
    pinMode(DC_PIN_BW, OUTPUT);
    stepper_current_rotation_way = FWD;
    stepper_target_rotation_way = FWD;
    stepper_current_speed = 0;
    stepper_target_speed = 0;
}

/**
 * Set the speed of the stepper
 * @param speed the wanted speed in %
 * @return A bool equal to 0 if no error and 1 if an error occured (speed too high)
*/
bool stepper_set_target_speed(uint8_t speed){
    bool error = false;
    uint8_t direction = 1;

    if (speed > 100){
        speed = 0;
        error = true;
    }
    stepper_target_speed = speed;
    // Set the ramp for smooth transitions only if no change in direction is ongoing
    if (stepper_target_rotation_way == BWD){
        direction = -1;
    }

    stepper_ramp.go(direction * speed, STEPPER_RAMP_DURATION);

    return error;
}

/**
 * Set the stepper rotation way
 * @param rotation_way the wanted rotation way
*/
void stepper_set_target_rotation_way(rotation_way rotation_way){
    uint8_t direction = 1;
    if (rotation_way != stepper_current_rotation_way){
        if (rotation_way == BWD){
            direction = -1;
        }
        stepper_ramp.go(direction * stepper_target_speed, STEPPER_RAMP_DURATION);
    }
    stepper_target_rotation_way = rotation_way;
}

/**
 * Update the actual speed of the stepper until the target way and speed is achieved
*/
void stepper_update_current_speed(void){
    bool error = false;
    uint8_t mapped_speed;
    uint8_t ramp_speed;

    // Update the ramp and get the new value
    stepper_ramp.update();
    ramp_speed = stepper_ramp.getValue();

    // Map the speed on 0-255 backward because of hardware implementation
    mapped_speed = map(ramp_speed, -100, 100, -STEPPER_MAX_SPEED, STEPPER_MAX_SPEED);
    stepper_current_speed = ramp_speed;
    winding_stepper.spin(mapped_speed);
}