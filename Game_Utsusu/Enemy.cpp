#include "Main.h"
/*------------------------------------------------------------------------------*
| <<< エネミー親クラス Enemy >>>
*------------------------------------------------------------------------------*/
// キャラクタ同士の当たり判定
// [[true : 接触 , false : 非接触]]
//------------------------------------------------------------------------------//
bool	Enemy::collision_to_player() {
	// 矩形情報
	COL_RECT my  = { (int)y - (int)h / 2, (int)y + (int)h / 2, (int)x - (int)w / 2, (int)x + (int)w / 2 };
	COL_RECT player = { tplayer.p_y - tplayer.p_h / 2, tplayer.p_y + tplayer.p_h / 2, tplayer.p_x - tplayer.p_w / 2, tplayer.p_x + tplayer.p_w / 2 };
	// 当たり判定
	if (col_RectAndRect(player, my)) {
		return true;	// 接触時
	}
	else {
		return false;	// 非接触時
	}
}
// ステージとの当たり判定
//------------------------------------------------------------------------------//
void	Enemy::collision_to_stage() {

	COL_RECT my  = { y - h / 2, y + h / 2, x - w / 2, x + w / 2 };
	COL_RECT maptip;

	for (int i = 0; i < tstage.size.x; i++) {
		for (int j = 0; j < tstage.size.y; j++) {

			// 空気ブロックじゃなかったら
			if (tstage.map[i][j] != 0) {

				maptip = { j * bsize, j * bsize + bsize, i * bsize, i * bsize + bsize };

				// 当たり判定
				if (col_RectAndRect(my, maptip)) {
					// https://qiita.com/aini_bellwood/items/3b888dbebf3368904061
					// 上記のアルゴリズムで戻す

					// チップの中心座標
					float tip_cx = i * bsize + (bsize / 2.f);
					float tip_cy = j * bsize + (bsize / 2.f);

					// プレイヤーがチップからみてどの方向にいるのかを過去の座標の差分から求める
					int dir = tplayer.hit_radian(x, y, tip_cx, tip_cy); // 最高に臭いコードなのでそのうち治す

					// 方向毎に処理
					// *簡略化できないか検討中...
					switch (dir) {
					case 1: // right
						x = i * bsize + bsize + (w / 2) + 1;
						break;
					case 2: // bottom
						y = j * bsize + bsize + (h / 2) + 1;
						jump_p = 0.f;
						break;
					case 3: // left
						x = i * bsize - (w / 2) - 1;
						break;
					case 4: // top
						y = j * bsize - (h / 2) - 1;
						jump_p = 0.f;
					default:
						break;
					}
				}
			}
		}
	}
}

/*
// GunEnemy 1 時間がたつと打つだけ
void Enemy_Gun::move()
{
	
}
void Enemy_Gun::update() {				// テストアップデート
	move();
	collision_to_stage();
	if (collision_to_player()) {
		DrawString(10, 10, "あたってます", 0xFFFFFF);
	}
	y -= jump_p;				// 重力計算の書き方の例
	jump_p -= gravity;
}
void Enemy_Gun::draw()
{
	if (attack_flag == false) {
		attack_count++;
		if (attack_count >= 100) {
			attack_flag = true;
			attack_count = 0;
			bullet_x = x - camera_px + WINDOW_SIZE_X / 2.f;
			bullet_y = y - camera_py + WINDOW_SIZE_Y / 2.f;
		}
	}
	else if (attack_flag == true) {
		attack_count++;
		//bullet_y = dy;
		bullet_y = y - camera_py + WINDOW_SIZE_Y / 2.f;
		DrawCircle(bullet_x, bullet_y, 10, 0xffffff, true);
		if (attack_count >= 100) {
			attack_count = 0;
			attack_flag = false;
		}
		else {
			bullet_x += bullet_speed - tplayer.inertia_deg;
		}
	}
}
*/

void Enemy_Gun::move()
{
	
	x++;
	dx++;
}

void Enemy_Gun::update() {				// テストアップデート
	move();
	collision_to_stage();
	if (collision_to_player()) {
		DrawString(10, 10, "あたってます", 0xFFFFFF);
	}
	y -= jump_p;				// 重力計算の書き方の例
	jump_p -= gravity;
	if (attack_count == 50)
	jump_p = 20.f;
}
void Enemy_Gun::draw()
{
	dx = x - camera_px + WINDOW_SIZE_X / 2.f;
	dy = y - camera_py + WINDOW_SIZE_Y / 2.f;
	DrawBox(dx - w / 2, dy - h / 2, dx + w / 2, dy + h / 2, 0xFF0000, false);

	if (attack_flag == false) {
		attack_count++;
		if (attack_count >= 100) {
			attack_flag = true;
			attack_count = 0;
			bullet_x = x - camera_px + WINDOW_SIZE_X / 2.f;
			bullet_y = y - camera_py + WINDOW_SIZE_Y / 2.f;
		}
	}
	else if (attack_flag == true) {
		attack_count++;
		//bullet_y = dy;
		bullet_y = y - camera_py + WINDOW_SIZE_Y / 2.f;
		DrawCircle(bullet_x, bullet_y, 10, 0xffffff, true);
		if (attack_count >= 100) {
			attack_count = 0;
			attack_flag = false;
		}
		else {
			bullet_x += bullet_speed - tplayer.inertia_deg;
		}
	}
}