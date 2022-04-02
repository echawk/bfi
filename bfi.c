/*

A totally unoriginal brainfuck interpreter written in C.

*/

#include <stdio.h>
#include <stdlib.h>

#define TAPE_SIZE 10
int tape[TAPE_SIZE];
int pos = 0;

void print_tape();

int main() {
  char *infile = "test.b";
  FILE *input = fopen(infile, "r");
  char ch;
  while ((ch = fgetc(input)) != EOF) {
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
    }
    fprintf(stderr, "%c", ch);
  }
  fclose(input);

  printf("\n");

  print_tape();

  return 0;
}

void print_tape() {
  int i = 0;
  while (i < TAPE_SIZE) {
    printf("tape[%d]: %d\n",i, tape[i]);
    i++;
  }

}
