/* ======================================================================== */
/*!
 * \file            SpawnRule.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A spawn rule modifies the initial values of a newly spawned object.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRule_BARRAGE_H
#define SpawnRule_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ComponentArray.hpp"
#include <rttr/rttr_enable.h>
#include <string>

namespace Barrage
{
  class Pool;
  
  //! Base class that all spawn rules should inherit from
  class SpawnRule
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the spawn rule with a given name.
      */
      /**************************************************************/
      SpawnRule(const std::string& name);
      
      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~SpawnRule() = default;

      /**************************************************************/
      /*!
        \brief
          Gets the name of the spawn rule.

        \return
          Returns the name of the spawn rule.
      */
      /**************************************************************/
      const std::string& GetName() const;

      /**************************************************************/
      /*!
        \brief
          Executes the spawn function. This is the typical spawn
          function signature.

        \param initPool
          The pool spawning the objects.

        \param destPool
          The pool the objects are being spawned into.

        \param firstObjIndex
          The index of the first newly spawned object in the
          destination pool.

        \param numNewObjects
          The number of newly spawned objects.

        \param sourceIndices
          The indices of the objects in the initPool that spawned 
          the new objects. The first source index in this vector
          corresponds to the first newly spawned object, the second
          to the second, etc.
      */
      /**************************************************************/
      virtual void Execute(Pool& initPool, Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices) = 0;

      /**************************************************************/
      /*!
        \brief
          Gets an rttr::variant representation of the spawn rule's
          data. In spawn rules that don't store data, this returns
          an empty/invalid rttr::variant.

        \return
          Returns the spawn rule's value as an rttr::variant.
      */
      /**************************************************************/
      virtual rttr::variant GetRTTRValue();

      /**************************************************************/
      /*!
        \brief
          Sets the spawn rule's data using an rttr::variant. In
          spawn rules that don't store data, this function does
          nothing.
      */
      /**************************************************************/
      virtual void SetRTTRValue(const rttr::variant& value);

    private:
      std::string name_;
  };

  typedef std::vector<std::shared_ptr<SpawnRule>> SpawnRuleList;

  //! Spawn rules that store data shared by all spawners
  template <typename T>
  class SpawnRuleT : public SpawnRule
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the spawn rule with a given name.
      */
      /**************************************************************/
      SpawnRuleT(const std::string& name);
      
      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~SpawnRuleT() = default;
      
      /**************************************************************/
      /*!
        \brief
          Gets an rttr::variant representation of the spawn rule's
          data.

        \return
          Returns the spawn rule's value as an rttr::variant.
      */
      /**************************************************************/
      rttr::variant GetRTTRValue() override;

      /**************************************************************/
      /*!
        \brief
          Sets the spawn rule's data using an rttr::variant.
      */
      /**************************************************************/
      void SetRTTRValue(const rttr::variant& value) override;

    protected:
      T data_;
  };

  class SpawnRuleWithArray : public SpawnRule
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the spawn rule with a given name.
      */
      /**************************************************************/
      SpawnRuleWithArray(const std::string& name);
      
      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~SpawnRuleWithArray() = default;

      /**************************************************************/
      /*!
        \brief
          Sets the number of elements in this spawn rule's data 
          array.

        \param capacity
          The number of elements in this spawn rule's data array.
      */
      /**************************************************************/
      virtual void SetCapacity(unsigned capacity) = 0;

      /**************************************************************/
      /*!
        \brief
          Updates the elements of the spawn rule's array to match
          the positions of still-alive spawners when some spawners
          have been destroyed.
      
        \param destructionArray
          Array of bools that tell whether each spawner is destroyed
          or not.
      */
      /**************************************************************/
      virtual void HandleDestructions(const bool* destructionArray, unsigned deadBeginIndex, unsigned aliveEndIndex) = 0;
  };

  typedef std::vector<std::shared_ptr<SpawnRuleWithArray>> SpawnRuleWithArrayList;

  //! Spawn rules that store an array of data (one element per spawner)
  template <typename T, typename A>
  class SpawnRuleTA : public SpawnRuleWithArray
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the spawn rule with a given name.
      */
      /**************************************************************/
      SpawnRuleTA(const std::string& name);

      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~SpawnRuleTA() = default;

      /**************************************************************/
      /*!
        \brief
          Gets an rttr::variant representation of the spawn rule's
          data.

        \return
          Returns the spawn rule's value as an rttr::variant.
      */
      /**************************************************************/
      rttr::variant GetRTTRValue() override;

      /**************************************************************/
      /*!
        \brief
          Sets the spawn rule's data using an rttr::variant.
      */
      /**************************************************************/
      void SetRTTRValue(const rttr::variant& value) override;

      /**************************************************************/
      /*!
        \brief
          Sets the number of elements in this spawn rule's data
          array.

        \param capacity
          The number of elements in this spawn rule's data array.
      */
      /**************************************************************/
      void SetCapacity(unsigned capacity) override;

      /**************************************************************/
      /*!
        \brief
          Updates the elements of the array to match the positions 
          of still-alive spawners when some spawners have been 
          destroyed.

        \param destructionArray
          Array of bools that tell whether each spawner is destroyed
          or not.
      */
      /**************************************************************/
      void HandleDestructions(const bool* destructionArray, unsigned deadBeginIndex, unsigned aliveEndIndex) override;

    protected:
      T data_;
      ComponentArrayT<A> dataArray_;
  };
}

#include "SpawnRule.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRule_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////