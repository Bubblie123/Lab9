#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType* next;
};

// Fill out this structure
struct HashType
{
    // create a pointer to a RecordType
    struct RecordType* record;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    return x % tableSize;
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
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
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
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
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    int index = hash(record->id, tableSize);
    if (hashTable[index].record == NULL) {
        hashTable[index].record = record;
        record->next = NULL;
    }
    else {
        struct RecordType *temp = hashTable[index].record;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = record;
        record->next = NULL;
    }
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    for (int i = 0; i < tableSize; i++) {
        printf("Index %d -> ", i);
        // Traverse the linked list at that index and print each record
        struct RecordType *currentRecord = hashTable[i].record;
        while (currentRecord != NULL) {
            printf("%d, %c, %d -> ", currentRecord->id, currentRecord->name, currentRecord->order);
            currentRecord = currentRecord->next;
        }
        printf("NULL\n");
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize the hash table of size 11
    int hashTableSize = 11;
    struct HashType * hashType = (struct HashType *)(calloc(hashTableSize, sizeof(struct HashType)));
    // create a variable hashTableSize and assign it a value

    // initialize a hashTable, use calloc (so everything is assigned to NULL)
    // for each record in pRecords, insert it into the hash table using the insertRecord function
    for (int i = 0; i < recordSz; i++) {
        insertRecord(hashType, pRecords + i, hashTableSize);
    }
    // call the display records function
    displayRecordsInHash(hashType, hashTableSize);
    // free all the allocated memory
    free(pRecords);
    free(hashType);

    return 0;
}
