#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

bool verify_pass(char *pass);
const char* password_generator();

int main() {
  char pass[30];
  printf("Requirements: ABCabc123#$& > 10 \n");
  printf("Please give a password: ");
  scanf("%s", pass);

  bool res = verify_pass(pass);
  if (res) {
    printf("%s is a strong password.\n", pass);
  }
  else {
    printf("%s is a weak password. Try using that one instead. %s \n", pass, password_generator());
  }
  return 0;
}

const char* password_generator() {
  int len = 15;

  char *password = malloc(len + 1);

  char *digits = "0123456789";
  int digits_length = strlen(digits);

  char *lowers = "abcdefghijklmnopqrstuwxyz";
  int lowers_length = strlen(lowers);

  char *uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int uppers_length = strlen(uppers);

  char *symbols = "!@#$%^&*()";
  int symbols_length = strlen(symbols);

  srand(time(NULL) * getpid());

  for (int i = 0; i < len; i++) {
    int ctype = rand() % 4;

    if (ctype == 0)
      password[i] = digits[rand() % digits_length];
    else if (ctype == 1)
      password[i] = lowers[rand() % lowers_length];
    else if (ctype == 2)
      password[i] = uppers[rand() % uppers_length];
    else
      password[i] = symbols[rand() % symbols_length];
  }
  password[len] = '\0';
  return password;
  }

bool verify_pass(char *pass) {
  int length = strlen(pass);
  if (length < 10) return false;

  bool has_upper = false;
  bool has_lower = false;
  bool has_digit = false;
  bool has_symbol = false;

  for (int i = 0; i < length; i++) {
    if (isupper(pass[i])) has_upper = true;
    if (islower(pass[i])) has_lower = true;
    if (isdigit(pass[i])) has_digit = true;
    if (ispunct(pass[i])) has_symbol = true;
  }

  if (!has_upper || !has_lower || !has_digit || !has_symbol) return false;

  return true;

}