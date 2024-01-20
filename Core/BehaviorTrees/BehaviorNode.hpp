/* ======================================================================== */
/*!
 * \file            BehaviorNode.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorNode_BARRAGE_H
#define BehaviorNode_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Pools/Pool.hpp"

#include <string>
#include <memory>
#include <vector>

namespace Barrage
{
  enum class BehaviorState
  {
    IsRunning,
    Success,
    Failure
  };
  
  struct BehaviorNodeInfo
  {
    Space& space_;
    Pool& pool_;

    inline BehaviorNodeInfo(Space& space, Pool& pool) : space_(space), pool_(pool) {}
  };
  
  class BehaviorNode
  {
    public:
      BehaviorNode(const std::string& name, unsigned maxChildren);
      
      virtual ~BehaviorNode() = default;

      virtual std::shared_ptr<BehaviorNode> Clone() const = 0;

      const std::string& GetName() const;
      
      unsigned GetParentIndex() const;

      unsigned GetMaxChildren() const;

      void SetParentIndex(unsigned index);

      BehaviorState Execute(BehaviorNodeInfo& info);

      virtual rttr::variant GetRTTRValue();

      virtual void SetRTTRValue(const rttr::variant& value);

      virtual bool HasArray();

    private:
      unsigned parentIndex_;
      unsigned maxChildren_;
      std::vector<unsigned> childIndices_;
      std::string name_;
  };

  template <typename T>
  class BehaviorNodeT : public BehaviorNode
  {
    public:
      BehaviorNodeT(const std::string& name, unsigned maxChildren);

      std::shared_ptr<BehaviorNode> Clone() const override;

      rttr::variant GetRTTRValue() override;

      void SetRTTRValue(const rttr::variant& value) override;

    protected:
      T data_;
  };

  class BehaviorNodeWithArray : public BehaviorNode
  {
    public:
      BehaviorNodeWithArray(const std::string& name, unsigned maxChildren);

      virtual void SetCapacity(unsigned capacity) = 0;

      virtual void HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex) = 0;

      bool HasArray() override;
  };

  template <typename T, typename A>
  class BehaviorNodeTA : public BehaviorNodeWithArray
  {
    public:
      BehaviorNodeTA(const std::string& name, unsigned maxChildren);

      std::shared_ptr<BehaviorNode> Clone() const override;

      rttr::variant GetRTTRValue() override;

      void SetRTTRValue(const rttr::variant& value) override;

      void SetCapacity(unsigned capacity) override;

      void HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex) override;

    protected:
      T data_;
      ComponentArrayT<A> dataArray_;
  };

  class BehaviorNodeDeepPtr
  {
    public:
      BehaviorNodeDeepPtr(std::nullptr_t nullPointer = nullptr);

      BehaviorNodeDeepPtr(std::shared_ptr<BehaviorNode> ptr);

      BehaviorNodeDeepPtr(const BehaviorNodeDeepPtr& other);

      BehaviorNodeDeepPtr& operator=(const BehaviorNodeDeepPtr& other);

      BehaviorNodeDeepPtr(BehaviorNodeDeepPtr&& other) noexcept;

      BehaviorNodeDeepPtr& operator=(BehaviorNodeDeepPtr&& other) noexcept;

      BehaviorNode* operator->() const;

      BehaviorNode& operator*() const;

      operator bool() const noexcept;

      std::shared_ptr<BehaviorNode> Get();

    private:
      std::shared_ptr<BehaviorNode> ptr_;
  };

  using BehaviorNodeList = std::vector<BehaviorNodeDeepPtr>;
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorNode_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////