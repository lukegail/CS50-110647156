CREATE TABLE students (
    id INTEGER,
    student_name TEXT,
    house TEXT,
    head TEXT,
    PRIMARY KEY(id)
);




CREATE TABLE students (
    id INTEGER,
    student_name TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE houses (
    id INTEGER,
    house TEXT,
    head TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE assignments (
    student_id INTEGER,
    house_id INTEGER,
    FOREIGN KEY(student_id) REFERENCES students(id),
    FOREIGN KEY(house_id) REFERENCES houses(id),
    PRIMARY KEY(student_id, house_id)
);




INSERT INTO new_students (id, student_name)
SELECT id, student_name FROM students;

INSERT INTO students (id, student_name) SELECT id, student_name FROM students_original;



INSERT INTO assignments (student_id, house_id)
SELECT students.id, houses.id
FROM s_o
JOIN students ON s_o.student_name = students.student_name
JOIN houses ON s_o.house = houses.house;
