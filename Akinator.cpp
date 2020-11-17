#include "Akinator.h"

//===============================================================================================================================

void Menu(const char* name_base)
{
    Screen_clear();

    printf("# Akinator\n"
           " (c) Panterrich, 2020\n\n"
           "Выберите соотвествующий режим работы\n"
           "[\e[6;31m1\e[0m] Отгадывание \n"
           "[\e[6;31m2\e[0m] Определения \n"
           "[\e[6;31m3\e[0m] Сравнения обьектов \n"
           "[\e[6;31m4\e[0m] Просмотр базы данных \n"
           "[\e[6;31m5\e[0m] Выход\n\n\n");

    system("echo \"Вас приветствует игра Акинатор. Выберите соответствующий режим игры.\" | festival --tts --language russian");

    Processing_mode(name_base);
}

void Menu_guessing(struct Tree* tree, const char* name_base)
{
    printf("\nХотите продолжить?\n"
           "[\e[31m1\e[0m] Начать занаво\n"
           "[\e[31m2\e[0m] Сохранить изменения\n"
           "[\e[31m3\e[0m] Выйти в меню\n");

    system("echo \"Хотите продолжить?\" | festival --tts --language russian");

    Processing_mode_guessing(tree, name_base);
}

void Menu_definition(struct Tree* tree, const char* name_base)
{
    printf("\nХотите продолжить?\n"
           "[\e[31m1\e[0m] Начать занаво\n"
           "[\e[31m2\e[0m] Выйти в меню\n");

    system("echo \"Хотите продолжить?\" | festival --tts --language russian");

    Processing_mode_definition(tree, name_base);
}

void Menu_comparing(struct Tree* tree, const char* name_base)
{
    printf("\nХотите продолжить?\n"
           "[\e[31m1\e[0m] Начать занаво\n"
           "[\e[31m2\e[0m] Выйти в меню\n");

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
        exit(0);

    default:
        printf("Unknown mode \n");
        break;
    }
}

void Processing_mode_guessing(struct Tree* tree, const char* name_base)
{
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
            printf("Unknown mode \n");
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
        case KEY_Y: return 1;
        case KEY_y: return 1;
        case KEY_N: return 0;
        case KEY_n: return 0;

        default: return -1;
    }
}

void Processing_mode_definition(struct Tree* tree, const char* name_base)
{
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
            printf("Unknown mode \n");
            break;
    }
}

void Processing_mode_comparing(struct Tree* tree, const char* name_base)
{
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
            printf("Unknown mode \n");
            break;
    }
}

void Mod_guessing(const char* name_base)
{   
    struct Tree tree = {};

    Tree_construct(&tree);
    Tree_create(&tree, name_base);

    Guessing(&tree, name_base);
}

void Mod_definition(const char* name_base)
{
    struct Tree tree = {};

    Tree_construct(&tree);
    Tree_create(&tree, name_base);

    Screen_clear();

    Definition(&tree, name_base);
}

void Mod_comparing(const char* name_base)
{
    struct Tree tree = {};

    Tree_construct(&tree);
    Tree_create(&tree, name_base);

    Screen_clear();

    Comparing(&tree, name_base);    
}

void Mod_dump(const char* name_base)
{
    struct Tree tree = {};

    Tree_construct(&tree);
    Tree_create(&tree, name_base);

    Screen_clear();

    Tree_graph(&tree);

    Menu(name_base);
}

void Guessing(struct Tree* tree, const char* name_base)
{   
    Screen_clear();

    printf("\nДавайте я попробую угадать ваше слово.\n");
    system("echo \"Давайте я попробую угадать ваше слово.\" | festival --tts --language russian");

    Question(tree, tree->root);

    Menu_guessing(tree, name_base);
}

void Question(struct Tree* tree, struct Node* current_node)
{
    char command[MAX_SIZE_COMMAND] = {};

    if (current_node->left == nullptr && current_node->right == nullptr)
    {
        if (strcmp(current_node->str, "Неизвестно кто") == 0)
        {
            printf("Я не знаю, кто это. Скажите мне кто это, чтобы я запомнил:\n");

            sprintf(command, "echo \"Я не знаю, кто это. Скажите мне кто это, чтобы я запомнил.\" | festival --tts --language russian");
            system(command);

            char new_object[MAX_SIZE_STR] = {};
            fgets(new_object, MAX_SIZE_STR, stdin);

            printf("Введите определительный признак для обьекта: %s.\n"
                    "Признак: ", new_object);
            
            char indication[MAX_SIZE_STR] = {};
            fgets(indication, MAX_SIZE_STR, stdin);

            struct Node* left_node  = (struct Node*) calloc(1, sizeof(struct Node));
            struct Node* right_node = (struct Node*) calloc(1, sizeof(struct Node));

            left_node->str   = current_node->str;
            left_node->len   = current_node->len;
            left_node->prev  = current_node;
            left_node->left  = nullptr;
            left_node->right = nullptr;

            right_node->str   = strdup(new_object);
            right_node->len   = strlen(left_node->str);
            right_node->prev  = current_node;
            right_node->left  = nullptr;
            right_node->right = nullptr;

            current_node->str   = strdup(indication);
            current_node->len   = strlen(current_node->str);
            current_node->left  = left_node;
            current_node->right = right_node;
        }

        else
        {
            printf("\nЭто %s? [Y\\N]\n", current_node->str);

            sprintf(command, "echo \"Я предположу, что это %s\" | festival --tts --language russian", current_node->str);
            system(command);

            if (Processing_answer())
            {
                printf("\nУра! Я выйграл. Вам не удалось меня переиграть.\n");

                sprintf(command, "echo \"Ура! Я выйграл. Вам не удалось меня переиграть.\" | festival --tts --language russian");
                system(command);
            }

            else
            {
                printf("\nЯ не знаю, кто это. Скажите мне кто это, чтобы я запомнил:\n");

                sprintf(command, "echo \"Я не знаю, кто это. Скажите мне кто это, чтобы я запомнил.\" | festival --tts --language russian");
                system(command);

                char new_object[MAX_SIZE_STR] = {};
                fgets(new_object, MAX_SIZE_STR, stdin);
                new_object[strlen(new_object) - 1] = '\0';

                printf("\nВведите разделительный признак для обьектов: %s и %s.\n"
                        "Где из ответа \"ДА\" следует объект %s\n"
                        "А из ответа \"НЕТ\" следует объект %s\n"
                        "Признак: ", 
                        current_node->str, new_object, new_object, current_node->str);
                
                char indication[MAX_SIZE_STR] = {};
                fgets(indication, MAX_SIZE_STR, stdin);
                indication[strlen(indication) - 1] = '\0';

                struct Node* left_node  = (struct Node*) calloc(1, sizeof(struct Node));
                struct Node* right_node = (struct Node*) calloc(1, sizeof(struct Node));

                left_node->str   = current_node->str;
                left_node->len   = current_node->len;
                left_node->prev  = current_node;
                left_node->left  = nullptr;
                left_node->right = nullptr;

                right_node->str   = strdup(new_object);
                right_node->len   = strlen(left_node->str);
                right_node->prev  = current_node;
                right_node->left  = nullptr;
                right_node->right = nullptr;

                current_node->str   = strdup(indication);
                current_node->len   = strlen(current_node->str);
                current_node->left  = left_node;
                current_node->right = right_node;
            }
        }
    }

    else
    {
        printf("\nЭто %s? [Y\\N]\n", current_node->str);

        sprintf(command, "echo \"Это %s?\" | festival --tts --language russian", current_node->str);
        system(command);

        if (Processing_answer())
        {
            Question(tree, current_node->right);
        }

        else
        {
            Question(tree, current_node->left);
        }
    }
}

void Definition(struct Tree* tree, const char* name_base)
{
    char command[MAX_SIZE_COMMAND] = {};

    Screen_clear();
    printf("\nВведите слово, определение которого хотите посмотреть:\n");

    sprintf(command, "echo \"Введите слово, определение которого хотите посмотреть:\" | festival --tts --language russian");
    system(command);

    char name[MAX_SIZE_STR] = {};
    fgets(name, MAX_SIZE_STR, stdin);
    name[strlen(name) - 1] = '\0';

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
        printf("%s:\n", name);

        for (size_t index = 0; index < path->size - 1; ++index)
        {
            if ((path->data)[index]->left  == (path->data)[index + 1])
            {
                printf("    не %s\n", (path->data)[index]->str);
            }

            if ((path->data)[index]->right == (path->data)[index + 1])
            {
                printf("    %s\n", (path->data)[index]->str);
            }
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
    char command[MAX_SIZE_COMMAND] = {};

    Screen_clear();
    printf("\nВведите 2 слова, которое вы хотите сравниить:\n");

    sprintf(command, "echo \"Введите 2 слова, которое вы хотите сравниить:\" | festival --tts --language russian");
    system(command);

    char name_1[MAX_SIZE_STR] = {};
    char name_2[MAX_SIZE_STR] = {};

    printf("1. ");
    fgets(name_1, MAX_SIZE_STR, stdin);

    printf("2. ");
    fgets(name_2, MAX_SIZE_STR, stdin);

    name_1[strlen(name_1) - 1] = '\0';
    name_2[strlen(name_2) - 1] = '\0';

    struct Stack* path_1 = Tree_search(name_1, tree);
    struct Stack* path_2 = Tree_search(name_2, tree);


    if (path_1->size == 0)
    {
        Screen_clear();
        printf("Обьект %s не найден в базе данных %s", name_1, tree->name_base);

        sprintf(command, "echo \"Объект %s не найден в базе данных %s\" | festival --tts --language russian", name_1, tree->name_base);
        system(command);
    }

    else if (path_2->size == 0)
    {
        Screen_clear();
        printf("Обьект %s не найден в базе данных %s", name_2, tree->name_base);

        sprintf(command, "echo \"Объект %s не найден в базе данных %s\" | festival --tts --language russian", name_2, tree->name_base);
        system(command);
    }

    else
    {
        Screen_clear();
        printf("1. %s\n"
               "2. %s\n\n"
               "Сходство:\n", name_1, name_2);

        size_t index_1 = 0;
        size_t index_2 = 0;

        while (((path_1->data)[index_1 + 1] == (path_2->data)[index_1 + 1]) && (index_1 < path_1->size - 1) && (index_2 < path_2->size - 1))
        {
            if ((path_1->data)[index_1]->left  == (path_1->data)[index_1 + 1])
            {
                printf("    не %s\n", (path_1->data)[index_1]->str);
            }

            if ((path_1->data)[index_1]->right == (path_1->data)[index_1 + 1])
            {
                printf("    %s\n", (path_1->data)[index_1]->str);
            }

            ++index_1;
            ++index_2;
        }

        printf("Различия:\n"
               "1. %s\n", name_1);
        
        for (; index_1 < path_1->size - 1; ++index_1)
        {
            if ((path_1->data)[index_1]->left  == (path_1->data)[index_1 + 1])
            {
                printf("    не %s\n", (path_1->data)[index_1]->str);
            }

            if ((path_1->data)[index_1]->right == (path_1->data)[index_1 + 1])
            {
                printf("    %s\n", (path_1->data)[index_1]->str);
            }
        }

        printf("2. %s\n", name_2);

        for (; index_2 < path_2->size - 1; ++index_2)
        {
            if ((path_2->data)[index_2]->left  == (path_2->data)[index_2 + 1])
            {
                printf("    не %s\n", (path_2->data)[index_2]->str);
            }

            if ((path_2->data)[index_2]->right == (path_2->data)[index_2 + 1])
            {
                printf("    %s\n", (path_2->data)[index_2]->str);
            }
        }

        sprintf(command, "echo \"Вот сходства и различия объектов: %s и %s\" | festival --tts --language russian", name_1, name_2);
        system(command);
    }

    Stack_destruct(path_1);
    Stack_destruct(path_2);

    free(path_1);
    free(path_2);

    Menu_comparing(tree, name_base);
}

void Tree_create(struct Tree* tree, const char* name_base)
{
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

        current_node->len = pointer_end - pointer_begin - 1;
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

            current_node->len = pointer_end - pointer_begin - 1;
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
