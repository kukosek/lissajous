#include <string.h>
#include "FpsCounter.h"
// This function gets called once on startup.
FpsCounter::FpsCounter(unsigned int ticks) {

        // Set all frame times to 0ms.
		memset(frametimes, 0, sizeof(frametimes));
        framecount = 0;
        fps = 0;
        frametimelast = ticks;

}

void FpsCounter::update(unsigned int ticks) {
        unsigned int frametimesindex;
        unsigned int getticks;
        unsigned int count;
        unsigned int i;

        // frametimesindex is the position in the array. It ranges from 0 to FRAME_VALUES.
        // This value rotates back to 0 after it hits FRAME_VALUES.
        frametimesindex = framecount % FRAME_VALUES;

        // store the current time
        getticks = ticks;

        // save the frame time value
        frametimes[frametimesindex] = getticks - frametimelast;

        // save the last frame time for the next fpsthink
        frametimelast = getticks;

        // increment the frame count
        framecount++;

        // Work out the current framerate

        // The code below could be moved into another function if you don't need the value every frame.

        // I've included a test to see if the whole array has been written to or not. This will stop
        // strange values on the first few (FRAME_VALUES) frames.
        if (framecount < FRAME_VALUES) {
                count = framecount;
        } else {
                count = FRAME_VALUES;
        }

        // add up all the values and divide to get the average frame time.
        fps = 0;
        for (i = 0; i < count; i++) {
                fps += frametimes[i];
        }

        fps /= count;

        // now to make it an actual frames per second value...
        fps = 1000.f / fps;

}
