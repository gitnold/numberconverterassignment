// code is under MIT license
//
// compiled with :
// clang -o conv conv.c -Wall -Wextra -Werror -std=c11 -pedantic -lm

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to hold an array list
typedef struct {
  int *items; // Pointer to the array of integers
  size_t len; // Current length of the array
  size_t capacity; // Maximum capacity of the array
} ArrayList;

// Initialize an ArrayList
ArrayList *arraylist_init(void) {
  ArrayList *obj = (ArrayList *)malloc(sizeof(ArrayList)); // Allocate memory for the ArrayList struct
  if (!obj) { // Check if memory allocation failed
    return NULL;
  }
  obj->items = (int *)malloc(sizeof(int) * 10); // Allocate memory for the array of integers
  if (!obj->items) { // Check if memory allocation failed
    return NULL;
  }
  obj->len = 0; // Initialize length to 0
  obj->capacity = 10; // Initialize capacity to 10
  return obj;
}

// Append a value to the ArrayList
void arraylist_append(ArrayList *arr, int value) {
  if (arr->len >= arr->capacity) { // Check if the array is full
    int *newbuffer = (int *)malloc(sizeof(int) * arr->capacity * 2); // Allocate memory for a new array with double the capacity
    memcpy(newbuffer, arr->items, arr->len * sizeof(int)); // Copy the existing array to the new array
    free(arr->items); // Free the old array
    arr->items = newbuffer; // Update the pointer to the new array
  }
  arr->items[arr->len] = value; // Add the new value to the array
  arr->len++; // Increment the length
}

// Free the ArrayList
void arraylist_free(ArrayList *arr) {
  if (arr) { // Check if the ArrayList exists
    free(arr->items); // Free the array of integers
    free(arr); // Free the ArrayList struct
  }
}

// Convert a decimal number to any base
void decimal_any_base(size_t decimal, size_t base) {
  ArrayList *arr = arraylist_init(); // Initialize an ArrayList
  if (!arr) { // Check if initialization failed
    printf("Could not initialize array\n");
    exit(1);
  }
  while (decimal != 0) { // Loop until the decimal number is 0
    int rem = decimal % base; // Get the remainder when dividing by the base
    arraylist_append(arr, (int)rem); // Append the remainder to the ArrayList
    decimal /= base; // Divide the decimal number by the base
  }
  printf("Converted number to base %zu: \n", base); // Print the base
  for (size_t i = arr->len; i > 0; i--) { // Loop through the ArrayList in reverse order
    int digit = arr->items[i - 1]; // Get the digit
    if (digit >= 10) { // Check if the digit is a letter
      switch (digit) { // Print the letter
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
    printf("%d", digit); // Print the digit
  }
  printf("\n");

  arraylist_free(arr); // Free the ArrayList
}

// Convert a binary number to any base
void binary_any_base(size_t binary, size_t base) {
  int decimal = 0, i = 0; // Initialize the decimal number and the counter
  while (binary != 0) { // Loop until the binary number is 0
    int last_digit = binary % 10; // Get the last digit
    decimal += last_digit * pow(2, i); // Add the digit multiplied by 2 raised to the power of the counter
    binary /= 10; // Divide the binary number by 10
    i++; // Increment the counter
  }
  decimal_any_base(decimal, base); // Convert the decimal number to the target base
}

// Convert a hexadecimal number to any base
void hex_any_base(size_t binary, size_t base) {
  int decimal = 0, i = 0; // Initialize the decimal number and the counter
  while (binary != 0) { // Loop until the binary number is 0
    int last_digit = binary % 10; // Get the last digit
    // bit shifting??
    decimal += last_digit * pow(2, i); // Add the digit multiplied by 2 raised to the power of the counter
    binary /= 10; // Divide the binary number by 10
    i++; // Increment the counter
  }
  decimal_any_base(decimal, base); // Convert the decimal number to the target base
}

// Convert an octal number to any base
void octal_any_base(size_t octal, size_t base) {
  // int counter = 0;
  int place_value, decimal; // Initialize the place value and the decimal number
  decimal = 0;
  place_value = 0;
  if (octal == 0) // Check if the octal number is 0
    printf("Converted %zu to base %zu : 0", octal, base); // Print the result

  while (octal != 0) { // Loop until the octal number is 0
    int last_digit = octal % 10; // Get the last digit
    decimal += last_digit * pow(8, place_value); // Add the digit multiplied by 8 raised to the power of the place value
    octal /= 10; // Divide the octal number by 10
    place_value++; // Increment the place value
  }
  decimal_any_base(decimal, base); // Convert the decimal number to the target base
}

// Print a welcome message
void printWelcome(void) {
  printf(">----- WELCOME TO THE NUMBER SYSTEMS CONVERTER (^_^) ------<\n");
  printf("-> decimal [t][10]\n-> hex [x][16]\n-> octal [o][8]\n-> Binary [n][2]\n");
  printf("Enter expression[ <number> <source base><target base>  e.g ff x8 -> converts hex to octal]\n~~~>");
}

// Main function
int main(void) {
  char expression[70]; // Initialize the expression string
  int decimal, base; // Initialize the decimal number and the base
  char source_base; // Initialize the source base

  printWelcome(); // Print the welcome message

  fgets(expression, 70, stdin); // Read the expression from the user
  char *hexchar; // Initialize a pointer to a hexadecimal character
  char hex[] = "abcdef"; // Initialize a string of hexadecimal characters
  hexchar = strpbrk(expression, hex); // Find the first hexadecimal character in the expression
  if (hexchar != 0) { // Check if a hexadecimal character was found
    sscanf(expression, "%x %c %d", &decimal, &source_base, &base); // Read the decimal number, source base, and target base from the expression
  } else {
    sscanf(expression, "%d %c %d", &decimal, &source_base, &base); // Read the decimal number, source base, and target base from the expression
  }

  switch (source_base) { // Switch on the source base
  case 'n': // Binary
    binary_any_base(decimal, base); // Convert the binary number to the target base
    break;
  case 'o': // Octal
    octal_any_base(decimal, base); // Convert the octal number to the target base
    break;
  case 't': // Decimal
    decimal_any_base(decimal, base); // Convert the decimal number to the target base
    break;
  case 'x': // Hexadecimal
    hex_any_base(decimal, base); // Convert the hexadecimal number to the target base
    break;
  default: // Invalid base
    printf("Invalid base!!"); // Print an error message
    break;
  }
}

