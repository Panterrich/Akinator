#define BG_BLACK       "40;"
#define BG_RED         "41;"
#define BG_GREEN       "42;"
#define BG_YELLOW      "43;"
#define BG_BLUE        "44;"
#define BG_MARGENTA    "45;"
#define BG_CYAN        "46;"
#define BG_WHITE       "47;"

#define BG_NORMAL      "49;"

#define BLACK       "30;"
#define RED         "31;"
#define GREEN       "32;"
#define YELLOW      "33;"
#define BLUE        "34;"
#define MARGENTA    "35;"
#define CYAN        "36;"
#define WHITE       "37;"

#define NORMAL      "39;"

#define RESET() "\e[0m"
#define COLOR(text, ...)  "\e[" ##__VA_ARGS__ "m" #text "\e[0m"
