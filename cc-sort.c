/*
 * cc-sort.c
 *
 * Copyright(C)2024  MT
 *
 * A collection of routines to sort an integer array.
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
 * 30 Nov 24   0.1   - Initial version - MT
 *  5 Dec 24   0.2   - Added comb sort and alternate bubble sort - MT
 *                   - Defined 'True' and 'False' - MT
 *
 */

#define  NAME        "cc-sort"
#define  VERSION     "0.1"
#define  BUILD       "0001"
#define  DATE        "30 Nov 24"
#define  AUTHOR      "MT"

#include <stdio.h>
#include <stdlib.h>

#define  SIZE        11

#define True 1
#define False !(True)

void swap (int a[], int m, int n)
{
   int tmp;
   tmp = a[m];
   a[m] = a[n];
   a[n] = tmp;
}

void shuffle (int a[], int n) 
{
   int i, j;

   for (i = n - 1; i > 0 ; i--)
   {
      j = (int)((double)i * (rand() / (RAND_MAX + 1.0)));
      swap (a, i, j);
   }
}

void reverse (int a[], int n) 

/* Based on K+R Ed 2 Page 62 */
{
   int i = 0;
      while (i < --n)
      {
         swap (a, i, n);
         i++;
      }
}

void init (int *a, int n)
{
   int i;
   for (i = 0; i < n; i++)
      a[i] = i - n / 2;
   srand (1966);
   shuffle (a , n);
}

void print (int *a, int n)
{
   int i;
   if (n > 0)
   {
      printf ("(%3d", a[0]);
      for (i = 1; i < n; i++)
         printf (", %3d", a[i]);
   }
   printf (")\n");
}

void bubblesort (int a[], int n) 

/* Iterates over the elements in the array comparing each pair of  adjacent
 * elements, swapping pairs of elements that are out of order. */
{
   int i, j;  
   for (i = 0; i < n - 1; i++)
      for (j = 0; j < n - i - 1; j++)
         if (a[j] > a[j + 1])
            swap (a, j, j + 1);
}

void _bubblesort (int *a, int n)
{
   int i, t, j = n, s = True;

   while (s) {
      s = False;
      for (i = 1; i < j; i++)
      {
         if (a[i] < a[i - 1])
         {
            t = a[i];
            a[i] = a[i - 1];
            a[i - 1] = t;
            s = True;
         }
      }
      j--;
   }
}

void exchangesort (int a[], int n)

/* Begins  with  the first element in the array and compares it with  every
 * following  element in the array.  If any of the following  elements  are
 * smaller than the current element, it is swapped with the current element
 * and the process repeated for the next element in the array */
{
   int i, j;
   for (i = 0; i < n - 1; i++)
      for (j = i + 1; j < n; j++)
          if (a[i] > a[j]) 
            /* If  the  previous element is bigger than the next swap  them 
             * over. */
            swap (a, i, j);
}

void insertionsort (int a[], int n) 

/* Compares  each successive element in the array with all of the preceding 
 * elements.  When an appropriate position if found the element is inserted
 * in its position, and all the other elements are moved down one place. */
{
   int i, j, k;

   for (i = 1; i < n; i++)
   {
      j = i;
      k = a[i];
      while (j > 0 && k < a[j - 1])
      {
         a[j] = a[j - 1];
         j--;
      }
      a[j] = k;
   }
}

void _insertionsort (int a[], int n) 

/* Insertion sort using swap */
{
   int i, j;
   for (i = 1; i < n; i++)
   {
      j = i;
      while (j > 0 && a[j] <= a[j - 1])
      {
         swap (a, j, j - 1);
         j--;
      }
   }
}

void combsort (int *a, int n)

/* The comb sort improves on the bubble sort by comparing values  separated 
 * by a variable gap. After each iteration the gap is reduced by a until it 
 * reaches the value of 1. */
{            
   int i, j, k, s = True;

   k = n;
   while (k > 1 || s == True)
   {
      k = k * 10 / 13;
      if (k == 9 || k == 10) k = 11;
      if (k < 1) k = 1;
      s = False;
      for (i = 0, j = k; j < n; i++, j++)
      {
         if (a[i] > a[j])
         {
            swap (a, i, j);
            s = True;
         }
      }
   }
}

void shellsort (int a[], int n) 

/* Based on K+R Ed 2 Page 62
 * 
 * Starts  by  comparing elements that are separated by a gap that is  half
 * the distance between the first and last element, the gap is then reduced
 * by half and the process repeated until the gap is one.  */
{
   int i, j, k;
   for (k = n / 2; k > 0; k /= 2)
      for (i = k; i < n; i++)
         for (j = i - k; j >=0 && a[j] > a[j + k]; j -= k)
            swap (a, j, j + k);
}   

void _quicksort (int a[], int m, int n)

/* Based on K+R Ed 2 Page 120 */
{
   int i, l;

   if (m >= n) return;
   swap (a, m, (m + n) / 2);
   l = m;
   for (i = m + 1; i <= n; i++)
      if (a[i] < a[m])
         swap(a, ++l, i);
   swap (a, m, l);
   _quicksort (a, m, l - 1);
   _quicksort (a, l + 1, n);
}

void quicksort (int a[], int n) 

/* Wrapper for _quicksort() to match the other sort functions */
{
   _quicksort (a, 0, n - 1);
}

int main(void)
{
   int a[SIZE];

   printf ("bubble sort\n");
   init (a, SIZE);
   print (a, SIZE);
   bubblesort (a, SIZE);
   print (a, SIZE);

   printf ("comb sort\n");
   init (a, SIZE);
   print (a, SIZE);
   combsort (a, SIZE);
   print (a, SIZE);

   printf ("exchange sort\n");
   init (a, SIZE);
   print (a, SIZE);
   exchangesort (a, SIZE);
   print (a, SIZE);

   printf ("insertion sort\n");
   init (a, SIZE);
   print (a, SIZE);
   insertionsort (a, SIZE);
   print (a, SIZE);

   printf ("shell sort\n");
   init (a, SIZE);
   print (a, SIZE);
   shellsort (a, SIZE);
   print (a, SIZE);

   printf ("quick sort\n");
   init (a, SIZE);
   print (a, SIZE);
   quicksort (a, SIZE);
   print (a, SIZE);

   printf ("reverse\n");
   print (a, SIZE);
   reverse (a, SIZE);
   print (a, SIZE);
}
