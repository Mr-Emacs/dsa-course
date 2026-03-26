#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *lhs;
    struct Node *rhs;
    int val;
} Node;

Node *new_node(int val)
{
    Node *node = malloc(sizeof(*node));
    if (node) {
        node->lhs = node->rhs = NULL;
        node->val = val;
    }
    return node;
}

Node *insert_node(Node *root, int val)
{
    if (!root){
        return new_node(val);
    } else if (val < root->val) {
        root->lhs = insert_node(root->lhs, val);
    } else if (val > root->val) {
        root->rhs = insert_node(root->rhs, val);
    }
    return root;
}

void bt_print(Node *root)
{
    if (!root) return;
    bt_print(root->lhs);
    printf("%d\n", root->val);
    bt_print(root->rhs);
}

int main()
{
    Node *root = NULL;
    root = insert_node(root, 20);
    insert_node(root, 30);
    insert_node(root, 40);
    insert_node(root, 50);

    bt_print(root);
}
