-- In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.

--    Your query should output a table with a single column for the name of each person.
--    There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
--    Kevin Bacon himself should not be included in the resulting list.

SELECT name
FROM people
WHERE id IN (
    SELECT stars.person_id
    FROM stars
    WHERE movie_id IN (
        SELECT stars.movie_id
        FROM stars
        JOIN people ON stars.person_id = people.id
        WHERE people.name = 'Kevin Bacon'
        AND people.birth = 1958
    )
)
AND name <> 'Kevin Bacon'


/*
SELF-JOIN METHOD

SELECT DISTINCT p1.name -- Give me the unique names that result from the following...
FROM people p1  -- Start with a list of all people.
JOIN stars s1 ON p1.id = s1.person_id  -- Find the movies they've starred in.
JOIN stars s2 ON s1.movie_id = s2.movie_id  -- for each of those movies, find all the stars who have been in those movies.
JOIN people p2 ON s2.person_id = p2.id -- Get their names.
WHERE p2.name = 'Kevin Bacon' AND p2.birth = 1958 AND p1.name <> 'Kevin Bacon';  -- filter the list.
*/