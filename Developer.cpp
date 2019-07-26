#include "Developer.h"

const bool Developer::is_debug_mode()
{
	return debug_mode;
}

const bool Developer::is_text_based_game()
{
	static const bool text_based_game_mode = true;
}
