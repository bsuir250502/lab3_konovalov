#include <stdlib.h>
#include <string.h>
#include "optlib.h"
#include "service.h"
#define MAX_STR_LENGTH 100
#define MAX_STR_COUNT 20
#define MAX_RING_ELEM_COUNT 8

typedef struct ring_ {
    struct ring_ *next;
    char strings[MAX_STR_COUNT][MAX_STR_LENGTH];
    int str_count;
} ring_t;

int input_ring_data(ring_t *);
int compare_str(const void *, const void *);
int compare_ring_elements(const void *, const void *);
ring_t *sort_ring(ring_t *);

int main(int argc, char **argv)
{
    int i = 0, str_count;
    ring_t *ring;
    ring_t *ring_start;
    if (!options(argc, argv))
        return 0;
    ring = ring_start = (ring_t *) calloc(1, sizeof(ring));
    str_count = input_ring_data(ring);
    qsort(ring->strings, str_count, sizeof(char *), compare_str);
    for (i = 0; i < MAX_RING_ELEM_COUNT - 1; i++) {
        ring->next = (ring_t *) calloc(1, sizeof(ring_t));
        ring = ring->next;
        str_count = input_ring_data(ring);
        qsort(ring->strings, str_count, sizeof(char *), compare_str);
    }
    ring->next = ring_start;
    ring_start = sort_ring(ring_start);
    for (i = 0; i < MAX_RING_ELEM_COUNT; i++) {
        printf("%s\n", ring_start->strings[0]);
        ring_start = ring_start->next;
    }
    return (0);                 /* I like it */
}

int input_ring_data(ring_t * ring)
{
    int end = 0;
    ring->str_count = 0;
    printf("Maximum 20 strings allowed. Deal with it.\n");
    while (!end) {
        printf("Print string #%d. To end input press enter:\n",
               ring->str_count + 1);
        if (fgets_c(ring->strings[ring->str_count], MAX_STR_LENGTH, stdin)
            == '\n' || ring->str_count > MAX_STR_COUNT) {
            end = 1;
            continue;
        }
        ring->str_count++;
    }
    return ring->str_count;
}

int compare_str(const void *a, const void *b)
{
    return strcmp((char *) a, (char *) b);
}

int compare_ring_elements(const void *a, const void *b)
{
    ring_t *first, *second;
    first = *(ring_t **) a;
    second = *(ring_t **) b;
    return strcmp(first->strings[0], second->strings[0]);
}

ring_t *sort_ring(ring_t * ring)
{
    ring_t *ring_elements[MAX_RING_ELEM_COUNT];
    ring_t *ring_current = ring;
    int i = 0;
    for (i = 0; i < MAX_RING_ELEM_COUNT; i++) {
        ring_elements[i] = ring_current;
        ring_current = ring_current->next;
    }
    qsort(&ring_elements[0], MAX_RING_ELEM_COUNT, sizeof(ring_t *),
          compare_ring_elements);
    for (i = 0; i < MAX_RING_ELEM_COUNT - 1; i++)
        ring_elements[i]->next = ring_elements[i + 1];
    ring_elements[i]->next = ring_elements[0];
    return ring_elements[0];
}
