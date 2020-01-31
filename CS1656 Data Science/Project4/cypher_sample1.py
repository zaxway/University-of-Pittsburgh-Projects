from neo4j.v1 import GraphDatabase, basic_auth

#connection with authentication
driver = GraphDatabase.driver("bolt://localhost:7687", auth=basic_auth("neo4j4", "cs1656"), encrypted=False)

#connection without authentication
#driver = GraphDatabase.driver("bolt://localhost", encrypted=False)

session = driver.session()
transaction = session.begin_transaction()

# initialize output strings
q1Str = ""
q2Str = ""
q3Str = ""
q4Str = ""
q5Str = ""
q6Str = ""
q7Str = ""
q8Str = ""

q1 = transaction.run("MATCH (a:Actor)-[:ACTS_IN]->(m:Movie) WITH a, count(m) AS movie_count RETURN a.name AS actor_name, movie_count AS number_of_films_acted_in ORDER BY movie_count DESC LIMIT 20")
print("______________Query 1_______________")
for record in q1:
    q1Str += str(record['actor_name']) + ", " + str(record['number_of_films_acted_in']) + "\n"
print(q1Str)
print("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _")
print()

q2 = transaction.run("MATCH (u:User)-[r:RATED]->(m:Movie) WHERE r.stars <= 3 RETURN m.title AS movie_title")
print("______________Query 2_________________")
for record in q2:
    q2Str += str(record['movie_title']) + "\n"
print(q2Str)
print("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _")
print()

q3 = transaction.run("MATCH (a:Actor)-[:ACTS_IN]->(m:Movie) RETURN m.title AS movie_title, COUNT(a) AS num_cast ORDER BY num_cast DESC LIMIT 1")
print("______________Query 3_________________")
for record in q3:
    q3Str += str(record['movie_title']) + "\n"
print(q3Str)
print("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _")
print()

q4 = transaction.run("MATCH (a:Actor)-[:ACTS_IN]->(m:Movie)<-[:DIRECTED]-(d:Director) WITH a, count(DISTINCT d) AS num_directors WHERE num_directors >= 3 RETURN a.name AS actor_name, num_directors")
print("______________Query 4_________________")
for record in q4:
    q4Str += str(record['actor_name']) + ", " + str(record['num_directors']) + "\n"
print(q4Str)
print("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _")
print()

# Oracle of Bacon probs
# bocon 2 acts in a movie that bacon1 also acts in
# bocon 0 i.e. Kevin Bacon acts in a movie that bacon 1 also also acts in
q5 = transaction.run("MATCH (b2:Actor)-[:ACTS_IN]->(b1m:Movie)<-[:ACTS_IN]-(b1:Actor)-[:ACTS_IN]->(b0m:Movie)<-[:ACTS_IN]-(b0:Actor {name: 'Kevin Bacon'}) RETURN b2.name AS actor_name")
print("______________Query 5_________________")
for record in q5:
    q5Str += str(record['actor_name']) + "\n"
print(q5Str)
print("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _")
print()

q6 = transaction.run("MATCH (a:Actor {name: 'Tom Hanks'})-[:ACTS_IN]->(m:Movie) RETURN DISTINCT m.genre AS genre")
print("______________Query 6_________________")
for record in q6:
    q6Str += str(record['genre']) + "\n"
print(q6Str)
print("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _")
print()

q7 = transaction.run("MATCH (d:Director)-[:DIRECTED]->(m:Movie) WITH d, count(DISTINCT m.genre) AS num_genres WHERE num_genres >= 2 RETURN d.name AS director_name, num_genres")
print("______________Query 7_________________")
for record in q7:
    q7Str += str(record['director_name']) + ", " + str(record['num_genres']) + "\n"
print(q7Str)
print("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _")
print()

q8 = transaction.run("MATCH (a:Actor)-[:ACTS_IN]->(m:Movie)<-[:DIRECTED]-(d:Director) WITH a, d, count(m) AS num_times_a_pair RETURN d.name AS director_name, a.name AS actor_name, num_times_a_pair ORDER BY num_times_a_pair DESC LIMIT 5")
print("______________Query 8_________________")
for record in q8:
    q8Str += str(record['director_name']) + ", " + str(record['actor_name']) + ", " + str(record['num_times_a_pair']) + "\n"
print(q8Str)
print("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _")
print()

with open("output.txt", 'w') as out:
    out.write("### Q1 ###" + "\n")
    out.write(q1Str)
    out.write("\n")

    out.write("### Q2 ###" + "\n")
    out.write(q2Str)
    out.write("\n")

    out.write("### Q3 ###" + "\n")
    out.write(q3Str)
    out.write("\n")

    out.write("### Q4 ###" + "\n")
    out.write(q4Str)
    out.write("\n")

    out.write("### Q5 ###" + "\n")
    out.write(q5Str)
    out.write("\n")

    out.write("### Q6 ###" + "\n")
    out.write(q6Str)
    out.write("\n")

    out.write("### Q7 ###" + "\n")
    out.write(q7Str)
    out.write("\n")

    out.write("### Q8 ###" + "\n")
    out.write(q8Str)
    out.write("\n")

transaction.close()
session.close()
