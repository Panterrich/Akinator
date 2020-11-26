#define CBG_BLACK       "40;"
#define CBG_RED         "41;"
#define CBG_GREEN       "42;"
#define CBG_YELLOW      "43;"
#define CBG_BLUE        "44;"
#define CBG_MARGENTA    "45;"
#define CBG_CYAN        "46;"
#define CBG_WHITE       "47;"

#define CBG_NORMAL      "49;"

#define CBLACK       "30;"
#define CRED         "31;"
#define CGREEN       "32;"
#define CYELLOW      "33;"
#define CBLUE        "34;"
#define CMARGENTA    "35;"
#define CCYAN        "36;"
#define CWHITE       "37;"

#define CNORMAL      "39;"

#define RESET() "\e[0m"  

#define BG_BLACK(text)       "\e[40m" #text "\e[0m"
#define BG_RED(text)         "\e[41m" #text "\e[0m"
#define BG_GREEN(text)       "\e[42m" #text "\e[0m"
#define BG_YELLOW(text)      "\e[43m" #text "\e[0m"
#define BG_BLUE(text)        "\e[44m" #text "\e[0m"
#define BG_MARGENTA(text)    "\e[45m" #text "\e[0m"
#define BG_CYAN(text)        "\e[46m" #text "\e[0m"
#define BG_WHITE(text)       "\e[47m" #text "\e[0m"

#define BG_NORMAL(text)     "\e[49m" #text "\e[0m"

#define BLACK(text)       "\e[30m" #text "\e[0m"
#define RED(text)         "\e[31m" #text "\e[0m"
#define GREEN(text)       "\e[32m" #text "\e[0m"
#define YELLOW(text)      "\e[33m" #text "\e[0m"
#define BLUE(text)        "\e[34m" #text "\e[0m"
#define MARGENTA(text)    "\e[35m" #text "\e[0m"
#define CYAN(text)        "\e[36m" #text "\e[0m"
#define WHITE(text)       "\e[37m" #text "\e[0m"

#define NORMAL(text)      "\e[39m" #text "\e[0m"

