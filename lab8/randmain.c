//
//  randmain.c
//  randall
//
//  Created by Tom Zhang on 3/5/17.
//  Copyright © 2017 Tom Zhang. All rights reserved.
//

#include "randcpuid.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

static bool
writebytes (unsigned long long x, int nbytes)
{
    int ndigits = nbytes * 2;
    do
    {
        if (putchar ("0123456789abcdef"[x & 0xf]) < 0)
            return false;
        x >>= 4;
        ndigits--;
    }
    while (0 < ndigits);
    
    return 0 <= putchar ('\n');
}

int main (int argc, char **argv)
{
    /* Check arguments.  */
    bool valid = false;
    long long nbytes;
    if (argc == 2)
    {
        char *endptr;
        errno = 0;
        nbytes = strtoll (argv[1], &endptr, 10);
        if (errno)
            perror (argv[1]);
        else
            valid = !*endptr && 0 <= nbytes;
    }
    if (!valid)
    {
        fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
        return 1;
    }
    
    /* If there's no work to do, don't worry about which library to use.  */
    if (nbytes == 0)
        return 0;
    
    
    /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
    void* handle;
    void (*initialize) (void) = NULL;
    unsigned long long (*rand64) (void) = NULL;
    void (*finalize) (void) = NULL;
    if (rdrand_supported ())
    {
        printf("Hardware_rand64\n");
        handle = dlopen("randlibhw.so", RTLD_NOW);
        if (handle == NULL)
        {
            fprintf(stderr, "Cannot open library randlibhw.so");
            return 1;
        }
        initialize = dlsym(handle, "hardware_rand64_init");
        if (initialize == NULL)
        {
            fprintf(stderr, "Hardware Initialize Error");
            return 1;
        }

        rand64 = dlsym(handle, "hardware_rand64");
        if (rand64 == NULL)
        {
            fprintf(stderr, "Hardware Generating Rand Error");
            return 1;
        }
        finalize = dlsym(handle, "hardware_rand64_fini");
        if (finalize == NULL)
        {
            fprintf(stderr, "Hardware Finalize Error");
            return 1;
        }
        
    }
    else
    {
        printf("Software_rand64\n");
        handle = dlopen("randlibsw.so", RTLD_NOW);
        if (handle == NULL)
        {
            fprintf(stderr, "Cannot open library randlibsw.so");
            return 1;
        }
        initialize = dlsym(handle, "software_rand64_init");
        if (initialize == NULL)
        {
            fprintf(stderr, "Software Initialize Error");
            return 1;
        }
        rand64 = dlsym(handle, "software_rand64");
        if (rand64 == NULL)
        {
            fprintf(stderr, "Software Generating Rand Error");
            return 1;
        }
        finalize = dlsym(handle, "software_rand64_fini");
        if (finalize == NULL)
        {
            fprintf(stderr, "Software Finalize Error");
            return 1;
        }
    }
    
    initialize ();
    int wordsize = sizeof rand64 ();
    int output_errno = 0;
    
    do
    {
        unsigned long long x = rand64 ();
        int outbytes = nbytes < wordsize ? nbytes : wordsize;
        if (!writebytes (x, outbytes))
        {
            output_errno = errno;
            break;
        }
        nbytes -= outbytes;
    }
    while (0 < nbytes);
    
    if (fclose (stdout) != 0)
        output_errno = errno;
    
    if (output_errno)
    {
        errno = output_errno;
        perror ("output");
        finalize ();
        dlclose(handle);
        return 1;
    }
    
    finalize ();
    dlclose(handle);
    return 0;
}