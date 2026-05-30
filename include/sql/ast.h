#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

enum class FieldType { Int, String };
enum class ValueKind { Null, Int, String };

struct Value {
    ValueKind kind = ValueKind::Null;
    long long intValue = 0;
    std::shared_ptr<const std::string> stringRef;

    static Value null();
    static Value integer(long long value);
    static Value text(std::string value);
    const std::string& asString() const;
};

struct TableRef {
    std::optional<std::string> database;
    std::string table;
};

struct Operand {
    bool column = false;
    std::string columnName;
    Value literal;

    static Operand fromColumn(std::string name);
    static Operand fromLiteral(Value value);
};

enum class ExprKind { Compare, Between, Like, And, Or };

struct Expr {
    ExprKind kind = ExprKind::Compare;
    Operand left;
    Operand right;
    Operand high;
    std::string op;
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;
};

struct ColumnDef {
    std::string name;
    FieldType type = FieldType::String;
    bool notNull = false;
    bool indexed = false;
    bool hasDefault = false;
    Value defaultValue;
};

enum class AggregateKind { None, Count, Sum, Avg };

struct SelectItem {
    bool star = false;
    bool aggregateStar = false;
    AggregateKind aggregate = AggregateKind::None;
    std::string column;
    std::string alias;
};

struct Assignment {
    std::string column;
    Value value;
};

enum class StatementKind {
    CreateDatabase,
    DropDatabase,
    UseDatabase,
    CreateTable,
    DropTable,
    Insert,
    Update,
    DeleteRows,
    SelectRows,
    Empty
};

struct Statement {
    StatementKind kind = StatementKind::Empty;
    std::string databaseName;
    TableRef table;
    std::vector<ColumnDef> columnDefs;
    std::vector<std::string> insertColumns;
    std::vector<std::vector<Value>> insertRows;
    std::vector<Assignment> assignments;
    std::unique_ptr<Expr> where;
    std::vector<SelectItem> selectItems;
};
