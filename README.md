## gcc-sort

A re-implementation of the sort routines in K&R Ed 2 to make them more like 
the current sort routine in the standard library.

- quick sort      - based on K+R Ed 2 Page 120

- shell sort      - based on K+R Ed 2 Page 62

- insertion sort

- exchange sort

- bubble sort 

- shuffle

- reverse

- swap

### Performance and compatibility

- MicroVAX (simh) running VAX/VMS 5.4-3 with VAX C V3.2-044

  Note - Only 10 iterations

```
$ cc gcc-sort
$ link gcc-sort
$ run gcc-sort
bubblesort     :  9.010 s  499500 comparisons  241621 swaps
exchangesort   :  8.080 s  499500 comparisons  178417 swaps
insertionsort  :  5.390 s  242618 comparisons  243619 copies
shellsort      :  0.280 s   15196 comparisons    7703 swaps
quicksort      :  0.220 s   11201 comparisons    6396 swaps
quicksort (*)  :  0.120 s   11045 comparisons
$ 
```
  

- MicroVAX VAX 4000-96 running OpenVMS 7.3 with DEC C V6.0-001

  Note - Only 10 iterations

```
$ cc gcc-sort
$ link gcc-sort
$ run gcc-sort
bubblesort     : 23.830 s  499500 comparisons  241621 swaps
exchangesort   : 20.710 s  499500 comparisons  178417 swaps
insertionsort  : 12.660 s  242618 comparisons  243619 copies
shellsort      :  0.740 s   15196 comparisons    7703 swaps
quicksort      :  0.590 s   11201 comparisons    6396 swaps
quicksort (*)  :  0.430 s   11045 comparisons
$ 
```

- AlphaServer DS10/466 running Tru64 UNIX V5.1B with Compaq C V6.5-011 

```
$ cc gcc-sort.c -o gcc-sort -lm
$ ./cc-sort
bubblesort     : 46.898 s  499500 comparisons  241621 swaps
exchangesort   : 44.098 s  499500 comparisons  178417 swaps
insertionsort  : 29.749 s  242618 comparisons  243619 copies
shellsort      :  2.000 s   15196 comparisons    7703 swaps
quicksort      :  1.400 s   11201 comparisons    6396 swaps
quicksort (*)  :  0.750 s   10218 comparisons
$
```
```
$ cc -arch generic -fast -O4 gcc-sort.c -o gcc-sort -lm
$ ./cc-sort
bubblesort     : 37.932 s  499500 comparisons  241621 swaps
exchangesort   : 35.799 s  499500 comparisons  178417 swaps
insertionsort  : 29.449 s  242618 comparisons  243619 copies
shellsort      :  1.400 s   15196 comparisons    7703 swaps
quicksort      :  0.833 s   11201 comparisons    6396 swaps
quicksort (*)  :  1.067 s   10218 comparisons
$
```
```
$ cc -arch ev6 -fast -O4 gcc-sort.c -o gcc-sort -lm
$ ./cc-sort
bubblesort     : 37.715 s  499500 comparisons  241621 swaps
exchangesort   : 35.515 s  499500 comparisons  178417 swaps
insertionsort  : 18.949 s  242618 comparisons  243619 copies
shellsort      :  1.383 s   15196 comparisons    7703 swaps
quicksort      :  0.800 s   11201 comparisons    6396 swaps
quicksort (*)  :  1.067 s   10218 comparisons
$ 
```

- AlphaServer DS10/466 running OpenVMS V7.3-2 with Compaq C V6.5-001

```
$ cc gcc-sort
$ link gcc-sort
$ run gcc-sort
bubblesort     : 57.440 s  499500 comparisons  241621 swaps
exchangesort   : 41.450 s  499500 comparisons  178417 swaps
insertionsort  : 28.790 s  242618 comparisons  243619 copies
shellsort      :  1.700 s   15196 comparisons    7703 swaps
quicksort      :  1.500 s   11201 comparisons    6396 swaps
quicksort (*)  :  0.890 s   11045 comparisons
$ 
```
```
$ cc gcc-sort /optimize=(inline=speed, level=4)
$ link gcc-sort
$ run gcc-sort
bubblesort     : 49.350 s  499500 comparisons  241621 swaps
exchangesort   : 42.600 s  499500 comparisons  178417 swaps
insertionsort  : 25.670 s  242618 comparisons  243619 copies
shellsort      :  1.750 s   15196 comparisons    7703 swaps
quicksort      :  1.530 s   11201 comparisons    6396 swaps
quicksort (*)  :  0.890 s   11045 comparisons
```
```
$ cc gcc-sort /architecture=ev6 /optimize=(inline=speed, level=4)
$ link gcc-sort
$ run gcc-sort
bubblesort     : 35.040 s  499500 comparisons  241621 swaps
exchangesort   : 33.440 s  499500 comparisons  178417 swaps
insertionsort  : 13.740 s  242618 comparisons  243619 copies
shellsort      :  1.400 s   15196 comparisons    7703 swaps
quicksort      :  1.140 s   11201 comparisons    6396 swaps
quicksort (*)  :  0.880 s   11045 comparisons
$
```

- AlphaServer ES40/1000 running OpenVMS Alpha V8.4-2L2 with VSI C V7.4-002

```
$ cc gcc-sort
$ link gcc-sort
$ run gcc-sort
bubblesort     : 27.500 s  499500 comparisons  241621 swaps
exchangesort   : 24.360 s  499500 comparisons  178417 swaps
insertionsort  : 17.030 s  242618 comparisons  243619 copies
shellsort      :  0.880 s   15196 comparisons    7703 swaps
quicksort      :  0.750 s   11201 comparisons    6396 swaps
quicksort (*)  :  1.120 s   11045 comparisons
$ 
```
```
$ cc gcc-sort /architecture=ev6
$ link gcc-sort
$ run gcc-sort
bubblesort     : 21.100 s  499500 comparisons  241621 swaps
exchangesort   : 20.090 s  499500 comparisons  178417 swaps
insertionsort  : 13.510 s  242618 comparisons  243619 copies
shellsort      :  0.730 s   15196 comparisons    7703 swaps
quicksort      :  0.570 s   11201 comparisons    6396 swaps
quicksort (*)  :  1.160 s   11045 comparisons
$ 
```

- Raspberry Pi 3B Plus Rev 1.3 running Debian 10 with GCC 8.3.0-6

```
$ cc gcc-sort.c -o gcc-sort
$ ./gcc-sort 
bubblesort    : 97.184 s
exchangesort  : 63.729 s
insertionsort : 55.552 s
shellsort     :  2.886 s
quicksort     :  2.515 s
quicksort (*) :  0.852 s
```

- HP D710 Desktop Intel Pentium 4 (3.0 GHz) running Debian 12 with GCC 12.2.0-14

```
$ cc gcc-sort.c -o gcc-sort
$ ./gcc-sort 
bubblesort    : 15.714 s
exchangesort  : 11.685 s
insertionsort :  8.929 s
shellsort     :  0.541 s
quicksort     :  0.446 s
quicksort (*) :  0.266 s
$
```

- HP Z420 Workstation Intel Xeon E5-1650v2 (3.5 GHz) running Debian 10 with GCC 8.3.0-6

```
$ cc gcc-sort.c -o gcc-sort
$ ./gcc-sort
bubblesort     :  6.150 s  499500 comparisons  241621 swaps
exchangesort   :  6.883 s  499500 comparisons  178417 swaps
insertionsort  :  3.834 s  242618 comparisons  243619 copies
shellsort      :  0.278 s   15196 comparisons    7703 swaps
quicksort      :  0.196 s   11201 comparisons    6396 swaps
quicksort (*)  :  0.084 s    8701 comparisons
$
```

