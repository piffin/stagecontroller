#include <Arduino.h>

class laser {
  private:
    int p_laser;
    
  public:
    laser(int pin) {
      p_laser = pin;
      pinMode(p_laser, OUTPUT);
    };
    
    void set(unsigned int value) {
      (value == 1) ? on() : off();
    };
    
    void on() {
      digitalWrite(p_laser, HIGH);
    };
    
    void off() {
      digitalWrite(p_laser, LOW);
    };
    
    void pulse(unsigned int count, unsigned long duration) {
      while(count-- > 0) {
        on();
        delay(duration);
        off();
        delay(duration);
      };
    };
    
};
