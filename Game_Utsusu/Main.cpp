
#include "Main.h"

int FrameStartTime;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	// İ’è
	ChangeWindowMode(true);
	SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32);
	SetMainWindowText("‰¹ƒQ[");

	// ‰Šú‰»
	if (DxLib_Init() == -1) {
		return -1;
	}

	SetWaitVSyncFlag(FALSE);
	SetDrawScreen(DX_SCREEN_BACK);

	// ƒQ[ƒ€‰Šú‰»
	game_init();
	FrameStartTime = GetNowCount();

	// ƒƒCƒ“ƒ‹[ƒv
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) 
	{
		// ‚P/‚U‚O•b—§‚Â‚Ü‚Å‘Ò‚Â
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}
		FrameStartTime = GetNowCount();

		// ƒQ[ƒ€ƒƒCƒ“
		game_main();
	}

	// ƒQ[ƒ€I—¹
	game_end();
	DxLib_End();

	return 0;
}