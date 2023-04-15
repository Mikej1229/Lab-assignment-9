#include <stdio.h>
#include <stdlib.h> 

struct RecordType
{
    int     id;
    char    name[50];
    int     order;
};


struct HashType
{
    struct RecordType * pData;
};

int hash(int x)
{
    return x % 10;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%s ", pRecord->name); // changed to a string
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %s %d\n", pData[i].id, pData[i].name, pData[i].order); // changed to a string
    }
    printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;
    struct RecordType * pRecord;
    for (i=0;i<hashSz;++i)
    {
        pRecord = (pHashArray + i)-> pData;
        if (pRecord != NULL)
        {
            printf("Index %d -> ", i); 
            while (pRecord != NULL)
            {
                printf("%d %s %d -> ", pRecord->id, pRecord->name, pRecord->order);
                pRecord = (pHashArray + (++i))-> pData; 
            }
            printf("\n");
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    struct HashType hashTable[10] = { 0 };

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    for (int i = 0; i < recordSz; i++) {
        int index = hash(pRecords[i].id);
        while (hashTable[index].pData != NULL) {
            index = (index + 1) % 10; 
        }
        hashTable[index].pData = &pRecords[i];
    }

}
