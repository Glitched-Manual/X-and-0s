#include "Developer.h"

Developer* Developer::_instance;

const bool Developer::is_debug_mode()
{
	return debug_mode;
}

const bool Developer::is_text_based_game()
{
	return text_based_game_mode;
}

const bool Developer::are_hit_boxes_rendered()
{
	return hit_boxes_rendered;
}