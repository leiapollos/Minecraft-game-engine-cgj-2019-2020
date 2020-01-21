#include "GameManager.h"

GameManager::GameManager() : persM(MatrixFactory::Perspective(math::toRadians(90.0f),1280.0f/740.0f,0.1f,2000.0f)) {
    BlockDatabase::get();
    for (int i = 0; i < 349; ++i) {
        pressed[i] = 0;
    }
    projM = &persM;
    srand ((unsigned int)time(NULL));
    skyboxShader = new ShaderProgram();
    createShaderProgram();
    createBufferObjects();
}


GameManager::~GameManager() {
    destroyShaderProgram();
    destroyBufferObjects();
    MeshManager::instance()->deleteMeshes();

}

void GameManager::update(double elapsed_sec, GLFWwindow* win) {
    int width, height;
    deltaTime += (float)elapsed_sec;
    ICamera* cam = scenegraph->getCamera();
    
    if (pressed[GLFW_KEY_A]) {
        cam->computeKeyboardInputs(ICamera::LEFT,(float)elapsed_sec);
    }
    else if(pressed[GLFW_KEY_S]) {
        cam->computeKeyboardInputs(ICamera::BACKWARD,(float)elapsed_sec);
    }
    else if (pressed[GLFW_KEY_D]) {
        cam->computeKeyboardInputs(ICamera::RIGHT,(float)elapsed_sec);
    }
    else if (pressed[GLFW_KEY_W]){
        cam->computeKeyboardInputs(ICamera::FORWARD,(float)elapsed_sec);
    }
    cam->update();
    world->update((float)elapsed_sec);

    glfwGetWindowSize(win, &width, &height);
    float aspect = (float)width / (float)height;
    persM = MatrixFactory::Perspective(math::toRadians(90.0f),aspect,0.1f,2000.0f);
    
}
// CALLBACKS

void GameManager::window_close_callback(GLFWwindow* win) {
    //destroyBufferObjects();
    std::cout << "closing..." << std::endl;
}

void GameManager::window_size_callback(GLFWwindow* win, int winx, int winy) {
    //std::cout << "size: " << winx << " " << winy << std::endl;
    glViewport(0, 0, winx, winy);
}

void GameManager::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS)
        pressed[key] = true;
    else if(action == GLFW_RELEASE) {
        pressed[key] = false;
    }
    
    //std::cout << "key: " << key << " " << scancode << " " << action << " " << mods << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
        window_close_callback(win);
    }
    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		ScreenShot* s = new ScreenShot();
		bool saved = s->createScreenShot();
		if (!saved)
			std::cout << "NOOOOO\n";
        delete s;
    }
}

void GameManager::mouse_callback(GLFWwindow* win, double xpos, double ypos) {
    //std::cout << "mouse: " << xpos << " " << ypos << std::endl;
    
    ICamera* cam = scenegraph->getCamera();
    if (pressed[GLFW_MOUSE_BUTTON_1]){
        if (!cam->initiation)
            cam->setMousePosition(Vector2((float)xpos,(float)ypos));
        else
            cam->mousePosition = Vector2((float)xpos,(float)ypos);
        cam->initiation = true;
    }
    else 
        cam->initiation = false;
    cam->computeMouseMovement((float)xpos,(float)ypos);
}

void GameManager::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
    //std::cout << "button: " << button << " " << action << " " << mods << std::endl;
    if(action == GLFW_PRESS)
        pressed[button] = true;
    else if(action == GLFW_RELEASE){
        pressed[button] = false;
    }
}

void GameManager::scroll_callback(GLFWwindow* win, double xoffset, double yoffset) {
    ICamera* cam = scenegraph->getCamera();
    //std::cout << "scroll: " << xoffset << " " << yoffset << std::endl;
    cam->computeMouseScroll((float)yoffset);
}

void GameManager::joystick_callback(int jid, int event) {
    //std::cout << "joystick: " << jid << " " << event << std::endl;
}

void GameManager::drawScene(double elapsed_sec) {
    ICamera* cam = scenegraph->getCamera();

    skybox->draw(cam, projM, fmodf(deltaTime,300.0f));

	cam->setViewMatrix(cam->getViewMatrix());
	cam->setProjectionMatrix(*projM);
    
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    world->draw((float)elapsed_sec);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void GameManager::createBufferObjects() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	//
    
    skybox = new Skybox(skyboxShader);
    scenegraph = new SceneGraph();
    scenegraph->setCamera(new FPSCamera(UBO_BP));
    world = new World(scenegraph);
}

void GameManager::createShaderProgram() {
	skyboxShader->compileShaderFromFile("../src/shaders/SkyColor.vert", ShaderType::VERTEX);
	skyboxShader->compileShaderFromFile("../src/shaders/SkyColor.frag", ShaderType::FRAGMENT);
	skyboxShader->bindAttribLocation(VERTICES, "in_Position");
	skyboxShader->bindAttribLocation(TEXCOORDS, "in_TexCoords");
	skyboxShader->bindAttribLocation(NORMALS, "in_Normal");
	skyboxShader->bindAttribLocation(LIGHT,"in_CardinalLight");
	skyboxShader->link();
	skyboxShader->addUniformBlock("SharedMatrices", UBO_BP);
	skyboxShader->detach();
}

void GameManager::destroyBufferObjects() {
    delete scenegraph;
    delete world;
    delete skybox;
}

void GameManager::destroyShaderProgram() {
    delete skyboxShader;
}
