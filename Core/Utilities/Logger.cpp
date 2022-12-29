/* ======================================================================== */
/*!
 * \file            Logger.cpp
 * \par             Barrage Engine
 * \author          David Wong Cascante
 * \par             dragonscale.games\@gmail.com

 * \brief
   The logger the engine uses to print debugging statements
   to different output streams.

 */
 /* ======================================================================== */

#include "Logger.hpp"
#include <spdlog/sinks/basic_file_sink.h>

namespace Barrage
{
  Logger::Logger()
  {
  }

  void Logger::Initialize()
  {
    using spdlog::level::level_enum;
    using spdlog::sinks::basic_file_sink_st;

    log_ = spdlog::create<basic_file_sink_st>("Default", "engine_log.txt");
    log_->set_level(level_enum::debug);
    log_->enable_backtrace(10u);
    log_->debug("Initialized the Logger class.");
    log_->dump_backtrace();
    log_->flush();
  }
}
