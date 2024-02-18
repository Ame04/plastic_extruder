/**
 * @file z_main.ino
 * @brief Main of the project
 * @author CAMUS Armand
 * @date 04/02/2024
 * @version A1
*/

void setup(void) {
    stepper_init();
    stepper_set_target_speed(20);

    dc_init();
    dc_set_target_speed(20);

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("LCD initialysed");
    lcd.setCursor(0,1);
    lcd.print("PaP Speed = 50");

    Serial.begin(SERIAL_BAUDRATE);
    Serial.println(F("System initialised, speed = 40"));
}

void loop(void){
    static bool speed = true;
    static unsigned long previous_time = millis();
    unsigned long time = millis();

    if (time - previous_time > 5000){
        Serial.print(F("Time = "));
        Serial.print(time);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Time = ");
        lcd.setCursor(7, 0);
        lcd.print(time);
        if (speed){
            speed = false;
            stepper_set_target_rotation_way(BWD);
            stepper_set_target_speed(20);
            dc_set_target_rotation_way(BWD);
            dc_set_target_speed(20);
            Serial.println(F("Speed changed to = 20"));
            lcd.setCursor(0,1);
            lcd.print("PaP Speed = 20");

        }
        else {
            speed = true;
            stepper_set_target_speed(50);
            stepper_set_target_rotation_way(FWD);
            dc_set_target_speed(50);
            dc_set_target_rotation_way(FWD);
            Serial.println(F(" Speed changed to = 50"));
            lcd.setCursor(0,1);
            lcd.print("PaP Speed = 50");
        }
        previous_time = time;
    }
    // To update the actual speed as often as possible.
    dc_update_current_speed();
    stepper_update_current_speed();
}