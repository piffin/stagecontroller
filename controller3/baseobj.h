class baseobj {
	public:
	baseobj() {};
	virtual void timer() {};
	virtual void message(unsigned int length, unsigned int array[], bool types[]) {};
};
