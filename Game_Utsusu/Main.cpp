
#include "Main.h"

int FrameStartTime;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	// 設定
	ChangeWindowMode(true);
	SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32);
	SetMainWindowText("音ゲー");

	// 初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	SetWaitVSyncFlag(FALSE);
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲーム初期化
	game_init();
	FrameStartTime = GetNowCount();

	// メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) 
	{
		// １/６０秒立つまで待つ
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}
		FrameStartTime = GetNowCount();

		// ゲームメイン
		game_main();
	}

	// ゲーム終了
	game_end();
	DxLib_End();

	return 0;
}