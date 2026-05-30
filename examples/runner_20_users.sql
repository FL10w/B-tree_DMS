--   запуск:
--   ./mini_btree_db --data-dir users20_storage examples/runner_20_users.sql

CREATE DATABASE users20_demo;
USE users20_demo;

-- Большая таблица пользователей: 20 строк, индексы, DEFAULT-значения.
CREATE TABLE users (
    id int INDEXED,
    email string INDEXED,
    username string NOT_NULL,
    age int DEFAULT 18,
    city string DEFAULT "Moscow",
    role string DEFAULT "user",
    rating int DEFAULT 0,
    note string
);

INSERT INTO users (id, email, username, age, city, role, rating) VALUE
    (1, "alice@example.com", "alice", 24, "Moscow", "admin", 95),
    (2, "bob@example.com", "bob", 31, "Saint Petersburg", "user", 72),
    (3, "carol@example.com", "carol", 19, "Kazan", "user", 81),
    (4, "dmitry@example.com", "dmitry", 27, "Moscow", "moderator", 88),
    (5, "elena@example.com", "elena", 22, "Novosibirsk", "user", 67),
    (6, "fedor@example.com", "fedor", 35, "Moscow", "user", 74),
    (7, "galina@example.com", "galina", 29, "Kazan", "admin", 91),
    (8, "hanna@example.com", "hanna", 26, "Sochi", "user", 79),
    (9, "igor@example.com", "igor", 41, "Moscow", "moderator", 84),
    (10, "julia@example.com", "julia", 20, "Perm", "user", 76),
    (11, "kirill@example.com", "kirill", 33, "Omsk", "user", 69),
    (12, "lena@example.com", "lena", 28, "Moscow", "admin", 97),
    (13, "maxim@example.com", "maxim", 23, "Kazan", "user", 73),
    (14, "nina@example.com", "nina", 30, "Samara", "moderator", 86),
    (15, "oleg@example.com", "oleg", 38, "Moscow", "user", 62),
    (16, "polina@example.com", "polina", 21, "Sochi", "user", 82),
    (17, "roman@example.com", "roman", 25, "Perm", "user", 77),
    (18, "sveta@example.com", "sveta", 32, "Moscow", "admin", 93),
    (19, "timur@example.com", "timur", 36, "Ufa", "moderator", 80),
    (20, "vera@example.com", "vera", 27, "Kazan", "user", 89);

-- DEFAULT заполняет пропущенные поля age, city, role, rating, note.
INSERT INTO users (id, email, username) VALUE
    (21, "default-user@example.com", "default_user");

-- Поиск через B-tree по INDEXED int/string.
SELECT * FROM users WHERE id == 12;
SELECT username, email, role FROM users WHERE email == "galina@example.com";

-- Диапазон и LIKE.
SELECT id, username, age, rating
FROM users
WHERE id BETWEEN 5 AND 12;

SELECT username, city
FROM users
WHERE username LIKE "a.*";

-- Составной WHERE с AND, OR и скобками.
SELECT id, username, city, role, rating
FROM users
WHERE (rating >= 90 AND city == "Moscow") OR role == "moderator";

-- UPDATE и DELETE.
UPDATE users SET rating = 99 WHERE email == "alice@example.com";
DELETE FROM users WHERE id == 15;

SELECT id, username, rating
FROM users
WHERE id >= 18;

-- Агрегаты по 20+ пользователям.
SELECT COUNT(*) AS total_users, SUM(rating) AS total_rating, AVG(rating) AS avg_rating
FROM users
WHERE id >= 1;

SELECT COUNT(note) AS filled_notes FROM users;

SHOW TELEMETRY;
