#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bubble_sort_int (int arr[], int n)
{
  int i, j, temp;

  for (i = 0; i < n - 1; i++)
    {
      for (j = 0; j < n - i - 1; j++)
        {
          if (arr[j] > arr[j + 1])
            {
              temp = arr[j];
              arr[j] = arr[j + 1];
              arr[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_string (char *arr[], int n)
{
  int i, j;
  char *temp;

  for (i = 0; i < n - 1; i++)
    {
      for (j = 0; j < n - i - 1; j++)
        {
          if (strcmp (arr[j], arr[j + 1]) > 0)
            {
              temp = arr[j];
              arr[j] = arr[j + 1];
              arr[j + 1] = temp;
            }
        }
    }
}

void print_int_array (int arr[], int n)
{
  int i;

  printf ("[");
  for (i = 0; i < n; i++)
    {
      printf ("%d", arr[i]);
      if (i < n - 1)
        printf (", ");
    }
  printf ("]\n");
}

void print_string_array (char *arr[], int n)
{
  int i;

  printf ("[");
  for (i = 0; i < n; i++)
    {
      printf ("'%s'", arr[i]);
      if (i < n - 1)
        printf (", ");
    }
  printf ("]\n");
}

int
main (void)
{
  printf ("Testing with integers:\n");
  int int_arr[] = {5, 2, 4, 3, 10, 7, 1, 9, 6, 8};
  int int_size = sizeof (int_arr) / sizeof (int_arr[0]);

  printf ("Original array: ");
  print_int_array (int_arr, int_size);

  bubble_sort_int (int_arr, int_size);

  printf ("Sorted array:   ");
  print_int_array (int_arr, int_size);

  printf ("\nTesting with strings (Bonus):\n");
  char *str_arr[] = {"banana", "apple", "carrot", "cardamon",
                     "donut", "taco", "pasta", "mushrooms"};
  int str_size = sizeof (str_arr) / sizeof (str_arr[0]);

  printf ("Original array: ");
  print_string_array (str_arr, str_size);

  bubble_sort_string (str_arr, str_size);

  printf ("Sorted array:   ");
  print_string_array (str_arr, str_size);

  return 0;
}
