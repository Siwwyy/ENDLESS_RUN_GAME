#include "../Headers/Includes.h"
#include "../Headers/Renderer.h"
#include "../Headers/libs.h"

#include <iostream>
#include <windows.h>

using namespace std;

//void processInput(GLFWwindow *window, glm::mat4 &view, Shader& shader, float &x, float &y, Keyboard& kb) // test
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	KeyStates newKeyStates;
//
//	newKeyStates.W = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ? true : false);
//	newKeyStates.A = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ? true : false);
//	newKeyStates.S = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ? true : false);
//	newKeyStates.D = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ? true : false);
//
//	kb.Update(newKeyStates);
//
//	x += (float)kb.getDirX() / 100;
//	y += (float)kb.getDirY() / 100;
//
//	view = glm::translate(view, glm::vec3(x, y, -3.0f));
//}
//

void framebuffer_resize_callback(GLFWwindow * window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}


int main()
{

	if (glfwInit() == false)
	{
		return EXIT_FAILURE;
	}

	//CREATE WINDOW
	const int WINDOW_WIDTH = 860;
	const int WINDOW_HEIGHT = 640;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, FALSE); //unresizable window

	GLFWwindow * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MY WINDOW", NULL, NULL);

	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	glfwMakeContextCurrent(window);		//IMPORTANT!!

	glewExperimental = GL_TRUE;

	//Error
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::MAIN.COO::GLEW_INIT_FAILED" << '\n';
		glfwTerminate();
	}

	//OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//if u want draw it by lines
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		

	//*===*===*===*===*===*===*//
	// Positions & indices setup
	float positions[] = {
		// positions          // texture coords
		 0.75f,  8.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.75f, -8.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.75f, -8.0f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.75f,  8.0f, 0.0f,   0.0f, 1.0f  // top left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray va;
	VertexBuffer vb(positions, 4 * 5 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	IndexBuffer ib(indices, 6);

	//*===*===*===*===*===*===*//
	// Shaders & textures setup
	Texture textureCat("res/textures/kot.png");
	Texture textureCat2("res/textures/kot2.png");
	Texture textureDeer("res/textures/rogacz.png");
	//Shader core_program("vertex_core.glsl", "fragment_core.glsl");
	Shader shader("Basic_vertex.shader", "Basic_fragment.shader");
	glUseProgram(0);

	Renderer renderer;

	//*===*===*===*===*===*===*//
	// Other variables...
	Path p;
	float r = 0.0f; // test
	float increment = 0.05f; // test

	// Main loop
	while (glfwWindowShouldClose(window) == false)
	{
		//glfwSetKeyCallback(window, keyCallBack); // napraw to !!
		//updateInput(window, position, rotation, scale);

		glClearColor(1.f, 3.f, 5.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//*===*===*===*===*===*===*//
		// Test - Path
		glm::mat4 proj = glm::mat4(1.0f); //
		glm::mat4 view = glm::mat4(1.0f); // "camera" / position  / rotation / scale / whatever of camera
		glm::mat4 model = glm::mat4(1.0f); // "model" / "vertex" / pos / rot / scale of object
		proj = glm::perspective(glm::radians(70.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		// processInput(window, view, shader, x, y, kb); // test

		glm::mat4 mvp = proj * view * model;

		shader.use();
		shader.setVec4f(glm::fvec4(0.8f, 0.3f, 0.8f, 1.0f), "u_Color");
		shader.setMat4fv(mvp, "u_MVP");

		/* Render here */
		renderer.Clear();

		shader.use();
		va.Bind();
		ib.Bind();

		// render queue
		// batch rendering ?
		for (int i = 0; i < p.getLength(); ++i) {
			// bind the right texture
			switch (p[i].textureId)
			{
			case 0:
				textureCat.Bind();
				shader.setVec4f(glm::fvec4(r, 0.3f, 0.8f, 1.0f), "u_Color");
				break;
			case 1:
				textureCat2.Bind();
				shader.setVec4f(glm::fvec4(r, 0.3f, 0.8f, 1.0f), "u_Color");
				break;
			case 2:
				shader.setVec4f(glm::fvec4(r, 0.3f, 0.8f, 1.0f), "u_Color");
				textureDeer.Bind();
				break;
			default:
				break;
			}

			// render the segment
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.75f, -p[i].zOffset));
			//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			mvp = proj * view * model;
			shader.setMat4fv(mvp, "u_MVP");
			renderer.Draw(va, ib, shader);
		}
		p.Update();

		// first cat
		// if ((float)glfwGetTime() < 4) {
			//texture.Bind(); // first cat
			// renderer.Draw(va, ib, shader);
		//}

		// second cat
		//if ((float)glfwGetTime() < 4 + 8) {
		//	//texture2.Bind();
		//	view = glm::mat4(1.0f);
		//	view = glm::translate(view, glm::vec3(0.0f, -0.75f, (float)glfwGetTime() * 2- 16));
		//	mvp = proj * view * model;
		//	shader.SetUniformMat4f("u_MVP", mvp);
		//	renderer.Draw(va, ib, shader);
		//}

		// test - uniforms
		if (r > 1.0f) {
			increment = -0.05f;
		}
		else if (r < 0.0f) {
			increment = 0.05f;
		}

		r += increment;

		glfwSwapBuffers(window);
		glFlush();
		glfwPollEvents();

	}



	system("Pause");
	return 0;
}