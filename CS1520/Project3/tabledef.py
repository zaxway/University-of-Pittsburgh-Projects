from flask import Flask, render_template
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime

db = SQLAlchemy();
########################################################################
class Patron(db.Model):
    __tablename__ = "Patrons"
    name = db.Column(db.String(32))
    username = db.Column(db.String(32), primary_key=True, unique=True)
    password = db.Column(db.String(32))

    #----------------------------------------------------------------------
    def __init__(self, name, username, password):
        self.name = name
        self.username = username
        self.password = password

class Appointments(db.Model):
    __tablename__ = "Appointments"
    appointmentID = db.Column(db.String(32), primary_key=True)
    date = db.Column(db.DateTime)
    time = db.Column(db.DateTime)
    patronUser = db.Column(db.String(32))
    stylistUser = db.Column(db.String(32))

    def __init__(self, appointmentID, date, time, patronUser, stylistUser):
        self.appointmentID = appointmentID
        self.date = date
        self.time = time
        self.patronUser = patronUser
        self.stylistUser = stylistUser

class Stylist(db.Model):
    __tablename__ = "Stylist"
    name = db.Column(db.String(32))
    username = db.Column(db.String(32), primary_key=True, unique=True)
    password = db.Column(db.String(32))

    def __init__(self, name, username, password):
        self.name = name
        self.username = username
        self.password = password
