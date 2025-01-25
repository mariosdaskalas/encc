#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool verify_pass(char *pass);

int main() {
  char pass[20];
  printf("Requirements: ABCabc123#$& > 10 \n");
  printf("Please give a password: ");
  scanf("%s", pass);

  bool res = verify_pass(pass);
  if (res) {
    printf("%s is a strong password.\n", pass);
  }
  else {
    printf("%s is a weak password. Try using that one instead. \n", pass);
  }
  return 0;
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