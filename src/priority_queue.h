#define parent(index) (index - 1) / 2
#define left_child(index) (index * 2) + 1
#define right_child(index) left_child(index) + 1

/*
 * Priority queue element
 *
 * data: void* = Element data
 * priority: int = Element priority
 */
typedef struct PriorityQueueElement {
    void* data;
    int priority;
} pqueue_e_t;

/*
 * Minimum priority queue
 *
 * elements: pqueue_e_t** = Elements
 * max_elements: int = Maximum number of elements
 * size: int = Current number of elements
 */
typedef struct PriorityQueue {
    pqueue_e_t** elements;
    int max_elements;
    int size;
} pqueue_t;

/*
 * Creates a priority queue
 *
 * max_elements: int = Maximum number of elements
 *
 * Pre: max_elements > 0
 * Post: None
 * Return: New priority queue
 */
pqueue_t* create_pqueue (int max_elements);
/*
 * Creates a priority queue element
 *
 * data: void* = Element data
 * priority: int = Element priority
 *
 * Pre: data != NULL
 * Post: None
 * Return: New priority queue element
 */
pqueue_e_t* create_pqueue_e (void* const data, int priority);
/*
 * Adds an element to priority queue
 *
 * pqueue: pqueue_t* = Priority queue
 * element: pqueue_e_t* = Element to add
 *
 * Pre: pqueue != NULL, element != NULL
 * Post: Element is added to priority queue if there is space
 * Return: None
 */
void enqueue (pqueue_t* pqueue, pqueue_e_t* const element);
/*
 * Removes smallest element from priority queue
 *
 * pqueue: pqueue_t* = Priority queue
 *
 * Pre: pqueue != NULL
 * Post: Smallest element is removed from priority queue if it exists
 * Return: Smallest element
 */
pqueue_e_t* dequeue (pqueue_t* pqueue);
/*
 * Frees priority queue
 * It is the user's responsibility to free individual elements
 *
 * pqueue: pqueue_t* = Priority queue
 *
 * Pre: pqueue != NULL
 * Post: pqueue and pqueue->elements are freed
 * Return: None
 */
void free_pqueue (pqueue_t* pqueue);
/*
 * Frees priority queue element
 * It is the user's responsibility to free element data
 *
 * element: pqueue_e_t* = Priority queue element
 *
 * Pre: element != NULL
 * Post: element is freed
 * Return: Element data
 */
void* free_pqueue_e (pqueue_e_t* element);
