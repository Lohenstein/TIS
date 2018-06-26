#pragma once


typedef struct {
	int x;
	int y;
}MAP_DATA;

class Stage {
public:
	MAP_DATA size;
	int		map[100][100];

	void	load(char name[]);
	void	draw();

};
extern int		bsize;
extern float	camera_px, camera_py;	// ƒJƒƒ‰‚ÌÀ•W