/*
 * gcc-sort.c
 *
 * Copyright(C)2024  MT
 *
 * A  re-implementation of the sort routines in K&R Ed 2 to make them  more
 * like the current sort routine in the standard library.
 *
 * This  program is free software: you can redistribute it and/or modify it
 * under  the terms of the GNU General Public License as published  by  the
 * Free  Software Foundation, either version 3 of the License, or (at  your
 * option) any later version.
 *
 * This  program  is distributed in the hope that it will  be  useful,  but
 * WITHOUT   ANY   WARRANTY;   without even   the   implied   warranty   of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You  should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * https://stackoverflow.com/questions/71982801
 *
 * 16 Nov 24   0.1   - Initial version - MT
 * 22 Nov 24         - Added shell sort - MT
 * 24 Nov 24         - Implemented a bubble sort - MT
 * 29 Nov 24   0.2   - Measures the amount of processing time used by  each
 *                     sorting algorithm and prints the results - MT
 * 30 Nov 24         - Tidied up data types - MT
 *                   - Added  an exchange sort, quicker than a bubble  sort
 *                     but slower then a shell sort - MT
 * 03 Dec 24         - Finally managed to implement an insertion sort which
 *                     is still much slower then a shell sort but is faster
 *                     than an exchange sort - MT
 * 08 Dec 24   0.3   - Added  counters allow the number comparison and swap
 *                     operations are required and uses separate  functions
 *                     to reinitialise the array and display the results of
 *                     each test - MT
 * 12 Jun 25   0.4   - Added a generic linear search routine and tidied  up
 *                     comments and spacing - MT
 * 13 Jun 24         - Initialise the array using the same test data  every
 *                     time - MT
 * 15 Jun 25         - Check the number of elements in the array is greater
 *                     then 1 before trying to shuffle it - MT
 *                   - Checked spelling and rewrote initialisation  routine
 *                     to separate the two different approaches  - MT
 *
 */

#define  NAME        "gcc-sort"
#define  VERSION     "0.2"
#define  BUILD       "0010"
#define  DATE        "13 Jun 25"
#define  AUTHOR      "MT"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define  True          -1
#define  False         0

#define  ITERATIONS    1000
#define  SIZE          1000

#if defined(VMS) && defined(VAX) && !defined(CLOCKS_PER_SEC)
#define  CLOCKS_PER_SEC CLK_TCK
#endif

int i_compaires, i_swaps, i_copies;

int cmpint (const void *h_left, const void *h_right)
{
   int i_left = *(int *)h_left;
   int i_right = *(int *)h_right;
   i_compaires++;
   return (i_left > i_right) - (i_left < i_right);
}

int cmpnum (const void *h_left, const void *h_right)

/* Based on K+R Ed 2 Page 121 */

{
   int i_left  = atoi(*(char **)h_left);
   int i_right = atoi(*(char **)h_right);
   return (i_left > i_right) - (i_left < i_right);
}

int cmpstr (const void *h_left, const void *h_right)
{
   char *s_left = *(char **)h_left;
   char *s_right = *(char **)h_right;
   return strcmp (s_left, s_right);
}

void prtstr (char **s_array, size_t t_num)
{
   size_t i_count;
   if (t_num > 0)
   {
      printf ("(%s", s_array[0]);
      for (i_count = 1; i_count < t_num; i_count++)
         printf (", %s", s_array[i_count]);
   }
   printf (")\n");
}

void prtint (int *i_array, size_t t_num)
{
   size_t i_count;
   if (t_num > 0)
   {
      printf ("(%2d", i_array[0]);
      for (i_count = 1; i_count < t_num; i_count++)
         printf (", %2d", i_array[i_count]);
   }
   printf (")\n");
}

static void swap (void *v_left, void *v_right, size_t t_size)

/* Byte for byte exchange will swap either pointers or values. */

{
   unsigned char *h_left = (unsigned char*) v_left;
   unsigned char *h_right = (unsigned char*) v_right;
   unsigned char c_temp;

   i_swaps++;
   while (t_size-- > 0) /* Swap each byte in turn. */
   {
      c_temp = *h_left;
      *h_left++ = *h_right;
      *h_right++ = c_temp;
   }
}

static void copy (void *v_left, void *v_right, size_t t_size)

/* Byte for byte exchange will swap either pointers or values. */

{
   unsigned char *h_left = (unsigned char*) v_left;
   unsigned char *h_right = (unsigned char*) v_right;

   i_copies++;
   while (t_size-- > 0) /* Swap each byte in turn. */
      *h_left++ = *h_right++;
}

static void shuffle (void *v_array, size_t t_num, size_t t_size)

/* Shuffle array elements. */

{
   unsigned char *h_ptr = (unsigned char *)v_array;
   size_t i_count, i_random;

   if (t_num > 1) /* Check that there are two or more elements in the array */
   {
      for (i_count = t_num - 1; i_count > 0 ; i_count--)
      {
         i_random = (size_t)((double)i_count * (rand() / (RAND_MAX + 1.0)));
         swap (h_ptr + i_count * t_size, h_ptr + i_random * t_size, t_size);
      }
   }
}

char search(void *v_array, void *v_data, size_t t_num, size_t t_size, int (*v_compare)(const void *, const void *)) 

/* Linear array search. */

{
   unsigned char *h_ptr = (unsigned char *)v_array;
   unsigned char *h_data = (unsigned char *)v_data;

   size_t i_count, i_upper = t_num;

   for (i_count = 0; i_count < i_upper; i_count++)
      if ((v_compare(h_ptr + i_count * t_size, h_data)) == 0)
         return True;
   return False;
}

void reverse (void *v_array, size_t t_num, size_t t_size)

/* Reverse elements in an array. Based on K+R Ed 2 Page 62. */

{
   unsigned char *h_ptr = (unsigned char *)v_array;
   size_t i_count = 0;
   while (i_count < --t_num)
   {
      swap (h_ptr + i_count * t_size, h_ptr + t_num * t_size, t_size);
      i_count++;
   }
}

void bubblesort (void *v_array, size_t t_num, size_t t_size, int (*v_compare)(const void *, const void *))

/* Iterates over the elements in the array comparing each pair of  adjacent
 * elements, swapping pairs of elements that are out of order. */
 
{
   unsigned char *h_ptr = (unsigned char *)v_array;
   size_t i_count, i_next, i_upper = t_num;

   for (i_count = 1; i_count < i_upper; i_count++)
      for (i_next = i_count; i_next > 0; i_next--)
         if ((v_compare(h_ptr + i_next * t_size, h_ptr + (i_next - 1) * t_size)) < 0)
            swap (h_ptr + i_next * t_size, h_ptr + (i_next - 1) * t_size, t_size);
}

void exchangesort (void *v_array, size_t t_num, size_t t_size, int (*v_compare)(const void *, const void *))

/* Begins  with  the first element in the array and compares it with  every
 * following  element in the array.  If any of the following  elements  are
 * smaller than the current element, it is swapped with the current element
 * and the process repeated for the next element in the array. */
{
   unsigned char *h_ptr = (unsigned char *)v_array;
   size_t i_count, i_next;

   for (i_count = 0; i_count < t_num - 1; i_count++)
      for (i_next = i_count + 1; i_next < t_num; i_next++)
         if ((v_compare(h_ptr + i_count * t_size, h_ptr + i_next * t_size)) > 0) 
            /* If  the  previous element is bigger than the next swap  them
             * over. */
            swap (h_ptr + i_count * t_size, h_ptr + i_next * t_size, t_size);
}

void insertionsort (void *v_array, size_t t_num, size_t t_size, int (*v_compare)(const void *, const void *))

/* Compares each successive element in the array with all of the  preceding
 * elements.  When an appropriate position if found the element is inserted
 * in its position, and all the other elements are moved down one place. */
 
{
   unsigned char *h_ptr = (unsigned char *)v_array;
   unsigned char *h_tmp = (unsigned char *)malloc(t_size);
   size_t i_count, i_next;

   if (!h_tmp) {
      fprintf(stderr, "Memory allocation failed in insertionsort\n");
      exit(EXIT_FAILURE);
   }

   for (i_count = 1; i_count < t_num; i_count++)
   {
      i_next = i_count;
      copy (h_tmp, h_ptr + i_count * t_size, t_size);
      while (i_next > 0 && ((v_compare (h_tmp, h_ptr + (i_next - 1) * t_size)) < 0))
      {
         copy (h_ptr + i_next * t_size, h_ptr + (i_next - 1) * t_size, t_size);
         i_next--;
      }
      copy (h_ptr + (i_next) * t_size, h_tmp, t_size);
   }
   free(h_tmp);
}

void _insertionsort (void *v_array, size_t t_num, size_t t_size, int (*v_compare)(const void *, const void *))

/* Alternative implementation using swap instead of a temporary variable.
 * 
 * Note - This is approximately 25% slower. */
 
{
   unsigned char *h_ptr = (unsigned char *)v_array;
   unsigned i_count, i_next;
   for (i_count = 1; i_count < t_num; i_count++)
   {
      i_next = i_count;
      while(i_next > 0 && (v_compare(h_ptr + i_next * t_size, h_ptr + (i_next - 1) * t_size)) <= 0)
      {
         swap (h_ptr + i_next * t_size, h_ptr + (i_next - 1) * t_size, t_size);
         i_next--;
      }
   }
}

void shellsort (void *v_array, size_t t_num, size_t t_size, int (*v_compare)(const void *, const void *))

/* Based on K+R Ed 2 Page 62.
 * 
 * Starts  by  comparing elements that are separated by a gap that is  half
 * the distance between the first and last element, the gap is then reduced
 * by half and the process repeated until the gap is one. */
 
{
   unsigned char *h_ptr = (unsigned char *)v_array;
   size_t i_count, i_gap;                                                                 /* int gap, i, j, temp; */
   int i_next;                                                                            /* int gap, i, j, temp; */

   for (i_gap = t_num / 2; i_gap > 0; i_gap /= 2)                                         /* for (gap = n / 2; gap > 0; gap /= 2) */
      for (i_count = i_gap; i_count < t_num; i_count++)                                   /*    for (i = gap; i < n; i++) */
         for (i_next = i_count - i_gap; (i_next >= 0 && (                                 /*       for (j = i - gap; j >=0 && v[j] > v[j + gap]; j -= gap) */
            v_compare(h_ptr + (i_next + i_gap) * t_size, h_ptr + i_next * t_size)) < 0);  /*       { */
            i_next = i_next - i_gap )                                                     /*          temp = v[j]; */
            swap (h_ptr + i_next * t_size, h_ptr + (i_next + i_gap) * t_size, t_size);    /*          v[j] = v[j + gap]; */
                                                                                          /*          v[j + gap] = temp; */
                                                                                          /*       } */
}                                                                                

void _quicksort (void *v_array, size_t t_left, size_t t_right, size_t t_size, int (*v_compare)(const void *, const void *))

/* Based on K+R Ed 2 Page 120. */

{
   unsigned char *h_ptr = (unsigned char *)v_array;
   size_t i_count, i_last;                                                                /* int i_count, i_last; */

   if ((long int)t_left >= (long int)t_right) return; /* Compare signed values) */        /* if (i_left >= i_right) return; */
   swap (h_ptr + t_left * t_size, h_ptr + ((t_left + t_right) / 2) * t_size, t_size);     /* swap (p_array, i_left, (i_left + i_right)/2); */
   i_last = t_left;                                                                       /* i_last = i_left; */
   for (i_count = t_left + 1; i_count <= t_right; i_count++)                              /* for (i_count = i_left + 1; i_count <= i_right; i_count++) */
      if (v_compare (h_ptr + i_count * t_size, h_ptr + t_left * t_size) < 0)              /*    if ((*compare)(p_array[i_count], p_array[i_left]) < 0) */
         swap (h_ptr + ++i_last * t_size, h_ptr + i_count * t_size, t_size);              /*       swap(p_array, ++i_last, i_count); */
   swap (h_ptr + t_left * t_size, h_ptr + i_last * t_size, t_size);                       /* swap (p_array, i_left, i_last); */
   _quicksort (v_array, t_left, i_last - 1, t_size, v_compare);                           /* qsort (p_array, i_left, i_last - 1, compare); */
   _quicksort (v_array, i_last + 1, t_right, t_size, v_compare);                          /* qsort (p_array, i_last + 1, i_right, compare); */
}

void quicksort (void *v_array, size_t t_num, size_t t_size, int (*v_compare)(const void *, const void *))

/* Wrapper for _quicksort() to make conform to the same calling standard as
 * the implementation in stdlib. */
 
{
   _quicksort (v_array, 0, t_num - 1, t_size, v_compare);
}


void initint (int *i_array, size_t t_num)

/* Using  the built in random number generator will give a different set of
 * values with different compilers. */ 
/** 
{
   size_t i_count;

   if (t_num > 0)
   {
      srand(32765); 
      for (i_count = 0; i_count < SIZE; i_count++)
         i_array[i_count] = rand() % 199 - 99 ;
      i_compaires = 0;
      i_copies = 0;
      i_swaps = 0;
   }
}
*/

/* Using a fixed set of random numbers allows the performance of different 
 * systems/compilers to be compared with each other. */ 

{
   const int i_constant[SIZE] = 
   { 
       19, 456, 959, 227, 470, 258, 182, 369,
      568, 694, 248, 970, 198, 106, 308, 419,
      546, 773, 181, 440, 667, 470, 958, 282,
      852, 960, 800, 701, 447, 172, 497, 416,
      199, 754, 979, 250, 633, 713, 333, 143,
      354, 411, 682, 693, 876, 559, 712, 274,
      217, 250, 317, 371,  57, 877, 904, 545,
      736, 404, 450, 221, 986,  52, 152, 204,
      572, 266, 597, 193, 639, 776, 661, 307,
      745,  47, 921, 881, 178, 398, 420, 278,
        4, 561, 979, 837, 601, 865, 903, 327,
      772, 337, 462, 696, 619, 175, 677, 554,
      698, 403, 820, 835, 893, 916, 237, 664,
      745,  56, 459, 109, 357,  11, 105, 425,
       68,  20, 911, 927, 674, 812, 129, 442,
      306, 164, 213, 209, 744, 711, 231, 219,
      522, 122, 670, 273,  75, 770, 297, 570,
      484,  24, 888, 200, 245,  85, 436,  58,
      181, 410, 296, 380, 350,  20, 732, 717,
      811, 832,  28, 755, 320, 886, 779, 550,
      571, 286, 732,  33, 257, 377, 202, 612,
      636, 288, 151, 205, 497, 241, 940, 468,
      526, 621, 322, 847, 819,  93, 155, 398,
      917, 147, 812, 744, 758, 188, 701, 839,
      629, 574, 748, 285, 166,  40, 461, 349,
      907, 196, 560, 142, 353, 965, 911, 240,
      255, 576, 886, 857, 754, 132, 119, 580,
       57, 143, 552, 297, 232, 518, 826, 617,
      128,  62, 862, 115, 232, 617, 699, 723,
       62,   0, 813, 184, 450, 349, 880, 753,
       18, 458, 654, 555,  35, 621, 293, 688,
      802,  69, 586, 335, 442, 562, 100, 448,
      522, 854, 213, 814, 725, 286, 698, 428,
      230, 618, 546,  55, 429, 581, 909, 602,
      987, 752, 542, 392, 426, 453,  53, 648,
      420, 716, 580, 654, 559, 600,  68, 346,
      524, 181, 405, 189, 425, 158, 563, 186,
      714, 579, 341, 598, 822, 319,  20, 757,
       26, 440, 157, 941, 478, 113, 211, 613,
      151, 639, 360, 566, 805, 820, 627, 186,
      118, 298, 863, 842, 455, 380,  27, 161,
      556, 241, 219, 101, 933, 387, 314, 731,
      255,  86, 846, 121, 952, 400, 783, 724,
      898, 750, 523, 575, 621, 955, 142, 876,
      495, 177, 181, 152, 495, 951, 335, 845,
      704, 634, 795, 224, 650,  61, 554, 169,
      977, 874, 567, 840, 442, 402, 810, 997,
      446, 653, 524, 843, 117,  99, 211, 426,
      882, 865, 181, 109, 357, 605, 865, 458,
      270, 470, 751, 766, 601, 598, 765, 315,
      241, 537, 668, 314, 670, 136,  13, 398,
       31, 116, 811, 115, 372, 845,  91,  30,
      161, 125, 506,  40, 320, 551, 518, 180,
      703, 160, 596, 116, 597, 729, 408, 377,
      784, 351, 633, 917, 251, 684, 971, 546,
      555, 914,  66, 340, 935, 877, 881, 526,
      526,  74, 453, 997, 229, 568, 772, 260,
      771, 517, 167, 265, 563, 383,  93, 286,
      763, 628, 746, 867,  71, 764, 134, 930,
      718, 105, 324, 915,  45, 746, 735,  57,
      441, 235, 688,   6, 100, 577, 512, 695,
      517, 228, 964, 776, 930, 112, 934, 924,
      772, 556, 843, 230, 136, 614,  29, 945,
      340, 155, 408, 117, 592, 933, 298, 293,
      741, 902, 339, 497, 826,  85, 799, 985,
      195, 769, 228, 492, 808, 965, 114, 278,
      423, 854, 672, 586,  69, 540, 519, 253,
      258, 789, 463, 783, 394, 149, 197, 694,
      908, 210, 344, 815, 272,  79, 535, 388,
      429, 799, 993, 303, 192, 261, 287, 514,
      931, 512, 173, 304, 801, 464,  91, 233,
      888, 753, 988, 463, 751, 295, 596, 329,
      994, 131, 310, 195, 912, 158, 111, 788,
      473, 520, 888, 862,  36, 143, 554,  37,
      532, 905, 732, 562, 496, 270, 300, 697,
      469,  27, 596, 284, 177,  67, 577, 404,
      147, 995, 861,  93,   5, 902, 618, 438,
      428, 653, 371, 139, 225, 444, 699, 990,
      286, 440, 729,  85,  97, 791, 560, 940,
      849,  28, 769, 338, 753, 810, 193, 806,
      792, 847,  60, 102, 198, 457, 187, 321,
      554, 963, 570, 208, 813, 677, 300, 789,
      621, 556, 842, 139,   0,  56, 668, 173,
      739,   2, 503, 990, 790, 149, 391, 375,
      262, 571, 740, 344, 565, 979, 671, 519,
      917, 544, 267, 132,  85, 512, 665, 120,
      441, 529, 924, 475, 590, 595,  35, 484,
      164, 832, 536, 792, 557, 494, 231, 689,
      801, 292, 920, 715, 673, 767, 195, 926,
      634, 183, 584, 797,  68, 687, 326, 858,
      495, 786, 927, 566, 918, 939, 606, 763,
      284,  81, 233, 701, 447, 725,  64, 382,
      191, 530, 365, 617, 499, 661, 276, 566,
       82, 986, 994, 981, 269, 196, 951, 387,
      846, 664, 853, 943, 901, 450, 482, 501,
      346, 971,  29, 272, 651, 278, 522, 383,
      121, 868, 972, 452, 771, 574, 496,  15,
      725, 924, 754, 521, 150, 254,  54, 587,
      729, 632, 897, 771, 158, 359, 525, 310,
      328, 569, 882, 819, 897, 318, 898, 483,
      525, 485, 152, 733, 811,  62,  96, 317,
      357, 901, 457, 250, 881, 765, 943, 838,
        5,  22, 813, 157, 483, 510, 304, 750,
      292, 790, 578, 526, 793, 513, 149, 181,
      648, 848, 723, 257, 793, 838, 140, 406,
      793, 795,  94, 820, 582, 833,  83, 607,
      415, 815, 767, 155, 866, 183, 150, 174,
      168, 780, 666, 555,  31, 377, 453,   8,
      361, 787, 410, 826, 523, 379, 146, 776,
      478, 917, 485, 184, 431, 384, 187, 180,
      828,  49,  58, 147, 726, 833,  33,  83,
      346, 862, 795, 775, 597, 735, 258, 312,
      453, 728,   8, 867, 179, 357,  89, 634,
      246, 242, 291, 655, 188, 936, 389, 625,
      643, 708, 277, 534, 689,  44, 343, 628,
      146,  65, 294, 944, 900, 259, 241, 963,
      272, 793, 491, 291,  11, 343, 441, 865,
      965, 922,  25, 209, 656, 657, 775, 140,
      386, 419, 290, 738, 308, 701, 319, 874,
      620, 926, 928, 492,  84,  39, 343, 479,
      817, 412, 686, 864, 687, 592, 309, 266,
      102, 384, 961, 792, 974, 407,  12, 133,
      918, 567, 830, 780, 665, 797,  20, 642,
      653, 847,  15, 819, 961, 875, 620, 329,
      781, 500, 380, 359, 312, 761,  15, 819
   };

   size_t i_count;

   if (t_num > 0)
   {
      for (i_count = 0; i_count < t_num; i_count++)
         i_array[i_count] = i_constant[i_count];
      i_compaires = 0;
      i_copies = 0;
      i_swaps = 0;
   }
}

void print(char *s_name, double d_time)
{
   printf ("%s%*s : %6.3f s", s_name, (int)(14 - strlen(s_name)),  "", (double)(d_time) / CLOCKS_PER_SEC);
   if (i_compaires) printf ("%*s%d comparisons", (int)(8 - log10(i_compaires)), "", i_compaires);
   if (i_copies) printf ("%*s%d copies", (int)(8 - log10(i_copies)), "", i_copies);
   if (i_swaps) printf ("%*s%d swaps", (int)(8 - log10(i_swaps)), "", i_swaps);
   printf ("\n");
}

int main(void)
{
   clock_t t_start, t_finish, t_baseline = 0;
   
   int i_numbers[SIZE];
   int i_count, i_size;

   i_size = sizeof(i_numbers)/sizeof(i_numbers[0]);

   t_start = clock();
   for (i_count = 0; i_count < ITERATIONS; i_count++)
      initint (i_numbers, i_size);
   t_finish = clock();
   t_baseline = t_finish - t_start;

   t_start = clock();
   for (i_count = 0; i_count < ITERATIONS; i_count++)
   {
      initint (i_numbers, i_size);
      bubblesort (i_numbers, i_size, sizeof(*i_numbers), cmpint);
   }
   t_finish = clock();
   print ("bubblesort", (double)(t_finish  - t_start - t_baseline));

   t_start = clock();
   for (i_count = 0; i_count < ITERATIONS; i_count++)
   {
      initint (i_numbers, i_size);
      exchangesort (i_numbers, i_size, sizeof(*i_numbers), cmpint);
   }
   t_finish = clock();
   print ("exchangesort", (double)(t_finish  - t_start - t_baseline));

   /** Insertion sort using swap()
   t_start = clock();
   for (i_count = 0; i_count < ITERATIONS; i_count++)
   {
      initint (i_numbers, i_size);
      _insertionsort (i_numbers, i_size, sizeof(*i_numbers), cmpint);
   }
   t_finish = clock();
   print ("insertionsort", (double)(t_finish  - t_start - t_baseline));
   */

   t_start = clock();
   for (i_count = 0; i_count < ITERATIONS; i_count++)
   {
      initint (i_numbers, i_size);
      insertionsort (i_numbers, i_size, sizeof(*i_numbers), cmpint);
   }
   t_finish = clock();
   print ("insertionsort", (double)(t_finish  - t_start - t_baseline));

   t_start = clock();
   for (i_count = 0; i_count < ITERATIONS; i_count++)
   {
      initint (i_numbers, i_size);
      shellsort (i_numbers, i_size, sizeof(*i_numbers), cmpint);
   }
   t_finish = clock();
   print ("shellsort", (double)(t_finish  - t_start - t_baseline));

   t_start = clock();
   for (i_count = 0; i_count < ITERATIONS; i_count++)
   {
      initint (i_numbers, i_size);
      quicksort (i_numbers, i_size, sizeof(*i_numbers), cmpint);
   }
   t_finish = clock();
   print ("quicksort", (double)(t_finish  - t_start - t_baseline));

   t_start = clock();
   for (i_count = 0; i_count < ITERATIONS; i_count++)
   {
      initint (i_numbers, i_size);
      qsort (i_numbers, i_size, sizeof(*i_numbers), cmpint);
   }
   t_finish = clock();
   print ("quicksort (*)", (double)(t_finish  - t_start - t_baseline));
}
