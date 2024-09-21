#include "../include/ResourceManager.hpp"

ResourceManager::ResourceManager() {

}

ResourceManager::ResourceManager(ResourceManager const&){

}

ResourceManager ResourceManager::operator=(ResourceManager const& rhs){
    return *this;
}

ResourceManager::~ResourceManager(){
    for(auto &i : mapper){
        SDL_FreeSurface(i.second);
    }
    mapper.clear();
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

// for perfomance as storing the suface s in the cache so as to not go through each time with those mapper iteration and finding in the disk

/*

ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager instance;
    return instance;
}

SDL_Surface* ResourceManager::GetSurface(const std::string& filepath) {
    auto search = mapper.find(filepath);
    if (search != mapper.end()) {
        // If the surface is found, add it to the cached set
        cachedSurfaces.insert(search->second);
        return search->second;
    } else {
        SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
        if (surface != nullptr) {
            mapper[filepath] = surface;
            // Add newly loaded surface to the cached set
            cachedSurfaces.insert(surface);
        }
        return surface;
    }
}

*/

void ResourceManager::ReleaseSurface(const std::string& filepath) {
    auto search = mapper.find(filepath);
    if (search != mapper.end()) {
        SDL_Surface* surface = search->second;
        // Remove surface from the cached set
        CachedSurfaces.erase(surface);
        SDL_FreeSurface(surface);
        mapper.erase(search);
    }
}

void ResourceManager::ClearCacheSurface() {
    for (auto surface : CachedSurfaces) {
        SDL_FreeSurface(surface);
    }
    CachedSurfaces.clear();
}
