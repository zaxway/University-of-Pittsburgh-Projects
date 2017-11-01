#include <stdio.h>

int checkCharacter (char c) {
  if (c >= 32 && c <= 126) {
    return 1; // true
  }
  return 0; // false
}


int main(int argc, char* argv[]) {
  FILE* f;
  f = fopen(argv[1], "r"); // want to read the bytes of this file
  // A charater is basically a byte soooo....
  // 4 character = four bytes.
  //char characters[4];
  // want to check to see if the current length is equal to 4.
  // sets initial variables.
  int currlength = 0;
  char character;
  char str[100];
  // check if there is stuff in files.
  if (f == NULL) {
    // if no stuff print and return.
    printf("File is NULL.");
    return 0;
  }
  // while we are not at the end of the file
  while(feof(f) == 0) {
    // read the file
    fread(&character, sizeof(character), 1, f);
    // check if character is between 32 and 126
    if (checkCharacter(character) == 1) {
      str[currlength] = character; //add the character to the array of chars
      currlength++; // increase current length by 1 for proper indexing.
    }

    if (currlength >= 4) { // since strings can be AT LEAST which means >= 4 bytes long
      // prints the string.
      printf("%s\n", str);

      // reset values
      str[0] = NULL; // because current length resets to 0 we must reset our array to 0 as well.
      currlength = 0;

    }
  }
  // close file and return
  fclose(f);
  return 0;
}
