#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LENGTH 50
#define MAX_COUNTRY_LENGTH 30
#define MAX_PLAYERS 100

// Structure to represent a player
typedef struct {
    char name[MAX_NAME_LENGTH];
    char country[MAX_COUNTRY_LENGTH];
    int score;
} Player;

// Function prototypes
void displayMenu();
void addPlayer(Player players[], int *count);
void displayLeaderboard(Player players[], int count);
void mergeSort(Player players[], int left, int right);
void merge(Player players[], int left, int mid, int right);
void generateSampleData(Player players[], int *count);
void saveToFile(Player players[], int count);
void loadFromFile(Player players[], int *count);

int main() {
    Player players[MAX_PLAYERS];
    int playerCount = 0;
    int choice;
    
    printf("=============================================\n");
    printf("    SPORTS EVENT LEADERBOARD SYSTEM\n");
    printf("         USING MERGE SORT ALGORITHM\n");
    printf("=============================================\n\n");
    
    // Load data from file if available
    loadFromFile(players, &playerCount);
    
    do {
        displayMenu();
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addPlayer(players, &playerCount);
                break;
            case 2:
                if(playerCount > 0) {
                    mergeSort(players, 0, playerCount - 1);
                    printf("\nLeaderboard sorted successfully!\n");
                } else {
                    printf("\nNo players to sort!\n");
                }
                break;
            case 3:
                displayLeaderboard(players, playerCount);
                break;
            case 4:
                generateSampleData(players, &playerCount);
                break;
            case 5:
                saveToFile(players, playerCount);
                break;
            case 6:
                loadFromFile(players, &playerCount);
                break;
            case 7:
                printf("\nThank you for using the Sports Leaderboard System!\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
        
        printf("\n");
    } while(choice != 7);
    
    return 0;
}

void displayMenu() {
    printf("=================== MENU ===================\n");
    printf("1. Add New Player\n");
    printf("2. Sort Leaderboard (Merge Sort)\n");
    printf("3. Display Leaderboard\n");
    printf("4. Generate Sample Data\n");
    printf("5. Save Data to File\n");
    printf("6. Load Data from File\n");
    printf("7. Exit\n");
    printf("=============================================\n");
}

void addPlayer(Player players[], int *count) {
    if(*count >= MAX_PLAYERS) {
        printf("\nError: Maximum player limit reached!\n");
        return;
    }
    
    Player newPlayer;
    
    printf("\n--- Add New Player ---\n");
    printf("Enter player name: ");
    getchar(); // Clear input buffer
    fgets(newPlayer.name, MAX_NAME_LENGTH, stdin);
    newPlayer.name[strcspn(newPlayer.name, "\n")] = 0; // Remove newline
    
    printf("Enter player country: ");
    fgets(newPlayer.country, MAX_COUNTRY_LENGTH, stdin);
    newPlayer.country[strcspn(newPlayer.country, "\n")] = 0; // Remove newline
    
    printf("Enter player score: ");
    scanf("%d", &newPlayer.score);
    
    players[*count] = newPlayer;
    (*count)++;
    
    printf("\nPlayer added successfully!\n");
}

void displayLeaderboard(Player players[], int count) {
    if(count == 0) {
        printf("\nNo players in the leaderboard!\n");
        return;
    }
    
    printf("\n================ LEADERBOARD ===============\n");
    printf("Rank  %-25s %-15s Score\n", "Name", "Country");
    printf("---------------------------------------------\n");
    
    for(int i = 0; i < count; i++) {
        // Display medal emojis for top 3
        char medal[10] = "";
        if(i == 0) strcpy(medal, "🥇");
        else if(i == 1) strcpy(medal, "🥈");
        else if(i == 2) strcpy(medal, "🥉");
        
        printf("%-2d%-3s %-25s %-15s %d\n", 
               i + 1, medal, players[i].name, players[i].country, players[i].score);
    }
    printf("=============================================\n");
    
    // Display sorting information
    printf("\nSorting Algorithm: Merge Sort\n");
    printf("Time Complexity: O(n log n)\n");
    printf("Space Complexity: O(n)\n");
}

// Merge Sort implementation
void mergeSort(Player players[], int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        
        // Recursively sort first and second halves
        mergeSort(players, left, mid);
        mergeSort(players, mid + 1, right);
        
        // Merge the sorted halves
        merge(players, left, mid, right);
    }
}

void merge(Player players[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    Player *leftArray = (Player*)malloc(n1 * sizeof(Player));
    Player *rightArray = (Player*)malloc(n2 * sizeof(Player));
    
    // Copy data to temporary arrays
    for(i = 0; i < n1; i++)
        leftArray[i] = players[left + i];
    for(j = 0; j < n2; j++)
        rightArray[j] = players[mid + 1 + j];
    
    // Merge the temporary arrays back into players[left..right]
    i = 0;
    j = 0;
    k = left;
    
    while(i < n1 && j < n2) {
        // Sort in descending order (highest score first)
        if(leftArray[i].score >= rightArray[j].score) {
            players[k] = leftArray[i];
            i++;
        } else {
            players[k] = rightArray[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements of leftArray
    while(i < n1) {
        players[k] = leftArray[i];
        i++;
        k++;
    }
    
    // Copy remaining elements of rightArray
    while(j < n2) {
        players[k] = rightArray[j];
        j++;
        k++;
    }
    
    free(leftArray);
    free(rightArray);
}

void generateSampleData(Player players[], int *count) {
    // Sample player data
    Player samplePlayers[] = {
        {"Michael Johnson", "USA", 95},
        {"Sarah Williams", "UK", 87},
        {"Carlos Rodriguez", "Spain", 92},
        {"Yuki Tanaka", "Japan", 78},
        {"Anna Schmidt", "Germany", 88},
        {"Luca Bianchi", "Italy", 83},
        {"Pierre Dubois", "France", 90},
        {"Emma Chen", "Canada", 85},
        {"David Smith", "Australia", 79},
        {"Maria Garcia", "Mexico", 91}
    };
    
    int sampleCount = sizeof(samplePlayers) / sizeof(samplePlayers[0]);
    
    if(*count + sampleCount > MAX_PLAYERS) {
        printf("\nNot enough space for sample data!\n");
        return;
    }
    
    // Add sample players
    for(int i = 0; i < sampleCount; i++) {
        players[*count] = samplePlayers[i];
        (*count)++;
    }
    
    printf("\nSample data generated successfully! Added %d players.\n", sampleCount);
}

void saveToFile(Player players[], int count) {
    FILE *file = fopen("leaderboard.dat", "wb");
    
    if(file == NULL) {
        printf("\nError: Could not save data to file!\n");
        return;
    }
    
    fwrite(&count, sizeof(int), 1, file);
    fwrite(players, sizeof(Player), count, file);
    
    fclose(file);
    printf("\nData saved to 'leaderboard.dat' successfully!\n");
}

void loadFromFile(Player players[], int *count) {
    FILE *file = fopen("leaderboard.dat", "rb");
    
    if(file == NULL) {
        printf("\nNo saved data found. Starting with empty leaderboard.\n");
        return;
    }
    
    fread(count, sizeof(int), 1, file);
    fread(players, sizeof(Player), *count, file);
    
    fclose(file);
    printf("\nData loaded from 'leaderboard.dat' successfully! Loaded %d players.\n", *count);
}
