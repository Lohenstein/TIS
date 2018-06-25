#pragma once

namespace	Game
{
	//--- ’è”éŒ¾ ---
	enum mode {
		mode_title,
		mode_game,
		mode_over,
	};
	//--- ŠÖ”éŒ¾ ---
};

extern  Stage	tstage;

extern	void	game_init(void);
extern	void	game_main(void);
extern	void	game_end(void);