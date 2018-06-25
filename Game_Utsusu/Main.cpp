
#include "Main.h"

int FrameStartTime;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	// �ݒ�
	ChangeWindowMode(true);
	SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32);
	SetMainWindowText("���Q�[");

	// ������
	if (DxLib_Init() == -1) {
		return -1;
	}

	SetWaitVSyncFlag(FALSE);
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[��������
	game_init();
	FrameStartTime = GetNowCount();

	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) 
	{
		// �P/�U�O�b���܂ő҂�
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}
		FrameStartTime = GetNowCount();

		// �Q�[�����C��
		game_main();
	}

	// �Q�[���I��
	game_end();
	DxLib_End();

	return 0;
}