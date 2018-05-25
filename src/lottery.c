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
  //THE LOGIC PART OF THE CODE >>
  FILE *log = NULL;
  log = fopen(outputFileName, "a");
  srand(time(NULL)); //Seed each program run random generation with a unique seed (from the time)
  int drawnTicket;
  start = clock(); //Initial clock just for logging
  for (timeLine = 0, processID = 0; remain != 0;)
  {
    drawnTicket = randomInclusive(0, totalTickets);
    for (int i = 0; i < totalNumOfProcesses; i++)
    {
      if (drawnTicket < lotteryTickets[i])
      {
        processID = i;
        break;
      }
    }

    if (remainingTime[processID] <= quantumLength && remainingTime[processID] > 0)
    {
      fprintf(log, "\n");
      fprintf(log, "Time %d: ", timeLine);
      fprintf(log, "P%d ", processID + 1);
      //CLOCK
      tmpClock = clock();
      while (((double)(clock() - tmpClock) / CLOCKS_PER_SEC) * 1000 < remainingTime[processID])
      {
      };
      //CLOCK
      timeLine += remainingTime[processID];
      remainingTime[processID] = 0;
      isFinished = 1;
    }
    else if (remainingTime[processID] > 0)
    {
      fprintf(log, "\n");
      fprintf(log, "Time %d: ", timeLine);
      fprintf(log, "P%d ", processID + 1);
      fprintf(log, "Entering quantum ");
      //CLOCK
      tmpClock = clock();
      while (((double)(clock() - tmpClock) / CLOCKS_PER_SEC) * 1000 < quantumLength)
      {
      };
      //CLOCK
      remainingTime[processID] -= quantumLength;
      timeLine += quantumLength;
    }
    if (remainingTime[processID] == 0 && isFinished == 1)
    {
      remain--;
      fprintf(log, " ||=> Done Turn Around: %d ", timeLine - arrivalTime[processID]);
      fprintf(log, " || Waiting Time: %d ", timeLine - arrivalTime[processID] - cpuBurst[processID]);

      waitTime += timeLine - arrivalTime[processID] - cpuBurst[processID];
      turnAround += timeLine - arrivalTime[processID];
      isFinished = 0;
    }
  }

  fprintf(log, "\n");
  fprintf(log, "\nAverage Turnaround Time = %f\n", turnAround * 1.0 / totalNumOfProcesses);
  fprintf(log, "Average Waiting Time= %f\n", waitTime * 1.0 / totalNumOfProcesses);

  fclose(log);

  printf("Success, output file has been written to %s\n", outputFileName);

  end = clock();
  double time_spent = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
  printf("Time elapsed during simulation = %f msec\n", time_spent);
  return 0;
}