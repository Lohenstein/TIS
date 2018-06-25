
#include "Main.h"

/*------------------------------------------------------------------------------*
| <<< �G���e�B�e�B�e�N���X Entity >>>
*------------------------------------------------------------------------------*/
// �G���e�B�e�B�Ƃ̓����蔻��
void	Entity::collision() {

	COL_RECT e = { (int)y - (int)h / 2, (int)y + (int)h / 2, (int)x - (int)w / 2, (int)x + (int)w / 2 };
	COL_RECT player = { tplayer.p_y - tplayer.p_h / 2, tplayer.p_y + tplayer.p_h / 2, tplayer.p_x - tplayer.p_w / 2, tplayer.p_x + tplayer.p_w / 2 };

	// �����蔻��
	float rad = col_CheckRadian(tplayer.p_w, tplayer.p_h, w, h) - PI;

	int dir = col_HitRadian(tplayer.p_x, tplayer.p_y, x, y, rad);
	int o_dir = col_HitRadian(tplayer.o_x, tplayer.o_y, x, y, rad);

	if (col_RectAndRect(player, e)) {
		switch (dir) {
		case 1: // right
			switch (o_dir) {
			case 4:
				tplayer.p_y = y - (h / 2) - (tplayer.p_h / 2) - 1;
				tplayer.jump_p = 0.f;
				break;
			case 2:
				tplayer.p_y = y + (h / 2) + (tplayer.p_h / 2) + 1;
				tplayer.jump_p = 0.f;
				break;
			default:
				tplayer.p_x = x + (w / 2) + (tplayer.p_w / 2) + 1;
				break;
			}
			break;
		case 2: // bottom
			switch (o_dir) {
			case 1:
				tplayer.p_x = x + (w / 2) + (tplayer.p_w / 2) + 1;
				break;
			case 3:
				tplayer.p_x = x - (w / 2) - (tplayer.p_w / 2) - 1;
				break;
			default:
				tplayer.p_y = y + (h / 2) + (tplayer.p_h / 2) + 1;
				tplayer.jump_p = 0.f;
				break;
			}
			break;
		case 3: // left
			switch (o_dir) {
			case 4:
				tplayer.p_y = y - (h / 2) - (tplayer.p_h / 2) - 1;
				tplayer.jump_p = 0.f;
				break;
			case 2:
				tplayer.p_y = y + (h / 2) + (tplayer.p_h / 2) + 1;
				tplayer.jump_p = 0.f;
				break;
			default:
				tplayer.p_x = x - (w / 2) - (tplayer.p_w / 2) - 1;
				break;
			}
			break;
		case 4: // top
			switch (o_dir) {
			case 1:
				tplayer.p_x = x + (w / 2) + (tplayer.p_w / 2) + 1;
				break;
			case 3:
				tplayer.p_x = x - (w / 2) - (tplayer.p_w / 2) - 1;
				break;
			default:
				tplayer.p_y = y - (h / 2) - (tplayer.p_h / 2) - 1;
				tplayer.jump_p = 0.f;
				break;
			}
			break;
		default:
			break;
		}
	}
}
/*------------------------------------------------------------------------------*
| <<< ������ MoveFloor >>>
*------------------------------------------------------------------------------*/
// �`��
void	MoveFloor::draw() {

	float dx, dy;
	dx = x - camera_px + WINDOW_SIZE_X / 2.f;
	dy = y - camera_py + WINDOW_SIZE_Y / 2.f;
	DrawBox(dx - w / 2, dy - h / 2, dx + w / 2, dy + h / 2, 0x0000FF, true);
}
// �X�V
void	MoveFloor::update(float s, int p1, int p2) {

	// �ړ�����p�x�Ƌ��������߂�
	float rad = atan2f(sy[p2] - sy[p1], sx[p2] - sx[p1]);
	float dis = sqrtf((sx[p2] - sx[p1]) * (sx[p2] - sx[p1]) + (sy[p2] - sy[p1]) * (sy[p2] - sy[p1]));

	// �ߋ��̈ړ���ۑ�
	ox = x;
	oy = y;

	// �ړ�����
	x = sx[p1] + (sinf(rad + PI) * p);
	y = sy[p1] + (cosf(rad + PI) * p);

	// �ړ��̕����Ɍ������ē�����
	if (flag)
		p += s;
	else
		p -= s;

	// �ړ��̕����̐؂�ւ�
	if (p >= dis || p <= 0.f) {
		if (flag)
			flag = false;
		else
			flag = true;
	}
	collision();	// �����蔻��
	onfloor();
}
// ���ɏ������x�N�g�����L
void	MoveFloor::onfloor() {

	COL_RECT player = { tplayer.p_y - tplayer.p_h / 2, tplayer.p_y + tplayer.p_h / 2, tplayer.p_x - tplayer.p_w / 2, tplayer.p_x + tplayer.p_w / 2 };
	COL_RECT e = { (int)y - (int)h / 2 - 2, (int)y + (int)h / 2, ((int)x - (int)w / 2) + 5, ((int)x + (int)w / 2) - 5 };

	// �x�N�g�������L
	if (col_RectAndRect(player, e)) {
		tplayer.p_x += (x - ox);
		tplayer.jump_p = -4.f;
	}
}
// �ړ��_��ݒ�
void	MoveFloor::set_point(int num, float px, float py) {

	sx[num] = px;
	sy[num] = py;
}
/*------------------------------------------------------------------------------*
| <<< ������痎���鏰 DropFloor >>>
*------------------------------------------------------------------------------*/
void	DropFloor::draw() {
	float dx, dy;
	dx = x - camera_px + WINDOW_SIZE_X / 2.f;
	dy = y - camera_py + WINDOW_SIZE_Y / 2.f;
	DrawBox(dx - w / 2, dy - h / 2, dx + w / 2, dy + h / 2, 0x00FF00, true);
}

void	DropFloor::update() {
	COL_RECT player = { tplayer.p_y - tplayer.p_h / 2, tplayer.p_y + tplayer.p_h / 2, tplayer.p_x - tplayer.p_w / 2, tplayer.p_x + tplayer.p_w / 2 };
	COL_RECT e = { (int)y - (int)h / 2 - 2, (int)y + (int)h / 2, (int)x - (int)w / 2, (int)x + (int)w / 2 };

	// ���ɏ������t���OON
	if (col_RectAndRect(player, e)) {
		flag = true;
	}
	// ��������
	if (flag) {
		time++;
		// ���ɏ����0.5�b�o������(60fps)
		const int fps = 60;
		if (time > fps / 2) {
			y -= drop_p;
			drop_p -= gravity;
			const int prev_time = 5;
			if (time > fps * prev_time) {
				drop_p = 0.f;
				flag = false;
				time = 0;
				y = sy;
			}
		}
	}
	collision();
}

void	DropFloor::set_point(float px, float py) {
	sx = px;
	sy = py;
	x = sx;
	y = sy;
}