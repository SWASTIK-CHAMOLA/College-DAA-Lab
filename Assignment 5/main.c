#include <stdio.h>

// Function to sort activities according to finish time (using simple bubble sort)
void sortActivities(int start[], int finish[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (finish[j] > finish[j + 1]) {
                // Swap finish times
                temp = finish[j];
                finish[j] = finish[j + 1];
                finish[j + 1] = temp;

                // Swap corresponding start times
                temp = start[j];
                start[j] = start[j + 1];
                start[j + 1] = temp;
            }
        }
    }
}

// Function to perform activity selection
void activitySelection(int start[], int finish[], int n) {
    int i, j;

    printf("Following activities are selected:\n");

    // The first activity always gets selected
    i = 0;
    printf("Activity %d (Start: %d, Finish: %d)\n", i + 1, start[i], finish[i]);

    // Consider rest of the activities
    for (j = 1; j < n; j++) {
        // If this activity starts after or when the last selected one finishes
        if (start[j] >= finish[i]) {
            printf("Activity %d (Start: %d, Finish: %d)\n", j + 1, start[j], finish[j]);
            i = j;  // Update i to the last selected activity
        }
    }
}

int main() {
    int n, i;

    printf("Enter number of activities: ");
    scanf("%d", &n);

    int start[n], finish[n];

    printf("Enter start times of activities:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &start[i]);
    }

    printf("Enter finish times of activities:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &finish[i]);
    }

    // Sort activities by finish time
    sortActivities(start, finish, n);

    printf("\nActivities sorted by finish time:\n");
    for (i = 0; i < n; i++) {
        printf("Activity %d: Start = %d, Finish = %d\n", i + 1, start[i], finish[i]);
    }

    printf("\nActivity Selection Problem using Greedy Approach\n\n");
    activitySelection(start, finish, n);

    return 0;
}
