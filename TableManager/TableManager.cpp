#include "TableManager.h"
#include <vector>
#include <cstdint>

PointsStore::PointsStore() {

	const int colors_r[] = {100, 224, 239, 38 , 212, 255    };
	const int colors_g[] = {181, 64 , 83 , 166, 225, 152   };
	const int colors_b[] = {246, 251, 80 , 154, 87 , 0  };
	int color_idx = rand() % sizeof(colors_r)/sizeof(colors_r[0]);

	color_r = colors_r[color_idx];
	color_g = colors_g[color_idx];
	color_b = colors_b[color_idx];
}

TableManager::TableManager(SDL_Renderer *s) {

	this->s = s;

}

void TableManager::fillPointsPlotted() {
	for (int i=0; i<pointsPlotted.size(); i++) {
		while (pointsPlotted[i].size() < x_circles.size()) {
			pointsPlotted[i].push_back(PointsStore());
		}
	}
}

void TableManager::add_circle_x(float speed, float phase_diff) {
	x_circles.push_back(ControlCircle(s, 0, 0, 5, speed, phase_diff));
	while (x_circles.size() > pointsPlotted.size()) {
		pointsPlotted.push_back(std::vector<PointsStore>());
	}
	fillPointsPlotted();
}
void TableManager::add_circle_y(float speed, float phase_diff) {
	y_circles.push_back(ControlCircle(s, 0, 0, 5, speed, phase_diff));
	while (y_circles.size() > pointsPlotted.size()) {
		pointsPlotted.push_back(std::vector<PointsStore>());
	}
	fillPointsPlotted();
}

void TableManager::draw(uint32_t delta, uint32_t windowWidth, uint32_t windowHeight, bool windowResized) {
	int margin = 100;
	int start_margin_x = 80;
	int start_margin_y = 80;
	int end_margin = 40;
	int circle_x_availlable_space = (windowWidth-start_margin_x-end_margin)/(x_circles.size()+1);
	int circle_y_available_space = (windowHeight-start_margin_y-end_margin)/(y_circles.size()+1);
	int radius;
	if (circle_x_availlable_space < circle_y_available_space) {
		radius = circle_x_availlable_space/2 - 5 ;
	}else{
		radius = circle_y_available_space/2 -5 ;
	}

	if (x_circles[0].event_new_cycle && y_circles[0].event_new_cycle) {

		for (int i=0; i<y_circles.size(); i++) {
			for (int j=0; j<x_circles.size(); j++) {
			PointsStore * points_hist = &pointsPlotted[i][j];
			points_hist->old_points = points_hist->points;
			points_hist->old_points_opacity = 255;
			points_hist->points.clear();
			x_circles[j].event_new_cycle = false;
			x_circles[i].event_new_cycle = false;
			}
		}
	}
	const int line_color = 50;
	for(int i=0; i<x_circles.size(); i++) {
		x_circles[i].x = start_margin_x + circle_x_availlable_space*1.5 + i*circle_x_availlable_space;
		x_circles[i].y = margin;
		x_circles[i].r = radius;
		x_circles[i].visible = showControlCircles;
		x_circles[i].draw(delta);

		if (showLines) {
			//draw drawing lines
			SDL_SetRenderDrawColor(s, line_color, line_color, line_color, 0xFF);
			SDL_RenderDrawLine(s, x_circles[i].x_result, 0, x_circles[i].x_result, windowHeight);
			SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
		}

	}
	for (int i=0; i<y_circles.size(); i++) {
		y_circles[i].y = start_margin_y + circle_y_available_space*1.5 + i*circle_y_available_space;
		y_circles[i].x = margin;
		y_circles[i].r = radius;
		y_circles[i].visible = showControlCircles;
		y_circles[i].draw(delta);

		if (showLines) {
			//draw drawing lines
			SDL_SetRenderDrawColor(s, line_color, line_color, line_color, 0xFF);
			SDL_RenderDrawLine(s, 0, y_circles[i].y_result, windowWidth, y_circles[i].y_result);
			SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
		}



		for (int j=0; j<x_circles.size(); j++) {

			//now draw the result points from the intersection


			SDL_Point newPoint = SDL_Point();
			newPoint.x = x_circles[j].x_result;
			newPoint.y = y_circles[i].y_result;


			PointsStore * points_hist = &pointsPlotted[i][j];

			if (windowResized) {
				points_hist->points.clear();
			}

			points_hist->points.push_back(newPoint);

			if (points_hist->old_points_opacity > 0) {
				SDL_Point* old_points_arr = &points_hist->old_points[0];

				SDL_SetRenderDrawColor(s, points_hist->color_r, points_hist->color_g, points_hist->color_b, points_hist->old_points_opacity);
				SDL_RenderDrawLines(s, old_points_arr, points_hist->old_points.size());
				SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);

				points_hist->old_points_opacity -= delta*0.2;
			}


			SDL_Point* points_arr = &points_hist->points[0];

			SDL_SetRenderDrawColor(s, points_hist->color_r, points_hist->color_g, points_hist->color_b, 0xFF);
			SDL_RenderDrawPoints(s, points_arr, points_hist->points.size());
			SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
		}

	}
}

