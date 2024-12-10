#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h" // Custom stack header
#include <string.h>

// Operator precedence mapping
int get_precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0; // For non-operators like '(' or '{'
}

// Check if a character is an opening bracket
int is_opening_bracket(char c) {
    return c == '(' || c == '{' || c == '[';
}

// Check if a character is a closing bracket
int is_closing_bracket(char c) {
    return c == ')' || c == '}' || c == ']';
}

// Matching bracket pairs
int is_matching_bracket(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '{' && closing == '}') ||
           (opening == '[' && closing == ']');
}

// Perform operation
int perform_operation(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) {
            printf("Error: Division by zero\n");
            exit(EXIT_FAILURE);
        }
        return a / b;
    }
    return 0;
}

// Process operators and update the stacks
void process_operator(IntStack *nums, CharStack *ops) {
    int b = pop(nums);
    int a = pop(nums);
    char op = pop_char(ops);
    push(nums, perform_operation(a, b, op));
}

int main() {
    char s[] = "4 *(0-2*50)";

    IntStack nums;
    CharStack ops;

    init(&nums);
    init_char(&ops);

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];

        if (isspace(c)) {
            continue; // Skip whitespace
        }

        if (isdigit(c)) {
            // Handle numbers (multi-digit)
            int num = 0;
            while (i < strlen(s) && isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            push(&nums, num);
            i--; // Adjust to avoid skipping the next character
        } else if (is_opening_bracket(c)) {
            push_char(&ops, c); // Push the opening bracket
        } else if (is_closing_bracket(c)) {
            // Process until matching opening bracket is found
            while (!isempty_char(&ops) && !is_matching_bracket(peek_char(&ops), c)) {
                process_operator(&nums, &ops);
            }
            if (isempty_char(&ops)) {
                printf("Error: Mismatched brackets\n");
                exit(EXIT_FAILURE);
            }
            pop_char(&ops); // Pop the opening bracket
        } else {
            // Handle operators
            while (!isempty_char(&ops) &&
                   get_precedence(peek_char(&ops)) >= get_precedence(c)) {
                process_operator(&nums, &ops);
            }
            push_char(&ops, c);
        }
    }

    // Process remaining operators in the stack
    while (!isempty_char(&ops)) {
        if (is_opening_bracket(peek_char(&ops))) {
            printf("Error: Mismatched brackets\n");
            exit(EXIT_FAILURE);
        }
        process_operator(&nums, &ops);
    }

    // The final result is the only number left in the stack
    printf("Result: %d\n", peek(&nums));

    return 0;
}
