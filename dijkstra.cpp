//
// Created by roy on 12/18/18.
//

#include "dijkstra.h"

double dijkstra::calc(string expression, maps* myMaps) {
    vector <string> expressionVec ;
    expressionVec = convert_to_vector(expression, myMaps) ; // convert string expression to vector
    expressionVec = shunting_Yard(expressionVec,myMaps) ;  // execute shunting yard algorithem
    return postFixEva(expressionVec) ;              // return the calculate value of the expression
}

/* This function receive an binary expression as a string
 * and interpret each char to the vector.
 * The function treat with numbers greater than 9 and negative
 * numbers as a char (insert them into the vector together)
 */

vector<string> dijkstra::convert_to_vector(string expression, maps* myMaps) {
    int index_Count = 1 ;
    char current_char ;
    char next_char ;
    vector <string> parseExpression ;
    string tempString ;
    expression.push_back('$') ;                      // push a default char for the loop run
    while (index_Count < expression.length()) {
        current_char = expression[index_Count-1] ;   // move the string to interpret string from the vector
        next_char = expression[index_Count];
        tempString = "" ;// move the next string after it
        tempString += current_char ;
        if (isdigit(current_char)) {                 // if digit, push to a temp string
            if ((!isdigit(next_char)) && (next_char != '.')) {  // if next is not digit, push the current into the vector
                parseExpression.push_back(tempString) ;
                index_Count++ ;
            }
            else {
                while ((isdigit(next_char)) || (next_char == '.')) { // if next is digit, read all the next digits
                    // if a '.' has found, insert it to the temp string
                    if (next_char == '.') {
                        tempString += next_char ;
                        index_Count++ ;
                        next_char = expression[index_Count];
                        continue ;
                    }
                    tempString.push_back(next_char);// push each digit into the temp string
                    index_Count++;
                    next_char = expression[index_Count];
                    if (!isdigit(next_char)) {      // if next is not digit
                        parseExpression.push_back(tempString); // push the temp string into vector and break
                        index_Count++;
                        tempString = "" ;
                        break ;
                    }
                }
            }
        }
        else if (myMaps->is_value_in_map("operator_priority_map", tempString)) {   // if current is an operator
            // deals with expression of '--' and '++'
            if (((current_char == '-') && (next_char == '-')) || ((current_char == '+') && (next_char == '+'))) {
                parseExpression.push_back("+") ;
                index_Count += 2 ;
            }
            // deals with expression of '-+'
            else if ((current_char == '-') && (next_char == '+')) {
                parseExpression.push_back("-");
                index_Count += 2;
            }
            // deals with expression of '/-', '*-', '(-' and '+-' which in those cases
            // the '-' sign is refer t negative and not minus
            else if (((current_char == '/') || (current_char == '*') || (current_char == '(')
                    || (current_char == '+')) && (next_char == '-')) {                 // check if there is a negative number
                parseExpression.push_back(tempString) ;
                tempString = "" ;
                tempString += '-' ;
                tempString += expression[index_Count+1] ;
                parseExpression.push_back(tempString) ;
                index_Count+= 3 ;
            }
            // deals with expression of '/+' and '*+' which in this case the '+' is unnecessary
            else if (((current_char == '/') || (current_char == '*')) && (next_char == '+')) {
                parseExpression.push_back(tempString) ;
                index_Count+= 2 ;
            }
            else {  // push an operator into the vector
                parseExpression.push_back(tempString) ;
                index_Count++ ;
            }
        }
        else {
            if (isalpha(current_char)) { // if first char is a alpha, it is a variable
                // while the next letter is an alpha/digit/'_'
                while((isalpha(next_char)) || isdigit(next_char) || (next_char == '_')) {
                    tempString += next_char ; // push it into temp string
                    index_Count++ ;
                    next_char = expression[index_Count] ;
                }
                index_Count++ ;
                // gets the variable value from it's map
                parseExpression.push_back(to_string(myMaps->get_double("symbols_tables", tempString))) ;
            }
            else { // if the char is not digit/operator/alpha/'_', ignore it
                index_Count++ ;
            }
        }
    }
    return parseExpression ;
}

/* This function implements "Shunting Yard" algorithem,
 * which receives an vector of expressions and returns the expression
 * in a diffrent order which will be easier to calculate.
 */

vector<string> dijkstra::shunting_Yard(vector <string> expression, maps* myMaps) {
    stack <string> symbolStack ;
    queue <string> outPut ;
        // loop through all the vector
    for (int i = 0 ; i < expression.size() ; i++) {
        // condition for checking if the char is closed bracket
        // if it is, move all the symbolStack to the ouput queue to reserve
        // the right arithmetic
        if (expression.at(i) == ")") {
            while (symbolStack.top() != "(") {
                outPut.push(symbolStack.top()); // push all operator to the queue until "("
                symbolStack.pop();
            }
            symbolStack.pop() ; // pop "(" out
            /*if (symbols[symbolStack.top()[0]] >= symbols[expression.at(i)[0]]) {
                outPut.push(symbolStack.top());     // if the priority of the operator is greater,
                symbolStack.pop();                  // pop it and push into the queue
                symbolStack.push(expression.at(i)); // push the low priority operator into stack
            }*/
            continue ;
        }
        if ((isdigit(expression.at(i)[0])) || ((expression.at(i)[0] == '-') && (isdigit(expression.at(i)[1])))) {
            outPut.push(expression.at(i)) ; // if number, push to queue
        }
        else if (symbolStack.size() > 0) {  // if symbolStack is not empty
            if (symbolStack.top() == "(") {
                symbolStack.push(expression.at(i)); // if "(" push automatically to the stack
                continue ;
            }
            /* Check if the operator's priority that is checked is less than
             * the priority of the operator that is on top of the stack
             */
            if (myMaps->get_int("operator_priority_map", symbolStack.top()[0])
                >= myMaps->get_int("operator_priority_map", expression.at(i)[0])) {
                outPut.push(symbolStack.top());     // if the priority of the operator is greater,
                symbolStack.pop();                  // pop it and push into the queue
                if (!(symbolStack.empty())) {
                    while ((myMaps->get_int("operator_priority_map", symbolStack.top()[0])
                           >= myMaps->get_int("operator_priority_map", expression.at(i)[0])) &&
                           (symbolStack.top()[0] != '(')) {
                        outPut.push(symbolStack.top());     // if the priority of the operator is greater,
                        symbolStack.pop();                  // pop it and push into the queue
                    }
                }
                symbolStack.push(expression.at(i)); // push the low priority operator into stack
            }
            else  {
                symbolStack.push(expression.at(i)); // if not, push the operator to stack
            }
        }
        else {
            symbolStack.push(expression.at(i)) ; // if the stack is empty, push the operator
        }
    }
    while (!symbolStack.empty()) {       // loop to push all operators from stack to queue
        outPut.push(symbolStack.top()) ; // to reserve the right arithmetic
        symbolStack.pop() ;
    }
    expression.clear() ;
    while (!outPut.empty()) {            // loop to push all the final order of the right arithmetic
        expression.push_back(outPut.front()) ; // from queue to a vector
        outPut.pop() ;
    }
    return expression ;
}

/* This function receives a vector of numbers and operator and calculate
 * each operator in the order the "Shunting Yard" algorithem decided.
 * The function uses the "binaryExpression" operators to calculate each calculation.
 * The function returns the final result of the expression in double type.
 */

double dijkstra::postFixEva(vector <string> expression) {
    stack <string> numbersStack ;
    map <char, int> symbolMap ;
    symbolMap ['+'] = 0 ;
    symbolMap ['-'] = 1 ;
    symbolMap ['*'] = 2 ;
    symbolMap ['/'] = 3 ;
    enum operators {plus, minus, mul, div};
    int tempOperator ;
    double rightChild ;
    double leftChild ;

    /* Loop to run through all vector elements
     */
    for (int i = 0 ; i < expression.size() ; i++) {
        // if vector[i] is a number, push to the numberStack
        if ((isdigit(expression.at(i)[0])) || ((expression.at(i)[0] == '-') && (isdigit(expression.at(i)[1])))) {
            numbersStack.push(expression.at(i)) ;
        }
        else {                                               // if vector[i] is operator
            tempOperator = symbolMap[expression.at(i)[0]] ;  // check which operator it is using the map
            rightChild = stod(numbersStack.top()) ;  // pop out the first number from the stack and cast to double
            numbersStack.pop() ;
            leftChild = stod(numbersStack.top()) ;   // pop out the second number from the stack and cast to duble
            numbersStack.pop() ;

            /* Switch Case for each arithmetic operator.
             * For each operator, the algorithem will calculate the result of the left and right childs
             * and push it into the stack.
             */
            switch (tempOperator) {
                case(plus):
                    numbersStack.push(to_string(Plus(Number(leftChild).calculate(), Number(rightChild).calculate()).calculate())) ;
                    break ;
                case(minus):
                    numbersStack.push(to_string(Minus(Number(leftChild).calculate(), Number(rightChild).calculate()).calculate())) ;
                    break ;
                case(mul):
                    numbersStack.push(to_string(Mul(Number(leftChild).calculate(), Number(rightChild).calculate()).calculate())) ;
                    break ;
                case(div):
                    numbersStack.push(to_string(Div(Number(leftChild).calculate(), Number(rightChild).calculate()).calculate())) ;
                    break ;
            }
        }
    }
    return stod(numbersStack.top()) ;
}