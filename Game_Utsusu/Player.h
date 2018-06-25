#pragma once

class Player {
public:
	float	p_x, p_y;		// �ʒu
	float	o_x, o_y;		// �ߋ��̈ʒu
	int		p_h, p_w;		// �傫��
	float	p_s;			// �ړ����x
	float	jump_p;			// �W�����v��
	float	gravity;		// �d��
	float	inertia_deg;	// �����ړ��̊p�x��

	float pdpx, pdpy;

	// �e�X�g�p�R���X�g���N�^
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