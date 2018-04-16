#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int data;
    struct node *next;
};

#define INT_MAX 100000;

void insert(struct node *G[], int vertex1, int vertex2);
void enqueue(struct node **head, struct node **tail, int s);
void bfs(struct node *G[], int source, int no_vertices);
int dequeue(struct node **head, struct node **tail);
void findPath(int i, int pred[]);

int main()
{
	struct node *G[20];
	int no_vertices;
	int no_edges;
	int vertex1,vertex2;
	int i;
	int source;

	for (int i = 0; i < 20; ++i)
	{
		G[i] = NULL;
	}

	scanf("%d",&no_vertices);
	scanf("%d",&no_edges);

	for (i = 0; i < no_edges; ++i)
	{
		scanf("%d %d",&vertex1,&vertex2);	
		insert(G,vertex1,vertex2);
	}

	scanf("%d",&source);

	bfs(G,source,no_vertices);

    return 0;
}

void insert(struct node *G[], int vertex1, int vertex2)
{
	struct node *p = NULL;
	struct node *q = NULL;

	q = (struct node *)malloc(sizeof(struct node));

	q->data = vertex2;
	q->next = NULL;

	if(G[vertex1] == NULL)
	{
		G[vertex1] = q; 
	}
	else
	{
		p = G[vertex1];

		while(p->next != NULL)
		{
			p = p->next;
		}
		p->next = q;
	}
}

void bfs(struct node *G[], int source, int no_vertices)
{
	int color[20];
	int dist[20];
	int pred[20];
	struct node *head = NULL;
    struct node *tail = NULL;
    struct node *temp = NULL;
    int u;
    int i;

    for (i = 0; i < 20; ++i)
	{
		if(i != source)
		{
			color[i] = 0;
			dist[i] = INT_MAX;
			pred[i] = -10;
		}
	}

	color[source] = 1;
	dist[source] = 0;
	pred[source] = -1;

	enqueue(&head,&tail,source);

	do
	{
		u = dequeue(&head,&tail);
		temp = G[u];

		while(temp != NULL)
		{
			if(color[temp->data] == 0)
			{
				color[temp->data] = 1;
				dist[temp->data] = dist[u] + 1;
				pred[temp->data] = u;
				enqueue(&head,&tail,temp->data);
			}
			temp = temp->next;
		}
		color[u] = 2;
	}
	while(head != NULL);

	for(i = 0; i < no_vertices; i++)
	{
		printf("min dist from source %d for vertex %d is %d\n",source,i,dist[i]);
	}

	for(i = 0; i < no_vertices; i++)
	{
		findPath(i, pred);
	}
}

void enqueue(struct node **head, struct node **tail, int s)
{
	struct node *temp = NULL;
	temp = (struct node *)malloc(sizeof(struct node));

	if (temp == NULL)
    {
        printf("Memory full!");
    }
	else if(*tail == NULL)
	{
		*tail = (struct node *)malloc(sizeof(struct node));
		(*tail)->next = NULL;
		(*tail)->data = s; 
		*head = *tail;
	}
	else
	{
		(*tail)->next = temp;
		temp->data = s;
		temp->next = NULL;
		*tail = temp;
	}
}

int dequeue(struct node **head, struct node **tail)
{
	struct node *temp = NULL;
	int item;

	temp = *head;

	if (*head == NULL)
    {
        printf("Queue is empty!");
        return -1;
    }
	else if(*tail == *head)
	{
		item = temp->data;
		free(temp);
		*head = NULL;
		*tail = NULL;

		return item;
	}
	else
	{
		item = temp->data;
		*head = temp->next;
		free(temp);

		return item;
	}
}

void findPath(int i, int pred[])
{
	while(i != -1){
		printf("%d ", i);
		i = pred[i];
	}
}