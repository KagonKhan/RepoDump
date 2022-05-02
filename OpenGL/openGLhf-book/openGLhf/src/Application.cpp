#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Shader.h"
#include "Camera.h"
#include "SOIL.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void SetBoxUniforms(const Shader& shader, const Shader& lampShader);
void CamMovement();

const GLuint WIDTH = 1920, HEIGHT = 1080;


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat g_LastX = 400.f, g_LastY = 300.f;
bool keys[1024];

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

bool firstMouse = true;

GLfloat g_DeltaTime = 0.f, g_LastFrame = 0.0f;
GLfloat mixValue = 0.2f;
GLfloat fov = 45.f;

/*TODO - careful about lib files - release mode */

int main() {
#pragma region Initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	//viewport
	glViewport(0, 0, WIDTH, HEIGHT);


	glfwSetKeyCallback(window, key_callback); // Function to call on key press
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
#pragma endregion

#pragma region init2
//	Shader shader("res/shaders/shader.vs", "res/shaders/shader.frag");
	Shader lightShader("res/shaders/lightShader.vs", "res/shaders/lightShader.frag");
	Shader lampShader("res/shaders/lampShader.vs", "res/shaders/lampShader.frag");
	Shader shader("res/shaders/shader.vs", "res/shaders/shader.frag");



	float verticesForBoxes[] = {
				//pos				tex				  normals
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		 0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		 0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		 0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		 0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		 0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,		 0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,		 0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,		 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		 0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		-1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		 1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		 1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		 1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,		 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		 0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,		 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		 0.0f,  1.0f,  0.0f
	};

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	/*GLuint indices[] = {
		0,1,3,
		1,2,3
	};*/

	GLuint boxesVAO, boxesVBO;
	glGenVertexArrays(1, &boxesVAO);
	glGenBuffers(1, &boxesVBO);

	glBindVertexArray(boxesVAO);
	glBindBuffer(GL_ARRAY_BUFFER, boxesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesForBoxes), verticesForBoxes, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3*sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(5*sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(3);
	glBindVertexArray(0);



	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	glBindVertexArray(0);


	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO); // data already taken as VBO from previous decl
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

#pragma endregion

#pragma region texture init
	int width, height;

	GLuint diffuseMap, specularMap, texture2;
	glGenTextures(1, &diffuseMap);
	glGenTextures(1, &specularMap);
	glGenTextures(1, &texture2);


	unsigned char* image = SOIL_load_image("res/shaders/maps/DiffuseMapBox.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);


	image = SOIL_load_image("res/shaders/maps/SpecularLightMapBox.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, specularMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);


	image = SOIL_load_image("res/images/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, texture2);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);


#pragma endregion


	glClearColor(0.1f, 0.1f, 0.1f, 1.f);


	while (!glfwWindowShouldClose(window)) { 
#pragma region preinit
		glfwPollEvents();
		CamMovement();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLfloat currentFrame = glfwGetTime();
		g_DeltaTime = currentFrame - g_LastFrame;
		g_LastFrame = currentFrame;
#pragma endregion


		lightPos = camera.m_Position;
		lightPos = glm::vec3(lightPos.x, lightPos.y, lightPos.z);

		/* ======================= BOXES ============================*/
		shader.Use();
#pragma region textures
		glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseMap);
			glUniform1i(glGetUniformLocation(shader.GetProgram(), "material.diffuse"), 0);
		glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, specularMap);
			glUniform1i(glGetUniformLocation(shader.GetProgram(), "material.specular"), 1);
		glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, texture2);
			glUniform1i(glGetUniformLocation(shader.GetProgram(), "ourTexture2"), 2);
		glUniform1f(glGetUniformLocation(shader.GetProgram(), "mixValue"), mixValue);

#pragma endregion
		SetBoxUniforms(shader, lampShader);


		GLuint modelLoc			   = glGetUniformLocation(shader.GetProgram(), "model");
		
		glBindVertexArray(boxesVAO);

		for (GLuint i = 0; i < 10; ++i) {
			glm::mat4 model(1.f);
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.f * i;
			model = glm::rotate(model, angle, glm::vec3(1.f, 0.3f, 0.5f));
			model = glm::scale(model, glm::vec3(0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

	

		/* ======================== LIGHT ==============================*/


		lampShader.Use();

		modelLoc	  = glGetUniformLocation(lampShader.GetProgram(), "model");
		
		glm::mat4 model = glm::mat4(1.f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.02f));


		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);



		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return 0;
}

void CamMovement() {

	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(Camera_Movement::FORWARD, g_DeltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, g_DeltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(Camera_Movement::LEFT, g_DeltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(Camera_Movement::RIGHT, g_DeltaTime);

	if (keys[GLFW_KEY_UP])
		mixValue += 0.1f;

	if (keys[GLFW_KEY_DOWN])
		mixValue -= 0.1f;
}

void SetBoxUniforms(const Shader& shader, const Shader& lampShader) {

	GLuint viewLoc = glGetUniformLocation(shader.GetProgram(), "view");
	GLuint projectionLoc = glGetUniformLocation(shader.GetProgram(), "projection");
	GLuint viewPosLoc = glGetUniformLocation(shader.GetProgram(), "viewPos");

	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(camera.m_Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3f(viewPosLoc, camera.m_Position.x, camera.m_Position.y, camera.m_Position.z);





	glm::vec3 lightColor(1.f);

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	GLint  lightColorLoc = glGetUniformLocation(shader.GetProgram(), "lightColor");
	GLuint lightPosLoc = glGetUniformLocation(shader.GetProgram(), "light.position");
	GLuint lightAmbientLoc = glGetUniformLocation(shader.GetProgram(), "light.ambient");
	GLuint lightDiffuseLoc = glGetUniformLocation(shader.GetProgram(), "light.diffuse");
	GLuint lightSpecularLoc = glGetUniformLocation(shader.GetProgram(), "light.specular");

	GLint  matAmbientLoc = glGetUniformLocation(shader.GetProgram(), "material.ambient");
	GLuint matDiffuseLoc = glGetUniformLocation(shader.GetProgram(), "material.specular");
	GLuint matSpecularLoc = glGetUniformLocation(shader.GetProgram(), "material.diffuse");
	GLuint matShineLoc = glGetUniformLocation(shader.GetProgram(), "material.shininess");

	glUniform3f(lightColorLoc, 1.0f, 1.f, 1.0f);
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(lightAmbientLoc, ambientColor.x, ambientColor.y, ambientColor.z);
	glUniform3f(lightDiffuseLoc, diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);

	glUniform3f(matAmbientLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(matDiffuseLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
	glUniform1f(matShineLoc, 32.f);







	viewLoc = glGetUniformLocation(lampShader.GetProgram(), "view");
	projectionLoc = glGetUniformLocation(lampShader.GetProgram(), "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);


	if (action == GLFW_PRESS)
		keys[key] = true;
	if (action == GLFW_RELEASE)
		keys[key] = false;


	if (key == GLFW_KEY_C)
		system("CLS");

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {// this bool variable is initially set to true
		g_LastX = xpos;
		g_LastY = ypos;
		firstMouse = false;
	}
	GLfloat xoffset = xpos - g_LastX;
	GLfloat yoffset = g_LastY - ypos;  // Reversed since y-coordinates go from bottom to left

	g_LastX = xpos;
	g_LastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset * 0.1f);
}






/* ====================== light BOX ============================*/
//lightShader.Use();
//
//modelLoc = glGetUniformLocation(lightShader.GetProgram(), "model");
//viewLoc = glGetUniformLocation(lightShader.GetProgram(), "view");
//projectionLoc = glGetUniformLocation(lightShader.GetProgram(), "projection");
//viewPosLoc = glGetUniformLocation(lightShader.GetProgram(), "viewPos");
//
//GLint objectColorLoc = glGetUniformLocation(lightShader.GetProgram(), "objectColor");
//lightColorLoc = glGetUniformLocation(lightShader.GetProgram(), "lightColor");
//lightPosLoc = glGetUniformLocation(lightShader.GetProgram(), "light.position");
//lightAmbientLoc = glGetUniformLocation(lightShader.GetProgram(), "light.ambient");
//lightDiffuseLoc = glGetUniformLocation(lightShader.GetProgram(), "light.diffuse");
//lightSpecularLoc = glGetUniformLocation(lightShader.GetProgram(), "light.specular");
//
//
//matAmbientLoc = glGetUniformLocation(lightShader.GetProgram(), "material.ambient");
//matDiffuseLoc = glGetUniformLocation(lightShader.GetProgram(), "material.specular");
//matSpecularLoc = glGetUniformLocation(lightShader.GetProgram(), "material.diffuse");
//matShineLoc = glGetUniformLocation(lightShader.GetProgram(), "material.shininess");
//
//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
//glUniform3f(viewPosLoc, camera.m_Position.x, camera.m_Position.y, camera.m_Position.z);
//
//glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
//glUniform3f(lightColorLoc, 1.0f, 1.f, 1.0f);
//glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
//glUniform3f(lightAmbientLoc, ambientColor.x, ambientColor.y, ambientColor.z);
//glUniform3f(lightDiffuseLoc, diffuseColor.x, diffuseColor.y, diffuseColor.z);
//glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
//
//
//glUniform3f(matAmbientLoc, 1.0f, 0.5f, 0.31f);
//glUniform3f(matDiffuseLoc, 1.0f, 0.5f, 0.31f);
//glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
//glUniform1f(matShineLoc, 32.f);
//
//glBindVertexArray(VAO);
//
//glm::mat4 model(1.f);
//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//glDrawArrays(GL_TRIANGLES, 0, 36);
//glBindVertexArray(0);