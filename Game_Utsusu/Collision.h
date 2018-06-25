#pragma once

//----------------------------------------------------------------------------
// 形状の構造体
//----------------------------------------------------------------------------

// 当たり判定をする矩形の構造体
typedef struct {
	int top;
	int bottom;
	int left;
	int right;
}COL_RECT;

// 結果を返す構造体
typedef struct {
	bool	result;	// 衝突したかどうか
	float	setp_x;	// した場合自キャラをどの位置に戻せばいいか
	float	setp_y;
}COL_HIT;

//----------------------------------------------------------------------------
// 当たり判定
//----------------------------------------------------------------------------
extern bool		col_RectAndRect(COL_RECT s1, COL_RECT s2);
extern float	col_CheckRadian(float p1w, float p1h, float p2w, float p2h);
extern int		col_HitRadian(float x1, float y1, float x2, float y2, float rad);
