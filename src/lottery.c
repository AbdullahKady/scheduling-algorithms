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

int main()
{
  time_t start, end, tmpClock;
  char inputFileName[256];
  char outputFileName[256];
  printf("Enter input file name: ");
  scanf("%s", inputFileName);
  printf("Enter Output file name: ");
  scanf("%s", outputFileName);
  int processID = 0, totalNumOfProcesses, timeLine, remain, isFinished = 0, quantumLength;
  totalNumOfProcesses = numOfProcesses(inputFileName);
  int waitTime = 0;
  int turnAround = 0;
  int arrivalTime[totalNumOfProcesses], cpuBurst[totalNumOfProcesses], remainingTime[totalNumOfProcesses], lotteryTickets[totalNumOfProcesses];
  FILE *file = fopen(inputFileName, "r");
  if (!file)
  {
    printf("FILE DOESN'T EXIST!!\n");
    return 0;
  }
  char quantum_string[256];
  fgets(quantum_string, sizeof(quantum_string), file);
  quantumLength = atoi(quantum_string); //Converting the quantum into an int
  remain = totalNumOfProcesses;

  char total_tickets_string[256];
  fgets(total_tickets_string, sizeof(total_tickets_string), file);
  int totalTickets = atoi(total_tickets_string);

  char tmpProcess[256];
  while (fgets(tmpProcess, sizeof(tmpProcess), file))
  {
    //Converting each element into an int, and storing them in the appropriate corresponding array cells.
    char *dup = strdup(tmpProcess);
    int currentArrivalTime = atoi(getElement(dup, 2));
    dup = strdup(tmpProcess);
    int currentCpuBurst = atoi(getElement(dup, 3));
    dup = strdup(tmpProcess);
    int currentTickets = atoi(getElement(dup, 4));

    arrivalTime[processID] = currentArrivalTime;
    cpuBurst[processID] = currentCpuBurst;
    remainingTime[processID] = cpuBurst[processID];
    if (processID == 0)
    {
      lotteryTickets[processID] = currentTickets;
    }
    else
    {
      lotteryTickets[processID] = lotteryTickets[processID - 1] + currentTickets;
    }
    processID++;
  }
  fclose(file);
  //LOADING ALL VALUES DONE
}