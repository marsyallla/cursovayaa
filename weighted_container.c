
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "uthash.h" 
typedef struct {
    int x;         
    double weight;
} Element;
typedef struct {
    int x;               
    int index;           
    UT_hash_handle hh;   
} HashElement;
HashElement *hash_table = NULL; 
Element *container = NULL;     
int size = 0;                   
int capacity = 0;              
double total_weight = 0.0;     
int *r = NULL;                 
double *allsums = NULL;        
int needs_update = 0;           
void container_init(int init_capacity, int m) {
    capacity = init_capacity;
    container = malloc(capacity * sizeof(Element));
    allsums = malloc(capacity * sizeof(double));
    r = malloc(m * sizeof(int));
    if (container == NULL  allsums == NULL  r == NULL) {
        printf("Not enough memory!\n");
        exit(1);
    }
}
void expand_capacity(int additional_space) {
    capacity += additional_space;
    container = realloc(container, capacity * sizeof(Element));
    allsums = realloc(allsums, capacity * sizeof(double));
    if (container == NULL || allsums == NULL) {
        printf("Not enough memory!\n");
        exit(1);
    }
}
void add_to_hash(int x, int index) {
    HashElement *element = malloc(sizeof(HashElement));
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
    allsums[0] = container[0].weight / total_weight;
    for (int i = 1; i < size; i++) {
        allsums[i] = allsums[i - 1] + container[i].weight / total_weight;
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
    }
}
void add_or_update_element( int *xi_array, double *wi_array,int num_elements, int m) {
    for(int i=0;i<num_elements;i++){
        int xi=xi_array[i];
        double wi=wi_array[i];
    }
    if (wi <= 0.0) {
        printf("Negative weight\n");
        return;
    }
    HashElement *existing = find_in_hash(xi);
    if (existing) {
        total_weight -= container[existing->index].weight;
        container[existing->index].weight = wi;
        total_weight += wi;
        needs_update = 1;
        continue;
    }
    if (size == capacity) {
        expand_capacity(1000); 
    }
    container[size].x = xi;
    container[size].weight = wi;
    add_to_hash(xi, size);
    size++;
    total_weight += wi;
    needs_update = 1;
}
void remove_element(int *xi_array, int num_elements, int m) {
    for(int i=0;i<num_elements;i++){
        int xi=xi_array[i];
    HashElement *existing = find_in_hash(xi);
    if (!existing) {
        printf("Element %d not found\n", xi);
        continue;
    }
    int index = existing->index;
    total_weight -= container[index].weight;
    for (int j = index; j < size - 1; j++) {
        container[j] = container[j + 1];
    }
    size--;
    for (int j = index; j < size; j++) {
        HashElement *e = find_in_hash(container[j].x);
        if (e) {
            e->index = j;
        }
    }
    remove_from_hash(xi);
    needs_update = 1;
}
void random_select(int m, int num_selections) {
    if (size == 0 || total_weight == 0.0) {
        printf("Container is empty or weight is zero\n");
        return -1;
    }
    update_if_needed(m);
    printf("Randomly picked elements:");
    for(int i=0;i<num_selections;i++){
    double random = (double)rand() / RAND_MAX;
    int j = (int)(m * random);
    if (j >= m) j = m - 1; 
    int i = r[j];
    while (i < size && random > allsums[i]) {
        i++;
    }
    if (i < size) {
        printf("%d\n", container[i].x);
        return container[i].x;
    }else {
        printf("Error:not selected element.\n");
        return -1;
    }
}
void display_container() {
    printf("Container state:\n");
    if (size == 0) {
        printf("Container is empty\n");
    } else {
        printf("Total weight: %.2f\n", total_weight);
        for (int i = 0; i < size; i++) {
            printf("%5d | %7d | %.2f \n", i, container[i].x, container[i].weight);
        }
    }
}
void menu(int m) {
    int choice;
    while (1) {
        printf("\n1. Add or update element\n");
        printf("2.Delete element\n");
        printf("3. Randomly pick element\n");
        printf("4. Exit\n");
        printf("5. Display container\n");
        printf("Your choiceр: ");
        scanf("%d", &choice);
        if (choice == 1) {
            int num_elements;
             printf("Enter number of elements:");
            scanf("%d", &num_elements);
            int *xi_array = malloc(num_elements * sizeof(int));
            double *wi_array = malloc(num_elements * sizeof(double));
            for (int i = 0; i < num_elements; i++) {
            printf("Enter element value (xi): ");
            scanf("%d", &xi_array[i]);
            printf("Enter element weight (wi): ");
            scanf("%lf", &wi_array[i]);
            add_or_update_element(xi, wi, m);
        } else if (choice == 2) {
            int num_elements;
             printf("Enter number of elements:");
            scanf("%d", &num_elements);
            int *xi_array = malloc(num_elements * sizeof(int));
            for (int i = 0; i < num_elements; i++) {
            printf("Enter value elemnt (xi) to delete: ");
            scanf("%d", &xi_array[i]);
            }
            remove_element(xi_array, num_elements, m) 
            free(xi_array)
        }
        } else if (choice == 3) {
            int num_selections;
            printf("Enter number of elements:");
            scanf("%d", &num_selections);
            random_select(m,num_selections);
        } else if (choice == 5) {
            display_container();
        } else if (choice == 4) {
            break;
        } else {
            printf("Wrong.Try again.\n");
        }
    }
}
int main() {
    srand(time(NULL)); 
    int m = 100; 
    container_init(1000, m); 
    menu(m); 
    free(container);
    free(allsums);
    free(r);
    HashElement *current, *tmp;
    HASH_ITER(hh, hash_table, current, tmp) {
        HASH_DEL(hash_table, current);
        free(current);
    }
    return 0;
}