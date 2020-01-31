from flask import Flask, flash, redirect, render_template, request, session, abort, url_for
from models import db, Player, Game
from flask_sqlalchemy import SQLAlchemy
import datetime
from functools import wraps
from sqlalchemy import or_, and_
import json
import os

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///" + os.path.join(
    app.root_path, "connect4.db"
)
# Suppress deprecation warning
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False
app.secret_key = "super secret key"
app.config['SEND_FILE_MAX_AGE_DEFAULT'] = 0


db.init_app(app)

@app.route("/landing")
def home():
    if session['logged_in'] == True:
        user = Player.query.filter_by(username=session['currUsername']).first()
        games = user.games()
        return render_template("landing.html", games=games, user=session['currUsername'])
    return render_template('login.html')

@app.route("/game/<game_id>/")
def game(game_id=None):
    if game_id:
        game = db.session.query(Game).get(game_id)
        return render_template("game.html", game=game)
    return abort(404)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'GET':
        return render_template('login.html')
    if request.method == 'POST':
        user = Player.query.filter_by(username=request.form['username']).first()
        if user != None:
            password = user.password
            if password == request.form['password']:
                currentUser = request.form['username']
                session['logged_in'] = True
                session['currUsername'] = currentUser
                session['currUserID'] = user.id
                games = user.games()
                return render_template("landing.html", games=games, user=session['currUsername'])
            else:
                flash("Incorrect Password!")
                return render_template('login.html')
        else:
            flash("Invalid Username!")
            return render_template('login.html')

@app.route('/signUp', methods=['GET', 'POST'])
def signUp():
    if request.method == 'GET':
        return render_template('signup.html')
    if request.method == 'POST':
        username = request.form['uName']
        password = request.form['password']
        birthday = request.form['bday']
        try:
            assert Player.query.filter_by(username=username).first() == None
            assert len(password) > 0
        except:
            flash("Password Length must be greater than 0 or username is taken!")
            return render_template('signup.html')
        new_player = Player(username=username, birthday=datetime.datetime.strptime(birthday, '%m/%d/%Y').date(), password=password)
        db.session.add(new_player)
        db.session.commit()
        return render_template('login.html')

@app.route('/createGame', methods=['GET', 'POST'])
def createGame():
    if request.method == 'GET':
        return render_template('createAGame.html')
    if request.method == 'POST':
        g = Game()
        db.session.add(g)
        usernameP1 = request.form['p1Username']
        usernameP2 = request.form['p2Username']
        try:
            assert not Player.query.filter_by(username=usernameP1).first() == None
            assert not Player.query.filter_by(username=usernameP2).first() == None
        except:
            flash("Could not find players in database. Refreshing!")
            return render_template('createAGame.html')
        p1 = Player.query.filter_by(username=usernameP1).first()
        p2 = Player.query.filter_by(username=usernameP2).first()
        creator = Player.query.filter_by(username=session['currUsername']).first()
        g.player_one = p1
        g.player_two = p2
        g.creator = creator

        db.session.commit()

        user = Player.query.filter_by(username=session['currUsername']).first()
        games = user.games()
        return render_template("landing.html", games=games, user=session['currUsername'])

@app.route('/deleteGame', methods=['GET', 'POST'])
def deleteAGame():
    if request.method == 'GET':
        games = Game.query.filter_by(creator_id=session['currUserID'])
        return render_template('deleteAGame.html', games=games)
    if request.method == 'POST':
        deleteGameByID = request.form['game_id']
        Game.query.filter_by(id=deleteGameByID).delete()
        db.session.commit()
        user = Player.query.filter_by(username=session['currUsername']).first()
        gaming = user.games()
        return render_template("landing.html", games=gaming, user=session['currUsername'])

@app.route('/logout', methods=['GET'])
def logout():
    if request.method == 'GET':
        session['logged_in'] = False
        session.clear()
        return render_template('login.html')

@app.route("/")
def toLogin():
    return redirect(url_for('login'))

# CLI Commands
@app.cli.command("initdb")
def init_db():
    """Initializes database and any model objects necessary for assignment"""
    db.drop_all()
    db.create_all()

    print("Initialized Connect 4 Database.")


@app.cli.command("devinit")
def init_dev_data():
    """Initializes database with data for development and testing"""
    db.drop_all()
    db.create_all()
    print("Initialized Connect 4 Database.")

    g = Game()
    db.session.add(g)

    p1 = Player(username="tow", birthday=datetime.datetime.strptime('11/06/1991', '%m/%d/%Y').date(), password="pass")
    p2 = Player(username="twaits", birthday=datetime.datetime.strptime('01/14/1987', '%m/%d/%Y').date(), password="pass")

    db.session.add(p1)
    print("Created %s" % p1.username)
    db.session.add(p2)
    print("Created %s" % p2.username)

    g.player_one = p1
    g.player_two = p2
    g.creator = p1

    db.session.commit()
    print("Added dummy data.")


if __name__ == "__main__":
    app.run(threaded=True)
