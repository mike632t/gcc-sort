## gcc-sort

A re-implementation of the sort routines in K&R Ed 2 to make them more like 
the current sort routine in the standard library.

- quicksort    - based on K+R Ed 2 Page 120

- shellsort    - based on K+R Ed 2 Page 62

- bubblesort 

- shuffle

- reverse

- swap

### Performance and compatibility

- MicroVAX VAX 4000-96 running OpenVMS 7.3 with DEC C V6.0-001

  Note - Only 10 iterations

```
$ cc cc-sort
$ link cc-sort
$ run cc-sort
bubblesort : 23.840 s
shellsort  :  0.690 s
quicksort  :  0.630 s
$ 
```

- AlphaServer DS10/466 running Tru64 UNIX V5.1B with Compaq C V6.5-011 

```
$ cc cc-sort.c -o cc-sort  
$ ./cc-sort  
bubblesort : 41.682 s
shellsort  :  1.500 s
quicksort  :  1.250 s
$ 
```

- AlphaServer DS10/466 running OpenVMS V7.3-2 with Compaq C V6.5-001

```
$ cc cc-sort.c
$ link cc-sort
$ run cc-sort
bubblesort : 41.300 s
shellsort  :  1.500 s
quicksort  :  1.520 s
$ 
```
```
$ cc cc-sort.c /architecture=ev6
$ link cc-sort
$ run cc-sort
bubblesort : 31.950 s
shellsort  :  1.120 s
quicksort  :  0.950 s
$
```

- AlphaServer ES40/1000 running OpenVMS Alpha V8.4-2L2 with VSI C V7.4-002

```
$ cc cc-sort /architecture=ev6
$ link cc-sort
$ run cc-sort
bubblesort : 17.770 s
shellsort  :  0.590 s
quicksort  :  0.440 s
$ 
```

- HP D710 Desktop Intel Pentium 4 (3.0 GHz) running Debian 12 with GCC 12.2.0-14

```
$ cc cc-sort.c -o cc-sort
$ ./gcc-sort 
bubblesort : 15.744 s
shellsort  :  0.545 s
quicksort  :  0.447 s
$
```

- HP Z420 Workstation Intel Xeon E5-1650v2 (3.5 GHz) running Debian 10 with GCC 8.3.0-6

```
$ cc cc-sort.c -o cc-sort
$ ./cc-sort
bubblesort   :  5.869 s
shellsort    :  0.231 s
quicksort    :  0.180 s
$
```

