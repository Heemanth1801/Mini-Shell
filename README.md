# Mini-Shell
This minishell almost satisfies all commands
For redirection and append provide spaces between the operators and follow the conventions that i specifies precisely in this file for all type of commands
It stores all history of commands of all time stores in a history.txt file
For the commands like passwd and for some others i don't want to change the password so i make passwd --help 
Which ensures that my shell works not only for that command for also other commands which related to it 

/*** LIST OF COMMANDS ***/

cd - it works as usual to the original shell
ls and all the commands related to ls
man
passwd --help
date
cal
clear
sleep -- here we can specify time , further details can get by typing sleep --help
history
exit
cat
more
less
touch
mv
rm
find --help
mkdir
pwd
rmdir
chmod
grep

And almost all internal commands
We can type --help with any of the above commands and can get the full information of that command
And we can execute all the commands that specified by --help

/*** AND WE CAN USE SINGLE PIPE FOR ANY TWO OF THE COMMANDS IF IT IS DEFINED FOR THEM AND IT WORKS WELL ***/

cat <filename> | grep <expresion>
ls | sort
echo | grep

Like this it succeeds in all the commands related to those and many more commands

/*** ENVIRONMENTAL VARIABLES ***/

To get a particular environment variable type
getenv <variable_name> 

To create a particular environment variable name type
setenv <variable_name> = <variable_value>

To get all the environment variables type
printenv


/*** THE FOLLOWING TYPES OF REDIRECTIONS CAN BE DONE ***/

./executablefile < inputfile
./executablefile > outputfile
./executablefile < inputfile > outputfile
command >> outputfile
