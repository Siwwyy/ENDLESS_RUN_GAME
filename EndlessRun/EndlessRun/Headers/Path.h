#ifndef _PATH_H_
#define _PATH_H_
#pragma once

//#include "Includes.h"
//#include "libs.h"
/*
	OPENGL AND CONNECTED LIBRARIES
*/
//GLEW
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

//SOIL2
#include<SOIL2.h>

// imgui
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>


#include <vector>

struct pathSegment {
	unsigned int type; // 0 = regular, 1 = turn, ...
	unsigned int textureId; // 1 = kot.png, 2 = kot2.png, 3 = rogacz.png
	unsigned int id;
	float zOffset;
};

class Path
{
public:

	enum { // segment types
		REGULAR
	};

	enum { // segment textures
		CAT1 = 1,
		CAT2 = 2,
		DEER = 3
	};

	Path();

	void Update();

	inline unsigned int getLength() { return segments_.size(); }

	inline const pathSegment & operator[](int i) {
		return segments_[i];
	}


private:
	std::vector<pathSegment> segments_;

	float oldTime;
	float newTime;
};

#endif /* _PATH_H_ */