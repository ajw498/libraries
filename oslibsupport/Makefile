# Makefile for OSLibSupport

all:
   AMU -f <Make$Dir>.Choices.MakeFile     -desktop
   AMU -f <Make$Dir>.Err.MakeFile 	  -desktop
   AMU -f <Make$Dir>.Events.MakeFile 	  -desktop
   AMU -f <Make$Dir>.Message.MakeFile 	  -desktop
   AMU -f <Make$Dir>.Task.MakeFile 	  -desktop
   AMU -f <Make$Dir>.X.MakeFile 	  -desktop
   LibFile -o -c <Make$Dir>.o.OSLibSupport -v <Make$Dir>.FileList 
   @Echo <Sys$Time> Library "OSLibSupport" Made

