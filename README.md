# AlphaCompiler

AlphaCompiler is a program that translates a program written in the Alpha programming language into machine language for a specific machine.

Τhe following 5 roles give a picture of the architecture of Alpha Compiler

1. Lexical Analyzer
2. Syntax Analyzer
3. Semantic Analyzer
4. Intermidiate Code Generator
5. Targer Code Generator

# Lexical Analyzer
Lexical Analyzer is a program that recognizes the elements of language Alpha

Τhe following categories(sets) define the elements of language Alpha

### Keywords
if, else, while, for, function, return, break, continue, and, not, or, local, true, false, nil

### Operators
\+ = - * / % == != ++ -- > < >= <=

### Numbers
Integer, Real

### Strings
"this is a string"

### Punctuations
{ } [ ] ( ) ;  , : :: . ..

### Identifier Names
Definition: letter and then letter or number

### Comments
1. Single line comments: //Comments
2. Block comments: /\*Comment\*/

