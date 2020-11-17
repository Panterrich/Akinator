#include "Guard.h"
//===================================================

void NULL_check(struct Stack* stk)
{
    if (stk == nullptr)
    {
        FILE* log = fopen("log.txt", "a");

        fprintf(log, "Stack (ERROR NULL PTR) [0x000000]\n");
        fflush(log);

        abort();
    }
}

int Stack_ERROR(struct Stack* stk)
{
    if (stk->error != 0)
    {
        return stk->error;
    }

    else 
    {   
        if ((stk->size >= stk->capacity) && (stk->capacity != 0))
        {
        stk->error = SIZE_OUT_OF_CAPACITY;
        return SIZE_OUT_OF_CAPACITY;
        }

        if (stk->size < 0)
        {
            stk->error = NEGATIVE_SIZE;
            return NEGATIVE_SIZE;
        }

        if (stk->capacity < 0)
        {
            stk->error = NEGATIVE_CAPACITY;
            return NEGATIVE_CAPACITY;
        }

        if (stk->canary_struct_left != Canary)
        {
            stk->error = WRONG_CANARY_STRUCT_LEFT;
            return WRONG_CANARY_STRUCT_LEFT;
        }

        if (stk->canary_struct_right != Canary)
        {
            stk->error = WRONG_CANARY_STRUCT_RIGHT;
            return WRONG_CANARY_STRUCT_RIGHT;
        }
        
        if ((stk->capacity != 0) && (stk->data == nullptr))
        {
            stk->error = NULL_POINTER_TO_ARRAY;
            return NULL_POINTER_TO_ARRAY;
        }

        if ((stk->capacity != 0) && (stk->data != nullptr))
        {

            if (stk->data == (element_t*) stk)
            {
                stk->error = ARRAY_AND_STRUCTURE_POINTERS_MATCHED;
                return ARRAY_AND_STRUCTURE_POINTERS_MATCHED;
            }

            if ((stk->size <= (stk->capacity - 1)) && (stk->size > 0))
            {
                if (!(Comparator_poison(stk->data[stk->size]) && !Comparator_poison(stk->data[stk->size - 1])))
                {
                    stk->error = WRONG_SIZE;
                    return WRONG_SIZE;
                }
            }

            else if (stk->size == 0)
            {
                if (!Comparator_poison(stk->data[stk->size]))
                {
                    stk->error = WRONG_SIZE;
                    return WRONG_SIZE;
                }
            }

            if (((canary_t*)(stk->data))[-1] != Canary)
            {
                stk->error = WRONG_CANARY_ARRAY_LEFT;
                return WRONG_CANARY_ARRAY_LEFT;
            }

            if (*((canary_t*)&((stk->data)[stk->capacity])) != Canary)
            {
                stk->error = WRONG_CANARY_ARRAY_RIGHT;
                return WRONG_CANARY_ARRAY_RIGHT;
            }
        }

        return 0;
    }
}

void Stack_dump(FILE* file, struct Stack* stk)
{
    NULL_check(stk);

    const char* code = Text_ERROR(stk);

    fprintf(file, "Stack (ERROR #%d: %s [0x%x] \"%s\" \n", stk->error, code, stk, (stk->name + 1));
    fprintf(file, "{\n");
    fprintf(file, "\tsize = %u\n",      stk->size);
    fprintf(file, "\tcapacity = %u\n",  stk->capacity);
    fprintf(file, "\tdata[0x%x]\n",     stk->data);
    fprintf(file, "\t{\n");

    if ((stk->data != nullptr) && (stk->error != NEGATIVE_CAPACITY)) 
    {
        Print_array(file, stk);
    }
    
    fprintf(file, "\t}\n");
    fprintf(file, "}\n\n\n");

    fflush(file);
}

void Poison_filling(struct Stack* stk, size_t start, size_t end)
{
    for (size_t i = start; i < end; ++i)
    {
        stk->data[i] = Poison;
    }
}

const char* Text_ERROR(struct Stack* stk)
{
    switch (stk->error)
    {
    case 0: return "OK";
    case_of_switch(SIZE_OUT_OF_CAPACITY)
    case_of_switch(OUT_OF_MEMORY)
    case_of_switch(NEGATIVE_SIZE)
    case_of_switch(NEGATIVE_CAPACITY)
    case_of_switch(NULL_POINTER_TO_ARRAY)
    case_of_switch(ARRAY_AND_STRUCTURE_POINTERS_MATCHED)
    case_of_switch(REPEATED_CONSTRUCTION)
    case_of_switch(WRONG_SIZE)
    case_of_switch(NULL_POP)
    case_of_switch(WRONG_CANARY_STRUCT_LEFT)
    case_of_switch(WRONG_CANARY_STRUCT_RIGHT)
    case_of_switch(WRONG_CANARY_ARRAY_LEFT)
    case_of_switch(WRONG_CANARY_ARRAY_RIGHT)
    case_of_switch(WRONG_STRUCT_HASH)
    case_of_switch(WRONG_STACK_HASH)
    case_of_switch(INVALID_PUSH)
    case_of_switch(STACK_IS_DESTRUCTED)
    default: return "Unknown ERROR";
    }
}

void Print_array(FILE*file, struct Stack* stk)
{
    switch (code_t)
    {    
    case 4:
        for (int i = 0; i <= stk->size; ++i)
        {
            if (stk->data[i] == nullptr)
                fprintf(file, "\t\t*[%d] = \\0 (Poison!)\n", i);
            else
                fprintf(file, "\t\t*[%d] = %x\n", i, stk->data[i]);
        }

        for (int i = stk->size + 1; i < stk->capacity; ++i)
        {
            if (stk->data[i] == nullptr) 
                fprintf(file, "\t\t[%d] = \\0 (Poison!)\n", i);
            else
                fprintf(file, "\t\t[%d] = %x\n", i, stk->data[i]);
        }
        break;
    
    default:
        fprintf(file, "\t\t Unknow type element\n");
        break;
    }
}

int Comparator_poison(element_t element)
{
    switch(code_t)
    {
        case 4: return (element == nullptr);
    }
}

void Placing_canary(struct Stack* stk, void* temp)
{
    NULL_check(stk);
    assert(temp != nullptr);

    canary_t* canary_array_left = (canary_t*) temp;
    *canary_array_left = Canary;

    stk->data = ((element_t*) &(canary_array_left[1]));
                    
    canary_t* canary_array_right = (canary_t*) &(stk->data[stk->capacity]);
    *canary_array_right = Canary;
}

