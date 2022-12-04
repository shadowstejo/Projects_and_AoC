/*
 *  Stephan Jokiel
 *  Maxine Rahlfes
*/

#include "base.h"


/**
Represents a single list node. The string value is dynamically allocated. 
The node is the owner of the value and has to free it when released.
*/
struct Node {
    String value; // dynamically allocated string, release memory!      Wert, der übergegeben wird
    struct Node* next; // self-reference                                Zeiger auf die restliche Liste
};
typedef struct Node Node;

/**
Create a list node. Copies the value (into dynamically allocated storage).
*/
Node* new_node(String value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = s_copy(value); // s_copy performs dynamic allocation
    node->next = next;
    return node;
}

/**
Prints the components of the given list.
*/
void print_list(Node* list) {
    if (list == NULL) {
        printf("[]");
    } else {
        printf("[%s", list->value);
        for (Node* n = list->next; n != NULL; n = n->next) {
            printf(", %s", n->value);
        }
        printf("]");
    }
}

/**
Print list followed by a newline.
*/
void println_list(Node* list) {
    print_list(list);
    printsln("");
}

/**
Return the number of elements in the list.
*/
int length_list(Node* list) {
    if(list == NULL){    
    return 0;
    } else {
        return 1 + length_list(list->next); //fürs jedes mal durch die Liste gehen wird +1 gerechnet?
    }
    
}

/**
Return the element at position.
*/
String get_list(Node* list, int position) {
    require("not negative", position >= 0);
    int i = 0; 
    
    if(list == NULL){
        return "";
        
    } else {
        for(Node* n = list; n != NULL; n = n->next){
             
            if(i == position){
                return n->value;
            } else {
                i ++;
            }
        }
    }
    return NULL;
}

/**
Free all nodes of the list, including the values it contains.
*/
void free_list(Node* list) {

    while (list != NULL){
        Node* x_next = list->next;
        free(list->value);
        free(list);
        list = x_next;
    }
}

/**
Adds an element to the end of the list. Modifies the existing list.
*/
Node* append_list(Node* list, String value) {
    Node *n = new_node(value, NULL);
    Node* list_app = list;

    //printf("value: %s\n", value);

    if(list == NULL){
        list_app = n;
    }
    else{
        while(list->next != NULL){
            list = list->next;
        }
        list->next = n;
    }
    return list_app;
}

// Remove element at position index from list. The element at index has to be deleted.
Node* remove_list(Node* list, int index) {
    if (list == NULL || index < 0) return list;
    if (index == 0) { // remove first element of non-empty list
        Node* n = list->next;
        free(list->value);
        free(list);
        return n;
    }
    // return second or later element of non-empty list
    int i = 0;
    for (Node* node = list; node != NULL; node = node->next) {
        if (i + 1 == index) {
            Node* to_remove = node->next;
            if (to_remove == NULL) return list;
            Node* n = to_remove->next;
            free(to_remove->value);
            free(to_remove);
            node->next = n;
            return list;
        }
        i++;
    }
    return list;
}

/**
Today's menu.
*/
const String menu[] = { "Currywurst", "Spaghetti", "Vegi", "Eintopf", "Salat" };

/**
The number of items on the menu.
*/
const int menu_count = sizeof(menu) / sizeof(char*);

/**
The list of completed food from the kitchen, waiting to be served. Each time a food item is served, the kitchen prepares a new food item randomly from the menu.
*/
Node* food; // List(String)

/**
The list of students standing in line and waiting for food. Each entry contains a string for the food that this student wants.
*/
Node* students; // List(String)

/**
The reputation of the mensa. The player is a staff member of the mensa. The goal of the player is to maximize the
 reputation of the mensa. Actually serving a dish that was asked for increases the reputation of the mensa by 1.
 Serving the wrong dish decreases the reputation by 1. If a student asks for a dish that is on the menu but not
 ready to be served, the reputation of the mensa decreases by 2.
*/
int reputation = 0;


/**
Example output:
fertige Essen: [Spaghetti, Vegi, Salat, Salat, Vegi]
nächster Essenswunsch: Currywurst (3 hungrige Studierende warten)
Reputation der Mensa: 0
> 
*/
void print_situation(void) {
    printf("fertige Essen: ");
    print_list(food);
    printf("\n");
    printf("naechster Essenswunsch: ");
    printf("%s ", get_list(students,0));
    printf("(%d hungrige Studierende warten)\n", length_list(students));
    printf("Reputation der Mensa: %d\n",reputation);
}

/**
Print final message, release all dynamically allocated memory, and exit the program.
Fertig für heute. Die Mensa schließt.
Finale Reputation der Mensa: 3
*/
void finish(void) {

    printf("Fertig fuer heute. Die Mensa schliesst.\n");
    printf("Finale Reputation der Mensa: %d", reputation);

    free_list(food);
    free_list(students);

    food = NULL;
    students = NULL;

    exit(0);
}

/**
Run the mensa simulation.

The mensa person then enters the (0-based) index from the list of food. -1 stands for "not available". -2 ends the program. 

Here is an example dialog:

fertige Essen: [Salat, Vegi, Vegi, Spaghetti, Eintopf]
nächster Essenswunsch: Spaghetti (3 hungrige Studierende warten)
Reputation der Mensa: 0
> 3
Vielen Dank! Ich liebe die Mensa!
fertige Essen: [Salat, Vegi, Vegi, Eintopf, Eintopf]
nächster Essenswunsch: Spaghetti (3 hungrige Studierende warten)
Reputation der Mensa: 1
> -1
Spaghetti ist nicht da? Schade.
fertige Essen: [Salat, Vegi, Vegi, Eintopf, Eintopf]
nächster Essenswunsch: Salat (2 hungrige Studierende warten)
Reputation der Mensa: -1
> 0
Vielen Dank! Ich liebe die Mensa!
fertige Essen: [Vegi, Vegi, Eintopf, Eintopf, Eintopf]
nächster Essenswunsch: Eintopf (2 hungrige Studierende warten)
Reputation der Mensa: 0
> 1
Vegi möchte ich nicht! Ich möchte Eintopf! Dann hole ich mir halt einen Döner!
fertige Essen: [Vegi, Vegi, Eintopf, Eintopf, Eintopf]
nächster Essenswunsch: Currywurst (1 hungrige Studierende warten)
Reputation der Mensa: -1
> 1
Vegi möchte ich nicht! Ich möchte Currywurst! Dann hole ich mir halt einen Döner!
Fertig für heute. Die Mensa schließt.
Reputation der Mensa: -2
*/
void run_mensa(void) {

    food = NULL;

    int k = 0;
    while (k < 5) {
        k++;
        food = append_list(food, menu[i_rnd(5)]);
    }

    students = NULL;

    int l = 0;
    while (l < 3) {
        l++;
        students = append_list(students, menu[i_rnd(5)]);
    }
    //println_list(students);  <- kann uns die essen der studis geben
    print_situation();

    int i;
    while ((i = i_input()) >= -1) {

        char *wunsch = get_list(students, 0);

        if (i == -1) {
            printf("%s ist nicht da? Schade.\n", wunsch);
            reputation -= 2;
            students = remove_list(students, 0);
        } else {
            char *choosen = get_list(food, i);
            bool is_equal = (strcmp(choosen, wunsch) == 0);

            if (is_equal) {
                printf("Vielen Dank! Ich liebe die Mensa!\n");
                reputation++;

                students = remove_list(students, 0);
                students = append_list(students, menu[i_rnd(5)]);

                food = remove_list(food, i);
                append_list(food, menu[i_rnd(5)]);
            } else if (!is_equal) {
                printf("%s mag Ich nicht! Ich will %s\n", choosen, wunsch);
                reputation--;
                students = remove_list(students, 0);
            }
        }
        if (length_list(students) == 0) {
            break;
        }
        print_situation();
    }
    finish();
}

int main(void) {
    report_memory_leaks(true);
    run_mensa();
    return 0;
}
