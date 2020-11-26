#include "Akinator.h"
#include "Colors.h"

//===============================================================================================================================

void Menu(const char* name_base)
{
    assert(name_base != nullptr);

    static int voice = 1;

    Screen_clear();
    
    printf("# Akinator\n"
           " (c) Panterrich, 2020\n\n"
           "Выберите соотвествующий режим работы\n"
           "[" RED(1) "] Отгадывание \n"
           "[" RED(2) "] Определения \n"
           "[" RED(3) "] Сравнения обьектов \n"
           "[" RED(4) "] Просмотр базы данных \n"
           "[" RED(5) "] Выход \n\n\n");

    if (voice)
    {
        system("echo \"Вас приветствует игра Акинатор. Выберите соответствующий режим игры.\" | festival --tts --language russian");

        voice = 0;
    }

    Processing_mode(name_base);
}

void Menu_guessing(struct Tree* tree, const char* name_base)
{
    Tree_null_check(tree);
    assert(name_base != nullptr);

    printf("\nХотите продолжить?\n"
           "[" RED(1) "] Начать заново\n"
           "[" RED(2) "] Сохранить изменения\n"
           "[" RED(3) "] Выйти в меню\n");

    system("echo \"Хотите продолжить?\" | festival --tts --language russian");

    Processing_mode_guessing(tree, name_base);
}

void Menu_definition(struct Tree* tree, const char* name_base)
{
    Tree_null_check(tree);
    assert(name_base != nullptr);

    printf("\nХотите продолжить?\n"
           "[" RED(1) "] Начать заново\n"
           "[" RED(2) "] Выйти в меню\n");

    system("echo \"Хотите продолжить?\" | festival --tts --language russian");

    Processing_mode_definition(tree, name_base);
}

void Menu_comparing(struct Tree* tree, const char* name_base)
{
    Tree_null_check(tree);
    assert(name_base != nullptr);

    printf("\nХотите продолжить?\n"
           "[" RED(1) "] Начать заново\n"
           "[" RED(2) "] Выйти в меню\n");

    system("echo \"Хотите продолжить?\" | festival --tts --language russian");

    Processing_mode_comparing(tree, name_base);
}

int Getkey()
{
    struct termios oldt = {};
    struct termios newt = {};

    int command = 0;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    command = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return command;
}

void Screen_clear()
{
    system("@cls||clear");
}

void Processing_mode(const char* name_base)
{
    assert(name_base != nullptr);

    int mode = 0;

    for (mode = Getkey(); (mode != KEY_1) &&
                          (mode != KEY_2) &&
                          (mode != KEY_3) &&
                          (mode != KEY_4) &&
                          (mode != KEY_5);
                                            mode = Getkey());

    switch (mode)
    {
    case KEY_1:
        Mod_guessing(name_base);
        break;

    case KEY_2:
        Mod_definition(name_base);
        break;

    case KEY_3:
        Mod_comparing(name_base);
        break;

    case KEY_4:
        Mod_dump(name_base);
        break;

    case KEY_5:
        return;

    default:
        printf("Unknown mode %d\n", mode);
        break;
    }
}

void Processing_mode_guessing(struct Tree* tree, const char* name_base)
{
    Tree_null_check(tree);
    assert(name_base != nullptr);

    int command = 0;

    for (command = Getkey(); (command != KEY_1) && 
                             (command != KEY_2) &&
                             (command != KEY_3);    
                                                    command = Getkey());

    switch (command)
    {
        case KEY_1:
            Screen_clear();
            Guessing(tree, name_base);
            break;

        case KEY_2:
            Tree_print(tree);

            printf("Изменения сохранены.\n");
            system("echo \"Изменения сохранены.\" | festival --tts --language russian");

            Menu_guessing(tree, name_base);
            break;
        
        case KEY_3:
            Tree_destruct(tree);
            Menu(name_base);
            break;

        default:
            printf("Unknown mode %d\n", command);
            break;
    }
}

int Processing_answer()
{
    int command = 0;

    for (command = Getkey(); (command != KEY_Y) && 
                             (command != KEY_N) &&
                             (command != KEY_y) &&
                             (command != KEY_n);    command = Getkey());

    switch (command)
    {
        case KEY_Y: printf("Да\n"); return 1;
        case KEY_y: printf("Да\n"); return 1;
        case KEY_N: printf("Нет\n"); return 0;
        case KEY_n: printf("Нет\n"); return 0;

        default: printf("Неизветсный ответ\n"); return -1;
    }
}

void Processing_mode_definition(struct Tree* tree, const char* name_base)
{   
    Tree_null_check(tree);
    assert(name_base != nullptr);

    int command = 0;

    for (command = Getkey(); (command != KEY_1) && 
                             (command != KEY_2);    
                                                    command = Getkey());

    switch (command)
    {
        case KEY_1:
            Screen_clear();
            Definition(tree, name_base);
            break;
        
        case KEY_2:
            Tree_destruct(tree);
            Menu(name_base);
            break;

        default:
            printf("Unknown mode %d\n", command);
            break;
    }
}

void Processing_mode_comparing(struct Tree* tree, const char* name_base)
{
    Tree_null_check(tree);
    assert(name_base != nullptr);

    int command = 0;

    for (command = Getkey(); (command != KEY_1) && 
                             (command != KEY_2);    
                                                    command = Getkey());

    switch (command)
    {
        case KEY_1:
            Screen_clear();
            Comparing(tree, name_base);
            break;
        
        case KEY_2:
            Tree_destruct(tree);
            Menu(name_base);
            break;

        default:
            printf("Unknown mode %d\n", command);
            break;
    }
}

void Mod_guessing(const char* name_base)
{   
    assert(name_base != nullptr);

    struct Tree tree = {};

    Tree_construct(&tree);
    Tree_create(&tree, name_base);

    Guessing(&tree, name_base);
}

void Mod_definition(const char* name_base)
{   
    assert(name_base != nullptr);

    struct Tree tree = {};

    Tree_construct(&tree);
    Tree_create(&tree, name_base);

    Screen_clear();

    Definition(&tree, name_base);
}

void Mod_comparing(const char* name_base)
{
    assert(name_base != nullptr);

    struct Tree tree = {};

    Tree_construct(&tree);
    Tree_create(&tree, name_base);

    Screen_clear();

    Comparing(&tree, name_base);    
}

void Mod_dump(const char* name_base)
{
    assert(name_base != nullptr);

    struct Tree tree = {};

    Tree_construct(&tree);
    Tree_create(&tree, name_base);

    Screen_clear();

    Tree_graph(&tree);

    Tree_destruct(&tree);

    Menu(name_base);
}

void Guessing(struct Tree* tree, const char* name_base)
{  
    Tree_null_check(tree);
    assert(name_base != nullptr);

    Screen_clear();

    printf("\nДавайте я попробую угадать ваше слово.\n");
    system("echo \"Давайте я попробую угадать ваше слово.\" | festival --tts --language russian");

    Question(tree, tree->root);

    Menu_guessing(tree, name_base);
}

void Question(struct Tree* tree, struct Node* current_node)
{
    Tree_null_check(tree);
    assert(current_node != nullptr);

    char command[MAX_SIZE_COMMAND] = "";

    if (current_node->left == nullptr && current_node->right == nullptr)
    {
        if (strcmp(current_node->str, "Неизвестно кто") == 0)
        {
            printf("Я не знаю, кто это. Скажите мне кого вы загадали, чтобы я запомнил.\n"
                   "Ваше слово: ");

            sprintf(command, "echo \"Я не знаю, кто это. Скажите мне кого вы загадали, чтобы я запомнил.\" | festival --tts --language russian");
            system(command);

            char new_object[MAX_SIZE_STR] = "";
            while (!Get_word(new_object)) printf("\nВы ввели некорректное слово, попробуйте ещё.\nВаше загаданное слово: ");

            if (Tree_search(new_object, tree)->size == 0)
            {
                printf("Введите определительный признак для вашего слова: %s.\n"
                       "Признак: ", new_object);
                
                sprintf(command, "echo \"Введите определительный признак для вашего слова: %s.\" | festival --tts --language russian", new_object);
                system(command);
                
                char indication[MAX_SIZE_STR] = "";
                while (!Get_word(indication)) printf("\nВы ввели некорректный признак, попробуйте ещё.\n Признак: ");

                struct Node* left_node  = (struct Node*) calloc(1, sizeof(struct Node));
                struct Node* right_node = (struct Node*) calloc(1, sizeof(struct Node));

                Node_fill(left_node,    current_node->str,  current_node->len,  current_node,       nullptr,   nullptr);
                Node_fill(right_node,   strdup(new_object), strlen(new_object), current_node,       nullptr,   nullptr);
                Node_fill(current_node, strdup(indication), strlen(indication), current_node->prev, left_node, right_node);

                tree->size += 2;
            }

            else
            {
                printf("Ваше слово %s найдено в базе данных, попробуйте сыграть ещё раз.\n", new_object);
                
                sprintf(command, "echo \"Ваше слово %s найдено в базе данных, попробуйте сыграть ещё раз.\" | festival --tts --language russian", new_object);
                system(command);
            }
        }

        else
        {
            printf("\nЯ предположу, что это %s? [" RED(Y) "/" RED(N) "]\n", current_node->str);

            sprintf(command, "echo \"Я предположу, что это %s\" | festival --tts --language russian", current_node->str);
            system(command);

            if (Processing_answer())
            {
                printf("\nУра! Я выиграл. Вам не удалось меня переиграть.\n");

                sprintf(command, "echo \"Ура! Я выиграл. Вам не удалось меня переиграть.\" | festival --tts --language russian");
                system(command);
            }

            else
            {
                printf("\nЯ не знаю, кто это. Скажите мне кого вы загадали, чтобы я запомнил.\n"
                       "Ваше слово: ");

                sprintf(command, "echo \"Я не знаю, кто это. Скажите мне кого вы загадали, чтобы я запомнил.\" | festival --tts --language russian");
                system(command);

                char new_object[MAX_SIZE_STR] = "";
                while (!Get_word(new_object)) printf("\nВы ввели некорректное слово, попробуйте ещё.\nВаше слово: ");

                if (Tree_search(new_object, tree)->size == 0)
                {
                    printf("\nВведите признак отличающий %s от %s.\n"
                            "Признак: ", 
                            new_object, current_node->str);

                    sprintf(command, "echo \"Введите признак отличающий %s от %s.\" | festival --tts --language russian", new_object, current_node->str);
                    system(command);
                    
                    char indication[MAX_SIZE_STR] = "";
                    while (!Get_word(indication)) printf("\nВы ввели некорректное слово, попробуйте ещё.\nПризнак: ");

                    struct Node* left_node  = (struct Node*) calloc(1, sizeof(struct Node));
                    struct Node* right_node = (struct Node*) calloc(1, sizeof(struct Node));

                    Node_fill(left_node,    current_node->str,  current_node->len,  current_node,       nullptr,   nullptr);
                    Node_fill(right_node,   strdup(new_object), strlen(new_object), current_node,       nullptr,   nullptr);
                    Node_fill(current_node, strdup(indication), strlen(indication), current_node->prev, left_node, right_node);

                    tree->size += 2;
                }

                else
                {
                    printf("Ваше слово %s найдено в базе данных, попробуйте сыграть ещё раз.\n", new_object);
                
                    sprintf(command, "echo \"Ваше слово %s найдено в базе данных, попробуйте сыграть ещё раз.\" | festival --tts --language russian", new_object);
                    system(command);
                }
            }
        }
    }

    else
    {
        printf("\nЭто %s? [" RED(Y) "/" RED(N) "]\n", current_node->str);

        sprintf(command, "echo \"Это %s?\" | festival --tts --language russian", current_node->str);
        system(command);

        if (Processing_answer()) Question(tree, current_node->right);                
        else                     Question(tree, current_node->left);
    }
}

void Definition(struct Tree* tree, const char* name_base)
{
    Tree_null_check(tree);
    assert(name_base != nullptr);

    char command[MAX_SIZE_COMMAND] = "";

    Screen_clear();
    printf("Введите слово, определение которого хотите посмотреть.\n"
           "Ваше слово: ");

    sprintf(command, "echo \"Введите слово, определение которого хотите посмотреть:\" | festival --tts --language russian");
    system(command);

    char name[MAX_SIZE_STR] = "";
    while(!Get_word(name)) printf("\nВы ввели некорректное слово, попробуйте ещё.\nВаше слово: ");

    struct Stack* path = Tree_search(name, tree);

    if (path->size == 0)
    {
        Screen_clear();
        printf("Обьект %s не найден в базе данных %s", name, tree->name_base);

        sprintf(command, "echo \"Объект %s не найден в базе данных %s\" | festival --tts --language russian", name, tree->name_base);
        system(command);
    }
    else
    {
        Screen_clear();
        printf("%s - это", name);

        sprintf(command, "echo \"%s - это\" | festival --tts --language russian", name);
        system(command);

        for (size_t index = 0; index < path->size - 2; ++index)
        {   
            if (index % 6 == 5) printf("\n");

            if ((path->data)[index]->left  == (path->data)[index + 1])
            {
                printf(" не %s,", (path->data)[index]->str);

                sprintf(command, "echo \" не %s\" | festival --tts --language russian", (path->data)[index]->str);
                system(command);
            }

            if ((path->data)[index]->right == (path->data)[index + 1])
            {
                printf(" %s,", (path->data)[index]->str);

                sprintf(command, "echo \" %s\" | festival --tts --language russian", (path->data)[index]->str);
                system(command);
            }
        }

         if ((path->data)[path->size - 2]->left  == (path->data)[path->size - 1])
            {
                printf(" не %s.\n", (path->data)[path->size - 2]->str);

                sprintf(command, "echo \"не %s\" | festival --tts --language russian", (path->data)[path->size - 2]->str);
                system(command);
            }

        if ((path->data)[path->size - 2]->right == (path->data)[path->size - 1])
        {
            printf(" %s.\n", (path->data)[path->size - 2]->str);

            sprintf(command, "echo \" %s\" | festival --tts --language russian", (path->data)[path->size - 2]->str);
            system(command);
        }

        sprintf(command, "echo \"Вот определение объекта %s\" | festival --tts --language russian", name);
        system(command);
    }

    Stack_destruct(path);
    free(path);
    
    Menu_definition(tree, name_base);
}

void Comparing(struct Tree* tree, const char* name_base)
{
    Tree_null_check(tree);
    assert(name_base != nullptr);

    char command[MAX_SIZE_COMMAND] = "";

    Screen_clear();
    printf("Введите 2 слова, которое вы хотите сравнить:\n");

    sprintf(command, "echo \"Введите 2 слова, которое вы хотите сравнить \" | festival --tts --language russian");
    system(command);

    char name_1[MAX_SIZE_STR] = "";
    char name_2[MAX_SIZE_STR] = "";

    printf("1. ");
    while (!Get_word(name_1)) printf("\nВы ввели некорректное слово, попробуйте ещё.\n1. ");

    printf("2. ");
    while (!Get_word(name_2)) printf("\nВы ввели некорректное слово, попробуйте ещё.\n2. ");

    struct Stack* path_1 = Tree_search(name_1, tree);
    struct Stack* path_2 = Tree_search(name_2, tree);


    if (path_1->size == 0)
    {
        Screen_clear();
        printf("Обьект %s не найден в базе данных %s", name_1, tree->name_base);

        sprintf(command, "echo \"Объект %s не найден в базе данных %s \" | festival --tts --language russian", name_1, tree->name_base);
        system(command);
    }

    else if (path_2->size == 0)
    {
        Screen_clear();
        printf("Обьект %s не найден в базе данных %s", name_2, tree->name_base);

        sprintf(command, "echo \"Объект %s не найден в базе данных %s \" | festival --tts --language russian", name_2, tree->name_base);
        system(command);
    }

    else
    {
        Screen_clear();
        printf("%s и %s схожи тем, что", name_1, name_2);

        sprintf(command, "echo \"%s и %s схожи тем что \" | festival --tts --language russian", name_1, name_2);
        system(command);

        size_t index_1 = 0;
        size_t index_2 = 0;

        while (((path_1->data)[index_1 + 1] == (path_2->data)[index_1 + 1]) && (index_1 < path_1->size - 1) && (index_2 < path_2->size - 1))
        {   
            if (index_1 % 6 == 5) printf("\n");

            if ((path_1->data)[index_1]->left  == (path_1->data)[index_1 + 1])
            {
                printf(" не %s,", (path_1->data)[index_1]->str);

                sprintf(command, "echo \"не %s\" | festival --tts --language russian", (path_1->data)[index_1]->str);
                system(command);
            }

            if ((path_1->data)[index_1]->right == (path_1->data)[index_1 + 1])
            {
                printf(" %s,", (path_1->data)[index_1]->str);

                sprintf(command, "echo \" %s\" | festival --tts --language russian", (path_1->data)[index_1]->str);
                system(command);
            }

            ++index_1;
            ++index_2;
        }

        printf("\nно %s отличается тем, что", name_1);

        sprintf(command, "echo \"но %s отличается тем что\" | festival --tts --language russian", name_1);
        system(command);
        
        for (; index_1 < path_1->size - 1; ++index_1)
        {   
            if (index_1 % 6 == 5) printf("\n");

            if ((path_1->data)[index_1]->left  == (path_1->data)[index_1 + 1])
            {
                printf(" не %s,", (path_1->data)[index_1]->str);

                sprintf(command, "echo \"не %s\" | festival --tts --language russian", (path_1->data)[index_1]->str);
                system(command);
            }

            if ((path_1->data)[index_1]->right == (path_1->data)[index_1 + 1])
            {
                printf(" %s,", (path_1->data)[index_1]->str);

                sprintf(command, "echo \" %s\" | festival --tts --language russian", (path_1->data)[index_1]->str);
                system(command);
            }
        }

        printf("\nа %s отличается тем, что", name_2);

        sprintf(command, "echo \" а %s отличается тем что\" | festival --tts --language russian", name_2);
        system(command);

        for (; index_2 < path_2->size - 2; ++index_2)
        {
            if (index_2 % 6 == 5) printf("\n");

            if ((path_2->data)[index_2]->left  == (path_2->data)[index_2 + 1])
            {
                printf(" не %s,", (path_2->data)[index_2]->str);

                sprintf(command, "echo \"не %s\" | festival --tts --language russian", (path_2->data)[index_2]->str);
                system(command);
            }

            if ((path_2->data)[index_2]->right == (path_2->data)[index_2 + 1])
            {
                printf(" %s,", (path_2->data)[index_2]->str);

                sprintf(command, "echo \" %s\" | festival --tts --language russian", (path_2->data)[index_2]->str);
                system(command);
            }
        }

        if ((path_2->data)[index_2]->left  == (path_2->data)[index_2 + 1])
        {
            printf(" не %s.\n", (path_2->data)[index_2]->str);

            sprintf(command, "echo \"не %s\" | festival --tts --language russian", (path_2->data)[index_2]->str);
            system(command);
        }

        if ((path_2->data)[index_2]->right == (path_2->data)[index_2 + 1])
        {
            printf(" %s.\n", (path_2->data)[index_2]->str);

            sprintf(command, "echo \" %s\" | festival --tts --language russian", (path_2->data)[index_2]->str);
            system(command);
        }


        sprintf(command, "echo \"Вот все сходства и различия объектов %s и %s\" | festival --tts --language russian", name_1, name_2);
        system(command);
    }

    Stack_destruct(path_1);
    Stack_destruct(path_2);

    free(path_1);
    free(path_2);

    Menu_comparing(tree, name_base);
}

int Get_word(char* name)
{
    if (fgets(name, MAX_SIZE_STR, stdin))
    {
        char* pointer_new_line = strchr(name, '\n');

        if (pointer_new_line == name) return 0;
        if (pointer_new_line)         *pointer_new_line = '\0';
        
        return 1;
    }
    
    else return 0;
}
