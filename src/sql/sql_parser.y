%code requires {
    #include "sql/ast.h"
    #include <string>
    #include <vector>
}

%{
#include "sql/parser_api.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

int yylex();
void yyerror(const char* message);

typedef struct yy_buffer_state* YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char* text);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern int yylex_destroy();

static Statement* parsedStatement = nullptr;
static std::string parseError;

static Expr* makeBinary(ExprKind kind, Expr* left, Expr* right) {
    auto* expr = new Expr();
    expr->kind = kind;
    expr->lhs.reset(left);
    expr->rhs.reset(right);
    return expr;
}
%}

%union {
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
}

%token CREATE DATABASE DROP USE TABLE INSERT INTO VALUE VALUES UPDATE SET DELETE FROM SELECT WHERE AS
%token INT_T STRING_T NOT_NULL INDEXED DEFAULT NULL_T BETWEEN LIKE AND OR
%token COUNT SUM AVG
%token EQ NE LE GE LT GT ASSIGN
%token <text> IDENTIFIER
%token <value> INT_LITERAL STRING_LITERAL

%type <statement> statement create_database drop_database use_database create_table drop_table insert_statement update_statement delete_statement select_statement
%type <table_ref> table_ref
%type <column_def> column_def column_attrs
%type <column_defs> column_defs
%type <field_type> column_type
%type <identifiers> identifier_list
%type <value> literal
%type <values> literal_list
%type <row_values> insert_rows
%type <assignment> assignment
%type <assignments> assignments
%type <select_item> select_item
%type <select_items> select_list select_item_list
%type <aggregate_kind> aggregate_function
%type <expr> condition disjunction conjunction predicate
%type <operand> operand
%type <text> identifier opt_alias comparison_operator

%start input

%%

input:
    statement optional_semicolon { parsedStatement = $1; }
;

optional_semicolon:
    %empty
  | ';'
;

statement:
    create_database
  | drop_database
  | use_database
  | create_table
  | drop_table
  | insert_statement
  | update_statement
  | delete_statement
  | select_statement
;

create_database:
    CREATE DATABASE identifier {
        auto* statement = new Statement();
        statement->kind = StatementKind::CreateDatabase;
        statement->databaseName = *$3;
        delete $3;
        $$ = statement;
    }
;

drop_database:
    DROP DATABASE identifier {
        auto* statement = new Statement();
        statement->kind = StatementKind::DropDatabase;
        statement->databaseName = *$3;
        delete $3;
        $$ = statement;
    }
;

use_database:
    USE identifier {
        auto* statement = new Statement();
        statement->kind = StatementKind::UseDatabase;
        statement->databaseName = *$2;
        delete $2;
        $$ = statement;
    }
;

create_table:
    CREATE TABLE table_ref '(' column_defs ')' {
        auto* statement = new Statement();
        statement->kind = StatementKind::CreateTable;
        statement->table = std::move(*$3);
        statement->columnDefs = std::move(*$5);
        delete $3;
        delete $5;
        $$ = statement;
    }
;

drop_table:
    DROP TABLE table_ref {
        auto* statement = new Statement();
        statement->kind = StatementKind::DropTable;
        statement->table = std::move(*$3);
        delete $3;
        $$ = statement;
    }
;

insert_statement:
    INSERT INTO table_ref '(' identifier_list ')' value_keyword insert_rows {
        auto* statement = new Statement();
        statement->kind = StatementKind::Insert;
        statement->table = std::move(*$3);
        statement->insertColumns = std::move(*$5);
        statement->insertRows = std::move(*$8);
        delete $3;
        delete $5;
        delete $8;
        $$ = statement;
    }
;

value_keyword:
    VALUE
  | VALUES
;

update_statement:
    UPDATE table_ref SET assignments {
        auto* statement = new Statement();
        statement->kind = StatementKind::Update;
        statement->table = std::move(*$2);
        statement->assignments = std::move(*$4);
        delete $2;
        delete $4;
        $$ = statement;
    }
  | UPDATE table_ref SET assignments WHERE condition {
        auto* statement = new Statement();
        statement->kind = StatementKind::Update;
        statement->table = std::move(*$2);
        statement->assignments = std::move(*$4);
        statement->where.reset($6);
        delete $2;
        delete $4;
        $$ = statement;
    }
;

delete_statement:
    DELETE FROM table_ref {
        auto* statement = new Statement();
        statement->kind = StatementKind::DeleteRows;
        statement->table = std::move(*$3);
        delete $3;
        $$ = statement;
    }
  | DELETE FROM table_ref WHERE condition {
        auto* statement = new Statement();
        statement->kind = StatementKind::DeleteRows;
        statement->table = std::move(*$3);
        statement->where.reset($5);
        delete $3;
        $$ = statement;
    }
;

select_statement:
    SELECT select_list FROM table_ref {
        auto* statement = new Statement();
        statement->kind = StatementKind::SelectRows;
        statement->selectItems = std::move(*$2);
        statement->table = std::move(*$4);
        delete $2;
        delete $4;
        $$ = statement;
    }
  | SELECT select_list FROM table_ref WHERE condition {
        auto* statement = new Statement();
        statement->kind = StatementKind::SelectRows;
        statement->selectItems = std::move(*$2);
        statement->table = std::move(*$4);
        statement->where.reset($6);
        delete $2;
        delete $4;
        $$ = statement;
    }
;

table_ref:
    identifier {
        auto* ref = new TableRef();
        ref->table = *$1;
        delete $1;
        $$ = ref;
    }
  | identifier '.' identifier {
        auto* ref = new TableRef();
        ref->database = *$1;
        ref->table = *$3;
        delete $1;
        delete $3;
        $$ = ref;
    }
;

identifier:
    IDENTIFIER { $$ = $1; }
;

identifier_list:
    identifier {
        auto* list = new std::vector<std::string>();
        list->push_back(*$1);
        delete $1;
        $$ = list;
    }
  | identifier_list ',' identifier {
        $1->push_back(*$3);
        delete $3;
        $$ = $1;
    }
;

column_defs:
    column_def {
        auto* list = new std::vector<ColumnDef>();
        list->push_back(std::move(*$1));
        delete $1;
        $$ = list;
    }
  | column_defs ',' column_def {
        $1->push_back(std::move(*$3));
        delete $3;
        $$ = $1;
    }
;

column_def:
    identifier column_type column_attrs {
        $3->name = *$1;
        $3->type = $2;
        if ($3->indexed) {
            $3->notNull = true;
        }
        delete $1;
        $$ = $3;
    }
;

column_type:
    INT_T { $$ = FieldType::Int; }
  | STRING_T { $$ = FieldType::String; }
;

column_attrs:
    %empty {
        $$ = new ColumnDef();
    }
  | column_attrs NOT_NULL {
        $1->notNull = true;
        $$ = $1;
    }
  | column_attrs INDEXED {
        $1->indexed = true;
        $1->notNull = true;
        $$ = $1;
    }
  | column_attrs DEFAULT literal {
        $1->hasDefault = true;
        $1->defaultValue = std::move(*$3);
        delete $3;
        $$ = $1;
    }
;

insert_rows:
    '(' literal_list ')' {
        auto* rows = new std::vector<std::vector<Value>>();
        rows->push_back(std::move(*$2));
        delete $2;
        $$ = rows;
    }
  | insert_rows ',' '(' literal_list ')' {
        $1->push_back(std::move(*$4));
        delete $4;
        $$ = $1;
    }
;

literal_list:
    literal {
        auto* list = new std::vector<Value>();
        list->push_back(std::move(*$1));
        delete $1;
        $$ = list;
    }
  | literal_list ',' literal {
        $1->push_back(std::move(*$3));
        delete $3;
        $$ = $1;
    }
;

literal:
    INT_LITERAL { $$ = $1; }
  | STRING_LITERAL { $$ = $1; }
  | NULL_T { $$ = new Value(Value::null()); }
;

assignments:
    assignment {
        auto* list = new std::vector<Assignment>();
        list->push_back(std::move(*$1));
        delete $1;
        $$ = list;
    }
  | assignments ',' assignment {
        $1->push_back(std::move(*$3));
        delete $3;
        $$ = $1;
    }
;

assignment:
    identifier ASSIGN literal {
        auto* assignment = new Assignment();
        assignment->column = *$1;
        assignment->value = std::move(*$3);
        delete $1;
        delete $3;
        $$ = assignment;
    }
;

select_list:
    '*' {
        auto* list = new std::vector<SelectItem>();
        SelectItem item;
        item.star = true;
        list->push_back(item);
        $$ = list;
    }
  | select_item_list { $$ = $1; }
;

select_item_list:
    select_item {
        auto* list = new std::vector<SelectItem>();
        list->push_back(std::move(*$1));
        delete $1;
        $$ = list;
    }
  | select_item_list ',' select_item {
        $1->push_back(std::move(*$3));
        delete $3;
        $$ = $1;
    }
;

select_item:
    identifier opt_alias {
        auto* item = new SelectItem();
        item->column = *$1;
        item->alias = *$2;
        delete $1;
        delete $2;
        $$ = item;
    }
  | identifier '.' identifier opt_alias {
        auto* item = new SelectItem();
        item->column = *$3;
        item->alias = *$4;
        delete $1;
        delete $3;
        delete $4;
        $$ = item;
    }
  | aggregate_function '(' '*' ')' opt_alias {
        auto* item = new SelectItem();
        item->aggregate = $1;
        item->aggregateStar = true;
        item->alias = *$5;
        delete $5;
        $$ = item;
    }
  | aggregate_function '(' identifier ')' opt_alias {
        auto* item = new SelectItem();
        item->aggregate = $1;
        item->column = *$3;
        item->alias = *$5;
        delete $3;
        delete $5;
        $$ = item;
    }
  | aggregate_function '(' identifier '.' identifier ')' opt_alias {
        auto* item = new SelectItem();
        item->aggregate = $1;
        item->column = *$5;
        item->alias = *$7;
        delete $3;
        delete $5;
        delete $7;
        $$ = item;
    }
;

opt_alias:
    %empty { $$ = new std::string(); }
  | AS identifier { $$ = $2; }
;

aggregate_function:
    COUNT { $$ = AggregateKind::Count; }
  | SUM { $$ = AggregateKind::Sum; }
  | AVG { $$ = AggregateKind::Avg; }
;

condition:
    disjunction { $$ = $1; }
;

disjunction:
    conjunction { $$ = $1; }
  | disjunction OR conjunction { $$ = makeBinary(ExprKind::Or, $1, $3); }
;

conjunction:
    predicate { $$ = $1; }
  | conjunction AND predicate { $$ = makeBinary(ExprKind::And, $1, $3); }
;

predicate:
    '(' condition ')' { $$ = $2; }
  | operand comparison_operator operand {
        auto* expr = new Expr();
        expr->kind = ExprKind::Compare;
        expr->left = std::move(*$1);
        expr->op = *$2;
        expr->right = std::move(*$3);
        delete $1;
        delete $2;
        delete $3;
        $$ = expr;
    }
  | operand BETWEEN operand AND operand {
        auto* expr = new Expr();
        expr->kind = ExprKind::Between;
        expr->left = std::move(*$1);
        expr->right = std::move(*$3);
        expr->high = std::move(*$5);
        delete $1;
        delete $3;
        delete $5;
        $$ = expr;
    }
  | operand LIKE operand {
        auto* expr = new Expr();
        expr->kind = ExprKind::Like;
        expr->left = std::move(*$1);
        expr->right = std::move(*$3);
        delete $1;
        delete $3;
        $$ = expr;
    }
;

operand:
    literal {
        auto* operand = new Operand(Operand::fromLiteral(std::move(*$1)));
        delete $1;
        $$ = operand;
    }
  | identifier {
        auto* operand = new Operand(Operand::fromColumn(*$1));
        delete $1;
        $$ = operand;
    }
  | identifier '.' identifier {
        auto* operand = new Operand(Operand::fromColumn(*$3));
        delete $1;
        delete $3;
        $$ = operand;
    }
;

comparison_operator:
    EQ { $$ = new std::string("=="); }
  | ASSIGN { $$ = new std::string("="); }
  | NE { $$ = new std::string("!="); }
  | LT { $$ = new std::string("<"); }
  | LE { $$ = new std::string("<="); }
  | GT { $$ = new std::string(">"); }
  | GE { $$ = new std::string(">="); }
;

%%

void yyerror(const char* message) {
    parseError = message ? message : "syntax error";
}

Statement parseSqlStatement(const std::string& source) {
    parsedStatement = nullptr;
    parseError.clear();

    YY_BUFFER_STATE buffer = yy_scan_string(source.c_str());
    int rc = 0;
    try {
        rc = yyparse();
    } catch (...) {
        yy_delete_buffer(buffer);
        yylex_destroy();
        delete parsedStatement;
        parsedStatement = nullptr;
        throw;
    }
    yy_delete_buffer(buffer);
    yylex_destroy();

    if (rc != 0 || !parsedStatement) {
        throw std::runtime_error(parseError.empty() ? "syntax error" : parseError);
    }

    Statement result = std::move(*parsedStatement);
    delete parsedStatement;
    parsedStatement = nullptr;
    return result;
}
