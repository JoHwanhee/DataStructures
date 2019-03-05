#include <stdio.h>
#include <stdlib.h>

typedef struct tagVertex{
    struct tagVertex* next;
    struct tagEdge* adjacencyList;
    struct tagEdge* last;
    int data;
    int visited;
    int index;
    int adjacencyCount;
} Vertex;

typedef struct tagEdge{
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

int main(int argc, char* argv[])
{
    Graph* g = createGraph();

    Vertex* a_vertex = createVertex('A');
    Vertex* b_vertex = createVertex('B');
    Vertex* c_vertex = createVertex('C');
    Vertex* d_vertex = createVertex('D');

    addVertex(g, a_vertex);
    addVertex(g, b_vertex);
    addVertex(g, c_vertex);

    addEdge(a_vertex, createEdge(a_vertex, b_vertex, 0));
    addEdge(a_vertex, createEdge(a_vertex, d_vertex, 0));
    addEdge(b_vertex, createEdge(b_vertex, a_vertex, 0));
    addEdge(c_vertex, createEdge(c_vertex, a_vertex, 0));

    printGraph(g);
    destoryGraph(g);
    getchar();

    return 0;
}

Graph * createGraph()
{
    Graph* g = malloc(sizeof(Graph));
    if(!g)
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
    if(g)
    {
        while(g->vertices)
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
    
    if(!v)
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
    if(v)
    {
        while(v->adjacencyList != NULL)
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
   
    if(!e)
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
    if(!e)
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
    if(v->adjacencyCount == 0)
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
    if(g)
    {
        for(Vertex* temp = g->vertices; temp; temp=temp->next)
        {
            
            printf("%c [", temp->data);

            for(Edge* edge = temp->adjacencyList; edge; edge=edge->next)
            {
                printf("%c -> %c (%d) ", edge->from->data, edge->to->data, edge->weight);
            }

            printf("]\n");
        }
    }
}
