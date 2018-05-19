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

main()
{
  return 0;
}