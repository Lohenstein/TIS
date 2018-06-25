
#include "Main.h"

// ��`���m�̂����蔻��
bool col_RectAndRect(COL_RECT s1, COL_RECT s2) {
	if (s1.left <= s2.right && s2.left <= s1.right &&
		s1.top <= s2.bottom && s2.top <= s1.bottom) {
		return true;
	}
	return false;
}

// ��ɍڂ��Ă�����ʐς𔻕ʂ���
float	col_CheckRadian(float p1w, float p1h, float p2w, float p2h) {
	float x = (p1w / 2.f) + (p2w / 2.f);
	float y = (p1h / 2.f) + (p2h / 2.f);
	return atan2f(y, x) + PI;
}

// �����蔻�菈����ǂ̕����ɖ߂��̂����p�x���狁�߂�
// 1 : right, 2 : bottom, 3 : left, 4 : top
int		col_HitRadian(float x1, float y1, float x2, float y2, float rad) {

	// �L�����N�^���S�ƃ}�b�v�`�b�v���S�̊p�x
	int deg  = (int)r2d(atan2f(y2 - y1, x2 - x1) + PI);
	int cdeg = (int)r2d(rad);

	if (deg > cdeg && deg <= 180 - cdeg) {
		DrawString(400, 10, "2", 0xFFFFFF);
		return 2;
	}
	else if (deg > 180 - cdeg && deg <= 180 + cdeg) {
		DrawString(400, 10, "3", 0xFFFFFF);
		return 3;
	}
	else if (deg > 180 + cdeg && deg <= 360 - cdeg) {
		DrawString(400, 10, "4", 0xFFFFFF);
		return 4;
	}
	else {
		DrawString(400, 10, "1", 0xFFFFFF);
		return 1;
	}
	return -1;
}