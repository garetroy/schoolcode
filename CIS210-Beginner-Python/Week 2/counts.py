"""
Count the number of occurrences of each major code in a file.
Authors: Garett Roberts
Credits: #FIXME

Input is a file in which major codes (e.g., "CIS", "UNDL", "GEOG")
appear one to a line. Output is a sequence of lines containing major code
and count, one per major.
"""

import argparse

def count_codes(majors_file):
    """
    Adds majors to a list.
    Counts the amount of times a major is in a list and then prints the major and the count in the list.
    If it is already a previously gone through major, it skips it and goes to the next.
    """
    majors = [ ]
    gone_through = [ ]

    for line in majors_file:
        majors.append(line.strip())

    majors = sorted(majors)
    count = 0
    for major in majors:
        count = majors.count(major)
        if major in gone_through:
            continue
        gone_through.append(major)
        print(major, count)

def main( ):
    """
    Interaction if run from the command line.
    Usage:  python3 counts.py  majors_code_file.txt
    """
    parser = argparse.ArgumentParser(description="Count major codes")
    parser.add_argument('majors', type=argparse.FileType('r'),
                        help="A text file containing major codes, one major code per line.")
    args = parser.parse_args()  # gets arguments from command line
    majors_file = args.majors
    count_codes(majors_file)
    
    
if __name__ == "__main__":
    main( )