#include "../include/ResourceManager.hpp"

ResourceManager::ResourceManager() {

}

// ResourceManager::ResourceManager(ResourceManager const&){

// }

// ResourceManager ResourceManager::operator=(ResourceManager const& rhs){
//     // though its of no use as in cingleton we dont use this copy assignment operator
//     return *this;
// }

ResourceManager& ResourceManager::GetInstance(){
    static ResourceManager* s_instance = new ResourceManager;
    return *s_instance;
}

ResourceManager::~ResourceManager(){
    Mapper::iterator it = mapper.begin();
    for(;it != mapper.end();++it){
        SDL_FreeSurface(it->second);
    }
    mapper.clear();
}

SDL_Surface* ResourceManager::GetSurface(std::string filepath){
    auto search = mapper.find(filepath);
    if(search != mapper.end()){
        return mapper[filepath];
    }else{
        std::cout << "Allocated only once" << std::endl;
        SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
        if(surface == nullptr){ 
            std::cout << "file not found" << std::endl;
        }
        mapper.insert(std::make_pair(filepath,surface));
        return mapper[filepath];
    }
    return nullptr;

}

