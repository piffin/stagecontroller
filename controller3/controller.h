#include "Arduino.h"
#define MAX_OBJS 20

class controller {
	private:
		baseobj*	objects[MAX_OBJS];
		unsigned int	refrence[MAX_OBJS];
		bool		timeenable[MAX_OBJS];
		unsigned long	timestep[MAX_OBJS];
		unsigned long	timerun[MAX_OBJS];
		unsigned long	lasttime;
		unsigned int	count;

	public:
		controller(){
			//lasttime = millis();
			count = 0;
			for(int i =0; i < MAX_OBJS; i++) {timeenable[i] = false;}
		}

		unsigned int addObject(baseobj &instance) {
			objects[count] = &instance;
			return count++;
		}

		void addTrigger(unsigned int index, unsigned int ref) {
			if(index < count)
				refrence[index] = ref;
		}

		void addTimer(unsigned int index, unsigned int delay) {
			if(index < count) {
				timestep[index] = delay;
                                timeenable[index] = true;
                                timerun[index] = micros();
                        }
		}

		void fireTrigger(unsigned int ref, unsigned int length, unsigned int &array, bool &types) {
			for(int i = 0; i < count; i++) {
				if(refrence[i] == ref)
					objects[i]->message(length, &array, &types);
			}
		}

                void fireTimer() {
			for(int i = 0; i < count; i++) {
				if(timeenable[i]){
					if(micros() > timerun[i] + timestep[i]) {
						objects[i]->timer();
						timerun[i] = micros();
					}
				}
			} 
		}
};

