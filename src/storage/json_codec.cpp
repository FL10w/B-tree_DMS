#include "storage/json_codec.h"

#include <stdexcept>

#include "core/value_ops.h"

namespace app {

json schemaToJson(const TableSchema& schema) {
    json data;
    data["name"] = schema.name;
    data["columns"] = json::array();

    for (const auto& column : schema.columns) {
        json item;
        item["name"] = column.name;
        item["type"] = fieldTypeName(column.type);
        item["not_null"] = column.notNull;
        item["indexed"] = column.indexed;
        if (column.defaultValue.has_value()) {
            item["default"] = valueToJson(*column.defaultValue);
        }
        data["columns"].push_back(std::move(item));
    }

    return data;
}

TableSchema schemaFromJson(const json& data) {
    TableSchema schema;
    schema.name = data.at("name").get<std::string>();

    for (const auto& item : data.at("columns")) {
        Column column;
        column.name = item.at("name").get<std::string>();
        column.type = parseFieldType(item.at("type").get<std::string>());
        column.notNull = item.value("not_null", false);
        column.indexed = item.value("indexed", false);
        if (item.contains("default")) {
            column.defaultValue = valueFromJson(item.at("default"));
        }
        schema.columns.push_back(std::move(column));
    }

    return schema;
}

json rowsToJson(const TableData& data) {
    json result;
    result["next_id"] = data.nextId;
    result["rows"] = json::array();

    for (const auto& row : data.rows) {
        json item;
        item["id"] = row.id;
        item["deleted"] = row.deleted;
        item["values"] = json::object();
        for (const auto& [column, value] : row.values) {
            item["values"][column] = valueToJson(value);
        }
        result["rows"].push_back(std::move(item));
    }

    return result;
}

TableData rowsFromJson(const json& data) {
    TableData result;
    result.nextId = data.value("next_id", 1LL);

    for (const auto& item : data.value("rows", json::array())) {
        Row row;
        row.id = item.at("id").get<long long>();
        row.deleted = item.value("deleted", false);
        for (const auto& value : item.at("values").items()) {
            row.values[value.key()] = valueFromJson(value.value());
        }
        result.rows.push_back(std::move(row));
    }

    return result;
}

}  // namespace app
