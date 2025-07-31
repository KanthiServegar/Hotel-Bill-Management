#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_VEG "menu_veg.txt"
#define FILENAME_NONVEG "menu_nonveg.txt"
#define FILENAME_ICECREAM "menu_icecream.txt"

#define OWNER_USERNAME "owner"
#define OWNER_PASSWORD "dream@123"

typedef struct {
    char itemName[50];
    float price;
} MenuItem;

typedef struct {
    char itemName[50];
    float price;
    int quantity;
} OrderItem;
OrderItem order[100];
int itemCount=0;
void viewOrders();
void login();
void ownerMenu();
void customerMenu();
void addItem(char *filename);
void deleteItem(char *filename);
void displayMenu(char *filename);
void placeOrder();
void displayBill(OrderItem order[], int itemCount);
char* chooseCategory();
void ownerMenuCategory();
void homepage();

int main() {
int choice;
while(1){
    printf("\n\n\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*                            _ _ _ _ _ _ _ __ _ _ _ _ _ _ _ _ _ _                             *\n");
    printf("*                           |                                     |                           *\n");
    printf("*                           |       Welcome to the Grand Hotel    |                           *\n");
    printf("*                           |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|                           *\n*\t\t\t\t\t\t\t\t\t\t\t      *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    
    printf("\n\n1.Login as Restaurant Owner\n");
    printf("2.Login as Customer\n3.Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar(); // consume newline character

switch (choice) {
        case 1:
login();
            ownerMenu();
            break;
        case 2:
            customerMenu();
            break;
        case 3:
                printf("Exiting...\n");
                exit(0); 
        default:
            printf("\nInvalid choice. Please try again.\n");
            login();
    }
}
}



void login() {
    char username[50];
    char password[50];

    printf("\n=======Restaurant Owner Login========\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, OWNER_USERNAME) == 0 && strcmp(password, OWNER_PASSWORD) == 0) {
        ownerMenu();
    } else {
        printf("\nInvalid username or password. Please try again.\n");
        login();
    }


}
void ownerMenu() {
//login();
    int choice;
    printf("\nOwner Menu:\n");
    printf("1. Add Item\n");
    printf("2. Delete Item\n");
    printf("3. Display Menu\n");
    printf("4. Exit to home page\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar(); // consume newline character

    switch (choice) {
        case 1:
        case 2:
        case 3:
            ownerMenuCategory(choice);
            break;
        case 4:
                return;
        default:
            printf("\nInvalid choice. Please try again.\n");
            ownerMenu();
    }
}

void ownerMenuCategory(int choice) {
    char *filename = chooseCategory();
    if (filename == NULL) {
        printf("\nInvalid category. Returning to menu.\n");
        ownerMenu();
        return;
    }

    switch (choice) {
        case 1:
            addItem(filename);
            break;
        case 2:
            deleteItem(filename);
            break;
        case 3:
            displayMenu(filename);
            ownerMenu();
            break;
    }
}

void customerMenu() {
    int choice;
    while(1)
    {
        char *filename;
        int more = 1;
        printf("=====Customer Menu=====\n");
        printf("1.View Menu\n");
        printf("2.Place Order\n");
        printf("3.View Orders\n");
        printf("4.Generate Bill\n");
        printf("5.Provide Feedback\n");
        printf("6.Exit to home page\n");
        printf("enter your choice\n");
        scanf("%d",&choice);
        switch(choice)
        {

    case 1:     
                    filename = chooseCategory();
                    displayMenu(filename);
                    break;
    case 2:
                    placeOrder(filename);
                    break;
    case 3:
                    viewOrders();
                    break;   
    case 4:
                     displayBill(order, itemCount);
                     break;
    case 5:
            break;
    case 6:
            return;
    default:
            printf("invalid choice\n");
            break;


}
}
}

void addItem(char *filename) {
    MenuItem item;
    FILE *fp = fopen(filename, "a");

    if (fp == NULL) {
        perror("\nError opening file");
        return;
    }

    printf("\nEnter item name: ");
    fgets(item.itemName, sizeof(item.itemName), stdin);
    item.itemName[strcspn(item.itemName, "\n")] = '\0'; // remove newline character
    printf("Enter item price: ");
    scanf("%f", &item.price);
    getchar(); // consume newline character

    fprintf(fp, "%s %.2f\n", item.itemName, item.price);
    fclose(fp);

    printf("\nItem added successfully.\n");
    ownerMenu();
}

void deleteItem(char *filename) {
    char itemName[50];
    FILE *fp = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        perror("\nError opening file");
        return;
    }

    printf("\nEnter item name to delete: ");
    fgets(itemName, sizeof(itemName), stdin);
    itemName[strcspn(itemName, "\n")] = '\0'; // remove newline character

    MenuItem item;
    int found = 0;

    while (fscanf(fp, "%49s %f", item.itemName, &item.price) != EOF) {
        if (strcmp(item.itemName, itemName) != 0) {
            fprintf(temp, "%s %.2f\n", item.itemName, item.price);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove(filename);
        rename("temp.txt", filename);
        printf("\nItem deleted successfully.\n");
    } else {
        printf("\nItem not found.\n");
        remove("temp.txt");
    }

    ownerMenu();
}

void displayMenu(char *filename) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        perror("\nError opening file");
        return;
    }

    MenuItem item;
    printf("\nMenu:\n");

    while (fscanf(fp, "%49s %f", item.itemName, &item.price) != EOF) {
        printf("%s - Rs.%.2f\n", item.itemName, item.price);
    }

    fclose(fp);

    if (ftell(fp) == 0) {
        printf("\nMenu is empty.\n");
    }
}

void placeOrder(char *filename) {
    char itemName[50];
    int quantity;
    float total = 0.0;
    int more = 1;
    OrderItem order[100]; // assuming max 100 items in an order
    int itemCount = 0;

    do {
        filename = chooseCategory();
        if (filename == NULL) {
            printf("\nInvalid category. Returning to menu.\n");
            continue;
        }
        displayMenu(filename);
        printf("\nEnter item name to order: ");
        fgets(itemName, sizeof(itemName), stdin);
        itemName[strcspn(itemName, "\n")] = '\0'; // remove newline character
        printf("\nEnter quantity: ");
        scanf("%d", &quantity);
        getchar(); // consume newline character

        FILE *fp = fopen(filename, "r");
        MenuItem item;
        int found = 0;

        if (fp == NULL) {
            perror("\nError opening file");
            return;
        }

        while (fscanf(fp, "%49s %f", item.itemName, &item.price) != EOF) {
            if (strcmp(item.itemName, itemName) == 0) {
                order[itemCount].price = item.price;
                order[itemCount].quantity = quantity;
                strcpy(order[itemCount].itemName, item.itemName);
                itemCount++;
                total += item.price * quantity;
                found = 1;
                break;
            }
        }

        fclose(fp);

        if (found) {
            printf("\nItem added to order.\n");
        } else {
            printf("\nItem not found.\n");
        }

        printf("\nDo you want to order more items from  category? (1 for yes, 0 for no): ");
        scanf("%d", &more);
        getchar(); // consume newline character
    } while (more);

   // displayBill(order, itemCount);
}

void displayBill(OrderItem order[], int itemCount) {
    float total = 0.0;
    printf("\n\nBilling Details:\n");
    printf("------------------------------------------------------------\n");
    printf("Item Name\tQuantity\tUnit Price\tTotalPrice\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < itemCount; i++) {
        float itemTotal = order[i].price * order[i].quantity;
        total += itemTotal;
        printf("%-20s %-10d Rs.%-10.2f Rs.%-10.2f\n", order[i].itemName, order[i].quantity, order[i].price, itemTotal);
    }

    printf("---------------------------------------------------------------\n");
    printf("\nTotal bill amount: Rs.%.2f\n", total);
    printf("---------------------------------------------------------------\n");
    printf("\nThank you for choosing the Grand Hotel!\n");
    printf("\nWe hope to see you again soon!\n");
    exit(0);
}

char* chooseCategory() {
    int choice;
    printf("\nChoose a category:\n");
    printf("1. Veg\n");
    printf("2. Non-Veg\n");
    printf("3. Ice-Cream\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar(); // consume newline character

    switch (choice) {
        case 1:
            return FILENAME_VEG;
        case 2:
            return FILENAME_NONVEG;
        case 3:
            return FILENAME_ICECREAM;
        
        default:
            return NULL;
    }
}
void viewOrders() {
    if (itemCount == 0) {
        printf("\nNo items in the current order.\n");
        return;
    }

    printf("\nCurrent Order Details:\n");
    printf("------------------------------------------------------------\n");
    printf("Item Name\tQuantity\tUnit Price\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < itemCount; i++) {
        printf("%-20s %-10d Rs.%-10.2f\n", order[i].itemName, order[i].quantity, order[i].price);
    }

    printf("------------------------------------------------------------\n");
}
