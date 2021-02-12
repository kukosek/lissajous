// Don't make it 0 or less :)
#include <bits/stdint-uintn.h>
#define FRAME_VALUES 60
class FpsCounter {
	public:
		// the value you want
		FpsCounter(uint32_t ticks);
		void update(uint32_t ticks);
		float fps;
	private:
		// An array to store frame times:
		uint32_t frametimes[FRAME_VALUES];

		// Last calculated SDL_GetTicks
		uint32_t frametimelast;

		// total frames rendered
		uint32_t framecount;

};
