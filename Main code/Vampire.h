#ifndef VAMPIRES_H
#define VAMPIRES_H

// colors
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

// Blood Types
#define VAL_A 10
#define VAL_B 20
#define VAL_AB 30
#define VAL_O 40

// Record
typedef struct Victim {
    int id;
    char name[20];
    char bloodtype[3];
    struct Victim* next;
} Victim;

// Function prototypes
Victim* add_victim(Victim* head, int id, char* name, char* bloodtype);
Victim* delete_victim(Victim* head, int id);
void    modify_victim(Victim* head, int id);  
void    display_victims(Victim* head);
int     calculate_power(Victim* head);

#endif
