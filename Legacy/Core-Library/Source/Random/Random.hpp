/* ======================================================================== */
/*!
 * \file            Random.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Random number generator based on xorshift.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Random_BARRAGE_H
#define Random_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
	//! Random number generator based on xorshift.
  class Random
	{
    public:    
      /**************************************************************/
      /*!
        \brief
          Default constructor. Allows user to set starting seed, or
          generates a random seed if none is provided.

        \param seed
          The 64-bit starting seed for the generator.
      */
      /**************************************************************/
      Random(unsigned long long seed = 0);

      /**************************************************************/
      /*!
        \brief
          Gets the starting seed of the generator.
      */
      /**************************************************************/
      unsigned long long GetSeed();
      
      /**************************************************************/
      /*!
        \brief
          Generates a random float between min and max (inclusive).

        \param min
          The minimum value of the range.

        \param max
          The maximum value of the range.

        \return
          Returns a random float between min and max (inclusive).
      */
      /**************************************************************/
      float RangeFloat(float min, float max);

      /**************************************************************/
      /*!
        \brief
          Generates a random int between min and max (inclusive).
          
          Guarantees the result will be random, with no result
          likelier than any other result (that is, guarantees result
          is sampled from a uniform distribution).

        \param min
          The minimum value of the range.

        \param max
          The maximum value of the range.

        \return
          Returns a random float between min and max (inclusive).
      */
      /**************************************************************/
      int RangeInt(int min, int max);

    private:
      /**************************************************************/
      /*!
        \brief
          Generates a random 64-bit starting seed for the generator.
      */
      /**************************************************************/
      void GenerateRandomSeed();
      
      /**************************************************************/
      /*!
        \brief
          Generates a random 64-bit number.

        \param
          Returns a random 64-bit number.
      */
      /**************************************************************/
      unsigned long long Generate();

      /**************************************************************/
      /*!
        \brief
          Generates a random float between 0.0f and 1.0f.

        \param
          Returns a random float between 0.0f and 1.0f.
      */
      /**************************************************************/
      float Float();

    private:
      unsigned long long startSeed_;   //!< The starting seed for the generator.
      unsigned long long currentSeed_; //!< The current seed in the random number sequence.
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Random_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////