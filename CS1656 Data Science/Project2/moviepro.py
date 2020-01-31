import sqlite3 as lite
import csv
import pandas
import re
con = lite.connect('cs1656.sqlite')

with con:
	cur = con.cursor()

	########################################################################
	### CREATE TABLES ######################################################
	########################################################################
	# DO NOT MODIFY - START
	cur.execute('DROP TABLE IF EXISTS Actors')
	cur.execute("CREATE TABLE Actors(aid INT, fname TEXT, lname TEXT, gender CHAR(6), PRIMARY KEY(aid))")

	cur.execute('DROP TABLE IF EXISTS Movies')
	cur.execute("CREATE TABLE Movies(mid INT, title TEXT, year INT, rank REAL, PRIMARY KEY(mid))")

	cur.execute('DROP TABLE IF EXISTS Directors')
	cur.execute("CREATE TABLE Directors(did INT, fname TEXT, lname TEXT, PRIMARY KEY(did))")

	cur.execute('DROP TABLE IF EXISTS Cast')
	cur.execute("CREATE TABLE Cast(aid INT, mid INT, role TEXT)")

	cur.execute('DROP TABLE IF EXISTS Movie_Director')
	cur.execute("CREATE TABLE Movie_Director(did INT, mid INT)")
	# DO NOT MODIFY - END

	########################################################################
	### READ DATA FROM FILES ###############################################
	########################################################################
	# actors.csv, cast.csv, directors.csv, movie_dir.csv, movies.csv
	# UPDATE THIS
	input = open('actors.csv', 'r')
	lines = input.readlines()
	for line in lines:
		result = [x.strip() for x in line.split(',')]
		result[0] = int(result[0])	# aid
		cur.execute("INSERT INTO  Actors(aid, fname, lname, gender) VALUES (?, ?, ?, ?)", result)
	con.commit()

	input = open('movies.csv', 'r')
	lines = input.readlines()
	for line in lines:
		result = [x.strip() for x in line.split(',')]
		result[0] = int(result[0])	# mid
		result[2] = int(result[2]) # year
		result[3] = float(result[3]) # rank
		cur.execute("INSERT INTO  Movies(mid, title, year, rank) VALUES (?, ?, ?, ?)", result)
	con.commit()

	input = open('directors.csv', 'r')
	lines = input.readlines()
	for line in lines:
		result = [x.strip() for x in line.split(',')]
		result[0] = int(result[0])	# did
		cur.execute("INSERT INTO  Directors(did, fname, lname) VALUES (?, ?, ?)", result)
	con.commit()

	input = open('cast.csv', 'r')
	lines = input.readlines()
	for line in lines:
		result = [x.strip() for x in line.split(',')]
		result[0] = int(result[0])	# aid
		result[1] = int(result[1]) # mid
		cur.execute("INSERT INTO  Cast(aid, mid, role) VALUES (?, ?, ?)", result)
	con.commit()

	input = open('movie_dir.csv', 'r')
	lines = input.readlines()
	for line in lines:
		result = [x.strip() for x in line.split(',')]
		result[0] = int(result[0])	# aid
		result[1] = int(result[1]) # mid
		cur.execute("INSERT INTO  Movie_Director(did, mid) VALUES (?, ?)", result)
	con.commit()


	########################################################################
	### INSERT DATA INTO DATABASE ##########################################
	########################################################################
	# UPDATE THIS TO WORK WITH DATA READ IN FROM CSV FILES
	# cur.execute("INSERT INTO Actors VALUES(1001, 'Harrison', 'Ford', 'Male')")
	# cur.execute("INSERT INTO Actors VALUES(1002, 'Daisy', 'Ridley', 'Female')")

	# cur.execute("INSERT INTO Movies VALUES(101, 'Star Wars VII: The Force Awakens', 2015, 8.2)")
	# cur.execute("INSERT INTO Movies VALUES(102, 'Rogue One: A Star Wars Story', 2016, 8.0)")
	#
	# cur.execute("INSERT INTO Cast VALUES(1001, 101, 'Han Solo')")
	# cur.execute("INSERT INTO Cast VALUES(1002, 101, 'Rey')")
	#
	# cur.execute("INSERT INTO Directors VALUES(5000, 'J.J.', 'Abrams')")
	#
	# cur.execute("INSERT INTO Movie_Director VALUES(5000, 101)")


	########################################################################
	### QUERY SECTION ######################################################
	########################################################################
	queries = {}

	# DO NOT MODIFY - START
	# DEBUG: all_movies ########################
	queries['all_movies'] = '''
SELECT * FROM Movies
'''
	# DEBUG: all_actors ########################
	queries['all_actors'] = '''
SELECT * FROM Actors
'''
	# DEBUG: all_cast ########################
	queries['all_cast'] = '''
SELECT * FROM Cast
'''
	# DEBUG: all_directors ########################
	queries['all_directors'] = '''
SELECT * FROM Directors
'''
	# DEBUG: all_movie_dir ########################
	queries['all_movie_dir'] = '''
SELECT * FROM Movie_Director
'''
	# DO NOT MODIFY - END

	########################################################################
	### INSERT YOUR QUERIES HERE ###########################################
	########################################################################
	# NOTE: You are allowed to also include other queries here (e.g.,
	# for creating views), that will be executed in alphabetical order.
	# We will grade your program based on the output files q01.csv,
	# q02.csv, ..., q12.csv

	# Q01 ########################
	queries['q01'] = '''
	SELECT a.fname, a.lname
	FROM Cast AS c
	NATURAL JOIN Actors AS a
	WHERE c.aid in (SELECT c.aid
					FROM Cast AS c
					NATURAL JOIN Movies AS m
					WHERE (m.year > 1980 AND m.year < 1990))
	AND c.aid in (SELECT c.aid
					FROM Cast AS c
					NATURAL JOIN Movies AS m
					WHERE (m.year >= 2000))
	GROUP BY c.aid
	ORDER BY a.lname, a.fname ASC
'''

	# Q02 ########################
	queries['q02'] = '''
	SELECT m.title, m.year
	FROM Movies AS m
	WHERE year in (SELECT m.year
					FROM Movies AS m
					WHERE m.title = "Rogue One: A Star Wars Story")
	AND rank > (SELECT m.rank
					FROM Movies AS m
					WHERE m.title = "Rogue One: A Star Wars Story"
					LIMIT 1)
	GROUP BY m.title
	ORDER BY m.title ASC
'''

	# Q03 ########################
	# Must have a GROUP BY before a ORDER BY aggreggate
	queries['q03'] = '''
	SELECT a.fname, a.lname, COUNT(DISTINCT m.mid)
	FROM Actors AS a
	NATURAL JOIN Cast AS c
	NATURAL JOIN Movies AS m
	WHERE m.title LIKE '%Star Wars%'
	GROUP BY a.fname, a.lname
	ORDER BY COUNT(DISTINCT m.mid) DESC
'''

	# Q04 ########################
	# Do not need a GROUP BY before a ORDER BY non-aggreggate
	queries['q04'] = '''
	SELECT a.lname, a.fname
	FROM Actors AS a
	NATURAL JOIN Cast AS c
	NATURAL JOIN Movies AS m
	WHERE m.year < 1985
	ORDER BY a.lname ASC
'''

	# Q05 ########################
	queries['q05'] = '''
	SELECT d.fname, d.lname, COUNT(DISTINCT md.mid) AS num_movies
	FROM Directors AS d
	NATURAL JOIN Movie_Director AS md
	GROUP BY d.did
	ORDER BY num_movies DESC
	LIMIT 20
'''

	# Q06 ########################
	# Seems like we use HAVING for aggreggate conditions, works like a WHERE
	# Also HAVING must have a GROUP BY clause before it, otherwise will result in
	# syntax error
	queries['q06'] = '''
	SELECT m.title, COUNT(c.aid) AS num_cast_members
	FROM Movies AS m
	NATURAL JOIN Cast AS c
	GROUP BY m.mid
	HAVING num_cast_members >= (SELECT MIN(num_cast_members2)
								FROM (SELECT COUNT(c2.aid) AS num_cast_members2
										FROM Movies as m2
										NATURAL JOIN CAST as c2
										GROUP BY m2.mid
										ORDER BY num_cast_members2 DESC
										LIMIT 10))
	ORDER BY num_cast_members DESC
'''

	# Q07 ########################
	# Trying to use subqueries while JOINING
	# coalesce() selects first num that is not null
	queries['q07'] = '''
	SELECT m.title, (SELECT COALESCE(numFemales, 0)), (SELECT COALESCE(numMales, 0))
	FROM Movies AS m
	NATURAL JOIN (SELECT mid,COUNT(c.aid) AS numFemales
					FROM Cast AS c
					NATURAL JOIN Actors AS a
					WHERE LOWER(a.gender) == LOWER('female')
					GROUP BY mid) FCount
	LEFT JOIN (SELECT mid,COUNT(c.aid) as numMales
						FROM Cast AS c
						NATURAL JOIN Actors AS a
						WHERE LOWER(a.gender) == LOWER('male')
						GROUP BY mid) MCount on FCount.mid=MCount.mid
	WHERE (SELECT COALESCE(numFemales, 0)) > (SELECT COALESCE(numMales, 0))
	ORDER BY m.title ASC

'''

	# Q08 ########################
	queries['q08'] = '''
	SELECT a.fname, a.lname, COUNT(DISTINCT d.did) as numDirectors
	FROM Actors AS a
	NATURAL JOIN (Cast NATURAL JOIN Movie_Director) AS cmd
	INNER JOIN Directors AS d ON d.did = cmd.did
	WHERE (a.fname != d.fname) AND (d.lname != a.lname)
	GROUP BY a.aid
	HAVING numDirectors >= 7
	ORDER BY COUNT(DISTINCT d.did) DESC
'''

	# Q09 ########################
	queries['q09'] = '''
	SELECT a.fname, a.lname, COUNT(c.mid)
	FROM Actors AS a
	NATURAL JOIN Cast AS c
	WHERE UPPER(a.fname) LIKE 'S%'
	GROUP BY a.aid
	ORDER BY COUNT(c.mid) DESC
'''

	# Q10 ########################
	queries['q10'] = '''
	SELECT a.lname, cm.title
	FROM Actors AS a
	NATURAL JOIN (Cast NATURAL JOIN Movies) AS cm
	NATURAL JOIN Movie_Director AS md
	INNER JOIN Directors AS d ON md.did = d.did
	WHERE a.lname = d.lname

'''

	# Q11 ########################
	# want to select id of actors that have worked on a film
	# that was worked on actors that have worked on a Kevin Bacon film

	# Then I want to select all actors within the except including bacon 1 actors and bacon 0 Actors
	queries['q11'] = '''
	SELECT a.fname,a.lname
	FROM Actors AS a
	NATURAL JOIN Cast AS c
	WHERE c.mid IN (SELECT c2.mid
					FROM Cast AS c2
					NATURAL JOIN Actors AS a2
					WHERE a2.aid IN (SELECT a3.aid
									FROM Cast AS c3
									NATURAL JOIN Actors AS a3
									WHERE c3.mid IN(SELECT c4.mid
													FROM Cast AS c4
													NATURAL JOIN Actors AS a4
													WHERE a4.fname = "Kevin" AND a4.lname = "Bacon")))
	EXCEPT
	SELECT a.fname, a.lname
	FROM Actors AS a
	WHERE a.aid IN (SELECT a3.aid
					FROM Cast AS c3
					NATURAL JOIN Actors AS a3
					WHERE c3.mid IN(SELECT c4.mid
									FROM Cast AS c4
									NATURAL JOIN Actors AS a4
									WHERE a4.fname = "Kevin" AND a4.lname = "Bacon"))

'''

	# Q12 ########################
	queries['q12'] = '''
	SELECT a.fname, a.lname, COUNT(DISTINCT m.mid), AVG(m.rank)
	FROM Actors AS a
	NATURAL JOIN Cast AS c
	NATURAL JOIN Movies AS m
	GROUP BY a.aid
	ORDER BY AVG(m.rank) DESC
	LIMIT 20
'''


	########################################################################
	### SAVE RESULTS TO FILES ##############################################
	########################################################################
	# DO NOT MODIFY - START
	for (qkey, qstring) in sorted(queries.items()):
		try:
			cur.execute(qstring)
			all_rows = cur.fetchall()

			print ("=========== ",qkey," QUERY ======================")
			print (qstring)
			print ("----------- ",qkey," RESULTS --------------------")
			for row in all_rows:
				print (row)
			print (" ")

			save_to_file = (re.search(r'q0\d', qkey) or re.search(r'q1[012]', qkey))
			if (save_to_file):
				with open(qkey+'.csv', 'w') as f:
					writer = csv.writer(f)
					writer.writerows(all_rows)
					f.close()
				print ("----------- ",qkey+".csv"," *SAVED* ----------------\n")

		except lite.Error as e:
			print ("An error occurred:", e.args[0])
	# DO NOT MODIFY - END
