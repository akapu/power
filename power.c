#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NODES 100
#define MAX_LEN_LINE 100
#define VIS 1
#define UNVIS 0


typedef struct node
{
    char data[MAX_LEN_LINE];
    int links[MAX_NODES];
    int len_links;
    unsigned char color;
} NODE;

int find_path(int *, NODE *, int *, int);

int main() {
    FILE *in = fopen("mexico-power-network.lst", "r");

    NODE nodes[MAX_NODES];
    int c;
    char temp[MAX_LEN_LINE];
    char *tok;
    int n_node;
    int i = 0;
    int j = 0;
    

    while ((c = getc(in)) != EOF)
    {
        if (c == '\n')
        {

            temp[i] = '\0';
            tok = strtok(temp, " ");
            n_node = atoi(tok);

            tok = strtok(NULL, " ");
            strcpy(nodes[n_node].data, tok);

            j = 0;

            while ((tok = strtok(NULL, " ")) != NULL)
            {
                nodes[n_node].links[j] = atoi(tok);
                j++;
            }

            nodes[n_node].len_links = j;

            nodes[n_node].color = UNVIS;

            i = 0;
        } 
        else
        {
            temp[i] = c;
            i++;
        }
    }
    fclose(in);

    int start, finish;

    scanf("%d %d", &start, &finish);

    int path[MAX_NODES];
    path[0] = start;
    int len_path = 1;

    if (find_path(path, nodes, &len_path, finish))
        for (i = 0; i < len_path; i++)
            printf("%d, ", path[i]);
    else
        printf("no solutions");

    printf("\n");
}

int find_path(int *path, NODE *nodes, int *len_path, int finish)
{
    int i = 0;
    int now = path[*len_path - 1];

    for (i = 0; i < nodes[now].len_links; i++)
        if (nodes[now].links[i] == finish)
        {
            path[*len_path] = finish;
            len_path++;
            return 1;
        }

    nodes[now].color = VIS;

    int link;

    for (i = 0; i < nodes[now].len_links; i++)
    {
        link = nodes[now].links[i];

        if (nodes[link].color == VIS)
            continue;

        path[*len_path] = link;
        *len_path++;

        if (find_path(path, nodes, len_path, finish))
            return 1;
    }

    *len_path--;

    return 0;
}

