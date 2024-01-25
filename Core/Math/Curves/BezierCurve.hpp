/* ======================================================================== */
/*!
 * \file            BezierCurve.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Contains code to generate cubic bezier curves.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BezierCurve_BARRAGE_H
#define BezierCurve_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Renderer/RendererTypes.hpp"

#include <vector>

namespace Barrage
{
  class BezierCurve
  {
    public:
      BezierCurve();

      BezierCurve(const Position& p0, const Position& p1, const Position& p2, const Position& p3, size_t numSegments);

      void SetControlPoints(const Position& p0, const Position& p1, const Position& p2, const Position& p3);
      
      void SetP0(Position p0);

      void SetP1(Position p1);

      void SetP2(Position p2);

      void SetP3(Position p3);

      void SetNumSegments(size_t numSegments);

      Position GetP0();

      Position GetP1();

      Position GetP2();

      Position GetP3();

      size_t GetNumSegments();

      Position GetPosition(double t);

    private:
      double GetLerpFactor(size_t startIndex, double t);
      
      Position GeneratePoint(double t);
      
      void BuildCurve();

    private:
      std::vector<Position> curve_;
      Position p0_;
      Position p1_;
      Position p2_;
      Position p3_;
      size_t numSegments_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // BezierCurve_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////