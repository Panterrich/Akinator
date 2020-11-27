#define CBOLD        "1;"
#define CITALIC      "3;"
#define CUNDERLINE   "4;"
#define CBLINKING    "5;"
#define CINVIS       "8;"

#define CBLACK       "30;"
#define CRED         "31;"
#define CGREEN       "32;"
#define CYELLOW      "33;"
#define CBLUE        "34;"
#define CMARGENTA    "35;"
#define CCYAN        "36;"
#define CWHITE       "37;"

#define CNORMAL      "39;"

#define CBG_BLACK       "40;"
#define CBG_RED         "41;"
#define CBG_GREEN       "42;"
#define CBG_YELLOW      "43;"
#define CBG_BLUE        "44;"
#define CBG_MARGENTA    "45;"
#define CBG_CYAN        "46;"
#define CBG_WHITE       "47;"

#define CBG_NORMAL      "49;"

//=======================================================

#define RBOLD        "\e[1m"
#define RITALIC      "\e[3m"
#define RUNDERLINE   "\e[4m"
#define RBLINKING    "\e[5m"
#define RINVIS       "\e[8m"

#define RBLACK       "\e[30m"
#define RRED         "\e[31m" 
#define RGREEN       "\e[32m" 
#define RYELLOW      "\e[33m" 
#define RBLUE        "\e[34m"
#define RMARGENTA    "\e[35m"
#define RCYAN        "\e[36m"
#define RWHITE       "\e[37m"

#define RNORMAL      "\e[39m"

#define RBG_BLACK       "\e[40m"
#define RBG_RED         "\e[41m"
#define RBG_GREEN       "\e[42m" 
#define RBG_YELLOW      "\e[43m" 
#define RBG_BLUE        "\e[44m" 
#define RBG_MARGENTA    "\e[45m" 
#define RBG_CYAN        "\e[46m" 
#define RBG_WHITE       "\e[47m" 

#define RBG_NORMAL      "\e[49m"

#define RESET() "\e[0m"  

//=======================================================

#define BOLD(text)        "\e[1m" #text "\e[0m"
#define ITALIC(text)      "\e[3m" #text "\e[0m"
#define UNDERLINE(text)   "\e[4m" #text "\e[0m"
#define BLINKING(text)    "\e[5m" #text "\e[0m"
#define INVIS(text)       "\e[8m" #text "\e[0m"

#define BLACK(text)       "\e[30m" #text "\e[0m"
#define RED(text)         "\e[31m" #text "\e[0m"
#define GREEN(text)       "\e[32m" #text "\e[0m"
#define YELLOW(text)      "\e[33m" #text "\e[0m"
#define BLUE(text)        "\e[34m" #text "\e[0m"
#define MARGENTA(text)    "\e[35m" #text "\e[0m"
#define CYAN(text)        "\e[36m" #text "\e[0m"
#define WHITE(text)       "\e[37m" #text "\e[0m"

#define NORMAL(text)      "\e[39m" #text "\e[0m"

#define BG_BLACK(text)       "\e[40m" #text "\e[0m"
#define BG_RED(text)         "\e[41m" #text "\e[0m"
#define BG_GREEN(text)       "\e[42m" #text "\e[0m"
#define BG_YELLOW(text)      "\e[43m" #text "\e[0m"
#define BG_BLUE(text)        "\e[44m" #text "\e[0m"
#define BG_MARGENTA(text)    "\e[45m" #text "\e[0m"
#define BG_CYAN(text)        "\e[46m" #text "\e[0m"
#define BG_WHITE(text)       "\e[47m" #text "\e[0m"

#define BG_NORMAL(text)     "\e[49m" #text "\e[0m"

//=======================================================

#define SBOLD(text)        "\e[1m" text "\e[0m"
#define SITALIC(text)      "\e[3m" text "\e[0m"
#define SUNDERLINE(text)   "\e[4m" text "\e[0m"
#define SBLINKING(text)    "\e[5m" text "\e[0m"
#define SINVIS(text)       "\e[8m" text "\e[0m"

#define SBLACK(text)       "\e[30m" text "\e[0m"
#define SRED(text)         "\e[31m" text "\e[0m"
#define SGREEN(text)       "\e[32m" text "\e[0m"
#define SYELLOW(text)      "\e[33m" text "\e[0m"
#define SBLUE(text)        "\e[34m" text "\e[0m"
#define SMARGENTA(text)    "\e[35m" text "\e[0m"
#define SCYAN(text)        "\e[36m" text "\e[0m"
#define SWHITE(text)       "\e[37m" text "\e[0m"

#define SNORMAL(text)      "\e[39m" text "\e[0m"

#define SBG_BLACK(text)       "\e[40m" text "\e[0m"
#define SBG_RED(text)         "\e[41m" text "\e[0m"
#define SBG_GREEN(text)       "\e[42m" text "\e[0m"
#define SBG_YELLOW(text)      "\e[43m" text "\e[0m"
#define SBG_BLUE(text)        "\e[44m" text "\e[0m"
#define SBG_MARGENTA(text)    "\e[45m" text "\e[0m"
#define SBG_CYAN(text)        "\e[46m" text "\e[0m"
#define SBG_WHITE(text)       "\e[47m" text "\e[0m"

#define SBG_NORMAL(text)     "\e[49m" text "\e[0m"

//=======================================================

#define COLOR(text, ...)  "\e[" __VA_ARGS__ "10m" #text "\e[0m"
#define SCOLOR(text, ...) "\e[" __VA_ARGS__ "10m" text  "\e[0m"

