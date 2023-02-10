/* ======================================================================== */
/*!
 * \file            ChangeValue.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Generic command for changing a value.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ChangeValue_BARRAGE_H
#define ChangeValue_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Serialization/DataWrapper.hpp>

namespace Barrage
{
  //! Generic command for changing a value
  class ChangeValue : public Command
  {
    class Writer
    {
      public:
        /**************************************************************/
        /*!
          \brief
            Writer base class constructor. Writers are used to save values
            and types so they can be written when the command is executed
            or undone.

          \param value
            The raw data to be written to.
        */
        /**************************************************************/
        Writer(DataWrapper value);

        /**************************************************************/
        /*!
          \brief
            Base class destructor.
        */
        /**************************************************************/
        virtual ~Writer() = default;
        
        /**************************************************************/
        /*!
          \brief
            Writes the original value to the value object.
        */
        /**************************************************************/
        virtual void WriteOldValue() = 0;

        /**************************************************************/
        /*!
          \brief
            Writes the value set by SetValue() to the value object.
        */
        /**************************************************************/
        virtual void WriteNewValue() = 0;

      protected:
        DataWrapper value_; //!< wraps the raw value
    };
    
    template <typename T>
    class WriterT : public Writer
    {
      public:
        /**************************************************************/
        /*!
          \brief
            Generic writer constructor. Writers are used to save values
            and types so they can be written when the command is executed
            or undone.

          \param value
            The raw data to be written to.
        */
        /**************************************************************/
        WriterT(DataWrapper value, const T& oldValue, const T& newValue);

        /**************************************************************/
        /*!
          \brief
            Writes the original value to the value object.
        */
        /**************************************************************/
        void WriteOldValue() override;

        /**************************************************************/
        /*!
          \brief
            Writes the value set by SetValue() to the value object.
        */
        /**************************************************************/
        void WriteNewValue() override;

      private:
        T oldValue_; //!< the original value
        T newValue_; //!< the value set by SetValue()
    };

    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the ChangeValue command.

        \param valueName
          The name of the value to be edited.

        \param valuePointer
          The pointer to the value being edited.
      */
      /**************************************************************/
      ChangeValue(const std::string& valueName, rttr::variant valuePointer);

      /**************************************************************/
      /*!
        \brief
          Deallocates writer.
      */
      /**************************************************************/
      ~ChangeValue();

      /**************************************************************/
      /*!
        \brief
          Gets the value this command changes.

        \tparam T
          The type of the value. 

        \return 
          Returns the value.
      */
      /**************************************************************/
      template <typename T>
      T GetValue();

      /**************************************************************/
      /*!
        \brief
          Queues a value to be set. The value is not actually set
          until Execute() is called.

        \tparam T
          The type of the value.

        \param newValue
          The updated value to set.

        \return
          Returns the value.
      */
      /**************************************************************/
      template <typename T>
      void SetValue(const T& newValue);

      /**************************************************************/
      /*!
        \brief
          Gets the name of the value.

        \return
          Returns the name of the value.
      */
      /**************************************************************/
      const std::string& GetValueName();

      /**************************************************************/
      /*!
        \brief
          Enables or disables undo chaining. (See Command.hpp for
          explanation of undo chaining.)

        \param enable
          If true, enables undo chaining. If false, disables undo
          chaining. (Disabled by default.)
      */
      /**************************************************************/
      void SetChainUndo(bool enable);

      /**************************************************************/
      /*!
        \brief
          Indicates whether SetValue() has been called.

        \return
          Returns true if SetValue() has been called at least once, 
          returns false otherwise.
      */
      /**************************************************************/
      bool ValueWasSet();

    private:
      /**************************************************************/
      /*!
        \brief
          Performs the value change.

        \return
          Returns true if the value change was successful, returns
          false otherwise.
      */
      /**************************************************************/
      bool Execute() override;

      /**************************************************************/
      /*!
        \brief
          Reverses the value change performed by Execute().
      */
      /**************************************************************/
      void Undo() override;

    private:
      rttr::variant valuePointer_; //!< Pointer to the value being edited
      DataWrapper value_;          //!< Represents the value being edited
      std::string valueName_;      //!< Name of the value
      Writer* writer_;             //!< Contains the old/new values and writes them as needed
  };
}

#include "ChangeValue.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ChangeValue_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////