#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Custom string implementation */
typedef struct {
  uint8_t *data;
  size_t size;
} string;

#define CAP 1024
#define RATE 0.8f
#define ARRAY_LEN(arr) sizeof((arr)) / sizeof((arr[0]))

#define CLIT_TO_STR(cliteral, str) {                 \
    do {                                             \
      strcpy((char *)(str)->data, (cliteral));       \
      (str)->size = strlen((cliteral));              \
    } while(0);                                      \
}

#define STR_NULL_APPEND(str) {                  \
    do  {                                       \
      (str)->data[(str)->size] = '\0';          \
    } while(0);                                 \
  }

#define SV_FMT "%.*s"
#define SV_ARGS(str) (int)(str).size, (char *)(str).data

string
read_file(const char *path)
{
  string str = {0};
  str.data = malloc(sizeof(sizeof(uint8_t) * CAP));
  if(!str.data) return (string){ .data = NULL, .size = 0 };

  FILE *fptr = fopen(path, "r");
  if (!fptr) return (string){ .data = NULL, .size = 0 };

  fseek(fptr, 0, SEEK_END);
  str.size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);

  if (str.size >= CAP) {
    str.data = realloc(str.data, (str.size + 1) * sizeof(str.data));
    assert(str.data != NULL);
  }
  fread(str.data, 1, str.size, fptr);
  STR_NULL_APPEND(&str);

  fclose(fptr);
  return str;
}

/* Hash related code */

typedef struct {
  string key;
  int value;
} hash_entry;

typedef struct {
  hash_entry *table;
  size_t count;
  size_t capacity;
  size_t collision;
} hash_table;

unsigned int
hash(const char *str, size_t capacity) {
  unsigned long hash = 6000;
  int c;
  while((c = *str++)) {
    // NOTE: I moved away from ((hash << 5) + hash) to (hash * 33)
    hash = (hash * 33) + c;
  }
  return hash % capacity;
}

hash_table*
create_hash_table(size_t capacity)
{
  hash_table *ht = malloc(sizeof(*hash));
  assert(ht != NULL);

  ht->capacity = capacity;
  ht->count = 0;
  ht->collision = 0;

  ht->table = malloc(ht->capacity * sizeof(*ht->table));
  memset(ht->table, 0, ht->capacity * sizeof(*ht->table));
  return ht;
}

void
insert(hash_table *ht, string key)
{
  if(ht->count >= ht->capacity * RATE) {
    ht->capacity *= 2;
    ht->table = realloc(ht->table, sizeof(*ht->table) * ht->capacity);
    assert(ht->table != NULL);
  }
  unsigned int index = hash((char *)key.data, ht->capacity);
  while(ht->table[index].key.data != NULL) {
    if(strcmp((char *)ht->table[index].key.data, (char *)key.data) == 0) {
      ht->table[index].value++;
      return;
    }
    ht->collision += 1;
    index = (index + 1) % ht->capacity;
  }
  ht->table[index].key = key;
  ht->table[index].value = 1;
  ht->count++;
}

float
collision_perc(hash_table *ht)
{
    return (float)ht->collision / (float)ht->count * 100.0;
}

int
main() {
    const char *path = "google-10000-english-usa.txt";
    string str = read_file(path);

    size_t capacity = (size_t)(RATE * str.size / sizeof(char));
    hash_table *ht = create_hash_table(capacity);

    char *token = strtok((char *)str.data, "\n");
    while (token != NULL) {
        string key = {.data = (uint8_t *)malloc(strlen(token) + 1), .size = strlen(token)};
        strcpy((char *)key.data, token);
        insert(ht, key);
        free(key.data);
        token = strtok(NULL, "\n");
    }

    printf("Collision percentage: %.2f%%\n", collision_perc(ht));

    free(str.data);
    return 0;
}
