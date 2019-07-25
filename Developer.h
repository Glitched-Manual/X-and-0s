#pragma once

#ifndef DEVELOPER_H
#define DEVELOPER_H

struct Developer {

	const bool is_debug_mode();
	
private:
 	static const bool debug_mode = false;
};

#endif //DEVELOPER_H

