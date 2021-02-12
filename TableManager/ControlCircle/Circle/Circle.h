#include <SDL2/SDL.h>
void circleDrawOctants(SDL_Renderer *s,
		int center_x, int center_y, int x_point, int y_point, bool fill);

void circle(SDL_Renderer *s,
		int center_x, int center_y, int r, bool fill, int thickness);
