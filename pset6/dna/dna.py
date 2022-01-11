import csv
from sys import exit, argv



#psuedocode:
#open files
#get the dna strings that we are looking for
#loop through the .txt file. if the string is repeated, return the number of times
#compare the number of times repeated with csvfile and comapre people
def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # open the two files from command line
    database = open(argv[1], 'r')
    sequence = open(argv[2],'r')

    # make the database into a dictionary which contains the strings we want
    db_file = csv.DictReader(database)
    #loads the strings we are comparing
    strs = db_file.fieldnames[1:]

    # put the sequence in a file we can read
    sequence_copy = sequence.read()
    sequence.close()

    #create a dictionary where we have the sequence and the amount of times it showes up
    repeats = {}
    for str in strs:
        # will make the keys the dna strings we are looking for and will give them values of the most repeats
        repeats[str] = countRepeats(str, sequence_copy)

    for row in db_file:
        if match(strs, repeats, row) == True:
            print(f"{row['name']}")
            database.close()
            return 
    print("No match")
    database.close()


def countRepeats(str, sequence):
    counter = 0
    # "ATCT" if found looks for => "ATCTATCT" and so on.
    while str*(counter+1) in sequence:
        counter += 1
    return counter

def match(strs, repeats, row):
    for seq in strs:
        # check if there is no match because if it returns True, we know for sure there is a match
        if repeats[seq] != int(row[seq]):
            return False
    return True



if __name__ == "__main__":
    main()