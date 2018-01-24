import flask
from flask import render_template
from flask import request
from flask import url_for
import uuid

import json
import logging

# Date handling 
import arrow # Replacement for datetime, based on moment.js
import datetime # But we still need time
from dateutil import tz  # For interpreting local times


# OAuth2  - Google library implementation for convenience
from oauth2client import client
import httplib2   # used in oauth2 flow

# Google API for services 
from apiclient import discovery

#mongo db
from pymongo import MongoClient
from bson.objectid import ObjectId

try: 
    dbclient = MongoClient()
    db = dbclient.meetme
    coll = db.scheduletimes
    prop = db.prop

except:
    print("Failure opening database.  Is Mongo running? Correct password?")
    sys.exit(1)
 
###
# Globals
###
import CONFIG
app = flask.Flask(__name__)

SCOPES = 'https://www.googleapis.com/auth/calendar.readonly'
CLIENT_SECRET_FILE = CONFIG.GOOGLE_LICENSE_KEY  ## You'll need this
APPLICATION_NAME = 'MeetMe class project'

#############################
#
#  Pages (routed from URLs)
#
#############################

@app.route("/")
@app.route("/index")
def index():
  app.logger.debug("Entering index")
  if 'firstid' not in flask.session:
    flask.session["firstid"] = ""
  if 'link' in flask.session and flask.session["firstid"] != "":
      flask.session.pop('link', None)
  if 'begin_date' not in flask.session:
    init_session_values()
  return render_template('index.html')

@app.route("/choose")
def choose():
    ## We'll need authorization to list calendars 
    ## I wanted to put what follows into a function, but had
    ## to pull it back here because the redirect has to be a
    ## 'return' 
    app.logger.debug("Checking credentials for Google calendar access")
    credentials = valid_credentials()
    if not credentials:
      app.logger.debug("Redirecting to authorization")
      return flask.redirect(flask.url_for('oauth2callback'))
    global gcal_service
    gcal_service = get_gcal_service(credentials)
    app.logger.debug("Returned from get_gcal_service")
    flask.session['calendars'] = list_calendars(gcal_service)
    if flask.session['firstid'] == "":
      return render_template('index.html')
    else:
      return render_template('calendar_choose.html')

@app.route("/_twopeopledirect/<firstpersonid>/<begindate>/<enddate>")
def routing(firstpersonid,begindate,enddate):
  """
  This function takes the information that was persented in the url, and makes some variables
  for the person, it then redirects to choose
  """
  flask.session["begin_date"] = begindate
  flask.session["end_date"] = enddate
  flask.session["daterange"] = arrow.get(begindate).format("M/D/YY h:mm A") + " - " + arrow.get(enddate).format("M/D/YY h:mm A")
  flask.session["disablechoose"] = "True"
  flask.session["firstid"] = firstpersonid
  return flask.redirect(flask.url_for("choose"))

@app.route("/select_proposals", methods=['POST'])
def select_proposals():
  """
  Sets proposed and returns the template called
  """
  flask.session["proposed"] = request.form.getlist('time')
  return render_template("proposed_times.html")

@app.route("/proposed_times")
@app.route("/proposed_times.html")
def render_proposed():
  """
  Returns template called
  """
  return render_template("proposed_times.html")


@app.route("/proposals")
@app.route("/proposals.html")
def render_proprosing():
  """
  Returns template called
  """
  return render_template("proposals.html")

####
#
#  Google calendar authorization:
#      Returns us to the main /choose screen after inserting
#      the calendar_service object in the session state.  May
#      redirect to OAuth server first, and may take multiple
#      trips through the oauth2 callback function.
#
#  Protocol for use ON EACH REQUEST: 
#     First, check for valid credentials
#     If we don't have valid credentials
#         Get credentials (jump to the oauth2 protocol)
#         (redirects back to /choose, this time with credentials)
#     If we do have valid credentials
#         Get the service object
#
#  The final result of successful authorization is a 'service'
#  object.  We use a 'service' object to actually retrieve data
#  from the Google services. Service objects are NOT serializable ---
#  we can't stash one in a cookie.  Instead, on each request we
#  get a fresh serivce object from our credentials, which are
#  serializable. 
#
#  Note that after authorization we always redirect to /choose;
#  If this is unsatisfactory, we'll need a session variable to use
#  as a 'continuation' or 'return address' to use instead. 
#
####

def valid_credentials():
    """
    Returns OAuth2 credentials if we have valid
    credentials in the session.  This is a 'truthy' value.
    Return None if we don't have credentials, or if they
    have expired or are otherwise invalid.  This is a 'falsy' value. 
    """
    if 'credentials' not in flask.session:
      return None

    credentials = client.OAuth2Credentials.from_json(
        flask.session['credentials'])

    if (credentials.invalid or
        credentials.access_token_expired):
      return None
    return credentials


def get_gcal_service(credentials):
  """
  We need a Google calendar 'service' object to obtain
  list of calendars, busy times, etc.  This requires
  authorization. If authorization is already in effect,
  we'll just return with the authorization. Otherwise,
  control flow will be interrupted by authorization, and we'll
  end up redirected back to /choose *without a service object*.
  Then the second call will succeed without additional authorization.
  """
  app.logger.debug("Entering get_gcal_service")
  http_auth = credentials.authorize(httplib2.Http())
  service = discovery.build('calendar', 'v3', http=http_auth)
  app.logger.debug("Returning service")
  return service

@app.route('/oauth2callback')
def oauth2callback():
  """
  The 'flow' has this one place to call back to.  We'll enter here
  more than once as steps in the flow are completed, and need to keep
  track of how far we've gotten. The first time we'll do the first
  step, the second time we'll skip the first step and do the second,
  and so on.
  """
  app.logger.debug("Entering oauth2callback")
  flow =  client.flow_from_clientsecrets(
      CLIENT_SECRET_FILE,
      scope= SCOPES,
      redirect_uri=flask.url_for('oauth2callback', _external=True))
  ## Note we are *not* redirecting above.  We are noting *where*
  ## we will redirect to, which is this function. 
  
  ## The *second* time we enter here, it's a callback 
  ## with 'code' set in the URL parameter.  If we don't
  ## see that, it must be the first time through, so we
  ## need to do step 1. 
  app.logger.debug("Got flow")
  if 'code' not in flask.request.args:
    app.logger.debug("Code not in flask.request.args")
    auth_uri = flow.step1_get_authorize_url()
    return flask.redirect(auth_uri)
    ## This will redirect back here, but the second time through
    ## we'll have the 'code' parameter set
  else:
    ## It's the second time through ... we can tell because
    ## we got the 'code' argument in the URL.
    app.logger.debug("Code was in flask.request.args")
    auth_code = flask.request.args.get('code')
    credentials = flow.step2_exchange(auth_code)
    flask.session['credentials'] = credentials.to_json()
    ## Now I can build the service and execute the query,
    ## but for the moment I'll just log it and go back to
    ## the main screen
    app.logger.debug("Got credentials")
    return flask.redirect(flask.url_for('choose'))

#####
#
#  Option setting:  Buttons or forms that add some
#     information into session state.  Don't do the
#     computation here; use of the information might
#     depend on what other information we have.
#   Setting an option sends us back to the main display
#      page, where we may put the new information to use. 
#
#####

@app.route('/setrange', methods=['POST'])
def setrange():
    """
    User chose a date range with the bootstrap daterange
    widget.
    """
    app.logger.debug("Entering setrange")  
    #flask.flash("Setrange gave us '{}'".format(
    #  request.form.get('daterange')))
    daterange = request.form.get('daterange')
    flask.session['daterange'] = daterange
    daterange_parts = daterange.split()
    flask.session['begin_date'] = interpret_date(daterange_parts[0])
    flask.session['end_date'] = interpret_date(daterange_parts[2])
    app.logger.debug("Setrange parsed {} - {}  dates as {} - {}".format(
      daterange_parts[0], daterange_parts[1], 
      flask.session['begin_date'], flask.session['end_date']))
    return flask.redirect(flask.url_for("choose"))

@app.route('/which_calendar', methods=['POST'])
def whichcalendar():
  """
  This selects the calendar desired from the drop down menu
  """
  calendars = ''.join(request.form.getlist('calendars'))
  [freetimes(i) for i in flask.session['calendars'] if calendars == i['id']]
  if flask.session["firstid"] == '':
    return flask.redirect(flask.url_for("index"))
  else:
    flask.session["firstid"] = ""
    return flask.redirect(flask.url_for("render_proprosing"))

####
#
#   Initialize session variables 
#
####

def init_session_values():
    """
    Start with some reasonable defaults for date and time ranges.
    Note this must be run in app context ... can't call from main. 
    """
    # Default date span = tomorrow to 1 week from now
    now = arrow.now('local')
    tomorrow = now.replace(days=+1)
    nextweek = now.replace(days=+7)
    flask.session["begin_date"] = tomorrow.floor('day').isoformat()
    flask.session["end_date"] = nextweek.ceil('day').isoformat()
    flask.session["daterange"] = "{} - {}".format(
        tomorrow.format("MM/DD/YYYY"),
        nextweek.format("MM/DD/YYYY"))
    # Default time span each day, 8 to 5
    flask.session["begin_time"] = interpret_time("9am")
    flask.session["end_time"] = interpret_time("5pm")

def interpret_time( text ):
    """
    Read time in a human-compatible format and
    interpret as ISO format with local timezone.
    May throw exception if time can't be interpreted. In that
    case it will also flash a message explaining accepted formats.
    """
    app.logger.debug("Decoding time '{}'".format(text))
    time_formats = ["ha", "h:mma",  "h:mm a", "H:mm"]
    try: 
        as_arrow = arrow.get(text, time_formats).replace(tzinfo=tz.tzlocal())
        app.logger.debug("Succeeded interpreting time")
    except:
        app.logger.debug("Failed to interpret time")
        flask.flash("Time '{}' didn't match accepted formats 13:30 or 1:30pm"
              .format(text))
        raise
    return as_arrow.isoformat()

def interpret_date( text ):
    """
    Convert text of date to ISO format used internally,
    with the local time zone.
    """
    try:
      as_arrow = arrow.get(text, "MM/DD/YYYY").replace(
          tzinfo=tz.tzlocal())
    except:
        flask.flash("Date '{}' didn't fit expected format 12/31/2001")
        raise
    return as_arrow.isoformat()

def next_day(isotext):
    """
    ISO date + 1 day (used in query to Google calendar)
    """
    as_arrow = arrow.get(isotext)
    return as_arrow.replace(days=+1).isoformat()

####
#
#  Functions (NOT pages) that return some information
#
####
  
def freetimes(calendar):
  """
  This get's the free times and the busy times within the certain time range
  it querys the calendar db and then puts them into a list. 
  """
  busyq = {
          "timeMin":flask.session['begin_date'],
          "timeMax":flask.session['end_date'],
          "items": [{"id": calendar['id']}]
          }
  busy_result = (gcal_service.freebusy().query(body=busyq).execute())['calendars'][calendar['id']]['busy']
  #busy times
  events = sorted([[arrow.get(event['start']).to('local'),arrow.get(event['end']).to('local')] for event in busy_result])
  freetimes = [[events[i][1],events[i+1][0]] for i in range(len(events) - 1) if events[i+1][0] > events[i][1]]
  new = new_entry(freetimes)
  if not flask.session["firstid"]:
    createlink(new)
    if len(freetimes) != 0:
      [flask.flash("From " + free[0].format('M/D/YY h:mm A') + " to " + free[1].format('M/D/YY h:mm A') + " you are free")for free in freetimes]
    else:
      flask.flash("No time avaiable")
  else:
    compare_two(flask.session["firstid"], new)
  return

def createlink(firstpersonid):
  """
  This creates the link for someone to share with their friend so they can compare times
  """
  begindate = str(flask.session['begin_date'])
  enddate = str(flask.session['end_date'])
  firstpersonid = str(firstpersonid)
  flask.session["link"] = "localhost:" + str(CONFIG.PORT) + "/_twopeopledirect/"+ firstpersonid +"/"+ begindate + "/" + enddate
  return

def new_entry(free_times):
  """
  This makes a new entry in the db
  """
  current_id = ""
  str_free_times = []
  for time_range in free_times:
    str_free_times.append([str(times) for times in time_range])
  person_number = str(coll.find().count())
  coll.insert_one({
  'Person': str(coll.find().count()),
  'free': str_free_times
})

  person_id = coll.find({"Person": person_number})[0]["_id"]
  return person_id


def compare_two(original_id, new_id):  
  """
  This starts to compare the free times of each person
  """
  original_id = ObjectId(original_id)
  new_id = ObjectId(new_id)
  new_free_times = []
  firstperson_freetimes = convert_to_arrowobj(coll.find({'_id':original_id})[0]["free"])
  secondperson_freetimes = convert_to_arrowobj(coll.find({'_id':new_id})[0]["free"])
  for time_range1 in firstperson_freetimes:
    for time_range2 in secondperson_freetimes:
      if date_intersection(time_range1,time_range2):
        new_free_times.append(find_intersection(time_range1, time_range2))
  flask.session["freetimecompare"] = new_free_times
  flask.session["freetimecomparestr"] = range_string(new_free_times)
  return 

def date_intersection(t1,t2):
  """
  Finds the date intersection
  """
  t1start, t1end = t1[0], t2[0]
  t2start, t2end = t2[0], t2[1]
  return (t1start <= t2start < t1end) or (t2start <= t1start <= t2end)

def find_intersection(t1,t2):
  """
  it gives the intersection of the times 
  """
  t1start, t1end = t1[0], t2[0]
  t2start, t2end = t2[0], t2[1]
  if (t1start <= t2start < t1end):
    return [t2start, t1end]
  elif(t2start <= t1start < t2end):
    return [t1start, t2end]

def range_string(list_of_freetimes):
  """
  This creates a string for the range of free times 
  """
  new_list = []
  for i in list_of_freetimes:
    new_list.append("From " + i[0].format("M/D/YY h:mm A") + " to " + i[1].format("M/D/YY h:mm A"))
  return list_of_freetimes

def convert_to_arrowobj(listoftimes):
  """
  This converts an item to an arrow object
  """
  new_list = []
  for time_range in listoftimes:
      new_list.append([arrow.get(i) for i in time_range])
  return sorted(new_list)

def list_calendars(service):
    """
    Given a google 'service' object, return a list of
    calendars.  Each calendar is represented by a dict, so that
    it can be stored in the session object and converted to
    json for cookies. The returned list is sorted to have
    the primary calendar first, and selected (that is, displayed in
    Google Calendars web app) calendars before unselected calendars.
    """
    app.logger.debug("Entering list_calendars")  
    calendar_list = service.calendarList().list().execute()["items"]
    result = [ ]
    for cal in calendar_list:
        kind = cal["kind"]
        id = cal["id"]
        if "description" in cal: 
            desc = cal["description"]
        else:
            desc = "(no description)"
        summary = cal["summary"]
        # Optional binary attributes with False as default
        selected = ("selected" in cal) and cal["selected"]
        primary = ("primary" in cal) and cal["primary"]
        

        result.append(
          { "kind": kind,
            "id": id,
            "summary": summary,
            "selected": selected,
            "primary": primary
            })
    return sorted(result, key=cal_sort_key)


def cal_sort_key( cal ):
    """
    Sort key for the list of calendars:  primary calendar first,
    then other selected calendars, then unselected calendars.
    (" " sorts before "X", and tuples are compared piecewise)
    """
    if cal["selected"]:
       selected_key = " "
    else:
       selected_key = "X"
    if cal["primary"]:
       primary_key = " "
    else:
       primary_key = "X"
    return (primary_key, selected_key, cal["summary"])


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
        normal = arrow.get( time )
        return normal.format("HH:mm")
    except:
        return "(bad time)"
    
#############


if __name__ == "__main__":
  # App is created above so that it will
  # exist whether this is 'main' or not
  # (e.g., if we are running in a CGI script)

  app.secret_key = str(uuid.uuid4())  
  app.debug=CONFIG.DEBUG
  app.logger.setLevel(logging.DEBUG)
  # We run on localhost only if debugging,
  # otherwise accessible to world
  if CONFIG.DEBUG:
    # Reachable only from the same computer
    app.run(port=CONFIG.PORT)
  else:
    # Reachable from anywhere 
    app.run(port=CONFIG.PORT,host="0.0.0.0")
    