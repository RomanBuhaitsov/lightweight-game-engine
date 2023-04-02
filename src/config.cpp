#include <stdlib.h>

int atoi_default(const char* s, int default_value) {
	if (s == NULL) {
		return default_value;
	}
	return atoi(s);
}

const int FRAMERATE = atoi_default(getenv("FRAMERATE"), 60);
const int MAX_FRAMESKIP = atoi_default(getenv("MAX_FRAMESKIP"), 10);
