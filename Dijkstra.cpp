//
// Created by roy on 12/18/18.
//

#include "Dijkstra.h"

double dijkstra::calc(string expression, maps* s_maps) {
    vector <string> expression_vec ;
    expression_vec = convert_to_vector(expression, s_maps) ; // convert string expression to vector
    expression_vec = shunting_Yard(expression_vec,s_maps) ;  // execute shunting yard algorithem
    return postFixEva(expression_vec) ;              // return the calculate value of the expression
}

/* This function receive an binary expression as a string
 * and interpret each char to the vector.
 * The function treat with numbers greater than 9 and negative
 * numbers as a char (insert them into the vector together)
 */

vector<string> dijkstra::convert_to_vector(string expression, maps* s_maps) {
    expression = variables_to_double(expression, s_maps) ;
    int index_Count = 1 ;
    char current_char ;
    char next_char ;
    vector <string> parse_expression ;
    string temp_string ;
    expression.push_back('$') ;                      // push a default char for the loop run
    while (index_Count < expression.length()) {
        current_char = expression[index_Count-1] ;   // move the string to interpret string from the vector
        next_char = expression[index_Count];
        temp_string = "" ;// move the next string after it
        temp_string += current_char ;
        if (isdigit(current_char)) {                 // if digit, push to a temp string
            if ((!isdigit(next_char)) && (next_char != '.')) {  // if next is not digit, push the current into the vector
                parse_expression.push_back(temp_string) ;
                index_Count++ ;
            }
            else {
                while ((isdigit(next_char)) || (next_char == '.')) { // if next is digit, read all the next digits
                    // if a '.' has found, insert it to the temp string
                    if (next_char == '.') {
                        temp_string += next_char ;
                        index_Count++ ;
                        next_char = expression[index_Count];
                        continue ;
                    }
                    temp_string.push_back(next_char);// push each digit into the temp string
                    index_Count++;
                    next_char = expression[index_Count];
                    if ((!isdigit(next_char)) && (next_char != '.')) {      // if next is not digit
                        parse_expression.push_back(temp_string); // push the temp string into vector and break
                        index_Count++;
                        temp_string = "" ;
                        break ;
                    }
                }
            }
        }
        else if (s_maps->is_value_in_map("operator_priority_map", temp_string)) {   // if current is an operator
            // deals with expression of '--' and '++'
            if (((current_char == '-') && (next_char == '-')) || ((current_char == '+') && (next_char == '+'))) {
                if (index_Count == 1) {
                    index_Count += 2 ;
                }
                else {
                    parse_expression.push_back("+");
                    index_Count += 2;
                }
            }
            // deals with expression of '-+'
            else if ((current_char == '-') && (next_char == '+')) {
                if (index_Count == 1) {
                    index_Count += 2 ;
                }
                else {
                    parse_expression.push_back("-");
                    index_Count += 2;
                }
            }
            else if ((current_char == '-') && (next_char == '(')) {
                parse_expression.push_back("+") ;
                parse_expression.push_back("(") ;
                parse_expression.push_back("0") ;
                parse_expression.push_back("-") ;
                parse_expression.push_back("(") ;
                int temp_index = index_Count+1 ;
                while(expression[temp_index] != ')') {
                    temp_index++ ;
                }
                temp_string = expression.substr(0, temp_index+1) ;
                if (temp_index+1 < expression.length()) {
                    temp_string += ")" + expression.substr(temp_index + 1, expression.length() - temp_index);
                    expression = temp_string;
                }
                else {
                    expression.push_back(')') ;
                }
                index_Count += 2 ;
                temp_string = "" ;
            }
            else if ((expression[0] == '-') && (index_Count == 1) && (isdigit(next_char))) {
                parse_expression.push_back("(") ;
                parse_expression.push_back("0") ;
                parse_expression.push_back("-") ;
                int temp_index = index_Count+1 ;
                while((expression[temp_index] == '.') || isdigit(expression[temp_index])) {
                    temp_index++ ;
                }
                temp_string = expression.substr(0, temp_index) ;
                if (temp_index+1 < expression.length()) {
                    temp_string += ")" + expression.substr(temp_index, expression.length() - temp_index);
                    expression = temp_string;
                }
                else {
                    expression.erase(expression.length()-1, 1) ;
                    expression.push_back(')') ;
                    expression.push_back('$') ;
                }
                index_Count += 1 ;
                temp_string = "" ;
            }
            // deals with expression of '/-', '*-', '(-' and '+-' which in those cases
            // the '-' sign is refer ut negative and not minus
            else if (((current_char == '/') || (current_char == '*') || (current_char == '(')
                    || (current_char == '+')) && (next_char == '-')) { // check if there is a negative number
                if (isdigit(expression[index_Count + 1])) {
                    parse_expression.push_back(temp_string);
                    temp_string = "";
                    temp_string += '-';
                    temp_string += expression[index_Count + 1] ;
                    index_Count += 2 ;
                    next_char = expression[index_Count] ;
                    while ((isdigit(next_char)) || (next_char == '.')) { // if next is digit, read all the next digits
                        // if a '.' has found, insert it to the temp string
                        if (next_char == '.') {
                            temp_string += next_char;
                            index_Count++;
                            next_char = expression[index_Count];
                            continue;
                        }
                        temp_string.push_back(next_char);// push each digit into the temp string
                        index_Count++;
                        next_char = expression[index_Count];
                        if ((!isdigit(next_char)) && (next_char != '.')) {      // if next is not digit
                            parse_expression.push_back(temp_string); // push the temp string into vector and break
                            index_Count++;
                            temp_string = "";
                            break;
                        }
                    }
                }
            }

            // deals with expression of '/+' and '*+' which in this case the '+' is unnecessary
            else if (((current_char == '/') || (current_char == '*')) && (next_char == '+')) {
                parse_expression.push_back(temp_string) ;
                index_Count+= 2 ;
            }
            else {  // push an operator into the vector
                parse_expression.push_back(temp_string) ;
                index_Count++ ;
            }
        }
        else {
            if (isalpha(current_char)) { // if first char is a alpha, it is a variable
                // while the next letter is an alpha/digit/'_'
                while((isalpha(next_char)) || isdigit(next_char) || (next_char == '_')) {
                    temp_string += next_char ; // push it into temp string
                    index_Count++ ;
                    next_char = expression[index_Count] ;
                }
                index_Count++ ;
                // gets the variable value from it's map
                parse_expression.push_back(to_string(s_maps->get_double(temp_string))) ;
            }
            else { // if the char is not digit/operator/alpha/'_', ignore it
                index_Count++ ;
            }
        }
    }
    return parse_expression ;
}

/* This function implements "Shunting Yard" algorithem,
 * which receives an vector of expressions and returns the expression
 * in a diffrent order which will be easier to calculate.
 */

vector<string> dijkstra::shunting_Yard(vector <string> expression, maps* s_maps) {
    stack <string> symbol_stack ;
    queue <string> out_put ;
        // loop through all the vector
    for (int i = 0 ; i < expression.size() ; i++) {
        // condition for checking if the char is closed bracket
        // if it is, move all the symbol_stack to the ouput queue to reserve
        // the right arithmetic
        if (expression.at(i) == ")") {
            while (symbol_stack.top() != "(") {
                out_put.push(symbol_stack.top()); // push all operator to the queue until "("
                symbol_stack.pop();
            }
            symbol_stack.pop() ; // pop "(" out
            continue ;
        }
        if ((isdigit(expression.at(i)[0])) || ((expression.at(i)[0] == '-') && (isdigit(expression.at(i)[1])))) {
            out_put.push(expression.at(i)) ; // if number, push to queue
        }
        else if (symbol_stack.size() > 0) {  // if symbol_stack is not empty
            if (symbol_stack.top() == "(") {
                symbol_stack.push(expression.at(i)); // if "(" push automatically to the stack
                continue ;
            }
            /* Check if the operator's priority that is checked is less than
             * the priority of the operator that is on top of the stack
             */
            if (s_maps->get_int("operator_priority_map", symbol_stack.top()[0])
                >= s_maps->get_int("operator_priority_map", expression.at(i)[0])) {
                out_put.push(symbol_stack.top());     // if the priority of the operator is greater,
                symbol_stack.pop();                  // pop it and push into the queue
                if (!(symbol_stack.empty())) {
                    while ((s_maps->get_int("operator_priority_map", symbol_stack.top()[0])
                           >= s_maps->get_int("operator_priority_map", expression.at(i)[0])) &&
                           (symbol_stack.top()[0] != '(')) {
                        out_put.push(symbol_stack.top());     // if the priority of the operator is greater,
                        symbol_stack.pop();                  // pop it and push into the queue
                    }
                }
                symbol_stack.push(expression.at(i)); // push the low priority operator into stack
            }
            else  {
                symbol_stack.push(expression.at(i)); // if not, push the operator to stack
            }
        }
        else {
            symbol_stack.push(expression.at(i)) ; // if the stack is empty, push the operator
        }
    }
    while (!symbol_stack.empty()) {       // loop to push all operators from stack to queue
        out_put.push(symbol_stack.top()) ; // to reserve the right arithmetic
        symbol_stack.pop() ;
    }
    expression.clear() ;
    while (!out_put.empty()) {            // loop to push all the final order of the right arithmetic
        expression.push_back(out_put.front()) ; // from queue to a vector
        out_put.pop() ;
    }
    return expression ;
}

/* This function receives a vector of numbers and operator and calculate
 * each operator in the order the "Shunting Yard" algorithem decided.
 * The function uses the "binaryExpression" operators to calculate each calculation.
 * The function returns the final result of the expression in double type.
 */

double dijkstra::postFixEva(vector <string> expression) {
    stack <string> numbers_stack ;
    map <char, int> symbol_map ;
    symbol_map ['+'] = 0 ;
    symbol_map ['-'] = 1 ;
    symbol_map ['*'] = 2 ;
    symbol_map ['/'] = 3 ;
    enum operators {plus, minus, mul, div};
    int temp_operator ;
    double right_child ;
    double left_child ;

    /* Loop to run through all vector elements
     */
    for (int i = 0 ; i < expression.size() ; i++) {
        // if vector[i] is a number, push to the numberStack
        if ((isdigit(expression.at(i)[0])) || ((expression.at(i)[0] == '-') && (isdigit(expression.at(i)[1])))) {
            numbers_stack.push(expression.at(i)) ;
        }
        else {                                               // if vector[i] is operator
            temp_operator = symbol_map[expression.at(i)[0]] ;  // check which operator it is using the map
            right_child = stod(numbers_stack.top()) ;  // pop out the first number from the stack and cast to double
            numbers_stack.pop() ;
            left_child = stod(numbers_stack.top()) ;   // pop out the second number from the stack and cast to duble
            numbers_stack.pop() ;

            /* Switch Case for each arithmetic operator.
             * For each operator, the algorithem will calculate the result of the left and right childs
             * and push it into the stack.
             */
            switch (temp_operator) {
                case(plus):
                    numbers_stack.push(to_string(left_child+right_child));
                    break ;
                case(minus):
                    numbers_stack.push(to_string(left_child-right_child));
                    break ;
                case(mul):
                    numbers_stack.push(to_string(left_child*right_child));
                    break ;
                case(div):
                    numbers_stack.push(to_string(left_child/right_child));
                    break ;
            }
        }
    }
    return stod(numbers_stack.top()) ;
}

/* This function run through all the expression and finding the variables
 * in the expression.
 * when a variable found, the function replaces the variables name with
 * it's value and
 */

string dijkstra::variables_to_double(string expression, maps* s_maps) {
    int index_count = 0 ;
    char next_char ;
    string temp_variable = "" ;
    string result = "" ;
    while(index_count < expression.length()) { // run throuht all expression
        next_char = expression[index_count+1] ;
        if (isalpha(expression[index_count])) { // if a char is an alphabet
            temp_variable += expression[index_count] ; // insert it to the temp string (variables name)
            // if next char is a part of the name, enter loop
            while((isalpha(next_char)) || isdigit(next_char) || (next_char == '_')) {
                index_count++ ;
                temp_variable += expression[index_count] ; // push it into temp string
                if (index_count+1 == expression.length()) { // if the expression is done
                    break ;
                }
                next_char = expression[index_count+1] ; // add char to the variable's name
            }
            index_count++ ;
            // calling the get function which returns the variable value from the map it located at
            result += to_string(s_maps->get_double(temp_variable)) ;
            temp_variable = "" ;
        }
        else {
            result += expression[index_count] ; // if not a part of the variable's name, keep it
            index_count++ ;
        }
    }
    return result ;
}