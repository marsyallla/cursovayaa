#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
typedef struct {
    int x;         
    double weight; 
} Element;
Element* container = NULL;     
int size = 0;                  
int capacity = 0;             
double total_weight = 0.0;     
int* r = NULL;                 
double* allsums = NULL;       
void container_init(int init_capacity, int m) {
    capacity = init_capacity;
    container = malloc(capacity * sizeof(Element));
    allsums = malloc(capacity * sizeof(double));
    r = malloc(m * sizeof(int));
    if (container == NULL||allsums == NULL||r == NULL) {
        printf("Error:not enough memory!\n");
        exit(1);
    }
}
void expand_capacity(int additional_space) {
    capacity += additional_space;
    container = realloc(container, capacity * sizeof(Element));
    allsums = realloc(allsums, capacity * sizeof(double));
    if (container == NULL || allsums == NULL) {
        printf("Error:not enough memory!\n");
        exit(1);
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
void add_or_update_element(int xi, double wi, int m) {
    if (wi <= 0.0) {
        printf("Error:negative weight!\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        if (container[i].x == xi) {
            total_weight -= container[i].weight;
            container[i].weight = wi;
            total_weight += wi;
            update_zhen(m);
            return;
        }
    }
    if (size == capacity) {
        expand_capacity(1000);
    }
    container[size].x = xi;
    container[size].weight = wi;
    size++;
    total_weight += wi;
    update_zhen(m);
}
void remove_element(int xi, int m) {
    for (int i = 0; i < size; i++) {
        if (container[i].x == xi) {
            total_weight -= container[i].weight;
            for (int j = i; j < size - 1; j++) {
                container[j] = container[j + 1];
            }
            size--;
            if (size > 0) {
                update_zhen(m);
            }
            return;
        }
    }
    printf("Element %d not found!\n", xi);
}
int random_select(int m) {
    if (size == 0 || total_weight == 0.0) {
        printf("Error: container is empty!\n");
        return -1;
    }
    double random = (double)rand() / RAND_MAX;
    int j = (int)(m * random);
    if (j >= m) j = m - 1; 
    int i = r[j];
    while (i < size && random > allsums[i]) {
        i++;
    }
    return (i < size) ? container[i].x : -1;
}
void menu(int m) {
    int choice;
    while (1) {
        printf("\n1.Add or update an element\n");
        printf("2. Delete an element\n");
        printf("3. Randomly picked elementа\n");
        printf("4. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int xi;
            double wi;
            printf("Enter element value (xi): ");
            scanf("%d", &xi);
            printf("Enter element weight (wi): ");
            scanf("%lf", &wi);
            add_or_update_element(xi, wi, m);
        } else if (choice == 2) {
            int xi;
            printf("Enter element to delete(xi) для удаления: ");
            scanf("%d", &xi);
            remove_element(xi, m);
        } else if (choice == 3) {
            int result = random_select(m);
            if (result != -1) {
                printf("Randomly picked element: %d\n", result);
            }
        } else if (choice == 4) {
            break;
        } else {
            printf("Error.Try again.\n");
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

    return 0;
}