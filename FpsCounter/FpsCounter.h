// Don't make it 0 or less :)
#define FRAME_VALUES 60
class FpsCounter {
	public:
		// the value you want
		FpsCounter(unsigned int ticks);
		void update(unsigned int ticks);
		float fps;
	private:
		// An array to store frame times:
		unsigned int frametimes[FRAME_VALUES];

		// Last calculated SDL_GetTicks
		unsigned int frametimelast;

		// total frames rendered
		unsigned int framecount;

};
