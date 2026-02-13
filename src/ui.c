#include "global.h"
#include "ui.h"
#include "calculate.h"

/*
*  Starts calculator window 
*/
void activate(GApplication *app, gpointer user_data) {
    GtkWidget *win;

    // Window setup and properties
    win = gtk_application_window_new(GTK_APPLICATION(app));

    gtk_window_set_title(GTK_WINDOW(win), "GTK Calculator");
    gtk_window_set_default_size(GTK_WINDOW(win), 600, 800);
    gtk_window_set_resizable(GTK_WINDOW(win), FALSE);
    gtk_window_set_application(GTK_WINDOW(win), GTK_APPLICATION(app));
    
    // Setup calculator state
    calc.digitsIdx = 0;
    calc.operatorsIdx = 0;
    
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
void button_setup(GtkWidget *grid) {
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
void button_clicked(GtkWidget *button, gpointer user_data) {
    const char *label = gtk_button_get_label(GTK_BUTTON(button));
        
    switch (label[0]) {
        // Equals
        case '=':
            // Activates when equation ends with an operator
            if (calc.operatorsIdx > calc.digitsIdx) {
                printf("Cannot end with operator\n");
                break;
            }
            
            // Activates when equation has NO operators
            if (calc.operatorsIdx == 0) {
                printf("Must contain atleast one operator\n");
                break;
            }

            printf("Printing\n");

            //calculate(calcEq, calcIndex);
            break;
        
        // Delete item
        case 'D':
            // Deletes digit
            if (calc.digitsIdx >= calc.operatorsIdx) {
                calc.digits[calc.digitsIdx] = '\0';
                calc.digitsIdx--;
            }
            
            // Deletes operator
            if (calc.digitsIdx == calc.operatorsIdx) {
                calc.operatorsIdx--; 
            }
            
            // Activates when trying to delete nothing
            if (calc.digitsIdx + calc.operatorsIdx == 0) {
                printf("No operators\n"); 
            }
            break;
        
        // Clear equation
        case 'A':
            //clear_equation();
            printf("AC!\n");
            
            break;
        
        // Digits and Operators
        default:
            // Operator entered
            if (is_operator(label[0])) {
                // Activates if an operator is entered first
                if (calc.digitsIdx == 0) {
                    break;
                }
                // Activates if an operator is repeated
                if (calc.operatorsIdx > calc.digitsIdx) {
                    printf("Cannot repeat operators\n");
                    break;
                }
                
                calc.operators[calc.operatorsIdx] = label[0];
                calc.operatorsIdx++;

            }
            // Digit entered 
            else {
                calc.digits[calc.digitsIdx] = atoi(&label[0]);
                calc.digitsIdx++;
            }
    }
    for (int i=0; i<MAX_EQUATION; i++) {
        printf("Digits %d\n", calc.digits[i]);
        printf("Operator %c\n", calc.operators[i]);
    }
}



