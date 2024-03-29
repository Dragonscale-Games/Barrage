/* ======================================================================== */
/*!
 * \file            AudioManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Manages game audio.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef AudioManager_BARRAGE_H
#define AudioManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"
#include "soloud/soloud_sfxr.h"

#include <unordered_map>
#include <string>

namespace Barrage
{
  typedef std::unordered_map<std::string, SoLoud::Wav> SoundUmap;
  
  //! Manages game audio
  class AudioManager
  {
    public:
      AudioManager();

      void Initialize();

      void Shutdown();

      void PlaySound(const std::string& name);

    private:
      SoLoud::Soloud audioEngine_;
      SoundUmap sounds_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // AudioManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////