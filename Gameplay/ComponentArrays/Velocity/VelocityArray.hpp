/* ======================================================================== */
/*!
 * \file            VelocityArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The Velocity component keeps track of the speed and direction of a game
   object.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef VelocityArray_BARRAGE_H
#define VelocityArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/ComponentArray.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  //!< Speed and direction of a game object
  struct Velocity
  {
    Velocity();

    Velocity(float angle, float speed);

    Radian GetAngle() const;

    float GetSpeed() const;

    float GetVx() const;

    float GetVy() const;

    void SetAngle(Radian angle);

    void SetSpeed(float speed);

    void SetVelocity(float vx, float vy);

    void SetVx(float vx);

    void SetVy(float vy);

    void Rotate(float angle);

    void AddSpeed(float speed);

    void AddVelocity(float vx, float vy);

    static void Reflect();

    private:
      void UpdateCartesianValues();

      void UpdatePolarValues();

    private:
      Radian angle_; //!< angle from x axis (counterclockwise is positive)
      float speed_;  //!< total speed in world units per tick
      float vx_;     //!< x speed in world units per tick
      float vy_;     //!< y speed in world units per tick

      static constexpr float MINIMUM_SPEED_THRESHOLD = 0.000001f;
  };

  typedef Barrage::ComponentArrayT<Velocity> VelocityArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // VelocityArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////