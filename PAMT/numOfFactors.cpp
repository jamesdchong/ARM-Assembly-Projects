/* Filename: numOfFactors.cpp
 * Author: James Chong
 * Userid: cs30xbh
 * Description: Takes number n and calculates how many evenly-divisible factors
 * 		there are between lo and hi
 * Date: 5/14/19
 */

#define MIN_LO 2

/*
 * Function name: numOfFactors()
 *
 * Function prototype: long long numOfFactors( long long n,
 *                                             long long lo,
 *                                             long long hi );
 *
 * Params: n is the value we are checking to determine how many factors
 *           evenly divide into it.
 *         lo is the low (inclusive) range of possible factors to check.
 *         hi is the high (exclusive) range of possible factors to check.
 *
 * Algorithm:
 *   if n <= 1 return 0 (we won't deal with values less than 2). By definition,
 *       prime numbers are greater than 1.
 *
 *   if lo <= 1, set lo to 2 (we won't deal with factors less than 2).
 *
 *   loop thru the range [lo, hi) as factors incrementing by 1 each time
 *       thru the loop checking if n is evenly divisible by each factor.
 *       If it is evenly divisible - increment the number of
 *       evenly-divisible factors for this range.
 *
 *       Your loop variable should be defined to be type long long!
 *   
 *   There may be other more efficient algorithms, but this will do.
 *   We want to see how multi-threading in C++11 with async()/get()
 *   might improve overall performance.
 *
 * Side Effects: None.
 *
 * Error Conditions: None.
 *
 * Return value: long long int indicating the number of evenly-divisible
 *               factors in n.
 */

long long numOfFactors( long long n, long long lo, long long hi ) { 

  // Initialize number of evenly divisible factors to 0
  long long numFactors = 0;

  // If n is less than or equal to 1, there are no evenly divisible factors
  if( n <= 1 ) {
    return 0;
  }

  // If lo is less than or equal to 1, lo equals 2
  if( lo <= 1 ) {
    lo = MIN_LO;
  }

  // Loop from lo to hi to find evenly divisible factors
  for( long long i = lo; i < hi; i++ ) {

    // If n is evenly divisible by i, increment numFactors
    if( n % i == 0 ) {
      numFactors++;
    }

  }

  // Return number of evenly divisible factors from low to hi of n
  return numFactors;

}

