#pragma once

#include <iomanip>
#include "MatrixFactory.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
#include "SphericalCamera.h"
#include "Mesh.h"
#include "FPSCamera.h"
#include "MeshManager.h"
#include "SceneGraph.h"
#include "SceneNode.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "World/Chunk/Chunk.h"
#include "World/Chunk/ChunkManager.h"
#include "Skybox.h"
#include "ResourcesManager.h"
#include "World/World.h"
#include "World/Block/BlockDatabase.h"
#include "World/WorldConstants.h"
#include "Sky/Cloud.h"
class GameManager {
	public:
		GameManager(void);
		~GameManager(void);

	private:
		int _keypressed;
		bool mouse_left_down, mouse_right_down;
		float _screenWidth;
		float _screenHeight;
		World* world;
		Matrix4 persM;
		Matrix4* projM;
		bool pressed[349];
		ShaderProgram* skyboxShader;
		Skybox* skybox;
		const GLuint UBO_BP = 0;
		float deltaTime = 0;
		SceneGraph* scenegraph;

	public:
		void update(double elapsed_sec, GLFWwindow* win);
		// CALLBACKS
		void window_close_callback(GLFWwindow* win);
		void window_size_callback(GLFWwindow* win, int winx, int winy);
		void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
		void mouse_callback(GLFWwindow* win, double xpos, double ypos);
		void mouse_button_callback(GLFWwindow* win, int button, int action, int mods);
		void scroll_callback(GLFWwindow* win, double xoffset, double yoffset);
		void joystick_callback(int jid, int event);
		void createShaderProgram();
		void createBufferObjects();
		void destroyBufferObjects();
		void destroyShaderProgram();
		void drawScene(double elapsed_sec);
		
};