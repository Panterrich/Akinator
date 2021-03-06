#ifndef GUARD_H
#define GUARD_H

#include "Stack.h"
//===================================================

#ifdef POINTER_T
    static const int code_t = 4;
    static struct Node* Poison = nullptr;
    static const char* Poison_text = "null";
#endif


//===================================================

#define STACK_ASSERT_OK(a) ;
//===================================================

#define case_of_switch(enum_const) case enum_const: return #enum_const;

//===================================================

enum ERROR 
{
    SIZE_OUT_OF_CAPACITY = 1,
    OUT_OF_MEMORY,
    NEGATIVE_SIZE,
    NEGATIVE_CAPACITY,
    NULL_POINTER_TO_ARRAY,
    ARRAY_AND_STRUCTURE_POINTERS_MATCHED,
    REPEATED_CONSTRUCTION,
    WRONG_SIZE,
    NULL_POP,
    WRONG_CANARY_STRUCT_LEFT,
    WRONG_CANARY_STRUCT_RIGHT,
    WRONG_CANARY_ARRAY_LEFT,
    WRONG_CANARY_ARRAY_RIGHT,
    WRONG_STRUCT_HASH,
    WRONG_STACK_HASH,
    INVALID_PUSH,
    STACK_IS_DESTRUCTED
};

//===================================================

void NULL_check(struct Stack* stk);

int Stack_ERROR(struct Stack* stk);

void Stack_dump(FILE* file, struct Stack* stk);

void Poison_filling(struct Stack* stk, size_t start, size_t end);

const char* Text_ERROR(struct Stack* stk);

void Print_array(FILE*file, struct Stack* stk);

int Comparator_poison(element_t element);

void Placing_canary(struct Stack* stk, void* temp);

unsigned int Struct_stack_HASHFAQ6(struct Stack* stk);

unsigned int Stack_HASHFAQ6(struct Stack* stk);

int Stack_is_destructed(struct Stack* stk);

#endif
