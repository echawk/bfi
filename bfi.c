/*

A totally unoriginal brainfuck interpreter written in C.

*/

#include <stdio.h>
#include <stdlib.h>

void print_tape();
char *read_file(char *file_path);
void print_char_arr(char *arr, int len);
void print_debug();

#define TAPE_SIZE 10
int tape[TAPE_SIZE];
int pos = 0;

/*
  This array controls how deep loops can be in the program -
  the depth of the loop (1, 2, etc), is associated with an index
  in this array. The index that is saved in this array is the index
  of the matching '[' for a respective ']'
 */
int loop_depth_indices[500];
int loop_depth = 0;

char ch;
char *input_arr;
int input_pos;

int main() {
  char *infile = "test.b";
  input_arr = read_file(infile);
  input_pos = 0;
  while (input_arr[input_pos] != 0) {
    ch = (char)input_arr[input_pos];
    switch (ch) {
    case '+':
      //fprintf(stderr, "%c", ch);
      tape[pos]++;
      input_pos++;
      break;
    case '-':
      //fprintf(stderr, "%c", ch);
      tape[pos]--;
      input_pos++;
      break;
    case '>':
      //fprintf(stderr, "%c", ch);
      pos++;
      input_pos++;
      break;
    case '<':
      //fprintf(stderr, "%c", ch);
      pos--;
      input_pos++;
      break;
    case '.':
      //fprintf(stderr, "%c", ch);
      printf("%c", tape[pos]);
      input_pos++;
      break;
    case ',':
      //fprintf(stderr, "%c", ch);
      tape[pos] = getchar();
      input_pos++;
      break;
    case '[':
      //fprintf(stderr, "%c", ch);
      loop_depth++;
      loop_depth_indices[loop_depth] = input_pos;
      /*
         If the byte at the data pointer is zero, then instead of moving
         the instruction pointer forward to the next cell, jump to the cell
         following the matching ']'
      */
      if (tape[pos] == 0) {
        while (input_arr[input_pos] != ']') {
          input_pos++;
        }
        input_pos++;
        break;
      }
      input_pos++;
      break;
    case ']':
      /*
        If the byte at the data pointer is nonzero, then instead of moving
        the instruction pointer forward to the next cell, jump to the cell
        after the matching '['
       */
      //fprintf(stderr, "%c", ch);
      if (tape[pos] != 0) {
        input_pos = loop_depth_indices[loop_depth] + 1;
        break;
      } else {
        loop_depth--;
        input_pos++;
      }
      break;
    default:
        input_pos++;
      break;
    }
  }
  printf("\n");

  print_tape();

  return 0;
}

char *read_file(char *file_path) {
  char *buffer;
  long file_length;
  FILE *input = fopen(file_path, "rb");
  fseek(input, 0, SEEK_END);
  file_length = ftell(input);
  rewind(input);

  buffer = (char *)malloc(file_length * sizeof(char));
  fread(buffer, file_length, 1, input);
  fclose(input);

  return buffer;
}

void print_debug() {
  printf("----------\n");
  printf("loop depth: %d\n", loop_depth);
  printf("loop_depth_indices[%d]: %d\n", loop_depth, loop_depth_indices[loop_depth]);
  printf("current char: %c\n", ch);
  printf("input_arr[%d]: %c\n", input_pos, input_arr[input_pos]);
  printf("input_pos: %d\n", input_pos);
  printf("tape position: %d\n", pos);
  print_tape();
  printf("----------\n");
}

void print_tape() {
  int i = 0;
  while (i < TAPE_SIZE) {
    printf("tape[%d]: %d\n", i, tape[i]);
    i++;
  }
}

void print_char_arr(char *arr, int len) {
  int i;
  for (i = 0; i < len; i++) {
    printf("arr[%d] = %c\n", i, arr[i]);
  }
}
