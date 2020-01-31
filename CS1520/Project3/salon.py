from flask import Flask
from flask import Flask, flash, redirect, render_template, request, session, abort, url_for
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime
from functools import wraps
from tabledef import db, Patron, Appointments, Stylist
from sqlalchemy import or_, and_
import os

app = Flask(__name__)

project_dir = os.path.dirname(os.path.abspath(__file__))
database_file = "sqlite:///{}".format(os.path.join(project_dir, "salon.db"))
app.config["SQLALCHEMY_DATABASE_URI"] = database_file
app.secret_key = "super secret key"

db.init_app(app)

@app.cli.command('initdb')
def initdb_command():
    db.drop_all()
    db.create_all()
    db.session.add(Patron('Bob Smith', 'bob', 'smith'))
    db.session.commit()
    print(Patron.query.all())

@app.route('/')
def home():
    return render_template('home.html')

@app.route('/viewAppointments', methods=['GET', 'POST'])
def viewAppointments():
    if request.method == 'GET':
        return render_template('viewAppointments.html')
    if request.method == 'POST':
        appointmentID = request.form['aptID']
        Appointments.query.filter_by(appointmentID=appointmentID).all()


@app.route('/cancelAppointment', methods=['GET', 'POST'])
def cancelAppointment():
    if request.method == 'GET':
        return render_template('cancelAppointment.html')
    if request.method == 'POST':
        appointmentID = request.form['aptID']

@app.route('/createAppointment', methods=['GET', 'POST'])
def createAppointment():
    if request.method == 'GET':
        return render_template('createAppointment.html')
    if request.method == 'POST':
        appointmentID = request.form['aptID']
        date = request.form['date']
        time = request.form['time']
        patronUser = request.form['uName']
        stylist = request.form['stylist']
        try:
            #assert Stylist.query.filter_by(username=stylist).first() != None
            assert Appointments.query.filter_by(time=time).first() == None
        except:
            flash("Stylist is not available or time slot is taken")
            return render_template('createAppointment.html')
        new_appt = Appointments(appointmentID, date, time, patronUser, stylist)
        db.session.add(new_appt)
        db.session.commit()
        return render_template('patronPage.html')

@app.route('/createStylistAccount', methods=['GET', 'POST'])
def stylistSignUp():
    if request.method == 'GET':
        return render_template('stylistSignUp.html')
    if request.method == 'POST':
        fullName = request.form['fName']
        username = request.form['uName']
        password = request.form['password']
        try:
            assert Stylist.query.filter_by(username=username).first() == None
            assert len(password) > 0
        except:
            flash("Password Length must be greater than 0 or username is taken!")
            return render_template('stylistSignUp.html')
        new_stylist = Stylist(fullName, username, password)
        db.session.add(new_stylist)
        db.session.commit()
        return render_template('stylistLogin.html')

@app.route('/stylistLogout')
def stylistLogout():
    session['stylist_logged_in'] = False
    return render_template('home.html')

@app.route('/stylistPage')
def stylistPage():
    if not session.get('stylist_logged_in'):
        return render_template('stylistLogin.html')
    else:
        return render_template('stylistPage.html')

@app.route('/stylistLogin', methods=['GET', 'POST'])
def stylistLogin():
    if request.method == 'GET':
        if session['stylist_logged_in'] == True:
            return render_template('stylistPage.html')
        return render_template('stylistLogin.html')
    if request.method == 'POST':
        user = Stylist.query.filter_by(username=request.form['username']).first()
        if user != None:
            password = user.password
            if password == request.form['password']:
                session['stylist_logged_in'] = True
                return redirect(url_for('stylistPage'))
            else:
                flash("Incorrect Password!")
                return render_template('stylistLogin.html')
        else:
            flash("Invalid Username!")
            return render_template('stylistLogin.html')

@app.route('/patronPage')
def patronPage():
    if not session.get('patron_logged_in'):
        return render_template('patronLogin.html')
    else:
        return render_template('patronPage.html')

@app.route('/patronLogin', methods=['GET', 'POST'])
def patronLogin():
    if request.method == 'GET':
        if session['patron_logged_in'] == True:
            return render_template('patronPage.html')
        return render_template('patronLogin.html')
    if request.method == 'POST':
        user = Patron.query.filter_by(username=request.form['username']).first()
        if user != None:
            password = user.password
            if password == request.form['password']:
                session['patron_logged_in'] = True
                return redirect(url_for('patronPage'))
            else:
                flash("Incorrect Password!")
                return render_template('patronLogin.html')
        else:
            flash("Invalid Username!")
            return render_template('patronLogin.html')

@app.route('/patronLogout')
def patronLogout():
    session['patron_logged_in'] = False
    return render_template('home.html')

@app.route('/patronSignUp', methods=['GET', 'POST'])
def patronSignUp():
    if request.method == 'GET':
        return render_template('patronSignUp.html')
    if request.method == 'POST':
        fullName = request.form['fName']
        username = request.form['uName']
        password = request.form['password']
        try:
            assert Patron.query.filter_by(username=username).first() == None
            assert len(password) > 0
        except:
            flash("Password Length must be greater than 0 or username is taken!")
            return render_template('patronSignUp.html')
        new_patron = Patron(fullName, username, password)
        db.session.add(new_patron)
        db.session.commit()
        return render_template('patronLogin.html')

@app.route('/ownerLogin')
def ownerLogin():
    if not session.get('logged_in'):
        # if session is not yet logged in, continue showing login.html
        return render_template('login.html')
    else:
        # otherwise render this page
        return render_template("ownerPage.html")

@app.route('/ownerLogin', methods=['POST'])
def do_admin_login():
    if request.form['password'] == 'pass' and request.form['username'] == 'owner':
        session['logged_in'] = True
    else:
        flash('wrong password!')
    return ownerLogin()

@app.route("/logout")
def logout():
    session['logged_in'] = False
    return home()

if __name__ == "__main__":
    app.run(debug=True)
