#include <stdio.h>
#include <stdlib.h>

// =============== DATA STRUCTURE DEFINITIONS ===============

// Simple linked list node - contains data and pointer to next node
typedef struct node {
    int data;
    struct node *next;
} node;

// Doubly linked list node - contains data and pointers to both previous and next nodes
typedef struct dnode {
    int data;
    struct dnode *prev;
    struct dnode *next;
} dnode;

// =============== UTILITY FUNCTIONS ===============

/**
 * Clears the input buffer to prevent scanf issues
 * Reads characters until newline or EOF is reached
 */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Safely gets integer input from user with validation
 * prompt - Message to display to user
 * @return The valid integer entered by user
 */
int getIntInput(const char *prompt) {
    int value;
    printf("%s", prompt);
    // Keep asking until valid integer is entered
    while (scanf("%d", &value) != 1) {
        clearInputBuffer();
        printf("Invalid input. Please enter an integer.\n%s", prompt);
    }
    clearInputBuffer();
    return value;
}

// =============== SIMPLE LINKED LIST FUNCTIONS ===============

/**
 * Prints a simple linked list from head to NULL
 * @param list - Pointer to the head of the list
 */
void printSimpleList(node *list) {
    if (list == NULL) {
        printf("\nList is empty\n");
        return;
    }
    node *p = list;
    printf("\nList: ");
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

/**
 * Frees all nodes in a simple linked list
 * @param list - Pointer to the head of the list
 */
void freeSimpleList(node *list) {
    node *temp;
    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
}

/**
 * Searches for a value in a simple linked list
 * @param list - Pointer to the head of the list
 * @param x - Value to search for
 * @return 1 if found, 0 if not found
 */
int searchSimple(node *list, int x) {
    node *p = list;
    while (p != NULL) {
        if (p->data == x)
            return 1;  // Value found
        p = p->next;
    }
    return 0;  // Value not found
}

/**
 * Deletes all occurrences of a value from a simple linked list
 * @param list - Pointer to the head of the list
 * @param x - Value to delete
 * @return New head of the list (may change if head nodes are deleted)
 */
node *deleteOccurrenceSimple(node *list, int x) {
    node *p, *temp;
    
    // Delete all head nodes that match x
    while (list != NULL && list->data == x) {
        temp = list;
        list = list->next;
        free(temp);
    }
    
    // Traverse and delete remaining occurrences
    p = list;
    while (p != NULL && p->next != NULL) {
        if (p->next->data == x) {
            temp = p->next;
            p->next = p->next->next;  // Skip the node
            free(temp);
        } else {
            p = p->next;  // Move to next node only if no deletion
        }
    }
    return list;
}

/**
 * Sorts a simple linked list in ascending order using bubble sort
 * @param list - Pointer to the head of the list
 * @return Pointer to the head of the sorted list
 */
node *sortSimpleList(node *list) {
    if (list == NULL) return NULL;
    node *p, *q;
    int temp;
    
    // Bubble sort: compare and swap data values
    for (p = list; p != NULL; p = p->next) {
        for (q = p->next; q != NULL; q = q->next) {
            if (p->data > q->data) {
                // Swap data values
                temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
    return list;
}

/**
 * Inserts a value into a sorted simple linked list maintaining sort order
 * @param list - Pointer to the head of the sorted list
 * @param x - Value to insert
 * @return New head of the list (may change if inserting before head)
 */
node *insertSortedSimple(node *list, int x) {
    // Allocate memory for new node
    node *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return list;
    }
    newNode->data = x;
    newNode->next = NULL;
    
    // Insert at head if list is empty or x is smallest
    if (list == NULL || x <= list->data) {
        newNode->next = list;
        return newNode;
    }
    
    // Find the correct position to insert
    node *p = list;
    while (p->next != NULL && p->next->data < x) {
        p = p->next;
    }
    
    // Insert the new node
    newNode->next = p->next;
    p->next = newNode;
    return list;
}

/**
 * Creates a simple linked list with n elements
 * @param n - Number of elements to create
 * @return Pointer to the head of the new list
 */
node *createSimpleList(int n) {
    node *list = NULL, *p;
    int value, i;
    
    for (i = 0; i < n; i++) {
        value = getIntInput("Enter value: ");
        p = malloc(sizeof(*p));
        if (p == NULL) {
            printf("Memory allocation failed\n");
            freeSimpleList(list);
            return NULL;
        }
        p->data = value;
        p->next = list;  // Insert at head
        list = p;
    }
    return list;
}

// =============== DOUBLY LINKED LIST FUNCTIONS ===============

/**
 * Prints a doubly linked list showing forward traversal
 * @param list - Pointer to the head of the list
 */
void printDoublyList(dnode *list) {
    if (list == NULL) {
        printf("\nList is empty\n");
        return;
    }
    dnode *p = list;
    printf("\nList (forward): NULL <-> ");
    while (p != NULL) {
        printf("%d <-> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

/**
 * Frees all nodes in a doubly linked list
 * @param list - Pointer to the head of the list
 */
void freeDoublyList(dnode *list) {
    dnode *temp;
    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
}

/**
 * Sorts a doubly linked list in ascending order using bubble sort
 * @param list - Pointer to the head of the list
 * @return Pointer to the head of the sorted list
 */
dnode *sortDoublyList(dnode *list) {
    if (list == NULL) return NULL;
    dnode *p, *q;
    int temp;
    
    // Bubble sort: compare and swap data values
    for (p = list; p != NULL; p = p->next) {
        for (q = p->next; q != NULL; q = q->next) {
            if (p->data > q->data) {
                // Swap data values
                temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
    return list;
}

/**
 * Inserts a value into a sorted doubly linked list maintaining sort order
 * @param list - Pointer to the head of the sorted list
 * @param x - Value to insert
 * @return New head of the list (may change if inserting before head)
 */
dnode *insertSortedDoubly(dnode *list, int x) {
    // Allocate memory for new node
    dnode *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return list;
    }
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = NULL;
    
    // Insert at head if list is empty or x is smallest
    if (list == NULL || x <= list->data) {
        newNode->next = list;
        if (list != NULL)
            list->prev = newNode;
        return newNode;
    }
    
    // Find the correct position to insert
    dnode *p = list;
    while (p->next != NULL && p->next->data < x) {
        p = p->next;
    }
    
    // Insert the new node and update all pointers
    newNode->next = p->next;
    if (p->next != NULL)
        p->next->prev = newNode;
    p->next = newNode;
    newNode->prev = p;
    return list;
}

/**
 * Creates a doubly linked list with n elements
 * @param n - Number of elements to create
 * @return Pointer to the head of the new list
 */
dnode *createDoublyList(int n) {
    dnode *list = NULL, *p;
    int value, i;
    
    for (i = 0; i < n; i++) {
        value = getIntInput("Enter value: ");
        p = malloc(sizeof(*p));
        if (p == NULL) {
            printf("Memory allocation failed\n");
            freeDoublyList(list);
            return NULL;
        }
        p->data = value;
        p->next = list;
        p->prev = NULL;
        if (list != NULL)
            list->prev = p;  // Update previous head's prev pointer
        list = p;
    }
    return list;
}

// =============== SIMPLE CIRCULAR LINKED LIST FUNCTIONS ===============

/**
 * Prints a simple circular linked list
 * Uses do-while to avoid infinite loop and show circular nature
 * @param list - Pointer to the head of the circular list
 */
void printCircularSimple(node *list) {
    if (list == NULL) {
        printf("\nList is empty\n");
        return;
    }
    node *p = list;
    printf("\nCircular List: ");
    do {
        printf("%d -> ", p->data);
        p = p->next;
    } while (p != list);  // Stop when we circle back to head
    printf("(back to %d)\n", list->data);
}

/**
 * Frees all nodes in a simple circular linked list
 * @param list - Pointer to the head of the circular list
 */
void freeCircularSimple(node *list) {
    if (list == NULL) return;
    
    // Break the circle first
    node *p = list->next;
    node *temp;
    while (p != list) {
        temp = p;
        p = p->next;
        free(temp);
    }
    free(list);  // Free the head node
}

/**
 * Inserts a value at the head of a simple circular linked list
 * @param list - Pointer to the current head
 * @param x - Value to insert
 * @return Pointer to the new head
 */
node *insertHeadCircular(node *list, int x) {
    node *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return list;
    }
    newNode->data = x;
    
    // If list is empty, create single-node circular list
    if (list == NULL) {
        newNode->next = newNode;
        return newNode;
    }
    
    // Find the last node (points to current head)
    node *p = list;
    while (p->next != list) {
        p = p->next;
    }
    
    // Insert new node at head
    newNode->next = list;
    p->next = newNode;  // Last node now points to new head
    return newNode;
}

/**
 * Inserts a value at the tail of a simple circular linked list
 * @param list - Pointer to the head
 * @param x - Value to insert
 * @return Pointer to the head (unchanged)
 */
node *insertTailCircular(node *list, int x) {
    node *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return list;
    }
    newNode->data = x;
    
    // If list is empty, create single-node circular list
    if (list == NULL) {
        newNode->next = newNode;
        return newNode;
    }
    
    // Find the last node
    node *p = list;
    while (p->next != list) {
        p = p->next;
    }
    
    // Insert new node at tail
    p->next = newNode;
    newNode->next = list;  // New tail points to head
    return list;
}

/**
 * Creates a simple circular linked list with n elements
 * @param n - Number of elements to create
 * @return Pointer to the head of the new circular list
 */
node *createCircularSimple(int n) {
    node *list = NULL, *p, *tail = NULL;
    int value, i;
    
    for (i = 0; i < n; i++) {
        value = getIntInput("Enter value: ");
        p = malloc(sizeof(*p));
        if (p == NULL) {
            printf("Memory allocation failed\n");
            freeCircularSimple(list);
            return NULL;
        }
        p->data = value;
        
        if (list == NULL) {
            // First node: points to itself
            list = p;
            tail = p;
            p->next = list;
        } else {
            // Subsequent nodes: maintain circular structure
            tail->next = p;
            p->next = list;  // New node points back to head
            tail = p;
        }
    }
    return list;
}

// =============== DOUBLY CIRCULAR LINKED LIST FUNCTIONS ===============

/**
 * Prints a doubly circular linked list
 * Uses do-while to avoid infinite loop and show circular nature
 * @param list - Pointer to the head of the doubly circular list
 */
void printCircularDoubly(dnode *list) {
    if (list == NULL) {
        printf("\nList is empty\n");
        return;
    }
    dnode *p = list;
    printf("\nDoubly Circular List: ");
    do {
        printf("%d <-> ", p->data);
        p = p->next;
    } while (p != list);  // Stop when we circle back to head
    printf("(back to %d)\n", list->data);
}

/**
 * Frees all nodes in a doubly circular linked list
 * @param list - Pointer to the head of the doubly circular list
 */
void freeCircularDoubly(dnode *list) {
    if (list == NULL) return;
    
    // Break the circle first
    dnode *p = list->next;
    dnode *temp;
    while (p != list) {
        temp = p;
        p = p->next;
        free(temp);
    }
    free(list);  // Free the head node
}

/**
 * Inserts a value at the head of a doubly circular linked list
 * @param list - Pointer to the current head
 * @param x - Value to insert
 * @return Pointer to the new head
 */
dnode *insertHeadCircularDoubly(dnode *list, int x) {
    dnode *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return list;
    }
    newNode->data = x;
    
    // If list is empty, create single-node doubly circular list
    if (list == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        return newNode;
    }
    
    // Get tail (which is list->prev in doubly circular)
    dnode *tail = list->prev;
    
    // Insert new node at head with all pointers updated
    newNode->next = list;
    newNode->prev = tail;
    tail->next = newNode;
    list->prev = newNode;
    return newNode;  // Return new head
}

/**
 * Inserts a value at the tail of a doubly circular linked list
 * @param list - Pointer to the head
 * @param x - Value to insert
 * @return Pointer to the head (unchanged)
 */
dnode *insertTailCircularDoubly(dnode *list, int x) {
    dnode *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return list;
    }
    newNode->data = x;
    
    // If list is empty, create single-node doubly circular list
    if (list == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        return newNode;
    }
    
    // Get tail (which is list->prev in doubly circular)
    dnode *tail = list->prev;
    
    // Insert new node at tail with all pointers updated
    newNode->next = list;
    newNode->prev = tail;
    tail->next = newNode;
    list->prev = newNode;
    return list;  // Head remains unchanged
}

/**
 * Creates a doubly circular linked list with n elements
 * @param n - Number of elements to create
 * @return Pointer to the head of the new doubly circular list
 */
dnode *createCircularDoubly(int n) {
    dnode *list = NULL, *p, *tail = NULL;
    int value, i;
    
    for (i = 0; i < n; i++) {
        value = getIntInput("Enter value: ");
        p = malloc(sizeof(*p));
        if (p == NULL) {
            printf("Memory allocation failed\n");
            freeCircularDoubly(list);
            return NULL;
        }
        p->data = value;
        
        if (list == NULL) {
            // First node: points to itself in both directions
            list = p;
            tail = p;
            p->next = list;
            p->prev = list;
        } else {
            // Subsequent nodes: maintain doubly circular structure
            p->prev = tail;
            p->next = list;
            tail->next = p;
            list->prev = p;  // Head's prev always points to new tail
            tail = p;
        }
    }
    return list;
}

// =============== MAIN FUNCTION ===============

int main() {
    int listType, operation, n, value;
    node *simpleList = NULL;
    dnode *doublyList = NULL;
    node *circularSimple = NULL;
    dnode *circularDoubly = NULL;
    
    // Display main menu
    printf("=== LINKED LIST MANAGER ===\n");
    printf("Which kind of list do you want to manipulate?\n");
    printf("1. Simple Linked List\n");
    printf("2. Doubly Linked List\n");
    printf("3. Simple Circular Linked List\n");
    printf("4. Doubly Circular Linked List\n");
    
    listType = getIntInput("Enter your choice (1-4): ");
    
    // Validate list type choice
    if (listType < 1 || listType > 4) {
        printf("Invalid choice!\n");
        return 1;
    }
    
    // Get number of elements and create the list
    n = getIntInput("\nEnter the number of elements in the list: ");
    if (n <= 0) {
        printf("Invalid number of elements!\n");
        return 1;
    }
    
    printf("\n");
    // Create and display the selected list type
    switch (listType) {
        case 1:
            simpleList = createSimpleList(n);
            if (simpleList == NULL) return 1;
            printSimpleList(simpleList);
            break;
        case 2:
            doublyList = createDoublyList(n);
            if (doublyList == NULL) return 1;
            printDoublyList(doublyList);
            break;
        case 3:
            circularSimple = createCircularSimple(n);
            if (circularSimple == NULL) return 1;
            printCircularSimple(circularSimple);
            break;
        case 4:
            circularDoubly = createCircularDoubly(n);
            if (circularDoubly == NULL) return 1;
            printCircularDoubly(circularDoubly);
            break;
    }
    
    // Display operations menu based on list type
    printf("\n=== AVAILABLE OPERATIONS ===\n");
    
    // SIMPLE LINKED LIST OPERATIONS
    if (listType == 1) {
        printf("1. Read an element and delete all its occurrences\n");
        printf("2. Insert an element in sorted order\n");
        
        operation = getIntInput("Enter your choice (1-2): ");
        
        if (operation == 1) {
            // Search and delete operation
            value = getIntInput("\nEnter a value to search and delete: ");
            if (searchSimple(simpleList, value)) {
                printf("%d found in the list.\n", value);
                simpleList = deleteOccurrenceSimple(simpleList, value);
                printf("All occurrences of %d deleted.\n", value);
            } else {
                printf("%d not found in the list.\n", value);
            }
            printf("Final list: ");
            printSimpleList(simpleList);
        } else if (operation == 2) {
            // Sorted insertion operation
            printf("\nSorting the list first...\n");
            simpleList = sortSimpleList(simpleList);
            printSimpleList(simpleList);
            value = getIntInput("\nEnter a value to insert in sorted order: ");
            simpleList = insertSortedSimple(simpleList, value);
            printf("After insertion: ");
            printSimpleList(simpleList);
        } else {
            printf("Invalid operation!\n");
        }
        freeSimpleList(simpleList);
        
    // DOUBLY LINKED LIST OPERATIONS
    } else if (listType == 2) {
        printf("1. Insert an element in sorted order\n");
        
        operation = getIntInput("Enter your choice (1): ");
        
        if (operation == 1) {
            // Sorted insertion operation
            printf("\nSorting the list first...\n");
            doublyList = sortDoublyList(doublyList);
            printDoublyList(doublyList);
            value = getIntInput("\nEnter a value to insert in sorted order: ");
            doublyList = insertSortedDoubly(doublyList, value);
            printf("After insertion: ");
            printDoublyList(doublyList);
        } else {
            printf("Invalid operation!\n");
        }
        freeDoublyList(doublyList);
        
    // SIMPLE CIRCULAR LINKED LIST OPERATIONS
    } else if (listType == 3) {
        printf("1. Insert at head\n");
        printf("2. Insert at tail\n");
        
        operation = getIntInput("Enter your choice (1-2): ");
        value = getIntInput("Enter value to insert: ");
        
        if (operation == 1) {
            // Insert at head
            circularSimple = insertHeadCircular(circularSimple, value);
            printf("Inserted at head.\n");
        } else if (operation == 2) {
            // Insert at tail
            circularSimple = insertTailCircular(circularSimple, value);
            printf("Inserted at tail.\n");
        } else {
            printf("Invalid operation!\n");
        }
        printCircularSimple(circularSimple);
        freeCircularSimple(circularSimple);
        
    // DOUBLY CIRCULAR LINKED LIST OPERATIONS
    } else if (listType == 4) {
        printf("1. Insert at head\n");
        printf("2. Insert at tail\n");
        
        operation = getIntInput("Enter your choice (1-2): ");
        value = getIntInput("Enter value to insert: ");
        
        if (operation == 1) {
            // Insert at head
            circularDoubly = insertHeadCircularDoubly(circularDoubly, value);
            printf("Inserted at head.\n");
        } else if (operation == 2) {
            // Insert at tail
            circularDoubly = insertTailCircularDoubly(circularDoubly, value);
            printf("Inserted at tail.\n");
        } else {
            printf("Invalid operation!\n");
        }
        printCircularDoubly(circularDoubly);
        freeCircularDoubly(circularDoubly);
    }
    
    printf("\nProgram terminated successfully.\n");
    return 0;
}