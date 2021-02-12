#include <SDL2/SDL.h>
#include <vector>
class PointsStore {
	public:
		PointsStore();
		std::vector<SDL_Point> points = std::vector<SDL_Point>();
		std::vector<SDL_Point> old_points = std::vector<SDL_Point>();
		int old_points_opacity = 0;
		int32_t insert_index = -1;
		int color_r;
		int color_g;
		int color_b;

};
class ControlCircle {
	public:
		ControlCircle(SDL_Renderer *s, int x, int y, int r, float speed, float phase_diff) {
			this->s = s;
			this->x = x;
			this->y = y;
			this->r = r;
			this->speed = speed;
			this->phase_diff = phase_diff;
			this->a = phase_diff;
		}
		SDL_Renderer *s;
		int x; //center x
		int y; //center y
		int r; //radius
		float speed;
		float phase_diff;
		void draw(uint32_t delta); //draws the next iteration

		bool visible = true;

		int x_result;
		int y_result;

		bool event_new_cycle = false; private: float a = 0; };
