#include "../Headers/Includes.h"
#include "../Headers/libs.h"
#include "../Headers/Obstacle.h"
#include <iostream>
#include <utility>
#include <string>
#include <windows.h>

#include <irrKlang.h>	//for music
using namespace irrklang;

using namespace std; // test
//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

void processInput(GLFWwindow * window, glm::vec3 & position, glm::vec3 & rotation, glm::vec3 & scale, Keyboard& kb) // test
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	KeyStates newKeyStates;

	newKeyStates.W = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
	newKeyStates.A = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
	newKeyStates.S = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
	newKeyStates.D = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);

	kb.Update(newKeyStates);

	position.x += (float)kb.getDirX() / 10;
	position.y += (float)kb.getDirY() / 10;
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

	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Error!\n";
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	//{

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
			glm::vec3(-0.5f, 1.0f, 0.f),				glm::vec3(1.f, 0.f, 0.f),					glm::vec2(0.f, 1.f),						glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5, 0.f),				glm::vec3(0.f, 1.f, 0.f),					glm::vec2(0.f, 0.f),						glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.f),				glm::vec3(0.f, 0.f, 1.f),					glm::vec2(1.f, 0.f),						glm::vec3(0.f, 0.f, 1.f),

			// TRIANGLE TWO
			glm::vec3(0.5f, 1.0f, 0.f),					glm::vec3(1.f, 1.f, 0.f),					glm::vec2(1.f, 1.f),						glm::vec3(0.f, 0.f,1.f)

		};

		unsigned int indices[] = 
		{
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
		Texture textureBrick1("res/textures/brick.jpg", GL_TEXTURE_2D, 0);		//0 means -> 0 ID
		Texture textureBrick2("res/textures/kot2.png", GL_TEXTURE_2D, 0);
		Texture textureBrick3("res/textures/simpson.png", GL_TEXTURE_2D, 0);
		Texture textureObstacle("res/textures/simpson.png", GL_TEXTURE_2D, 0);
		Texture textureObstacle1("res/textures/kot2.png", GL_TEXTURE_2D, 0);
		Texture textureObstacle2("res/textures/simpson.png", GL_TEXTURE_2D, 0);
		Texture textureFence("res/textures/fence.jpg", GL_TEXTURE_2D, 0);


		Texture background_menu_texture("res/textures/menu_background_image.png", GL_TEXTURE_2D, 0);
		Texture background_logo("res/textures/logo_endless_run_game.png", GL_TEXTURE_2D, 0);
		Texture background_press_space("res/textures/press_space.png", GL_TEXTURE_2D, 0);

		

		Texture textureHero1("res/textures/kacio_hero_1.png", GL_TEXTURE_2D, 0);
		//Texture textureHero1("res/textures/ludzik-glowadd.jpg", GL_TEXTURE_3D, 0);
		//Texture textureHero1("res/textures/ludzik-glowa3D.png", GL_TEXTURE_2D, 0);
		Texture textureHero2("res/textures/kacio_hero_2.png", GL_TEXTURE_2D, 0);
		//Texture textureHero2("res/textures/ludzik-glowadd.jpg", GL_TEXTURE_3D, 0);
	//	Texture textureHero2("res/textures/ludzik-glowa3D.png", GL_TEXTURE_2D, 0);
		Texture textureHero3("res/textures/kacio_hero_3.png", GL_TEXTURE_2D, 0);
		//Texture textureHero3("res/textures/ludzik-glowa3D.png", GL_TEXTURE_2D, 0);
		int currentHeroTexture = 1;

		// Mesh
		Renderer renderer;
		Mesh mesh(vertices, 4 * 5, indices, 2 * 3); // Path
		Mesh meshHero(verticesHero, 4 * 5, indices, 2 * 3); // Hero
		Mesh meshFence(vertices, 4 * 5, indices, 2 * 3); // Side fences

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // test

		// keyboard functionality & path management
		// todo: replace w/ data structure class
		Keyboard kb;
		Path p;
		Hero h;
		Obstacle Obstacle_Object;
		Texture * ptr_texture = nullptr;
		//Obstacle_Object.push_texture(&textureBrick1);
	//	Obstacle_Object.push_texture(&textureBrick2);
		//Obstacle_Object.push_texture(&textureBrick3);
		Obstacle_Object.push_texture(&textureObstacle);
		Obstacle_Object.push_texture(&textureObstacle1);
		Obstacle_Object.push_texture(&textureObstacle2);
		//std::cout << &textureObstacle << endl;	//working
		//std::cin.get();
		// Other variables...
		float r = 0.0f;
		float increment = 0.05f;
		float oldTime; // todo: move to data structure class
		float newTime;
		float deltaTime;
		oldTime = newTime = deltaTime = 0;

		glm::vec3 postion(0.f);
		glm::vec3 rotation(0.f);
		glm::vec3 scale(0.f);



		/*
			MUSIC
		*/

		ISoundEngine *SoundEngine = createIrrKlangDevice();
		//SoundEngine->play2D("res/audio/Sound FX Pack/\MLG Parody Sound FX/20th Century Recorder Edition.mp3", GL_TRUE);
		//////////////////////////////////////////////////////////////////
		//SoundEngine->drop();
		//int a = 0;
		/* Loop until the user closes the window */
		size_t obstacle_counter = 0;

		
		//background_menu_texture;
	/*	background_menu_texture.Bind();
		shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");
		shader.set1i(background_menu_texture.GetTextureUnit(), "u_Texture");
		shader.use();
		mesh.render(&shader);*/

	//	renderer.Draw()

		//ptr_texture = (Obstacle_Object.Create_Obstacle());
		//std::cout << ptr_texture << endl;	//works
		//std::cin.get();
		//background_menu_texture.Bind();
		////std::cin.get();
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(1.0f, -0.75f, -10.0f));
		////model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		////model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		////model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//mvp = proj * view * model;
		//shader.setMat4fv(mvp, "u_MVP");
		//shader.set1i(ptr_texture->GetTextureUnit(), "u_Texture");

		//shader.use();
		//mesh.render(&shader);
		//obstacle_counter = 0;


		//CREATE MENU HERE
		//if (GetAsyncKeyState(VK_SPACE))
		bool skip = false;
	//	for (;;)
		//{
			//if (GetAsyncKeyState(VK_SPACE))
			//if (GetAsyncKeyState(VK_SPACE))	//works
			//{
		float a = 0;
		float b = 0;
		float c = 0;
		float d = 0;
		bool tym = false;
				while (!glfwWindowShouldClose(window)) // Game Loop
				{
					if (GetAsyncKeyState(VK_SPACE))
					{
						skip = true;
					}

					if (skip == true)
					{
						//glClearColor(0.3f, 0.5f, 0.5f, 0.5f);
						//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
						// Update
						deltaTime = newTime - oldTime; // calculate elapsed time
						oldTime = newTime;
						newTime = (float)glfwGetTime();
						processInput(window, postion, rotation, scale, kb); // get keyboard input
						p.Update(deltaTime); // update path
						h.update(deltaTime, kb.getDirX(), kb.getDirY()); // update hero

						if (r > 1.0f)
							increment = -0.01f;
						else if (r < 0.0f)
							increment = 0.01f;
						r += increment;

						// Draw

						// MVP matrices
						glm::mat4 proj = glm::mat4(1.0f); //
						glm::mat4 view = glm::mat4(1.0f); // "camera"
						glm::mat4 model = glm::mat4(1.0f); // "object"
						proj = glm::perspective(glm::radians(70.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
						//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
						glm::mat4 mvp = proj * view * model;

						/* Render here */
						renderer.Clear();

						// Path
						for (unsigned int i = 0; i < p.getLength(); ++i)
						{

							// calculate MVP matrix
							// todo move calculations to shaders
							model = glm::mat4(1.0f);
							// te do wyjebania
							//model = glm::translate(model, glm::vec3(0.0f, -0.75f, -p[i].zOffset));
							//model = glm::rotate(model, glm::radians(90.0f * p[i].rotation), glm::vec3(0.0f, 1.0f, 0.0f));
							//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

							// te do zostawienia
							// 1. po��
							model = glm::translate(model, glm::vec3(0.0f, -0.75f, 0.0f));
							model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
							// 2. przesu� o zOffset
							model = glm::translate(model, glm::vec3(0.0f, -p[i].zOffset, 0.0f));
							// 3. obr�� o rotation
							model = glm::rotate(model, glm::radians(90.0f * p[i].rotation), glm::vec3(0.0f, 0.0f, 1.0f));
							// 4. przesu� o xOffset
							model = glm::translate(model, glm::vec3(0.0f, -p[i].xOffset, 0.0f)); // z, x, y


							//model = glm::translate(model, glm::vec3(p[i].xOffset, -0.75f, -p[i].zOffset));
							//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
							//model = glm::rotate(model, glm::radians(90.0f * p[i].rotation), glm::vec3(0.0f, 0.0f, 1.0f));

							mvp = proj * view * model;
							shader.setMat4fv(mvp, "u_MVP");

							switch (p[i].textureId)
							{
							case 0:
								textureBrick1.Bind();
								shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");
								shader.set1i(textureBrick1.GetTextureUnit(), "u_Texture");
								break;

							case 1:
								textureBrick2.Bind();
								shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");
								shader.set1i(textureBrick2.GetTextureUnit(), "u_Texture");
								break;

							case 2:
								textureBrick3.Bind();
								shader.setVec4f(glm::fvec4(r / 2, r / 3, 1.0f, 1.0f), "u_Color");
								shader.set1i(textureBrick3.GetTextureUnit(), "u_Texture");
								break;
							default:
								break;
							}

							shader.use();
							mesh.render(&shader);

							// Side fences
							textureFence.Bind();
							model = glm::mat4(1.0f);
							model = glm::translate(model, glm::vec3(1.5f, -0.75f, -p[i].zOffset));
							model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
							model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
							mvp = proj * view * model;
							shader.setMat4fv(mvp, "u_MVP");
							shader.set1i(textureFence.GetTextureUnit(), "u_Texture");
							shader.use();
							meshFence.render(&shader);

							model = glm::mat4(1.0f);
							model = glm::translate(model, glm::vec3(-1.5f, -0.75f, -p[i].zOffset));
							model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
							model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
							mvp = proj * view * model;
							shader.setMat4fv(mvp, "u_MVP");
							meshFence.render(&shader);

						}

						//delete ptr_texture;
				//	}

					// Character
						model = glm::translate(glm::mat4(1.0f), glm::vec3(h.getPosition().first, -0.75f + h.getPosition().second, -3.0f));
						model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
						mvp = proj * view * model;
						shader.setMat4fv(mvp, "u_MVP");
						shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

						if (++currentHeroTexture >= 24)
						{
							currentHeroTexture = 0;
						}


						switch (currentHeroTexture / 8 + 1)
						{
						case 1:
							textureHero1.Bind();
							shader.set1i(textureHero1.GetTextureUnit(), "u_Texture");
							//SoundEngine->play2D("res/audio/Sound FX Pack/\MLG Parody Sound FX/20th Century Recorder Edition.mp3", GL_TRUE);
							break;

						case 2:
							textureHero2.Bind();
							shader.set1i(textureHero2.GetTextureUnit(), "u_Texture");
							//SoundEngine->setAllSoundsPaused();
							break;

						case 3:
							textureHero3.Bind();
							shader.set1i(textureHero3.GetTextureUnit(), "u_Texture");
							//SoundEngine->setAllSoundsPaused();
							break;
						default:
							break;
						}

						shader.use();
						meshHero.render(&shader);

						if (obstacle_counter % 23 == 0)
						{
							//Obstacle
						//Obstacle_Object.Create_Obstacle();	//returns a pointer to the choosen texture
					//	Obstacle_Object.Create_Obstacle()->Bind();
							//ptr_texture = (Obstacle_Object.Create_Obstacle());
							////std::cout << ptr_texture << endl;	//works
							////std::cin.get();
							//ptr_texture->Bind();
							////std::cin.get();
							//model = glm::mat4(1.0f);
							//model = glm::translate(model, glm::vec3(1.0f, -0.75f, -10.0f));
							////model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
							////model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
							////model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
							//mvp = proj * view * model;
							//shader.setMat4fv(mvp, "u_MVP");
							//shader.set1i(ptr_texture->GetTextureUnit(), "u_Texture");
							//
							//shader.use();
							//mesh.render(&shader);
							//obstacle_counter = 0;

						}

						//Obstacle_Object.Create_Obstacle();	//returns a pointer to the choosen texture
					
						++obstacle_counter;
					}
					else
					{
						glm::mat4 proj = glm::mat4(1.0f); //
						glm::mat4 view = glm::mat4(1.0f); // "camera"
						glm::mat4 model = glm::mat4(1.0f); // "object"
						//proj = glm::perspective(glm::radians(70.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
						proj = glm::perspective(glm::radians(50.0f), ((float)WIDTH / (float)HEIGHT)/2, 0.1f, 100.0f);
						model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.3f, -1.0f));
						model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
						glm::mat4 mvp = proj * view * model;
						shader.setMat4fv(mvp, "u_MVP");
						shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

						renderer.Clear();



						background_menu_texture.Bind();
						shader.set1i(background_menu_texture.GetTextureUnit(), "u_Texture");
						shader.use();
						meshHero.render(&shader);




						proj = glm::perspective(glm::radians(80.0f), (float)WIDTH / (float)HEIGHT/2, 0.1f, 100.0f);
						model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.45f, -1.0f));
						model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
						mvp = proj * view * model;
						shader.setMat4fv(mvp, "u_MVP");
						shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");


						background_logo.Bind();
						shader.set1i(background_logo.GetTextureUnit(), "u_Texture");
						shader.use();
						meshHero.render(&shader);




						proj = glm::perspective(glm::radians(90.0f), ((float)WIDTH / (float)HEIGHT)/1.5f, 0.1f, 100.0f);
						model = glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5f, -1.0f));
						model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
						mvp = proj * view * model;
						shader.setMat4fv(mvp, "u_MVP");
						shader.setVec4f(glm::fvec4(1.0f, a, 1.0f, 1.0f), "u_Color");
						background_press_space.Bind();
						shader.set1i(background_press_space.GetTextureUnit(), "u_Texture");

						shader.use();
						meshHero.render(&shader);
					

						if (tym == true)
						{
							a -= 0.1f;
						}
						else if (tym == false)
						{
							a += 0.1f;
						}

						if (a > 2.0f)
						{
							tym = true;
						}
						else if (a < 0.0f)
						{
							tym = false;
						}
					}
					/* Swap front and back buffers */
					glfwSwapBuffers(window);

					/* Poll for and process events */
					glfwPollEvents();
				}

				shader.unuse();
				//delete ptr_texture;
				//break;
	ptr_texture = nullptr;
	glfwTerminate();
	return 0;
}