#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

#define TWO_TIME_LARGER 2

queue_t* create_queue(int capacity) {
    queue_t* queue = malloc(sizeof(queue_t));
    //Check if malloc was successful
    if(!queue) {
        fprintf(stderr, "Error: Malloc\n");
        free(queue);
        queue = NULL;
        return NULL;
    }
    queue -> data = malloc(sizeof(void*) * capacity);
    if(!queue->data) {
        fprintf(stderr, "Error: Malloc\n");
        free(queue);
        queue = NULL;
        return NULL;
    }
    queue -> front = 0;
    queue -> rear = 0;
    queue -> size = capacity;
    queue -> num_of_elements = 0;
    return queue;
}

void delete_queue(queue_t *queue) {
    free(queue->data);
    free(queue);
}

bool push_to_queue(queue_t *queue, void *data) {
    int tmp_ind = 0;
    //Check if queue is full
    if(queue->num_of_elements >= queue->size) {
        queue->size = queue->size * TWO_TIME_LARGER;
        void** tmp = malloc(sizeof(void*) * queue->size);
        if(!tmp) {
            fprintf(stderr, "Error: Malloc tmp\n");
            return false;
        }

        for(int i = 0; i < queue->num_of_elements; i++) {
            tmp_ind = (queue->front + i) % queue->num_of_elements;
            tmp[i] = queue->data[tmp_ind];
        }
        
        free(queue->data);
        queue->data = tmp;

        //Set front to 0-th index
        queue->front = 0;
        //Change queue rear to number of element because when queue is full queue rear = 0
        queue->rear = queue->num_of_elements;
    }


    //Add pointer element to the array
    queue->data[queue->rear] = data;
    //Move pointer rear to the next empty space
    queue->rear = (queue->rear + 1) % queue->size;
    //Increase number of elements in the array
    queue->num_of_elements++;
    return true;
}

void* pop_from_queue(queue_t *queue) {
    int tmp_ind = 0;
    void* element;
    //Check if queue is empty
    if(queue->num_of_elements <= 0) {
        return NULL;
    }

    //Load element to temporary variable, that will be returned
    element = queue->data[queue->front];

    if(queue->num_of_elements <= (queue->size / 3)) {
        int tmp_size = queue->size;
        queue->size = (queue->size / 3);
        void** tmp1 = malloc(sizeof(void*) * queue->size);
        if(!tmp1) {
            fprintf(stderr, "Error: Malloc tmp\n");
            return false;
        }
        for(int i = 0; i < queue->num_of_elements; i++) {
            tmp_ind = (queue->front + i) % tmp_size;
            tmp1[i] = queue->data[tmp_ind];
        }
        
        free(queue->data);
        queue->data = tmp1;
        //Set front to 0-th index
        queue->front = 0;
        //Change queue rear to number of element because when queue is full queue rear = 0
        queue->rear = queue->num_of_elements % queue->size;
    }

    //Move pointer front to next element
    queue->front = (queue->front + 1) % queue->size;
    //Decrease number of elements in array
    queue->num_of_elements--;
    return element;
}

void* get_from_queue(queue_t *queue, int idx) {
    int tmp_idx = (idx + queue->front) % queue->size;
    if(idx >= queue->size || idx < 0) {
        return NULL;
    }
    if(tmp_idx >= queue->rear) {
        return NULL;
    }

    return queue->data[tmp_idx];
}

int get_queue_size(queue_t *queue) {
    return queue -> num_of_elements;
}
