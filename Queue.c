#include <stdio.h>
#include <stdlib.h>

typedef struct quque {
	int* array;
	int size, front, rear, capacity;
} Queue;

Queue* createQueue(int capacity)
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));

	if(queue == NULL)
	{
		printf("Heap over.");
		exit(1);
	}

	queue->array = (int *)malloc(sizeof(int) * capacity);
	
	if (queue->array == NULL)
	{
		printf("Heap over.");
		exit(1);
	}

	queue->capacity = capacity;
	queue->size = 0;
	queue->front = 0;
	queue->rear = capacity - 1;

	return queue;
}

int isFull(Queue* queue)
{
	return queue->size == queue->capacity;
}

int isEmpty(Queue* queue)
{
	return queue->size == 0;
}

void enqueue(Queue* queue, int data)
{
	if(isFull(queue))
	{
		printf("Queue is full.");
		return;
	}

	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->size++;
	queue->array[queue->rear] = data;

	printf("enqueue : %d\n", data);
}

int dequeue(Queue* queue)
{
	if (isEmpty(queue))
	{
		printf("Queue is empty.");
		return INT_MIN;
	}

	int retData = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size--;
	return retData;
}

int front(Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->front];
}

int rear(Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->rear];
}




int main(void)
{
	Queue* queue = createQueue(10);
	enqueue(queue, 1);
	enqueue(queue, 2);
	enqueue(queue, 3);
	enqueue(queue, 4);
	enqueue(queue, 5);
	enqueue(queue, 6);
	enqueue(queue, 7);
	enqueue(queue, 8);
	enqueue(queue, 9);
	enqueue(queue, 10);

	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));

	enqueue(queue, 5);
	printf("%d \n", dequeue(queue));

	enqueue(queue, 1);

	printf("front : %d \n", front(queue));
	printf("rear : %d \n", rear(queue));
	getchar();

	return 0;
}