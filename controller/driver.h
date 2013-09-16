#include <Arduino.h>

class driver {
  private:
    unsigned long posit;
    unsigned long target;
    
    unsigned int spd;
    
    int p_dir;
    int p_step;
    int p_max;
    int p_min;
    
    bool direction;
    
  public:
    driver(int dir, int step, int min, int max, bool invert) {
      p_dir = dir;
      p_max = max;
      p_min = min;
      p_step = step;
      direction = invert;
 
      pinMode(dir, OUTPUT);
      pinMode(step, OUTPUT);
      pinMode(min, INPUT);
      pinMode(min, INPUT);      
    };
    
    void step() {
      if((digitalRead(p_max) && target > posit) || (digitalRead(p_min) && target < posit))
        target = posit;
      if (posit == target)
        return;
      if(posit > target) {
        digitalWrite(p_dir, direction);
        posit--;
      } else {
        posit++;
        digitalWrite(p_dir, !direction);
      }
        
      digitalWrite(p_step, HIGH);
    };
    
    void complete() {
      digitalWrite(p_step, LOW); 
    }
    
    boolean home() {
      digitalWrite(p_dir,direction);
      if(digitalRead(p_min)) {
        posit = 0;
        return true;
      }
      digitalWrite(p_step, !(digitalRead(p_step)));
      return false;
    };
    
    void setTarget(long value, bool absolute) {
      if(!absolute)
        target = posit + value;
      else
        if(value >= 0)
          target = value;     
    };
    
    unsigned long getPos() {
     return posit; 
    }
    
    void setSpeed(unsigned int speed) {
      spd = speed;
    }
    
};
