/* ======================================================================== */
/*!
 * \file            Parser.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

#include "stdafx.h"
#include "Parser.hpp"

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

#include <fstream>

namespace Barrage
{
  Parser::Parser() :
    document_()
  {
    document_.SetObject();
  }

  void Parser::LoadJSON(const std::string& path)
  {
    std::ifstream ifs(path);

    if (!ifs.is_open())
      return;

    rj::IStreamWrapper isw(ifs);

    document_.ParseStream(isw);
  }

  void Parser::SaveJSON(const std::string& path)
  {
    std::ofstream ofs(path);

    if (!ofs.is_open())
      return;

    rj::OStreamWrapper osw(ofs);

    rj::PrettyWriter<rj::OStreamWrapper> writer(osw);
    writer.SetFormatOptions(rapidjson::kFormatSingleLineArray);
    document_.Accept(writer);
  }

  rapidjson::Document& Parser::GetRoot()
  {
    return document_;
  }
}