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

#include <string_view>

//! The engine's logger.
namespace Barrage
{
  class Logger
  {
  public:
    //! Creates a logger going to the standard output.
    Logger();
    //! Initializes the logger to output towards a character
    //! stream.
    void AddFileLogger(const std::string_view& filepath);
  private:
    //! A single set of log instances to users can send the same messages
    //! to all logs.
    static std::vector<std::shared_ptr<spdlog::logger> > logs_;
    //! The internal logger for the class.
    std::shared_ptr<spdlog::logger> log_;
  };
}

#endif // Logger_BARRAGE_H
