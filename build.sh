#!/usr/bin/env bash
set -euo pipefail

output="${1:-mini_btree_db}"
root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
generated="$root/generated"

cd "$root"

if [[ -f "$generated/sql_parser.cpp" &&
      -f "$generated/sql_parser.hpp" &&
      -f "$generated/sql_lexer.cpp" ]]; then
    echo "Using existing generated files."
else
    echo "Generated parser files are missing. Creating them once."

    for tool in bison flex; do
        if ! command -v "$tool" >/dev/null 2>&1; then
            echo "$tool was not found. Install dependencies:" >&2
            echo "sudo apt install -y build-essential flex bison nlohmann-json3-dev" >&2
            exit 1
        fi
    done

    mkdir -p "$generated"

    bison --defines="$generated/sql_parser.hpp" \
        -o "$generated/sql_parser.cpp" \
        src/sql/sql_parser.y

    flex -o "$generated/sql_lexer.cpp" \
        src/sql/sql_lexer.l
fi

mapfile -t sources < <(find src -type f -name '*.cpp' | sort)

g++ -std=c++17 -Wall -Wextra -pedantic \
    -Iinclude -Igenerated \
    "${sources[@]}" generated/sql_parser.cpp generated/sql_lexer.cpp \
    -o "$output"

echo "Built $output"
