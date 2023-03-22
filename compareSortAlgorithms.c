#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if (l < r){
		int x = l + (r - l)/2;      // find middle
		mergeSort(pData, l, x);     // sort left half
		mergeSort(pData, x + 1, r);     // sort right half

		int n1= x - l + 1;
		int n2 = r - x;
		int left[n1], right[n2];

		memcpy(left, &pData[l], n1 * sizeof(int));      //copy from main array to subarray
		memcpy(right, &pData[x + 1], n2 * sizeof(int)); 

		int a = 0;
		int b = 0;
		int c = l;
		while(a < n1 && b < n2){       // merge subarrays into main
			if(left[a] <= right[b]){
				pData[c] = left[a];
				a++;
			}
			else{
				pData[c] = right[b];
				b++;
			}
			c++;
		}

		while(a < n1){      // put remaining from main array to left
			pData[c] = left[a];
			a++;
			c++;
		}

		while(b < n2){
			pData[c] = right[b];    // put remaining from main to right
			b++;
			c++;
		}
		extraMemoryAllocated += n1*sizeof(int) + n2*sizeof(int);
	}
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int x, y, key;

	for(x = 1; x < n; x++){
		key = pData[x];
		y = x - 1;

		while(y >= 0 && pData[y] > key){    // shift elements to the right
			pData[y+1] = pData[y];
			y = y - 1;
		}
		pData[y + 1] = key;     // put key into position
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	for(int i = 0; i < n-1; ++i){
		int s = 0;

		for(int j = 0; j < n - i - 1;++j){
			if(pData[j] > pData[j+1]){      // swap elements that are not in order
				int temp = pData[j];
				pData[j] = pData[j+1];
				pData[j+1] = temp;

				s = 1;
			}
		}

		if(s == 0){     // if no swaps, already sorted
			break;
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int min;

	for(int i = 0; i<n-1; ++i){
		min = i;

		for(int j = i+1; j<n; ++j){
			if(pData[j] < pData[min]){
				min = j;
			}
		}
		if(min != i){
			int temp = pData[i];
			pData[i] = pData[min];
			pData[min] = temp;
		}
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		for(int i = 0; i< dataSz; i++){
			fscanf(inFile, "%d", &((*ppData)[i]));
		}
		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}