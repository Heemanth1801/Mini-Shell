# Mini-Shell
This minishell almost satisfies all commands <br/>
For redirection and append provide spaces between the operators and follow the conventions that i specifies precisely in this file for all type of commands <br/>
It stores all history of commands of all time stores in a history.txt file <br/>
For the commands like passwd and for some others i don't want to change the password so i make passwd --help <br/>
Which ensures that my shell works not only for that command for also other commands which related to it  <br/>

# LIST OF COMMANDS

cd - it works as usual to the original shell <br/>
ls and all the commands related to ls <br/>
man <br/>
passwd --help <br/>
date <br/>
cal <br/>
clear <br/>
sleep -- here we can specify time , further details can get by typing sleep --help <br/>
history <br/>
exit <br/>
cat <br/>
more <br/>
less <br/>
touch <br/>
mv <br/>
rm <br/>
find --help <br/>
mkdir <br/>
pwd <br/>
rmdir <br/>
chmod <br/>
grep <br/>

And almost all internal commands <br/>
We can type --help with any of the above commands and can get the full information of that command <br/>
And we can execute all the commands that specified by --help <br/>

## AND WE CAN USE SINGLE PIPE FOR ANY TWO OF THE COMMANDS IF IT IS DEFINED FOR THEM AND IT WORKS WELL

cat <filename> | grep <expresion> <br/>
ls | sort <br/>
echo | grep <br/>

Like this it succeeds in all the commands related to those and many more commands <br/>

# ENVIRONMENTAL VARIABLES

To get a particular environment variable type <br/>
getenv <variable_name>  <br/>

To create a particular environment variable name type <br/>
setenv <variable_name> = <variable_value> <br/>

To get all the environment variables type <br/>
printenv <br/>


# THE FOLLOWING TYPES OF REDIRECTIONS CAN BE DONE <br/>

./executablefile < inputfile <br/>
./executablefile > outputfile <br/>
./executablefile < inputfile > outputfile <br/>
command >> outputfile <br/>
