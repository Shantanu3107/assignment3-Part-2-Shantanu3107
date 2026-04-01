#!/bin/bash

#check for correct number of arguments
if [ $# -ne  2 ]; 
then
   echo "Error: Two arguments required."
   echo "Usage: $0 <filesdir> <searchstr>"
   exit 1
fi

filesdir=$1
searchstr=$2

#Check if filesdir is a valid directory
if [ ! -d "$filesdir" ]; 
then
   echo "Error: $filesdir does not represent a directory on the filesystem."
   exit 1
fi

#Count number of files 
X=$(find "$filesdir" -type f | wc -l)

#Count number of matching lines
Y=$(grep -r "$searchstr" "$filesdir" 2>/dev/null | wc -l)

# Print result
echo "The number of files are $X and the number of matching lines are $Y"

