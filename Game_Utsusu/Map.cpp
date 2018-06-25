
#include "Main.h"

using namespace std;

int		bsize = 32;				// ブロックのサイズ
float	camera_px, camera_py;	// カメラの座標
double	camera_time_x, camera_time_y;
bool	camera_flag_x, camera_flag_y;
bool	camera_flag_half_x, camera_flag_half_y;

vector<string> split(string& input, char delimiter)
{
	istringstream stream(input);
	string field;
	vector<string> result;
	while (getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}

void	Stage::load(char name[]) {

	ifstream ifs; ifs.open(name);
	string line;

	int count = 0;
	while (getline(ifs, line)) {
		vector<string> str = split(line, ',');
		if (count == 0) {
			size.x = stoi(str.at(0));
			size.y = stoi(str.at(1));
		}
		else {
			for (int i = 0; i < str.size(); i++) {
				map[i][count - 1] = stoi(str.at(i));
			}
		}
		count++;
	}
}

void	Stage::draw() {

	// -----カメライージング横軸-------------------------------------------
	if (tplayer.p_x == camera_px) {
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
					camera_px = tplayer.p_x;
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
	if (tplayer.p_y == camera_py) {
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
					camera_py = tplayer.p_y;
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

	camera_px = InOutQuad(camera_time_x, 1.0, (double)tplayer.p_x, (double)camera_px);
	camera_py = InOutQuad(camera_time_y, 1.0, (double)tplayer.p_y, (double)camera_py);

	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {

			float dpx = i * bsize - camera_px + WINDOW_SIZE_X / 2.f;
			float dpy = j * bsize - camera_py + WINDOW_SIZE_Y / 2.f;

			if (map[i][j] == 1) {
				DrawBox(dpx, dpy, dpx + bsize, dpy + bsize, 0x555555, true);
			}
		}
	}
}