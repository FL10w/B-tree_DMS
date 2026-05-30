/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_FLOW_DOCUMENTS_VSC_4754375739857329_GENERATED_SQL_PARSER_HPP_INCLUDED
# define YY_YY_HOME_FLOW_DOCUMENTS_VSC_4754375739857329_GENERATED_SQL_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/sql/sql_parser.y"

    #include "sql/ast.h"
    #include <string>
    #include <vector>

#line 55 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CREATE = 258,                  /* CREATE  */
    DATABASE = 259,                /* DATABASE  */
    DROP = 260,                    /* DROP  */
    USE = 261,                     /* USE  */
    TABLE = 262,                   /* TABLE  */
    INSERT = 263,                  /* INSERT  */
    INTO = 264,                    /* INTO  */
    VALUE = 265,                   /* VALUE  */
    VALUES = 266,                  /* VALUES  */
    UPDATE = 267,                  /* UPDATE  */
    SET = 268,                     /* SET  */
    DELETE = 269,                  /* DELETE  */
    FROM = 270,                    /* FROM  */
    SELECT = 271,                  /* SELECT  */
    WHERE = 272,                   /* WHERE  */
    AS = 273,                      /* AS  */
    INT_T = 274,                   /* INT_T  */
    STRING_T = 275,                /* STRING_T  */
    NOT_NULL = 276,                /* NOT_NULL  */
    INDEXED = 277,                 /* INDEXED  */
    DEFAULT = 278,                 /* DEFAULT  */
    NULL_T = 279,                  /* NULL_T  */
    BETWEEN = 280,                 /* BETWEEN  */
    LIKE = 281,                    /* LIKE  */
    AND = 282,                     /* AND  */
    OR = 283,                      /* OR  */
    COUNT = 284,                   /* COUNT  */
    SUM = 285,                     /* SUM  */
    AVG = 286,                     /* AVG  */
    EQ = 287,                      /* EQ  */
    NE = 288,                      /* NE  */
    LE = 289,                      /* LE  */
    GE = 290,                      /* GE  */
    LT = 291,                      /* LT  */
    GT = 292,                      /* GT  */
    ASSIGN = 293,                  /* ASSIGN  */
    IDENTIFIER = 294,              /* IDENTIFIER  */
    INT_LITERAL = 295,             /* INT_LITERAL  */
    STRING_LITERAL = 296           /* STRING_LITERAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 36 "src/sql/sql_parser.y"

    std::string* text;
    Value* value;
    Operand* operand;
    Expr* expr;
    TableRef* table_ref;
    ColumnDef* column_def;
    std::vector<ColumnDef>* column_defs;
    std::vector<std::string>* identifiers;
    std::vector<Value>* values;
    std::vector<std::vector<Value>>* row_values;
    Assignment* assignment;
    std::vector<Assignment>* assignments;
    SelectItem* select_item;
    std::vector<SelectItem>* select_items;
    Statement* statement;
    FieldType field_type;
    AggregateKind aggregate_kind;

#line 133 "/home/flow/Documents/vsc/4754375739857329/generated/sql_parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_FLOW_DOCUMENTS_VSC_4754375739857329_GENERATED_SQL_PARSER_HPP_INCLUDED  */
