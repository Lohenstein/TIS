
#include "Main.h"

/*------------------------------------------------------------------------------*
| <<< エンティティ親クラス Entity >>>
*------------------------------------------------------------------------------*/
// エンティティとの当たり判定
void	Entity::collision() {

	COL_RECT e = { (int)y - (int)h / 2, (int)y + (int)h / 2, (int)x - (int)w / 2, (int)x + (int)w / 2 };
	COL_RECT player = { tplayer.p_y - tplayer.p_h / 2, tplayer.p_y + tplayer.p_h / 2, tplayer.p_x - tplayer.p_w / 2, tplayer.p_x + tplayer.p_w / 2 };

	// 当たり判定
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
| <<< 動く床 MoveFloor >>>
*------------------------------------------------------------------------------*/
// 描画
void	MoveFloor::draw() {

	float dx, dy;
	dx = x - camera_px + WINDOW_SIZE_X / 2.f;
	dy = y - camera_py + WINDOW_SIZE_Y / 2.f;
	DrawBox(dx - w / 2, dy - h / 2, dx + w / 2, dy + h / 2, 0x0000FF, true);
}
// 更新
void	MoveFloor::update(float s, int p1, int p2) {

	// 移動する角度と距離を求める
	float rad = atan2f(sy[p2] - sy[p1], sx[p2] - sx[p1]);
	float dis = sqrtf((sx[p2] - sx[p1]) * (sx[p2] - sx[p1]) + (sy[p2] - sy[p1]) * (sy[p2] - sy[p1]));

	// 過去の移動を保存
	ox = x;
	oy = y;

	// 移動する
	x = sx[p1] + (sinf(rad + PI) * p);
	y = sy[p1] + (cosf(rad + PI) * p);

	// 移動の方向に向かって動かす
	if (flag)
		p += s;
	else
		p -= s;

	// 移動の方向の切り替え
	if (p >= dis || p <= 0.f) {
		if (flag)
			flag = false;
		else
			flag = true;
	}
	collision();	// 当たり判定
	onfloor();
}
// 床に乗ったらベクトル共有
void	MoveFloor::onfloor() {

	COL_RECT player = { tplayer.p_y - tplayer.p_h / 2, tplayer.p_y + tplayer.p_h / 2, tplayer.p_x - tplayer.p_w / 2, tplayer.p_x + tplayer.p_w / 2 };
	COL_RECT e = { (int)y - (int)h / 2 - 2, (int)y + (int)h / 2, ((int)x - (int)w / 2) + 5, ((int)x + (int)w / 2) - 5 };

	// ベクトルを共有
	if (col_RectAndRect(player, e)) {
		tplayer.p_x += (x - ox);
		tplayer.jump_p = -4.f;
	}
}
// 移動点を設定
void	MoveFloor::set_point(int num, float px, float py) {

	sx[num] = px;
	sy[num] = py;
}
/*------------------------------------------------------------------------------*
| <<< 乗ったら落ちる床 DropFloor >>>
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

	// 床に乗ったらフラグON
	if (col_RectAndRect(player, e)) {
		flag = true;
	}
	// 落下処理
	if (flag) {
		time++;
		// 床に乗って0.5秒経ったら(60fps)
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