#include <SDL2/SDL.h>
#include "ControlCircle/ControlCircle.h"
#include <vector>
class TableManager {
	public:
		TableManager(SDL_Renderer *s);
		void add_circle_x(float speed, float phase_diff);
		void add_circle_y(float speed, float phase_diff);
		void draw(uint32_t delta, uint32_t windowWidth, uint32_t windowHeight, bool windowResized);
		bool showLines = true;
		bool showControlCircles = true;
	private:
		SDL_Renderer *s;
		std::vector<ControlCircle> x_circles;
		std::vector<ControlCircle> y_circles;
		bool recalculatePositions = true;
		void fillPointsPlotted();
		std::vector<std::vector<PointsStore>> pointsPlotted =
			std::vector<std::vector<PointsStore>>();
};
