#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include <string>
#include <iostream>
#include <ostream>
#include <unordered_map>
#include "Mesh.h"

class RenderException : public std::runtime_error {
    public:
        RenderException( const std::string & msg ) :
            std::runtime_error(msg) { }
};
class MeshManager {
    private:
        typedef std::unordered_map<std::string,Mesh*> Map;
        Map map;

    protected:
        MeshManager();

    public:
        static MeshManager* instance();
        Mesh* get(std::string name);
        void add(std::string name, Mesh* mesh);
        void deleteMeshes();
};

#endif