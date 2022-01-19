/* ======================================================================== */
/*!
 * \file            template.cxx
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc@gmail.com

 * \brief
   Tests the compilation for all third party libraries.
 */
/* ======================================================================== */

/* ======================================================================== */
/* Includes */
/* ======================================================================== */
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <glm/glm.hpp>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>

#include <Refureku/Object.h>

#include <fstream>

/*

struct Testing
{
  Testing() : a(0), b(0) {};
  glm::vec3 a;
  glm::vec2 b;
};

RTTR_REGISTRATION
{
  rttr::registration::class_<Testing>("Testing")
    .constructor<>()
    .property("a", &Testing::a)
    .property("b", &Testing::b);
}
*/

void fire(void)
{
  /*
  // Set up the object beingn reflected.
  Testing t;
  t.a = glm::vec3(1.0f);
  t.b = glm::vec2(1.0f);
  
  rapidjson::Document d;
  d.SetObject();
  rapidjson::Value& global = d.GetObject();
  
  std::ofstream writtenJson("sample.json");
  rapidjson::OStreamWrapper ostream(writtenJson);
  rapidjson::Writer<rapidjson::OStreamWrapper> writer(ostream);
  d.Accept(writer);
  */
}
