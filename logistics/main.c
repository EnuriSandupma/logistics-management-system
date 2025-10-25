#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define MAX_NAME_LENGTH 50
#define FUEL_PRICE 310.0

typedef struct {
    char name[20];
    int capacity;
    int rate_per_km;
    int avg_speed;
    int fuel_efficiency;
} Vehicle;

// Delivery record structure
typedef struct {
    int source;
    int destination;
    int weight;
    int vehicle_type;
    float distance;
    float cost;
    float time;
    float profit;
    float customer_charge;
} Delivery;

// Global variables
char cities[MAX_CITIES][MAX_NAME_LENGTH];
int distances[MAX_CITIES][MAX_CITIES];
int city_count = 0;
Delivery deliveries[MAX_DELIVERIES];
int delivery_count = 0;

// Vehicle types
Vehicle vehicles[3] = {
    {"Van", 1000, 60, 12, 12},
    {"Truck", 5000, 40, 50, 6},
    {"Lorry", 10000, 80, 45, 4}
};





// Function prototypes
void displayMenu();
void addCity();
void renameCity();
void removeCity();
void displayCities();
void setDistance();
void displayDistanceTable();
void processDeliveryRequest();
void loadFromFile();
int findCity(char*name);
void clearInputBuffer();
int findLeastCostRoute(int source, int dest);
float calculateDeliveryCost(int distance, int rate, int weight);


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
            case 5:
                setDistance();
                break;
            case 6:
                displayDistanceTable();
                break;
            case 7:
                processDeliveryRequest();
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
void setDistance() {
    if(city_count < 2) {
        printf("\nNeed at least 2 cities to set distance!\n");
        return;
    }

    displayCities();

    int city1, city2, dist;
    printf("\nEnter first city number: ");
    scanf("%d", &city1);
    printf("Enter second city number: ");
    scanf("%d", &city2);
    clearInputBuffer();

    if(city1 < 1 || city1 > city_count || city2 < 1 || city2 > city_count) {
        printf("\nInvalid city number!\n");
        return;
    }

    if(city1 == city2) {
        printf("\nError: Cannot set distance from a city to itself!\n");
        return;
    }

    printf("Enter distance (km): ");
    scanf("%d", &dist);
    clearInputBuffer();

    if(dist < 0) {
        printf("\nError: Distance cannot be negative!\n");
        return;
    }


    distances[city1-1][city2-1] = dist;
    distances[city2-1][city1-1] = dist;

    printf("\nDistance set successfully!\n");
    printf("%s <-> %s: %d km\n", cities[city1-1], cities[city2-1], dist);
}
void displayDistanceTable() {
    if(city_count == 0) {
        printf("\nNo cities available!\n");
        return;
    }

    printf("\n========================================\n");
    printf("        DISTANCE TABLE (km)\n");
    printf("========================================\n");


    printf("%-15s", "");
    for(int i = 0; i < city_count; i++) {
        printf("%-10s", cities[i]);
    }
    printf("\n");


    for(int i = 0; i < city_count; i++) {
        printf("%-15s", cities[i]);
        for(int j = 0; j < city_count; j++) {
            printf("%-10d", distances[i][j]);
        }
        printf("\n");
    }
    printf("========================================\n");
}
void processDeliveryRequest() {
    if(city_count < 2) {
        printf("\nNeed at least 2 cities to process delivery!\n");
        return;
    }

    if(delivery_count >= MAX_DELIVERIES) {
        printf("\nError: Maximum delivery limit reached!\n");
        return;
    }

    displayCities();

    int source, dest, weight, vehicle_type;

    printf("\nEnter source city number: ");
    scanf("%d", &source);
    printf("Enter destination city number: ");
    scanf("%d", &dest);
    clearInputBuffer();

    if(source < 1 || source > city_count || dest < 1 || dest > city_count) {
        printf("\nInvalid city number!\n");
        return;
    }

    if(source == dest) {
        printf("\nError: Source and destination cannot be the same!\n");
        return;
    }

    printf("\nVehicle Types:\n");
    for(int i = 0; i < 3; i++) {
        printf("%d. %s (Capacity: %d kg, Speed: %d km/h, Rate: %d LKR/km)\n",
               i+1, vehicles[i].name, vehicles[i].capacity, vehicles[i].avg_speed, vehicles[i].rate_per_km);
    }

    printf("\nEnter vehicle type (1-3): ");
    scanf("%d", &vehicle_type);
    printf("Enter weight (kg): ");
    scanf("%d", &weight);
    clearInputBuffer();

    if(vehicle_type < 1 || vehicle_type > 3) {
        printf("\nInvalid vehicle type!\n");
        return;
    }

    if(weight > vehicles[vehicle_type-1].capacity) {
        printf("\nError: Weight exceeds vehicle capacity!\n");
        printf("Maximum capacity for %s: %d kg\n", vehicles[vehicle_type-1].name, vehicles[vehicle_type-1].capacity);
        return;
    }

    // Find least cost route
    int min_distance = findLeastCostRoute(source-1, dest-1);

    if(min_distance == 0) {
        printf("\nError: No route available between these cities!\n");
        return;
    }

    // Calculate costs
    float base_cost = calculateDeliveryCost(min_distance, vehicles[vehicle_type-1].rate_per_km, weight);
    float fuel_used = (float)min_distance / vehicles[vehicle_type-1].fuel_efficiency;
    float fuel_cost = fuel_used * FUEL_PRICE;
    float operational_cost = base_cost + fuel_cost;
    float profit = base_cost * 0.25;
    float customer_charge = operational_cost + profit;
    float time = (float)min_distance / vehicles[vehicle_type-1].avg_speed;

    // Store delivery record
    deliveries[delivery_count].source = source - 1;
    deliveries[delivery_count].destination = dest - 1;
    deliveries[delivery_count].weight = weight;
    deliveries[delivery_count].vehicle_type = vehicle_type - 1;
    deliveries[delivery_count].distance = min_distance;
    deliveries[delivery_count].cost = base_cost;
    deliveries[delivery_count].time = time;
    deliveries[delivery_count].profit = profit;
    deliveries[delivery_count].customer_charge = customer_charge;
    delivery_count++;

    // Display results
    printf("\n======================================================\n");
    printf("           DELIVERY COST ESTIMATION\n");
    printf("------------------------------------------------------\n");
    printf("From: %s\n", cities[source-1]);
    printf("To: %s\n", cities[dest-1]);
    printf("Minimum Distance: %d km\n", min_distance);
    printf("Vehicle: %s\n", vehicles[vehicle_type-1].name);
    printf("Weight: %d kg\n", weight);
    printf("------------------------------------------------------\n");
    printf("Base Cost: %.2f LKR\n", base_cost);
    printf("Fuel Used: %.2f L\n", fuel_used);
    printf("Fuel Cost: %.2f LKR\n", fuel_cost);
    printf("Operational Cost: %.2f LKR\n", operational_cost);
    printf("Profit (25%%): %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", customer_charge);
    printf("Estimated Time: %.2f hours\n", time);
    printf("======================================================\n");

    printf("\nDelivery request processed successfully!\n");
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

