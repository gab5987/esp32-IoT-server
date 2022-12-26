#include "main.hpp"

u_int8_t BUZZER_PIN = 4;
hw_timer_t *Buzzer_timer = NULL;

void _SECTION_ATTR_IMPL(".iram1", __COUNTER__) BuzzerOff() { ledcWrite(0, 0); }
void _SECTION_ATTR_IMPL(".iram1", __COUNTER__) BuzzerOn() { ledcWriteNote(0, NOTE_G, 7); }

void buzzerTimerSetup(int time, void(*method)()) {
    Buzzer_timer = timerBegin(0, 80, true);
    timerAttachInterrupt(Buzzer_timer, method, true);
    timerAlarmWrite(Buzzer_timer, time * 1000000, true);
    timerAlarmEnable(Buzzer_timer);
}

void initialBuzzer() {
    ledcAttachPin(BUZZER_PIN, 0);
    BuzzerOn();
    buzzerTimerSetup(1, BuzzerOff);
}

void errorBuzzer() {

}