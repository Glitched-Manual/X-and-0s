#pragma once

#include <cstdio>
#include <iostream>
#ifndef DEVELOPER_H
#define DEVELOPER_H
struct Developer
{
private:
	static Developer * _instance;
	Developer()
	{
		puts("Developer initailized\n");
	}
	Developer(const Developer&) {};
	Developer& operator=(const Developer&) {};
	~Developer() {};
	
	static const bool debug_mode = true;
	static const bool text_based_game_mode = true;
	static const bool hit_boxes_rendered = true;

public:

	static Developer * GetInstance()
	{
		if (_instance == NULL)
		{
			_instance = new Developer;
		}
		return _instance;
	}
	const bool is_debug_mode();
	const bool is_text_based_game();
	const bool are_hit_boxes_rendered();
};

#endif //DEVELOPER_H

