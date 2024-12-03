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
 *
 */

#define  NAME        "gcc-sort"
#define  VERSION     "0.2"
#define  BUILD       "0005"
#define  DATE        "03 Nov 24"
#define  AUTHOR      "MT"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define  ITERATIONS  1000
#define  SIZE        1000

#if defined(VMS) && defined(VAX) && !defined(CLOCKS_PER_SEC)
#define  CLOCKS_PER_SEC CLK_TCK
#endif

int cmpint (const void *h_left, const void *h_right)
{
   int i_left = *(int *)h_left;
   int i_right = *(int *)h_right;
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

   while (t_size-- > 0) /* Swap each byte in turn. */
      *h_left++ = *h_right++;
}

void shuffle (void *v_array, size_t t_num, size_t t_size)
{
   unsigned char *h_ptr = (unsigned char *)v_array;
   size_t i_count, i_random;

   for (i_count = t_num - 1; i_count > 0 ; i_count--)
   {
      i_random = (int)((double)i_count * (rand() / (RAND_MAX + 1.0)));
      swap (h_ptr + i_count * t_size, h_ptr + i_random * t_size, t_size);
   }
}

void reverse (void *v_array, size_t t_num, size_t t_size)

/* Based on K+R Ed 2 Page 62. */
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
   unsigned char *h_tmp = (unsigned char *)malloc(t_size+10);
   size_t i_count, i_next;

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

/* Alternative implementation using swap instead of a temporary vairable.
 * 
 * Note - This is approximately 25% slower.
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
} */

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

int main(void)
{
   clock_t t_start, t_finish, t_baseline;
   int i_numbers[SIZE];
   int i_count, i_counter;
   int i_size;
   
   i_size = sizeof(i_numbers)/sizeof(i_numbers[0]);

   for (i_counter = 0; i_counter < ITERATIONS; i_counter++)
   {
      for (i_count = 0; i_count < SIZE; i_count++)
         i_numbers[i_count] = rand() % 199 - 99 ;
   }

   t_start = clock();
   for (i_counter = 0; i_counter < ITERATIONS; i_counter++)
   {
      for (i_count = 0; i_count < SIZE; i_count++)
         i_numbers[i_count] = rand() % 199 - 99 ;
   }
   t_finish = clock();
   t_baseline = t_finish - t_start;

   t_start = clock();
   for (i_counter = 0; i_counter < ITERATIONS; i_counter++)
   {
      for (i_count = 0; i_count < SIZE; i_count++)
         i_numbers[i_count] = rand() % 199 - 99 ;
      bubblesort (i_numbers, i_size, sizeof(*i_numbers), cmpint);
   }
   t_finish = clock();
   printf ("bubblesort    : %6.3f s\n", (double)(t_finish  - t_start - t_baseline) / CLOCKS_PER_SEC);

   t_start = clock();
   for (i_counter = 0; i_counter < ITERATIONS; i_counter++)
   {
      for (i_count = 0; i_count < SIZE; i_count++)
         i_numbers[i_count] = rand() % 199 - 99 ;
      exchangesort (i_numbers, i_size, sizeof(*i_numbers), cmpint);
   }
   t_finish = clock();
   printf ("exchangesort  : %6.3f s\n", (double)(t_finish  - t_start - t_baseline) / CLOCKS_PER_SEC);

   t_start = clock();
   for (i_counter = 0; i_counter < ITERATIONS; i_counter++)
   {
      for (i_count = 0; i_count < SIZE; i_count++)
         i_numbers[i_count] = rand() % 199 - 99 ;
      insertionsort (i_numbers, i_size, sizeof(*i_numbers), cmpint);
   }
   t_finish = clock();
   printf ("insertionsort : %6.3f s\n", (double)(t_finish  - t_start - t_baseline) / CLOCKS_PER_SEC);

   t_start = clock();
   for (i_counter = 0; i_counter < ITERATIONS; i_counter++)
   {
      for (i_count = 0; i_count < SIZE; i_count++)
         i_numbers[i_count] = rand() % 199 - 99 ;
      shellsort (i_numbers, i_size, sizeof(*i_numbers), cmpint);
   }
   t_finish = clock();
   printf ("shellsort     : %6.3f s\n", (double)(t_finish  - t_start - t_baseline) / CLOCKS_PER_SEC);

   t_start = clock();
   for (i_counter = 0; i_counter < ITERATIONS; i_counter++)
   {
      for (i_count = 0; i_count < SIZE; i_count++)
         i_numbers[i_count] = rand() % 199 - 99 ;
      quicksort (i_numbers, i_size, sizeof(*i_numbers), cmpint);
   }
   t_finish = clock();
   printf ("quicksort     : %6.3f s\n", (double)(t_finish  - t_start - t_baseline) / CLOCKS_PER_SEC);

   t_start = clock();
   for (i_counter = 0; i_counter < ITERATIONS; i_counter++)
   {
      for (i_count = 0; i_count < SIZE; i_count++)
         i_numbers[i_count] = rand() % 199 - 99 ;
      qsort (i_numbers, i_size, sizeof(*i_numbers), cmpint);
   }
   t_finish = clock();
   printf ("quicksort (*) : %6.3f s\n", (double)(t_finish  - t_start - t_baseline) / CLOCKS_PER_SEC);
}
