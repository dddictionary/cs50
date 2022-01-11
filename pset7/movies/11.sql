-- In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order) 
-- that Chadwick Boseman starred in, starting with the highest rated.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Chadwick Boseman.
SELECT movies.title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
JOIN ratings on movies.id = ratings.movie_id
WHERE people.name = 'Chadwick Boseman'
ORDER BY rating DESC
LIMIT 5;