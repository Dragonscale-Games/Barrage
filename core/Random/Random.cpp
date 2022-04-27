/* ======================================================================== */
/*!
 * \file            Random.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Random number generator based on xorshift.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "Random.hpp"

#include <random>
#include <chrono>
#include <stdexcept>
#include <climits>

namespace Barrage
{
  Random::Random(unsigned long long seed) :
    startSeed_(seed), 
    currentSeed_(seed)
  {
    if (seed == 0)
    {
      GenerateRandomSeed();
    }
  }

  unsigned long long Random::GetSeed()
  {
    return startSeed_;
  }

  float Random::RangeFloat(float min, float max)
  {
    return min + Float() * (max - min);
  }

  int Random::RangeInt(int min, int max)
  {
    // if input is dirty, just return min
    if (min >= max)
    {
      return min;
    }
    
    // figure out how many results are possible within the range
    unsigned long long possible_results = static_cast<unsigned long long>(static_cast<long long>(max) - static_cast<long long>(min)) + 1;

    // find the maximum acceptable generated number, which is the biggest number the generator can
    // roll that makes the sample space a positive integer multiple of the number of possible results
    unsigned long long max_roll = (ULLONG_MAX / possible_results) * possible_results - 1;

    // will eventually be a random number between 0 and (possible_results - 1)
    unsigned long long generated_number;

    // try to generate an acceptable uniformly distributed number - stop if it takes too long (exceptionally rare)
    for (int i = 0; i < 100; i++)
    {
      generated_number = Generate();

      if (generated_number <= max_roll)
        break;
    }

    // map generated number to range between 0 and (possible_results - 1)
    generated_number %= possible_results;

    // our result is the minimum number plus a random number between 0 and (max - min + 1)
    int result = min + static_cast<int>(generated_number);

    return result;
  }

  void Random::GenerateRandomSeed()
  {
    unsigned long long seed;

    // start by trying to use random_device method, which provides best randomness
    try
    {
      std::random_device device_seed;

      unsigned seed1, seed2;

      // generate 32-bit seeds until a nonzero seed is generated - use for rightmost 32 bits of 64-bit seed
      do {

        seed1 = device_seed();

      } while (seed1 == 0);

      // generate 32-bit seeds until a nonzero seed is generated - use for leftmost 32 bits of 64-bit seed
      do {

        seed2 = device_seed();

      } while (seed2 == 0);

      seed = seed1 + (static_cast<unsigned long long>(seed2) << 32);
    }
    // if random_device method is not supported, generate a seed using the system clock
    catch (const std::exception& e)
    {
      UNREFERENCED(e);
      auto clock = std::chrono::system_clock::now();

      seed = static_cast<unsigned long long>(clock.time_since_epoch().count());

      // use a nonzero seed if 0 is generated - xorshift breaks on a zero seed
      if (seed == 0)
      {
        seed = 0xC0FFEEC0FFEE;
      }
    }

    startSeed_ = seed;
    currentSeed_ = seed;
  }

  unsigned long long Random::Generate()
  {
    // xorshift algorithm from page 4 of George Marsaglia's paper "Xorshift RNGs"
    currentSeed_ ^= (currentSeed_ << 13);
    currentSeed_ ^= (currentSeed_ >> 7);
    currentSeed_ ^= (currentSeed_ << 17);

    return currentSeed_ - 1;
  }

  float Random::Float()
  {
    // Generate() returns a number between 0 and (ULLONG_MAX - 1)
    return static_cast<float>(Generate()) / static_cast<float>(ULLONG_MAX - 1);
  }
}