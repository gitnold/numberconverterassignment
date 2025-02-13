// code is under MIT license
//
// compiled with :
// clang -o conv conv.c -Wall -Wextra -Werror -std=c11 -pedantic -lm

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int *items;
  size_t len;
  size_t capacity;
} ArrayList;

ArrayList *arraylist_init(void) {
  ArrayList *obj = (ArrayList *)malloc(sizeof(ArrayList));
  if (!obj) {
    return NULL;
  }
  obj->items = (int *)malloc(sizeof(int) * 10);
  if (!obj->items) {
    return NULL;
  }
  obj->len = 0;
  obj->capacity = 10;
  return obj;
}

void arraylist_append(ArrayList *arr, int value) {
  if (arr->len >= arr->capacity) {
    int *newbuffer = (int *)malloc(sizeof(int) * arr->capacity * 2);
    memcpy(newbuffer, arr->items, arr->len * sizeof(int));
    free(arr->items);
    arr->items = newbuffer;
  }
  arr->items[arr->len] = value;
  arr->len++;
}

void arraylist_free(ArrayList *arr) {
  if (arr) {
    free(arr->items);
    free(arr);
  }
}

void decimal_any_base(size_t decimal, size_t base) {
  ArrayList *arr = arraylist_init();
  if (!arr) {
    printf("Could not initialize array\n");
    exit(1);
  }
  while (decimal != 0) {
    int rem = decimal % base;
    arraylist_append(arr, (int)rem);
    decimal /= base;
  }
  printf("Converted number to base %zu: \n", base);
  for (size_t i = arr->len; i > 0; i--) {
    int digit = arr->items[i - 1];
    if (digit >= 10) {
      switch (digit) {
      case 10:
        printf("A");
        continue;
        break;
      case 11:
        printf("B");
        continue;
        break;
      case 12:
        printf("C");
        continue;
        break;
      case 13:
        printf("D");
        continue;
        break;
      case 14:
        printf("E");
        continue;
        break;
      case 15:
        printf("F");
        continue;
        break;
      }
    }
    printf("%d", digit);
  }
  printf("\n");

  arraylist_free(arr);
}

void binary_any_base(size_t binary, size_t base) {
  int decimal = 0, i = 0;
  while (binary != 0) {
    int last_digit = binary % 10;
    decimal += last_digit * pow(2, i);
    binary /= 10;
    i++;
  }
  decimal_any_base(decimal, base);
}

void hex_any_base(size_t binary, size_t base) {
  int decimal = 0, i = 0;
  while (binary != 0) {
    int last_digit = binary % 10;
    // bit shifting??
    decimal += last_digit * pow(2, i);
    binary /= 10;
    i++;
  }
  decimal_any_base(decimal, base);
}

void octal_any_base(size_t octal, size_t base) {
  // int counter = 0;
  int place_value, decimal;
  decimal = 0;
  place_value = 0;
  if (octal == 0)
    printf("Converted %zu to base %zu : 0", octal, base);

  while (octal != 0) {
    int last_digit = octal % 10;
    decimal += last_digit * pow(8, place_value);
    octal /= 10;
    place_value++;
  }
  decimal_any_base(decimal, base);
}

void printWelcome(void) {
  printf(">----- WELCOME TO THE NUMBER SYSTEMS CONVERTER (^_^) ------<\n");
  printf("-> decimal [t][10]\n-> hex [x][16]\n-> octal [o][8]\n-> Binary "
         "[n][2]\n");
  printf("Enter expression[ <number> <source base><target base>  e.g ff x8 -> "
         "converts hex to "
         "octal]\n~~~>");
}

int main(void) {
  char expression[70];
  int decimal, base;
  char source_base;

  printWelcome();

  fgets(expression, 70, stdin);
  char *hexchar;
  char hex[] = "abcdef";
  hexchar = strpbrk(expression, hex);
  sscanf(expression, "%*d %d", &base);
  if (hexchar != 0) {
    sscanf(expression, "%x %c%d", &decimal, &source_base, &base);
  } else {
    sscanf(expression, "%d %c%d", &decimal, &source_base, &base);
  }

  switch (source_base) {
  case 'n':
    decimal_any_base(decimal, base);
    break;
  case 'o':
    octal_any_base(decimal, base);
    break;
  case 't':
    decimal_any_base(decimal, base);
    break;
  case 'x':
    hex_any_base(decimal, base);
    break;
  default:
    printf("Invalid base!!");
    break;
  }
}
