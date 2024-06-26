#include "../include/ResourceManager.hpp"

ResourceManager::ResourceManager() {

}

ResourceManager::ResourceManager(ResourceManager const&){

}

ResourceManager ResourceManager::operator=(ResourceManager const& rhs){
    return *this;
}

ResourceManager& ResourceManager::GetInstance(){
    static ResourceManager* s_instance = new ResourceManager;
    return *s_instance;
}

SDL_Surface* ResourceManager::GetSurface(std::string filepath){
    auto search = mapper.find(filepath);
    if(search != mapper.end()){
        return mapper[filepath];
    }else{
        std::cout << "Allocated only once" << std::endl;
        SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
        mapper.insert(std::make_pair(filepath,surface));
        return mapper[filepath];
    }
    return nullptr;

}

