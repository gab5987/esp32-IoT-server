#ifndef _BUZZER_
#define _BUZZER_

void runBuzzer(int time = 1000000);
void _SECTION_ATTR_IMPL(".iram1", __COUNTER__) BuzzerOff();
void _SECTION_ATTR_IMPL(".iram1", __COUNTER__) BuzzerOn();

#endif