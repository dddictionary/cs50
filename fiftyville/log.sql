-- Keep a log of any SQL queries you execute as you solve the mystery.
--Authorities believe that the thief stole the duck and then, shortly afterwards, took a flight out of town with the help of an accomplice.
--All you know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street.


--Get the police description 
SELECT description 
    FROM crime_scene_reports
        WHERE month = 7 AND day = 28 AND year = 2021 AND street = 'Humphrey Street';

--Took place at 10:15 AM

--Get the interviews from the three witnesses
SELECT name, transcript  
    FROM interviews
        WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE '%thief%';


--Investigate this lead:
--Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. 
--If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
--Took place at 10:15 AM        

SELECT name 
    FROM people 
        JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
            WHERE day = 28 AND year = 2021 AND month = 7 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit';

--Suspect List:Vanessa, Bruce, Barry, Luca, Sofia, Iman, Diana, Kelsey

--Follow second lead: I don't know the thief's name, but it was someone I recognized. Earlier this morning, 
--before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
SELECT DISTINCT(name)
    FROM people
        JOIN bank_accounts ON people.id = bank_accounts.person_id
        JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
            WHERE day = 28 AND month = 7 AND year = 2021 AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street';
--Suspect List: Luca, Kenny, Taylor, Bruce, Brooke, Iman, Benista, Diana
--Repeats: Luca, Bruce, Iman, Diana

--Follow third lead: 
--As the thief was leaving the bakery, they called someone who talked to them for less than a minute. 
--In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. 
--The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT name 
    FROM people 
        JOIN passengers ON people.passport_number = passengers.passport_number
        JOIN flights ON passengers.flight_id = flights.id
            WHERE flight_id = 
                (SELECT id 
                    FROM flights
                    WHERE day = 29 AND month = 7 AND year = 2021
                    ORDER BY hour, minute
                    LIMIT 1);
--Suspect List: Doris, Sofia, Bruce, Edward, Kelsey, Taylor, Kenny, Luca
--Repeats: Luca, Bruce

--Follow same lead as above to get the people who made the phone call
SELECT name 
    FROM people
        JOIN phone_calls ON people.phone_number = phone_calls.caller
        WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60;
--Suspects: Sofia, Kelsey, Bruce, Taylor, Diana, Carina, Kenny, Benista
--Repeats: Bruce must be the thief

--Find the flight he took the next day
SELECT city
    FROM airports
        WHERE id IN (
            SELECT destination_airport_id 
                FROM flights 
                    WHERE day = 29 AND month = 7 AND year = 2021
                    ORDER BY hour, minute LIMIT 1);

--Flight is to NYC. what a coincidence ;)
--Find accomplice:
SELECT name 
    FROM people
        JOIN phone_calls ON people.phone_number = phone_calls.receiver
        WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60 AND caller IN (
            SELECT phone_number
            FROM people 
            WHERE name = 'Bruce');

--Robin is accomplice



