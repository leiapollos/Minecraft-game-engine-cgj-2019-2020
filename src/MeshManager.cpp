#include "MeshManager.h"

MeshManager::MeshManager() {}
MeshManager* MeshManager::instance() {
    static MeshManager manager;
    return &manager;
}

Mesh* MeshManager::get(std::string name) {
    Map::iterator it;
    it = map.find(name);
    //map[name]->print();
    if (it == map.end()){
        throw(RenderException("No mesh called " + name + " found."));
    }

    return map[name];
}

void MeshManager::add(std::string name, Mesh* mesh){
    Map::iterator it;
    it = map.find(name);
    if (it != map.end()){
        std::cout << "Mesh already exists, replacing it..." << std::endl;
    }
    map[name] = mesh;
}

void MeshManager::deleteMeshes(){
    Map::iterator it = map.begin();
    Mesh* beg;
    while (it != map.end()) {
        beg = it->second;
        if (beg != NULL)
            delete beg;
        map.erase(it);
        it = map.begin();
    }
}
