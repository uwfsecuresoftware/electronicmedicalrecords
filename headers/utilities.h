#ifndef UTILITY_H
#define UTILITY_H

class Utility {
	public:
		static void zeroArray(int target[]);
		static void zeroArray(char *& target);
		static void zeroArray(float *& target, float * src);
};

#endif