#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Given the file name, it returns how many
// processes exist in the file (lines -2)
int numOfProcesses(char *fileName)
{
  FILE *file = fopen(fileName, "r");
  if (!file)
  {
    return 0;
  }
  int result = 0;
  char buf[200];
  while (fgets(buf, sizeof(buf), file))
  {
    result++;
  }
  fclose(file);
  return result - 2;
}

// Returns the nth (specified by num)
// element in a csv string
char *getElement(char *lines, int elementIndex)
{
  char *current;
  for (current = strtok(lines, ",");
       current && *current;
       current = strtok(NULL, ",\n"))
  {
    if (!--elementIndex)
      return current;
  }
  return NULL;
}

// As the name implies :D generates a random number
// between the given ranges (inclusive)
int randomInclusive(int min, int max)
{
  return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

main()
{
  return 0;
}