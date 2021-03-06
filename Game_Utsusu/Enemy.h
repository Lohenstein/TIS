#pragma once
/*------------------------------------------------------------------------------*
| <<< エネミー親クラス Enemy >>>
*------------------------------------------------------------------------------*/
class Enemy {
public:
	// ---< 変数 >---------------------------------------------------------
	float	x, y;				// 敵キャラクタ座標(敵の中心)
	float	w, h;				// 幅と高さ
	float	jump_p  = 0.f;		// ジャンプ
	float	gravity = 1.f;		// 重力
	float   dx, dy;


	// ---< コンストラクタ >------------------------------------------------
	Enemy() {
		x = 500.f;	// 適当に初期化する
		y = 0.f;
		w = 100.f;
		h = 120.f;
	}
	// ---< 関数 >---------------------------------------------------------
	bool	collision_to_player();	// 敵と自キャラの当たり判定
	void	collision_to_stage();	// 敵とステージの衝突判定

	// ---< 以下テスト用！オーバーライドして使うこと！ >-----------------------
	void	update() {				// テストアップデート
		collision_to_stage();
		if (collision_to_player()) {
			DrawString(10, 10, "あたってます", 0xFFFFFF);
		}
		y -= jump_p;				// 重力計算の書き方の例
		jump_p -= gravity;
	}
	void	draw() {				// テスト描画
		float dx, dy;
		dx = x - Cam.get_x();
		dy = y - Cam.get_y();
		DrawBox(dx - w / 2, dy - h / 2, dx + w / 2, dy + h / 2, 0xFF0000, false);
	}
};

class Enemy_Gun : public Enemy 
{
public:
	bool attack_flag;
	int attack_count;
	int bullet_speed;
	int bullet_x;
	int bullet_y;

	//int rand	

	Enemy_Gun() {
		w = 80.f;
		attack_flag = false;
		bullet_speed = 10;
	}

	void draw();
	void move();
	void update();
};


