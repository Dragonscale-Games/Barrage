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
#include <rttr/registration>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>
#include <fstream>

struct Testing
{
  Testing() {};
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

void fire(void)
{
  // Set up rttr typing.
  rttr::type testingT = rttr::type::get<Testing>();
  rttr::property aT = testingT.get_property("a");
  rttr::property bT = testingT.get_property("b");
  // Set up the object beingn reflected.
  Testing t;
  t.a = glm::vec3(1.0f);
  t.b = glm::vec2(1.0f);
  // Write our document.
  rttr::variant a = aT.get_value(t);
  rttr::variant b = bT.get_value(t);
  rapidjson::Document d;

  d.SetObject();
  rapidjson::Value& global = d.GetObject();
  global.AddMember("a", rapidjson::Value(a.to_float()), d.GetAllocator());
  global.AddMember("b", rapidjson::Value(b.to_float()), d.GetAllocator());
  
  std::ofstream writtenJson("sample.json");
  rapidjson::OStreamWrapper ostream(writtenJson);
  rapidjson::Writer<rapidjson::OStreamWrapper> writer(ostream);
  d.Accept(writer);
}
