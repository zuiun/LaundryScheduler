#include <assert.h>
#include "auxiliary.h"
#include "priority_queue.h"

/*
 * Swaps two elements in priority queue
 *
 * pqueue: pqueue_t* = Priority queue
 * from_index: int = Index from which to swap
 * to_index: int = Index to which to swap
 *
 * Pre: pqueue != NULL, 0 <= from_index && from_index < pqueue->size, 0 <= to_index && to_index < pqueue->size
 * Post: Elements at from_index and to_index are swapped
 * Return: None
 */
void swap (pqueue_t* pqueue, int from_index, int to_index) {
    assert (pqueue != NULL);
    assert (0 <= from_index && from_index < pqueue->size);
    assert (0 <= to_index && to_index < pqueue->size);

    pqueue_e_t* temporary = pqueue->elements [to_index];

    pqueue->elements [to_index] = pqueue->elements [from_index];
    pqueue->elements [from_index] = temporary;
}

/*
 * Enforces minimum heap property upwards
 *
 * pqueue: pqueue_t* = Priority queue
 * index: int = Index to check
 *
 * Pre: pqueue != NULL, 0 <= index && index < pqueue->size
 * Post: Minimum heap property is maintained
 * Return: None
 */
void heapify_up (pqueue_t* pqueue, int index) {
    assert (pqueue != NULL);
    assert (0 <= index && index < pqueue->size);

    if (parent(index) >= 0 && pqueue->elements [index]->priority < pqueue->elements [parent(index)]->priority) {
        swap (pqueue, index, parent(index));
        heapify_up (pqueue, parent(index));
    }
}

/*
 * Enforces minimum heap property downwards
 *
 * pqueue: pqueue_t* = Priority queue
 * index: int = Index to check
 *
 * Pre: pqueue != NULL, 0 <= index && index < pqueue->size
 * Post: Minimum heap property is maintained
 * Return: None
 */
void heapify_down (pqueue_t* pqueue, int index) {
    assert (pqueue != NULL);
    assert (0 <= index && index < pqueue->size);

    int smallest = index;

    if (left_child(index) < pqueue->size && pqueue->elements[left_child(index)] != NULL && pqueue->elements[left_child(index)]->priority < pqueue->elements[smallest]->priority) {
        smallest = left_child(index);
    }

    if (right_child(index) < pqueue->size && pqueue->elements[right_child(index)] != NULL && pqueue->elements[right_child(index)]->priority < pqueue->elements[smallest]->priority) {
        smallest = right_child(index);
    }

    if (smallest != index) {
        swap (pqueue, index, smallest);
        heapify_down (pqueue, smallest);
    }
}

pqueue_t* create_pqueue (int max_elements) {
    assert (max_elements > 0);

    pqueue_t* pqueue = allocate (sizeof (pqueue_t));

    pqueue->elements = allocate (sizeof (pqueue_e_t*) * max_elements);
    pqueue->max_elements = max_elements;
    pqueue->size = 0;
    return pqueue;
}

pqueue_e_t* create_pqueue_e (void* backing_data, int priority) {
    assert (backing_data != NULL);

    pqueue_e_t* element = allocate (sizeof (pqueue_e_t));

    element->backing_data = backing_data;
    element->priority = priority;
    return element;
}

void enqueue (pqueue_t* pqueue, pqueue_e_t* element) {
    assert (pqueue != NULL);
    assert (element != NULL);

    int index = pqueue->size;

    if (index < pqueue->max_elements) {
        pqueue->elements [index] = element;
        pqueue->size ++;
        heapify_up (pqueue, index);
    } else {
        printf ("Cannot enqueue to full priority queue\n");
    }
}

pqueue_e_t* dequeue (pqueue_t* pqueue) {
    assert (pqueue != NULL);

    pqueue_e_t* element = NULL;
    int index = 0;

    if (pqueue->size == 0) {
        printf ("Cannot dequeue from empty priority queue\n");
    } else {
        element = pqueue->elements [0];
        pqueue->size --;

        if (pqueue->size > 1) {
            index = pqueue->size;
            swap (pqueue, 0, index);
            heapify_down (pqueue, 0);
        }

        pqueue->elements [index] = NULL;
    }

    return element;
}
