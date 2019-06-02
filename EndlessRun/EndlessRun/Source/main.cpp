#include "../Headers/Includes.h"
#include "../Headers/Obstacle.h"
#include "../Headers/libs.h"
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <windows.h>

#include <irrKlang.h> //for music
using namespace irrklang;
using namespace std; // test
//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

void render_score(int &your_score, Shader &shader, Mesh &meshHero, glm::mat4 &mvp, glm::mat4 &proj, glm::mat4 &view,
				  glm::mat4 &model, Texture *array, const size_t array_size, const unsigned int WIDTH,
				  const unsigned HEIGHT) {
	int which_texture = 0;
	int my_score = your_score;
	if (your_score < 10) {
		proj = glm::perspective(glm::radians(130.0f), (float)WIDTH / (float)HEIGHT / 2, 0.1f, 100.0f);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.9f, 1.9f, -1.0f));
		model = glm::rotate(model, glm::radians(180.0f),
							glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
		mvp = proj * view * model;
		shader.setMat4fv(mvp, "u_MVP");
		shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

		array[your_score].Bind();
		shader.set1i(array[your_score].GetTextureUnit(), "u_Texture");
		shader.use();
		meshHero.render(&shader);
	} else if (your_score == 10) {
		proj = glm::perspective(glm::radians(130.0f), (float)WIDTH / (float)HEIGHT / 2, 0.1f, 100.0f);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.03f, 1.9f, -1.0f));
		model = glm::rotate(model, glm::radians(180.0f),
							glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
		mvp = proj * view * model;
		shader.setMat4fv(mvp, "u_MVP");
		shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

		array[1].Bind();
		shader.set1i(array[1].GetTextureUnit(), "u_Texture");
		shader.use();
		meshHero.render(&shader);

		proj = glm::perspective(glm::radians(130.0f), (float)WIDTH / (float)HEIGHT / 2, 0.1f, 100.0f);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.9f, 1.9f, -1.0f));
		model = glm::rotate(model, glm::radians(180.0f),
							glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
		mvp = proj * view * model;
		shader.setMat4fv(mvp, "u_MVP");
		shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

		array[0].Bind();
		shader.set1i(array[0].GetTextureUnit(), "u_Texture");
		shader.use();
		meshHero.render(&shader);
	} else {
		int digit = 0;
		float digit_position = -0.9f;
		while (my_score >= 1) {
			digit = (my_score % 10);
			my_score /= 10;
			proj = glm::perspective(glm::radians(130.0f), (float)WIDTH / (float)HEIGHT / 2, 0.1f, 100.0f);
			model = glm::translate(glm::mat4(1.0f), glm::vec3(digit_position, 1.9f, -1.0f));
			model = glm::rotate(model, glm::radians(180.0f),
								glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
			mvp = proj * view * model;
			shader.setMat4fv(mvp, "u_MVP");
			shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

			array[digit].Bind();
			shader.set1i(array[digit].GetTextureUnit(), "u_Texture");
			shader.use();
			meshHero.render(&shader);
			digit_position -= 0.13f;
		}
	}
}

void increase_score(int &score) {
	++score;
	if (score > 9) {
		score = 0;
	}
	this_thread::sleep_for(std::chrono::seconds(1));
}

void processInput(GLFWwindow *window, glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale, Keyboard &kb) // test
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

int main(void) {
	if (!glfwInit())
		return -1;

	GLFWwindow *window;

	/* Initialize the library */

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	if (!window) {
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

	//{

	//{
	//	//Position	0 1 2							//Color	RGB									//Texcoords (texture
	// coordinates)
	////Normals
	////	TRIANGLE ONE
	//	glm::vec3(-0.5f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),					glm::vec2(0.f, 1.f),
	// glm::vec3(0.f, 0.f, 1.f), 	glm::vec3(-0.5f, -0.5, 0.f),				glm::vec3(0.f, 1.f, 0.f),
	// glm::vec2(0.f, 0.f),						glm::vec3(0.f, 0.f, 1.f), 	glm::vec3(0.5f, -0.5f, 0.f),
	// glm::vec3(0.f, 0.f, 1.f),					glm::vec2(1.f, 0.f),						glm::vec3(0.f,
	// 0.f, 1.f),
	//
	////TRIANGLE TWO
	//	glm::vec3(0.5f, 0.5f, 0.f),					glm::vec3(1.f, 1.f, 0.f),					glm::vec2(1.f, 1.f),
	// glm::vec3(0.f, 0.f, 1.f)
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
		{				// Position	0 1 2	//Color	RGB		//Texcoords (texture // coordinates)			//Normals
		 // TRIANGLE ONE
		 glm::vec3(0.9f, 8.0f, 0.0f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(1.0f, 1.0f), glm::vec3(0.f, 0.f, 1.f),
		 glm::vec3(0.9f, -8.0f, 0.0f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(1.0f, 0.0f), glm::vec3(0.f, 0.f, 1.f),
		 glm::vec3(-0.9f, -8.0f, 0.0f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.0f, 0.0f), glm::vec3(0.f, 0.f, 1.f),
		 // TRIANGLE TWO
		 glm::vec3(-0.9f, 8.0f, 0.0f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.0f, 1.0f), glm::vec3(0.f, 0.f, 1.f)

		};

	Vertex verticesHero[] = // Hero
		{glm::vec3(-0.5f, 1.0f, 0.f), glm::vec3(1.f, 0.f, 0.f),	glm::vec2(0.f, 1.f),
		 glm::vec3(0.f, 0.f, 1.f),	glm::vec3(-0.5f, -0.5, 0.f), glm::vec3(0.f, 1.f, 0.f),
		 glm::vec2(0.f, 0.f),		  glm::vec3(0.f, 0.f, 1.f),	glm::vec3(0.5f, -0.5f, 0.f),
		 glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f, 0.f),		   glm::vec3(0.f, 0.f, 1.f),

		 glm::vec3(0.5f, 1.0f, 0.f),  glm::vec3(1.f, 1.f, 0.f),	glm::vec2(1.f, 1.f),
		 glm::vec3(0.f, 0.f, 1.f)

		};

	Vertex verticesObstacleRegular[] = // h: 2, w: 1 (jump-over)
		{glm::vec3(-0.25f, 1.0f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, 1.f),
		 glm::vec3(-0.25f, 0.0f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f),
		 glm::vec3(0.25f, 0.0f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 1.f),

		 // TRIANGLE TWO
		 glm::vec3(0.25f, 1.0f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, 1.f)

		};

	Vertex verticesObstacleWide[] = // h: 2, w: 2 (jump-over)
		{glm::vec3(-0.5f, 1.0f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, 1.f),
		 glm::vec3(-0.5f, 0.0f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f),
		 glm::vec3(0.5f, 0.0f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 1.f),

		 // TRIANGLE TWO
		 glm::vec3(0.5f, 1.0f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, 1.f)

		};

	Vertex verticesObstacleWideTall[] = // h: 2, w: 2 (jump-over)
	{ glm::vec3(-0.5f, 2.0f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, 1.f),
	 glm::vec3(-0.5f, 1.0f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f),
	 glm::vec3(0.5f, 1.0f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 1.f),

		// TRIANGLE TWO
		glm::vec3(0.5f, 2.0f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, 1.f)

	};

	Vertex verticesObstacleWider[] = // h: 2, w: 2 (jump-over)
		{glm::vec3(-1.0f, 1.0f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, 1.f),
		 glm::vec3(-1.0f, 0.0f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f),
		 glm::vec3(1.0f, 0.0f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 1.f),

		 // TRIANGLE TWO
		 glm::vec3(1.0f, 1.0f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, 1.f)

		};

	unsigned int indices[] = {0, 1, 2, 2, 3, 0};

	// Enable texture blending
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// Create shaders
	Shader shader("Basic_vertex.glsl", "Basic_fragment.glsl");
	shader.use();

	// Textures
	// todo: automatycznie poobracac pionowo teksturki
	Texture textureBrick1("res/textures/brick.jpg", GL_TEXTURE_2D, 0); // 0 means -> 0 ID
	Texture textureBrick2("res/textures/kot2.png", GL_TEXTURE_2D, 0);
	Texture textureBrick3("res/textures/simpson.png", GL_TEXTURE_2D, 0);
	Texture textureFence("res/textures/fence.jpg", GL_TEXTURE_2D, 0);

	Texture textureObstacle("res/textures/kot.png", GL_TEXTURE_2D, 0);

	//Texture background_menu_texture("res/textures/menu_background_image.png", GL_TEXTURE_2D, 0);
	Texture background_menu_texture("res/textures/tlo4.png", GL_TEXTURE_2D, 0);
	Texture tunel("res/textures/tunel.png", GL_TEXTURE_2D, 0);
	Texture sun("res/textures/slonko.png", GL_TEXTURE_2D, 0);
	//Texture sun("res/textures/pkow.png", GL_TEXTURE_2D, 0);
	//Texture background_menu_texture_in_game("res/textures/background_iamge.png", GL_TEXTURE_2D, 0);
	Texture clouds("res/textures/clouds.png", GL_TEXTURE_2D, 0);
	Texture score("res/textures/score.png", GL_TEXTURE_2D, 0);
	Texture score1("res/textures/1.png", GL_TEXTURE_2D, 0);
	Texture score2("res/textures/2.png", GL_TEXTURE_2D, 0);
	Texture score3("res/textures/3.png", GL_TEXTURE_2D, 0);
	Texture score4("res/textures/4.png", GL_TEXTURE_2D, 0);
	Texture score5("res/textures/5.png", GL_TEXTURE_2D, 0);
	Texture score6("res/textures/6.png", GL_TEXTURE_2D, 0);
	Texture score7("res/textures/7.png", GL_TEXTURE_2D, 0);
	Texture score8("res/textures/8.png", GL_TEXTURE_2D, 0);
	Texture score9("res/textures/9.png", GL_TEXTURE_2D, 0);
	Texture score0("res/textures/0.png", GL_TEXTURE_2D, 0);
	const size_t size_texture_array = 10;
	Texture texture_array[size_texture_array] = {score0, score1, score2, score3, score4,
												 score5, score6, score7, score8, score9};
	// Texture *score_ptr = nullptr;
	Texture background_logo("res/textures/logo_endless_run_game.png", GL_TEXTURE_2D, 0);
	Texture background_press_space("res/textures/press_space.png", GL_TEXTURE_2D, 0);

	// Texture textureHero1("res/textures/kacio_hero_1.png", GL_TEXTURE_2D, 0);
	// Texture textureHero1("res/textures/ludzik-glowadd.jpg", GL_TEXTURE_3D, 0);


	//Texture textureHero1("res/textures/ludzik-glowa3D.png", GL_TEXTURE_2D, 0);
	Texture textureHero1("res/textures/majkel_jordan.png", GL_TEXTURE_2D, 0);


	// Texture textureHero2("res/textures/kacio_hero_2.png", GL_TEXTURE_2D, 0);
	// Texture textureHero2("res/textures/ludzik-glowadd.jpg", GL_TEXTURE_3D, 0);


	//Texture textureHero2("res/textures/ludzik-glowa3D.png", GL_TEXTURE_2D, 0);
	Texture textureHero2("res/textures/majkel_jordan1.png", GL_TEXTURE_2D, 0);


	//	Texture textureHero3("res/textures/kacio_hero_3.png", GL_TEXTURE_2D, 0);


	//Texture textureHero3("res/textures/ludzik-glowa3D.png", GL_TEXTURE_2D, 0);
	Texture textureHero3("res/textures/majkel_jordan2.png", GL_TEXTURE_2D, 0);


	int currentHeroTexture = 1;

	// Mesh
	Renderer renderer;
	Mesh mesh(vertices, 4 * 5, indices, 2 * 3);								  // Path
	Mesh meshHero(verticesHero, 4 * 5, indices, 2 * 3);						  // Hero
	Mesh meshObstacleRegular(verticesObstacleRegular, 4 * 5, indices, 2 * 3); // Obstacle
	Mesh meshObstacleWide(verticesObstacleWide, 4 * 5, indices, 2 * 3);		  // Obstacle
	Mesh meshObstacleWideTall(verticesObstacleWideTall, 4 * 5, indices, 2 * 3);		  // Obstacle
	Mesh meshObstacleWider(verticesObstacleWider, 4 * 5, indices, 2 * 3);	  // Obstacle

	//Mesh meshObstacleRegular(verticesObstacleRegular, 4 * 5, indices, 2 * 3); // Obstacle-regular
	//Mesh meshObstacleWide(verticesObstacleWide, 4 * 5, indices, 2 * 3);		  // Obstacle-regular
	//Mesh meshObstacleWider(verticesObstacleWider, 4 * 5, indices, 2 * 3);	 // Obstacle-regular
	Mesh meshFence(vertices, 4 * 5, indices, 2 * 3);						  // Side fences

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // test

	// keyboard functionality & path management
	// todo: replace w/ data structure class
	Keyboard kb;
	Path p;
	Hero h;
	Texture *ptr_texture = nullptr;
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
	SoundEngine->setSoundVolume(0.5);
	// SoundEngine->play2D("res/audio/Sound FX Pack/\MLG Parody Sound FX/20th Century Recorder Edition.mp3", GL_TRUE);
	//////////////////////////////////////////////////////////////////
	size_t obstacle_counter = 0;

	bool skip = false;
	bool music_play = false;
	bool score_set = false;
	int your_score = 0;
	int score_counter = 0;
	float a = 0;
	float b = 0;
	float c = 0;
	float d = 0;
	float cloud_moves = 0.f;
	bool tym = false;
	bool tym2 = false;
	bool game_over = false;

	while (!glfwWindowShouldClose(window)) // Game Loop
	{

		if (GetAsyncKeyState(VK_SPACE)) {
			skip = true;
			game_over = false;
		} else if (GetAsyncKeyState(VK_ESCAPE) || game_over == true) {

			if (skip == true)
			{
				SoundEngine->setAllSoundsPaused();
				SoundEngine->play2D("res/audio/gameover.mp3", GL_TRUE);
				glm::vec3 postion(0.f);
				glm::vec3 rotation(0.f);
				glm::vec3 scale(0.f);
				your_score = 0;
				cloud_moves = 0;
				score_set = false;
				tym = false;
				tym2 = false;
				music_play = false;
				score_counter = 0;
				currentHeroTexture = 1;
				this_thread::sleep_for(std::chrono::seconds(3));
				renderer.Clear();
				SoundEngine->setAllSoundsPaused();
			}
			skip = false;
			// SoundEngine->play2D("res/audio/Sound FX Pack/\MLG Parody Sound FX/20th Century Recorder
			// Edition.mp3",GL_TRUE);
		}
		if (skip == true) {
			if (music_play == false) {
				SoundEngine->play2D("res/audio/soundtrack1.mp3", GL_TRUE);
				// SoundEngine->play2D("res/audio/soundtrack2.mp3", GL_TRUE);
				music_play = true;
			}
			 glClearColor(0.0f, 0.0f, 0.5f, 0.5f);
			// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			// Update
			deltaTime = newTime - oldTime; // calculate elapsed time
			oldTime = newTime;
			newTime = (float)glfwGetTime();
			processInput(window, postion, rotation, scale, kb); // get keyboard input
			p.Update(deltaTime);								// update path
			h.update(deltaTime, kb.getDirX(), kb.getDirY());	// update hero

			if (r > 1.0f)
				increment = -0.01f;
			else if (r < 0.0f)
				increment = 0.01f;
			r += increment;

			// Draw

			// MVP matrices
			glm::mat4 proj = glm::mat4(1.0f);  //
			glm::mat4 view = glm::mat4(1.0f);  // "camera"
			glm::mat4 model = glm::mat4(1.0f); // "object"
			proj = glm::perspective(glm::radians(70.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
			// model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 mvp = proj * view * model;

			/* Render here */
			renderer.Clear();

			proj = glm::perspective(glm::radians(140.0f), (float)WIDTH / (float)HEIGHT / 2, 0.1f, 150.0f);
			 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, -0.3f));
			 model = glm::rotate(model, glm::radians(180.0f),
								glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
			 mvp = proj * view * model;
			 shader.setMat4fv(mvp, "u_MVP");
			 shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

			 tunel.Bind();
			 shader.set1i(tunel.GetTextureUnit(), "u_Texture");
			 shader.use();
			 meshHero.render(&shader);
			 // MVP matrices
			 proj = glm::mat4(1.0f);  //
			 view = glm::mat4(1.0f);  // "camera"
			 model = glm::mat4(1.0f); // "object"
			 proj = glm::perspective(glm::radians(70.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
			 // model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			 mvp = proj * view * model;

			// Path
			for (unsigned int i = 0; i < p.getLength(); ++i) {

				// calculate MVP matrix
				// todo move calculations to shaders
				model = glm::mat4(1.0f);

				// te do zostawienia
				// 1. poloz
				model = glm::translate(model, glm::vec3(0.0f, -0.75f, 0.0f));
				model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				// 2. przesun o zOffset
				model = glm::translate(model, glm::vec3(0.0f, -p[i].zOffset, 0.0f));
				// 3. obroc o rotation
				// model = glm::rotate(model, glm::radians(90.0f * p[i].rotation), glm::vec3(0.0f, 0.0f, 1.0f));
				// 4. przesun o xOffset
				// model = glm::translate(model, glm::vec3(0.0f, -p[i].xOffset, 0.0f)); // z, x, y

				mvp = proj * view * model;
				shader.setMat4fv(mvp, "u_MVP");

				switch (p[i].textureId) {
				case 0:
					//++your_score;
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

			// Obstacles
			for (unsigned int i = 0; i < p.getLength(); ++i) {

				unsigned int j = p.getLength() - i - 1;

				// Check for collisions
				if (i == 0 && p[0].zOffset < -0.8f && p[0].zOffset > -0.95f) {
					// system("pause");
					Obstacle o = p[0].obstacle;
					std::pair<float, float> heroPosition = h.getPosition();
					bool doesCollide = false;
					auto collidesHorizontally = [](int obstaclePos, int width, float playerPos) {
						if (width == 1) {
							float radiusMin = obstaclePos - 0.25f;
							float radiusMax = obstaclePos + 0.25f;
							return (playerPos > radiusMin) && (playerPos < radiusMax);
						}

						if (width == 2) {
							if (obstaclePos == -1) {
								return playerPos < 0.33f;
							} else {
								return playerPos > -0.33f;
							}
						} else  if (width == 3) {
							return true;
						}
					};

					switch (o.type()) {
					case Obstacle::JUMP_OVER:
						doesCollide =
							(heroPosition.second < 1.36f / 2) && collidesHorizontally(o.pos(), 1, heroPosition.first);
						break;
					case Obstacle::JUMP_OVER_WIDE:
						doesCollide =
							(heroPosition.second < 1.36f / 2) && collidesHorizontally(o.pos(), 2, heroPosition.first);
						break;
					case Obstacle::OMIT_WIDE:
						doesCollide = collidesHorizontally(o.pos(), 2, heroPosition.first);
					}
					
					if (doesCollide) {
						//std::cout << "Collision!\n";
						// todo: Game over screen
						//skip = false;
						game_over = true;
					}
				}

				// Render obstacle

				if (p[j].zOffset > -2) {
					int t = p[j].obstacle.type();

					float px = p[j].obstacle.pos() * 0.5f;

					if (t == Obstacle::OMIT_WIDE || t == Obstacle::JUMP_OVER_WIDE) {
						px += 0.2f;
					}
					float py = -0.35f + (t == Obstacle::OMIT_WIDE) + ((t == Obstacle::SLIDE) || (t == Obstacle::SLIDE_WIDE));

					model = glm::translate(glm::mat4(1.0f), glm::vec3(px, py, -3.0f));
					model = glm::translate(model, glm::vec3(0.0f, 0.0f, -p[j].zOffset));
					model =
						glm::rotate(model, glm::radians(180.0f),
									glm::vec3(1.0f, 0.0f, 0.0f)); // tekstura, todo: wyciac po poprawce w klasie texture
					mvp = proj * view * model;

					shader.setMat4fv(mvp, "u_MVP");
					shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

					textureObstacle.Bind();
					shader.set1i(textureObstacle.GetTextureUnit(), "u_Texture");
					shader.use();

					switch (t) {
					case Obstacle::JUMP_OVER:
					case Obstacle::SLIDE:
						meshObstacleRegular.render(&shader);
						break;
					case Obstacle::OMIT_WIDE:
						meshObstacleWideTall.render(&shader);
					case Obstacle::JUMP_OVER_WIDE:
						meshObstacleWide.render(&shader);
						break;
					case Obstacle::SLIDE_WIDE:
						meshObstacleWider.render(&shader);
					}
				}
			}

			// Character
			model = glm::translate(glm::mat4(1.0f),
								   glm::vec3(h.getPosition().first, -0.75f + h.getPosition().second, -3.0f));
			model = glm::rotate(model, glm::radians(180.0f),
								glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
			mvp = proj * view * model;
			shader.setMat4fv(mvp, "u_MVP");
			shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

			if (++currentHeroTexture >= 24) {
				currentHeroTexture = 0;
			}

			switch (currentHeroTexture / 8 + 1) {
			case 1:
				//++your_score;
				textureHero1.Bind();
				shader.set1i(textureHero1.GetTextureUnit(), "u_Texture");
				// SoundEngine->play2D("res/audio/Sound FX Pack/\MLG Parody Sound FX/20th Century Recorder Edition.mp3",
				// GL_TRUE);
				break;

			case 2:
				textureHero2.Bind();
				shader.set1i(textureHero2.GetTextureUnit(), "u_Texture");
				// SoundEngine->setAllSoundsPaused();
				break;

			case 3:
				textureHero3.Bind();
				shader.set1i(textureHero3.GetTextureUnit(), "u_Texture");
				// SoundEngine->setAllSoundsPaused();
				break;
			default:
				break;
			}

			shader.use();
			meshHero.render(&shader);

			proj = glm::perspective(glm::radians(130.0f), (float)WIDTH / (float)HEIGHT / 2, 0.1f, 100.0f);
			model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.55f, 1.9f, -1.0f));
			model = glm::rotate(model, glm::radians(180.0f),
								glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
			mvp = proj * view * model;
			shader.setMat4fv(mvp, "u_MVP");
			shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

			score.Bind();
			shader.set1i(score.GetTextureUnit(), "u_Texture");
			shader.use();
			meshHero.render(&shader);

			// render_score(your_score, shader, meshHero, mvp, proj, view, model, texture_array, size_texture_array,
			// WIDTH,
			//			 HEIGHT);

			proj = glm::mat4(1.0f);	 //
			view = glm::mat4(1.0f);	 // "camera"

			render_score(your_score, shader, meshHero, mvp, proj, view, model, texture_array, size_texture_array, WIDTH,
						 HEIGHT);
			proj = glm::mat4(1.0f);  //
			view = glm::mat4(1.0f);  // "camera"
			model = glm::mat4(1.0f); // "object"
			if (score_counter % 61 == 0 && score_counter > 0) {
				++your_score;
				score_counter = 0;
			}
			++score_counter;







			proj = glm::perspective(glm::radians(120.0f), (float)WIDTH / (float)HEIGHT / 2, 0.1f, 150.0f);
			model = glm::translate(glm::mat4(1.0f), glm::vec3(cloud_moves, 0.45f, -1.0f));
			model = glm::rotate(model, glm::radians(180.0f),
								glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
			mvp = proj * view * model;
			shader.setMat4fv(mvp, "u_MVP");
			shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

			clouds.Bind();
			shader.set1i(clouds.GetTextureUnit(), "u_Texture");
			shader.use();
			meshHero.render(&shader);


			if (tym2 == true) {
				cloud_moves -= 0.01f;
			} else if (tym2 == false) {
				cloud_moves += 0.01f;
			}

			if (cloud_moves > 0.9f) {
				tym2 = true;
			} else if (cloud_moves < -0.9f) {
				tym2 = false;
			}




			proj = glm::perspective(glm::radians(110.0f), (float)WIDTH / (float)HEIGHT / 2, 0.1f, 150.0f);
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.9f, 1.1f, -1.0f));
			model = glm::rotate(model, glm::radians(180.0f),
								glm::vec3(1.0f, 0.0f, cloud_moves)); // todo: wyciac po poprawce w klasie texture
			mvp = proj * view * model;
			shader.setMat4fv(mvp, "u_MVP");
			shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

			sun.Bind();
			shader.set1i(sun.GetTextureUnit(), "u_Texture");
			shader.use();
			meshHero.render(&shader);



			//proj = glm::perspective(glm::radians(140.0f), (float)WIDTH / (float)HEIGHT / 2, 0.1f, 150.0f);
			//model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, -1.9f));
			//model = glm::rotate(model, glm::radians(180.0f),
			//					glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
			//mvp = proj * view * model;
			//shader.setMat4fv(mvp, "u_MVP");
			//shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

			//tunel.Bind();
			//shader.set1i(tunel.GetTextureUnit(), "u_Texture");
			//shader.use();
			//meshHero.render(&shader);





			//++cloud_moves;

		} else {
			glm::mat4 proj = glm::mat4(1.0f);  //
			glm::mat4 view = glm::mat4(1.0f);  // "camera"
			glm::mat4 model = glm::mat4(1.0f); // "object"
			proj = glm::perspective(glm::radians(59.0f), ((float)WIDTH / (float)HEIGHT) / 2, 0.1f, 100.0f);
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.1f, -1.0f));
			model = glm::rotate(model, glm::radians(180.0f),
								glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
			glm::mat4 mvp = proj * view * model;
			shader.setMat4fv(mvp, "u_MVP");
			shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

			renderer.Clear();

			background_menu_texture.Bind();
			shader.set1i(background_menu_texture.GetTextureUnit(), "u_Texture");
			shader.use();
			meshHero.render(&shader);




		











			proj = glm::perspective(glm::radians(80.0f), (float)WIDTH / (float)HEIGHT / 2, 0.1f, 100.0f);
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.45f, -1.0f));
			model = glm::rotate(model, glm::radians(180.0f),
								glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
			mvp = proj * view * model;
			shader.setMat4fv(mvp, "u_MVP");
			shader.setVec4f(glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), "u_Color");

			background_logo.Bind();
			shader.set1i(background_logo.GetTextureUnit(), "u_Texture");
			shader.use();
			meshHero.render(&shader);

			proj = glm::perspective(glm::radians(90.0f), ((float)WIDTH / (float)HEIGHT) / 1.5f, 0.1f, 100.0f);
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5f, -1.0f));
			model = glm::rotate(model, glm::radians(180.0f),
								glm::vec3(1.0f, 0.0f, 0.0f)); // todo: wyciac po poprawce w klasie texture
			mvp = proj * view * model;
			shader.setMat4fv(mvp, "u_MVP");
			shader.setVec4f(glm::fvec4(1.0f, a, 1.0f, 1.0f), "u_Color");
			background_press_space.Bind();
			shader.set1i(background_press_space.GetTextureUnit(), "u_Texture");

			shader.use();
			meshHero.render(&shader);

			if (tym == true) {
				a -= 0.1f;
			} else if (tym == false) {
				a += 0.1f;
			}

			if (a > 3.0f) {
				tym = true;
			} else if (a < 0.0f) {
				tym = false;
			}
		}
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	shader.unuse();
	ptr_texture = nullptr;
	glfwTerminate();
	return 0;
}
