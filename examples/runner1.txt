--   запуск:
--   mini_btree_db.exe --data-dir runner_storage examples\runner.sql

CREATE DATABASE runner_demo;
USE runner_demo;

-- Основное задание: иерархия БД/таблиц, типы int/string, ограничения NOT_NULL и INDEXED.
-- Доп. задание 10: DEFAULT-значения для пропущенных столбцов при INSERT.
CREATE TABLE students (
    id int INDEXED,
    email string INDEXED,
    name string NOT_NULL,
    group_name string DEFAULT "CS-01",
    score int DEFAULT 0,
    note string
);

CREATE TABLE courses (
    code string INDEXED,
    title string NOT_NULL,
    hours int DEFAULT 36
);

-- Основное задание: INSERT. Повторяющиеся строки дополнительно показывают доп. задание 2.
INSERT INTO students (id, email, name, score) VALUE
    (1, "ivan@example.com", "Ivan", 82),
    (2, "anna@example.com", "Anna", 95),
    (3, "petr@example.com", "Petr", 71);

-- DEFAULT заполняет поля, которые не переданы явно.
INSERT INTO students (id, email, name) VALUE
    (4, "maria@example.com", "Maria");

INSERT INTO courses (code, title) VALUE
    ("sysprog", "System programming"),
    ("db", "Databases");

-- Основное задание: SELECT с JSON-выводом и поиск через B-tree по INDEXED int/string.
SELECT * FROM students WHERE id == 2;
SELECT code AS course, title, hours FROM courses WHERE code == "db";

-- Основное задание: условия WHERE, BETWEEN, LIKE и алиасы.
SELECT name AS student, score
FROM students
WHERE score BETWEEN 80 AND 100;

SELECT name
FROM students
WHERE name LIKE "A.*";

-- Доп. задание 11: составной WHERE с AND, OR и скобками.
SELECT id, name, group_name, score
FROM students
WHERE (score >= 80 AND group_name == "CS-01") OR name == "Petr";

-- Основное задание: UPDATE и DELETE.
UPDATE students SET score = 88 WHERE email == "ivan@example.com";
DELETE FROM students WHERE id == 3;

SELECT * FROM students WHERE id >= 1;

-- Основное задание: ограничения и валидация. Эти две ошибки ожидаемые.
INSERT INTO students (id, email, name) VALUE
    (2, "duplicate@example.com", "Duplicate id");

INSERT INTO students (id, email, name) VALUE
    (5, "null-name@example.com", NULL);

-- Доп. задание 12: агрегатные функции.
SELECT COUNT(*) AS total_students, SUM(score) AS total_score, AVG(score) AS avg_score
FROM students
WHERE id >= 1;

SELECT COUNT(note) AS filled_notes FROM students;

-- Доп. задание 7: Access Logs пишутся в runner_storage\_access.log во время выполнения.
-- Доп. задание 8: телеметрия. Здесь же видны счетчики string pool для доп. задания 2. SHOW TELEMETRY
-- Снимок телеметрии пишется в runner_storage\_telemetry.json.
-- Основное задание: DROP TABLE.
DROP TABLE courses;


SHOW TELEMETRY;
