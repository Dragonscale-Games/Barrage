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
  constexpr int BEHAVIOR_BEGIN = -1;
  constexpr int BEHAVIOR_END = -2;
  
  class BehaviorNode;

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

  constexpr size_t MAX_PARALLEL_NODE_CHILDREN = 4;

  enum class BehaviorNodeType
  {
    Action,
    Composite,
    Decorator,
    Parallel
  };

  class BehaviorState
  {
    public:
      enum class State
      {
        Running,
        Transfer,
        Success,
        Failure
      };
      
      State GetState();

      unsigned GetNextNodeIndex();

      static BehaviorState Running();

      static BehaviorState Transfer(unsigned nextNodeIndex);

      static BehaviorState Success();

      static BehaviorState Failure();
    
    private:
      BehaviorState(State state, unsigned nextNodeIndex = 0);

    private:
      State state_;
      unsigned nextNodeIndex_;
  };

  struct BehaviorNodeInfo
  {
    BehaviorNodeList& tree_;
    Space& space_;
    Pool& pool_;
    unsigned objectIndex_;

    inline BehaviorNodeInfo(
      BehaviorNodeList& tree,
      Space& space,
      Pool& pool,
      unsigned objectIndex
    ) :
      tree_(tree),
      space_(space),
      pool_(pool),
      objectIndex_(objectIndex)
    {
    }
  };

  class BehaviorNode
  {
    public:
      BehaviorNode(const std::string& name, BehaviorNodeType type);

      virtual ~BehaviorNode() = default;

      virtual std::shared_ptr<BehaviorNode> Clone() const = 0;

      const std::string& GetName() const;

      int GetParentIndex() const;

      BehaviorNodeType GetType() const;

      const std::vector<int>& GetChildIndices() const;

      void SetParentIndex(int index);

      void AddChildIndex(int index);

      virtual void OnBegin(BehaviorNodeInfo& info);

      virtual BehaviorState Execute(BehaviorNodeInfo& info);

      virtual void OnChildFinish(BehaviorNodeInfo& info, BehaviorState::State result, int childIndex);

      virtual rttr::variant GetRTTRValue();

      virtual void SetRTTRValue(const rttr::variant& value);

      virtual bool HasArray();

    protected:
      int parentIndex_;
      std::vector<int> childIndices_;
      BehaviorNodeType type_;
      std::string name_;
  };

  template <typename T>
  class BehaviorNodeT : public BehaviorNode
  {
    public:
      BehaviorNodeT(const std::string& name, BehaviorNodeType type);

      std::shared_ptr<BehaviorNode> Clone() const override;

      rttr::variant GetRTTRValue() override;

      void SetRTTRValue(const rttr::variant& value) override;

    protected:
      T data_;
  };

  class BehaviorNodeWithArray : public BehaviorNode
  {
    public:
      BehaviorNodeWithArray(const std::string& name, BehaviorNodeType type);

      virtual void SetCapacity(unsigned capacity) = 0;

      virtual void HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex) = 0;

      bool HasArray() override;
  };

  template <typename T, typename A>
  class BehaviorNodeTA : public BehaviorNodeWithArray
  {
    public:
      BehaviorNodeTA(const std::string& name, BehaviorNodeType type);

      std::shared_ptr<BehaviorNode> Clone() const override;

      rttr::variant GetRTTRValue() override;

      void SetRTTRValue(const rttr::variant& value) override;

      void SetCapacity(unsigned capacity) override;

      void HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex) override;

    protected:
      T data_;
      ComponentArrayT<A> dataArray_;
  };
}

#include "BehaviorNode.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorNode_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////