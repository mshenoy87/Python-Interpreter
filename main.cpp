//
// Author: Megha Shenoy
// Professor Hummel
// 
// Description: 
// A simple python interpreter using SimplePy module
//  
//

#include <iostream>
#include <string>
#include <cmath>
#include <cctype>

#include "token.h"

using namespace std;

// struct for variable
struct Variable
{
    string Name;
    string Type;
    string Value;
};

struct Result
{
    string Value;
    string Type;  
};


// 
// searchMemIndex()
// 
// Find index in memory to check if a value is a variable
//
int searchMemIndex(Variable memory[], int& NumVars, string searchValue){
    
    for (int i = 0; i <= NumVars; i++){
        if (memory[i].Name == searchValue){
            return i;
        }
    }
    return -1;
}

//
// retrieveElement()
//
// retrieves element value and type from program and stores it as result 
//
Result retrieveElement(Token program[], int& PC, Variable memory[], int& NumVars){
    
    Result result;
        
    // if current element is...
    if (program[PC].ID == TokenID::INT_LITERAL){
        result.Value = program[PC].Value;
        result.Type = "int";
    } else if (program[PC].ID == TokenID::IDENTIFIER){
        for (int i=0; i<NumVars; i++){
        }
        int index = searchMemIndex(memory, NumVars, program[PC].Value);
        if (index >=0){
            result.Value = memory[index].Value;
            result.Type = memory[index].Type;
        }
    } else if (program[PC].ID == TokenID::STR_LITERAL){
        result.Value = program[PC].Value;
        result.Type = "str";
    }
    
    return result;
}

//
// typeFunction()
// 
// function for getting the type function in python
// returns the type of function as a string
//
Result typeFunction(Token program[], int& PC, Variable memory[], int& NumVars){


    PC++;  // pass "type"
    PC++;  // pass "("
    
    Result result;    // result struct
    result = retrieveElement(program, PC, memory, NumVars);    // retrieve element
    
    result.Value = result.Type;    
    result.Type = "str"; 
    
    PC++;  // advance past the string
    PC++; // advance to next element
    
    // return string (type)
    return result;
    
}

// 
// convertToString()
// 
// retrieves element, converts type to string
// returns result
// 
Result convertToString(Token program[], int& PC, Variable memory[], int& NumVars){

    PC++;    
    PC++;    // pass the "(" sign

    Result result;
    result = retrieveElement(program, PC, memory, NumVars);
    result.Type = "str";    // convert TYPE

    PC++;    
    PC++;    // pass ")"
    
    return result;
    
}

//
// convertToInt()
// 
// retrieves element from memory/program
// checks if indexes are digits
// if not a digit, then outputs an error
// otherwise convert to int
//
Result convertToInt(Token program[], int& PC, Variable memory[], int& NumVars){
    PC++;
    PC++;    // pass "("
   
    Result result;
    result = retrieveElement(program, PC, memory, NumVars);
    
    Token var = program[PC];
    string resultValue = result.Value;
    int i;
    for (i=0; i < (int) resultValue.length(); i++){  // check if everything is a digit
        if (!isdigit(resultValue[i])){
            break;                
        }
    }
    if (i == (int)resultValue.length()){
        result.Type = "int";
    } else if (var.ID == TokenID::IDENTIFIER && i != (int)resultValue.length()) {
        cout << "**Error: cannot convert " << var.Value << " containing '" << resultValue;
        cout << "' @ (" << program[PC].Line << ", " << program[PC].Col << ") to 'int'" << endl;
        result.Value = "0";
        result.Type = "int";
    } else if (var.ID == TokenID::STR_LITERAL && i != (int)resultValue.length()){
        cout << "**Error: cannot convert string '" << resultValue;
        cout << "' @ (" << program[PC].Line << ", " << program[PC].Col << ") to 'int'" << endl;
        result.Value = "0";
        result.Type = "int";
    }
    
    PC++;
    PC++;
   
    return result;
}

//
// inputFunction()
// 
// outputs words in parentheses until ")"
// takes an input
// checks if value is an int or string
// stores its value and type
//
Result inputFunction(Token program[], int& PC, Variable memory[], int& NumVars){
    
    PC++;    
    PC++;    // pass the "("
    
    Result result;
    string inputValue;
    
    // print everything until ")"
    while (program[PC].ID != TokenID::RIGHT_PAREN){
        cout << program[PC].Value << " ";
        PC++;
    }  

    // use getline() function
    getline(cin, inputValue);
    result.Value = inputValue;
    
    result.Type = "str";
    
    PC++;
  
    // return result
    return result;
}

//
// evaluateOpString()
// 
// evaluates  <, >, <=, >=, ==, != for STRING
//
int evaluateRelOpString(Result left, Result right, Token& op){
    int resultInt = 0;

    if (op.ID == TokenID::LT) {
        if (left.Value < right.Value){
            resultInt = 1;
        }
    } else if (op.ID == TokenID::LTE){
        if (left.Value <= right.Value){
            resultInt = 1;
        }
    } else if (op.ID == TokenID::GT){
        if (left.Value > right.Value){
            resultInt = 1;
        } 
    } else if (op.ID == TokenID::GTE){
        if (left.Value >= right.Value){
            resultInt = 1;
        }
    } else if (op.ID == TokenID::EQUAL_EQUAL){
        if (left.Value == right.Value){
            resultInt = 1;
        }
    } else if (op.ID == TokenID::NOT_EQUAL){
        if (left.Value != right.Value){
            resultInt = 1;
        }
    }
    return resultInt;
}

//
// evaluateOpInt()
// 
// evaluates  <, >, <=, >=, ==, != for INT
//
int evaluateRelOpInt(int leftIntegerVal, int rightIntegerVal, Token op){
    
    int resultInt = 0;

    if (op.ID == TokenID::LT) {
        if (leftIntegerVal < rightIntegerVal){
            resultInt = 1;
        }
    } else if (op.ID == TokenID::LTE){
        if (leftIntegerVal <= rightIntegerVal){
            resultInt = 1;
        }
    } else if (op.ID == TokenID::GT){
        if (leftIntegerVal > rightIntegerVal){
            resultInt = 1;
        } 
    } else if (op.ID == TokenID::GTE){
        if (leftIntegerVal >= rightIntegerVal){
            resultInt = 1;
        }
    } else if (op.ID == TokenID::EQUAL_EQUAL){
        if (leftIntegerVal == rightIntegerVal){
            resultInt = 1;
        }
    } else if (op.ID == TokenID::NOT_EQUAL){
        if (leftIntegerVal != rightIntegerVal){
            resultInt = 1;
        }
    }
    return resultInt;    
    
    
}

//
// evaluate ()
//
// either <identifier> = <element> <op> <element> or <identifier> = <element> 
// evaluates based on values and performs string concatenation
//
Result evaluate(Token program[], int& PC, Variable memory[], int& NumVars){
    
    // expresions ::= <element> <op> <element>) 
    // element ::= <varname> | <literal>
    // 
    Result result;
    Result left = retrieveElement(program, PC, memory, NumVars);    // Gets left value

    PC++;     // move onto operation value
  
    Token op = program[PC];
    
    //if it is an EXPRESSION
    if (op.ID == TokenID::PLUS || op.ID == TokenID::MINUS || op.ID == TokenID::MULT ||
        op.ID == TokenID::POWER || op.ID == TokenID::DIV || op.ID == TokenID::MOD || 
        op.ID == TokenID::LT || op.ID == TokenID::LTE || op.ID == TokenID::GT || 
        op.ID == TokenID::GTE || op.ID == TokenID::EQUAL_EQUAL || op.ID == TokenID::NOT_EQUAL){
        
        PC++;

        Result right = retrieveElement(program, PC, memory, NumVars);    // store right value

        
        int resultInteger = 0;   
        
        // perform operations in terms of variable operations
        if (left.Type == "int" && right.Type == "int"){  // Math operation
            int leftIntegerVal = stoi(left.Value);
            int rightIntegerVal = stoi(right.Value); 
            
            if (op.ID == TokenID::PLUS){
                resultInteger = leftIntegerVal + rightIntegerVal;
            } else if (op.ID == TokenID::MINUS) {
                resultInteger = leftIntegerVal - rightIntegerVal;
            } else if (op.ID == TokenID::MULT){
                resultInteger = leftIntegerVal * rightIntegerVal;
            } else if (op.ID == TokenID::POWER) {
                int r = static_cast<int>(pow(leftIntegerVal, rightIntegerVal));
                resultInteger= r;
            } else if (op.ID == TokenID::DIV) {
                if (rightIntegerVal != 0){
                    resultInteger = leftIntegerVal / rightIntegerVal;
                }
            } else if (op.ID == TokenID::MOD) {
                if (rightIntegerVal != 0){
                    resultInteger = leftIntegerVal % rightIntegerVal;
                }
            } else if (op.ID == TokenID::LT || op.ID == TokenID::LTE || op.ID == TokenID::GT ||
                       op.ID == TokenID::GTE || op.ID == TokenID::EQUAL_EQUAL || op.ID == TokenID::NOT_EQUAL){
                resultInteger = evaluateRelOpInt(leftIntegerVal, rightIntegerVal, op);
            }
            
            result.Value = to_string(resultInteger);
            result.Type = "int";
            
        } else if (left.Type == "str" && right.Type == "str"){    // string concatenation
            if (op.ID == TokenID::PLUS){
                result.Value = left.Value + right.Value;
                result.Type = "str";
            } else if (op.ID == TokenID::LT || op.ID == TokenID::LTE || op.ID == TokenID::GT ||
                  op.ID == TokenID::GTE || op.ID == TokenID::EQUAL_EQUAL || op.ID == TokenID::NOT_EQUAL){
                resultInteger = evaluateRelOpString(left, right, op);
                result.Value = to_string(resultInteger);
                result.Type = "int";
            }
        } else if (left.Type != right.Type) {    // if both values are not the same 
            cout << "**Error: type error with '" << op.Value;
            cout << "' @ (" << op.Line << ", " << op.Col;
            cout << "), expr is '" << left.Type << "' + '" << right.Type << "'" << endl;
            result.Value = "0";
            result.Type = "int";
        }
        PC++;   // pass right element
    }
    else {   // if not <element> <op> <element>
        result = left;
    } 
    
    return result;
}

// print ()
// 
// print function
//
void printFunction(Token program[], int& PC, Variable memory[], int& NumVars){
    
    PC++;
    PC++; // skip over ")"
    
    while (program[PC].ID != TokenID::RIGHT_PAREN){

        string strName = program[PC].Value;
 
        // create an element for every value in between () for print
        Result element = retrieveElement(program, PC, memory, NumVars);

        // print element value
        if (program[PC].ID == TokenID::COMMA){
            cout << " ";
        } else {
            cout << element.Value;
        }
        PC++;

    }
    cout << endl;
    if (program[PC].ID != TokenID::EOS){
        PC++;
    }

}

//
// executeStmt()
// 
// executes statements line by line based on the identifier 
//
void executeStmt (Token program[], int& PC, Variable memory[], int& NumVars){

 
    if (program[PC].Value == "print"){   // print(___) in python
        printFunction(program, PC, memory, NumVars);

    }
    else {
        
        string varName = program[PC].Value;
 
        PC++;   // pass identifier
 
        PC++;   // pass = or (           
 
        
        // create result struct
        Result result;
        
        if (program[PC].Value == "type"){     // if after "=" is type
            result = typeFunction(program, PC, memory, NumVars);
            
        }
        else if (program[PC].Value == "int") {     // if after "=" is int
            result = convertToInt(program, PC, memory, NumVars);
            
        }
        else if (program[PC].Value == "str") {     // if after "=" is str
            result = convertToString(program, PC, memory, NumVars);
            
        }
        else if (program[PC].Value == "input"){    // if after "=" is input
            result = inputFunction(program, PC, memory, NumVars);
        }
        else {     // if after "=" is not any of the functions, then evaluate expression 
            result = evaluate(program, PC, memory, NumVars);
            
        }
        
        // after everything, search if in memory
        int index = searchMemIndex(memory, NumVars, varName);
        
        if (index < 0){
            memory[NumVars].Name = varName;
            memory[NumVars].Value = result.Value;
            memory[NumVars].Type = result.Type;
            NumVars++;
        } else {
            // save values and type into memory in designated position
            memory[index].Value = result.Value;
            memory[index].Type = result.Type; 
        }
       
    }
}


void conditionalExecution(Token program[],int& PC, Variable memory[], int NumVars){
     PC++;   // for the indent

    while(program[PC].ID != TokenID::UNDENT){
       
        executeStmt(program, PC, memory, NumVars);
        if (program[PC].ID == TokenID::EOS){
            cout << "break" << endl;
            break;
        }    
    }
}

void conditionalNonExecution(Token program[],int& PC, Variable memory[], int NumVars){

    while(program[PC].ID != TokenID::UNDENT){
        if (program[PC].ID == TokenID::EOS){
            cout << "break" << endl;
            break;
        }
        PC++;
    }
}


//
// conditional()
// 
// if-elif-else statements
//
void conditionals(Token program[], int& PC, Variable memory[], int& NumVars, Result& result){

    if (program[PC].ID == TokenID::IF_KEYW || program[PC].ID == TokenID::ELIF_KEYW){
 
        PC++;

       if (stoi(result.Value) != 1){
            result = evaluate(program, PC, memory, NumVars);
            PC++;    // this is for a colon
            if (stoi(result.Value) == 1){
                conditionalExecution(program, PC, memory, NumVars);
            } else {
                conditionalNonExecution(program, PC, memory, NumVars);
            }
       }else{
           conditionalNonExecution(program, PC, memory, NumVars);
       }
    
       if (program[PC].ID != TokenID::EOS){
            PC++;
       }
    } else { // Python's ELSE condition
        if (stoi(result.Value) != 1){

            PC++;
            PC++;

            conditionalExecution(program, PC, memory, NumVars);
            if (program[PC].ID != TokenID::EOS){
                PC++;
            }
        }else{
            conditionalNonExecution(program, PC, memory, NumVars); 
            if (program[PC].ID == TokenID::UNDENT){
                PC++;
            }

        } 
    }
}


// ##################################################################################
//
// main filename memorysize
//
int main(int argc, char* argv[])
{
   // 
   // 1. process command-line args:
   //
   //argv[0] = ./main
   //argv[1] = filename.py
   //argv[2] = memorysize
   //
    if (argc != 3)
    {
        cout << "usage: ./main filename.py memorysize" << endl;
        return 0;
    }

    string filename(argv[1]);  // this is your SimplePy program file
    int MemorySize = stoi(argv[2]);  // this is size for Memory array
        

    //
    // call inputSimplePy to input the SimplePy program, and
    // you'll get back an array of Tokens.  Allocate another array
    // for your memory, and then start executing!
    //
    //cout << filename << endl;    // delete these eventually
    //cout << MemorySize << endl;
    
    
    // create array of tokens from contents of file
    int numTokens;
    int NumVars = 0;
    
    Token* program = inputSimplePy(filename, numTokens);
    Variable* memory = new Variable[MemorySize];
    
    // if file cannot be opened, then print message
    if (numTokens == 0){
        cout << "**Error, unable to open program file '" << filename << "'" << endl;         
    }else{

        int PC = 0;   // program counter

        // loop through array contents
        Result result;
        result.Value = "-1";
        while (program[PC].ID != TokenID::EOS){
            if (program[PC].ID == TokenID::IF_KEYW || program[PC].ID == TokenID::ELIF_KEYW || 
                program[PC].ID == TokenID::ELSE_KEYW){
                
                conditionals(program, PC, memory, NumVars, result);
             } else {
                result.Value = "-1";
                // if statements carrying out actions based on python program
                executeStmt(program, PC, memory, NumVars);
            }
            
        }
    }
    
    delete[] program;  
    delete[] memory;
    
    return 0;
}