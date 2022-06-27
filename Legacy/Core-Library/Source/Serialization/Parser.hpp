/* ======================================================================== */
/*!
 * \file            Parser.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Allows loading and saving of JSON files into/from an in-memory document.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Parser_BARRAGE_H
#define Parser_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <rapidjson/document.h>

namespace rj = rapidjson;

namespace Barrage
{
  //! Allows loading and saving of JSON files into/from an in-memory document
  class Parser
	{
    public:   
      Parser();

      void LoadJSON(const std::string& path);

      void SaveJSON(const std::string& path);

      rj::Document& GetRoot();

    private:
      rj::Document document_;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Parser_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////