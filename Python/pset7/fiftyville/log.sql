-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports
WHERE
    day = "28"
    AND month = "7"
    AND year = "2020"
    AND street = "Chamberlin Street";

-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time
-- — each of their interview transcripts mentions the courthouse.

SELECT transcript FROM interviews
WHERE
    day = "28"
    AND month = "7"
    AND year = "2020"
    AND transcript like "%courthouse%";

-- Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse
-- parking lot and drive away. If you have security footage from the courthouse parking lot,
-- you might want to look for cars that left the parking lot in that time frame.

-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before
-- I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there
-- withdrawing some money.

-- As the thief was leaving the courthouse, they called someone who talked to them for less than
-- a minute. In the call, I heard the thief say that they were planning to take the earliest flight
-- out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to
-- purchase the flight ticket.

SELECT name FROM people
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
WHERE
    day = "28"
    AND month = "7"
    AND year = "2020"
    AND hour = "10"
    AND minute >= "15"
    AND minute <= "25"
    AND activity = "exit";

-- Patrick Ernest Amber Danielle Roger Elizabeth Russell Evelyn

SELECT DISTINCT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE
    day = "28"
    AND month = "7"
    AND year = "2020"
    AND atm_location = "Fifer Street"
    AND transaction_type = "withdraw";

-- Danielle Bobby Madison Ernest Roy Elizabeth Victoria Russell

SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE flight_id = (
    SELECT id FROM flights
    WHERE
        day = "29"
        AND month = "7"
        AND year = "2020"
        ORDER BY hour, minute
        LIMIT 1
);

-- Doris Roger Ernest Edward Evelyn Madison Bobby Danielle

SELECT name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE
    day = "28"
    AND month = "7"
    AND year = "2020"
    AND duration < "60";

-- Roger Evelyn Ernest Evelyn Madison Russell Kimberly Bobby Victoria
-- Thief is Ernest.

SELECT name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE
    caller = (SELECT phone_number FROM people WHERE name = "Ernest")
    AND day = "28"
    AND month = "7"
    AND year = "2020"
    AND duration < "60";

-- Berthold
-- The accomplice is Berthold.

SELECT city FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE
    day = "29"
    AND month = "7"
    AND year = "2020"
    ORDER BY hour, minute
    LIMIT 1;

-- London
-- The city is London.
