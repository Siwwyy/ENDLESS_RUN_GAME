#ifndef _ASSERT_H_
#define _ASSERT_H_
#pragma once

#include "Includes.h"	

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))


#endif /* _ASSERT_H_ */