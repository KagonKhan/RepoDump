DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS books;

CREATE TABLE users (userID INTEGER PRIMARY KEY ASC, username TEXT, password TEXT, isAdmin boolean);
INSERT INTO users(username, password, isAdmin) VALUES ('admin', 'admin', true);
INSERT INTO users(username, password, isAdmin) VALUES ('sebastian', 'szynk', false);


CREATE TABLE IF NOT EXISTS books (title TEXT);
INSERT INTO books(title) VALUES
    ('The Lord of the Rings'),
    ('The Catcher in the Rye'),
    ('To Kill a Mockingbird'),
    ('Da Vinci Code'),
    ('Don Quixote'),
    ('The Lion, the Witch and the audacity of this ...witch'),
    ('The Alchemist');
             