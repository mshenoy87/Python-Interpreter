/*token.h*/

//
// Token definitions for SimplePy programming language
//
// Originally written by: Prof. Hummel, U. of Illinois Chicago, Spring 2021
// Project 03
//
// DO NOT CHANGE THIS FILE
//

#pragma once

#include <iostream>
#include <istream>
#include <string>

using namespace std;


//
// Token
// 
// A token in the SimplePy programming language
//
struct Token
{
   int     ID;    // TokenID (see enum below)
   string  Value; // the actual token, e.g. literal "123" or identifier "x"
   int     Line;  // line containing the token (1-based)
   int     Col;   // column where the token starts (1-based)

   //
   // overload << so we can output a Token easily
   //
   friend ostream& operator<<(ostream& os, const Token& T);  // defined in token.cpp
};


//
// TokenID
//
// Every token in SimplePy has a unique ID number
//
enum TokenID 
{ 
   UNKNOWN = -1, // a character that is not part of SimplePy
   EOS,          // End-Of-Stream 0
   LEFT_PAREN,   // (1
   RIGHT_PAREN,  // )2
   COMMA,        // ,3
   PLUS,         // +4
   MINUS,        // -5
   MULT,         // *6
   POWER,        // **7
   DIV,          // /8
   MOD,          // %9
   LT,           // <10
   LTE,          // <=11
   GT,           // >12
   GTE,          // >=13
   EQUAL,        // =14
   EQUAL_EQUAL,  // ==15
   NOT_EQUAL,    // !=16
   INT_LITERAL,  // e.g. 123 17
   STR_LITERAL,  // e.g. "hello cs141" 18
   IDENTIFIER,   // e.g. count or print 19
   //
   // keywords:
   //
   IF_KEYW,      // if 20
   ELIF_KEYW,    // elif 21
   ELSE_KEYW,    // else 22
   WHILE_KEYW,   // while 23
   //
   // indentation-related for grouping:
   //
   COLON,        // :
   INDENT,
   UNDENT
};


//
// inputSimplePy
//
// Inputs a SimplePy program from either a file or the keyboard.
// If the filename != "" then we try to open the file and read
// the tokens from there. If filename is "" then we assume keyboard 
// input via cin; the user can simulate EOF on a keyboard via Ctrl-D 
// on Linux or Ctrl-Z then ENTER on Windows.
//
// Pre-condition: filename is "" or a filename containing a 
// SimplePy program.
//
// Post-condition: an array of SimplePy tokens is returned, with 
// numTokens = # of tokens in the array. If a filename was specified
// and the file could not be opened, nullptr is returned with 
// numTokens = 0.
//
Token* inputSimplePy(string filename, int& numTokens);
