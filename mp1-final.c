/*
7/31/2023
CPU - Scheduling - Project 1
ALEGRE, ALASTAIR PEARCE
HAY, JORDYN WILLIAM
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>


void fcfs( int y, int* arr);
void sjf(int y, int* arr);
void srtf(int y, int* arr);
void RR(int y, int z, int* arr);

int main(){
FILE* file;
char filename[30];
char* token;
char string1[10], string2[10], string3[10];
int inputArr[10][3];
int i, j, x, y, z, temp;
int* arr = (int*)malloc(y*3*sizeof(int));

printf("Input filename: ");
gets(filename);
strcat(filename, ".txt");
printf("filename is: %s\n", filename);
file = fopen(filename, "r");

x = 0; //scheduling
y = 3; //number of processes
z = 1; //time slice 
if (file == NULL){
printf("File could not be opened");
}

else{
    fscanf(file, "%d %d %d", &x, &y, &z);
    printf("%d %d %d\n", x, y, z); 
    
    for (i = 0; i < y * 3; i++){
            fscanf(file, "%d", &arr[i]);
    }
}
fclose(file);
switch (x)
{
case 0:
    fcfs(y, arr);
    break;
case 1:
    sjf(y, arr);
    break;
case 2:
    srtf(y, arr);
    break;
case 3:
    RR(y, z, arr);
    break;
default:
    break;
}
return 0;   
}

void fcfs(int y, int* arr){
    int i = 0, j = 0;
    int start = arr[1], end = arr[1];
    float temp = 0;

    int* endTime = (int*)malloc(y * sizeof(int));
    int* startTime = (int*)malloc(y * sizeof(int));
    FILE* file;
    file = fopen("fcfs.txt", "w");
    
    for (i = 0; i < y; i++){
        start = end;
        startTime[i] = start;
        end += arr[j * 3 + 2];
        endTime[i] = end;
        temp += start - arr[i * 3 + 1];
        j++;
        printf("P[%d] Start time: %d End time: %d | Waiting time: %d\n", 
        arr[i * 3], startTime[i], endTime[i], startTime[i] - arr[i * 3 + 1]);
        fprintf(file,"P[%d] Start time: %d End time: %d | Waiting time: %d\n", 
        arr[i * 3], startTime[i], endTime[i], startTime[i] - arr[i * 3 + 1]);
    }
    printf("Average waiting time: %.1f", temp / y);
    fprintf(file, "Average waiting time: %.1f", temp / y);
    fclose(file);

}

void RR(int size, int splice, int* arr){
  int i = 0, j = 0, k = 0;
  int time = 0, burst = 0;
  int startTime = arr[1]; // start at first process
  int endTime = arr[1];
  int* waitTime = (int*)malloc(size * sizeof(int));
  char string[100];
  char output[size][10000];
  bool check = false;
  float aveWait = 0;
  FILE *file;
  file = fopen("RR.txt", "w");

  for (i = 0; i < size; i++){
    sprintf(output[i], "P[%d] ", arr[i * 3]);
  }
  

  do{
        check = false;
    for (i = 0; i < size; i++){
        if (arr[i * 3 + 2] > 0){
            startTime = endTime;
            burst = arr[i * 3 + 2];
            arr[i * 3 + 2] -= splice;
            if (burst - splice <= 0){ // if quantum splice is less than burst time
                endTime += burst;
                    if (i > 0){
                        waitTime[i] = startTime - arr[i * 3 + 1];
                        aveWait += waitTime[i];
                    }
                    else{
                        waitTime[i] = 0;
                    }
                sprintf(string, "Start time: %d End time: %d | Waiting time: %d", startTime, endTime, waitTime[i]);
                strcat(output[i], string);
            }
            else{
                endTime += splice;
                sprintf(string, "Start time: %d End time: %d |", startTime, endTime);
                strcat(output[i], string);
                check = true;
            }
            
        }
        
    }
  }while(check == true);

  for(i = 0; i < size; i++){
    printf("%s\n", output[i]);
    fprintf(file, "%s\n", output[i]);
  }
  printf("Average waiting time: %.1f", aveWait / size);
  fprintf(file, "Average waiting time: %.1f", aveWait / size);
  fclose(file);

  
}


void srtf(int size, int* arr){
  int i = 0, j = 0;
  int time = arr[1], burst = 0;
  int startTime = arr[1];
  int endTime = arr[1];
  int* waitTime = (int*)malloc(size * sizeof(int));
  char string[100];
  char output[size][10000];
  bool check = false;
  int min = 99999999, minI = 0, prevMin = 0;
  int complete = 0;
  int counter = 0;
  int order[size], bt[size];
  float aveWait = 0;
  FILE *file;
  file = fopen("srtf.txt", "w");
 
  for (i = 0; i < size; i++){
    sprintf(output[i], "P[%d] ", arr[i * 3]);
    bt[i] = arr[i * 3 + 2];
  }
  while(complete < size){
    for (i = 0; i < size; i++){
        if(arr[i * 3 + 1] <= time && arr[i * 3 + 2] < min && arr[i * 3 + 2] > 0){
            min = arr[i * 3 + 2];
            minI = i;
            check = true;
        }
    }

        if(check == true){
            startTime = time;
            sprintf(string, "Start time: %d ", startTime);
            strcat(output[minI], string);
            if(counter > 0){
                endTime = time;
                sprintf(string, "End time: %d | ", endTime);
                strcat(output[prevMin], string);
            }
            prevMin = minI;
            counter++;
            check = false;
        }

        arr[minI * 3 + 2]--;
        min--;
        time++;

        if(min == 0){
            min = 99999999;
            complete++;
            order[j] = minI;
            waitTime[j] = time - arr[minI * 3 + 1] - bt[minI];
            aveWait += waitTime[j];
            j++;
        }
        
  }
  sprintf(string, "End time: %d | ", time);
  strcat(output[minI], string);
  for(i = 0; i < size; i++){
    sprintf(string, "Wait Time: %d", waitTime[i]);
    strcat(output[order[i]], string);
    printf("%s\n", output[order[i]]);
    fprintf(file, "%s\n", output[i]);
  }
  printf("Average waiting time: %.1f", aveWait / size);
  fprintf(file, "Average waiting time: %.1f", aveWait / size);
  fclose(file);
}

void sjf(int size, int* arr) {
  int i = 0, j = 0;
  int time = arr[1], burst = 0;
  int startTime = arr[1];
  int endTime = arr[1];
  int* waitTime = (int*)malloc(size * sizeof(int));
  char string[100];
  char output[size][1000];
  bool check = false;
  int min = 99999999, minI = 0, prevMin = 0;
  int complete = 0;
  int counter = 0;
  int order[size], bt[size];
  float aveWait = 0;
  FILE *file;
  file = fopen("sjf.txt", "w");



  for (i = 0; i < size; i++){
    sprintf(output[i], "P[%d]", arr[i * 3]);
    bt[i] = arr[i * 3 + 2];
  }

  while (complete < size){
    for (i = 0; i < size; i++){
        if(arr[i * 3 + 2] < min && arr[i * 3 + 2] > 0 && arr[i * 3 + 1] <= endTime){
            min = arr[i * 3 + 2];
            minI = i;
        }
    }

    sprintf(string, "Start time: %d ", endTime);
    strcat(output[minI], string);
    endTime += arr[minI * 3 + 2];
    arr[minI * 3 + 2] = 0;
    sprintf(string, "End time: %d | ", endTime);
    strcat(output[minI], string);
    order[j] = minI;
    waitTime[minI] = endTime - arr[minI * 3 + 1] - bt[minI];
    aveWait += waitTime[minI];
    j++;
    min = 999999999;
    complete++;

  }

  for(i = 0; i < size; i++){
    sprintf(string, "Wait Time: %d", waitTime[order[i]]);
    strcat(output[order[i]], string);
    printf("%s\n", output[order[i]]);
    fprintf(file, "%s\n", output[i]);
  }
  printf("Average waiting time: %.1f", aveWait / size);
  fprintf(file, "Average waiting time: %.1f", aveWait / size);
  fclose(file);
}