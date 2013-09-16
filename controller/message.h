class message
{
    private:
          unsigned char data[20];
          int length;
          bool complete;
          
          unsigned int axis = 8;
          unsigned int mode;
          bool absolute;
          long amount;
          
          void setAxis(unsigned int pos) {
            axis = data[pos] - 120; 
          }
          
          void setAmount(int s, int e) {
            bool neg = false;
            absolute = true;
            switch(data[s]) {
              case '-':
                neg = true;
              case '+':
                absolute = false;
                s++;
                break;
              case '=':
                s++;
                break;
            }
                        
             long total = 0;
             for(int i = s; i < e; i++) {
               total = (total * 10) + (data[i] - 48);
             }
               amount = (neg) ? -total : total;
          }

    public:
          message() {
            length = 0;
          };
          bool addChar(unsigned char chr) {
            data[length] = chr;
            length++;
            if (chr == 59) {
              for(int i = 0; i < length; i++) {
                if(data[i] == 58) {
                  if(data[i-1] == 108) {
                    mode = 3;
                    amount = (data[i+1] - 48);
                  } else {
                    setAxis(i - 1);
                    if(data[i+1] == 63) {
                      mode = 1;
                    } else if(data[i+1] == 115){
                      mode = 2;
                      setAmount(i + 2, length - 1);
                    } else {
                      mode = 0;
                      setAmount(i + 1, length - 1);
                    }
                  }
                }
              }
              length = 0;
              return true;
            }
            return false;
          };
          unsigned int getAxis() { return axis; }
          bool getAbs() {return absolute; }
          unsigned int getMode() {return mode; }
          long getAmount() {return amount; }
};
