"""
Very simple Flask web site, with one page
displaying a course schedule.

"""

import flask
from flask import render_template
from flask import request
from flask import url_for
from flask import jsonify # For AJAX transactions

import json
import logging

# Date handling 
import arrow # Replacement for datetime, based on moment.js
import datetime # But we still need time
from dateutil import tz  # For interpreting local times

# Our own module
# import acp_limits


###
# Globals
###
app = flask.Flask(__name__)
import CONFIG

import uuid
app.secret_key = str(uuid.uuid4())
app.debug=CONFIG.DEBUG
app.logger.setLevel(logging.DEBUG)


###
# Pages
###

@app.route("/")
@app.route("/index")
@app.route("/calc")
def index():
  app.logger.debug("Main page entry")
  return flask.render_template('calc.html')


@app.errorhandler(404)
def page_not_found(error):
    app.logger.debug("Page not found")
    flask.session['linkback'] =  flask.url_for("index")
    return flask.render_template('page_not_found.html'), 404


###############
#
# AJAX request handlers 
#   These return JSON, rather than rendering pages. 
#
###############
@app.route("/_calc_times")
def calc_times():
  """
  Calculates open/close times from distnace, using rules 
  described at http://www.rusa.org/octime_alg.html.
  Expects two URL-encoded argument, the distnace. 
  """

  distance_speeds = {0:[0,15,34], 1:[201,15,32], 2:[401,15,30], 3:[601,11.428,28], 4:[1001,13.333,26]} # This is the speeds if going a certain distance

  app.logger.debug("Got a JSON request");
  distance = request.args.get('distance', 0, type=int)
  currenttime = request.args.get('currenttime', 1, type=str)
  miles = request.args.get('units', 2, type=str)
  first_checkpoint = request.args.get('first_checkpoint', 3, type=str)
  total_distance = request.args.get('total_distance', 4, type=int)
  speedneeded = []
  if miles == "True": #converts miles to km if in miles
    distance = distance * 1.609
  try: #tries to use the current time provided, if not then it uses default
    start_time = arrow.get(currenttime, "M/D/YY H:m") 
  except:
    start_time = arrow.get('1/1/15 0:0', "M/D/YY H:m")
  for i in range(5): #Goes through the various speeds and checks to see which one to use
    if distance >= distance_speeds[i][0]:
      speedneeded = distance_speeds[i]
    else:
      break
  open_raw_time = distance/speedneeded[2]
  close_raw_time = distance/speedneeded[1]
  oh, om = divmod(open_raw_time, 1) #Gets the whole number and the float number
  oh = int(oh)
  ch, cm = divmod(close_raw_time, 1)
  ch = int(ch)
  openminutes = round(om * 60)
  closeminutes = round(cm * 60)
  if first_checkpoint == "True": #This is if the user just inputted on the first time
    opentime = start_time.format('MM/DD/YY HH:mm')
    closetime = start_time.replace(hours=+1).format('MM/DD/YY HH:mm')
  else:
    opentime = start_time.replace(hours=+int(oh)).replace(minutes=+openminutes).format('MM/DD/YY HH:mm')
    closetime = start_time.replace(hours=+int(ch)).replace(minutes=+closeminutes).format('MM/DD/YY HH:mm')
  last_opentime = opentime
  return jsonify(opentime=opentime, closetime=closetime)
 
#################
#
# Functions used within the templates
#
#################

@app.template_filter( 'fmtdate' )
def format_arrow_date( date ):
    try: 
        normal = arrow.get( date )
        return normal.format("ddd MM/DD/YYYY")
    except:
        return "(bad date)"

@app.template_filter( 'fmttime' )
def format_arrow_time( time ):
    try: 
        normal = arrow.get( date )
        return normal.format("hh:mm")
    except:
        return "(bad time)"



#############


if __name__ == "__main__":
    import uuid
    app.secret_key = str(uuid.uuid4())
    app.debug=CONFIG.DEBUG
    app.logger.setLevel(logging.DEBUG)
    app.run(port=CONFIG.PORT)

    
