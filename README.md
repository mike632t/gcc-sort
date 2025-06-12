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

- MicroVAX VAX 4000-96 running OpenVMS 7.3 with DEC C V6.0-001

  Note - Only 10 iterations

```
$ cc gcc-sort
$ link gcc-sort
$ run gcc-sort
bubblesort    : 26.100 s
exchangesort  : 18.470 s
insertionsort : 12.690 s
shellsort     :  0.650 s
quicksort     :  0.620 s
quicksort (*) :  0.380 s
$ 
```

- AlphaServer DS10/466 running Digital UNIX V4.0F with DEC C V5.9-005

```
$ cc gcc-sort.c -o gcc-sort  
$ ./cc-sort  
bubblesort    : 39.515 s
exchangesort  : 26.016 s
insertionsort : 23.516 s
shellsort     :  1.400 s
quicksort     :  1.483 s
quicksort (*) :  1.100 s
$ 
```
- AlphaServer DS10/466 running Tru64 UNIX V5.1B with Compaq C V6.5-011 

```
$ cc gcc-sort.c -o gcc-sort  
$ ./cc-sort  
bubblesort    : 41.648 s
exchangesort  : 24.699 s
insertionsort : 22.582 s
shellsort     :  1.450 s
quicksort     :  1.250 s
quicksort (*) :  0.817 s
$ 
```

- AlphaServer DS10/466 running OpenVMS V7.3-2 with Compaq C V6.5-001

```
$ cc gcc-sort.c
$ link gcc-sort
$ run gcc-sort
bubblesort    : 41.070 s
exchangesort  : 34.880 s
insertionsort : 29.690 s
shellsort     :  1.550 s
quicksort     :  1.490 s
quicksort (*) :  0.730 s
$ 
```
```
$ cc gcc-sort.c /architecture=ev6
$ link gcc-sort
$ run gcc-sort
bubblesort    : 31.740 s
exchangesort  : 23.110 s
insertionsort : 11.360 s
shellsort     :  1.150 s
quicksort     :  0.950 s
quicksort (*) :  0.730 s

$
```

- AlphaServer ES40/1000 running OpenVMS Alpha V8.4-2L2 with VSI C V7.4-002

```
$ cc gcc-sort.c
$ link gcc-sort
$ run gcc-sort
bubblesort     : 28.050 s  499500 comparisons  251379 swaps
exchangesort   : 19.030 s  499500 comparisons   80100 swaps
insertionsort  : 21.510 s  254864 comparisons  253875 swaps
insertionsort  : 17.600 s  252371 comparisons  253377 copies
shellsort      :  0.820 s   13916 comparisons    6422 swaps
quicksort      :  0.830 s   11724 comparisons    6891 swaps
quicksort (*)  :  0.970 s   10119 comparisons
$ 
```
```
$ cc gcc-sort /architecture=ev6
$ link gcc-sort
$ run gcc-sort
bubblesort     : 20.990 s  499500 comparisons  251379 swaps
exchangesort   : 17.330 s  499500 comparisons   80100 swaps
insertionsort  : 14.490 s  254864 comparisons  253875 swaps
insertionsort  : 14.180 s  252371 comparisons  253377 copies
shellsort      :  0.650 s   13916 comparisons    6422 swaps
quicksort      :  0.700 s   11724 comparisons    6891 swaps
quicksort (*)  :  1.060 s   10119 comparisons
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
bubblesort    :  5.702 s
exchangesort  :  4.332 s
insertionsort :  3.534 s
shellsort     :  0.228 s
quicksort     :  0.180 s
quicksort (*) :  0.084 s
$
```

