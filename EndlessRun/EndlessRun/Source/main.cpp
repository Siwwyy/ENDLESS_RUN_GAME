#include "../Headers/Includes.h"
#include "../Headers/libs.h"

#include <iostream>
#include <utility>

using namespace std; // test


void processInput(GLFWwindow * window, glm::vec3 & position, glm::vec3 & rotation, glm::vec3 & scale, Keyboard& kb) // test
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	KeyStates newKeyStates;

	newKeyStates.W = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ? true : false);
	newKeyStates.A = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ? true : false);
	newKeyStates.S = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ? true : false);
	newKeyStates.D = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ? true : false);

	kb.Update(newKeyStates);

	//x += (float)kb.getDirX() / 100;
	//y += (float)kb.getDirY() / 100;
	position.x += (float)kb.getDirX() / 10;
	position.y += (float)kb.getDirY() / 10;
	//view = glm::translate(view, glm::vec3(x, y, -3.0f));
}


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

		Vertex vertices[] = // Path
		{
			//Position	0 1 2							//Color	RGB									//Texcoords (texture coordinates)			//Normals
			// TRIANGLE ONE
			glm::vec3(0.9f,  8.0f, 0.0f),				glm::vec3(1.f, 0.f, 0.f),					glm::vec2(1.0f, 1.0f),						glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.9f, -8.0f, 0.0f),				glm::vec3(0.f, 1.f, 0.f),					glm::vec2(1.0f, 0.0f),						glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.9f, -8.0f, 0.0f),				glm::vec3(0.f, 0.f, 1.f),					glm::vec2(0.0f, 0.0f),						glm::vec3(0.f, 0.f, 1.f),
			// TRIANGLE TWO
			glm::vec3(-0.9f,  8.0f, 0.0f),				glm::vec3(1.f, 1.f, 0.f),					glm::vec2(0.0f, 1.0f),						glm::vec3(0.f, 0.f, 1.f)

		};

		Vertex verticesHero[] = // Hero
		{
			//Position	0 1 2							//Color	RGB									//Texcoords (texture coordinates)			//Normals
			// TRIANGLE ONE
			glm::vec3(-0.5f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),					glm::vec2(0.f, 1.f),						glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5, 0.f),				glm::vec3(0.f, 1.f, 0.f),					glm::vec2(0.f, 0.f),						glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.f),				glm::vec3(0.f, 0.f, 1.f),					glm::vec2(1.f, 0.f),						glm::vec3(0.f, 0.f, 1.f),

			// TRIANGLE TWO
			glm::vec3(0.5f, 0.5f, 0.f),					glm::vec3(1.f, 1.f, 0.f),					glm::vec2(1.f, 1.f),						glm::vec3(0.f, 0.f, 1.f)

		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		// Enable texture blending
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		// Create shaders
		Shader shader("Basic_vertex.glsl", "Basic_fragment.glsl");
		shader.use();

		// Textures
		// todo: automatycznie poobracac pionowo teksturki
		Texture textureCat("res/textures/kot.png", GL_TEXTURE_2D, 0);		//0 means -> 0 ID
		Texture textureCat2("res/textures/kot2.png", GL_TEXTURE_2D, 0);
		Texture textureDeer("res/textures/simpson.png", GL_TEXTURE_2D, 0);
		Texture textureHero("res/textures/kacio.png", GL_TEXTURE_2D, 0);

		// Mesh
		Renderer renderer;
		Mesh mesh(vertices, 4 * 5, indices, 2 * 3); // Path
		Mesh meshHero(verticesHero, 4 * 5, indices, 2 * 3); // Hero

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // test

		// keyboard functionality & path management
		Keyboard kb;
		Path p;
		Hero h;

		// Other variables...
		float r = 0.0f; // test
		float increment = 0.05f; // test
		float oldTime; // todo: move to data structure class
		float newTime;
		float deltaTime;
		oldTime = newTime = deltaTime = 0;

		glm::vec3 postion(0.f);
		glm::vec3 rotation(0.f);
		glm::vec3 scale(0.f);
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{

			deltaTime = newTime - oldTime;
			oldTime = newTime;
			newTime = glfwGetTime();
			processInput(window, postion, rotation, scale, kb);
			// MVP matrices
			glm::mat4 proj = glm::mat4(1.0f); //
			glm::mat4 view = glm::mat4(1.0f); // "camera" / position  / rotation / scale / whatever of camera
			glm::mat4 model = glm::mat4(1.0f); // "model" / "vertex" / pos / rot / scale of object
			proj = glm::perspective(glm::radians(70.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 mvp = proj * view * model;

			/* Render here */
			renderer.Clear();


			// Path render queue
			// batch rendering ?
			for (int i = 0; i < p.getLength(); ++i) {

				// calculate MVP matrix
				model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.75f, -p[i].zOffset));
				//model = glm::translate(glm::mat4(1.0f), glm::vec3(-postion.x, -0.75f - postion.y, -p[i].zOffset));
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
					shader.setVec4f(glm::fvec4(r / 3, r / 2, r + 0.2, 1.0f), "u_Color");
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
			p.Update(deltaTime);

			// test - uniforms
			if (r > 1.0f) {
				increment = -0.05f;
			}
			else if (r < 0.0f) {
				increment = 0.05f;
			}

			r += increment;

			// Character render
			//cout << h.getPosition().first << ' ' << h.getPosition().second << endl;
			h.update(deltaTime, kb.getDirX(), kb.getDirY());
			model = glm::translate(glm::mat4(1.0f), glm::vec3(h.getPosition().first, -0.75f + h.getPosition().second, -3.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
			mvp = proj * view * model;
			shader.setMat4fv(mvp, "u_MVP");
			shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 0.5f), "u_Color");
			shader.set1i(textureHero.GetTextureUnit(), "u_Texture");
			textureHero.Bind();
			shader.use();
			meshHero.render(&shader);


			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		//va.Unbind();
		shader.unuse();
		//vb.Unbind();
		//ib.Unbind();
	}

	glfwTerminate();
	return 0;
}