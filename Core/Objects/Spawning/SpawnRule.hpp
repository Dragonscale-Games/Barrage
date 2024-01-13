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

#include "Objects/Components/ComponentArray.hpp"
#include <rttr/rttr_enable.h>
#include <string>

namespace Barrage
{
  class Space;
  class Pool;

  struct GroupInfo
  {
    unsigned numObjectsPerGroup_; // all objects in a group have the same value
    unsigned numGroups_;          // each group has a different value
    unsigned numLayerCopies_;     // each layer copy should have the same groups and objects

    inline GroupInfo() : numObjectsPerGroup_(1), numGroups_(0), numLayerCopies_(1) {}
    inline GroupInfo(unsigned numGroups) : numObjectsPerGroup_(1), numGroups_(numGroups), numLayerCopies_(1) {}
  };

  struct SpawnRuleInfo
  {
    Pool& sourcePool_;
    Pool& destinationPool_;
    Space& space_;
    unsigned startIndex_;
    unsigned sourceIndex_;
    GroupInfo& groupInfo_;

    inline SpawnRuleInfo(
      Pool& sourcePool, 
      Pool& destinationPool, 
      Space& space, 
      unsigned startIndex, 
      unsigned sourceIndex,
      GroupInfo& groupInfo
    ) : 
      sourcePool_(sourcePool),
      destinationPool_(destinationPool),
      space_(space),
      startIndex_(startIndex),
      sourceIndex_(sourceIndex),
      groupInfo_(groupInfo)
    {
    }
  };

  enum class SpawnRuleStage
  {
    SIZE_RULE,
    VALUE_RULE
  };

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
          Creates a spawn rule that's a deep copy of this spawn rule.

        \return
          Returns a pointer to the new spawn rule.
      */
      /**************************************************************/
      virtual std::shared_ptr<SpawnRule> Clone() const = 0;

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
          Executes the spawn rule for all objects from a single 
          spawner.

        \param info
          Contains information about the current spawn (source pool,
          destination pool, number of objects spawned, etc).
      */
      /**************************************************************/
      virtual void Execute(SpawnRuleInfo& info);

      void ExecuteFull(
        Pool& sourcePool,
        Pool& destinationPool,
        Space& space,
        unsigned startIndex,
        std::vector<unsigned>& sourceIndices,
        ComponentArrayT<GroupInfo>& groupInfoArray
      );

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

      /**************************************************************/
      /*!
        \brief
          Checks whether the spawn rule has a component array that
          needs to be updated when objects are destroyed.

        \return
          Returns true if the spawn rule has an array, returns false
          otherwise.
      */
      /**************************************************************/
      virtual bool HasArray();

    protected:
      /**************************************************************/
      /*!
        \brief
          Helper function for calculating the index of the object
          being modified.

        \param groupInfo
          Information about the spawn layer's group and layer copy
          sizes.

        \param startIndex
          The index of the first object produced by the spawner.

        \param objectNumber
          In a group, the number of the current object (starting at
          zero).

        \param groupNumber
          In a layer copy, the number of the current group (starting
          at zero).

        \param layerCopyNumber
          The number of the current layer copy.

        \return
          Returns the index of the object to modify.
      */
      /**************************************************************/
      static unsigned CalculateDestinationIndex(
        SpawnRuleInfo& info,
        unsigned objectNumber,
        unsigned groupNumber,
        unsigned layerCopyNumber
      );
    
    private:
      std::string name_;
  };

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
          Creates a spawn rule that's a deep copy of this spawn rule.

        \return
          Returns a pointer to the new spawn rule.
      */
      /**************************************************************/
      std::shared_ptr<SpawnRule> Clone() const override;

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

        \param writeIndex
          The index of the first dead object.

        \param endIndex
          One past the index of the last object that could be alive.
      */
      /**************************************************************/
      virtual void HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex) = 0;

      /**************************************************************/
      /*!
        \brief
          Checks whether the spawn rule has a component array that
          needs to be updated when objects are destroyed.

        \return
          Returns true if the spawn rule has an array, returns false
          otherwise.
      */
      /**************************************************************/
      bool HasArray() override;
  };

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
          Creates a spawn rule that's a deep copy of this spawn rule.

        \return
          Returns a pointer to the new spawn rule.
      */
      /**************************************************************/
      std::shared_ptr<SpawnRule> Clone() const override;

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
      void HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex) override;

    protected:
      T data_;
      ComponentArrayT<A> dataArray_;
  };

  class GenericSpawnRule
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Default/conversion constructor. Wraps a nullptr.

        \param nullPointer
          Dummy parameter. Allows default parameter conversion like:
            Foo(GenericSpawnRule pointer = nullptr)
      */
      /**************************************************************/
      GenericSpawnRule(std::nullptr_t nullPointer = nullptr);

      /**************************************************************/
      /*!
        \brief
          Constructs this GenericSpawnRule from a shared pointer. The
          shared pointer is stored internally (wrapped).

        \param ptr
          The shared pointer to wrap.
      */
      /**************************************************************/
      GenericSpawnRule(std::shared_ptr<SpawnRule> ptr);

      /**************************************************************/
      /*!
        \brief
          Copy constructor for deep copying a spawn rule pointer.

        \param other
          The spawn rule pointer to deep copy.
      */
      /**************************************************************/
      GenericSpawnRule(const GenericSpawnRule& other);

      /**************************************************************/
      /*!
        \brief
          Copy assignment operator for deep copying a spawn rule
          pointer.

        \param other
          The spawn rule pointer to deep copy.
      */
      /**************************************************************/
      GenericSpawnRule& operator=(const GenericSpawnRule& other);

      /**************************************************************/
      /*!
        \brief
          Move constructor. Transfers ownership of the managed
          object from the source spawn rule pointer.

        \param other
          The spawn rule pointer to move.
      */
      /**************************************************************/
      GenericSpawnRule(GenericSpawnRule&& other) noexcept;

      /**************************************************************/
      /*!
        \brief
          Move assignment operator. Transfers ownership of the
          managed object from the source spawn rule pointer.

        \param other
          The spawn rule pointer to move.
      */
      /**************************************************************/
      GenericSpawnRule& operator=(GenericSpawnRule&& other) noexcept;

      /**************************************************************/
      /*!
        \brief
          Arrow operator overload.

        \return
          Returns the underlying spawn rule as a pointer.
      */
      /**************************************************************/
      SpawnRule* operator->() const;

      /**************************************************************/
      /*!
        \brief
          Star operator overload.

        \return
          Returns the underlying spawn rule as a reference.
      */
      /**************************************************************/
      SpawnRule& operator*() const;

      /**************************************************************/
      /*!
        \brief
          Bool conversion operator. Allows easy nullptr checks.
      */
      /**************************************************************/
      operator bool() const noexcept;

      /**************************************************************/
      /*!
        \brief
          Gets the underlying shared pointer for this object.

        \return
          Returns the shared pointer.
      */
      /**************************************************************/
      std::shared_ptr<SpawnRule> Get();

    private:
      std::shared_ptr<SpawnRule> ptr_;
  };

  using SpawnRuleList = std::vector<GenericSpawnRule>;
}

#include "SpawnRule.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRule_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////