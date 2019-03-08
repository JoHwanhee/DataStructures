#include <stdio.h>
#include <stdlib.h>

typedef struct tagQueue {
    struct tagVertex* front;
    struct tagVertex* real;
    int size;
} Queue;


typedef struct tagVertex {
    struct tagVertex* next;
    struct tagEdge* adjacencyList;
    struct tagEdge* last;
    int data;
    int visited;
    int index;
    int adjacencyCount;
} Vertex;

typedef struct tagEdge {
    int weight;
    struct tagEdge* next;
    struct tagVertex* from;
    struct tagVertex* to;
} Edge;

typedef struct tagGraph
{
    Vertex* vertices;
    int vertexCount;
    Vertex* last;
} Graph;


Graph* createGraph();
void destoryGraph(Graph* g);

Vertex* createVertex(int data);
void destoryVertex(Vertex* v);

Edge* createEdge(Vertex* from, Vertex* to, int weight);
void destoryEdge(Edge* e);

void addVertex(Graph* g, Vertex* v);
void addEdge(Vertex* v, Edge* e);
void printGraph(Graph* g);

void dfs(Vertex* v);
void bfs(Vertex* root);


void enQueue(Queue* queue, Vertex* v);
Vertex* deQueue(Queue* queue);
Queue* create_queue();
void destory_queue(Queue* queue);


void enQueue(Queue* queue, Vertex* v)
{   
    if(queue->size == 0)
    {
        queue->front = v;
        queue->real = v;
        queue->front->next = queue->real;
        queue->size++;
    }
    else
    {
        queue->real->next = v;
        queue->real = v;
        queue->size++;
    }
}

Vertex* deQueue(Queue* queue)
{
    if(queue->size > 0)
    {
        Vertex* v = queue->front;
        
        queue->front = queue->front->next;
        queue->size--;
        return v;
    }
    return NULL;
}

int isEmpty(Queue* queue)
{
    return queue->size < 1;
}

Queue* create_queue()
{
    Queue* queue = malloc(sizeof(Queue));
    queue->front = NULL;
    queue->real = NULL;
    queue->size = 0;

    return queue;
}

void destory_queue(Queue* queue)
{
    free(queue);
}

int main(int argc, char* argv[])
{
    Graph* g = createGraph();

    Vertex* a_vertex = createVertex('A');
    Vertex* b_vertex = createVertex('B');
    Vertex* c_vertex = createVertex('C');
    Vertex* d_vertex = createVertex('D');
    Vertex* e_vertex = createVertex('E');
    Vertex* f_vertex = createVertex('F');
    Vertex* g_vertex = createVertex('G');
    Vertex* h_vertex = createVertex('H');

    /*
     *       a
     *     / | \
     *     b c d
     *     |   | \
     *     e   f  g
     *         |
     *         H
     */

    addVertex(g, a_vertex);
    addVertex(g, b_vertex);
    addVertex(g, c_vertex);
    addVertex(g, d_vertex);
    addVertex(g, e_vertex);
    addVertex(g, f_vertex);
    addVertex(g, g_vertex);
    addVertex(g, h_vertex);

    addEdge(a_vertex, createEdge(a_vertex, b_vertex, 0));
    addEdge(a_vertex, createEdge(a_vertex, c_vertex, 0));
    addEdge(a_vertex, createEdge(a_vertex, d_vertex, 0));
    addEdge(b_vertex, createEdge(b_vertex, a_vertex, 0));
    addEdge(b_vertex, createEdge(b_vertex, e_vertex, 0));
    addEdge(c_vertex, createEdge(c_vertex, a_vertex, 0));
    addEdge(d_vertex, createEdge(d_vertex, a_vertex, 0));
    addEdge(d_vertex, createEdge(d_vertex, f_vertex, 0));
    addEdge(d_vertex, createEdge(d_vertex, g_vertex, 0));
    addEdge(e_vertex, createEdge(e_vertex, e_vertex, 0));
    addEdge(f_vertex, createEdge(f_vertex, d_vertex, 0));
    addEdge(f_vertex, createEdge(f_vertex, h_vertex, 0));
    addEdge(g_vertex, createEdge(g_vertex, d_vertex, 0));
    addEdge(h_vertex, createEdge(h_vertex, f_vertex, 0));

    printGraph(g);
    //dfs(a_vertex);o
    bfs(a_vertex);
    destoryGraph(g);
    getchar();

    return 0;
}

Graph * createGraph()
{
    Graph* g = malloc(sizeof(Graph));
    if (!g)
    {
        exit(1);
    }

    g->vertexCount = 0;
    g->vertices = NULL;
    g->last = NULL;
    return g;
}

void destoryGraph(Graph * g)
{
    if (g)
    {
        while (g->vertices != NULL)
        {
            Vertex* next = g->vertices->next;
            destoryVertex(g->vertices);
            g->vertices = next;
        }
        free(g);
    }
}

Vertex * createVertex(int data)
{
    Vertex* v = malloc(sizeof(Vertex));

    if (!v)
    {
        exit(1);
    }

    v->next = NULL;
    v->adjacencyList = NULL;
    v->data = data;
    v->index = -1;
    v->visited = 0;
    v->last = NULL;
    v->adjacencyCount = 0;

    return v;
}

void destoryVertex(Vertex * v)
{
    if (v)
    {
        while (v->adjacencyList != NULL)
        {
            Edge* next = v->adjacencyList->next;
            destoryEdge(v->adjacencyList);
            v->adjacencyList = next;
        }
        free(v);
    }

}

Edge * createEdge(Vertex * from, Vertex * to, int weight)
{
    Edge* e = malloc(sizeof(Edge));

    if (!e)
    {
        exit(1);
    }

    e->next = NULL;
    e->from = from;
    e->to = to;
    e->weight = weight;
    return e;
}

void destoryEdge(Edge* e)
{
    if (!e)
    {
        free(e);
    }
}

void addVertex(Graph * g, Vertex * v)
{
    if (g->vertexCount == 0)
    {
        g->vertices = v;
    }
    else
    {
        g->last->next = v;
    }
    g->last = v;
    v->index = g->vertexCount++;
}

void addEdge(Vertex * v, Edge * e)
{
    if (v->adjacencyCount == 0)
    {
        v->adjacencyList = e;
    }
    else
    {
        v->last->next = e;
    }
    v->last = e;
    v->adjacencyCount++;
}

void printGraph(Graph * g)
{
    if (g)
    {
        for (Vertex* temp = g->vertices; temp; temp = temp->next)
        {

            printf("%c [", temp->data);

            for (Edge* edge = temp->adjacencyList; edge; edge = edge->next)
            {
                printf("%c -> %c (%d) ", edge->from->data, edge->to->data, edge->weight);
            }

            printf("]\n");
        }
    }
}

void dfs(Vertex* v)
{
    if(!v)
    {
        return;
    }
    if(v->visited)
    {
        return;        
    }

    printf("%c", v->data);
    Edge* e = v->adjacencyList;
    v->visited = 1;

    while (e)
    {
        dfs(e->to);
        e = e->next;
    }
}

void bfs(Vertex* root)
{
    if(!root)
    {
        return;
    }

    Queue* q = create_queue();
    enQueue(q, root);

    while(!isEmpty(q))
    {
        Vertex* v = deQueue(q);
        printf("%c", v->data);
        v->visited = 1;

        Edge* e = v->adjacencyList;
        while(e)
        {
            if(!e->to->visited)
            {
                enQueue(q, e->to);
            }

            e = e->next;
        }
    }

    destory_queue(q);
}
