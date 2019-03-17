#include "../Headers/Includes.h"
//#include "../Headers/Renderer.h"
#include "../Headers/libs.h"

#include <iostream>
#include <windows.h>

using namespace std;

//INITIALIZE THE VERTEX AND INDICES 
//Vertices
Vertex vertices[] =
{
	//Position	0 1 2							//Color	RGB									//Texcoords (texture coordinates)			//Normals
	//TRIANGLE ONE
	glm::vec3(-0.5f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),					glm::vec2(0.f, 1.f),						glm::vec3(0.f, 0.f, 1.f),
	glm::vec3(-0.5f, -0.5, 0.f),				glm::vec3(0.f, 1.f, 0.f),					glm::vec2(0.f, 0.f),						glm::vec3(0.f, 0.f, 1.f),
	glm::vec3(0.5f, -0.5f, 0.f),				glm::vec3(0.f, 0.f, 1.f),					glm::vec2(1.f, 0.f),						glm::vec3(0.f, 0.f, 1.f),

	//TRIANGLE TWO
	glm::vec3(0.5f, 0.5f, 0.f),					glm::vec3(1.f, 1.f, 0.f),					glm::vec2(1.f, 1.f),						glm::vec3(0.f, 0.f, 1.f)
};
unsigned nrOfVertices = (sizeof(vertices) / sizeof(Vertex));	//amount of vertices

GLuint indices[] =
{
	0,1,2, //triangle one
	0,2,3 //triangle two
	//3,4,5 //triangle two, using 6 vertices
};
unsigned nrOfIndices = (sizeof(indices) / sizeof(GLuint));	//amount of indices


void processInput(GLFWwindow *window, glm::mat4 &view, Shader& shader, float &x, float &y, Keyboard& kb) // test
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	KeyStates newKeyStates;

	newKeyStates.W = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ? true : false);
	newKeyStates.A = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ? true : false);
	newKeyStates.S = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ? true : false);
	newKeyStates.D = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ? true : false);

	kb.Update(newKeyStates);

	x += (float)kb.getDirX() / 100;
	y += (float)kb.getDirY() / 100;

	view = glm::translate(view, glm::vec3(x, y, -3.0f));
}


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

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//4.4   major.minor
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, FALSE);	//unresizable window

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
		

	//INITIALIZE THE SHADER
//	Shader Core_Shader("vertex_core.glsl", "fragment_core.glsl");
	Shader Core_Shader("Basic_vertex.glsl", "Basic_fragment.glsl");

	//INITIALIZE THE MESH
	
	Mesh Mesh_Object(vertices, nrOfVertices, indices, nrOfIndices);

	////*===*===*===*===*===*===*//
	//// Positions & indices setup
	//float positions[] = {
	//	// positions          // texture coords
	//	 0.75f,  8.0f, 0.0f,   1.0f, 1.0f, // top right
	//	 0.75f, -8.0f, 0.0f,   1.0f, 0.0f, // bottom right
	//	-0.75f, -8.0f, 0.0f,   0.0f, 0.0f, // bottom left
	//	-0.75f,  8.0f, 0.0f,   0.0f, 1.0f  // top left
	//};

	//unsigned int indices[] = {
	//	0, 1, 2,
	//	2, 3, 0
	//};

	/*VertexArray va;
	VertexBuffer vb(positions, 4 * 5 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	IndexBuffer ib(indices, 6);*/



	/*VAO, VBO, EBO
	GENERATE VAO AND BIND*/
	//GLuint VAO;
	//glCreateVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

	////GENERATE VAO AND BIND AND SEND DATA
	//GLuint VBO;
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	////glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);	//if u want change it dynamically
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	////GENERATE EBO AND BIND AND SEND DATA
	//GLuint EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	////glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);  //if u want change it dynamically
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	////SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
	////[0][0.5][0][1][0][0][1][0][]
	////POSITION
	////GLuint attribLoc = glGetAttribLocation(core_program, "vertex_position");  if u dont have a shader location put where are zeros this attrib location
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	////[][][][][][][][][][][] ->VERTEX
	//glEnableVertexAttribArray(0);

	////COLOR
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	//glEnableVertexAttribArray(1);

	////Texcoord
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	//glEnableVertexAttribArray(2);

	////Normal
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	//glEnableVertexAttribArray(3);

	////BIND VAO 0
	//glBindVertexArray(0);







	//*===*===*===*===*===*===*//
	// Shaders & textures setup
	Texture textureCat("res/textures/kot.png", GL_TEXTURE_2D, 0);		//0 means -> 0 ID
	//Texture textureCat2("res/textures/kot2.png");
	//Texture textureDeer("res/textures/rogacz.png");

	//Shader shader("Basic_vertex.shader", "Basic_fragment.shader");
	//glUseProgram(0);

	//Renderer renderer;

	//*===*===*===*===*===*===*//
	// Other variables...
	//Path p;
	//float r = 0.0f; // test
	//float increment = 0.05f; // test
	



	Material material0(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), textureCat.GetTextureUnit());


	glUseProgram(0); //before the main loop !
	// Main loop
	while (glfwWindowShouldClose(window) == false)
	{
		//glfwSetKeyCallback(window, keyCallBack); // napraw to !!
		//updateInput(window, position, rotation, scale);
		glfwPollEvents();
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		////*===*===*===*===*===*===*//
		//// Test - Path
		//glm::mat4 proj = glm::mat4(1.0f); //
		//glm::mat4 view = glm::mat4(1.0f); // "camera" / position  / rotation / scale / whatever of camera
		//glm::mat4 model = glm::mat4(1.0f); // "model" / "vertex" / pos / rot / scale of object
		//proj = glm::perspective(glm::radians(70.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		////view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		//// processInput(window, view, shader, x, y, kb); // test

		//glm::mat4 mvp = proj * view * model;

		//shader.use();
		//shader.setVec4f(glm::fvec4(0.8f, 0.3f, 0.8f, 1.0f), "u_Color");
		//shader.setMat4fv(mvp, "u_MVP");

		///* Render here */
		//renderer.Clear();

		//shader.use();
		//va.Bind();
		//ib.Bind();

		//// render queue
		//// batch rendering ?
		//for (int i = 0; i < p.getLength(); ++i) {
		//	// bind the right texture
		//	switch (p[i].textureId)
		//	{
		//	case 0:
		//		textureCat.Bind();
		//		shader.setVec4f(glm::fvec4(r, 0.3f, 0.8f, 1.0f), "u_Color");
		//		break;
		//	case 1:
		//		textureCat2.Bind();
		//		shader.setVec4f(glm::fvec4(r, 0.3f, 0.8f, 1.0f), "u_Color");
		//		break;
		//	case 2:
		//		shader.setVec4f(glm::fvec4(r, 0.3f, 0.8f, 1.0f), "u_Color");
		//		textureDeer.Bind();
		//		break;
		//	default:
		//		break;
		//	}

		//	// render the segment
		//	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.75f, -p[i].zOffset));
		//	//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//	mvp = proj * view * model;
		//	shader.setMat4fv(mvp, "u_MVP");
		//	renderer.Draw(va, ib, shader);
		//}
		//p.Update();

		//// first cat
		//// if ((float)glfwGetTime() < 4) {
		//	//texture.Bind(); // first cat
		//	// renderer.Draw(va, ib, shader);
		////}

		//// second cat
		////if ((float)glfwGetTime() < 4 + 8) {
		////	//texture2.Bind();
		////	view = glm::mat4(1.0f);
		////	view = glm::translate(view, glm::vec3(0.0f, -0.75f, (float)glfwGetTime() * 2- 16));
		////	mvp = proj * view * model;
		////	shader.SetUniformMat4f("u_MVP", mvp);
		////	renderer.Draw(va, ib, shader);
		////}

		//// test - uniforms
		//if (r > 1.0f) {
		//	increment = -0.05f;
		//}
		//else if (r < 0.0f) {
		//	increment = 0.05f;
		//}

		//r += increment;




		Core_Shader.set1i(textureCat.GetTextureUnit(), "texture0");
		//material0.sendToShader(Core_Shader);

		//Use program //START BEFORE U STOP DRAWING!!!!!!!!!
		Core_Shader.use();
		textureCat.Bind();

		//glBindVertexArray(VAO);
		Mesh_Object.render(&Core_Shader);
		//glDrawArrays(GL_TRIANGLES, 0, nrOfVertices);	
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);	//drawing by indices
	//	Mesh_Object.render(&Core_Shader);

		glfwSwapBuffers(window);
		glFlush();
		
		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);	//if u set in texture class type like GL_TEXTURE_2D
	}

	//AFTER MAIN LOOP, TO CLEAR EVERYTHING
	glfwDestroyWindow(window);
	glfwTerminate();
//	glDeleteProgram(Core_Shader);
	//system("Pause");
	return EXIT_SUCCESS;
}