#pragma once

#ifndef DEVELOPER_H
#define DEVELOPER_H

struct Developer {

	const bool is_debug_mode();
	const bool is_text_based_game();

private:
 	static const bool debug_mode = false;
	static const bool text_based_game_mode = true;
};

#endif //DEVELOPER_H

