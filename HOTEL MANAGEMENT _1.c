#include <stdio.h>
#include <string.h>
#define MAX_ROOMS 5
#define MAX_USERS 100
#define MAX_FOOD 5
// ---------------- STRUCTURES ----------------
struct Room {
    int roomNo;
    char category[30];
    float ratePerDay;
    int status;
};
struct User {
    char name[50], id[20], contact[11], password[7];
    int bookedRoom;
    char checkIn[11], checkOut[11];
    int noOfDays;
    float foodBill, roomService, roomCharge, totalBill;
};
struct Food {
    int foodId;
    char foodName[30];
    float price;
};
// ---------------- ROOM DATA ----------------
struct Room rooms[MAX_ROOMS] = {
    {101, "AC Single Bed", 2000, 1},
    {102, "AC Double Bed", 3000, 1},
    {103, "Non-AC Single Bed", 1200, 1},
    {104, "Non-AC Double Bed", 1800, 1},
    {105, "AC Two Beds", 3500, 1}
};
// ---------------- FOOD MENU ----------------
struct Food foods[MAX_FOOD] = {
    {1, "Burger", 120}, {2, "Pizza", 250}, {3, "Tea", 20},  {4, "Coffee", 40},  {5, "Sandwich", 80}
};
// ---------------- USERS ----------------
struct User users[MAX_USERS];
int userCount = 0;
// ---------------- FUNCTION DECLARATIONS ----------------
void adminPanel();
void userPanel();
void addUser();
void viewRooms();
void viewFoodMenu();
void roomBooking();
void cancelRoom();
void bookedRoom();
void orderFood();
void viewReceipt();
void viewBill();
int validateDate(int d, int m, int y);
int dateToDays(int d, int m, int y);
int findUserById(char id[]);
// ---------------- FIND USER BY ID ----------------
int findUserById(char id[]) {
    int i;
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, id) == 0) {
            return i;
        } }
    return -1;
}
// ---------------- MAIN ----------------
int main() {
    int choice;
    char username[20], password[20];
    while (1) {
        printf("\n========== HOTEL MANAGEMENT SYSTEM ==========\n");
        printf("1. Admin\n");
        printf("2. User\n");
        printf("3. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            // ---------------- ADMIN LOGIN ----------------
            case 1:
                printf("\n========== ADMIN LOGIN ==========\n");
                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Password: ");
                scanf("%s", password);
                if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
                    printf("Login Successful!\n");
                    adminPanel();
                }   else {
                    printf("Invalid Username or Password!\n");
                }
                break;
            // ---------------- USER PANEL ----------------
            case 2:
                userPanel();
                break;
            // ---------------- EXIT ----------------
            case 3:
                printf("Thank You!\n");
                return 0;
            default:
                printf("Invalid Choice!\n");
        }   }  }
// ---------------- ADMIN PANEL ----------------
void adminPanel() {
    int choice;
    while (1) {
        printf("\n========== ADMIN PANEL ==========\n");
        printf("1. Add User\n");
        printf("2. View Rooms\n");
        printf("3. View Food Menu\n");
        printf("4. View Bill\n");
        printf("5. Back\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                viewRooms();
                break;
            case 3:
                viewFoodMenu();
                break;
            case 4:
                viewBill();
                break;
            case 5:
                return;
            default:
                printf("Invalid Choice!\n");
        }  }  }
// ---------------- USER PANEL ----------------
void userPanel() {
    int choice;
    while (1) {
        printf("\n========== USER PANEL ==========\n");
        printf("1. View Rooms\n");
        printf("2. View Food Menu\n");
        printf("3. Book Room\n");
        printf("4. Cancel Room\n");
        printf("5. Booked Room\n");
        printf("6. Order Food\n");
        printf("7. View Receipt\n");
        printf("8. Back\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                viewRooms();
                break;
            case 2:
                viewFoodMenu();
                break;
            case 3:
                roomBooking();
                break;
            case 4:
                cancelRoom();
                break;
            case 5:
                bookedRoom();
                break;
            case 6:
                orderFood();
                break;
            case 7:
                viewReceipt();
                break;
            case 8:
                return;
            default:
                printf("Invalid Choice!\n");
        }  }  }
// ---------------- ADD USER ----------------
void addUser() {
    int i, valid;
    printf("\nEnter Name: ");
    scanf(" %[^\n]", users[userCount].name);
    printf("Enter User ID: ");
    scanf("%s", users[userCount].id);
    // CONTACT VALIDATION
    while (1) {
        valid = 1;
        printf("Enter Contact Number (10 digits): ");
        scanf("%s", users[userCount].contact);
        if (strlen(users[userCount].contact) != 10)
            valid = 0;
        for (i = 0; i < strlen(users[userCount].contact); i++) {
            if (users[userCount].contact[i] < '0' ||   users[userCount].contact[i] > '9') {
                valid = 0;
                break;
            }  }
        if (valid)
            break;
        printf("Invalid Contact Number!\n");
    }
    // PASSWORD VALIDATION
    while (1) {
        valid = 1;
        printf("Enter Password (6 digits): ");
        scanf("%s", users[userCount].password);
        if (strlen(users[userCount].password) != 6)
            valid = 0;
        for (i = 0; i < strlen(users[userCount].password); i++) {
            if (users[userCount].password[i] < '0' ||    users[userCount].password[i] > '9') {
                valid = 0;
                break;
            } }
        if (valid)
            break;
        printf("Invalid Password!\n");
    }
    users[userCount].bookedRoom = -1;
    users[userCount].foodBill = 0;
    users[userCount].roomService = 500;
    users[userCount].roomCharge = 0;
    users[userCount].totalBill = 0;
    printf("User Added Successfully!\n");
    userCount++;
}
// ---------------- VIEW ROOMS ----------------
void viewRooms() {
    int i;
    printf("\n========== ROOM DETAILS ==========\n");
    for (i = 0; i < MAX_ROOMS; i++) {
        printf("\nRoom Number   : %d", rooms[i].roomNo);
        printf("\nCategory      : %s", rooms[i].category);
        printf("\nRate Per Day  : %.2f", rooms[i].ratePerDay);
        printf("\nStatus        : %s\n", rooms[i].status ? "Available" : "Booked");
    }  }
// ---------------- VIEW FOOD MENU ----------------
void viewFoodMenu() {
    int i;
    printf("\n========== FOOD MENU ==========\n");
    for (i = 0; i < MAX_FOOD; i++) {
        printf("%d. %s - %.2f\n", foods[i].foodId, foods[i].foodName, foods[i].price);
    } }
// ---------------- DATE VALIDATION ----------------
int validateDate(int d, int m, int y) {
    if (y < 2024 || y > 2100)
        return 0;
    if (m < 1 || m > 12)
        return 0;
    if (d < 1 || d > 31)
        return 0;
    if ((m == 4 || m == 6 ||
         m == 9 || m == 11) && d > 30)
        return 0;
    if (m == 2) {
        int leap =
            (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        if (leap && d > 29)
            return 0;
        if (!leap && d > 28)
            return 0;
    }
    return 1;
}
// ---------------- DATE TO DAYS ----------------
int dateToDays(int d, int m, int y) {
    int monthDays[] =
        {31,28,31,30,31,30,31,31,30,31,30,31};
    int days = y * 365 + d;
    int i;
    for (i = 0; i < m - 1; i++) {
        days += monthDays[i];
    }
    days += y / 4 - y / 100 + y / 400;
    return days;
}
// ---------------- ROOM BOOKING ----------------
void roomBooking() {
    char userId[20];
    int u, roomNo, i;
    int inD, inM, inY;
    int outD, outM, outY;
    printf("Enter User ID: ");
    scanf("%s", userId);
    u = findUserById(userId);
    if (u == -1) {
        printf("User Not Found!\n");
        return;
    }
    viewRooms();
    printf("\nEnter Room Number: ");
    scanf("%d", &roomNo);
    for (i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i].roomNo == roomNo &&  rooms[i].status == 1) {
            printf("Enter Check-In Date (DD MM YYYY): ");
            scanf("%d %d %d",  &inD, &inM, &inY);
            if (!validateDate(inD, inM, inY)) {
                printf("Invalid Check-In Date!\n");
                return;
            }
            printf("Enter Check-Out Date (DD MM YYYY): ");
            scanf("%d %d %d", &outD, &outM, &outY);
            if (!validateDate(outD, outM, outY)) {
                printf("Invalid Check-Out Date!\n");
                return;
            }
            int inDays = dateToDays(inD, inM, inY);
            int outDays = dateToDays(outD, outM, outY);
            if (outDays <= inDays) {
                printf("Check-Out Date must be greater than Check-In Date!\n");
                return;
            }
            users[u].noOfDays = outDays - inDays;
            sprintf(users[u].checkIn, "%02d/%02d/%04d", inD, inM, inY);
            sprintf(users[u].checkOut, "%02d/%02d/%04d", outD, outM, outY);
            users[u].bookedRoom = roomNo;
            rooms[i].status = 0;
            // AUTOMATIC BILL
            users[u].roomCharge =  rooms[i].ratePerDay * users[u].noOfDays;
            users[u].totalBill = users[u].roomCharge +  users[u].foodBill +  users[u].roomService;
            printf("Room Booked Successfully!\n");
            return;
        }  }
    printf("Room Not Available!\n");
}
// ---------------- CANCEL ROOM ----------------
void cancelRoom() {
    char userId[20];
    int u, i;
    printf("Enter User ID: ");
    scanf("%s", userId);
    u = findUserById(userId);
    if (u == -1) {
        printf("User Not Found!\n");
        return;
    }
    for (i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i].roomNo ==  users[u].bookedRoom) {
            rooms[i].status = 1;
        } }
    users[u].bookedRoom = -1;
    printf("Room Cancelled Successfully!\n");
}
// ---------------- BOOKED ROOM ----------------
void bookedRoom() {
    char userId[20];
    int u;
    printf("Enter User ID: ");
    scanf("%s", userId);
    u = findUserById(userId);
    if (u == -1) {
        printf("User Not Found!\n");
        return;
    }
    if (users[u].bookedRoom == -1) {
        printf("No Room Booked!\n");
        return;
    }
    printf("\nBooked Room Number : %d\n", users[u].bookedRoom);
}
// ---------------- ORDER FOOD ----------------
void orderFood() {
    char userId[20];
    int u, choice, qty;
    float bill = 0;
    printf("Enter User ID: ");
    scanf("%s", userId);
    u = findUserById(userId);
    if (u == -1) {
        printf("User Not Found!\n");
        return;
    }
    viewFoodMenu();
    while (1) {
        printf("Enter Food ID (0 to Stop): ");
        scanf("%d", &choice);
        if (choice == 0)
            break;
        if (choice < 1 || choice > MAX_FOOD) {
            printf("Invalid Food ID!\n");
            continue;
        }
        printf("Enter Quantity: ");
        scanf("%d", &qty);
        bill += foods[choice - 1].price * qty;
    }
    users[u].foodBill += bill;
    // UPDATE BILL
    users[u].totalBill =  users[u].roomCharge +  users[u].foodBill +  users[u].roomService;
    printf("Food Ordered Successfully!\n");
}
// ---------------- VIEW BILL ----------------
void viewBill() {
    char userId[20];
    int u;
    printf("Enter User ID: ");
    scanf("%s", userId);
    u = findUserById(userId);
    if (u == -1) {
        printf("User Not Found!\n");
        return;
    }
    printf("\n========== BILL ==========\n");
    printf("Room Charge : %.2f\n",  users[u].roomCharge);
    printf("Food Bill   : %.2f\n",  users[u].foodBill);
    printf("Room Service: %.2f\n",  users[u].roomService);
    printf("--------------------------\n");
    printf("Total Bill  : %.2f\n",  users[u].totalBill);
}
// ---------------- VIEW RECEIPT ----------------
void viewReceipt() {
    char userId[20];
    int u;
    printf("Enter User ID: ");
    scanf("%s", userId);
    u = findUserById(userId);
    if (u == -1) {
        printf("User Not Found!\n");
        return;
    }
    printf("\n========== HOTEL RECEIPT ==========\n");
    printf("Customer Name : %s\n",  users[u].name);
    printf("User ID       : %s\n",  users[u].id);
    printf("Room Number   : %d\n",  users[u].bookedRoom);
    printf("Check-In Date : %s\n",  users[u].checkIn);
    printf("Check-Out Date: %s\n",  users[u].checkOut);
    printf("No. of Days   : %d\n",  users[u].noOfDays);
    printf("Room Charge   : %.2f\n",users[u].roomCharge);
    printf("Food Bill     : %.2f\n",users[u].foodBill);
    printf("Room Service  : %.2f\n",users[u].roomService);
    printf("-----------------------------------\n");
    printf("TOTAL BILL    : %.2f\n",users[u].totalBill);
    printf("===================================\n");
}


