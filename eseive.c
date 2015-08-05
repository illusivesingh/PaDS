#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

typedef long long int big;

int main(int argc, char ** argv)
{
    /***************** Function Declarations ***********************/
    
    // Costructs a random number having "bits" number of bits.
    big createBigNumber (const int bits);

    // Invokes the esieve routine ane prints its accuarray stat.
    void checkAccuracy (const big num, const int numThreads);

    // Invokes the esieve routine and prints its performance stat.
    void checkPerformance (const big num, const int numThreads);
    
    /***************************************************************/



    if (argc != 5)
    {
        // Number of arguments is not correct.
        printf ("The command line arguments are not correct.\n");
        printf ("Usage: <executable> <number of bits> ");
        printf ("<number of threads> <Accuracy Flag> ");
        printf ("<Performance Flag>\n");
        exit (1);
    }
    else {;} // The code following the if-else block will be executed.
    
    const int bits = atoi(argv[1]); /* Number of bits in the random 
        * number. */
    if(bits < 0 || bits > 32)
    {
        // Number of bits for the random number are not proper.
        printf("Number of bits should be within 0 to 32\n");
        return 0;
    }
    else {;} /* The number of bits for the random number are correct.
        * Following code will be executed. */
    
    const int numThreads = atoi(argv[2]); /* Number of threads. */
    const int checkAcc   = atoi(argv[3]); // Accuracy check flag.
    const int checkPerf  = atoi(argv[4]); // Performance check flag.

    const big num = createBigNumber (bits); /* Create a random number
        * having bits as specified in the command line arguments. */
    
    printf("Evaluating for number %lld\n", num);

    if(num == 0)
    {
        /* The random number genrated is 0. We can't evaluate any 
         * thing for 0. Thus exiting. */
        printf ("The number genrated was 0, please run the code again.\n");
        exit (1);
    }
    else
    {;} /* The random number genrated is valid. 
        * Code following the if-else block will be executed. */

    /* Both Accuracy and Performance can't be evaluated simultaneosly.
     * Thus verfying if both are set.
     * If only one is set the respective function will be invoked. */
    if(checkAcc != 0 && checkPerf != 0)
    {
        printf("Any one of accuracy or performance needs to be tested\n");
        exit (1);
    }
    else if(checkAcc != 0)
    {
        // Evaluate Accuracy
        printf ("Evaluating for Accuracy.\n");
        checkAccuracy(num, numThreads);
    }
    else if(checkPerf != 0)
    {
        // Evaluate performance
        printf ("Evaluating for Performance.\n");
        checkPerformance(num, numThreads);
    }
    else
    {
        // Nither Accuracy Nor Performance flag is set.
        printf ("Either Accuracy or Performance flag shall be set\n");
        exit (1);
    }
    return 0;
}


/* Input:
 *      num: A random number for which the performance will be evaluated.
 *      numThreads: number of threads to measure the accuarcy with.
 *  Output: 
 *      Prints the Perfromance measure to stdout.
 *  This Function:
 * */
void eseive (const big num, char * arr)
{
    if (arr == NULL)
    {
        printf ("eseive: array pointer is NULL.\n");
        printf ("Fatal Error. Exiting.\n");
        exit (1);
    }
    // else continue execution.

    // Executing the seiving algorithm in parallel.
    /*
#pragma omp parallel for
    for (big i = 0; i < num; ++i)
    {
        // write the seiving algo.
    }*/
}


/* Input:
 *      num: A random number for which the performance will be evaluated.
 *      numThreads: number of threads to measure the accuarcy with.
 *  Output: 
 *      Prints the Perfromance measure to stdout.
 *  This Function:
 *      For each number between 3 to n.
 *      compares the flag in about number being prime / not prime in
 *      the array "arr" to the number actually being prime / not prime.
 *      and prints the numbers for which the the prime / not prime flag
 *      doesn't agree.
 * */
void checkAccuracy (const big num, const int numThreads)
{
    /***************** Function Declarations ***********************/
    
    // Implements the seiving algorithm
    void eseive (const big num, char * arr);

    // Allocates an empty array of size num and initializes it to 0s
    char *createArray (const big num);

    // Deallocates the array pointed by arr.
    void destroyArray (char * arr);

    // Returns 0 if input number is not prime, else returns non zero num.
    extern int isPrime (big);

    /***************************************************************/
    char * arr = createArray(num); /* creates an array of size num
        * and initializes each element to 0. */
    
    omp_set_num_threads(numThreads); // set number of threads.
    
    eseive(num, arr); // run the algorithm.
    
    //printPrimes(num, arr);
    // For each number from i = 3 to n.
    for (big i = 3; i < num; ++i)
    {
        // Check if the number is marked as prime or not.
        if (arr[i] != 0)
        {
            // The number i is marked as prime.
            if (isPrime (i) == 0)
                printf("VIOLATION : %lld is not prime\n", i); /* but 
                    * it is not actually a prime number. */
            else
                ; // And "i" is a prime number, correct result.
        }
        else // arr [i] == 0;
        {
            // The number "i" is marked as composite.
            if (isPrime (i) != 0)
                printf("VIOLATION : %lld is prime\n", i); /* but it is 
                    * actually a prime number. */
            else
                ; // And "i" is not a prime, correct result.
        }
    }
    
    destroyArray(arr); // deallocate the array space.
    return;
}


/* Input:
 *      num: A random number for which the performance will be evaluated.
 *      numThreads: number of threads to measure the performance.
 *  Output: 
 *      Prints the Perfromance measure to stdout.
 *  This Function:
 *   1  sets the prime / not prime flag for each number i, in arr [i]
 *      by running the esieve algorithm serially.
 *   2  Then run the esieve algorithm for numThread times, each time
 *      increasing the number of threads by 1, starting from 1.
 *   3  Prints the time taken to execute the program.
 * */
void checkPerformance(const big num, const int numThreads)
{
    /***************** Function Declarations ***********************/
    
    // Implements the seiving algorithm
    void eseive (const big num, char * arr);

    // Allocates an empty array of size num and initializes it to 0s
    char *createArray (const big num);

    // Deallocates the array pointed by arr.
    void destroyArray (char * arr);

    // Gets the current system time and returns it.
    double getWallTime ();

    /***************************************************************/
    char * arr = createArray(num); /* Create an empty array.
        * index i represents whether arr [i] is prime or not.
        * if arr [i] == 0, it is not prime,
        * else arr [i] is prime. */

    //Warm up cache
    omp_set_num_threads(1); // set number of threads for openmp
    
    eseive(num, arr);
    
    // Actual perfomance evaluation.
    for(int i = 1; i <= numThreads; ++i)
    {
        omp_set_num_threads(i); // Set thread count
        
        const double startTime = getWallTime(); // get start time.
        eseive (num, arr); // run algorithm
        const double stopTime = getWallTime(); // get stop time.
        
        printf("Threads %d\tTime %g\n", i, stopTime-startTime); /*
            * print the results. */
    }
    
    destroyArray(arr); // deallocate the array.
    return;
}

/* Input:
 *      num: size of the array.
 *      arr: pointer to the array containing primes.
 * Output:
 *      prints the primes in the array arr to stdout.
 * */
void printPrimes(const big num, const char * arr)
{
    if (arr == NULL)
    {
        printf ("printPrimes: array pointer is NULL.\n");
        printf ("Fatal Error. Exiting.\n");
        exit (1);
    }
    // else continue execution.
    
    printf("Primes are :\n");
    for(big i = 0; i < num; ++i)
    {
        if(arr[i] != 0)
        {
            // It is a prime number, print it.
            printf("%lld\n", i);
        }
        else
            ; // It is not a prime number skip it.
    }
    return;
}

/** Input: 
 *      None.
 *  Output:
 *      The current system time.
 * */
double getWallTime ()
{
    struct timeval time;
    if (gettimeofday (&time, NULL) != 0)
    {
        printf ("getWallTime: couldn't fetch system time. ");
        printf ("Fatal error. Exiting.\n");
        exit (1);;
    }
    // else continue execution.
    
    double wallTime;
    wallTime = (double) time.tv_sec + (double) time.tv_usec * 0.000001;
    return wallTime;
}

/* Input:
 *  bits: Number of bits in the random number that will be genrated.
 * Output:
 *  A random number having "bits" number of bits.
 * This Function:
 *  For each bit:
 *   1   genrates a random number.
 *   2   takes its modulus with 2 to get 0 or 1, randomly.
 *   3   left shifts the number, num, (the random number genrated so far
 *       by 1.
 *   4   Then sets the Right most digit as 0 or 1 based on the above
 *       randomly genrated bit.
 * */
big createBigNumber (const int bits)
{
    big num = 0; // Initialize all bits to 0.
    big thisBit; // Temporary variable used to store a bit in loop.

    srand(time(NULL)); // Seed for rand ().
    
    // For each bit.
    for(int i = 0; i < bits; ++i)
    {
        // Gerate a random bit (%2) and sdet it to the ith bit.
        num     = num << 1; // left shift by 1.
        
        thisBit = (rand() % 2); /* Randomly get 0 or 1. All other bits
            * except the least significant digit in thisBit are 0. 
            * The least significant is either 0 or 1, randomly*/
 
        num     |= thisBit; // Binary OR operation with thisBit
    }
    return num;
}

/** Input:  
 *     num: size of the array.
 *  Output:
 *     returns pointer to an character array with each element have 
 *     been initialized to 0.
 *  This function:
 *     dynamically allocates an array of size num.
 * */
char *createArray (const big num)
{
    char *arr = (char *) malloc (num * sizeof (char)); // Allocate.
    memset (arr, 0, num * sizeof (char)); // Initialize
    return arr;
}

/** Input:
 *      arr: pointer to an array.
 *  This Function:
 *      Deallocates the memory pointed by arr from the process.
 * */
void destroyArray (char * arr)
{
    if (arr == NULL)
    {
        printf ("destroyArray: Error: Input pointer is NULL.\n");
        return;
    }
	free (arr); // deallocate since arr is not NULL.
    arr = NULL;
}

