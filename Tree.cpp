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

void Node_fill(struct Node* node, char* string, size_t length, struct Node* previous_node, struct Node* left_node, struct Node* right_node)
{
    node->str   = string;
    node->len   = length;
    node->prev  = previous_node;
    node->left  = left_node;
    node->right = right_node;
}

void Tree_destruct(struct Tree* tree)
{
    Tree_null_check(tree);

    Node_destruct(tree->root);

    free(tree->name_base);
    
    tree->root      = nullptr;
    tree->name_base = nullptr;
    tree->size      = 0;
    tree->error     = 0;
}

void Node_destruct(struct Node* current_node)
{   
    assert(current_node != nullptr);

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
    Tree_null_check(tree);
    assert(name != nullptr);

    struct Stack* path_element = (struct Stack*) calloc(1, sizeof(struct Stack));
    
    Stack_construct(path_element, 100);

    Node_search(name, tree->root, path_element);
    
    return path_element;
}

int Node_search(const char* name, struct Node* current_node, struct Stack* path_element)
{
    assert(name         != nullptr);
    assert(current_node != nullptr);
    assert(path_element != nullptr);

    Stack_push(path_element, current_node);

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

void Tree_create(struct Tree* tree, const char* name_base)
{
    Tree_null_check(tree);
    assert(name_base != nullptr);

    char command[MAX_SIZE_COMMAND] = {};
    sprintf(command, "iconv -f WINDOWS-1251 -t UTF-8 %s -o test.txt && mv test.txt %s", name_base, name_base);
    system(command);

    FILE* text = fopen(name_base, "rb");

    if (text == nullptr)
    {
        tree->error = TREE_WRONG_NAME_DATA_BASE;
        TREE_ASSERT_OK(tree);
    }

    struct Text base = {};
    Create_text(text, &base);

    fclose(text);

    tree->name_base = (char*) calloc(base.lines[0].len, sizeof(char));
    sscanf(base.lines[0].str, "{ %s }", tree->name_base);

    double version_base = 0;
    sscanf(base.lines[1].str, "{ Version %lf }", &version_base);

    if (version_base != VERSION)
    {
        tree->error = TREE_NO_SUPPORTED_VERSION_BASE;
        TREE_ASSERT_OK(tree);
    }

    char* lang = (char*) calloc(base.lines[2].len, sizeof(char));
    sscanf(base.lines[2].str, "{ %s }", lang);


    if (strcmp(LANG1, lang) != 0 && strcmp(LANG2, lang) != 0)
    {
        tree->error = TREE_NO_SUPPORTED_LANGUAGE;
        TREE_ASSERT_OK(tree);
    }

    free(lang);

    char   first_bracket = 0;
    size_t number_line   = 2;

    while (first_bracket != '[')
    {   
        ++number_line;
        sscanf(base.lines[number_line].str, " %c", &first_bracket);

        if (number_line == base.n_lines)
        {
            tree->error = TREE_NO_DATA_IN_BASE;
            TREE_ASSERT_OK(tree);
        }
    }

    if (tree->root != nullptr)
    {
        Tree_destruct(tree);
    }

    tree->root = Node_create(tree, nullptr, &base, &number_line);

    Free_memory(&base);

    sprintf(command, "iconv --from-code=UTF-8 --to-code=WINDOWS-1251 %s.txt -o %s.txt", tree->name_base, tree->name_base);
    system(command);
}

struct Node* Node_create(struct Tree* tree, struct Node* previos_node, struct Text* base, size_t* number_line)
{
    Tree_null_check(tree);
    assert(base         != nullptr);
    assert(number_line  != nullptr);
    TREE_ASSERT_OK(tree);

    struct Node* current_node = (struct Node*) calloc(1, sizeof(struct Node));

    ++(tree->size);

    if (strchr((base->lines)[*number_line].str, '[') == nullptr)
    {
        tree->error = TREE_SYNTAX_ERROR_IN_BASE;
        TREE_ASSERT_OK(tree);
    }

    char* pointer_begin = strchr((base->lines)[(*number_line) + 1].str, '?');

    if (pointer_begin != nullptr)
    {
        char* pointer_end = strchr(pointer_begin + 1, '?');

        if (pointer_end == nullptr)
        {
            tree->error = TREE_SYNTAX_ERROR_IN_BASE;
            TREE_ASSERT_OK(tree);
        }

        *pointer_end = '\0';

        current_node->len = pointer_end - pointer_begin;
        current_node->str = (char*) calloc(current_node->len, sizeof(char));

        strcpy(current_node->str, pointer_begin + 1);

        current_node->prev = previos_node;

        *number_line += 2;

        current_node->right = Node_create(tree, current_node, base, number_line);
        current_node->left  = Node_create(tree, current_node, base, number_line);  
    }

    else 
    {   
        pointer_begin = strchr((base->lines)[*number_line + 1].str, '`');

        if (pointer_begin != nullptr)
        {
            char* pointer_end = strchr(pointer_begin + 1, '`');

            *pointer_end = '\0';

            current_node->len = pointer_end - pointer_begin;
            current_node->str = (char*) calloc(current_node->len, sizeof(char));
            strcpy(current_node->str, pointer_begin + 1);

            current_node->prev = previos_node;

            *number_line += 2;

            current_node->right = nullptr;
            current_node->left  = nullptr;
        }
    }

    pointer_begin = strchr((base->lines)[*number_line].str, ']');

    if (pointer_begin == nullptr)
    {
       tree->error == TREE_SYNTAX_ERROR_IN_BASE;
       TREE_ASSERT_OK(tree);
    }

    ++(*number_line);
    return current_node;
}

void Tree_print(struct Tree* tree)
{
    Tree_null_check(tree);
    TREE_ASSERT_OK(tree);

    char name_output[MAX_SIZE_COMMAND] = {};
    sprintf(name_output, "%s.txt", tree->name_base);

    FILE* file = fopen(name_output, "w");

    fprintf(file, "{ %s }\n"
                  "{ Version %.1lg }\n"
                  "{ RUS }\n\n",
                   tree->name_base, VERSION);
    
    Node_print(tree->root, file);

    fclose(file);

    char command[MAX_SIZE_COMMAND] = {};
    sprintf(command, "astyle --mode=cs --style=ansi %s", name_output);
    system(command);

    sprintf(command, "iconv --from-code=UTF-8 --to-code=WINDOWS-1251 %s.txt -o %s.txt", tree->name_base, tree->name_base);
    system(command);
}

void Node_print(struct Node* current_node, FILE* file)
{
    assert(file != nullptr);

    if (current_node == nullptr) return;

    fprintf(file, "[\n");

    if (current_node->left != nullptr && current_node->right != nullptr)
    {
        fprintf(file, "?%s?\n", current_node->str);
    }

    else if (current_node->left == nullptr && current_node->right == nullptr)
    {
        fprintf(file, "`%s`\n", current_node->str);
    }

    if (current_node->right != nullptr) Node_print(current_node->right, file);
    if (current_node->left  != nullptr) Node_print(current_node->left,  file);

    fprintf(file, "]\n");
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

    fprintf(text, "\tlabelloc=\"t\";"
                  "\tlabel=\"Akinator base: %s \";"
                  "}\n", tree->name_base);

    fclose(text);

    char command[100] = {};

    sprintf(command, "dot -Tjpeg -o images/base_%d.jpeg images/tree_graph.dot", number_call);
    system(command);

    sprintf(command, "gwenview images/base_%d.jpeg", number_call);
    system(command);
}

void Node_graph(struct Tree* tree, struct Node* current_node, size_t* count, FILE* text)
{   
    if (*count > tree->size) return;

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
    Tree_null_check(tree);

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
