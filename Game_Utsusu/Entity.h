#pragma once


class Entity {
public:
	float	x, y;
	float	h, w;

	void	collision();
};

class MoveFloor : public Entity {
public:
	// 変数
	int		now_point;
	bool	flag;
	float	ox, oy, p;
	float	sx[10], sy[10];

	// コンストラクタ
	MoveFloor() {
		flag = true;
		h = 30.f;
		w = 160.f;
		p = 0.f;
		now_point = 0;
	}
	MoveFloor(float hh, float ww) {
		flag = true;
		h = hh, w = ww;
		p = 0.f;
		now_point = 0;
	}
	// 関数
	void	draw();
	void	onfloor();
	void	update(float s, int p1, int p2);
	void	set_point(int num, float px, float py);
};

class DropFloor : public Entity {
public:
	int		time;
	bool	flag;
	float	sx, sy;
	float	gravity = 1.f;
	float	drop_p  = 0.f;

	DropFloor() {
		flag = false;
		h = 30.f;
		w = 160.f;
		time = 0;
	}

	void	draw();
	void	update();
	void	set_point(float px, float py);
};

extern MoveFloor entity[ENTITY_MAX];
extern DropFloor df[ENTITY_MAX];