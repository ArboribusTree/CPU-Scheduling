#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

void fcfs(int x, int y, int z, int* arr);
void srtf(int x, int y, int z, int* arr);

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

fcfs(x, y, z, arr);
return 0;   
}

void fcfs(int x, int y, int z, int* arr){
    int i = 0, j = 0;
    int start = 0, end = 0;
    float temp = 0;

    int* endTime = (int*)malloc(y * sizeof(int));
    int* startTime = (int*)malloc(y * sizeof(int));
    FILE* file;
    file = fopen("output0.txt", "w");
    
    for (i = 0; i < y; i++){
        start = end;
        startTime[i] = start;
        end += arr[j * 3 + 2];
        endTime[i] = end;
        temp += start;
        j++;
        printf("P[%d] Start time: %d End time: %d | Waiting time: %d\n", arr[i * 3], startTime[i], endTime[i], startTime[i]);
        fprintf(file,"P[%d] Start time: %d End time: %d | Waiting time: %d\n", arr[i * 3], startTime[i], endTime[i], startTime[i]);
    }
    printf("Average waiting time: %.1f", temp / y);
    fprintf(file, "Average waiting time: %.1f", temp / y);
    fclose(file);


}


void srtf(int x, int y, int z, int* arr){
    int i, j, time;
    int start, end, complete;
    int* endTime = (int*)malloc(y * sizeof(int));
    int* startTime = (int*)malloc(y * sizeof(int));
    int* pid = (int*)malloc(y * sizeof(int));
    int* srtfArr = arr;

    int min = 9999999, minI = 0;
    bool complete, check;
    
    complete = 0; //number of complete processes
    j = 0;
    time = 0;
    check = false;

    while (complete != y){
        for (i = 0; i < y; i++){
            if (arr[i * 3 + 1] <= time && arr[i * 3 + 2] < min){
                min = arr[i * 3 + 2];
                j = i;
                check = true;
            }

            if(check){
                if (j > 0)
                    endTime[j] = time;

                startTime[j] = time;
            }

            arr[j * 3 + 1]--;
            min = arr[j * 3 + 1];
            time++;

            if (min == 0)
                min = 9999999;
            
            
            
        }
    }
    
    

}
