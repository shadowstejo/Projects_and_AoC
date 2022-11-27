/*
 *  Stephan Jokiel
 *  Maxine Rahlfes
*/

#include "base.h"

/*
    Macro for testing if a condition is valid for all i's in the range of [0, length)].
    e.g.
    int length = 10;
    int x[length];
    
    ensure("Array initialized with 0's", forall_i(length, x[i] == 0));

*/
#define forall_i(length, condition) ({\
   bool result = true;\
   for (int i = 0; i < length; i++) { if (!(condition)) { result = false; break; } }\
   result;\
})


#define STACK_SIZE  10

typedef enum {
	OPERATION, VALUE, EMPTY
} Tag;



typedef struct{
	Tag tag;
	
	union{
		int value;
		char operation;
	};
} StackElement;

typedef struct{
	StackElement elements[STACK_SIZE];
	int stack_pointer;
    int stack_height;
} Stack;

//checks if char c belongs to an operation
bool is_operation(char c){
	return c == '+' || c == '/' || c == '-' || c == '*';
}

//checks wheter c is a digit
bool is_digit(char c){
	return c >= '0' && c <= '9';
}

StackElement make_stack_element(Tag tag){
	StackElement ele;
    ele.tag = tag;
    
	return ele;
} 

StackElement make_value(int value){
	StackElement ele = make_stack_element(VALUE);
    ele.value = value;
	return ele;
}

StackElement make_operation(char operation){
	StackElement ele = make_stack_element(OPERATION);
    ele.operation = operation;
	return ele;
}


bool is_empty(Stack* stack){
	return stack->stack_pointer < 0;
}


void clear_stack(Stack* stack){
    require("pointer nicht Null", stack != NULL); //stack darf nicht auf Speicheradresse 0 zeigen. 
    for (int i = 0; i < STACK_SIZE; i ++){
        stack->elements[i] = make_stack_element(EMPTY); //an iter Steller wird Empty eingefügt
    }
    stack->stack_pointer = -1;
    stack->stack_height = STACK_SIZE;
    ensure("Stack is empty", forall( int i = 0, i < STACK_SIZE, i++, stack->elements[i].tag == EMPTY));
}

void push(StackElement element, Stack* stack){ //es soll ein weiteres Element auf unser Stack gelegt werden, was aber nur geschieht, wenn das Stack noch nicht voll ist (d.h. noch nicht 9 beträgt)
    require_not_null(stack);
	if(stack->stack_pointer < (stack->stack_height - 1)){ // stack_pointer darf höchstens 8 sein, um noch Platz für ein Element zu haben
		stack->stack_pointer++;                             
		stack->elements[stack->stack_pointer] = element;    //an Position Stack_pointer wird ein Elment gesetzt
	}
}

StackElement pop(Stack* stack){ //Elment wird vom STack gelöscht
    require_not_null(stack);
    require("non empty stack", stack->stack_pointer >= 0);
    StackElement ele = stack->elements[stack->stack_pointer ];
    stack->elements[stack->stack_pointer] = make_stack_element(EMPTY);
	stack->stack_pointer--;
	return ele; // returns Element, dass gelöscht wurde ??
}

/* Precondition versus If/else-Verzweigung 
precondtions geben Bescheid, wona der Abreuch der Funktion liegt und an welcher Funktion/Zeile es gebreakt ist
    eine if else Block kann Fehler ebenfalls aussortieren, jedoch gibt es nicht den Ort des Fehlers zurück, was Fehlerfindung erschweren kann. 
*/


void print_stack_element(StackElement ele){
    printc('[');
    switch(ele.tag){
        case VALUE:
            printi(ele.value);
            break;
        case OPERATION:
            printc(ele.operation);
            break;
        default:
            ;
            break;  
    }
        
    printc(']');
    println();
}

void print_stack(Stack* stack, int n) { //Übergeben wird ein Stack, auf dem sich x Elmente befinden, wovon n ausgegeben werden sollen
    require("valid n", n >= 0 && n <= STACK_SIZE); //Precondition 
    require("enough elements on stack", stack->stack_pointer >= n - 1); //übeprüft, ob wir auf dem Stack genug Elmente habe, um n Element auszugeben.
    
    for(int i = 0; i < n; i++) {
        print_stack_element(stack->elements[stack->stack_pointer - i]); //ausgeben von n Elementen, die rückwärts ausgegeben werden (stack_pointer-i)
    }
}
    

void compute(Stack* stack){
    require_not_null(stack);
    require("Expected 2 operands but only got 1", stack->elements[0].tag == VALUE && stack->elements[1].tag == VALUE );
    require("Atleast Three elements", stack->stack_pointer >= 2);
    require("Operator on top of stack", stack->elements[stack->stack_pointer].tag == OPERATION);
    
    StackElement op = pop(stack);
    StackElement a = pop(stack);
    StackElement b = pop(stack);
    StackElement new_value; // warum kann man die Variabel-Deklaration nicht innerhalb Case machen?
                            // Fehlermeldung:"error: a label can only be part of a statement and a declaration is not a statementStackElement new_value"
        switch(op.operation){
            case '+':
                new_value = make_value(b.value + a.value);
                push(new_value, stack);
                break;
            case '-':
                new_value = make_value(b.value - a.value);
                push( new_value, stack);
                break;
            case '*':
                new_value = make_value(b.value * a.value);
                push(new_value, stack);
                break;
            case '/':
                new_value = make_value(b.value / a.value);
                push(new_value, stack);
                break;
        }
} 
 int main (void){	
	Stack stack;
    stack.stack_height = STACK_SIZE;
	clear_stack(&stack); // & = Adresse
	int input_size = 128;	
	char input[input_size];
	
	for(int i = 0; i< input_size; i++){
		input[i] = '\0';
	}
	int input_index = 0;

	int c;
	while((c = getchar()) != 'q'){

		if(c == '\n'){
			for(int i = 0; i< input_index; i++){
                char c = input[i];
                if(is_operation(c)){
                    push(make_operation(c), &stack);
                    print_stack(&stack, stack.stack_pointer + 1);
                    println();
                    compute(&stack);
                    print_stack(&stack, stack.stack_pointer + 1);
                    println();
                }
                else if(is_digit(c)){ // if value
                    int val = 0;        
                    while(is_digit(c)){        //while c = digit 
                       val *= 10;               //wenn neue Zahl dazukommt, wird mal 10 gerechnet 
                       val += c - '0';              //Adition alte Zahl und neues digit 
                       //printf("a: %d, %c\n", val, c);
                       c = 0;                           //c is not a digit -> als Abbruchbedingung 
                       if(is_digit(input[i + 1])){      //wenn nächstes Zeichen in der Eingabe noch ein digit ist, dann wird es zum neuen c deklariert
                           i++;                         //index wird hochgezählt
                           c = input[i];    
                        }
                    }
                    printiln(val);
                    push(make_value(val), &stack);
                }
			}
			for(int i = 0; i< input_size; i++){
				input[i] = '\0';
			}
			input_index = 0;
		}
		else {
			input[input_index] = c;
			input_index++;
		}
	}
	return 0;
}