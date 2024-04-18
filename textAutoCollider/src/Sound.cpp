#include "../include/Sound.hpp"
#include<iostream>

    Sound::Sound(std::string filepath){ 
    if(SDL_LoadWAV(filepath.c_str(), &m_audioSpec , &m_waveStart , &m_waveLength)==nullptr)
       {
        std::cerr << "Sound loading error : " << SDL_GetError() << std::endl;
       } 
    }

    Sound::~Sound(){
        SDL_FreeWAV(m_waveStart);
        SDL_CloseAudioDevice(m_device);
    }

    void Sound::PlaySound(){
        int Status = SDL_QueueAudio(m_device , m_waveStart,m_waveLength);
        SDL_PauseAudioDevice(m_device,0);
    }

    void Sound::StopSound(){
        SDL_PauseAudioDevice(m_device,1);
    }

    void Sound::SetUpDevice(){ // 0 for not recording 1 for recording 
    // first nullptr mean assging default and by itself 
    // then the aduio spec 
    // then for getting that infomration stored of spec
    // allow chanegs or not
        m_device = SDL_OpenAudioDevice(nullptr,  0 , &m_audioSpec,nullptr , SDL_AUDIO_ALLOW_ANY_CHANGE );

        if(0 == m_device){
            std::cerr << "SOund device error" << SDL_GetError() << std::endl;
        }
    }

