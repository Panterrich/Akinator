#include "Akinator.h"

//=========================================================================================

void Tree_construct(struct Tree* tree)
{
    Tree_null_check(tree);

    tree->size      = 0;
    tree->size      = 0;
    tree->name_base = nullptr;
    tree->root      = nullptr;

    TREE_ASSERT_OK(tree);
}

void Tree_destruct(struct Tree* tree)
{
    Node_destruct(tree->root);

    free(tree->name_base);
    
    tree->root      = nullptr;
    tree->name_base = nullptr;
    tree->size      = 0;
    tree->error     = 0;
}

void Node_destruct(struct Node* current_node)
{
    if (current_node->left  != nullptr) Node_destruct(current_node->left);
    if (current_node->right != nullptr) Node_destruct(current_node->right);

    free(current_node->str);

    current_node->len   = 0;
    current_node->str   = nullptr;
    current_node->left  = nullptr;
    current_node->right = nullptr;
    current_node->prev  = nullptr;
    
    free(current_node);
}

struct Stack* Tree_search(const char* name, struct Tree* tree)
{
    struct Stack* path_element = (struct Stack*) calloc(1, sizeof(struct Stack));
    
    Stack_construct(path_element, 100);

    Node_search(name, tree->root, path_element);
    
    return path_element;
}

int Node_search(const char* name, struct Node* current_node, struct Stack* path_element)
{
    Stack_push(path_element, current_node);

    printf("size: %lu\n", path_element->size);

    if (strcmp(name, current_node->str) == 0) 
    {
        return 1;
    }

    else
    {
        if (current_node->left != nullptr && current_node->right != nullptr)
        {
            if (Node_search(name, current_node->left,  path_element) ||
                Node_search(name, current_node->right, path_element))
            {
                return 1;
            }

            else
            {
                Stack_pop(path_element);
                return 0;
            }
        }

        else if (current_node->left == nullptr && current_node ->right == nullptr)
        {
            Stack_pop(path_element);
            return 0;
        }

        return 0;
    }

}



void Tree_null_check(struct Tree* tree)
{
    if (tree == nullptr)
    {
        FILE* log = fopen("log.txt", "a");

        fprintf(log, "Tree (ERROR NULL PTR) [0x000000] \n");
        fflush(log);

        abort();
    }
}

int Tree_ERROR(struct Tree* tree)
{
    Tree_null_check(tree);

    if (tree->error != 0)
    {
        return tree->error;
    }


    if (tree->size < 0)
    {
        tree->error = NEGATIVE_SIZE;
        return NEGATIVE_SIZE;
    }

    if (tree->root != nullptr)
    {
        size_t count = 0;

        Node_validator(tree, tree->root, &count);

        if (tree->error != 0)
        {
            return tree->error;
        }

        if (tree->size != count)
        {
            tree->error = WRONG_SIZE;
            return WRONG_SIZE;
        }
    }

    return 0;
}

void Node_validator(struct Tree* tree, struct Node* current_node, size_t* count)
{
    ++(*count);

    if (tree->error != 0) return;

    if (current_node->str == nullptr)
    {
        tree->error = TREE_WRONG_STR;
        return;
    }

    if ((current_node->left == nullptr) && (current_node->right != nullptr))
    {
        tree->error = TREE_WRONG_LEFT_NODE;
        return;
    }

    if ((current_node->left != nullptr) && (current_node->right == nullptr))
    {
        tree->error = TREE_WRONG_RIGHT_NODE;
        return;
    }

    if ((current_node->left != nullptr) && (current_node->right != nullptr))
    {
        Node_validator(tree, current_node->left,  count);
        Node_validator(tree, current_node->right, count);
    }
}

void Tree_dump(struct Tree* tree, FILE* log)
{
    Tree_null_check(tree);
    
    const char* code = Tree_text_ERROR(tree);

    fprintf(log, "Tree (ERROR #%d: %s [0x%x] \"%s\" Base: \"%s\" \n"
                  "{\n"
                  "\tsize = %u\n" 
                  "\tdata[0x%x]\n"
                  "}\n\n\n",  
                  tree->error, code, tree, tree->name_tree + 1, tree->name_base, tree->size, tree->root);

    fflush(log);
}

void Tree_graph(struct Tree* tree)
{
    Tree_null_check(tree);

    static size_t number_call = 0;

    ++number_call;

    FILE* text = fopen("images/tree_graph.dot", "w");

    fprintf(text, "digraph G {\n"            
                  "graph [bgcolor = Snow2]\n");

    size_t count = 0;

    Node_graph(tree, tree->root, &count, text);

    fprintf(text, "}\n");

    fclose(text);

    char command[100] = {};

    sprintf(command, "dot -Tjpeg -o images/base_%d.jpeg images/tree_graph.dot", number_call);
    system(command);

    sprintf(command, "gwenview images/base_%d.jpeg", number_call);
    system(command);
}

void Node_graph(struct Tree* tree, struct Node* current_node, size_t* count, FILE* text)
{   
    ++(*count);

    if (current_node->right == nullptr && current_node->left == nullptr)
    {
        fprintf(text, "\t \"%s\" [shape = box, style = filled, color = black, fillcolor = orange]\n", current_node->str);
    }

    else 
    {
        fprintf(text, "\t \"%s\" [shape = box, style = filled, color = black, fillcolor = lightskyblue]\n", current_node->str);
    }

    if (current_node->left != nullptr)
    {
        fprintf(text, "\t \"%s\" -> \"%s\" [label=\"Нет\"]\n", current_node->str, (current_node->left)->str);
    }


    if (current_node->right != nullptr)
    {
        fprintf(text, "\t \"%s\" -> \"%s\" [label=\"Да\"]\n", current_node->str, (current_node->right)->str);
    }

    if (current_node->left  != nullptr) Node_graph(tree, current_node->left,  count, text);
    if (current_node->right != nullptr) Node_graph(tree, current_node->right, count, text);      
}

const char* Tree_text_ERROR(struct Tree* tree)
{   
    switch (tree->error)
    {
        case 0: return "OK";
        
        case_of_switch(TREE_NEGATIVE_SIZE)
        case_of_switch(TREE_WRONG_SIZE)
        case_of_switch(TREE_WRONG_STR)
        case_of_switch(TREE_WRONG_LEFT_NODE)
        case_of_switch(TREE_WRONG_RIGHT_NODE)
        case_of_switch(TREE_NO_SUPPORTED_VERSION_BASE)
        case_of_switch(TREE_NO_SUPPORTED_LANGUAGE)
        case_of_switch(TREE_NO_DATA_IN_BASE)
        case_of_switch(TREE_SYNTAX_ERROR_IN_BASE)
        case_of_switch(TREE_WRONG_NAME_DATA_BASE)

        default: return "Unknown ERROR";
    }
}
