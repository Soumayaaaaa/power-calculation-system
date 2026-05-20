#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Vampire.h"

void wait_ms(int ms) {
    Sleep(ms);
}

void loading() {
    printf(RED "                        __.......__\n" RESET);
    printf(RED "                      .-:::::::::::::-.\n" RESET);
    printf(RED "                    .:::''':::::::''':::.\n" RESET);
    printf(RED "                  .:::'     `:::'     `:::.\n" RESET);
    printf(RED "             .'\\  ::'   ^^^  `:'  ^^^   '::\n" RESET);
    printf(RED "            :   \\ ::   _.__       __._   :: /   ;\n" RESET);
    printf(RED "           :     \\`: .' ___\\     /___ `. :'/     ;\n" RESET);
    printf(RED "          :       /\\   (_|_)\\   /(_|_)   /\\       ;\n" RESET);
    printf(RED "          :      / .\\   __.' ) ( `.__   /. \\      ;\n" RESET);
    printf(RED "          :      \\ (        {   }        ) /      ;\n" RESET);
    printf(RED "           :      `-(     .  ^\"^  .     )-'      ;\n" RESET);
    printf(RED "            `.       \\  .'<`-._.-'>'.  /       .'\n" RESET);
    printf(RED "              `.      \\    \\;`.';/    /      .'\n" RESET);
    printf(RED "                `._    `-._       _.-'    _.'\n" RESET);
    printf(RED "                 .'`-.__ .'`-._.-'`. __.-'`.\n" RESET);
    printf(RED "               .'       `.         .'       `.\n" RESET);
    printf(RED "             .'           `-.   .-'           `.\n" RESET);
   
   
    printf(RED "                                                      ,---,          \n" RESET);
    printf(RED "                                                   ,`--.' |          \n" RESET);
    printf(RED "                                   ____            |   :  :          \n" RESET);
    printf(RED "       ,---.                     ,'  , `.,-.----.  |   |  '          \n" RESET);
    printf(RED "      /__./|                  ,-+-,.' _ |\\    /  \\ '   :  |          \n" RESET);
    printf(RED " ,---.;  ; |               ,-+-. ;   , |||   :    |;   |.'.--.--.   \n" RESET);
    printf(RED "/___/ \\  | |   ,--.--.    ,--.'|'   |  |||   | .\\ :'---' /  /    '  \n" RESET);
    printf(RED "\\   ;  \\ ' |  /       \\  |   |  ,', |  |,.   : |: |     |  :  /`./  \n" RESET);
    printf(RED " \\   \\  \\: | .--.  .-. | |   | /  | |--' |   |  \\ :     |  :  ;_    \n" RESET);
    printf(RED "  ;   \\  ' .  \\__\\/: . . |   : |  | ,    |   : .  |      \\  \\    `. \n" RESET);
    printf(RED "   \\   \\   '  ,  .--.; | |   : |  |/     :     |`-'       `----.   \\ \n" RESET);
    printf(RED "    \\   `  ; /  /  ,.  | |   | |`-'      :   : :         /  /`--'  / \n" RESET);
    printf(RED "     :   \\ |;  :   .'   \\|   ;/          |   | :        '--'.     /  \n" RESET);
    printf(RED "      '---\\ |  ,     .-./'---'           `---'.|          `--'---'\n" RESET);
    printf(RED "             `--`---'                      `---`                     \n" RESET);
    printf(CYAN "\n                    ------- CONTROL SYSTEM -------\n\n" RESET);
    printf(RED "\n                        Awakening the vampire...\n" RESET);
    printf("  ");
    printf(RED "Starting vampire control" RESET);
    for(int i = 0; i < 20; i++) {
        printf(".");
        fflush(stdout);
        wait_ms(150);
    }
    printf("\n\n");
}

void print_menu() {
    printf(CYAN "\n----------------------------\n" RESET);
    printf(RED  "      VAMPIRE CONTROL\n" RESET);
    printf(CYAN "============================\n" RESET);
    printf(YELLOW "1." RESET " Add victim\n");
    printf(YELLOW "2." RESET " Delete victim\n");
    printf(YELLOW "3." RESET " Modify victim\n");
    printf(YELLOW "4." RESET " Display all victims\n");
    printf(YELLOW "5." RESET " Calculate total power\n");
    printf(YELLOW "6." RESET " Exit\n");
    printf(CYAN "============================\n" RESET);
    printf("Choice: ");
}

int main() {
    Victim* head = NULL;
    int choice;
    int id;
    char name[20];
    char bloodtype[3];

    loading();

    while (1) {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);

                printf("Enter name: ");
                scanf("%19s", name);

                printf("Enter blood type (A/B/O/AB): ");
                scanf("%2s", bloodtype);

                head = add_victim(head, id, name, bloodtype);
                break;

            case 2:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                head = delete_victim(head, id);
                break;

            case 3:
                printf("Enter ID to modify: ");
                scanf("%d", &id);
                modify_victim(head, id);
                break;

            case 4:
                display_victims(head);
                break;

            case 5:
                printf(RED "Total vampire power: %d\n" RESET, calculate_power(head));
                break;

            case 6:
                free_list(head);
                printf(RED "\nThe night is over...\n\n" RESET);
                return 0;

            default:
                printf(YELLOW "Invalid choice. Try again.\n" RESET);
        }
    }
}
