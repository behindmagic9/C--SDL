#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP
#include<iostream>
#include<string>
#include<unordered_map>
#include<SDL2/SDL.h>

class ResourceManager{
private:
    ResourceManager() ;
    ResourceManager(ResourceManager const&);
    ResourceManager operator=(ResourceManager const&) ;
public :
    static ResourceManager& GetInstance();

    SDL_Surface* GetSurface(std::string filepath);

private :
    typedef std::unordered_map<std::string ,SDL_Surface* > Mapper;
    Mapper mapper;
};


#endif