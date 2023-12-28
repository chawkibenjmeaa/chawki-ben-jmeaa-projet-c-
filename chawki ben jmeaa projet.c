#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct {
    int busId;
    char destination[50];
    int capacity;
    int reservedSeats;
} Bus;

typedef struct {
    int reservationId;
    int busId;
    char passengerName[50];
    int seatNumber;
} Reservation;


void createBus(Bus buses[], int *busCount);
void displayBuses(Bus buses[], int busCount);
void createReservation(Reservation reservations[], int *reservationCount, Bus buses[], int busCount);
void displayReservations(Reservation reservations[], int reservationCount);
void modifyReservation(Reservation reservations[], int reservationCount);


int main() {
    Bus buses[MAX_BUSES];
    Reservation reservations[MAX_RESERVATIONS];
    int busCount = 0;
    int reservationCount = 0;
    int choice;

    do {

        printf("\nE-Bus Application Menu\n");
        printf("1. Create a new bus\n");
        printf("2. Display bus details\n");
        printf("3. Create a new reservation\n");
        printf("4. Display reservation details\n");
        printf("5. Modify reservation details\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createBus(buses, &busCount);
                break;
            case 2:
                displayBuses(buses, busCount);
                break;
            case 3:
                createReservation(reservations, &reservationCount, buses, busCount);
                break;
            case 4:
                displayReservations(reservations, reservationCount);
                break;
            case 5:
                modifyReservation(reservations, reservationCount);
                break;
            case 6:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}


void createBus(Bus buses[], int *busCount) {
    if (*busCount < MAX_BUSES) {
        printf("Enter Bus ID: ");
        scanf("%d", &buses[*busCount].busId);

        printf("Enter Destination: ");
        scanf("%s", buses[*busCount].destination);

        printf("Enter Capacity: ");
        scanf("%d", &buses[*busCount].capacity);

        buses[*busCount].reservedSeats = 0;
        (*busCount)++;

        printf("Bus created successfully.\n");
    } else {
        printf("Error: Maximum number of buses reached.\n");
    }
}

void displayBuses(Bus buses[], int busCount) {
    printf("\nBus Details\n");
    printf("-------------------------------------------------\n");
    printf("Bus ID\tDestination\tCapacity\tReserved Seats\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < busCount; i++) {
        printf("%d\t%s\t\t%d\t\t%d\n", buses[i].busId, buses[i].destination, buses[i].capacity, buses[i].reservedSeats);
    }
}

void createReservation(Reservation reservations[], int *reservationCount, Bus buses[], int busCount) {
    if (*reservationCount < MAX_RESERVATIONS) {
        if (busCount == 0) {
            printf("Error: No buses available. Please create a bus first.\n");
            return;
        }

        printf("Enter Passenger Name: ");
        scanf("%s", reservations[*reservationCount].passengerName);

        printf("Enter Bus ID for Reservation: ");
        scanf("%d", &reservations[*reservationCount].busId);

        if (reservations[*reservationCount].busId < 1 ) {
            printf("Error: Invalid Bus ID.\n");
            return;
        }

        printf("Enter Seat Number: ");
        scanf("%d", &reservations[*reservationCount].seatNumber);

        if (reservations[*reservationCount].seatNumber < 1 || reservations[*reservationCount].seatNumber > buses[reservations[*reservationCount].busId - 1].capacity) {
            printf("Error: Invalid Seat Number.\n");
            return;
        }

        reservations[*reservationCount].reservationId = *reservationCount + 1;
        (*reservationCount)++;
        printf("Reservation created successfully.\n");
    } else {
        printf("Error: Maximum number of reservations reached.\n");
    }
}

void displayReservations(Reservation reservations[], int reservationCount) {
    printf("\nReservation Details\n");
    printf("-------------------------------------------------\n");
    printf("Res ID\tBus ID\tPassenger Name\tSeat Number\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < reservationCount; i++) {
        printf("%d\t%d\t%s\t\t%d\n", reservations[i].reservationId, reservations[i].busId,
               reservations[i].passengerName, reservations[i].seatNumber);
    }
}

void modifyReservation(Reservation reservations[], int reservationCount) {
    if (reservationCount == 0) {
        printf("Error: No reservations available.\n");
        return;
    }

    int resId;
    printf("Enter Reservation ID to modify: ");
    scanf("%d", &resId);

    int index = -1;
    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].reservationId == resId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Reservation not found.\n");
    } else {
        printf("Enter new Seat Number: ");
        scanf("%d", &reservations[index].seatNumber);
        printf("Reservation modified successfully.\n");
    }
}
