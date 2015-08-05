#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

typedef long long int big;

extern int isPrime(big);

void eseive(const big num,
	char * arr);

void printPrimes(const big num,
	const char * arr);

void checkAccuracy(const big num, 
		const int numThreads);

void checkPerformance(const big num,
		const int numThreads);

double getWallTime()
{
    struct timeval time;
    if(gettimeofday(&time, NULL))
	return 0;
    double wallTime = (double)time.tv_sec + (double)time.tv_usec * 0.000001;
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

char * createArray(const big num)
{
    char * arr = (char *)malloc(num * sizeof(char));
    memset(arr, 0, num * sizeof(char));
    return arr;
}

void destroyArray(char * arr)
{
    if(arr)
	free(arr);
    arr = NULL;
}


int main(int argc, char ** argv)
{
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
        // checkAccuracy(num, numThreads);
    }
    else if(checkPerf != 0)
    {
        // Evaluate performance
        printf ("Evaluating for Performance.\n");
        // checkPerformance(num, numThreads);
    }
    else
    {
        // Nither Accuracy Nor Performance flag is set.
        printf ("Either Accuracy or Performance flag shall be set\n");
        exit (1);
    }
    return 0;
}

void eseive(const big num,
	char * arr)
{

//Fill in the Code

}


void checkAccuracy (const big num, const int numThreads)
{
    char * arr = createArray(num);
    omp_set_num_threads(numThreads);
    eseive(num, arr);
    //printPrimes(num, arr);
    for(big i = 3; i < num; ++i)
    {
	if(!arr[i])
	{
	    if(!isPrime(i))
		printf("VIOLATION : %lld is not prime\n", i);
	}
	else
	{
	    if(isPrime(i))
		printf("VIOLATION : %lld is prime\n", i);
	}
    }
    destroyArray(arr);
    return;
}

void checkPerformance(const big num,
		const int numThreads)
{
    char * arr = createArray(num);
    //Warm up cache
    omp_set_num_threads(1);
    eseive(num, arr);
    for(int i = 1; i <= numThreads; ++i)
    {
	omp_set_num_threads(i);
	const double startTime = getWallTime();
	eseive(num, arr);
	const double stopTime = getWallTime();
	printf("Threads %d\tTime %g\n", i, stopTime-startTime);
    }
    destroyArray(arr);
    return;
}

void printPrimes(const big num,
	const char * arr)
{
    printf("Primes are :\n");
    for(big i = 0; i < num; ++i)
    {
	if(!arr[i])
	    printf("%lld\n", i);
    }
    return;
}
