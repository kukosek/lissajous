#include <SDL2/SDL.h>
#include "Circle.h"
void circleDrawOctants(SDL_Renderer *s, int center_x, int center_y, int x_point, int y_point, bool fill) {
	SDL_SetRenderDrawColor(s, 0xFF, 0xFF, 0xFF, 0xFF);

	if (fill) {
		SDL_RenderDrawLine(s,
				center_x - x_point, center_y + y_point,
				center_x + x_point, center_y + y_point
				);
		SDL_RenderDrawLine(s,
				center_x - x_point, center_y - y_point,
				center_x + x_point, center_y - y_point
				);
		SDL_RenderDrawLine(s,
				center_x + y_point, center_y + x_point,
				center_x - y_point, center_y + x_point
				);
		SDL_RenderDrawLine(s,
				center_x + y_point, center_y - x_point,
				center_x - y_point, center_y - x_point
				);
	}else {
		SDL_RenderDrawPoint(s, center_x + x_point, center_y + y_point);
		SDL_RenderDrawPoint(s, center_x + x_point, center_y - y_point);
		SDL_RenderDrawPoint(s, center_x - x_point, center_y + y_point);
		SDL_RenderDrawPoint(s, center_x - x_point, center_y - y_point);

		SDL_RenderDrawPoint(s, center_x + y_point, center_y + x_point);
		SDL_RenderDrawPoint(s, center_x + y_point, center_y - x_point);
		SDL_RenderDrawPoint(s, center_x - y_point, center_y + x_point);
		SDL_RenderDrawPoint(s, center_x - y_point, center_y - x_point);

	}
	SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);

}

// midpoint algo. faster
void circle(SDL_Renderer *s, int center_x, int center_y, int r, bool fill, int thickness) {
	for (int radius=r; radius>r-thickness; radius--) {
		int x = 0;
		int y = radius;
		int P = 1 - radius;
		while (y >= x) {
			if (y==radius) {
				circleDrawOctants(s, center_x, center_y, x, y, fill);
			}

			//calculate next x and y
			float midpoint_x = x - 0.5;
			if (P < 0) {
				P = P + 2*x + 3;
			}else{
				P = P + 2*(x-y) + 5;
				y--;
			}
			x++;

			//render the points to all octants
			circleDrawOctants(s, center_x, center_y, x, y, fill);
		}
	}
}
