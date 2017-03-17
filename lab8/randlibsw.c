//
//  randlibsw.c
//  randall
//
//  Created by Tom Zhang on 3/5/17.
//  Copyright © 2017 Tom Zhang. All rights reserved.
//

#include "randlib.h"
#include <stdio.h>
#include <stdlib.h>

/* Software implementation.  */

/* Input stream containing random bytes.  */
static FILE *urandstream;

/* Initialize the software rand64 implementation.  */
__attribute__((__constructor__)) extern void software_rand64_init (void)
{
    urandstream = fopen ("/dev/urandom", "r");
    if (! urandstream)
        abort ();
}

/* Return a random value, using software operations.  */
__attribute__ ((destructor)) extern unsigned long long software_rand64 (void)
{
    unsigned long long int x;
    if (fread (&x, sizeof x, 1, urandstream) != 1)
        abort ();
    return x;
}

/* Finalize the software rand64 implementation.  */
extern void
software_rand64_fini (void)
{
    fclose (urandstream);
}
