#include "pins.h"
#include "message.h"
#include "driver.h"
#include "laser.h"

int incomingByte = 0;   // for incoming serial data
message msg;

driver x(x_dir, x_step, x_min, x_max, true);
driver y(y_dir, y_step, y_min, y_max, true);
driver z(z_dir, z_step, z_min, z_max, true);
laser  l(laser_pin);

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
          
        while(!x.home() || !y.home() || !z.home()) {
          delayMicroseconds(step_delay);
        };
}

void loop() {
        if (Serial.available() > 0) {
                if(msg.addChar(Serial.read())) {
                  switch(msg.getMode()) {
                    case 0:
                      switch(msg.getAxis()) {
                        case 0:
                          x.setTarget(msg.getAmount(), msg.getAbs());
                        break;
                        case 1:
                          y.setTarget(msg.getAmount(), msg.getAbs());
                        break;
                        case 2:
                          z.setTarget(msg.getAmount(), msg.getAbs());
                        break;                  
                      }
                      break;
                    case 1:
                      switch(msg.getAxis()) {
                        case 0:
                          Serial.print("x:");
                          Serial.println(x.getPos());
                        break;
                        case 1:
                          Serial.print("y:");
                          Serial.println(y.getPos());
                        break;
                        case 2:
                          Serial.print("z:");
                          Serial.println(z.getPos());
                        break;                  
                      }
                      break;
                    case 2:
                      switch(msg.getAxis()) {
                        case 0:
                          x.setSpeed(msg.getAmount());
                        break;
                        case 1:
                          y.setSpeed(msg.getAmount());
                        break;
                        case 2:
                          z.setSpeed(msg.getAmount());
                        break;                  
                      }
                      break; 
                     case 3:
                        l.set(msg.getAmount());
                     break;                     
                }
                }
        }
        x.step();
        y.step();
        z.step();
        delayMicroseconds(step_delay);
        x.complete();
        y.complete();
        z.complete();
        delayMicroseconds(step_delay);
}

