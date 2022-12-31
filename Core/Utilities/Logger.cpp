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
    spdlog::flush_every(std::chrono::seconds(3));
  }

  void Logger::AddFileLogger(const std::string_view& filepath)
  {
    using spdlog::level::level_enum;
    using spdlog::sinks::basic_file_sink_mt;

    log_ = spdlog::create<basic_file_sink_mt>(filepath.data(), filepath.data(), true);
    log_->set_level(level_enum::debug);
    log_->enable_backtrace(32u);
    log_->debug("Initialized the Logger class.");
  }
}
