/* ======================================================================== */
/*!
 * \file            BezierCurve.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Contains code to generate cubic bezier curves.
 */
 /* ======================================================================== */

#include "BezierCurve.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  BezierCurve::BezierCurve() :
    curve_(),
    p0_(-100.0f, -100.0f),
    p1_(-50.0f, -50.0f),
    p2_(50.0f, 50.0f),
    p3_(100.0f, 100.0f),
    numSegments_(100)
  {
    BuildCurve();
  }

  BezierCurve::BezierCurve(
    const Position& p0, 
    const Position& p1, 
    const Position& p2, 
    const Position& p3, 
    size_t numSegments
  ) :
    curve_(),
    p0_(p0),
    p1_(p1),
    p2_(p2),
    p3_(p3),
    numSegments_(numSegments != 0 ? numSegments : 1)
  {
    BuildCurve();
  }

  void BezierCurve::SetControlPoints(const Position& p0, const Position& p1, const Position& p2, const Position& p3)
  {
    p0_ = p0;
    p1_ = p1;
    p2_ = p2;
    p3_ = p3;

    BuildCurve();
  }

  void BezierCurve::SetP0(Position p0)
  {
    p0_ = p0;

    BuildCurve();
  }

  void BezierCurve::SetP1(Position p1)
  {
    p1_ = p1;

    BuildCurve();
  }

  void BezierCurve::SetP2(Position p2)
  {
    p2_ = p2;

    BuildCurve();
  }

  void BezierCurve::SetP3(Position p3)
  {
    p3_ = p3;

    BuildCurve();
  }

  void BezierCurve::SetNumSegments(size_t numSegments)
  {
    numSegments_ = Clamp<size_t>(numSegments, 1, 1000);

    BuildCurve();
  }

  Position BezierCurve::GetP0()
  {
    return p0_;
  }

  Position BezierCurve::GetP1()
  {
    return p1_;
  }

  Position BezierCurve::GetP2()
  {
    return p2_;
  }

  Position BezierCurve::GetP3()
  {
    return p3_;
  }

  size_t BezierCurve::GetNumSegments()
  {
    return numSegments_;
  }

  Position BezierCurve::GetPosition(double t)
  {
    t = Clamp(t, 0.0, 1.0);

    size_t startIndex = std::min(static_cast<size_t>(t * numSegments_), numSegments_);
    size_t endIndex = std::min(startIndex + 1, numSegments_);

    const Position& pStart = curve_[startIndex];
    const Position& pEnd = curve_[endIndex];

    double lerpFactor = GetLerpFactor(startIndex, t);

    Position result;
    result.x_ = Lerp(pStart.x_, pEnd.x_, lerpFactor);
    result.y_ = Lerp(pStart.y_, pEnd.y_, lerpFactor);

    return result;
  }

  double BezierCurve::GetLerpFactor(size_t startIndex, double t)
  {
    double pointStep = 1.0 / numSegments_;
    return (t - startIndex * pointStep) / pointStep;
  }

  Position BezierCurve::GeneratePoint(double t)
  {
    double u = 1 - t;
    double tt = t * t;
    double uu = u * u;
    double uuu = uu * u;
    double ttt = tt * t;

    double x = uuu * p0_.x_;
    double y = uuu * p0_.y_;

    x += 3 * uu * t * p1_.x_; 
    y += 3 * uu * t * p1_.y_; 

    x += 3 * u * tt * p2_.x_; 
    y += 3 * u * tt * p2_.y_; 

    x += ttt * p3_.x_; 
    y += ttt * p3_.y_; 

    return Position(static_cast<float>(x), static_cast<float>(y));
  }

  void BezierCurve::BuildCurve()
  {
    curve_.clear();

    for (size_t i = 0; i <= numSegments_; ++i)
    {
      double t = static_cast<double>(i) / numSegments_;

      curve_.push_back(GeneratePoint(t));
    }
  }
}