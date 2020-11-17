#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <assert.h>

//============================================================

#include "libr/Onegin.h"
#include "libr/Stack.h"
#include "libr/Guard.h"

//============================================================

const double VERSION  = 1.0;
const char   LANG1[4] = "RUS";
const char   LANG2[4] = "ENG";  


const int MAX_SIZE_STR     = 200;
const int MAX_SIZE_COMMAND = 300;

//============================================================

#define TREE_ASSERT_OK(tree)                                                                         \
    if (Tree_ERROR(tree))                                                                       \
    {                                                                                           \
        FILE *log = fopen("log.txt", "a");                                                      \
        assert(log != nullptr);                                                                 \
                                                                                                \
        fprintf(log, "ERROR: file %s line %d function %s\n", __FILE__, __LINE__, __FUNCTION__); \
        Tree_dump(tree, log);                                                                   \
        fflush(log);                                                                            \
                                                                                                \
        if (tree->root != nullptr)                                                              \
        {                                                                                       \
            Tree_graph(tree);                                                                   \
        }                                                                                       \
                                                                                                \
        abort();                                                                                \
    }

#define TREE_CONSTRUCT(tree)      \
    (tree)->name_tree = #tree;    \
    Tree_construct(tree)

#define case_of_switch(enum_const) \
    case enum_const:               \
        return #enum_const;

//============================================================

struct Node
{
    char* str;
    size_t len;

    struct Node* prev;

    struct Node* left;
    struct Node* right;
};

struct Tree
{
    const char* name_tree;
          char* name_base;

    size_t size;
    struct Node* root;

    int error;
};

//======================================================================

enum TREE_ERROR
{
    TREE_NEGATIVE_SIZE    = 1,

    TREE_WRONG_SIZE       = 2,
    TREE_WRONG_STR        = 3,
    
    TREE_WRONG_LEFT_NODE  = 4,
    TREE_WRONG_RIGHT_NODE = 5,

    TREE_NO_SUPPORTED_VERSION_BASE = 6,
    TREE_NO_SUPPORTED_LANGUAGE     = 7,
    TREE_NO_DATA_IN_BASE           = 8,
    TREE_SYNTAX_ERROR_IN_BASE      = 9,
    TREE_WRONG_NAME_DATA_BASE      = 10,
};

enum KEYS
{
    KEY_1 = 49,   
    KEY_2 = 50,
    KEY_3 = 51,   
    KEY_4 = 52,
    KEY_5 = 53,

    KEY_Y = 89,
    KEY_y = 121,
    KEY_N = 78,
    KEY_n = 110,
};

//======================================================================

int Getkey();

void Screen_clear();

void Menu(const char* name_base);

void Processing_mode(const char* name_base);

void Mod_guessing(const char* name_base);

void Mod_definition(const char* name_base);

void Mod_comparing(const char* name_base);

void Mod_dump(const char* name_base);

int Processing_answer();

void Question(struct Tree* tree, struct Node* current_node);

void Processing_mode_guessing(struct Tree* tree, const char* name_base);

void Guessing(struct Tree* tree, const char* name_base);

void Menu_guessing(struct Tree* tree, const char* name_base);

void Definition(struct Tree* tree, const char* name_base);

void Menu_definition(struct Tree* tree, const char* name_base);

void Processing_mode_definition(struct Tree* tree, const char* name_base);

struct Stack* Tree_search(const char* name, struct Tree* tree);

int Node_search(const char* name, struct Node* current_node, struct Stack* path_element);

void Comparing(struct Tree* tree, const char* name_base);

void Menu_comparing(struct Tree* tree, const char* name_base);

void Processing_mode_comparing(struct Tree* tree, const char* name_base);

void Tree_dump(struct Tree* tree, FILE* log);

void Tree_graph(struct Tree* tree);

void Tree_print(struct Tree* tree);

void Node_graph(struct Tree* tree, struct Node* current_node, size_t* count, FILE* text);

void Tree_create(struct Tree* tree, const char* name_base);

void Node_print(struct Node* current_node, FILE* file);

struct Node* Node_create(struct Tree* tree, struct Node* previos_node, struct Text* base, size_t* number_line);

void Tree_null_check(struct Tree* tree);

int Tree_ERROR(struct Tree* tree);

void Node_validator(struct Tree* tree, struct Node* current_node, size_t* count);

const char* Tree_text_ERROR(struct Tree* tree);

void Tree_construct(struct Tree* tree);

void Tree_destruct(struct Tree* tree);

void Node_destruct(struct Node* current_node);

