"""
Test program for pre-processing schedule
"""
import arrow

base = arrow.now()

def process(raw):
    """
    Line by line processing of syllabus file.  Each line that needs
    processing is preceded by 'head: ' for some string 'head'.  Lines
    may be continued if they don't contain ':'.  
    """
    field = None
    entry = { }
    cooked = [ ] 
    for line in raw:
        line = line.rstrip()
        if len(line) == 0:
            continue
        parts = line.split(':')
        if len(parts) == 1 and field:
            entry[field] = entry[field] + line
            continue
        if len(parts) == 2: 
            field = parts[0]
            content = parts[1]
        else:
            raise ValueError("Trouble with line: '{}'\n".format(line) + 
                "Split into |{}|".format("|".join(parts)))

        if field == "begin":
            try:
                base = arrow.get(content, "M/D/YYYY")
            except:
                raise ValueError("Unable to parse date {}".format(content))

        elif field == "week":
            if entry:
                cooked.append(entry)
                entry = { }
            entry['topic'] = ""
            entry['project'] = ""
            entry['week'] = content
            if len(cooked) == 0: #Checks to see if we should use base or should add a week
                entry['weekstartday'] = str(base.format("MM/DD"))
            elif len(cooked) != 0:
                base = base.replace(weeks=+1)
                entry['weekstartday'] = str(base.format("MM/DD"))
            if thisweek(base): #checks to see if the date is within the week
                entry['currentweek'] = True
            else:
                entry['currentweek'] = False
        elif field == 'topic' or field == 'project':
            entry[field] = content

        else:
            raise ValueError("Syntax error in line: {}".format(line))

    return cooked

def thisweek(base):
    """
    This function checks to see if the current date is within a week of the base date given.
    Returns:
        Bool
    """
    base_range = base.replace(days=+6)
    too_far = base.replace(weeks=+1)
    current_time = arrow.utcnow()
    if current_time < base_range and current_time > base:
        return True
    else:
        return False

def main():
    f = open("static/schedule.txt")
    parsed = process(f)
    print(parsed)

if __name__ == "__main__":
    main()

    
    
            
    
