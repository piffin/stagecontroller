class message
{
	private:
		unsigned char	data[20];
		unsigned int	arguments[10];
		unsigned int	length, param;

		void addParam(unsigned int start, unsigned int finish) {
                        bool num = false;
                        long total = 0;
                        for(int i = start; i <= finish; i++) {
			        if(data[i] < 48 || data[i] > 57) {
                                        if(num) {
                                          arguments[param++] = total;
                                          num = false;
                                        }
                                        arguments[param++] = data[i];
			        } else {
                                        num = true;
			        	total = (total * 10) + (data[i] - 48);
			        }
			}
                        if(num) {
                          arguments[param++] = total;
                          num = false;
                        }
		}

	public:
		message() {
			length = 0;
		}

		bool addChar(unsigned char chr) {
			data[length++] = chr;

			if (chr == ';') {
				param = 0;
				unsigned int last = 0;
				for(unsigned int i = 0; i < length; i++) {
					if(data[i] == ':') {
						addParam(last, i-1);
						last = i + 1;
					}
				}
                                addParam(last,length-2);
				length = 0;
				return true;
			}
			return false;
		}

		unsigned int getTarget() {
			return arguments[0];
		}

		unsigned int& getMessage() {
			return arguments[1];
		}

		unsigned int getMessageLen() {
			return param - 1;
		}
};
