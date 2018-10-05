#include <stdio.h> 
#include <string.h>
#include <conio.h>

#define is_available 1

typedef struct memory_chunk heap_memory; 
struct memory_chunk{ 
	heap_memory *next; 
	unsigned int size; 
	int is_free; 
	void *memory; 
}; 

int   memory_init  (void* ptr, unsigned int size);
void* memory_alloc (unsigned int size);
int   memory_check (void* ptr);
int   memory_free  (void* valid_ptr);

heap_memory mlist; 

int memory_init (void *ptr, unsigned int size){ 
	printf ("Memory inicialization: \n---------------------- ");


	mlist.next = NULL; 
	mlist.size = size; 
	mlist.is_free = is_available; 
	mlist.memory = ptr;

	printf ("Inicialized %d bytes in cell 0x%x\n\n", size, mlist.memory);

	return 1; 
} 

void* memory_alloc (unsigned int size){ 
	printf ("Memory allocation:\n------------------ ");

	if (size <= 0) { 
		printf("ERROR\n"); 
		return NULL; 
	} 

	int heap_size, index = 0;
	
	heap_memory *temp = &mlist; 
	while (temp) {
		heap_size = temp->size;
		temp = temp->next;
		index++;
	}

	temp = &mlist;


	int alloc_size = size + sizeof(heap_memory); 
	
	while(temp) { 
		if (temp->is_free == 1) { 
			/*
			if (temp->size == 0 && size <= heap_size){
				void * allocated_memory = (heap_memory*)(temp); 
				temp->size = size; 
				temp->is_free = 0; 
//				if (index > 1)
					temp->memory = (temp)+sizeof(temp->size) + sizeof(temp->is_free);
				heap_size -= size; 

				printf("Allocated %d bytes in cell: 0x%x\n\n", size, temp->memory); 

				heap_memory *last = temp;
				while (last->next){
					last = last->next;
				}
				last->size = heap_size;
				
				return temp->memory;
			}
			*/
			if (temp->size >= alloc_size) { 
				void * allocated_memory = (heap_memory*)(temp); 
				temp->size = size; 
				temp->is_free = 0;
//				if (index > 1)
					temp->memory = (temp)+sizeof(temp->size) + sizeof(temp->is_free);
				heap_size -= size;
				temp->next = (heap_memory*)temp->memory + size;
	
				heap_memory *new_memory_ptr = temp->next;
				new_memory_ptr->is_free = 1;
				new_memory_ptr->size = heap_size;
//				new_memory_ptr->memory = (new_memory_ptr) + sizeof (new_memory_ptr->size) + sizeof (new_memory_ptr->is_free);
				new_memory_ptr->next = NULL;

				printf("Allocated %d bytes in cell: 0x%x\n\n", size, temp->memory);
				
				return temp->memory; 
			}	 
		} 
		temp = temp->next; 
	}
	
	printf ("\nNo Memory Available\n\n"); 
	return NULL; 
} 

int memory_check (void* ptr){

	printf("Memory check: \n------------- ");

	heap_memory *temp = &mlist;

	printf("\n\tSize\tMemory-Ptr");
	while (temp) {
		printf("\n\t%d\t0x%x ", temp->size, temp->memory);
		temp = temp->next;
	}
	printf("\n\n");

	temp = &mlist;

	while (temp->next){
		if (temp->memory == ptr){
			if (temp->size == 0) {
				printf ("Memory block 0x%x is empty and ready for rewriting.\n\n", ptr);
				return 0;
			}
			else {
				printf ("Memory block 0x%x is used, can not be rewriten now.\n\n", ptr);
				return 1;
			}
		}
		temp = temp->next;
	}

	return 0;
}

int memory_free (void *valid_ptr){
	printf ("Memory free: \n----------- ");

	if (valid_ptr == NULL){
		printf ("ERROR: no valid pointer!\n");
		return 1;
	}

	int heap_size;

	heap_memory *temp = &mlist;
	while (temp) {
		heap_size = temp->size;
		temp = temp->next;
	}

	temp = &mlist;

	while (temp->next){
		if (temp->memory == valid_ptr) {
			heap_size += temp->size;
			temp->is_free = is_available;
			printf ("Deallocated %d bytes, memory block 0x%x is free now\n\n", temp->size, valid_ptr);
			temp->size = 0;
		}
		temp = temp->next;
	}

	temp->size = heap_size;

	return 0;
}

int main() { 
	char region[60];
	memory_init(region, 60);	
	void* pointer = memory_alloc(30);
	memory_check(pointer);

	char* pointer_2 = (char*)memory_alloc(5 * sizeof(char));
	memory_check(pointer_2);

	memory_free(pointer);

	memory_check(pointer);

	char* pointer_3 = (char*)memory_alloc(35 * sizeof(char));
	memory_check(pointer_3);

	//TODO user can use just 0.6 of initialized memory, need to be fixed FUCK blyat suka zajebalsa ja delat etot jebuchij projekt

	/*
	memory_check(pointer);	
	if (pointer)
		memset(pointer, 0, 10);
	if (pointer)
		memory_free (pointer);
	memory_check(pointer);
		
	char* another_pointer_3 = (char*) memory_alloc (200);
	memory_check(another_pointer_3);
	if (another_pointer_3)
		memset(another_pointer_3, 0, 10);
	if (another_pointer_3)
		memory_free(another_pointer_3);		
	memory_check(another_pointer_3);

	char *second = (char*)memory_alloc(150 * sizeof (char));
	memory_check(second);

	int *third = (int*)memory_alloc(150 * sizeof (int));
	memory_check(third);

	memory_free(third);

	memory_check(third);

	int *fourth = (int*)memory_alloc(100 * sizeof(int));

	memory_check(fourth);
	
	char *fifth = (char*)memory_alloc(10 * sizeof(char));

	*/

	return 1; 
}