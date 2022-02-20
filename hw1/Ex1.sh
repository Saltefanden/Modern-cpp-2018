# wordcount the lines streamed from data/data.dat
wc -l < data/data.dat 
# == 175

# Lines that contain dolor or dalor
# $ grep --help
#  -c, --count               print only a count of matching lines per FILE
#  -w, --word-regexp         force PATTERN to match only whole words
# grep -cw "d[oa]lor" data/data.dat
# == 51

# Or those that may contain dolor/dalor + some ending
grep -c "d[oa]lor" data/data.dat
# == 106

# words in data.dat
wc -w < data/data.dat
# == 1904

#Words starting with mol
# $ grep --help
#  -o, --only-matching       show only the part of a line matching PATTERN
#  -w, --word-regexp         force PATTERN to match only whole words
grep -ow "mol\w*" data/data.dat | wc -w
# == 36

# How many txt files in data/test_folder
find data/test_folder -name "*.txt" | wc -l
# == 101