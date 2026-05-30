%option noyywrap nounput noinput yylineno never-interactive

%{
#include "sql_parser.hpp"

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>

static std::string upperWord(const char* text) {
    std::string result(text);
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char ch) {
        return static_cast<char>(std::toupper(ch));
    });
    return result;
}

static std::string unquote(const char* text, int length) {
    std::string result;
    for (int i = 1; i + 1 < length; ++i) {
        if (text[i] == '\\' && i + 1 < length - 1) {
            result.push_back(text[++i]);
        } else {
            result.push_back(text[i]);
        }
    }
    return result;
}
%}

%%

[ \t\r\n]+          ;
"--".*              ;
"=="                return EQ;
"!="                return NE;
"<="                return LE;
">="                return GE;
"<"                 return LT;
">"                 return GT;
"="                 return ASSIGN;
";"                 return ';';
","                 return ',';
"."                 return '.';
"("                 return '(';
")"                 return ')';
"*"                 return '*';

\"([^\"\\]|\\.)*\" {
    yylval.value = new Value(Value::text(unquote(yytext, yyleng)));
    return STRING_LITERAL;
}

\'([^\'\\]|\\.)*\' {
    yylval.value = new Value(Value::text(unquote(yytext, yyleng)));
    return STRING_LITERAL;
}

-?[0-9]+ {
    try {
        yylval.value = new Value(Value::integer(std::stoll(yytext)));
    } catch (const std::exception&) {
        throw std::runtime_error(std::string("integer literal is out of range: ") + yytext);
    }
    return INT_LITERAL;
}

[A-Za-z_][A-Za-z0-9_]* {
    const std::string upper = upperWord(yytext);
    if (upper == "CREATE") return CREATE;
    if (upper == "DATABASE") return DATABASE;
    if (upper == "DROP") return DROP;
    if (upper == "USE") return USE;
    if (upper == "TABLE") return TABLE;
    if (upper == "INSERT") return INSERT;
    if (upper == "INTO") return INTO;
    if (upper == "VALUE") return VALUE;
    if (upper == "VALUES") return VALUES;
    if (upper == "UPDATE") return UPDATE;
    if (upper == "SET") return SET;
    if (upper == "DELETE") return DELETE;
    if (upper == "FROM") return FROM;
    if (upper == "SELECT") return SELECT;
    if (upper == "WHERE") return WHERE;
    if (upper == "AS") return AS;
    if (upper == "INT") return INT_T;
    if (upper == "STRING") return STRING_T;
    if (upper == "NOT_NULL") return NOT_NULL;
    if (upper == "INDEXED") return INDEXED;
    if (upper == "DEFAULT") return DEFAULT;
    if (upper == "NULL") return NULL_T;
    if (upper == "BETWEEN") return BETWEEN;
    if (upper == "LIKE") return LIKE;
    if (upper == "AND") return AND;
    if (upper == "OR") return OR;
    if (upper == "COUNT") return COUNT;
    if (upper == "SUM") return SUM;
    if (upper == "AVG") return AVG;

    yylval.text = new std::string(yytext);
    return IDENTIFIER;
}

. {
    throw std::runtime_error(std::string("unexpected character: ") + yytext);
}

%%
