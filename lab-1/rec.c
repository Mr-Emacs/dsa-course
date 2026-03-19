#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BOOL_TO_CSTR(str, x) {                              \
    if(x) printf("%s: True\n", str);                        \
    else printf("%s:  False\n", str);                       \
  }

bool
is_palindrome(const char *str, int left, int right)
{
    if (left >= right) return true;
    if (str[left] != str[right]) return false;
    return is_palindrome(str, left + 1, right - 1);
}

#define foreach(i, xs) for (i = 0; i < xs; ++i)
int main()
{
    int i;

    char valid[3][10] = { "nun", "bob", "mom" };
    foreach(i, 3) {
        BOOL_TO_CSTR(valid[i],
            is_palindrome(valid[i], 0, strlen(valid[i]) - 1));
    }

    // NOTE: False value expected.
    char invalid[3][10] = { "test", "hey", "tim" };
    foreach(i, 3) {
        BOOL_TO_CSTR(invalid[i],
            is_palindrome(invalid[i], 0, strlen(invalid[i]) - 1));
    }
}
