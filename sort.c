#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}


void heapify(int arr[], int size, int i)
{
    int root = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < size && arr[left] > arr[root])
    {
        root = left;
    }

    if(right < size && arr[right] > arr[root])
    {
        root = right;
    }

    if(root != i)
    {
        swap(&arr[i], &arr[root]);

        heapify(arr, size, root);
    }


}
// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
	
//want the largest element to be at the root
    for(int i = n / 2 - 1; i>= 0; i--)
    {
        heapify(arr, n, i);
    }

    for(int i = n - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
    }
}

void merge(int pData[], int l, int m, int r)
{

  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  
//temp arrays to store the left elements and right elements
  int *lTemp = (int*) malloc(n1*sizeof(int));
  int *rTemp = (int*) malloc(n2*sizeof(int));

  for (i = 0; i < n1; i++)
    lTemp[i] = pData[l + i];
  for (j = 0; j < n2; j++)
    rTemp[j] = pData[m + 1+ j];

  i = 0; // Initial index of first subarray
  j = 0; // Initial index of second subarray
  k = l; // Initial index of merged subarray
  
  while (i < n1 && j < n2)
  {
    if (lTemp[i] <= rTemp[j])
    {
      pData[k] = lTemp[i];
      i++;
    }
    else
    {
      pData[k] = rTemp[j];
      j++;
    }
      k++;
  }
/* Copy the remaining elements of L[], if there
are any */
  while (i < n1)
  {
    pData[k] = lTemp[i];
    i++;
    k++;
  }
/* Copy the remaining elements of R[], if there
are any */
  while (j < n2)
  {
    pData[k] = rTemp[j];
    j++;
    k++;
  }
  free(lTemp);
  free(rTemp);
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
    	if (l < r)
  {
  //midpoint bc divide and conquer 
    int m = (l+r)/2;

    mergeSort(pData, l, m);
    mergeSort(pData, m+1, r);

    merge(pData, l, m, r);
  }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
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
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
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
