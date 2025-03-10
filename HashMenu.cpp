/*
Nama: Serafino Kyrios Gunawan
NIM: 2802420126
*/
#include<stdio.h>
#include<stdlib.h>

#define TABLE_SIZE 10
#define EMPTY -1
#define DELETE -2

typedef struct Node
{
    int key;
    int value;
    struct Node* next;
} Node;

//	Hash Table
typedef struct HashTable
{
    int keys[TABLE_SIZE];
    int values[TABLE_SIZE];
    Node* chains[TABLE_SIZE];
} HashTable;

//	Hash Table Initialization
void initialization(HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
	{
        ht->keys[i] = EMPTY;
        ht->values[i] = 0;
        ht->chains[i] = NULL;
    }
}

//	Hash Division
int hash_division(int key)
{
    return key % TABLE_SIZE;
}

//	Hash Mid-square (Counting Digits)
int countDigits(int number)
{
    int count = 0;
    if (number == 0) return 1;
    while (number != 0)
	{
        number /= 10;
        count++;
    }
    return count;
}

//	Hash Mid-square
int hash_mid_square(int key)
{
	int key_squared = key * key;
	int len_key_squared = countDigits(key_squared);
	
	if (len_key_squared == 1)
	{
	     return key_squared%TABLE_SIZE;
	}
	
	else if (len_key_squared == 2)
	{
	    int result = key_squared;
	    
	    return result%TABLE_SIZE;
	}
	
	else
	{
	    int result = key_squared / 10;
	    
	    return result%TABLE_SIZE;
	}
}

//	Hash Folding
int hash_folding(int key)
{
    int sum = 0;
    
    while (key > 0)
	{
        sum += key % 100;
        key /= 100;
    }
    
    return sum % TABLE_SIZE;
}

//	Hash Digit Extraction
int hash_digit_extraction(int key)
{
    return (key / 10) % TABLE_SIZE;
}

//	Hash Rotation
int hash_rotation(int key)
{
    int last_digit = key % 10;
    key /= 10;
    
    key = last_digit * 10000 + key;
    return key % TABLE_SIZE;
}

//	Hash Functions
int hash(int ht_type, int key)
{
    switch (ht_type)
	{
        case 1: return hash_division(key);
        case 2: return hash_mid_square(key);
        case 3: return hash_folding(key);
        case 4: return hash_digit_extraction(key);
        case 5: return hash_rotation(key);
        default: return hash_division(key);
    }
}

//	Insert a key-value pair
void insert(HashTable *ht, int ht_type, int collision_type, int key, int value)
{
    int index = hash(ht_type, key);
    int original_index = index;

	// Linear Probing
    if (collision_type == 1)
	{
        while (ht->keys[index] != EMPTY && ht->keys[index] != DELETE && ht->keys[index] != key)
		{
            index = (index + 1) % TABLE_SIZE;
            
            if (index == original_index)
			{
				return;
			}
        }
        
        ht->keys[index] = key;
        ht->values[index] = value;
    }
    
    //	Chaining
	else if (collision_type == 2)
	{
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->value = value;
        newNode->next = ht->chains[index];
        ht->chains[index] = newNode;
    }
    
    //	Rehashing
	else if (collision_type == 3)
	{
        int new_index = (index + 7) % TABLE_SIZE;
        
        while (ht->keys[new_index] != EMPTY && ht->keys[new_index] != DELETE)
		{
            new_index = (new_index + 7) % TABLE_SIZE;
            if (new_index == index) return;
        }
        
        ht->keys[new_index] = key;
        ht->values[new_index] = value;
    }
}

//	Search for a Key in Hash Table
int search(HashTable *ht, int ht_type, int collision_type, int key)
{
    int index = hash(ht_type, key);
    int original_index = index;
	
	//	Collision Resolution Types
	//	Linear Probing
    if (collision_type == 1)
	{
        while (ht->keys[index] != EMPTY)
		{
            if (ht->keys[index] == key)
			{
				return ht->values[index];
			}
			
            index = (index + 1) % TABLE_SIZE;
            
            if (index == original_index) 
			{
				break;
			}
        }
    }
    
    //	Chaining
	else if (collision_type == 2)
	{
        Node* current = ht->chains[index];
        
        while (current)
		{
            if (current->key == key) return current->value;
            current = current->next;
        }
        
        return -1;
    }
    
	//	Rehashing
	else if (collision_type == 3)
	{
        int new_index = (index + 7) % TABLE_SIZE;
        while (ht->keys[new_index] != EMPTY) {
            if (ht->keys[new_index] == key) return ht->values[new_index];
            new_index = (new_index + 7) % TABLE_SIZE;
            if (new_index == index) break;
        }
    }
    
    //	Key Not Found
    return -1;
}

//	Displaying Hash Table
void display(HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
	{
        if (ht->keys[i] != EMPTY && ht->keys[i] != DELETE)
        {
        	printf("Slot %d: (%d, %d)\n", i, ht->keys[i], ht->values[i]);
		}
        else
        {
        	printf("Slot %d: Empty\n", i);
		}
        
        Node* current = ht->chains[i];
        
        while (current)
		{
            printf(" -> (%d, %d)", current->key, current->value);
            current = current->next;
        }
        printf("\n");
    }
}

int main()
{
	// MENU
	HashTable ht;
	initialization(&ht);
	
	int ht_type;
	int collision_type;
	
    printf("Hash Function Types\n1. Division\n2. Mid-Square\n3. Folding\n4. Digit Extraction\n5. Rotation\n");
    printf("Enter Hash Function Type (Example: 1-5): ");
    scanf("%d", &ht_type);

    printf("Collision Resolution Types\n1. Linear Probing\n2. Chaining\n3. Rehashing\n");
    printf("Enter Collision Resolution Type (Example: 1-3): ");
    scanf("%d", &collision_type);
	
	// User Insert, Display, and Search
	
	//	Insert
    insert(&ht, ht_type, collision_type, 10, 100);
    insert(&ht, ht_type, collision_type, 20, 200);
    insert(&ht, ht_type, collision_type, 25, 250);
    insert(&ht, ht_type, collision_type, 30, 300);
	
	//	Display
	display(&ht);
	
	//	Search
    int searchKey;
    printf("Enter Key to Search (Example: 0-x): ");
    scanf("%d", &searchKey);
    
    int result = search(&ht, ht_type, collision_type, searchKey);
    if (result != -1)
    {
    	printf("Key %d found with value %d\n", searchKey, result);
	}
    else
    {
    	printf("Key %d NOT FOUND\n", searchKey);
	}

	return 0;
}
