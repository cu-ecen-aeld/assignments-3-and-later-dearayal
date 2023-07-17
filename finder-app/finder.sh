#!/bin/sh
# Script for assignment 1
# Author: Daniel Araya

 if [ $# -ne 2 ]
 then
     echo "Wrong number of arguments!"
     echo "Usage: finder.sh <filesdir> <searchstr>"
     exit 1  #  Exits with value 1 error and print statement
 fi

 # First argument is a path to a directory on the filesystem -> filesdir
 if [ -d  $1 ]
 then
    filesdir=$1
 else 
     echo $1 "does not represents a directory"
     exit 1  #  Exits with value 1 error and print statement
 fi
 
  # Second argument is a text string which will be searched -> searchstr
  searchstr=$2

  # Count files in filesdir
  files=$(ls $filesdir | wc -l)
  
  # Count occurences for each file 
  sum=0
  matches=$(grep -r -c $searchstr $filesdir | awk 'BEGIN{FS=":"}{sum+=$2}END{print sum}')

  # Print summary message
  echo "The number of files are" $files "and the number of matching lines are" $matches
  exit 0  
