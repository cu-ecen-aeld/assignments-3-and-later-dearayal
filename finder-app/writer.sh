#!/bin/sh
# Script for assignment 1
# Author: Daniel Araya

 if [ $# -ne 2 ]
 then
     echo "Wrong number of arguments!"
     echo "Usage: writer.sh <writefile> <writestr>"
     exit 1  # Exits with value 1 error and print statement
 fi

 # First argument is a full path to a file
 writefile=$1

 # If file exists delete it    
 if [ -e  $writefile ]; then
 #   echo "File exists!"
    rm -r $writefile
 fi

 # Create new file 
 $(mkdir -p "$(dirname "$writefile")" && touch "$writefile")
 $(chmod 777 $writefile)
 
 # Second argument is a text string which will be written withing this file
 writestr=$2
 echo $writestr > $writefile

 exit 0  
