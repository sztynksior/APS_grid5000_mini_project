/*
 * This is a test program for PGAPack. The objective is to maximize the 
 * number of 1-bits in a chromosome.
 */

#include <pgapack.h>

double NumberOfSetBits(PGAContext *, int, int, double *);

/**********************************************************************
 *                             user main program                      *
 **********************************************************************/

int main( int argc, char **argv ) {
    PGAContext *ctx;

    ctx = PGACreate(&argc, argv, PGA_DATATYPE_BINARY, 10000, PGA_MAXIMIZE);
    PGASetRandomSeed(ctx, 1);
    PGASetPopSize(ctx, 10000);
    PGASetMaxGAIterValue(ctx, 3000);
    PGASetPrintOptions(ctx, PGA_REPORT_AVERAGE);
    PGASetUp(ctx);

    PGARun(ctx, NumberOfSetBits);

    if (PGAGetRank(ctx, MPI_COMM_WORLD) == 0)
        printf("Number of processes: %d", PGAGetNumProcs (ctx, MPI_COMM_WORLD));

    PGADestroy(ctx);

    return(0);
}

/**********************************************************************
 *                     user defined evaluation function               *
 *  ctx  - context variable                                           *
 *  p    - chromosome index in population                            *
 *  pop  - which population to refer to                              *
 **********************************************************************/

double NumberOfSetBits(PGAContext *ctx, int p, int pop, double *dummy) {
    int i, nbits, stringlen;

    stringlen = PGAGetStringLength(ctx);

    nbits = 0;
    for (i=0; i<stringlen; i++)
        if ( PGAGetBinaryAllele(ctx, P, pop, i) )
            nbits++;

    return((double) nbits);
}
