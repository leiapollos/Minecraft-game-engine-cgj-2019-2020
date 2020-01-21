#include "matrix4.h"
#include "MatrixFactory.h"
#include "Quaternion.h"
//#include "Mesh.h"
//class Mesh;

class Entity {
    public:

        Matrix4 transformation;
        Entity() : transformation  (MatrixFactory::CreateTransformMatrix(0,0,0,0,1)) {

        }
        Entity(const Matrix4& transf) : transformation(transf) {
        }

        Entity(const Vector3& pos) 
                                : transformation(MatrixFactory::CreateTransformMatrix(pos.x,pos.y,pos.z,0,1)) {
        }

        ~Entity() {};

        virtual Matrix4& getModelMatrix() {
            return transformation;
        }

        virtual void setModelMatrix(const Matrix4& transf) {
            transformation = transf;
        }


};
