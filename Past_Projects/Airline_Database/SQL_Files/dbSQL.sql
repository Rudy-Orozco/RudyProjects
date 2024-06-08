/* 1. Gather all aircraft that have been flown between 3000 to 8000 hours */
SELECT 	TailNum, Model, CodeSize
FROM	AIRCRAFT
WHERE	AirTime >= 3000 AND AirTime <= 8000;


/* 2. Get all the names of pilots that are currently based in dallas */
SELECT	P.Fname, P.MInit, P.Lname
FROM 	PILOT P JOIN BASED_AT B ON P.SSN = B.bSSN 
		JOIN DESTINATION D ON B.bIATA = D.IATA
WHERE	City = 'Dallas';


/* 3. What model aircraft has a range of at least 3000 nautical miles */
SELECT 	Model
FROM	AIRCRAFT
WHERE	FltRange >= 3000;


/* 4. Which Pilots command a 787-8 aicraft */
SELECT	P.Fname, P.MInit, P.Lname
FROM	PILOT P JOIN COMMAND_ C ON P.SSN = C.cSSN
		JOIN AIRCRAFT A ON C.cTailNum = A.TailNum
WHERE	Model = '787' AND CodeSize = '8';


/* 5. Which pilots can fly an aircraft that is set for a route from DFW to NRT */
SELECT	P.Fname, P.MInit, P.Lname
FROM	PILOT P JOIN OPERATE_ O ON P.SSN = O.oSSN
		JOIN ROUTE_ R ON O.oFlightNo = R.FlightNo
WHERE	DepIATA = "DFW" AND ArrIATA = "NRT";
		

/* 6. Retrieve all pilots that are female and that fly an Airbus aircraft */
SELECT	P.Fname, P.MInit, P.Lname
FROM	PILOT P JOIN COMMAND_ C ON P.SSN = C.cSSN
		JOIN AIRCRAFT A ON C.cTailNum = A.TailNum
WHERE	Gender = 'F' AND Manufact = 'Airbus';


/* 7. [COMPLEX QUERY] List the number of available aircraft by manufacturer from greatest to least */
SELECT 		A.Manufact, COUNT(O.ownTailNum) AS NumAircraft
FROM 		AIRCRAFT A JOIN OWNS_ O ON O.ownTailNum = A.TailNum
GROUP BY 	A.Manufact
HAVING		COUNT(O.ownTailNum) > 0
ORDER BY	NumAircraft DESC;

/* 8. What airline does "Kira Clove" Fly for */
SELECT	A.AirlName
FROM	AIRLINE A JOIN WORKS_FOR W ON A.AirlID = W.wAirlID
		JOIN PILOT P ON P.SSN = W.wSSN
WHERE	Fname = 'Kira' AND Lname = 'Clove';

/* 9. Get all the A320's Tail Numbers Currently in the database */
SELECT	A.TailNum
FROM	AIRCRAFT A
WHERE	Model = 'A321';

/* 0. Gather all aircraft is owned by the airline “American Airlines */
SELECT	A.TailNum, A.Model, A.CodeSize
FROM	AIRCRAFT A JOIN OWNS_ O ON A.TailNum = O.ownTailNum
		JOIN AIRLINE Al ON Al.AirlID = O.ownAirlID
WHERE	AirlName = 'American Airlines';