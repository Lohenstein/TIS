#pragma once

//----------------------------------------------------------------------------
// �`��̍\����
//----------------------------------------------------------------------------

// �����蔻��������`�̍\����
typedef struct {
	int top;
	int bottom;
	int left;
	int right;
}COL_RECT;

// ���ʂ�Ԃ��\����
typedef struct {
	bool	result;	// �Փ˂������ǂ���
	float	setp_x;	// �����ꍇ���L�������ǂ̈ʒu�ɖ߂��΂�����
	float	setp_y;
}COL_HIT;

//----------------------------------------------------------------------------
// �����蔻��
//----------------------------------------------------------------------------
extern bool		col_RectAndRect(COL_RECT s1, COL_RECT s2);
extern float	col_CheckRadian(float p1w, float p1h, float p2w, float p2h);
extern int		col_HitRadian(float x1, float y1, float x2, float y2, float rad);
