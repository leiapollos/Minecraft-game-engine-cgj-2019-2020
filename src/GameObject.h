#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Entity.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
#include "Mesh.h"
#include "MatrixFactory.h"
#include "Physics/AABB.h"
#include "World/WorldConstants.h"
#include "ICamera.h"
class GameObject : public Entity {
	public:
        Mesh mesh;
        AABB m_aabb;
        GameObject() : Entity(), m_aabb({CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE}) {
        	
        };

		GameObject(const Vector3& pos) 
						: Entity(pos)
						, m_aabb({CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE}) {
        	m_aabb.update({pos.x, pos.y,
                   pos.z});
        };


        //GameObject(Mesh& _mesh) : Entity (), mesh(_mesh) {
            //setMesh(_mesh);
        //};

		//GameObject(Mesh& _mesh, const Matrix4& transf) : Entity(transf), mesh(_mesh) {//const Vector3& trans, const Quaternion& rotation) : Entity(trans, rotation) {
			//setMesh(_mesh);
		//};


		//GameObject(const Matrix4& transf) : Entity(transf) {//const Vector3& trans, const Quaternion& rotation) : Entity(trans, rotation) {
		//};

		virtual ~GameObject() = default;

		virtual void draw(){
			mesh.draw();	
		};

		virtual void draw(ShaderProgram* sp, ICamera* camera) {

			GLint uniformID = sp->getUniformLocation("ModelMatrix");
			glUniformMatrix4fv(uniformID,1,GL_FALSE,  getModelMatrix().data);
			draw();
		};

		virtual void draw(ShaderProgram* sp, Matrix4 parent){
			GLint uniformID = sp->getUniformLocation("ModelMatrix");
			glUniformMatrix4fv(uniformID,1,GL_FALSE,  (parent*getModelMatrix()).data);
			draw();
		};

		void setMesh(Mesh& _mesh) {
			mesh = _mesh;
		}

		void resetMesh() {
			mesh.resetMesh();
		}
		
	private:
		
};
#endif