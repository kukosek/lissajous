#include "ControlCircle.h"
#include "Circle/Circle.h"
#include <cstdint>
void ControlCircle::draw(uint32_t delta) {
	if (visible) circle(s, x, y, r, false, 1);

	x_result = x+sin(a)*r;
	y_result = y+cos(a)*r;

	if (visible) circle(s, x_result, y_result, 5, true, 1);

	a = a + speed * delta;
	if (a >= 2*M_PI+phase_diff) {
		a = phase_diff;
		event_new_cycle = true;
	}

}
