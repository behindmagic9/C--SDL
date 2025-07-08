#ifndef SOUND_HPP
#define SOUND_HPP

#include<SDL2/SDL.h>
#include<string>


class ISound{
public:
    virtual ~ISound() {};
    virtual void PlaySound() = 0;
    virtual void StopSound() = 0;
};

class Sound : public ISound {
public:

    Sound(std::string filepath);

    ~Sound();

    void PlaySound();

    void StopSound();

    void SetUpDevice();

private :
// device the sound will be payed on
// Note : This could be moved to some configuration
// i.e a higher level 'Audio class Manager'
    SDL_AudioDeviceID m_device;

    // properties of wave file tha is loaded
    SDL_AudioSpec m_audioSpec;
    Uint8* m_waveStart;
    Uint32 m_waveLength;
};

#endif