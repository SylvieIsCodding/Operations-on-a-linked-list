# Linked List Manager in C

A C program to create and manipulate different types of linked lists, including:
- **Simple (singly) linked list**
- **Doubly linked list**
- **Simple circular linked list**
- **Doubly circular linked list**

It supports operations such as insertion, deletion, searching, sorting, and printing lists.

## Features

- Create any type of linked list dynamically.
- Insert elements at head, tail, or in sorted order.
- Delete all occurrences of a specific value (singly linked list).
- Sort lists in ascending order.
- Print lists in linear or circular format.
- Handles user input validation and memory allocation safely.

## Usage

**1. Compile the program:**
```bash
gcc linked_list_manager.c -o linked_list_manager
```

**2. Run the executable:**
```bash
./linked_list_manager
```

**3. Follow the prompts:**
- Choose the type of list (1–4)
- Enter the number of elements
- Input the list elements
- Select operations (insert, delete, search, sort)
- View the resulting list

## Example Run

```
=== LINKED LIST MANAGER ===
Which kind of list do you want to manipulate?
1. Simple Linked List
2. Doubly Linked List
3. Simple Circular Linked List
4. Doubly Circular Linked List
Enter your choice (1-4): 1

Enter the number of elements in the list: 5
Enter value: 10
Enter value: 5
Enter value: 20
Enter value: 5
Enter value: 15

List: 15 -> 5 -> 20 -> 5 -> 10 -> NULL

=== AVAILABLE OPERATIONS ===
1. Read an element and delete all its occurrences
2. Insert an element in sorted order
Enter your choice (1-2): 1

Enter a value to search and delete: 5
5 found in the list.
All occurrences of 5 deleted.
Final list: 15 -> 20 -> 10 -> NULL
```

## Supported Operations

### Singly Linked List
- Delete all occurrences of a value
- Insert a value in sorted order
- Search for a value
- Sort list in ascending order

### Doubly Linked List
- Insert a value in sorted order
- Sort list in ascending order

### Circular Lists (Simple & Doubly)
- Insert at head
- Insert at tail
- Print circularly

## Time & Space Complexity

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Search | O(n) | O(1) |
| Insert in sorted order | O(n) | O(1) |
| Delete occurrences | O(n) | O(1) |
| Sort | O(n²) | O(1) |
| Create list | O(n) | O(n) |

*n = number of nodes in the list*

## Notes

- Input validation ensures safe entries.
- Handles memory allocation errors gracefully.
- Circular lists maintain proper links to avoid segmentation faults.
- Useful for learning and understanding linked list operations in C.
