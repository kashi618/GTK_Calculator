#include <gtk/gtk.h>


/* Macros */
#define BUTTON_SPACING 5  // Sets spacing between buttons (try to keep it at 5)
#define BUTTON_SIZE 80    // Sets size of buttons
#define MAX_EQUATION 100  // Maximum amount of operators and digits


/* Function Signatures */
static void activate(GApplication *, gpointer);
static void button_setup(GtkWidget *);
static void create_button(GtkWidget *, char *, int, int, int);
static void button_clicked(GtkWidget *, gpointer);
static void calculate(int [], int);

static int  is_operator(char);
static int  is_empty(char);

static int* get_digits(int *, int);
//static int* get_operators();


/* Structs */
typedef struct {
    // String of current equation
    char eqStr[MAX_EQUATION];
    int eqStrIdx = 0;
    
    // List of digits in current equation
    int* digits;
    int digitsIdx = 0;
    
    // list of operators in current equation
    char* operators;
    int operatorsIdx = 0;

    // Stores if current equation has an operator
    int hasOperator;
    int hasOperatorIdx = 0;
    
    // Result of calculation
    double result;
} CalculatorState;


/* Global variables */
CalculatorState calc;

char calcEq[MAX_EQUATION] = {"\0"};
int  calcIndex = 0;

int  containsOperator = 0;
int  operatorIndex = 0;



/*
int listDigits[MAX_EQUATION];    // List of digits in the current equation
int listOperators[MAX_EQUATION]; // List of operators in the current equation
int listOperatorsIndex = 0, listDigitsIndex = 0;
*/

// Main
int main(int argc, char* argv[]) {
    // Setup GTK
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.github.kashi618.calculator", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}


/*
*  Starts calculator window 
*/
static void activate(GApplication *app, gpointer user_data) {
    GtkWidget *win;

    // Window setup and properties
    win = gtk_application_window_new(GTK_APPLICATION(app));

    gtk_window_set_title(GTK_WINDOW(win), "GTK Calculator");
    gtk_window_set_default_size(GTK_WINDOW(win), 600, 800);
    gtk_window_set_resizable(GTK_WINDOW(win), FALSE);
    gtk_window_set_application(GTK_WINDOW(win), GTK_APPLICATION(app));

    // Calculator Buttons
    GtkWidget *buttonGrid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(buttonGrid), BUTTON_SPACING);
    gtk_grid_set_row_spacing(GTK_GRID(buttonGrid), BUTTON_SPACING);

    button_setup(buttonGrid);

    // Show window
    gtk_window_set_child(GTK_WINDOW(win), buttonGrid);
    gtk_window_present(GTK_WINDOW(win));

} // END activate


/*
*  Sets up calculator button layout and functionality
*/
static void button_setup(GtkWidget *grid) {
    GtkWidget *button;
    int row, col;
    char *keys[4][5] = {
        {"7", "8", "9", "Del", "AC"},
        {"4", "5", "6", "x", "/"},
        {"1", "2", "3", "+", "-"},
        {"0",  "", ".", "=",  ""}
    };

    // Grid of keys
    for (row=0; row<4; row++) {
        for (col=0; col<5; col++) {
            // Skip second part of double grid buttons
            if (row==3 && (col==1 || col==4)) {
                continue;
            }

            button = gtk_button_new_with_label(keys[row][col]);
            gtk_widget_set_size_request(button, BUTTON_SIZE, BUTTON_SIZE);
            g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), NULL);

            // Set size of double grid Keys (0 and =)
            if (row==3 && (col==0 || col==3)) {
                gtk_grid_attach(GTK_GRID(grid), button, col, row, 2, 1);
            }

            // Del and AC keys
            else if (row==0 && col>=3) {
                if (col==3) {
                    gtk_widget_set_margin_end(button, -BUTTON_SPACING/2);
                }
                else { // (col==4)
                    gtk_widget_set_margin_start(button, -BUTTON_SPACING/2);
                }
                gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
            }

            // Regular/single grid keys (digits, operators, decimal)
            else {
                gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
            }
        }
    } // END for loop
} // END button_setup


/*
*  Call back function for when a button is pressed
*/
static void button_clicked(GtkWidget *button, gpointer user_data) {
    const char *label = gtk_button_get_label(GTK_BUTTON(button));
    
    switch (label[0]) {
        case '=':
            if (has_operator(calc) && is_operator(calc.eqStr[eqStrIdx-1])) {
                printf("Cannot end with operator\n");
                break;
            }

            if (containsOperator == 0) {
                printf("Must contain atleast one operator\n");
                break;
            }

            //calculate(calcEq, calcIndex);
            break;

        case 'D':
            if (calcIndex>0) {
                calcIndex--; // Due to string terminator
                printf("Deleted %c\n", calcEq[calcIndex]);                
                calcEq[calcIndex] = '\0';
            }
            else if (containsOperator == 1) {
                if (calcIndex == operatorIndex) {
                    containsOperator = 0;
                }
            }
            else {
                printf("No operations\n");
            }
            break;

        case 'A':
            printf("AC!\n");

            calcEq[0] = '\0';
            calcIndex = 0;
            break;

        default:
            // Checks if starts with operator
            if (calcIndex==0 && is_operator(label[0])) {
                printf("Cannot start with an operator!\n");
                break;
            }

            // Check if operators are repeated
            if (is_operator(calcEq[calcIndex-1]) && is_operator(label[0])) {
                printf("Cannot have multiple operators in a row\n");
                break;
            }

            // Updates when equation has an operator
            if (is_operator(label[0])) containsOperator=1;


            // Increment calcIndex, and set it to input
            calcEq[calcIndex++] = label[0];
            calcEq[calcIndex] = '\0';
    }

    if (label[0] != '=') printf("Current equation: %s\n", calcEq);
}


/*
*  Calculates a string equation
*/
static void calculate(int calcEq[], int calcIndex) {
    printf("Calculating.........\n");

    int *digit = get_digits(calcEq, calcIndex);
}


/*
*  Returns True (1) if a character is an operator
*/
static int is_operator(char x) {
    switch (x) {
        case '+': case '-': case 'x': case '/':
            return 1;
            break;
        default:
            return 0;
    }
}


/*
*  Returns array of digits from a string equation 
*/
static int* get_digits(int* calcEq, int calcIndex) {
    int count = 0;
    
    // Count how many digits there are
    for (int i=0; i<calcIndex; i++) {
        if (!is_operator(calcEq[i])) {
            count++;
        }
    }

    printf("Amount digits: %d\n", count);
    //int listDigit
    //return listDigit;
}



/*
static char* get_operators() {

    
}
*/

static int has_operator(CalculatorState calc) {
    if (calc.operatorIdx) {
         
    }
}
