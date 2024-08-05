/*
 * Filename: main.cpp 
 * Author: James Chong
 * Userid: cs30xbh
 * Description: Main driver that reads command line numbers to determine number
 * 		of factors, then reports results and statistics
 * Date: 5/14/19
 */

#include <math.h>
#include <iostream>
#include <thread>
#include <future>
#include <sys/time.h>
#include "pamt.h"

/*
 * Function name: main
 * Function prototype: int main( int argc, char* argv[] );
 * Description: C++ main driver which reads numbers from the command line to
 *              determine number of factors (both sequentially and parallel)
 *              and reports results and statistics.
 *
 * Parameters: numbers to factor
 *
 * Side Effects: Outputs number of threads, value of each number to factor, 
 *               number of factors for number, and benchmark info.
 *
 * Error Conditions:
 * 	- If number of command line args is less than 2, print error message to
 * 	  stderr
 * 	- If any command line number is larger than MAX_NUM_TO_RUN, print error
 * 	  message and exit loop
 * 	- If a command line number is less than 1, print error message and
 * 	  exit loop
 *
 *
 * Return Value: 0 indicating successful execution, 1 indicating usage error. 
 */

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s num1 [num2 num3 ...]\n", argv[0]);
    return 1;
  }

  struct timeval t0, t1;

  for( int i = 1; i < argc; ++i ) {

    long long num = strtoll(argv[i], NULL, 0);

    if ( num > MAX_NUM_TO_RUN ) {
      std::cout << num << " is too large to run. Try a value <= to "
                << MAX_NUM_TO_RUN << std::endl << std::endl;

      std::cout << "--------------" << std::endl << std::endl;

      continue;
    }

    /*
     * First do sequential numOfFactors
     */

    std::cout << "Sequential numOfFactors for " << num <<
                 " (be patient for large values)" << std::endl;

    gettimeofday( &t0, NULL ); // start

    /*
     * Start min factor at 2, max factor to be one more than num since
     * max factor is exclusive and want to include num as a factor.
     */

    long long factors = numOfFactors( num, 2, num + 1 );

    gettimeofday( &t1, NULL ); // finish

    if ( factors == 0 ) {
      std::cout << "Not dealing with numbers <= 1" << std::endl << std::endl;

      std::cout << "--------------" << std::endl << std::endl;

      continue;
    }

    double seqTime = t1.tv_sec - t0.tv_sec +
                    (t1.tv_usec - t0.tv_usec) / 1000000.0;

    std::cout << num << (factors == 1 ? " is " : " is not ")
              << "prime" << std::endl;

    std::cout << "Number of factors: " << factors << std::endl;

    std::cout << "Completed in " << seqTime << " sec" << std::endl << std::endl;

    /*
     * Now do async-get C++11 multi-threading
     */

    if ( num < MIN_NUM_TO_PARALLELIZE ) {
      std::cout << num << " is too small to run multi-threading version"
                << std::endl << std::endl;

      std::cout << "Try a value >= " << MIN_NUM_TO_PARALLELIZE
                << std::endl << std::endl;

      std::cout << "--------------" << std::endl << std::endl;

      continue;
    }

    std::cout << "Number of threads = " << numOfThreads << std::endl;

    std::cout << "Async-get parallel numOfFactors for " << num << std::endl;  

    /*
     * Calculate the size of each parallel partition (range of factors
     * each thread will use) based on the number of threads advertized. 
     */

    long long partitionSize = num / numOfThreads - 1;

    /*
     * results[] holds the future<long long> number of factors from the
     *           different async threads. We will later have to get()
     *           "join" each thread to reduce on these number of factors.
     */

    std::future<long long> results[numOfThreads - 1];

    gettimeofday( &t0, NULL ); // start parallel part

    /*
     * Map each of the partitions (range of factors) to a separate thread
     * with async() (except the last partition (range of factors)).
     *
     * Launch a thread to work on its part of the range of factors. Each
     * thread will return its result with that partition's number of factors.
     */

    int j;
    for ( j = 0; j < numOfThreads - 1; ++j ) {
      results[j] = std::async( std::launch::async, numOfFactors,
                               num, j * partitionSize,
			       ( j + 1 ) * partitionSize );
      /*
       * Fill in the rest of the async() function call - the arguments
       * to numOfFactors() each separated by a comma.
       */

    }

    /*
     * Run the last partition in this main (current) thread. Initialize
     * variable factors to this last partition's result.
     *
     * Be sure to include any extra values at the upper range due to
     * integer divide calculating size of each partition.
     * Hi (exclusive) factor value needs to be (num + 1) so we use the number
     * itself as a factor.
     */

    factors = numOfFactors( num, ( numOfThreads - 1 ) * partitionSize,
                            num + 1 );

    /*
     * We have to join/wait on all the other (n - 1) thread results with
     * get() and sum them together with the last main (current) thread's
     * number of factors we already have from the line above.
     *
     * This is a reduction - reducing all the separate thread results
     * into a single answer.
     */

    /*
     * Reduce on all the separate thread results summing them into
     * a single total number of factors.
     *
     * Cycle through the results array which holds the results from the
     * different threads and reduce to a single overall total number of
     * factors by summing all the thread results (along with the main
     * thread's number of factors) using get() as in results[j].get()
     */

    for( j = 0; j < numOfThreads - 1; ++j ) {
      factors += results[j].get();
    }

    gettimeofday( &t1, NULL ); // finish - have to include reduction work

    double parallelTime = t1.tv_sec - t0.tv_sec + 
                         (t1.tv_usec - t0.tv_usec) / 1000000.0;

    std::cout << num << (factors == 1 ? " is " : " is not ")
              << "prime" << std::endl;

    std::cout << "Number of factors: " << factors << std::endl;

    std::cout << "Completed in " << parallelTime 
              << " sec" << std::endl << std::endl;

    std::cout << "Speed-up: " << (double) seqTime / parallelTime 
              << std::endl << std::endl;

    std::cout << "--------------" << std::endl << std::endl;
  }

  return 0;
}

