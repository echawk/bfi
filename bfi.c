/*

A totally unoriginal brainfuck interpreter written in C.

*/

#include <stdio.h>
#include <stdlib.h>

void print_tape();
char *read_file(char *file_path);

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
char *infile;

int main(int argc, char*argv[]) {
  if (argc == 2) {
    infile = argv[1];
  } else {
    printf("Expecting a file!\n");
    exit(1);
  }

  input_arr = read_file(infile);
  input_pos = 0;
  while (input_arr[input_pos] != 0) {
    next_char:
    ch = (char)input_arr[input_pos];
    switch (ch) {
    case '+':
      tape[pos]++;
      break;
    case '-':
      tape[pos]--;
      break;
    case '>':
      pos++;
      break;
    case '<':
      pos--;
      break;
    case '.':
      printf("%c", tape[pos]);
      break;
    case ',':
      tape[pos] = getchar();
      break;
    case '[':
      loop_depth++;
      loop_depth_indices[loop_depth] = input_pos;
      break;
    case ']':
      if (tape[pos] != 0) {
        input_pos = loop_depth_indices[loop_depth] + 1;
        goto next_char;
      } else {
        loop_depth--;
      }
      break;
    }
    input_pos++;
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
void print_tape() {
  int i;
  for (i = 0; i < TAPE_SIZE; i++) {
    printf("tape[%d]: %d\n", i, tape[i]);
  }
}
