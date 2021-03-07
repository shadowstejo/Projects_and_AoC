dreinull.py is a script for a geocache called md5sum in Hannover.
it uses a slightly modified md5sum implementation from rosetta code.
The main-part is fully self-written and checks through 2 interlooped loops and compares the modified md5sum to the given cypher-code.
If both fit, the two names plus the final coordinates are output. 
The two names are a bonus for the log which is written on the geocaching-page.


zweite.py is a script for another geocache which checks word for anagrams. 
it sorts and then compares all uppercased letters in a textfile to see if they match. 
Sadly it doesn't know if 2 or 3 following words would match. that would exceed computing power.
Just a first trial, in the end we solved it with only using this script 2 or 3 times on a different text file.
Hannover.txt is just an example (it's the Hannover Wikipedia Page)
