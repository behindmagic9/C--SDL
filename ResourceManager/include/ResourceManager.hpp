#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP
#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<SDL2/SDL.h>

class ResourceManager{
private:
    ResourceManager() ;
    // copy contructor and assignemnt operator which are of no use int he singleton instance
    ResourceManager(ResourceManager const&);
    ResourceManager operator=(ResourceManager const&) ;
    ~ResourceManager() ;
public :
    static ResourceManager& GetInstance();

    SDL_Surface* GetSurface(std::string filepath);

    void ReleaseSurface(const std::string& filepath);

    void ClearCacheSurface();
private :
    std::unordered_map<std::string ,SDL_Surface* > mapper;
    //  will be shared across all instances of the class because there's only one instance of the class itself
    // becase of the static instance

    std::unordered_set<SDL_Surface*> CachedSurfaces;
};


#endif