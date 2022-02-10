#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

int array[250];
typedef struct parameters{
    int left;
    int right;
}args;


void merge(int low, int mid, int high)
{
    int i, j, k;
    int size1 = mid - low + 1;
    int size2 =  high - mid;

    int left[size1], right[size2];
    for (i = 0; i < size1; i++){
        left[i] = array[low + i];
       
        }
        
    for (j = 0; j < size2; j++){
        right[j] = array[mid + 1 + j];
        }
    i = 0,j = 0, k = low;
    while (i < size1 && j < size2)
    {
        if (left[i] <= right[j])
        {
            array[k] = left[i];
            i++;
        }
        else
        {
            array[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < size1)
    {
        array[k] = left[i];
        i++;
        k++;
    }

    while (j < size2)
    {
        array[k] = right[j];
        j++;
        k++;
    }
}





void* merge_Sort(void* para)
{
    args component = *((args*)para);
    int low = component.left;
    int high = component.right;
    if (low < high)
    {
          
        pthread_t thread1;
        pthread_t thread2;
        
       int mid=(low+high)/2;
        
        args component1 ;
        component1.left=low;
        component1.right=mid;
        
        args component2 ;
        component2.left=mid+1;
        component2.right=high;
        
        
        pthread_create(&thread1, NULL, merge_Sort, &component1);
        pthread_create(&thread2, NULL, merge_Sort, &component2);
        
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        
        
       merge(low, mid, high);
       
    }
   
}

void print_array(int size){

 for(int i=0;i<size;i++)
    printf("%d\t",array[i]);
    
    printf("\n");
}


int main(int argc , char **argv)
{  int i ;
   int size;

   FILE* inputfile;
   if(argv[1]==0)
    return 0;
    
    inputfile = fopen(argv[1], "r");

    
    
    if (inputfile ==NULL){
    printf("file not found \n");
    exit(1);}
    else{
    fscanf(inputfile, "%d", &size);
    printf("Size of array is: %d \n",size);
    printf("Unsorted array is: \n");
    for(i=0; i<size; i++)
        fscanf(inputfile, "%d", &array[i]);
    fclose(inputfile);
   
       print_array(size);
    
    args data ;
    data.left=0;
   data.right=size-1;
    
   
    pthread_t t;
    pthread_create(&t, NULL, merge_Sort, &data );
    pthread_join(t, NULL);
 
  printf("Sorted array is:\n");
  print_array(size);
    }
   return 0;
   } 
