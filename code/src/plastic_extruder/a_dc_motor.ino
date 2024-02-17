/**
 * @file a_dc_motor.ino
 * @author CAMUS Armand
 * @date 04/02/2024
 * @brief Main of the project
*/

/*******************************************************************************
 * Global variables of module
********************************************************************************/

dc_rotation_way dc_current_rotation_way;
uint8_t dc_speed;

/*******************************************************************************
 * Functions of module
********************************************************************************/
/**
 * Initialyse DC motor pins and way of rotation
*/
void dc_init(void){
    pinMode(DC_PIN_FW, OUTPUT);
    pinMode(DC_PIN_BW, OUTPUT);
    dc_current_rotation_way = FORWARD;
    dc_speed = 0;
}

/**
 * Set the speed of the motor
 * @param speed the wanted speed in %
 * @return A bool equal to 0 if no error and 1 if an error occured, either speed to high or
 * ratation way not known
*/
bool dc_set_speed(uint8_t speed){
    bool error = false;
    uint8_t mapped_speed;

    if (speed > 100){
        speed = 0;
        error = true;
    }
    // Map the speed on 255 backward because of hardware implementation
    mapped_speed = map(speed, 0, 100, 255, 0);
    if (dc_current_rotation_way == FORWARD) {
        digitalWrite(DC_PIN_BW, HIGH);
        analogWrite(DC_PIN_FW, mapped_speed);
    }
    else if (dc_current_rotation_way == BACKWARD){
        digitalWrite(DC_PIN_FW, HIGH);
        analogWrite(DC_PIN_BW, mapped_speed);
    }
    else {
        error = true;
    }
    dc_speed = speed;

    return error;
}

/**
 * Set the rotation way
 * @param rotation_way the wanted rotation way
*/
void dc_set_rotation_way(dc_rotation_way rotation_way){
    dc_current_rotation_way = rotation_way;
    dc_set_speed(dc_speed);

}

