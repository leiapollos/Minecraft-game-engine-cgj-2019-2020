#include "SceneNode.h"
//
SceneNode::SceneNode(std::string _tag) {
	parent = nullptr;
    isRoot = false;
    tag = _tag;
    object = nullptr;
}

SceneNode::~SceneNode() {
	/*if (object != nullptr) {
        delete object;
        object = 0;
    }*/
    if (!isRoot) {
        for (int i = 0; i < (int)children.size(); i++){
            delete children[i];
            children[i] = 0;
    	}
        children.clear();
    }
}


SceneNode* SceneNode::createNode(std::string tag) {
    SceneNode* child = new SceneNode(tag);
    child->setParent(this);
    children.push_back(child);
    return child;
}
void SceneNode::setObject(GameObject* _object){
	object = _object;
}
void SceneNode::setMesh(Mesh* _mesh){
	object->setMesh(*_mesh);
}

void SceneNode::setParent(SceneNode* _parent){
	parent = _parent;
}



Matrix4 SceneNode::getModelMatrix() {
	return object->getModelMatrix();
}

void SceneNode::setModelMatrix(const Matrix4& m) {
	object->setModelMatrix(m);
}

/*void SceneNode::translateNode(const Vector3& t){
	object->translateObj(t);
}

void SceneNode::rotateNode(const Quaternion& r){
	object->rotateObj(r);
}

void SceneNode::scaleNode(const Vector3& s){
	object->scaleObj(s);
}*/

void SceneNode::setTag(std::string _tag){
	tag = _tag;
}

std::string SceneNode::getTag(){
	return tag;
}

/*void SceneNode::applyMatrixToChildren(const Vector3& t, const Quaternion& r, const Vector3& s) {
	if (!children.empty()) {
        for (int i = 0; i < (int)children.size(); i++) {
            children[i]->translateNode(t);
            children[i]->rotateNode(r);
            children[i]->scaleNode(s);
        }
    }
}*/

void SceneNode::draw(ShaderProgram* program, ICamera* cam) {
	if (object == nullptr) {
        throw RenderException("No Object set for the node " + tag);
    }
    if (program == nullptr) {
        throw RenderException("Could not find any shader program");
    }
    //float* modelMatrix = this->getModelMatrix().data;
    if (!isRoot)
    	object->draw(program, parent->getModelMatrix());
    else
    	object->draw(program, cam);//, parent->getModelMatrix());
    /*GLint uniformID = program->getUniformLocation("ViewMatrix");
	glUniformMatrix4fv(uniformID,1,GL_FALSE,camera->getViewMatrix().data);
	uniformID = program->getUniformLocation("ProjectionMatrix");
	glUniformMatrix4fv(uniformID,1,GL_FALSE,camera->proj->data);*/
    if (!children.empty()) {
        for (int i = 0; i < (int)children.size(); i++) {
            children[i]->draw(program, cam);
        }
    }
}