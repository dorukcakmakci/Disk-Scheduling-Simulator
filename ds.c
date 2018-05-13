#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double find_mean(int *arr, int size){
    double result = 0;
    for(int i = 0; i < size; i++){
        result += arr[i];
    }
    result /= (size);
    return result;
}

double find_stddev(int * arr, int size){

    double mean = find_mean(arr,size);
    double result = 0;
    for(int j = 0; j < size; j++){
        result += pow(arr[j] - mean,2);
    }
    result /= (size - 1);
    result = sqrt(result);
    return result;
}


void FCFS(int N, char* filename){

    FILE* fptr;
    int time[100];
    int *cylinder;
    cylinder = malloc(100 * sizeof(int));

    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("ERROR: Can not open the file...\n");
        return;
    }

    int i = 0;
    int linecount = 0;

    while(!feof(fptr)){
        if( i == 0){
            fscanf(fptr, "%d", &time[linecount]);
            i++;
        }
        else if (i == 1){
            fscanf(fptr, "%d", &cylinder[linecount]);
            i--;
            linecount++;
        }
    }


    if(linecount != 100){
        time[linecount] = -1;
        cylinder[linecount] = -1;
    }
    for (int j = 0; j <= linecount; j++){
        if(j != linecount)
            printf("Request %d => Time: %d   Cylinder => %d\n", (j+1), time[j], cylinder[j]);
        else
            printf("Request Ended => Time: %d   Cylinder => %d\n", time[j], cylinder[j]);
    }

    int elapsedTime = 0;
    int oldElapsedTime = 0;
    int numberOfRequestsFinished = 0;
   
    int *requestGrantTime;
    requestGrantTime = malloc(100*sizeof(int));
    
    int currentIndex = 0;
    int currentCylinder = 1;

    while(numberOfRequestsFinished < linecount){
        //printf("Elapsed Time: %d\n", elapsedTime);

        if(elapsedTime < time[currentIndex]){
            elapsedTime++;
            printf("1\n");
            continue;
        }
        if(currentCylinder == cylinder[currentIndex]){
            requestGrantTime[currentIndex] += elapsedTime - time[currentIndex];//elapsedTime - oldElapsedTime + time[currentIndex];
            oldElapsedTime = elapsedTime;
            printf("%d-------\n", numberOfRequestsFinished);
            fflush(stdout);
            numberOfRequestsFinished++;
            currentIndex++;
            printf("2\n");
        }
        else if(currentCylinder < cylinder[currentIndex]){
            while(currentCylinder < cylinder[currentIndex]){
                requestGrantTime[currentIndex]--;
                currentCylinder++;
                elapsedTime++;
            }
            printf("3\n");
        }
        else if(currentCylinder > cylinder[currentIndex]){
            while(currentCylinder > cylinder[currentIndex]){
                requestGrantTime[currentIndex]--;
                currentCylinder--;
                elapsedTime++;
            }
            printf("4\n");
        }
    }
    printf("linecount===%d\n", linecount);

    printf("FCFS\n----\nElapsed time: %d\nAverage wait time: %f\nStandard deviation of wait times: %f\n", elapsedTime, find_mean(requestGrantTime, linecount), find_stddev(requestGrantTime, linecount));
    for(int i  = 0; i< linecount; i++){
        printf("Request %d => Time: %d   Cylinder => %d Wait Time: %d\n", (i+1), time[i], cylinder[i], requestGrantTime[i]);
    }
    fflush(stdout);

    fclose(fptr);

    free(requestGrantTime);
    

     
}

int getMinimumNotTraversedIndex(int * request, int * granted, int headLocation, int size, int *time, int currentTime){
    int result = -1;
    int min = 999999;
    for(int i = 0; i < size; i++){
        if(granted[i] == 1){
            continue;
        }
        else{
            if(abs(request[i] - headLocation) < min && time[i] <= currentTime){
                result = i;
                min = abs(request[i] - headLocation);
            }
        }
    }
    return result;
}

void SSTF(int N, char* filename){

    FILE* fptr;
    int time[100];
    int *cylinder;
    cylinder = malloc(100*sizeof(int));

    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("ERROR: Can not open the file...\n");
        return;
    }

    int i = 0;
    int linecount = 0;
    
    while(!feof(fptr)){
        if( i == 0){
            fscanf(fptr, "%d", &time[linecount]);
            i++;
        }
        else if (i == 1){
            fscanf(fptr, "%d", &cylinder[linecount]);
            i--;
            linecount++;
        }
    }


    if(linecount != 100){
        time[linecount] = -1;
        
    }
        cylinder[linecount] = -1;
    
    for (int j = 0; j <= linecount; j++){
        if(j != linecount)
            printf("Request %d => Time: %d   Cylinder => %d\n", (j+1), time[j], cylinder[j]);
        else
            printf("Request Ended => Time: %d   Cylinder => %d\n", time[j], cylinder[j]);
    }

    int elapsedTime = 0;
    int oldElapsedTime = 0;
    int numberOfRequestsFinished = 0;
   
    int *requestGrantTime;
    requestGrantTime = malloc(100*sizeof(int));

    int *grantRequest;
    grantRequest =  malloc(100*sizeof(int));

    for(int i = 0; i < 100; i++){
        if(i >= linecount)
            grantRequest[i] = 1;
        else if(i == 0){
            printf("yarrakBB\n");
            grantRequest[i] = 1;
            printf("yarrakAA\n");
        }
            
        else
            grantRequest[i] = 0;
    }
    
    int currentCylinder = 1;
    int currentIndex = 0;
    

    while(numberOfRequestsFinished < linecount){

        if(elapsedTime < time[currentIndex]){
            elapsedTime++;
            printf("1\n");
            continue;
        }
        if(currentCylinder == cylinder[currentIndex]){
            
            oldElapsedTime = elapsedTime;
            printf("%d-------\n", numberOfRequestsFinished);
            fflush(stdout);
            numberOfRequestsFinished++;
            currentIndex = getMinimumNotTraversedIndex(cylinder,  grantRequest, currentCylinder, linecount, time, elapsedTime);
            grantRequest[currentIndex] = 1;
            requestGrantTime[currentIndex] = elapsedTime - time[currentIndex];
            printf("2\n");
        }
        else if(currentCylinder < cylinder[currentIndex]){
            while(currentCylinder < cylinder[currentIndex]){
                currentCylinder++;
                elapsedTime++;
            }
            printf("3\n");
        }
        else if(currentCylinder > cylinder[currentIndex]){
            while(currentCylinder > cylinder[currentIndex]){
                currentCylinder--;
                elapsedTime++;
            }
            printf("4\n");
        }
    }

    printf("SSTF\n----\nElapsed time: %d\nAverage wait time: %f\nStandard deviation of wait times: %f\n", elapsedTime, find_mean(requestGrantTime, linecount), find_stddev(requestGrantTime, linecount));
    for(int i  = 0; i< linecount; i++){
        printf("Request %d => Time: %d   Cylinder => %d Wait Time: %d\n", (i+1), time[i], cylinder[i], requestGrantTime[i]);
    }
    fflush(stdout);

    fclose(fptr);

    //free(requestGrantTime); 
    //free(cylinder);
    //free(grantRequest); 
}

/*int *getMaximumAndMinimumNotTraversedIndex(int * request, int * granted, int size, int *time, int currentTime){
    int *result = malloc(2*sizeof(int));
    int max = -1;
    int min = 999999;
    for(int i = 0; i < size; i++){
        if(granted[i] == 1){
            continue;
        }
        else{
            if(request[i] > max && time[i] < currentTime){
                result[1] = i;
                max = request[i];
            }
            if(request[i] <  min && time[i] < currentTime){
                result[0] = i;
                min = request[i];
            }
        }
    }
    return result;
}*/
// returns -1 if no such index
int getNotGrantedIndexToTheRight(int * request, int * granted, int headLocation, int size, int *time, int currentTime){
    int result = -1; 
    int min = 999999;
    for(int i = 0; i < size; i++){
        if(granted[i] == 1){
            continue;
        }
        else{
            if(request[i] > headLocation && request[i] <  min && time[i] <= currentTime){
                result = i;
                min = request[i];
            }
        }
    }
    return result;
}
// returns -1 if no such index
int getNotGrantedIndexToTheLeft(int * request, int * granted, int headLocation,  int size, int *time, int currentTime){
    int result = -1; 
    int max = -1;
    for(int i = 0; i < size; i++){
        if(granted[i] == 1){
            continue;
        }
        else{
            if(request[i] < headLocation && request[i] >  max && time[i] <= currentTime){
                result = i;
                max = request[i];
            }
        }
    }
    return result;
}

void LOOK(int N, char* filename){
    
    FILE* fptr;
    int time[100];
    int cylinder[100];

    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("ERROR: Can not open the file...\n");
        return;
    }

    int i = 0;
    int linecount = 0;
    
    while(!feof(fptr)){
        if( i == 0){
            fscanf(fptr, "%d", &time[linecount]);
            i++;
        }
        else if (i == 1){
            fscanf(fptr, "%d", &cylinder[linecount]);
            i--;
            linecount++;
        }
    }


    if(linecount != 100){
        time[linecount] = -1;
        cylinder[linecount] = -1;
    }
    for (int j = 0; j <= linecount; j++){
        if(j != linecount)
            printf("Request %d => Time: %d   Cylinder => %d\n", (j+1), time[j], cylinder[j]);
        else
            printf("Request Ended => Time: %d   Cylinder => %d\n", time[j], cylinder[j]);
    }

    int elapsedTime = 0;
    int oldElapsedTime = 0;
    int numberOfRequestsFinished = 0;
   
    int *requestGrantTime;
    requestGrantTime = malloc(100*sizeof(int));

    for(int i = 0; i < 100; i++){
        requestGrantTime[i] = 0;
    }

    int *grantRequest;
    grantRequest =  malloc(100*sizeof(int));

    for(int i = 0; i < 100; i++){
        if(i >= linecount)
            grantRequest[i] = 1;
        else 
            grantRequest[i] = 0;
    }

    int currentIndex = 0;
    int currentCylinder = 1;

    int direction = 1; // 1--> right /// 0--> left
    int tempR = -2;
    int tempL = -2;

    tempR = getNotGrantedIndexToTheRight(cylinder,  grantRequest, currentCylinder, linecount, time, elapsedTime);
    tempL = getNotGrantedIndexToTheLeft(cylinder,  grantRequest, currentCylinder, linecount, time, elapsedTime);

    while(numberOfRequestsFinished < linecount){

        

        if(elapsedTime < time[currentIndex]){
            elapsedTime++;
            printf("1\n");
            continue;
        }
    
        printf("TempR: %d  --  CurrentCylinder: %d  -- ", tempR, currentCylinder);
        printf("TempL: %d --currentIndex: %d -- direction: %d \n", tempL, currentIndex, direction);
        fflush(stdout);

        if (direction == 1 && tempR != -1 ){
            currentIndex = tempR;
            while(currentCylinder < cylinder[currentIndex]){
                requestGrantTime[currentIndex]--;
                currentCylinder++;
                elapsedTime++;
            }
            if(currentCylinder == cylinder[currentIndex]){
                    requestGrantTime[currentIndex] += elapsedTime - time[currentIndex];
                    grantRequest[currentIndex] = 1;
                    oldElapsedTime = elapsedTime;
                    printf("%d-------\n", numberOfRequestsFinished);
                    fflush(stdout);
                    numberOfRequestsFinished++;
                    printf("2\n");
            }
            printf("3\n");
            tempR = getNotGrantedIndexToTheRight(cylinder,  grantRequest, currentCylinder, linecount, time, elapsedTime);
            tempL = getNotGrantedIndexToTheLeft(cylinder,  grantRequest, currentCylinder, linecount, time, elapsedTime);
            if(tempR == -1)
                direction--;
        }
         if (direction == 0 && tempL != -1 ){
            
            currentIndex = tempL;
            while(currentCylinder > cylinder[currentIndex]){
                requestGrantTime[currentIndex]--;
                currentCylinder--;
                elapsedTime++;
            }
            if(currentCylinder == cylinder[currentIndex]){
                    requestGrantTime[currentIndex] += elapsedTime - time[currentIndex];
                    oldElapsedTime = elapsedTime;
                    grantRequest[currentIndex] = 1;
                    printf("%d-------\n", numberOfRequestsFinished);
                    fflush(stdout);
                    numberOfRequestsFinished++;
                    printf("2\n");
            }
            printf("4\n");
            tempR = getNotGrantedIndexToTheRight(cylinder,  grantRequest, currentCylinder, linecount, time, elapsedTime);
            tempL = getNotGrantedIndexToTheLeft(cylinder,  grantRequest, currentCylinder, linecount, time, elapsedTime);
            if(tempL == -1){
                direction++;
            }
        }
        if(tempR == -1 && tempL == -1){
            break;
        }

        
    }

    printf("LOOK\n----\nElapsed time: %d\nAverage wait time: %f\nStandard deviation of wait times: %f\n", elapsedTime, find_mean(requestGrantTime, linecount), find_stddev(requestGrantTime, linecount));
    for(int i  = 0; i< linecount; i++){
        printf("Request %d => Time: %d   Cylinder => %d Wait Time: %d\n", (i+1), time[i], cylinder[i], requestGrantTime[i]);
    }
    fflush(stdout);

    fclose(fptr);

    /*free(requestGrantTime); 
    free(cylinder);
    free(grantRequest);*/

     
}

// returns -1 if no such index
int getNotGrantedMinimalIndexToTheLeft(int * request, int * granted, int headLocation,  int size, int *time, int currentTime){
    int result = -1; 
    int min = 999999;
    for(int i = 0; i < size; i++){
        if(granted[i] == 1){
            continue;
        }
        else{
            if(request[i] < headLocation && request[i] <  min && time[i] <= currentTime){
                result = i;
                min = request[i];
            }
        }
    }
    return result;
}

void CLOOK(int N, char* filename){
 
    FILE* fptr;
    int time[100];
    int cylinder[100];

    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("ERROR: Can not open the file...\n");
        return;
    }

    int i = 0;
    int linecount = 0;
    
    while(!feof(fptr)){
        if( i == 0){
            fscanf(fptr, "%d", &time[linecount]);
            i++;
        }
        else if (i == 1){
            fscanf(fptr, "%d", &cylinder[linecount]);
            i--;
            linecount++;
        }
    }


    if(linecount != 100){
        time[linecount] = -1;
        cylinder[linecount] = -1;
    }
    for (int j = 0; j <= linecount; j++){
        if(j != linecount)
            printf("Request %d => Time: %d   Cylinder => %d\n", (j+1), time[j], cylinder[j]);
        else
            printf("Request Ended => Time: %d   Cylinder => %d\n", time[j], cylinder[j]);
    }

    int elapsedTime = 0;
    int oldElapsedTime = 0;
    int numberOfRequestsFinished = 0;
   
    int *requestGrantTime;
    requestGrantTime = malloc(100*sizeof(int));

    for(int i = 0; i < 100; i++){
        requestGrantTime[i] = 0;
    }

    int *grantRequest;
    grantRequest =  malloc(100*sizeof(int));

    for(int i = 0; i < 100; i++){
        if(i >= linecount)
            grantRequest[i] = 1;
        else 
            grantRequest[i] = 0;
    }

    int currentIndex = 0;
    int currentCylinder = 1;

    int direction = 1; // 1--> right /// 0--> left
    int tempR = -2;
    int tempL = -2;

    tempR = getNotGrantedIndexToTheRight(cylinder,  grantRequest, currentCylinder, linecount, time, elapsedTime);

    while(numberOfRequestsFinished < linecount){

        

        if(elapsedTime < time[currentIndex]){
            elapsedTime++;
            printf("1\n");
            continue;
        }
    
        printf("TempR: %d  --  CurrentCylinder: %d  -- ", tempR, currentCylinder);
        fflush(stdout);

        if (tempR != -1 ){
            currentIndex = tempR;
            while(currentCylinder < cylinder[currentIndex]){
                requestGrantTime[currentIndex]--;
                currentCylinder++;
                elapsedTime++;
            }
            if(currentCylinder == cylinder[currentIndex]){
                requestGrantTime[currentIndex] += elapsedTime - time[currentIndex];
                grantRequest[currentIndex] = 1;
                oldElapsedTime = elapsedTime;
                printf("%d-------\n", numberOfRequestsFinished);
                fflush(stdout);
                numberOfRequestsFinished++;
                printf("2\n");
            }
            printf("3\n");
            tempR = getNotGrantedIndexToTheRight(cylinder,  grantRequest, currentCylinder, linecount, time, elapsedTime);
        }
        else if(tempR == -1){
            
            tempR = getNotGrantedMinimalIndexToTheLeft(cylinder,  grantRequest, currentCylinder, linecount, time, elapsedTime);
            if(tempR  == -1){
                    break;
            }
            while(currentCylinder > cylinder[tempR]){
                currentCylinder--;
                requestGrantTime[tempR]--;
                /*for(int i = 0; i < linecount; i++){
                    if(grantRequest[i] == 0 && time[i] <= elapsedTime){
                        requestGrantTime[i]--;
                    }
                }*/
                elapsedTime++;  
            }
            

            printf("Left minimal index: %d -- current cykinder: %d -- num req: %d\n", tempR, currentCylinder, numberOfRequestsFinished);
        }
         
        
    }

    printf("CLOOK\n----\nElapsed time: %d\nAverage wait time: %f\nStandard deviation of wait times: %f\n", elapsedTime, find_mean(requestGrantTime, linecount), find_stddev(requestGrantTime, linecount));
    for(int i  = 0; i< linecount; i++){
        printf("Request %d => Time: %d   Cylinder => %d Wait Time: %d\n", (i+1), time[i], cylinder[i], requestGrantTime[i]);
    }
    fflush(stdout);

    fclose(fptr);

    /*free(requestGrantTime); 
    free(cylinder);
    free(grantRequest);*/

    fclose(fptr);

     
}

int main(int argc, char ** argv){

    //get the arguments
    if(argc == 1 || argc == 2 || argc > 3 ){
        printf("Arguments are insufficient.\n");
        return -1;
    }
    
    int N = argv[1];
    char * filename = argv[2];
   
    //Use FCFS to schedule
    //FCFS(N, filename);
    
    //Use SSTF to schedule
    //SSTF(N, filename);

    //Use LOOK to schedule
    //LOOK(N, filename);

    //Use CLOOK to schedule
    CLOOK(N, filename);
    return 0;
}
