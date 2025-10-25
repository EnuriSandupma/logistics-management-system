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
void renameCity();
void removeCity();
void displayCities();
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
            case 2:
                renameCity();
                break;
            case 3:
                removeCity();
                break;
            case 4:
                displayCities();
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

void renameCity() {
    if(city_count == 0) {
        printf("\nNo cities available!\n");
        return;
    }

void displayCities();

    int index;
    printf("\nEnter city number to rename: ");
    scanf("%d", &index);
    clearInputBuffer();

    if(index < 1 || index > city_count) {
        printf("\nInvalid city number!\n");
        return;
    }

    char new_name[MAX_NAME_LENGTH];
    printf("Enter new name: ");
    fgets(new_name, MAX_NAME_LENGTH, stdin);
    new_name[strcspn(new_name, "\n")] = 0;

    // Check if new name already exists
    if(findCity(new_name) != -1) {
        printf("\nError: City name already exists!\n");
        return;
    }

    printf("\nCity '%s' renamed to '%s'\n", cities[index-1], new_name);
    strcpy(cities[index-1], new_name);
}
void removeCity() {
    if(city_count == 0) {
        printf("\nNo cities available!\n");
        return;
    }

void displayCities();

    int index;
    printf("\nEnter city number to remove: ");
    scanf("%d", &index);
    clearInputBuffer();

    if(index < 1 || index > city_count) {
        printf("\nInvalid city number!\n");
        return;
    }

    printf("\nCity '%s' removed successfully!\n", cities[index-1]);


    for(int i = index-1; i < city_count-1; i++) {
        strcpy(cities[i], cities[i+1]);


        for(int j = 0; j < city_count; j++) {
            distances[i][j] = distances[i+1][j];
        }
    }


    for(int i = 0; i < city_count; i++) {
        for(int j = index-1; j < city_count-1; j++) {
            distances[i][j] = distances[i][j+1];
        }
    }

    city_count--;
}
void displayCities() {
    if(city_count == 0) {
        printf("\nNo cities available!\n");
        return;
    }

    printf("\n========================================\n");
    printf("           CITY LIST\n");
    printf("========================================\n");
    for(int i = 0; i < city_count; i++) {
        printf("%d. %s\n", i+1, cities[i]);
    }
    printf("========================================\n");
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
