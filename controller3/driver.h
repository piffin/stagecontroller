#include <Arduino.h>

class driver : public baseobj {
	private:
		unsigned long	posit;
		unsigned long	target;

		unsigned int	spd;

		int		p_dir;
		int		p_step;
		int		p_max;
		int		p_min;

		bool		direction;
    
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
		}
    
		void message(unsigned int length, unsigned int array[], bool types[]) {
  #ifdef DEBUG
  Serial.println(length);
  for(int i = 0; i < length; i++) {
  Serial.println(array[i], types[i]);
  Serial.println(types[i]);
  }
  #endif
			switch(length) {
				case 1:
					return;
				break;
				case 2:
                                        if(types[1] == 0 && array[1] == '?') {
                                                Serial.print((char)array[0]);
                                                Serial.print(":");
                                                Serial.print(posit);
                                                Serial.println(";");
                                        } else {
					        setTarget(array[1], true);
                                        }
				break;
				case 3:

				  	long temp = array[2];
                                      temp = (array[1] == '-') ? -temp:temp;
					        setTarget(temp, false);
				break;
			}
		}
    
		void timer() {
			if(digitalRead(p_step)) {
				digitalWrite(p_step, LOW);
			} else {
				step();
			}
		}
    
		void step() {
			if((digitalRead(p_max) && target > posit) || (digitalRead(p_min) && target < posit))
				target = posit;
			if (posit == target)
				return;
			if(posit > target) {
				digitalWrite(p_dir, direction);
				posit--;
			} else {
				digitalWrite(p_dir, !direction);
				posit++;
			}
			digitalWrite(p_step, HIGH);
		}
    
		boolean home() {
			digitalWrite(p_dir,direction);
			if(digitalRead(p_min)) {
				posit = 0;
				return true;
			}
			digitalWrite(p_step, !(digitalRead(p_step)));
			return false;
		}
    
		void setTarget(long value, bool absolute) {
			if(!absolute)
				target = posit + value;
			else
				if(value >= 0)
					target = value;     
		}
    
		unsigned long getPos() {
			return posit; 
		}
    
		void setSpeed(unsigned int speed) {
			spd = speed;
		}
};
