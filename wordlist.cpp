#include <string>
string dig = "\0040\0021\0022\0023\0024\0025\0026\0027\0028\0029\005";
string ch1 = "\004A\002B\002C\002D\002E\002F\002G\002H\002I\002J\002K\002L\002M\002N\002O\002P\002Q\002R\002S\002T\002U\002V\002W\002X\002Y\002Z";
string ch2 = "\002a\002b\002c\002d\002e\002f\002g\002h\002i\002j\002k\002l\002m\002n\002o\002p\002q\002r\002s\002t\002u\002v\002w\002x\002y\002z\002_\005";
string ch = ch1 + ch2;
string a[][2] = {
    "int", "INT",
    "long", "LONG",
    "short", "SHORT",
    "float", "FLOAT",
    "double", "DOUBLE",
    "char", "CHAR",
    "unsigned", "UNSIGNED",
    "signed", "SIGNED",
    "const", "CONST",
    "void", "VOID",
    "volatile", "VOLATILE",
    "enum", "ENUM",
    "struct", "STRUCT",
    "union", "UNION",
    "if", "IF",
    "else", "ELSE",
    "goto", "GOTO",
    "switch", "SWITCH",
    "case", "CASE",
    "do", "DO",
    "while", "WHILE",
    "for", "FOR",
    "continue", "CONTINUE",
    "break", "BREAK",
    "return", "RETURN",
    "default", "DEFAULT",
    "typedef", "TYPEDEF",
    "auto", "AUTO",
    "register", "REGISTER",
    "extern", "EXTERN",
    "static", "STATIC",
    "sizeof", "SIZEOF",
    "+", "+",
    "-", "-",
    "*", "*",
    "/", "/",
    "%", "%",
    "++", "++",
    "--", "--",
    "==", "==",
    "!=", "!=",
    "<", "<",
    ">", ">",
    ">=", ">=",
    "<=", "<=",
    "&&", "&&",
    "||", "||",
    "!", "!",
    "&", "&",
    "|", "|",
    "^", "^",
    "<<", "<<",
    ">>", ">>",
    "~", "~",
    "=", "=",
    "+=", "+=",
    "-=", "-=",
    "*=", "*=",
    "/=", "/=",
    "%=", "%=", 
    "<<=", "<<=",//
    ">>=", ">>=",//
    "&=", "&=",//
    "^=", "^=",//
    "|=", "|=",//
    "?", "?",
    ":", ":",
    "->", "->",
    "(", "(",
    ")", ")",
    "{", "{",
    "}", "}",
    "[", "[",
    "]", "]",
    "\"", "\"",
    "'", "'",
    "/*", "/*",
    "*/", "*/",
    "//", "//",
    ";", ";",
    ",", ",",
    ".", ".",
    dig + dig + "\001", "NUMBER",
    ch + "\004" + ch + "\002" + dig + "\005\001", "ID",
    "\004 \002\t\002\n\005\001", "BLANK"
}