#include "../Headers/Includes.h"
#include "../Headers/libs.h"

#include <iostream>

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

int main(void)
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window;

	/* Initialize the library */

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// test
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		std::cout << "Error!\n";
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	{

		//Vertex vertices[] =
//{
//	//Position	0 1 2							//Color	RGB									//Texcoords (texture coordinates)			//Normals
////	TRIANGLE ONE
//	glm::vec3(-0.5f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),					glm::vec2(0.f, 1.f),						glm::vec3(0.f, 0.f, 1.f),
//	glm::vec3(-0.5f, -0.5, 0.f),				glm::vec3(0.f, 1.f, 0.f),					glm::vec2(0.f, 0.f),						glm::vec3(0.f, 0.f, 1.f),
//	glm::vec3(0.5f, -0.5f, 0.f),				glm::vec3(0.f, 0.f, 1.f),					glm::vec2(1.f, 0.f),						glm::vec3(0.f, 0.f, 1.f),
//
////TRIANGLE TWO
//	glm::vec3(0.5f, 0.5f, 0.f),					glm::vec3(1.f, 1.f, 0.f),					glm::vec2(1.f, 1.f),						glm::vec3(0.f, 0.f, 1.f)
//};
////unsigned nrOfVertices = (sizeof(vertices) / sizeof(Vertex));	//amount of vertices
////
////GLuint indices[] =
//{
//	0,1,2, //triangle one
//	0,2,3 //triangle two
//	3,4,5 //triangle two, using 6 vertices
//};

		Vertex vertices[] =
		{
			//Position	0 1 2							//Color	RGB									//Texcoords (texture coordinates)			//Normals
			//	TRIANGLE ONE
			glm::vec3(0.9f,  8.0f, 0.0f),				glm::vec3(1.f, 0.f, 0.f),					glm::vec2(1.0f, 1.0f),						glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.9f, -8.0f, 0.0f),				glm::vec3(0.f, 1.f, 0.f),					glm::vec2(1.0f, 0.0f),						glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.9f, -8.0f, 0.0f),				glm::vec3(0.f, 0.f, 1.f),					glm::vec2(0.0f, 0.0f),						glm::vec3(0.f, 0.f, 1.f),
			//TRIANGLE TWO
			glm::vec3(-0.9f,  8.0f, 0.0f),				glm::vec3(1.f, 1.f, 0.f),					glm::vec2(0.0f, 1.0f),						glm::vec3(0.f, 0.f, 1.f)

		};
		//float positions[] = {
		//	// positions          // texture coords
		//	 0.9f,  8.0f, 0.0f,   1.0f, 1.0f, // top right
		//	 0.9f, -8.0f, 0.0f,   1.0f, 0.0f, // bottom right
		//	-0.9f, -8.0f, 0.0f,   0.0f, 0.0f, // bottom left
		//	-0.9f,  8.0f, 0.0f,   0.0f, 1.0f  // top left
		//};
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		// Enable texture blending
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		//// Set up vertex buffer & vertex array
		//VertexArray va;
		//VertexBuffer vb(vertices, 4 * 5 * sizeof(float));

		//VertexBufferLayout layout;
		//layout.Push<float>(3);
		//layout.Push<float>(2);
		//va.AddBuffer(vb, layout);

		//// Set up index buffer
		//IndexBuffer ib(indices, 6);

		// Create shaders
		Shader shader("Basic_vertex.glsl", "Basic_fragment.glsl");
		shader.use();

		// Textures
		Texture textureCat("res/textures/kot.png", GL_TEXTURE_2D, 0);		//0 means -> 0 ID
		Texture textureCat2("res/textures/kot2.png", GL_TEXTURE_2D, 0);
		Texture textureDeer("res/textures/simpson.png", GL_TEXTURE_2D, 0);

		// Mesh
		Renderer renderer;
		Mesh mesh(vertices, 4 * 5, indices, 2 * 3);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // test

		// keyboard functionality & path management
		Keyboard kb;
		Path p;

		float r = 0.0f; // test
		float increment = 0.05f; // test

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			// MVP matrices
			glm::mat4 proj = glm::mat4(1.0f); //
			glm::mat4 view = glm::mat4(1.0f); // "camera" / position  / rotation / scale / whatever of camera
			glm::mat4 model = glm::mat4(1.0f); // "model" / "vertex" / pos / rot / scale of object
			proj = glm::perspective(glm::radians(70.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			// processInput(window, view, shader, x, y, kb); // test

			glm::mat4 mvp = proj * view * model;

			shader.setVec4f(glm::fvec4(0.8f, 0.3f, 0.8f, 1.0f), "u_Color");
			shader.setMat4fv(mvp, "u_MVP");
			/* Render here */
			renderer.Clear();

			//shader.use();
			//va.Bind();
			//ib.Bind();

			// render queue
			// batch rendering ?
			for (int i = 0; i < p.getLength(); ++i) {

				// calculate MVP matrix
				model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.75f, -p[i].zOffset));
				model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				mvp = proj * view * model;
				shader.setMat4fv(mvp, "u_MVP");

				// bind the right texture
				switch (p[i].textureId)
				{
				case 0:
					textureCat.Bind();
					shader.setVec4f(glm::fvec4(r, 0.3f, 0.8f, 1.0f), "u_Color");
					shader.set1i(textureDeer.GetTextureUnit(), "u_Texture");
					break;

				case 1:
					textureCat2.Bind();
					shader.setVec4f(glm::fvec4(r, 0.3f, 0.8f, 1.0f), "u_Color");
					shader.set1i(textureDeer.GetTextureUnit(), "u_Texture");
					break;

				case 2:
					shader.setVec4f(glm::fvec4(r/3, r/2, r + 0.2, 1.0f), "u_Color");
					shader.set1i(textureDeer.GetTextureUnit(), "u_Texture");
					textureDeer.Bind();
					break;
				default:
					break;
				}

				// render the segment
				shader.use();
				//renderer.Draw(va, ib, shader);
				mesh.render(&shader);
			}
			p.Update();

			// test - uniforms
			if (r > 1.0f) {
				increment = -0.05f;
			}
			else if (r < 0.0f) {
				increment = 0.05f;
			}

			r += increment;

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		//va.Unbind();
		//shader.unuse();
		//vb.Unbind();
		//ib.Unbind();
	}

	glfwTerminate();
	return 0;
}