#ifndef PAMT_H    /* Macro Guard */
#define PAMT_H


/* 
 * The number of concurrent threads that the current machine can support.
 */

const int numOfThreads = std::thread::hardware_concurrency();

/*
 * Set some minimum value to perform multi-threading
 */

#define MIN_NUM_TO_PARALLELIZE (numOfThreads * 2)

/*
 * Set some maximum value to perform factoring, say 2^32, otherwise it will
 * take too long.
 */

#define MAX_NUM_TO_RUN 4294967296LL

/*
 * Local function prototypes for PAMT
 */

long long numOfFactors( long long n, long long lo, long long hi );

#endif

