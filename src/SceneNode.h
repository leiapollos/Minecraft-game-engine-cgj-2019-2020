#ifndef SCENENODE_H
#define SCENENODE_H

#include <string>
#include "matrix4.h"
#include "GameObject.h"
#include "ICamera.h"
#include "MeshManager.h"
class SceneNode {
    private:
        SceneNode* parent;
        std::string tag;

    public:
        std::vector<SceneNode*> children;
        GameObject* object;
        bool isRoot;

        SceneNode(std::string _tag = "");
        virtual ~SceneNode();
        SceneNode* createNode(std::string tag = "");
        void setObject(GameObject* _object);
        void setMesh(Mesh* _mesh);
        void setParent(SceneNode* _parent);
        
        Matrix4 getModelMatrix();
        void setModelMatrix(const Matrix4& m);
        /*void translateNode(const Vector3& t);
        void rotateNode(const Quaternion& r);
        void scaleNode(const Vector3& s);*/
        //void applyMatrixToChildren(const Vector3& t, const Quaternion& r, const Vector3& s);
        void setTag(std::string _tag);
        std::string getTag();
        void draw(ShaderProgram* program, ICamera* cam);
};
#endif