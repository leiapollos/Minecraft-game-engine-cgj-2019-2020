#include "SceneGraph.h"

SceneGraph::SceneGraph() {
    root = new SceneNode("root");
    root->isRoot = true;
}

SceneGraph::~SceneGraph() {
    for (int i = 0; i < (int)root->children.size(); i++)
        delete root->children[i];
    root->children.clear();
    delete root;
    delete camera; // We might not want this...

    root = 0;
    camera = 0;
}


SceneNode* SceneGraph::createNode(std::string tag) {
    return root->createNode(tag);
}

void SceneGraph::setCamera(ICamera* _camera){
    camera = _camera;
}

ICamera* SceneGraph::getCamera() {
    return camera;
}

SceneNode* SceneGraph::getRoot() {
    return root;
}

void SceneGraph::draw(ShaderProgram* program, ICamera* cam) {
    root->draw(program, cam);
    /*if (!root->children.empty()) {
        for (int i = 0; i < (int)root->children.size(); i++) {
            root->children[i]->draw(program);
        }
    }*/ /*else {
        throw RenderException("The graph is empty.");
    }*/
}