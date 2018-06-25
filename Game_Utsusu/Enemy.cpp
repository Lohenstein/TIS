#include "Main.h"
/*------------------------------------------------------------------------------*
| <<< �G�l�~�[�e�N���X Enemy >>>
*------------------------------------------------------------------------------*/
// �L�����N�^���m�̓����蔻��
// [[true : �ڐG , false : ��ڐG]]
//------------------------------------------------------------------------------//
bool	Enemy::collision_to_player() {
	// ��`���
	COL_RECT my  = { (int)y - (int)h / 2, (int)y + (int)h / 2, (int)x - (int)w / 2, (int)x + (int)w / 2 };
	COL_RECT player = { tplayer.p_y - tplayer.p_h / 2, tplayer.p_y + tplayer.p_h / 2, tplayer.p_x - tplayer.p_w / 2, tplayer.p_x + tplayer.p_w / 2 };
	// �����蔻��
	if (col_RectAndRect(player, my)) {
		return true;	// �ڐG��
	}
	else {
		return false;	// ��ڐG��
	}
}
// �X�e�[�W�Ƃ̓����蔻��
//------------------------------------------------------------------------------//
void	Enemy::collision_to_stage() {

	COL_RECT my  = { y - h / 2, y + h / 2, x - w / 2, x + w / 2 };
	COL_RECT maptip;

	for (int i = 0; i < tstage.size.x; i++) {
		for (int j = 0; j < tstage.size.y; j++) {

			// ��C�u���b�N����Ȃ�������
			if (tstage.map[i][j] != 0) {

				maptip = { j * bsize, j * bsize + bsize, i * bsize, i * bsize + bsize };

				// �����蔻��
				if (col_RectAndRect(my, maptip)) {
					// https://qiita.com/aini_bellwood/items/3b888dbebf3368904061
					// ��L�̃A���S���Y���Ŗ߂�

					// �`�b�v�̒��S���W
					float tip_cx = i * bsize + (bsize / 2.f);
					float tip_cy = j * bsize + (bsize / 2.f);

					// �v���C���[���`�b�v����݂Ăǂ̕����ɂ���̂����ߋ��̍��W�̍������狁�߂�
					int dir = tplayer.hit_radian(x, y, tip_cx, tip_cy); // �ō��ɏL���R�[�h�Ȃ̂ł��̂�������

					// �������ɏ���
					// *�ȗ����ł��Ȃ���������...
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