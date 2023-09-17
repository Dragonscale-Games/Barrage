/* ======================================================================== */
/*!
 * \file            Engine.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   In charge of setting up engine modules (renderer, input, etc).
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Engine_BARRAGE_H
#define Engine_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <memory>

namespace Barrage
{
  //! The core engine class for Barrage
  class Engine
  {
    public:
      Engine(Engine const&) = delete;
      Engine(Engine&&) = delete;
      Engine& operator=(Engine const&) = delete;
      Engine& operator=(Engine&&) = delete;
      
      /**************************************************************/
      /*!
        \brief
          Gets the instance of the (singleton) engine.

        \return
          Returns a reference to the engine instance.
      */
      /**************************************************************/
      static Engine& Get();

      /**************************************************************/
      /*!
        \brief
          Initializes the engine and all its modules.
      */
      /**************************************************************/
      void Initialize();

      /**************************************************************/
      /*!
        \brief
          Shuts down the engine and all its modules.
      */
      /**************************************************************/
      void Shutdown();

    private:
      /**************************************************************/
      /*!
        \brief
          Private constructor for singleton class.
      */
      /**************************************************************/
      Engine() {}
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Engine_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////