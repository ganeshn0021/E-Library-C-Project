#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct library {
    char book_name[100];
    char author[100];
    int pages;
    float price;
    int quantity;
};

void display_books(struct library lib[], int count);
void search_by_title(struct library lib[], int count);
void delete_book(struct library lib[], int *count);
void update_book(struct library lib[], int count);
void sort_books(struct library lib[], int count);

int main() {
    struct library lib[MAX];
    int count = 0;
    int input;

    while (1) {
        printf("\n********###### E-LIBRARY MENU #####********\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by Title\n");
        printf("4. Delete a Book\n");
        printf("5. Update Book Information\n");
        printf("6. Sort Books (Title, Author, Price)\n");
        printf("7. Count of Books\n");
        printf("8. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &input);
        getchar();  // Clear newline

        switch (input) {
            case 1:
                if (count >= MAX) {
                    printf("Library is full!\n");
                    break;
                }

                printf("Enter book name: ");
                fgets(lib[count].book_name, sizeof(lib[count].book_name), stdin);
                lib[count].book_name[strcspn(lib[count].book_name, "\n")] = '\0';

                printf("Enter author name: ");
                fgets(lib[count].author, sizeof(lib[count].author), stdin);
                lib[count].author[strcspn(lib[count].author, "\n")] = '\0';

                printf("Enter number of pages: ");
                scanf("%d", &lib[count].pages);

                printf("Enter price: ");
                scanf("%f", &lib[count].price);

                printf("Enter quantity: ");
                scanf("%d", &lib[count].quantity);
                getchar(); // Clear input buffer

                count++;
                printf("Book added successfully.\n");
                break;

            case 2:
                display_books(lib, count);
                break;

            case 3:
                search_by_title(lib, count);
                break;

            case 4:
                delete_book(lib, &count);
                break;

            case 5:
                update_book(lib, count);
                break;

            case 6:
                sort_books(lib, count);
                break;

            case 7:
                printf("Total number of books: %d\n", count);
                break;

            case 8:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

void display_books(struct library lib[], int count) {
    if (count == 0) {
        printf("Library is empty.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nBook %d:\n", i + 1);
        printf("Title: %s\n", lib[i].book_name);
        printf("Author: %s\n", lib[i].author);
        printf("Pages: %d\n", lib[i].pages);
        printf("Price: %.2f\n", lib[i].price);
        printf("Quantity: %d\n", lib[i].quantity);
    }
}

void search_by_title(struct library lib[], int count) {
    char title[100];
    int found = 0;

    printf("Enter book title to search: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    for (int i = 0; i < count; i++) {
        if (strcasecmp(lib[i].book_name, title) == 0) {
            printf("\nBook Found:\n");
            printf("Title: %s\n", lib[i].book_name);
            printf("Author: %s\n", lib[i].author);
            printf("Pages: %d\n", lib[i].pages);
            printf("Price: %.2f\n", lib[i].price);
            printf("Quantity: %d\n", lib[i].quantity);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void delete_book(struct library lib[], int *count) {
    char title[100];
    int found = 0;

    printf("Enter book title to delete: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    for (int i = 0; i < *count; i++) {
        if (strcasecmp(lib[i].book_name, title) == 0) {
            for (int j = i; j < *count - 1; j++) {
                lib[j] = lib[j + 1];
            }
            (*count)--;  // Decrease the count of books
            found = 1;
            printf("Book deleted.\n");
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void update_book(struct library lib[], int count) {
    char title[100];
    int found = 0;

    printf("Enter book title to update: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    for (int i = 0; i < count; i++) {
        if (strcasecmp(lib[i].book_name, title) == 0) {
            printf("Enter new author name: ");
            fgets(lib[i].author, sizeof(lib[i].author), stdin);
            lib[i].author[strcspn(lib[i].author, "\n")] = '\0';

            printf("Enter new number of pages: ");
            scanf("%d", &lib[i].pages);

            printf("Enter new price: ");
            scanf("%f", &lib[i].price);

            printf("Enter new quantity: ");
            scanf("%d", &lib[i].quantity);
            getchar(); // Clear buffer

            printf("Book updated.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void sort_books(struct library lib[], int count) {
    int choice;
    struct library temp;

    printf("Sort by:\n1. Title\n2. Author\n3. Price\nEnter choice: ");
    scanf("%d", &choice);
    getchar(); // clear buffer

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            int cmp = 0;
            if (choice == 1)
                cmp = strcasecmp(lib[i].book_name, lib[j].book_name);
            else if (choice == 2)
                cmp = strcasecmp(lib[i].author, lib[j].author);
            else if (choice == 3)
                cmp = lib[i].price > lib[j].price;

            if (cmp > 0) {
                temp = lib[i];
                lib[i] = lib[j];
                lib[j] = temp;
            }
        }
    }

    printf("Books sorted.\n");
}
