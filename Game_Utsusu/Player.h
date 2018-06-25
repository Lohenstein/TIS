#pragma once

class Player {
public:
	float	p_x, p_y;		// 位置
	float	o_x, o_y;		// 過去の位置
	int		p_h, p_w;		// 大きさ
	float	p_s;			// 移動速度
	float	jump_p;			// ジャンプ力
	float	gravity;		// 重力
	float	inertia_deg;	// 慣性移動の角度θ

	float pdpx, pdpy;

	// テスト用コンストラクタ
	Player() {
		p_x = 400.f;
		p_y = 100.f;
		p_h = 120.f;
		p_w = 90;
		p_s = 6.f;
		gravity = 1.f;
		inertia_deg = 0;
		pdpx = WINDOW_SIZE_X / 2;
		pdpy = WINDOW_SIZE_Y / 2;
	}
	Player(float x, float y, int h, int w, float s) {
		p_x = x;
		p_y = y;
		p_h = h;
		p_w = w;
		p_s = s;
	}

	void	update();
	void	move();
	void	draw();
	int		hit_radian(float x1, float y1, float x2, float y2);
	COL_HIT	collision();
};

extern Player tplayer;