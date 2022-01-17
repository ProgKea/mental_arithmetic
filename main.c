#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int min, max, rand_a, rand_b, answer, streak=0;
char operator;

void clear_terminal() {
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 11);
}

int generate_random_number(int min, int max) {
  return (rand() % (max-min+1))+min;
}

void print_streak() {
  printf("Streak: %d\n", streak);
}

void print_equation(int a, int b, char operator) {
  printf("%d %c %d = ", a, operator, b);
}

bool check_answer(int a, int b, char operator, int answer) {
  int result=(operator=='+')?(a+b):((operator=='-')?(a-b):((operator=='*')?(a*b):0));
  if (answer == result) return true;
  else return false;
}

void start_game(int min, int max, char operator) {
  clear_terminal();
  rand_a = generate_random_number(min, max);
  rand_b = generate_random_number(min, max);
  print_streak();
  print_equation(rand_a, rand_b, operator);
  scanf("%d", &answer);
  if (check_answer(rand_a, rand_b, operator, answer)) {
    streak++;
    start_game(min, max, operator);
  } else {
    streak = 0;
    start_game(min, max, operator);
    printf("testing");
  }
}

int main(void) {
  // set random seed
  srand(time(NULL));

  clear_terminal();
  printf("Enter minimum and maximum\n");
  scanf("%d %d", &min, &max);

  if (min > max) {
    printf("Minimum must be lower than Maximum!\n");
    exit(1);
  }

  printf("Enter operator ('*', '+' or '-')\n");
  scanf(" %c", &operator);
  clear_terminal();

  start_game(min, max, operator);
  return 0;
}
