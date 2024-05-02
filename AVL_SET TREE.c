#include <stdio.h>
#include <stdlib.h>

struct node {
    char key;
    struct node *left;
    struct node *right;
    int height;
};

struct node* insert(struct node*, char);
struct node* delete(struct node*, char);
struct node* minvalnode(struct node*);
void emplace(struct node*, char);
struct node* find(struct node*, char);
struct node* begin(struct node*);
struct node* end(struct node*);
struct node* left_rotate(struct node*);
struct node* right_rotate(struct node*);
struct node* union_set(struct node*, struct node*); 
int empty(struct node*);
void clear(struct node*);

int empty(struct node* root) {
    if (root == NULL)
        return printf("\n\t\tset is empty...\n");
    else
        return printf("\n\t\tset is not empty...\n");
}

struct node* newnode(char key) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->key = key;
    newnode->left = newnode->right = NULL;

    return newnode;
}

int main() {
    int choice = 1;
    char c;
    struct node* root1 = NULL;
    struct node* root2 = NULL;
    while (choice != 0) {
        printf("\n1.Insert into Set 1:\n");
        printf("2.Insert into Set 2:\n");
        printf("3.Delete from Set 1:\n");
        printf("4.Delete from Set 2:\n");
        printf("5.Emplace into Set 1:\n");
        printf("6.Emplace into Set 2:\n");
        printf("7.Find  \n");
        printf("8.Check if Set 1 is empty:\n");
        printf("9.Check if Set 2 is empty:\n");
        printf("10.Display Set 1 (Inorder):\n");
        printf("11.Display Set 2 (Inorder):\n");
        printf("12.Begin \n");
        printf("13.End  \n");
        printf("14.clear  \n");
        printf("15.Perform Union and Display (Inorder):\n");
        printf("16.Perform Union and Display (Preorder):\n");
        printf("17.Perform Union and Display (Postorder):\n");
        printf("0.Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            char n;
        case 1:
            printf("Enter the character to insert into Set 1: ");
            scanf(" %c", &c);
            root1 = insert(root1, c);
            printf("The character %c is inserted into Set 1\n", c);
            break;
        case 2:
            printf("Enter the character to insert into Set 2: ");
            scanf(" %c", &c);
            root2 = insert(root2, c);
            printf("The character %c is inserted into Set 2\n", c);
            break;
        case 3:
            printf("Enter the character to delete from Set 1: ");
            scanf(" %c", &c);
            root1 = delete(root1, c);
            printf("The character %c is deleted from Set 1\n", c);
            display_inorder(root1);
            break;
        case 4:
            printf("Enter the character to delete from Set 2: ");
            scanf(" %c", &c);
            root2 = delete(root2, c);
            printf("The character %c is deleted from Set 2\n", c);
            display_inorder(root2);
            break;
        case 5:
            printf("Enter the character to emplace into Set 1: ");
            scanf(" %c", &c);
            emplace(root1, c);
            break;
        case 6:
            printf("Enter the character to emplace into Set 2: ");
            scanf(" %c", &c);
            emplace(root2, c);
            break;
        case 7:
    printf("Enter the key to be searched: ");
    scanf(" %c", &n);
    if (find(root1, n) != NULL)
        printf("Key '%c' is found in Set 1\n", n);
    else
        printf("Key '%c' is not found in Set 1\n", n);

    if (find(root2, n) != NULL)
        printf("Key '%c' is found in Set 2\n", n);
    else
        printf("Key '%c' is not found in Set 2\n", n);
    break;
        case 8:
            empty(root1);
            break;
        case 9:
            empty(root2);
            break;
        case 10:
    
            display_inorder(root1);
            
            break;
        case 11:
    
            display_inorder(root2);
            
            break;
        case 12:
             printf("First elment of set-1 is %c\n",(begin(root1)->key));
             printf("First elment of set-2 is %c\n",(begin(root2)->key));
             
            break;
        case 13:
             
            printf("last elment of set-1 is %c\n",(end(root1)->key));
            printf("last elment of set-2 is %c\n",(end(root2)->key));
             
            break;
        case 14:
            clear(root1);
            clear(root2);
            printf("\nALL elements in set-1 and set-2 are cleared .\n");
            break;  
        
        case 15:
            printf("Union of Set 1 and Set 2: ");
            display_inorder(union_set(root1, root2)); 
            break;

        case 16:
            printf("Union of Set 1 and Set 2 (Preorder): ");
            display_preorder(union_set(root1, root2)); 
            break;
        case 17:
            printf("Union of Set 1 and Set 2 (Postorder): ");
            display_postorder(union_set(root1, root2)); 
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}


int max(int a, int b) {
    return a > b ? a : b;
}

int height(struct node* newnode) {
    if (newnode == NULL)
        return 0;

    return newnode->height = 1;
}

int balancing_factor(struct node* newnode) {
    if (newnode == NULL) {
        return 0;
    }

    return height(newnode->left) - height(newnode->right);
}

struct node* left_rotate(struct node* temp2) {
    struct node* temp1 = temp2->right;
    struct node* n = temp1->left;

    temp1->left = temp2;
    temp2->right = n;

    return temp1;
}

struct node* right_rotate(struct node* temp1) {
    struct node* temp2 = temp1->left;
    struct node* n = temp2->right;

    temp2->right = temp1;
    temp1->left = n;

    return temp2;
}

void clear(struct node* root) {
    if (root != NULL) {
        clear(root->left);
        clear(root->right);
        free(root);
    }
}

struct node* insert(struct node* root, char key) {
    if (root == NULL)
        return newnode(key);

    if (key < root->key)
            root->left = insert(root->left, key);
        else if (key > root->key)
            root->right = insert(root->right, key);
            

    root->height = max(height(root->left), height(root->right)) + 1;
    int bf = balancing_factor(root);

    if (bf > 1 && key < root->left->key)
        return right_rotate(root);

    if (bf < -1 && key > root->right->key)
        return left_rotate(root);

    if (bf > 1 && key > root->left->key) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (bf < -1 && key < root->right->key) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

struct node* find(struct node* root, char key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return find(root->left, key);

    if (key > root->key)
        return find(root->right, key);
}

void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf(" %c ", root->key);
        inorder(root->right);
    }
}

struct node* delete(struct node* root, char key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = delete(root->left, key);
    else if (key > root->key)
        root->right = delete(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            struct node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            struct node* temp = minvalnode(root->right);
            root->key = temp->key;
            root->right = delete(root->right, temp->key);
        }
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int bf = balancing_factor(root);

    if (bf > 1 && balancing_factor(root->left) >= 0)
        return left_rotate(root);

    if (bf < -1 && balancing_factor(root->right) <= 0)
        return right_rotate(root);

    if (bf > 1 && balancing_factor(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (bf < -1 && balancing_factor(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

void emplace(struct node* root, char key) {
    struct node* node = find(root, key);
    if (node == NULL) {
        root = insert(root, key); 
    } else {
        printf("The character %c is already present in the set.\n", key);
    }
}

struct node* begin(struct node* root) {
    struct node* temp = root;
    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}

struct node* end(struct node* root) {
    struct node* temp = root;
    while (temp->right != NULL)
        temp = temp->right;

    return temp;
}

struct node* minvalnode(struct node* root) {
    struct node* temp = root;
    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}


void display_inorder(struct node* root) {
    printf("Inorder Traversal of set: ");
    printf("{");
    inorder(root);
    printf("}");
    printf("\n");
}

struct node* union_set(struct node* root1, struct node* root2) {
    
    if (root2 == NULL)
        return root1;

    root1 = insert(root1, root2->key); 
    root1 = union_set(root1, root2->left);
    root1 = union_set(root1, root2->right);

   return root1;
}
