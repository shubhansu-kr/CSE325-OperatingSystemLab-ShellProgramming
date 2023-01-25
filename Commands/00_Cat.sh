# !/bin/bash

# Cat Command

cat text1.txt
cat text2.txt
cat text3.txt

# -s is used to suppress multiple empty lines in the file.
cat -s text1.txt 

# >> : Double arrow appends the text 
cat text1 >> text2

# > : single arrow overwrites the file 
cat text1 > text2 

# Merge multiple files into one 
cat text1.txt text2.txt text3.txt >> text4.txt



# cat Command manual: 

# Usage: cat [OPTION]... [FILE]...
# Concatenate FILE(s) to standard output.

# With no FILE, or when FILE is -, read standard input.

#   -A, --show-all           equivalent to -vET
#   -b, --number-nonblank    number nonempty output lines, overrides -n
#   -e                       equivalent to -vE
#   -E, --show-ends          display $ at end of each line
#   -n, --number             number all output lines
#   -s, --squeeze-blank      suppress repeated empty output lines
#   -t                       equivalent to -vT
#   -T, --show-tabs          display TAB characters as ^I
#   -u                       (ignored)
#   -v, --show-nonprinting   use ^ and M- notation, except for LFD and TAB
#       --help     display this help and exit
#       --version  output version information and exit

# Examples:
#   cat f - g  Output f's contents, then standard input, then g's contents.
#   cat        Copy standard input to standard output.

# GNU coreutils online help: <https://www.gnu.org/software/coreutils/>
# Full documentation <https://www.gnu.org/software/coreutils/cat>
# or available locally via: info '(coreutils) cat invocation'