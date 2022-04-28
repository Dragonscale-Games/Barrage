/* ======================================================================== */
/*!
 *
 * \file            Reflection.hpp
 * \author          David Wong Cascante
 * \par             david.wongcascante\@digipen.edu

 * \brief
 * Provides macro functionality for any class to provide type information
 * about itself.
 * 
 * The original source for this implementation can be found in: 
 * https://technicallydeclined.com/static-reflection-and-serialization-in-c/
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Reflection_MODULE_H
#define Reflection_MODULE_H
////////////////////////////////////////////////////////////////////////////////

// ============================================================================
// Includes
// ============================================================================
#include <string>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <glm/glm.hpp>

namespace Barrage
{
  // ============================================================================
  // Classes
  // ============================================================================

  enum TypeInfoType
  {
    INFO_PRIMITIVE, INFO_VECTOR, INFO_STRUCT,
  };

  struct TypeInfo //!< A structure containing type information.
  {
    TypeInfoType infoType_;
    size_t size_;       //!< The size of the data stored in bytes.
    const char* name_;  //!< The name of the type.
    virtual ~TypeInfo() {} //!< The virtual destructor for multiple types.
  };

  struct PrimitiveInfo : public TypeInfo //!< A structure containing type information for primitive types.
  {
  };

  struct StdVectorInfo : public TypeInfo //!< A structure containig the type information for vectors.
  {
    size_t length_; //!< The size of the vector.
  };

  struct Field //!< The structure to encompase basic type information.
  {
    const TypeInfo* info_;  //!< The information about the type of the field.
    size_t offset_;         //!< The offset into the field to access the data with.
    const char* name_;      //!< The name of the property targetted.

    Field() : info_(nullptr), offset_(0), name_(nullptr)
    {
    }
  };

#define MAX_FIELDS 32 //!< The maximum number of fields available per class.
  struct StructInfo : public TypeInfo //!< A structure containing the type information of compositions.
  {
    std::vector<Field> fields_; //!< The number of fields in a structure.
    StructInfo() { fields_.resize(MAX_FIELDS); }
  };

  template <typename T>
  TypeInfo* getPrimitiveInfo();

#define DEFINE_PRIMITIVE(TYPE) \
template <> \
TypeInfo* getPrimitiveInfo<TYPE>() \
{ \
  static TypeInfo type; \
  type.infoType_ = INFO_PRIMITIVE; \
  type.size_ = sizeof(TYPE); \
  type.name_ = #TYPE; \
  return &type; \
} 

  DEFINE_PRIMITIVE(bool)
  DEFINE_PRIMITIVE(int)
  DEFINE_PRIMITIVE(long)
  DEFINE_PRIMITIVE(short)
  DEFINE_PRIMITIVE(float)
  DEFINE_PRIMITIVE(double)
  DEFINE_PRIMITIVE(uint8_t)
  DEFINE_PRIMITIVE(uint16_t)
  DEFINE_PRIMITIVE(uint32_t)
  DEFINE_PRIMITIVE(uint64_t)
  // Define a primitive for strings.
  DEFINE_PRIMITIVE(std::string)
  // Define a primitive for most linear algebra objects.
  DEFINE_PRIMITIVE(glm::vec1);
  DEFINE_PRIMITIVE(glm::vec2);
  DEFINE_PRIMITIVE(glm::vec3);
  DEFINE_PRIMITIVE(glm::vec4);
  DEFINE_PRIMITIVE(glm::ivec1);
  DEFINE_PRIMITIVE(glm::ivec2);
  DEFINE_PRIMITIVE(glm::ivec3);
  DEFINE_PRIMITIVE(glm::ivec4);
  DEFINE_PRIMITIVE(glm::uvec1);
  DEFINE_PRIMITIVE(glm::uvec2);
  DEFINE_PRIMITIVE(glm::uvec3);
  DEFINE_PRIMITIVE(glm::uvec4);
  DEFINE_PRIMITIVE(glm::mat2);
  DEFINE_PRIMITIVE(glm::mat3);
  DEFINE_PRIMITIVE(glm::mat4);

  // Define a primitive for vectors.
  template <typename T>
  TypeInfo* getVectorInfo()
  {
    static StdVectorInfo type;
    type.infoType_ = INFO_STRUCT;
    type.size_ = sizeof(std::vector<T>);
    type.name_ = "std::vector";
    type.length_ = 0;
    return &type;
  }

  class DefaultResolver
  {
  public:

    template <typename T> static char ResolverEnabler(decltype(&T::reflection));
    template <typename T> static int ResolverEnabler(...);

    template <typename T>
    struct IsReflected
    {

      enum { value = (sizeof(ResolverEnabler<T>(nullptr)) == sizeof(char)) };
      //constexpr operator bool()
      //{
      //  return (sizeof(ResolverEnabler<T>(nullptr)) == sizeof(uint8_t));
      //}
    };

    template <typename T, typename std::enable_if<IsReflected<T>::value, bool>::type = true>
    static const TypeInfo* Resolve()
    {
      return &T::reflection.info_;
    }

    template <typename T, typename std::enable_if<!IsReflected<T>::value, bool>::type = true>
    static const TypeInfo* Resolve()
    {
      return getPrimitiveInfo<T>();
    }
  };

  template <typename T>
  class TypeResolver
  {
  public:
    static const TypeInfo* Resolve()
    {
      return DefaultResolver::Resolve<T>();
    }
  };

  template <typename T>
  class TypeResolver<std::vector<T>>
  {
  public:
    static const TypeInfo* Resolve()
    {
      return getVectorInfo<T>();
    }
  };

  // ============================================================================
  // Defines
  // ============================================================================

#define BEGIN_REFLECTION(CLASS)                                                 \
  class Reflection { \
    typedef CLASS C; \
  public: \
    Reflection() { \
      enum { FIRST = __COUNTER__ }; \
      info_.size_ = sizeof(C); \
      info_.name_ = #CLASS; \
      info_.infoType_ = INFO_STRUCT; \

#define ADD_BASE(CLASS)                                                         \
      enum { FIELD##Index = __COUNTER__ - FIRST - 1}; \
      info_.fields_[FIELD##Index].info_ = TypeResolver<CLASS>::Resolve(); \
      info_.fields_[FIELD##Index].name_ = #CLASS; \
      info_.fields_[FIELD##Index].offset_ = 0; \
      end_ = &info_.fields_[FIELD##Index + 1]; \
      
#define ADD_MEMBER(FIELD)                                                       \
      enum { FIELD##Index = __COUNTER__ - FIRST - 1}; \
      info_.fields_[FIELD##Index].info_ = TypeResolver<decltype(FIELD)>::Resolve(); \
      info_.fields_[FIELD##Index].name_ = #FIELD; \
      info_.fields_[FIELD##Index].offset_ = offsetof(C, FIELD); \
      end_ = &info_.fields_[FIELD##Index + 1]; \

#define END_REFLECTION                                                   \
    } \
    const Field* GetFields() \
    { \
      return info_.fields_.data(); \
    } \
    const Field* begin() \
    { \
      return info_.fields_.data(); \
    } \
    const Field* end() \
    { \
      return end_; \
    } \
    const Field* FindField(const std::string& name) { \
      const Field* fields = GetFields(); \
      const Field* end = fields + MAX_FIELDS + 1; \
      for(size_t i = 0; i < MAX_FIELDS; ++i) { \
        const Field* field = fields + i; \
        if (field && name == field->name_) { \
          return field; \
        } \
      } \
      return nullptr; \
    } \
    template <typename T> \
    void SetMember(const Field* field, C& instance, const T& value) { \
        T* m = reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(&instance) + field->offset_); \
        *m = value; \
    } \
    template <typename T> \
    void SetMember(const std::string& name, C& instance, const T& value) { \
      const Field* field = FindField(name); \
      if(field) { \
        SetMember(field, instance, value); \
      } \
    } \
    template <typename T> \
    const T* GetMember(const Field* field, C& instance) { \
        T* m = reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(&instance) + field->offset_); \
        return m; \
    } \
    template <typename T> \
    const T* GetMember(const std::string& name, C& instance) { \
      const Field* field = FindField(name); \
      if(field) { \
        return GetMember<T>(field, instance); \
      } \
      return nullptr; \
    } \
    StructInfo info_; \
  private: \
    const Field* end_; \
  }; \
  static Reflection reflection;

#define REFLECT(CLASS) CLASS::Reflection CLASS::reflection;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Reflection_MODULE_H
////////////////////////////////////////////////////////////////////////////////
