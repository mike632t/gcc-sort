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
 *
 */

#define  NAME        "cc-sort"
#define  VERSION     "0.1"
#define  BUILD       "0001"
#define  DATE        "30 Nov 24"
#define  AUTHOR      "MT"

#include <stdio.h>
#include <stdlib.h>

#define  ITERATIONS  1000
#define  SIZE        11

void swap (int arr[], int m, int n)
{
   int tmp;
   tmp = arr[m];
   arr[m] = arr[n];
   arr[n] = tmp;
}

void shuffle (int arr[], int n) 
{
   int i, j;

   for (i = n - 1; i > 0 ; i--)
   {
      j = (int)((double)i * (rand() / (RAND_MAX + 1.0)));
      swap (arr, i, j);
   }
}

void reverse (int arr[], int n) 

/* Based on K+R Ed 2 Page 62 */
{
   int i = 0;
      while (i < --n)
      {
         swap (arr, i, n);
         i++;
      }
}

void init (int *arr, int n)
{
   int i;
   for (i = 0; i < n; i++)
      arr[i] = i - n / 2;
   srand (1966);
   shuffle (arr , n);
}

void print (int *arr, int n)
{
   int i;
   if (n > 0)
   {
      printf ("(%3d", arr[0]);
      for (i = 1; i < n; i++)
         printf (", %3d", arr[i]);
   }
   printf (")\n");
}

void bubblesort (int arr[], int n) 

/* Iterates over the elements in the array comparing each pair of  adjacent
 * elements, swapping pairs of elements that are out of order. */
{
   int i, j;  
   for (i = 0; i < n - 1; i++)
      for (j = 0; j < n - i - 1; j++)
         if (arr[j] > arr[j + 1])
            swap (arr, j, j + 1);
}  

void exchangesort (int arr[], int n)

/* Begins  with  the first element in the array and compares it with  every
 * following  element in the array.  If any of the following  elements  are
 * smaller than the current element, it is swapped with the current element
 * and the process repeated for the next element in the array */
{
   int i, j;
   for (i = 0; i < n - 1; i++)
      for (j = i + 1; j < n; j++)
          if (arr[i] > arr[j]) 
            /* If  the  previous element is bigger than the next swap  them 
             * over. */
            swap (arr, i, j);
}

void insertionsort (int arr[], int n) 

/* Compares  each successive element in the array with all of the preceding 
 * elements.  When an appropriate position if found the element is inserted
 * in its position, and all the other elements are moved down one place. */
{
   int i, j, k;

   for (i = 1; i < n; i++)
   {
      j = i;
      k = arr[i];
      while (j > 0 && k < arr[j - 1])
      {
         arr[j] = arr[j - 1];
         j--;
      }
      arr[j] = k;
   }
}

void insertionsortswap (int arr[], int n) 

/* Insertion sort using swap */
{
   int i, j;
   for (i = 1; i < n; i++)
   {
      j = i;
      while (j > 0 && arr[j] <= arr[j - 1])
      {
         swap (arr, j, j - 1);
         j--;
      }
   }
}

void shellsort (int arr[], int n) 

/* Based on K+R Ed 2 Page 62
 * 
 * Starts  by  comparing elements that are separated by a gap that is  half
 * the distance between the first and last element, the gap is then reduced
 * by half and the process repeated until the gap is one.  */
{
   int i, j, k;
   for (k = n / 2; k > 0; k /= 2)
      for (i = k; i < n; i++)
         for (j = i - k; j >=0 && arr[j] > arr[j + k]; j -= k)
            swap (arr, j, j + k);
}   

void _quicksort (int arr[], int m, int n)

/* Based on K+R Ed 2 Page 120 */
{
   int i, l;

   if (m >= n) return;
   swap (arr, m, (m + n)/2);
   l = m;
   for (i = m + 1; i <= n; i++)
      if (arr[i] < arr[m])
         swap(arr, ++l, i);
   swap (arr, m, l);
   _quicksort (arr, m, l - 1);
   _quicksort (arr, l + 1, n);
}

void quicksort (int arr[], int n) 

/* Wrapper for _quicksort() to match the other sort functions */
{
   _quicksort (arr, 0, n - 1);
}

int main(void)
{
   int arr[SIZE];

   printf ("bubble sort\n");
   init (arr, SIZE);
   print (arr, SIZE);
   bubblesort (arr, SIZE);
   print (arr, SIZE);

   printf ("exchange sort\n");
   init (arr, SIZE);
   print (arr, SIZE);
   exchangesort (arr, SIZE);
   print (arr, SIZE);

   printf ("insertion sort\n");
   init (arr, SIZE);
   print (arr, SIZE);
   insertionsort (arr, SIZE);
   print (arr, SIZE);

   printf ("shell sort\n");
   init (arr, SIZE);
   print (arr, SIZE);
   shellsort (arr, SIZE);
   print (arr, SIZE);

   printf ("quick sort\n");
   init (arr, SIZE);
   print (arr, SIZE);
   quicksort (arr, SIZE);
   print (arr, SIZE);

   printf ("reverse\n");
   print (arr, SIZE);
   reverse (arr, SIZE);
   print (arr, SIZE);}
