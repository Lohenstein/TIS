
#include "Main.h"

namespace Game
{
	int mode = mode_game;
}
Stage	tstage;
Player	tplayer;
MoveFloor	entity[ENTITY_MAX];
DropFloor	df[ENTITY_MAX];
Enemy	test;

using	namespace Game;

/*------------------------------------------------------------------------------*
| <<< �Q�[�������� >>>
*------------------------------------------------------------------------------*/
void	game_init(void)
{
	tstage.load("mapdata.csv");

	entity[0].set_point(0, 400, 680);
	entity[0].set_point(1, 1000, 200);
	df[0].set_point(1400, 500);
}
/*------------------------------------------------------------------------------*
| <<< �Q�[�����C�� >>>
*------------------------------------------------------------------------------*/
void	game_main(void)
{
	// ����
	switch (mode)
	{
	case mode_title:
		break;
	case mode_game:
		input();
		entity[0].update(3.f, 0, 1);
		df[0].update();
		tplayer.update();
		test.update();
		break;
	case mode_over:
		break;
	}

	// �`��
	switch (mode)
	{
	case mode_title:
		break;
	case mode_game:
		tplayer.draw();
		tstage.draw();
		entity[0].draw();
		df[0].draw();
		test.draw();
		break;
	case mode_over:
		break;
	}
}

/*------------------------------------------------------------------------------*
| <<< �Q�[���I�� >>>
*------------------------------------------------------------------------------*/
void	game_end(void)
{
}