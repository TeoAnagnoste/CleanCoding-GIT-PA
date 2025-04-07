#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
    int data;
    struct NODE *next;
} NODE;

typedef struct 
{
    int v;
    int *vis;
    struct NODE **alst;
} g;

g GPH;

typedef struct 
{
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v)
{
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(g *g, int src, int dest)
{
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

g *create_g(int v)
{
    g *g = malloc(sizeof(g));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++)
    {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}

STK *create_s(int scap)
{
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int pshd, STK *s)
{
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

void DFS(g *g, STK *s, int v_nr)
{
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);

    push(v_nr, s);

    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        aux = aux->next;
    }
}

void insert_edges(g *g, int edg_nr, int nrv)
{
    int src, dest, i;
    printf("adauga %d muchii (de la 1 la %d)\n", edg_nr, nrv);
    for (i = 0; i < edg_nr; i++)
    {
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(g *g, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        g->vis[i] = 0;
    }
}

void canbe(g *g, int nrv, STK *s1)
{
    int *canbe = calloc(nrv, sizeof(int));

    for (int i = 0; i < nrv; i++)
    {
        DFS(g, s1, i);
        wipe(g, nrv);
        for (int j = 0; j < nrv; j++)
        {
            if (g->vis[j] == 1 && i != j)
            {
                canbe[i] = 1;
                break;
            }
        }
    }

    // Afișează rezultatul pentru fiecare nod
    printf("Nodurile care pot ajunge la alte noduri:\n");
    for (int i = 0; i < nrv; i++)
    {
        if (canbe[i] == 1)
        {
            printf("Nodul %d poate ajunge la cel puțin un alt nod.\n", i);
        }
        else
        {
            printf("Nodul %d nu poate ajunge la niciun alt nod.\n", i);
        }
    }

    free(canbe);
}

int main()
{
    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int vortex_1;
    int virtex_2;
    int ans;

    printf("Cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("Cate muchii are graful? ");
    scanf("%d", &edg_nr);

    g *g = create_g(nrv);
    STK *s1 = create_s(2 * nrv);
    insert_edges(g, edg_nr, nrv);
    canbe(g, nrv, s1);

    return 0;
}