#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>

class ResourceManager
{
public:
    ResourceManager(){};

    // a singleton pattern so no use of copy and assignment operator
    ResourceManager(ResourceManager const &) = delete;
    ResourceManager operator=(ResourceManager const &) = delete;

    ~ResourceManager()
    {
        for (auto &i : fileMap)
        {
            SDL_FreeSurface(i.second); // clearing the surfaces
        }
        fileMap.clear(); // clearing the strings or key
    }

    static ResourceManager &GetInstance()
    {
        static ResourceManager *s_instance = new ResourceManager;
        return *s_instance;
    }

    SDL_Surface *GetSurface(std::string filepath)
    {
        auto search = fileMap.find(filepath.c_str());
        if (search != fileMap.end())
        {
            // found
            return fileMap[filepath];
        }
        else
        {
            std::cout << "Allocated only once" << std::endl;
            SDL_Surface *surface = SDL_LoadBMP(filepath.c_str());
            fileMap.insert(std::make_pair(filepath, surface));
            return fileMap[filepath];
        }
        return nullptr;
    }

    void ReleaseSurface(std::string filepath)
    {
        auto search = fileMap.find(filepath.c_str());
        if (search != fileMap.end())
        {
            SDL_Surface *surfACE = search->second;
            SDL_FreeSurface(surfACE);
            fileMap.erase(filepath);
        }
    }

private:
    std::unordered_map<std::string, SDL_Surface *> fileMap;
    // fileMap Mapper;
};

#endif