/* ======================================================================== */
/*!
 * \file            Logger.hpp
 * \par             Barrage Engine
 * \author          David Wong Cascante
 * \par             dragonscale.games\@gmail.com

 * \brief
   The logger the engine uses to print debugging statements
   to different output streams.

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Logger_BARRAGE_H
#define Logger_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <spdlog/spdlog.h>
#include <spdlog/common.h>
#include <spdlog/formatter.h>

//! The engine's logger.
namespace Barrage
{
  class Logger
  {
  public:
    Logger();
    void Initialize();
  private:
    //! The internal logger for the class.
    std::shared_ptr<spdlog::logger> log_;
  };
}

#endif // Logger_BARRAGE_H
