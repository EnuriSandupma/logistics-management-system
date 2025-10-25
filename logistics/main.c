#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define MAX_NAME_LENGTH 50
#define FUEL_PRICE 310.0




// Global variables
char cities[MAX_CITIES][MAX_NAME_LENGTH];
int distances[MAX_CITIES][MAX_CITIES];
int city_count = 0;





// Function prototypes
void displayMenu();
void addCity();
void loadFromFile();
int findCity(char*name);
void clearInputBuffer();


// Main function with menu
int main() {
    int choice;

    printf("\n========================================\n");
    printf("   LOGISTICS MANAGEMENT SYSTEM\n");
    printf("========================================\n");

    loadFromFile();

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
switch(choice) {
            case 1:
                addCity();
                break;
 exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }


    }
    return 0;
}

// Menu display function
void displayMenu() {
    printf("\n========================================\n");
    printf("           MAIN MENU\n");
    printf("========================================\n");
    printf("1. Add New City\n");
    printf("2. Rename City\n");
    printf("3. Remove City\n");
    printf("4. Display All Cities\n");
    printf("5. Set/Edit Distance Between Cities\n");
    printf("6. Display Distance Table\n");
    printf("7. Process Delivery Request\n");
    printf("8. View Delivery Records\n");
    printf("9. Generate Reports\n");
    printf("10. Save and Exit\n");
    printf("========================================\n");
}
void addCity() {
    if(city_count >= MAX_CITIES) {
        printf("\nError: Maximum city limit reached!\n");
        return;
    }

    char name[MAX_NAME_LENGTH];
    printf("\nEnter city name: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline



    strcpy(cities[city_count], name);


    for(int i = 0; i <= city_count; i++) {
        distances[city_count][i] = 0;
        distances[i][city_count] = 0;
    }
city_count++;
    printf("\nCity '%s' added successfully!\n", name);
}



    int findCity(char*name) {
    for(int i=0;i<city_count;i++) {
        if(strcasecmp(cities[i],name) == 0) {
            return i;
        }
    }

    return -1;
    }
void loadFromFile() {
    // Load cities and distances
    FILE *fp = fopen("routes.txt", "r");
    if(fp == NULL) {
        return; // File doesn't exist yet
    }
}


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
