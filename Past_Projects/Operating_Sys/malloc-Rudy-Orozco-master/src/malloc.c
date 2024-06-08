#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ALIGN4(s)         (((((s) - 1) >> 2) << 2) + 4)
#define BLOCK_DATA(b)     ((b) + 1)
#define BLOCK_HEADER(ptr) ((struct _block *)(ptr) - 1)

static int atexit_registered = 0;
static int num_mallocs       = 0;
static int num_frees         = 0;
static int num_reuses        = 0;
static int num_grows         = 0;
static int num_splits        = 0;
static int num_coalesces     = 0;
static int num_blocks        = 0;
static int num_requested     = 0;
static int max_heap          = 0;

/*
 *  \brief printStatistics
 *
 *  \param none
 *
 *  Prints the heap statistics upon process exit.  Registered
 *  via atexit()
 *
 *  \return none
 */
void printStatistics( void )
{
  printf("\nheap management statistics\n");
  printf("mallocs:\t%d\n", num_mallocs );
  printf("frees:\t\t%d\n", num_frees );
  printf("reuses:\t\t%d\n", num_reuses );
  printf("grows:\t\t%d\n", num_grows );
  printf("splits:\t\t%d\n", num_splits );
  printf("coalesces:\t%d\n", num_coalesces );
  printf("blocks:\t\t%d\n", num_blocks );
  printf("requested:\t%d\n", num_requested );
  printf("max heap:\t%d\n", max_heap );
}

struct _block 
{
   size_t  size;         /* Size of the allocated _block of memory in bytes */
   struct _block *next;  /* Pointer to the next _block of allocated memory  */
   bool   free;          /* Is this _block free?                            */
   char   padding[3];    /* Padding: IENTRTMzMjAgU3jMDEED                   */
};

struct _block *heapList = NULL; /* Free list to track the _blocks available */
struct _block *roamingPtr = NULL;

/*
 * \brief findFreeBlock
 *
 * \param last pointer to the linked list of free _blocks
 * \param size size of the _block needed in bytes 
 *
 * \return a _block that fits the request or NULL if no free _block matches
 *
 * \TODO Implement Next Fit
 * \TODO Implement Best Fit
 * \TODO Implement Worst Fit
 */
struct _block *findFreeBlock(struct _block **last, size_t size) 
{
   struct _block *curr = heapList;

#if defined FIT && FIT == 0
   /* First fit */
   //
   // While we haven't run off the end of the linked list and
   // while the current node we point to isn't free or isn't big enough
   // then continue to iterate over the list.  This loop ends either
   // with curr pointing to NULL, meaning we've run to the end of the list
   // without finding a node or it ends pointing to a free node that has enough
   // space for the request.
   // 
   while (curr && !(curr->free && curr->size >= size)) 
   {
      *last = curr;
      curr  = curr->next;
   }
#endif

// \TODO Put your Best Fit code in this #ifdef block
#if defined BEST && BEST == 0
      
   struct _block *temp = NULL;   // set temp to NULL initally
   struct _block **Lasttemp;

   int bestsize = 9999999;

   while (curr) // while the pointer is not at the end of the list
   {
      if(curr && curr->free && (curr->size > size) && (curr->size < bestsize)) // if the curr size less than the best size and is big enough for requested
      {
         bestsize = curr->size; // copy the worst size    

         Lasttemp = last;
         temp = curr;            // save the current node
      }
      *last = curr;              // Move to the next node
      curr  = curr->next;
   }
   last = Lasttemp;              // set the current node to the saved temporary nodes
   curr = temp;                  // set curr to temp, curr will be NULL if no block was found
   
#endif

// \TODO Put your Worst Fit code in this #ifdef block
#if defined WORST && WORST == 0
   /** \TODO Implement worst fit here */
   
   struct _block *temp = NULL;   // set temp to NULL initally
   struct _block **Lasttemp;

   int worstSize = 0;

   while (curr) // while the pointer is not at the end of the list
   {
      if(curr && curr->free && (curr->size >= worstSize)) // if the curr size is greater than the worst size so far
      {
         worstSize = curr->size; // copy the worst size    

         Lasttemp = last;
         temp = curr;            // save the current node
      }
      *last = curr;              // Move to the next node
      curr  = curr->next;        
   }
   last = Lasttemp;              // set the current node to the saved temporary nodes
   curr = temp;                  // set curr to temp, curr will be NULL if no block was found

#endif

// \TODO Put your Next Fit code in this #ifdef block
#if defined NEXT && NEXT == 0
   /** \TODO Implement next fit here */

   struct _block *head = curr;   // save the head of the heaplist (curr = heapList)
   struct _block *start = curr;  // to check if it loops back to where it started

   if(roamingPtr != NULL)        // if the roamingPtr is empty, it is at the beginning.
   {
      head = curr;               // save the head 
      curr = roamingPtr;         // set the curr to the last location
   }

   while (curr && !(curr->free && (curr->size >= size))) // while curr is not null, curr is not free and the size has not been found and has not looped once
   {
      *last = curr;        // set last 
      curr = curr->next;   // move curr to next
      roamingPtr = curr;   // update roamingPtr

      if((curr == *last) && (curr->next == NULL)) // if the curr is the last pointer and the next pointer is null
      {
         curr = head;               // set the curr to the head
      }

      if(start && (start == curr))  // if the curr is back to the start
      {
         curr = NULL;               // set curr to NULL, which will exit the loop.
      }
   }

#endif

   return curr;
}

/*
 * \brief growheap
 *
 * Given a requested size of memory, use sbrk() to dynamically 
 * increase the data segment of the calling process.  Updates
 * the free list with the newly allocated memory.
 *
 * \param last tail of the free _block list
 * \param size size in bytes to request from the OS
 *
 * \return returns the newly allocated _block of NULL if failed
 */
struct _block *growHeap(struct _block *last, size_t size) 
{
   num_grows++;
   /* Request more space from OS */
   struct _block *curr = (struct _block *)sbrk(0);
   struct _block *prev = (struct _block *)sbrk(sizeof(struct _block) + size);

   assert(curr == prev);

   /* OS allocation failed */
   if (curr == (struct _block *)-1) 
   {
      return NULL;
   }

   /* Update heapList if not set */
   if (heapList == NULL) 
   {
      heapList = curr;
   }

   /* Attach new _block to previous _block */
   if (last) 
   {
      last->next = curr;
   }

   /* Update _block metadata:
      Set the size of the new block and initialize the new block to "free".
      Set its next pointer to NULL since it's now the tail of the linked list.
   */
   curr->size = size;
   curr->next = NULL;
   curr->free = false;
   num_blocks++;
   return curr;
}

/*
 * \brief malloc
 *
 * finds a free _block of heap memory for the calling process.
 * if there is no free _block that satisfies the request then grows the 
 * heap and returns a new _block
 *
 * \param size size of the requested memory in bytes
 *
 * \return returns the requested memory allocation to the calling process 
 * or NULL if failed
 */
void *malloc(size_t size) 
{
   num_mallocs++;

   if(size > max_heap)
   {
      max_heap = size;
   }

   if( atexit_registered == 0 )
   {
      atexit_registered = 1;
      atexit( printStatistics );
   }

   /* Align to multiple of 4 */
   size = ALIGN4(size);

   /* Handle 0 size */
   if (size == 0) 
   {
      return NULL;
   }

   /* Look for free _block.  If a free block isn't found then we need to grow our heap. */

   struct _block *last = heapList;
   struct _block *next = findFreeBlock(&last, size);

   /* TODO: If the block found by findFreeBlock is larger than we need then:
            If the leftover space in the new block is greater than the sizeof(_block)+4 then
            split the block.
            If the leftover space in the new block is less than the sizeof(_block)+4 then
            don't split the block.
   */

   if(next && ((next->size - size) > sizeof(struct _block)+4))   // if the block is larger than need, split and reuse block
   {
      num_reuses++;
      num_splits++;

      struct _block *temp = NULL;         // Create a Temp
      //struct _block *newptr = next;     // Create newptr (to make things easier to read)
                                          // Note: Changed everything back to "next" so it can be returned correctly.

      temp = next->next;            // Make temporary save of the next pointer
      size_t oldsize = next->size;  // save old size

      next->next = (struct _block*)((long long)BLOCK_DATA(next) + (long long)size); // offset the next pointer
      next->size = size;                                                            // set new size

      if(next && next->next && next->next->next)   // verify next ptr and split the block
      {
         next->next->next = temp;                                    // Set the next ptr to temp
         next->next->size = oldsize - size - sizeof(struct _block);  // Set the size 
         next->next->free = true;                                    // Set free to true
      }
   }
   else if(next && (next->size - size) < sizeof(struct _block)+4) // if the block is less than struct(block), reuse block and don't split
   {    
      num_reuses++;                 
   }

   /* Could not find free _block, so grow heap */
   if (next == NULL) 
   {
      num_requested = num_requested + size;  
      next = growHeap(last, size);           
   }

   /* Could not find free _block or grow heap, so just return NULL */
   if (next == NULL) 
   {
      return NULL;
   }
   
   /* Mark _block as in use */
   next->free = false;

   /* Return data address associated with _block to the user */
   return BLOCK_DATA(next);
}

/*
 * \brief free
 *
 * frees the memory _block pointed to by pointer. if the _block is adjacent
 * to another _block then coalesces (combines) them
 *
 * \param ptr the heap memory to free
 *
 * \return none
 */
void free(void *ptr) 
{
   if (ptr == NULL) 
   {
      return;
   }

   /* Make _block as free */
   struct _block *curr = BLOCK_HEADER(ptr);
   assert(curr->free == 0);
   curr->free = true;
   num_frees++;

   /* TODO: Coalesce free _blocks.  If the next block or previous block 
            are free then combine them with this block being freed.
   */

   /* NOTE: I don't know how to implement to check the previous block, so only coalescing forward */

   struct _block * newptr = heapList;

   while(newptr)  //while newptr has not reached the end of the list (NULL).
   {
      if(newptr && (newptr->free == true)) // If the block is free
      {
         if(newptr->next && (newptr->next->free == true))   // If the next block is free
         {
            num_coalesces++;
            //num_blocks--;                                                                  // Not necessary? caused issues to count of num_blocks

            newptr->size = (newptr->size) + (newptr->next->size) + sizeof(struct _block);    // Add up the size of the next block
            newptr->next = newptr->next->next;                                               // Set the next pointer of the current to the next pointer after the next.
         }
         else  // if next block is not free
         {
            return;  // exit the function
         }
      }
      newptr = newptr->next;
   }
}

void *calloc( size_t nmemb, size_t size )
{
   // \TODO Implement calloc

   struct _block *newptr = malloc(nmemb * size);   // Malloc newptr
   memset(newptr, 0, nmemb * size);                // Set memory to 0 with the size

   return newptr;
}

void *realloc( void *ptr, size_t size )
{
   // \TODO Implement realloc

   // user passes in a ptr to realloc and we'll call it arg
   // allocate a new block using the new size call it newptr
   // copy from BLOCK_DATA(arg) to BLOCK_DATA(newptr) using memcpy
   // return BLOCK_DATA(newptr)

   struct _block *newptr = malloc(size);           // malloc newptr
   struct _block *oldblck = BLOCK_HEADER(ptr);     // get the old block data

   memcpy(BLOCK_DATA(newptr), ptr, oldblck->size); // copy the old data from the oldblck to the newptr

   return BLOCK_DATA(newptr);
}



/* vim: IENTRTMzMjAgU3ByaW5nIDIwMjM= -----------------------------------------*/
/* vim: set expandtab sts=3 sw=3 ts=6 ft=cpp: --------------------------------*/
