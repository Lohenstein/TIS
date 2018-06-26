
#include "Main.h"

// -----計算に必要な変数類---------------------------------------------
double	camera_time_x, camera_time_y;
bool	camera_flag_x, camera_flag_y;
bool	camera_flag_half_x, camera_flag_half_y;

/*------------------------------------------------------------------------------*
| <<< カメラクラス Camera >>>
*------------------------------------------------------------------------------*/
void	Camera::update() {

	// -----カメライージング横軸-------------------------------------------
	if (tplayer.p_x == px) {
		camera_time_x = 0.0;
		camera_flag_x = false;
		camera_flag_half_x = false;
	}
	else if (camera_flag_x == false) {
		camera_flag_x = true;
	}
	else if (camera_flag_x) {
		if (camera_time_x >= 0.5) {
			camera_flag_half_x = true;
		}
		if (camera_flag_half_x) {
			if (tplayer.p_x == tplayer.o_x) {
				camera_time_x += 0.01;
				if (camera_time_x >= 1.0) {
					camera_flag_x = false;
					camera_flag_half_x = false;
					px = tplayer.p_x;
				}
			}
			else {
				camera_time_x = 0.5;
			}
		}
		else {
			camera_time_x += 0.01;
		}
	}

	// -----カメライージング縦軸-------------------------------------------
	if (tplayer.p_y == py) {
		camera_time_y = 0.0;
		camera_flag_y = false;
		camera_flag_half_y = false;
	}
	else if (camera_flag_y == false) {
		camera_flag_y = true;
	}
	else if (camera_flag_y) {
		if (camera_time_y >= 0.5) {
			camera_flag_half_y = true;
		}
		if (camera_flag_half_y) {
			if (tplayer.p_y == tplayer.o_y) {
				camera_time_y += 0.01;
				if (camera_time_y >= 1.0) {
					camera_flag_y = false;
					camera_flag_half_y = false;
					py = tplayer.p_y;
				}
			}
			else {
				camera_time_y = 0.5;
			}
		}
		else {
			camera_time_y += 0.01;
		}
	}
	// ----イージング-------------------------------------------
	px = InOutQuad(camera_time_x, 1.0, (double)tplayer.p_x, (double)px);
	py = InOutQuad(camera_time_y, 1.0, (double)tplayer.p_y, (double)py);

	camera_px = px - WINDOW_SIZE_X / 2.f;
	camera_py = py - WINDOW_SIZE_Y / 2.f;
}