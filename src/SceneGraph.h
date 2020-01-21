#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H
#include "SceneNode.h"
#include "ShaderProgram.h"

class SceneGraph {
    private:
        SceneNode* root;
        ICamera* camera;
    public:
        SceneGraph();
        virtual ~SceneGraph();
        SceneNode* createNode(std::string tag = "");
        void setCamera(ICamera* _camera);
        ICamera* getCamera();
        SceneNode* getRoot();
        void draw(ShaderProgram* program, ICamera* cam);
};

#endif