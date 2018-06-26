
#include "Main.h"

using namespace std;

int		bsize = 32;				// ブロックのサイズ

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

	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {

			float dpx = i * bsize - Cam.get_x();
			float dpy = j * bsize - Cam.get_y();

			if (map[i][j] == 1) {
				DrawBox(dpx, dpy, dpx + bsize, dpy + bsize, 0x555555, true);
			}
		}
	}
}