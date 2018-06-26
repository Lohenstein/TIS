#pragma once
/*------------------------------------------------------------------------------*
| <<< �G�l�~�[�e�N���X Enemy >>>
*------------------------------------------------------------------------------*/
class Enemy {
public:
	// ---< �ϐ� >---------------------------------------------------------
	float	x, y;				// �G�L�����N�^���W(�G�̒��S)
	float	w, h;				// ���ƍ���
	float	jump_p  = 0.f;		// �W�����v
	float	gravity = 1.f;		// �d��
	float   dx, dy;


	// ---< �R���X�g���N�^ >------------------------------------------------
	Enemy() {
		x = 500.f;	// �K���ɏ���������
		y = 0.f;
		w = 100.f;
		h = 120.f;
	}
	// ---< �֐� >---------------------------------------------------------
	bool	collision_to_player();	// �G�Ǝ��L�����̓����蔻��
	void	collision_to_stage();	// �G�ƃX�e�[�W�̏Փ˔���

	// ---< �ȉ��e�X�g�p�I�I�[�o�[���C�h���Ďg�����ƁI >-----------------------
	void	update() {				// �e�X�g�A�b�v�f�[�g
		collision_to_stage();
		if (collision_to_player()) {
			DrawString(10, 10, "�������Ă܂�", 0xFFFFFF);
		}
		y -= jump_p;				// �d�͌v�Z�̏������̗�
		jump_p -= gravity;
	}
	void	draw() {				// �e�X�g�`��
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


