/**
 * @file z_main.ino
 * @author CAMUS Armand
 * @date 04/02/2024
 * @brief Main of the project
*/

void setup(void) {
    winding_stepper.begin(STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);
    winding_stepper.spin(50);

    dc_init();
    dc_set_speed(20);

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("LCD initialysed");
    lcd.setCursor(0,1);
    lcd.print("PaP Speed = 50");

    Serial.begin(9600);
    Serial.println(F("System initialised, speed = 40"));
}

void loop(void){
    static bool speed = true;
    static unsigned long previous_time = millis();
    unsigned long time = millis();

    if (time - previous_time > 5000){
        Serial.print(F("Time = "));
        Serial.print(time);
        lcd.setCursor(0, 0);
        lcd.print("Time = ");
        lcd.setCursor(7, 0);
        lcd.print(time);
        if (speed){
            speed = false;
            winding_stepper.spin(20);
            dc_set_speed(20);
            Serial.println(F("Speed changed to = 20"));
            lcd.setCursor(0,1);
            lcd.print("PaP Speed = 20");

        }
        else {
            speed = true;
            winding_stepper.spin(50);
            dc_set_speed(50);
            Serial.println(F(" Speed changed to = 50"));
            lcd.setCursor(0,1);
            lcd.print("PaP Speed = 50");
        }
        previous_time = time;
    }
}