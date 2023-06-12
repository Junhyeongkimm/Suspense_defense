#include "MusicManager.h"
#include "Engine.h"
#include "SFML/Audio.hpp"


sf::Music* CS230::MusicManager::Load(std::string file_path)
{
    std::map<std::string, sf::Music*>::iterator iter;
    iter = sounds.find(file_path);
    if (iter != sounds.end())
    {
        return iter->second;
    }
    else {
        Engine::GetLogger().LogDebug("Loading Sounds : " + file_path);
        sounds.insert(std::make_pair(file_path, new sf::Music{}));
        iter = sounds.find(file_path);
        (*iter).second->openFromFile(file_path);
        return iter->second;
    }
}

void CS230::MusicManager::Unload()
{
    for (auto iter = sounds.begin(); iter != sounds.end(); ++iter)
    {
        delete iter->second;
    }
    std::map<std::string, sf::Music*> forSwap;
    sounds.clear();
    sounds.swap(forSwap);

}