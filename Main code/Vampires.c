#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Vampire.h"

// convert lowercase letters to uppercase inside a blood type string.
void normalize_bloodtype(char bloodtype[]) {
    int i;

    for (i = 0; bloodtype[i] != '\0'; i++) {
        if (bloodtype[i] >= 'a' && bloodtype[i] <= 'z') {
            bloodtype[i] = bloodtype[i] - 32;
        }
    }
}

// checking if the bloodtype actually exist
int is_valid_bloodtype(char bloodtype[]) {
    return strcmp(bloodtype, "A") == 0 ||
           strcmp(bloodtype, "B") == 0 ||
           strcmp(bloodtype, "O") == 0 ||
           strcmp(bloodtype, "AB") == 0;
}

// give the numeric vampire value of a blood type
int blood_value(char bloodtype[]) {
    if (strcmp(bloodtype, "A") == 0) {
        return VAL_A;
    }
    if (strcmp(bloodtype, "B") == 0) {
        return VAL_B;
    }
    if (strcmp(bloodtype, "AB") == 0) {
        return VAL_AB;
    }
    if (strcmp(bloodtype, "O") == 0) {
        return VAL_O;
    }

    return 0;
}

// search for a victim id (to avoid duplicate id's)
int id_exists(Victim* head, int id) {
    Victim* current = head;

    while (current != NULL) {
        if (current->id == id) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

// check if a value already exists in an array
int value_exists(int values[], int size, int value) {
    int i;

    for (i = 0; i < size; i++) {
        if (values[i] == value) {
            return 1;
        }
    }

    return 0;
}

// qdd a victim while keeping the linked list sorted by id
Victim* add_victim(Victim* head, int id, char* name, char* bloodtype) {
    Victim* new_victim;
    Victim* current;
    char fixed_bloodtype[3];

    strcpy(fixed_bloodtype, bloodtype);
    normalize_bloodtype(fixed_bloodtype);

    if (!is_valid_bloodtype(fixed_bloodtype)) {
        printf(YELLOW "Invalid blood type. Use A, B, O or AB.\n" RESET);
        return head;
    }

    if (id_exists(head, id)) {
        printf(YELLOW "This ID already exists. Duplicate IDs are not allowed.\n" RESET);
        return head;
    }

    new_victim = (Victim*)malloc(sizeof(Victim));
    if (new_victim == NULL) {
        printf(RED "Memory allocation failed.\n" RESET);
        return head;
    }

    new_victim->id = id;
    strcpy(new_victim->name, name);
    strcpy(new_victim->bloodtype, fixed_bloodtype);
    new_victim->next = NULL;

    if (head == NULL || id < head->id) {
        new_victim->next = head;
        printf(GREEN "Victim added.\n" RESET);
        return new_victim;
    }

    current = head;
    while (current->next != NULL && current->next->id < id) {
        current = current->next;
    }

    new_victim->next = current->next;
    current->next = new_victim;

    printf(GREEN "Victim added.\n" RESET);

    return head;
}

// delete a victim by id
Victim* delete_victim(Victim* head, int id) {
    Victim* current = head;
    Victim* previous = NULL;

    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf(YELLOW "Victim not found.\n" RESET);
        return head;
    }

    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf(GREEN "Victim deleted.\n" RESET);

    return head;
}

// modify the name and blood type of one victim
void modify_victim(Victim* head, int id) {
    Victim* current = head;
    char new_name[NAME_SIZE];
    char new_bloodtype[3];

    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current == NULL) {
        printf(YELLOW "Victim not found.\n" RESET);
        return;
    }

    printf("Enter new name: ");
    scanf(" %49[^\n]", new_name);

    printf("Enter new blood type (A/B/O/AB): ");
    scanf(" %2s", new_bloodtype);
    normalize_bloodtype(new_bloodtype);

    if (!is_valid_bloodtype(new_bloodtype)) {
        printf(YELLOW "Invalid blood type. Modification cancelled.\n" RESET);
        return;
    }

    strcpy(current->name, new_name);
    strcpy(current->bloodtype, new_bloodtype);

    printf(GREEN "Victim modified.\n" RESET);
}

// display all victims in the linked list.
void display_victims(Victim* head) {
    Victim* current = head;

    if (head == NULL) {
        printf(YELLOW "The list is empty.\n" RESET);
        return;
    }

    printf(CYAN "\nVictims list\n" RESET);
    printf(CYAN "-------------------------------------\n" RESET);

    while (current != NULL) {
        printf("ID: %d | Name: %s | Blood: %s | Power: %d\n",
               current->id,
               current->name,
               current->bloodtype,
               blood_value(current->bloodtype));

        current = current->next;
    }
}

//the final function:
// wetraverse the list, calculate blood values, and count each value only once
int calculate_power(Victim* head) {
    Victim* current = head;
    int used_values[4];
    int used_count = 0;
    int total = 0;
    int value;

    while (current != NULL) {
        value = blood_value(current->bloodtype);

        if (value != 0 && !value_exists(used_values, used_count, value)) {
            total = total + value;
            used_values[used_count] = value;
            used_count++;
        }

        current = current->next;
    }

    return total;
}

// save the linked list in a sequential text file
void save_victims_to_file(Victim* head, char filename[]) {
    FILE* file;
    Victim* current = head;

    file = fopen(filename, "w");

    if (file == NULL) {
        printf(RED "Error: could not create the file.\n" RESET);
        return;
    }

    fprintf(file, "VAMPIRE VICTIMS LIST\n");
    fprintf(file, "--------------------\n");

    while (current != NULL) {
        fprintf(file, "ID: %d | Name: %s | Blood: %s | Power: %d\n",
                current->id,
                current->name,
                current->bloodtype,
                blood_value(current->bloodtype));

        current = current->next;
    }

    fprintf(file, "\nTotal vampire power: %d\n", calculate_power(head));

    fclose(file);

    printf(GREEN "Victims saved in the sequential file: %s\n" RESET, filename);
}
// we free the memory used by the linked list before exiting
void free_list(Victim* head) {
    Victim* current = head;
    Victim* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
