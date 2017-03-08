1. The very first and most important step is read through the original code and find where should 
insert the multithreading methods. What I found is the location where 4 for-loops are nested.

2. The best way to multithreading these 4 for-loops are separate the work by 'nthreads' parts. I 
created a structure called 'vars' at first, which include all variables needed for the for-loops, 
I also created an integer named 'threadArgument'.

3. After created the structure, change all original variables in main() to 'vars.variableNames'.

4. Then I passed this structure into threads, created a pointer of this structure in thread function,
and assign the address of 'vars' to this pointer which named 't_vars'.

5. Changed all variables contained in structure to 't_vars->variableNames'.

6. To achieve the multithreading, I set 'threadArgument = 0' before enter threads, then if there's an
thread created, 'threadArgument++'. I also assign the 'px' in original for-loop equal to 
'threadArgument', and third argument in that for-loop as 'px+=nthreads'. Therefore, for thread 1, 
px = 0, and will jump '0+nthreads' each time, and so on for other threads. Therefore the works of 
the original for loop is divided into 'nthreads' pieces.

7. The time consuming as below:
time ./srt 1-test.ppm > 1-test.ppm.tmp
real	0m55.682s
user	0m55.641s
sys	0m0.033s

time ./srt 2-test.ppm > 2-test.ppm.tmp
real	0m27.939s
user	0m55.737s
sys	0m0.022s

time ./srt 4-test.ppm > 4-test.ppm
real	0m13.985s
user	0m55.524s
sys	0m0.015s

time ./srt 8-test.ppm > 8-test.ppm
real	0m7.209s
user	0m55.706s
sys	0m0.008s

time ./srt 16-test.ppm > 16-test.ppm
real	0m5.078s
user	0m59.497s
sys	0m0.016s

The result picture of 1 to 4 threads are perfect, and they successfully reduce the time consuming.
But not for 8 and 16 threads, there are missing pixels because POSIX thread doesn't support more than
 4 threads, but the work is already divided by 8 and 16 pieces, so there are 8 and 16 parts work was 
never done in 8-test.ppm and 16-test.ppm although 8 and 16 used less time.