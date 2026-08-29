#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int id;
    char name[30];
    float price_per_kg;
} Cake;

// Initial 5 Cakes Menu
Cake menu[10] = {
    {1, "Chocolate Fudge", 1200.0},
    {2, "Red Velvet", 1500.0},
    {3, "Vanilla Berry", 1000.0},
    {4, "Black Forest", 1100.0},
    {5, "Mango Delight", 1300.0}
};
int total_cakes = 5;

float total_sales_today = 0.0;
int manager_pin = 1234;

// Function Declarations
void gotoxy(int x, int y);
void setColor(int color);
void drawBox(int x1, int y1, int x2, int y2);
void loading();
void loadData();
void saveData();
void getMaskedInput(char *str, int max_len);
void showMenu();
void placeOrder();
void addNewCake();
void changeManagerPin();
void addSalesHistory(const char* cake_name, float weight, float total, const char* msg);
void showSalesHistory();

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawBox(int x1, int y1, int x2, int y2) {
    for(int i = x1; i <= x2; i++) {
        gotoxy(i, y1); printf("-");
        gotoxy(i, y2); printf("-");
    }
    for(int i = y1; i <= y2; i++) {
        gotoxy(x1, i); printf("|");
        gotoxy(x2, i); printf("|");
    }
}

void loading() {
    system("cls");
    setColor(13);
    gotoxy(42, 12); printf("Processing Request...");
    gotoxy(35, 14);
    for(int i = 0; i < 30; i++) {
        Sleep(20);
        printf("%c", 219);
    }
}

void loadData() {
    FILE *fp = fopen("bakery_data.txt", "r");
    if (fp == NULL) {
        total_sales_today = 0.0;
        manager_pin = 1234;
        saveData();
    } else {
        fscanf(fp, "%f %d", &total_sales_today, &manager_pin);
        fclose(fp);
    }
}

void saveData() {
    FILE *fp = fopen("bakery_data.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%.2f %d", total_sales_today, manager_pin);
        fclose(fp);
    }
}

void getMaskedInput(char *str, int max_len) {
    char ch;
    int i = 0;
    while(1) {
        ch = getch();
        if(ch == 13) break;
        else if(ch == 8) {
            if(i > 0) {
                i--;
                printf("\b \b");
            }
        } else if(isdigit(ch) && i < max_len) {
            str[i++] = ch;
            printf("*");
        }
    }
    str[i] = '\0';
}

void addSalesHistory(const char* cake_name, float weight, float total, const char* msg) {
    FILE *fp = fopen("sales_history.txt", "a");
    if (fp != NULL) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        fprintf(fp, "%02d/%02d/%04d %02d:%02d | %-15s | %.1f Kg | BTD %7.2f | Msg: %s\n",
                t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
                t->tm_hour, t->tm_min, cake_name, weight, total, msg);
        fclose(fp);
    }
}

void showMenu() {
    system("cls");
    setColor(14);
    drawBox(12, 2, 88, 22);
    gotoxy(36, 4); printf("--- CAKE MENU & PRICES ---");
    setColor(15);
    gotoxy(18, 7);  printf("ID   Cake Flavor             Price (Per Kg)");
    gotoxy(18, 8);  printf("-------------------------------------------");
    for(int i = 0; i < total_cakes; i++) {
        gotoxy(18, 9 + i);
        printf("%-4d %-23s BTD %.2f", menu[i].id, menu[i].name, menu[i].price_per_kg);
    }
    setColor(13);
    gotoxy(25, 20); printf("Press any key to return to Main Menu...");
    getch();
}

void placeOrder() {
    system("cls");
    setColor(14);
    drawBox(10, 2, 90, 24);
    gotoxy(38, 4); printf("--- PLACE YOUR CAKE ORDER ---");

    setColor(15);
    int item_id;
    float weight;
    char custom_msg[35];

    gotoxy(15, 7); printf("Enter Cake ID (1-%d): ", total_cakes);
    scanf("%d", &item_id);

    if(item_id < 1 || item_id > total_cakes) {
        setColor(12);
        gotoxy(15, 9); printf("Invalid Cake Selection!");
        getch();
        return;
    }

    gotoxy(15, 9); printf("Selected: %s (BTD %.2f / kg)", menu[item_id-1].name, menu[item_id-1].price_per_kg);
    gotoxy(15, 11); printf("Enter Weight in Kg (e.g., 1.5): ");
    scanf("%f", &weight);

    if(weight <= 0) {
        setColor(12);
        gotoxy(15, 13); printf("Invalid Weight!");
        getch();
        return;
    }

    fflush(stdin);
    gotoxy(15, 13); printf("Enter Message on Cake: ");
    fgets(custom_msg, sizeof(custom_msg), stdin);
    custom_msg[strcspn(custom_msg, "\n")] = 0;

    // Discount check logic
    float raw_total = menu[item_id-1].price_per_kg * weight;
    float discount = 0.0;

    if(raw_total >= 3000.0) {
        discount = raw_total * 0.10; // 10% Discount on orders over 3000 BTD
    }

    float final_bill = raw_total - discount;

    loading();
    system("cls");
    setColor(10);
    drawBox(20, 3, 80, 22);
    gotoxy(41, 5); printf("--- INVOICE RECEIPT ---");
    setColor(15);
    gotoxy(25, 8);  printf("Cake Item     : %s", menu[item_id-1].name);
    gotoxy(25, 10); printf("Weight        : %.1f Kg", weight);
    gotoxy(25, 12); printf("Custom Text   : \"%s\"", strlen(custom_msg) > 0 ? custom_msg : "None");
    gotoxy(25, 14); printf("Subtotal      : BTD %.2f", raw_total);
    gotoxy(25, 16); printf("Discount (10%%): BTD %.2f", discount);
    gotoxy(25, 18); printf("Net Payable   : BTD %.2f", final_bill);

    total_sales_today += final_bill;
    saveData();
    addSalesHistory(menu[item_id-1].name, weight, final_bill, strlen(custom_msg) > 0 ? custom_msg : "N/A");

    setColor(14);
    gotoxy(28, 20); printf("Order Placed Successfully! Press key...");
    getch();
}

void addNewCake() {
    system("cls");
    setColor(12);
    gotoxy(25, 5); printf("Manager Access Required!");
    gotoxy(25, 7); printf("Enter 4-digit PIN: ");
    char pin_str[10];
    getMaskedInput(pin_str, 4);

    if(atoi(pin_str) != manager_pin) {
        setColor(12);
        gotoxy(25, 9); printf("Wrong PIN! Access Denied.");
        getch();
        return;
    }

    if(total_cakes >= 10) {
        setColor(12);
        gotoxy(25, 11); printf("Menu is full! Cannot add more items.");
        getch();
        return;
    }

    system("cls");
    setColor(11);
    drawBox(20, 5, 80, 18);
    gotoxy(35, 7); printf("--- ADD NEW CAKE ITEM ---");
    setColor(15);

    menu[total_cakes].id = total_cakes + 1;
    gotoxy(25, 10); printf("Enter Cake Name: ");
    fflush(stdin);
    fgets(menu[total_cakes].name, 30, stdin);
    menu[total_cakes].name[strcspn(menu[total_cakes].name, "\n")] = 0;

    gotoxy(25, 12); printf("Enter Price Per Kg: ");
    scanf("%f", &menu[total_cakes].price_per_kg);

    total_cakes++;
    setColor(10);
    gotoxy(25, 15); printf("New Cake Added to Menu Successfully!");
    getch();
}

void changeManagerPin() {
    system("cls");
    setColor(12);
    gotoxy(25, 5); printf("Enter Current 4-digit PIN: ");
    char pin_str[10];
    getMaskedInput(pin_str, 4);

    if(atoi(pin_str) != manager_pin) {
        setColor(12);
        gotoxy(25, 7); printf("Wrong PIN! Access Denied.");
        getch();
        return;
    }

    gotoxy(25, 9); printf("Enter New 4-digit PIN: ");
    char new_p_str[10];
    getMaskedInput(new_p_str, 4);

    if(strlen(new_p_str) == 4) {
        manager_pin = atoi(new_p_str);
        saveData();
        setColor(10);
        gotoxy(25, 12); printf("Manager PIN Changed Successfully!");
    } else {
        setColor(12);
        gotoxy(25, 12); printf("PIN must be exactly 4 digits!");
    }
    getch();
}

void showSalesHistory() {
    system("cls");
    setColor(12);
    gotoxy(25, 5); printf("Manager Access Required!");
    gotoxy(25, 7); printf("Enter 4-digit PIN: ");
    char pin_str[10];
    getMaskedInput(pin_str, 4);

    if(atoi(pin_str) != manager_pin) {
        setColor(12);
        gotoxy(25, 9); printf("Wrong PIN! Access Denied.");
        getch();
        return;
    }

    system("cls");
    drawBox(5, 3, 95, 24);
    setColor(11);
    gotoxy(38, 5); printf("--- SALES & ORDER HISTORY ---");
    setColor(15);

    FILE *fp = fopen("sales_history.txt", "r");
    if (fp == NULL) {
        gotoxy(32, 11); printf("No order history found!");
    } else {
        char line[120];
        int y = 8;
        while (fgets(line, sizeof(line), fp) && y <= 19) {
            gotoxy(8, y++);
            printf("%s", line);
        }
        fclose(fp);
    }

    setColor(10);
    gotoxy(10, 21); printf("Total Revenue Generated Today: BTD %.2f", total_sales_today);
    setColor(14);
    gotoxy(25, 23); printf("Press any key to return to Main Menu...");
    getch();
}

int main() {
    int choice;
    time_t start_time, end_time;

    loadData();
    system("title SWEET DELIGHTS BAKERY - POS SYSTEM");
    system("mode con: cols=100 lines=30");

    time(&start_time);

    while(1) {
        system("cls");
        setColor(13);
        drawBox(10, 2, 90, 25);
        gotoxy(34, 4); printf("=== MEGHNA CAKE SHOP ===");

        setColor(15);
        // Clean 6-Option UI Alignment
        gotoxy(15, 8);  printf("1. View Cake Menu");
        gotoxy(15, 11); printf("2. Place New Order");
        gotoxy(15, 14); printf("3. Add New Item (Manager)");

        gotoxy(55, 8);  printf("4. Sales History (Manager)");
        gotoxy(55, 11); printf("5. Change Manager PIN");
        gotoxy(55, 14); printf("6. Exit System");

        gotoxy(15, 19); printf("Select Option: ");

        // Non-blocking inactivity timeout (60 seconds)
        while(1) {
            time(&end_time);
            if(difftime(end_time, start_time) > 60) {
                system("cls");
                setColor(12);
                printf("\n\n\t\tSystem Session Timeout due to inactivity!\n");
                saveData();
                getch();
                return 0;
            }
            if(kbhit()) {
                scanf("%d", &choice);
                break;
            }
            Sleep(100);
        }

        time(&start_time);

        switch(choice) {
            case 1:
                showMenu();
                break;

            case 2:
                placeOrder();
                break;

            case 3:
                addNewCake();
                break;

            case 4:
                showSalesHistory();
                break;

            case 5:
                changeManagerPin();
                break;

            case 6:
                saveData();
                system("cls");
                setColor(14);
                printf("\n\n\t\tThank you for using Sweet Delights POS. Goodbye!\n");
                Sleep(1500);
                return 0;

            default:
                setColor(12);
                printf("\n\tInvalid Option!");
                Sleep(1000);
        }
    }
    return 0;
}
