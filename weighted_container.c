#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "uthash.h"

typedef struct Element {
    int x;
    double weight;
    struct Element *next;
} Element;

typedef struct {
    int x;
    int index;
    UT_hash_handle hh;
} HashElement;

HashElement *hash_table = NULL;
Element *head = NULL;
int size = 0;
int capacity = 0;
double total_weight = 0.0;
int *r = NULL;
double *allsums = NULL;
int needs_update = 0;

void container_init(int init_capacity, int m) {
    capacity = init_capacity;
    r = malloc(m * sizeof(int));
    allsums = malloc(capacity * sizeof(double));
    
    if (r == NULL || allsums == NULL) {
        printf("Not enough memory!\n");
        exit(1);
    }
}

void add_to_hash(int x, int index) {
    HashElement *element = malloc(sizeof(HashElement));
    if (element == NULL) {
        printf("Failed to allocate memory for hash element.\n");
        exit(1);
    }
    element->x = x;
    element->index = index;
    HASH_ADD_INT(hash_table, x, element);
}

HashElement* find_in_hash(int x) {
    HashElement *element;
    HASH_FIND_INT(hash_table, &x, element);
    return element;
}

void remove_from_hash(int x) {
    HashElement *element = find_in_hash(x);
    if (element) {
        HASH_DEL(hash_table, element);
        free(element);
    }
}

void update_zhen(int m) {
    if (size == 0 || total_weight == 0.0) {
        return;
    }

    allsums[0] = head->weight / total_weight;
    Element *current = head->next;

    for (int i = 1; i < size; i++) {
        if (current != NULL) {
            allsums[i] = allsums[i - 1] + current->weight / total_weight;
            current = current->next;
        }
    }

    int i = 1;
    for (int j = 1; j <= m; j++) {
        while (i < size && allsums[i - 1] <= (double)(j - 1) / m) {
            i++;
        }
        r[j - 1] = i;
    }
}

void update_if_needed(int m) {
    if (needs_update) {
        update_zhen(m);
        needs_update = 0;
    }
}

void add_or_update_element(int *xi_array, double *wi_array, int num_elements) {
    for (int i = 0; i < num_elements; i++) {
        int xi = xi_array[i];
        double wi = wi_array[i];

        if (wi < 0.0) {
            printf("Negative weight for element %d\n", xi);
            continue;
        }

        HashElement *existing = find_in_hash(xi);
        if (existing) {
            Element *current = head;
            for (int j = 0; j <= existing->index; j++) {
                current = current->next;
            }
            if (current != NULL) {
                total_weight -= current->weight;
                current->weight = wi;
                total_weight += wi;
                needs_update = 1;
            } else {
                printf("Error: Element with index %d not found.\n", existing->index);
            }
        } else {
            Element *new_element = malloc(sizeof(Element));
            if (new_element == NULL) {
                printf("Failed to allocate memory for new element.\n");
                exit(1);
            }
            new_element->x = xi;
            new_element->weight = wi;
            new_element->next = head;
            head = new_element;
            size++;
            total_weight+=wi;
            add_to_hash(xi,size-1);
        }
    }
}

void remove_element(int *xi_array, int num_elements, int m) {
    for (int i = 0; i < num_elements; i++) {
        int xi = xi_array[i];
        HashElement *existing = find_in_hash(xi);
        if (!existing) {
            printf("Element %d not found\n", xi);
            continue;
        }
        int index = existing->index;
        Element *current = head;
        Element *prev = NULL;
        for (int j = 0; j < index; j++) {
            prev = current;
            current = current->next;
        }
        total_weight -= current->weight;
        if (prev) {
            prev->next = current->next;
            } else {
            head = current->next;
        }
        free(current);
        size--;
        for (int j = index; j < size; j++) {
            HashElement *e = find_in_hash(head->x);
            e->index--;
            head = head->next;
        }
        remove_from_hash(xi);
        needs_update = 1;
    }
}

void random_select(int m, int num_selections) {
    if (size == 0 || total_weight == 0.0) {
        printf("Container is empty or weight is zero\n");
        return;
    }
    update_if_needed(m);
    printf("Randomly picked elements:\n");
    for (int i = 0; i < num_selections; i++) {
        double random = (double)rand() / RAND_MAX;
        int j = (int)(m * random);
        if (j >= m) j = m - 1;
        int idx = r[j];
        Element *current = head;
        for (int k = 0; k < idx; k++) {
            current = current->next;
        }
        printf("%d\n", current->x);
    }
}

void display_container() {
    printf("Container state:\n");
    if (size == 0) {
        printf("Container is empty\n");
    } else {
        printf("Total weight: %.2f\n", total_weight);
        Element *current = head;
        int index = 0;
        while (current) {
            printf("%5d | %7d | %.2f \n", index++, current->x, current->weight);
            current = current->next;
        }
    }
}

void menu(int m) {
    int choice;
    while (1) {
        printf("\n1. Add or update element\n");
        printf("2. Delete element\n");
        printf("3. Randomly pick element\n");
        printf("4. Exit\n");
        printf("5. Display container\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            int num_elements;
            printf("Enter number of elements: ");
            scanf("%d", &num_elements);
            int *xi_array = malloc(num_elements * sizeof(int));
            double *wi_array = malloc(num_elements * sizeof(double));
            for (int i = 0; i < num_elements; i++) {
                printf("Enter element value (xi): ");
                scanf("%d", &xi_array[i]);
                printf("Enter element weight (wi): ");
                scanf("%lf", &wi_array[i]);
                add_or_update_element(xi_array, wi_array, num_elements);
            }
            free(xi_array);
            free(wi_array);
            
        } else if (choice == 2) {
            int num_elements;
            printf("Enter number of elements: ");
            scanf("%d", &num_elements);
            int *xi_array = malloc(num_elements * sizeof(int));
            for (int i = 0; i < num_elements; i++) {
                printf("Enter value element (xi) to delete: ");
                scanf("%d", &xi_array[i]);
            }
            remove_element(xi_array, num_elements, m);
            free(xi_array);
            
        } else if (choice == 3) {
            int num_selections;
            printf("Enter number of elements: ");
            scanf("%d", &num_selections);
            random_select(m, num_selections);
            
        } else if (choice == 5) {
            display_container();
            
        } else if (choice == 4) {
            break;
        } else {
            printf("Wrong. Try again.\n");
        }
    }
}

int main() {
    srand(time(NULL));
    int m = 100;
    container_init(1000, m);
    menu(m);
    free(r);
    free(allsums);
    Element *current = head;
    while (current) {
        Element *tmp = current;
        current = current->next;
        free(tmp);
    }
    HashElement *current_hash, *tmp_hash;
    HASH_ITER(hh, hash_table, current_hash, tmp_hash) {
        HASH_DEL(hash_table, current_hash);
        free(current_hash);
    }
    return 0;
}