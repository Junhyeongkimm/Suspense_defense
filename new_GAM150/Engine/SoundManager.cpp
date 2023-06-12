#include "SoundManager.h"
#include "Engine.h"



void CS230::SoundManager::Load(std::string file_path)
{
    std::map<std::string, sf::SoundBuffer*>::iterator iter;
    iter = sounds.find(file_path);
    if (iter != sounds.end())
    {
        if (sound1.getStatus() != sf::SoundSource::Playing)
        {
            sound1.setBuffer(*iter->second);
            sound1.play();
        }
        else if (sound1.getStatus() == sf::SoundSource::Playing && sound2.getStatus() != sf::SoundSource::Playing)
        {
            sound2.setBuffer(*iter->second);
            sound2.play();
        }
        else if (sound1.getStatus() == sf::SoundSource::Playing && sound2.getStatus() == sf::SoundSource::Playing)
        {
            sound1.stop();
            sound1.setBuffer(*iter->second);
            sound1.play();
        }

    }
    else {
        Engine::GetLogger().LogDebug("Loading Sounds : " + file_path);
        sounds.insert(std::make_pair(file_path, new sf::SoundBuffer{}));
        iter = sounds.find(file_path);
        (*iter).second->loadFromFile(file_path);
    }
}

void CS230::SoundManager::Unload()
{
    for (auto iter = sounds.begin(); iter != sounds.end(); ++iter)
    {
        delete iter->second;
    }
    std::map<std::string, sf::SoundBuffer*> forSwap;
    sounds.clear();
    sounds.swap(forSwap);
}