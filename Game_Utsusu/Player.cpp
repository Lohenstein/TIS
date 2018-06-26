#include "Main.h"

void	Player::update() {

	gravity = 1.f;
	move();
	collision();
}

void	Player::draw() {

	float pp_x = p_x - p_x + WINDOW_SIZE_X / 2 + (p_x - Cam.get_rawx());
	float pp_y = p_y - p_y + WINDOW_SIZE_Y / 2 + (p_y - Cam.get_rawy());

	DrawBox(pp_x - p_w / 2, pp_y - p_h / 2, pp_x + p_w / 2, pp_y + p_h / 2, 0xFF0000, true);
}

// 自キャラ対なにかの当たり判定
COL_HIT	Player::collision() {

	COL_RECT player = { p_y - p_h / 2, p_y + p_h / 2, p_x - p_w / 2, p_x + p_w / 2 };
	COL_RECT maptip;

	COL_HIT	 result = { false, 0.f, 0.f };

	// マップとの当たり判定
	// -----------------------------------------------------------------------------------------------------------
	for (int i = 0; i < tstage.size.x; i++) {
		for (int j = 0; j < tstage.size.y; j++) {

			// 空気ブロックじゃなかったら
			if (tstage.map[i][j] != 0) {

				maptip = { j * bsize, j * bsize + bsize, i * bsize, i * bsize + bsize };

				// 当たり判定
				if (col_RectAndRect(player, maptip)) {
					// https://qiita.com/aini_bellwood/items/3b888dbebf3368904061
					// 上記のアルゴリズムで戻す
					
					// チップの中心座標
					float tip_cx = i * bsize + (bsize / 2.f);
					float tip_cy = j * bsize + (bsize / 2.f);

					// プレイヤーがチップからみてどの方向にいるのかを過去の座標の差分から求める
					int dir		= hit_radian(p_x, p_y, tip_cx, tip_cy);
					int o_dir	= hit_radian(o_x, o_y, tip_cx, tip_cy);

					// 方向毎に処理
					// *簡略化できないか検討中...
					switch (dir) {
					case 1: // right
						switch (o_dir) {
						case 4:
							p_y = j * bsize - (p_h / 2) - 1;
							jump_p = 0.f;
							break;
						case 2:
							p_y = j * bsize + bsize + (p_h / 2) + 1;
							jump_p = 0.f;
							break;
						default:
							p_x = i * bsize + bsize + (p_w / 2) + 1;
							inertia_deg = 0;
							break;
						}
						break;
					case 2: // bottom
						switch (o_dir) {
						case 1:
							p_x = i * bsize + bsize + (p_w / 2) + 1;
							inertia_deg = 0;
							break;
						case 3:
							p_x = i * bsize - (p_w / 2) - 1;
							inertia_deg = 0;
							break;
						default:
							p_y = j * bsize + bsize + (p_h / 2) + 1;
							jump_p = 0.f;
							break;
						}
						break;
					case 3: // left
						switch (o_dir) {
						case 4:
							p_y = j * bsize - (p_h / 2) - 1;
							jump_p = 0.f;
							break;
						case 2:
							p_y = j * bsize + bsize + (p_h / 2) + 1;
							jump_p = 0.f;
							break;
						default:
							p_x = i * bsize - (p_w / 2) - 1;
							inertia_deg = 0;
							break;
						}
						break;
					case 4: // top
						switch (o_dir) {
						case 1:
							p_x = i * bsize + bsize + (p_w / 2) + 1;
							inertia_deg = 0;
							break;
						case 3:
							p_x = i * bsize - (p_w / 2) - 1;
							inertia_deg = 0;
							break;
						default:
							p_y = j * bsize - (p_h / 2) - 1;
							jump_p = 0.f;
							break;
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}
	return result;
}

// 当たり判定処理後どの方向に戻すのかを角度から求める
// 1 : right, 2 : bottom, 3 : left, 4 : top
int		Player::hit_radian(float x1, float y1, float x2, float y2) {

	// キャラクタ中心とマップチップ中心の角度
	int deg = (int)r2d(atan2f(y2 - y1, x2 - x1)) + 180;

	if (deg > 45 && deg <= 135) {
		DrawString(700, 10, "2", 0xFFFFFF);
		return 2;
	}
	else if (deg > 135 && deg <= 225) {
		DrawString(700, 10, "3", 0xFFFFFF);
		return 3;
	}
	else if (deg > 225 && deg <= 315) {
		DrawString(700, 10, "4", 0xFFFFFF);
		return 4;
	}
	else {
		DrawString(700, 10, "1", 0xFFFFFF);
		return 1;
	}
	return -1;
}

// 自キャラクターの移動
void	Player::move() {

	// 過去の位置を記録
	o_x = p_x;
	o_y = p_y;

	// 左右の移動
	if (key[KEY_INPUT_A] == 2 || key[KEY_INPUT_D] == 2) {
		if (key[KEY_INPUT_A] == 2) {
			inertia_deg -= 4;	// 移動量θを減少
		}
		if (key[KEY_INPUT_D] == 2) {
			inertia_deg += 4;	// 移動量θを増加
		}
	}
	else {
		// キー押し下げ時以外は収束する
		if (inertia_deg > 0) inertia_deg -= 2;
		if (inertia_deg < 0) inertia_deg += 2;
	}
	if (inertia_deg >  90) inertia_deg =  90;	// はみ出しリミッタ
	if (inertia_deg < -90) inertia_deg = -90;

	p_x += sin((float)d2r(inertia_deg)) * p_s;	// 移動

	// ジャンプ
	if (key[KEY_INPUT_SPACE] == 1) jump_p = 20.f;
	
	p_y -= jump_p;		// ジャンプの重力
	jump_p -= gravity;
}