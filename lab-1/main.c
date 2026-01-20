#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// The time complexity is O(n) because we only have a single for loop.

#define BOOL_TO_CSTR(str, x) {                              \
    if(x) printf("%s: True\n", str);                        \
    else printf("%s:  False\n", str);                       \
  }

bool
is_palindrome(const char *str)
{
  size_t len = strlen(str);
  char reverse[len + 1];
  reverse[len] = '\0';
  int j = 0;
  for (size_t i = 0; i < len ; i++) {
    reverse[i] = str[len - 1 - i];
  }
  if (strcmp(reverse, str) != 0) return false;
  return true;
}

int
main(void)
{
  // NOTE: Truth value expected.
  char valid[3][10] = { "nun", "bob", "mom" };
  for (int i = 0; i < 3; i++) {
    bool x = is_palindrome(valid[i]);
    BOOL_TO_CSTR(valid[i],x);
  }

  // NOTE: False value expected.
  char invalid[3][10] = { "test", "hey", "im" };
  for (int i = 0; i < 3; i++) {
    bool x = is_palindrome(invalid[i]);
    BOOL_TO_CSTR(invalid[i],x);
  }

}
