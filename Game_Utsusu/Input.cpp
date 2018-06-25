 #include "Main.h"

int		key[256];
int		pad_b[16];

// �L�[�{�[�h���͂��擾
void	input_key() {

	static char buf[256];
	GetHitKeyStateAll(buf);

	for (int i = 0; i < 256; i++) {
		if (buf[i]) {
			if (key[i] == 0) key[i] = 1;
			else if (key[i] == 1) key[i] = 2;
		}
		else key[i] = 0;
	}
}

// �Q�[���p�b�h���͂��擾
void	 input_pad() {

	XINPUT_STATE input_pad;
	GetJoypadXInputState(DX_INPUT_PAD1, &input_pad);

	for (int i = 0; i < 16; i++) {
		if (input_pad.Buttons[i]) {
			if (pad_b[i] == 0) pad_b[i] = 1;
			else if (pad_b[i] == 1) pad_b[i] = 2;
		}
		else pad_b[i] = 0;
	}
}

// �����Ƃ��擾(�O���[�o��)
void	input() {
	input_key();
	input_pad();
}
