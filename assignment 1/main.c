#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for BST Node
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* newNode(int value) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = value;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert function (recursive)
struct Node* insert(struct Node* node, int value) {
    if (node == NULL) return newNode(value);

    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);

    return node;
}

// Recursive BST search
struct Node* recursiveSearch(struct Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return recursiveSearch(root->left, key);

    return recursiveSearch(root->right, key);
}

// Iterative BST search
struct Node* iterativeSearch(struct Node* root, int key) {
    while (root != NULL) {
        if (key == root->data)
            return root;
        else if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

// Inorder Traversal (sorted order display)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    int arr[] = {3, 6, 8, 12, 14, 17, 25, 29, 31, 36, 42, 47, 53, 55, 62};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    printf("Inorder traversal of BST (Sorted Order): ");
    inorder(root);
    printf("\n");

    int key;
    printf("Enter element to search: ");
    scanf("%d", &key);

    // Measure recursive search time
    clock_t start = clock();
    struct Node* recResult = recursiveSearch(root, key);
    clock_t end = clock();
    double recTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (recResult != NULL)
        printf("Recursive Search: Element %d found.\n", key);
    else
        printf("Recursive Search: Element %d not found.\n", key);

    // Measure iterative search time
    start = clock();
    struct Node* iterResult = iterativeSearch(root, key);
    end = clock();
    double iterTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (iterResult != NULL)
        printf("Iterative Search: Element %d found.\n", key);
    else
        printf("Iterative Search: Element %d not found.\n", key);

    // Compare performance
    printf("\nPerformance Comparison:\n");
    printf("Recursive Search Time: %f seconds\n", recTime);
    printf("Iterative Search Time: %f seconds\n", iterTime);

    return 0;
}
