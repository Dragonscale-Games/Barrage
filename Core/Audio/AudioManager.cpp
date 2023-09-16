/* ======================================================================== */
/*!
 * \file            AudioManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Manages game audio.
 */
 /* ======================================================================== */

#include "AudioManager.hpp"

namespace Barrage
{
  AudioManager::AudioManager() : audioEngine_(), sounds_()
  {
  }

  void AudioManager::Initialize()
  {
    audioEngine_.init();
  }

  void AudioManager::Shutdown()
  {
    sounds_.clear();
    audioEngine_.deinit();
  }

  void AudioManager::PlaySound(const std::string& name)
  {
    if (sounds_.count(name) == 0)
    {
      std::string sound_path = "Assets/Audio/" + name + ".wav";
      sounds_[name].load(sound_path.c_str());
    }

    audioEngine_.play(sounds_.at(name));
  }
}
