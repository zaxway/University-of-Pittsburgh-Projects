import re

class Media:
    def __init__(self, title):
        self.title = title
    def slug(self):
        tmp = re.sub('[^A-Za-z0-9 ]+', '', self.title)
        tmp = tmp.replace(" ", "-")
        return tmp.lower()
class Movie(Media):
    def __init__(self, title, year, director, runtime):
        super(Movie, self).__init__(title)
        self.year = year
        self.director = director
        self.runtime = runtime
    def __repr__(self):
        return '<Movie: %s>'% self.title
    def __str__(self):
        return '(%d) %s'% (self.year, self.title)
    def abbreviation(self):
        abbreviationOfTitle = self.slug().replace("-", "")
        return abbreviationOfTitle[0:3]
    def retYear(self):
        return self.year

# decorators
def add_msg(msg):
    def decorator(func):
        def new_function(*args, **kwargs):
            print("=====\n%s\n=====" % msg)
            return func(*args, **kwargs)
        return new_function
    return decorator

@add_msg("Before year 2000")
def before_year(year):
    [print(movie) for movie in movieList if movie.year < year]

@add_msg("Abbreviations")
def abbr():
    [print(movie.abbreviation()) for movie in movieList]

@add_msg("Slugs")
def slugs():
    [print(movie.slug()) for movie in movieList]

def main():
    print("Thanks for checking the Local Movie Database!")
    abbr()
    slugs()
    before_year(2000)
    print("Thank you")

if __name__ == '__main__':
    movieList = [
        Movie("G.I. Joe", 1976, "Bobby Smith", 3.42),
        Movie("Brotha", 1944, "Stanley Nir", 4.23),
        Movie("Zombie", 1945, "Alice Nee", 1.21),
        Movie("Walking Dead", 2005, "Sebastian Lee", 2.42),
        Movie("Sista", 2009, "Bob Chan", 2.16)]
    print(movieList)
    main()
