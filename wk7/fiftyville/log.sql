-- Keep a log of any SQL queries you execute as you solve the mystery.

/*In log.sql, keep a log of all SQL queries that you run on the database.
Above each query, label each with a comment (in SQL, comments are any lines that begin with --)
describing why you’re running the query and/or what information you’re hoping to get out of that particular query.
You can use comments in the log file to add additional notes about your thought process as you solve the mystery:
ultimately, this file should serve as evidence of the process you used to identify the thief!*/


-- Find Crime Scene Report from the date and street of the Crime
SELECT *
FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- Find interviews from that day that mention 'bakery'
SELECT *
FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- Find bakery's secutiy logs from within ten minutes of the theft at 10:15
SELECT *
FROM bakery_security_logs
WHERE day = 28 AND hour = 10 AND minute >15 AND minute < 25;

-- Find name of person with license plate on the car that left the bakery
SELECT name
FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28 AND hour = 10 AND minute >15 AND minute < 25;

-- Find atm transactions on Leggett St
SELECT *
FROM atm_transactions
WHERE day = 28 AND atm_location = 'Leggett Street';

-- Find names of people who made these transactions
SELECT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE day = 28 AND atm_location = 'Leggett Street';

-- Find phone calls made on the day of the crime under 60 seconds
SELECT *
FROM phone_calls
WHERE day = 28 AND duration < 60;

-- Find names of Callers and Receivers of these phone calls
SELECT p1.name AS Caller, p2.name AS Receiver
FROM phone_calls
JOIN people p1 ON phone_calls.caller = p1.phone_number
JOIN people p2 ON phone_calls.receiver = p2.phone_number
WHERE phone_calls.day = 28 AND phone_calls.duration < 60;

-- Find flights made the day after the crime
SELECT *
FROM flights
WHERE day = 29;

-- Find destination city of the earliest flight
SELECT city
FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE day = 29 AND destination_airport_id = 4;

-- Find list of passengers on this flight
SELECT name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.id = 36;

-- Find name of thief by cross referencing license plate owners, atm/bank account owners, callers, and passengers
SELECT name
FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28 AND hour = 10 AND minute >15 AND minute < 25

INTERSECT

SELECT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE day = 28 AND atm_location = 'Leggett Street'

INTERSECT

SELECT name AS Caller
FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE phone_calls.day = 28 AND phone_calls.duration < 60

INTERSECT

SELECT name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.id = 36;




