#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct Graph {
    int V;
    Node **array;
} Graph;

Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int V) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (Node **)malloc(V * sizeof(Node *));
    int i;
    for(i=0; i<V; i++) {
        graph->array[i] = NULL;
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    Node *newNode = createNode(dest);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;
}

void printGraph(Graph *graph) {
    int i;
    for(i=0; i<graph->V; i++) {
        Node *temp = graph->array[i];
        printf("Adjacency list of vertex %d\n head ", i+1);
        while(temp) {
            printf("-> %d", temp->data+1);
            temp = temp->next;
        }
        printf("\n");
    }
}

void readMatrixFromFile(int arr[N][N]) {
    int i, j;
    FILE *fp = fopen("matrix.txt", "r");
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            fscanf(fp, "%d", &arr[i][j]);
        }
    }
    fclose(fp);
}

void matrixToAdjacencyList(int arr[N][N], Graph *graph) {
    int i, j;
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            if(arr[i][j] == 1) {
                addEdge(graph, i, j);
            }
        }
    }
}

Node * deleteNode(Node * head, int value){
    Node *p = head;
    Node *q = head->next;
    while(q->data!=value && q->next!= NULL)
    {
        p = p->next;
        q = q->next;
    }

    if(q->data == value){
        p->next = q->next;
        free(q);
    }
    return head;
}

int indegree(Graph *graph, int v) {
    int count = 0;
        Node *temp = graph->array[v];
        while(temp) {
            count++;
            temp = temp->next;
        }
    return count;
}

int main() {
    int arr[N][N]={0};
    int i,j,k=0,m=0;
    int taken[N]={0};
    readMatrixFromFile(arr);

    Graph *graph = createGraph(N);
    matrixToAdjacencyList(arr, graph);

    while(m<N) {
        k++;
        printf("\nDonem %d: ",k);
        for (i = 0; i < graph->V; ++i) {
            if (indegree(graph, i) == 0 && taken[i] != 1) {
                taken[i] = 1;
                m++;
                printf("Course-%d ", i + 1);
            }
        }

        for (j = 0; j < graph->V; ++j) {
            Node *temp = graph->array[j];
            while (temp != NULL) {
                    if (taken[temp->data] == 1) {
                        if(temp->next!=NULL) {
                            deleteNode(graph->array[j], temp->data);
                        }
                        else{
                                graph->array[j]=NULL;
                        }
                    }
                temp = temp->next;
            }
        }

    }
    printf("\n\nMinimum %d donemde tamamlanir",k);
    return 0;
}