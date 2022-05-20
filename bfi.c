/*

A totally unoriginal brainfuck interpreter written in C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_tape();
void interpret(char *input_arr);
void repl();
void reset_tape();
char *read_file(char *file_path);

#define TAPE_SIZE 10
int tape[TAPE_SIZE];
int pos = 0;

#define REPL_SIZE 1000
char repl_buff[REPL_SIZE];

/*
  This array controls how deep loops can be in the program -
  the depth of the loop (1, 2, etc), is associated with an index
  in this array. The index that is saved in this array is the index
  of the matching '[' for a respective ']'
 */
int loop_depth_indices[500];
int loop_depth = 0;

int main(int argc, char*argv[]) {
  char *input_arr;
  if (argc == 2) {
    input_arr = read_file(argv[1]);
    reset_tape();
    interpret(input_arr);
    print_tape();
    return 0;
  } else {
    repl();
  }
  return 0;
}

void prompt_read() {
  printf("# ");
  fflush(stdout);
  memset(repl_buff, 0, sizeof(repl_buff));
  fgets(repl_buff, sizeof(repl_buff), stdin);
}

void repl(){
  printf("[REPL] Type q to quit!\n");
  while(1) {
    prompt_read();
    if (repl_buff[0] == 'q') {
      return;
    } else  {
      repl_buff[strlen(repl_buff)-1] = '\0';
      /* reset_tape(); */
      interpret(repl_buff);
      print_tape();
    }
  }
}

void interpret(char *input_arr) {
  char ch;
  int input_pos = 0;
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
}

void reset_tape() { memset(tape, 0, sizeof(tape)); pos = 0; }

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
