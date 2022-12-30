#include "main.hpp"

// Here we define the buzzer pin and the timer
u_int8_t BUZZER_PIN = 4;
hw_timer_t *Buzzer_timer = NULL;

// Functions to turn the buzzer on and off
void _SECTION_ATTR_IMPL(".iram1", __COUNTER__) BuzzerOff() { ledcWrite(0, 0); timerEnd(Buzzer_timer);}
void _SECTION_ATTR_IMPL(".iram1", __COUNTER__) BuzzerOn() { ledcWriteNote(0, NOTE_G, 7); }

// This sets up the timer as a interrupt, it receives the time in microseconds and the function to be called when the timer ends
void buzzerTimerSetup(int time, void(*method)()) {
    Buzzer_timer = timerBegin(0, 80, true);            // timer 0, div 80
    timerAttachInterrupt(Buzzer_timer, method, true);  // attach callback
    timerAlarmWrite(Buzzer_timer, time, true);         // set time in us
    timerAlarmEnable(Buzzer_timer);                    // enable interrupt
}

void runBuzzer(int time) {
    ledcAttachPin(BUZZER_PIN, 0);       // attach the buzzer to the timer
    BuzzerOn();                         // turn the buzzer on
    buzzerTimerSetup(time, BuzzerOff);  // set the timer to turn the buzzer off
}
