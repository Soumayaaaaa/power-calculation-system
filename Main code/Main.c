#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

typedef struct Victim {
    int id;
    char bloodType[10];
    struct Victim* next;
} Victim;

static void wait_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

void loading() {
    printf("Loading");
    for(int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        wait_ms(1000);
    }
    printf("\n");
}

int main(){
    printf(CYAN "\n----------------------------\n" RESET);
    printf(RED "   VAMPIRE CONTROL\n" RESET);
    printf(CYAN "============================\n" RESET);
    printf("1. Add victim\n");
    printf("2. Delete victim\n");
    printf("3. Modify victim\n");
    printf("4. Display victims\n");
    printf("5. Calculate power\n");
    printf("6. Exit\n");
    printf(CYAN "============================\n" RESET);
    return 0;
}
