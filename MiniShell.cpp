#include<bits/stdc++.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

using namespace std;

//function for printing history

void printinghistory()
{
    //opening the respective file to print the history
    ifstream file("history.txt");
    string str;
    while(getline(file, str)) {
        cout << str << "\n";
    }
}

//funcition for printing directory

void printdir()
{
     char cwd[256];
     //geting the directory by the getline command
     getcwd(cwd,256);
     cout<<cwd<<"~$"<<endl;
     cout<<">>>>";
}

//here input will be saved in a history.txt file

void savinghistory(string a)
{
    //opening the file to save the input history
    ofstream b("history.txt",ios::app);
    b<<a<<"\n";
}

//this function takes input from the for the shell

int takingcommands(string& input)
{
    //calling the printdir function to print the currrent working directory
    printdir();
    getline(cin,input);
    if(input.size() == 0){
            return 0;
    }
    else{
        return 1;
    }
}

//seperating words in the command

void seperatingwords(string& a, vector<string>& b)
{
    stringstream X(a);
    string T;
    //taking input and seperating the words or removing the unnecessary spaces
    while (getline(X, T, ' ')) {
        while (T.length()==0 ){
            getline(X, T, ' ');
            }
        b.push_back(T);
    }
}


//looking for the cd command in the input and changing the directory to the respective path

int directory (vector<string> a)
{
    int i;
    //chedking for cd command itseld is there or not
    if((a[0].compare("cd"))==0){
        if(a.size()==1){
            char * b;
            b=getenv("USER");
            chdir("/home");
            i = chdir(b);
        }//changing the path to the respective pathmentioned
        else{
        //converting the string to a char pointer as the function only takes char pointers
            char char_array[a[1].size()];
            strcpy(char_array, a[1].c_str());
            //calling inbuilt function to change the directory
            i = chdir(char_array);
        }
        if(i!=0){
        //if no such directory exits in the present directory
            cout<<"directory not exits"<<endl;
        }
        return 1;
    }
    else{
    //returning zero if no cd command is there in the input command
        return 0;
    }
}

//checking for the exit and history commands

int exitcommand(vector<string> a)
{
    if(a.size()==1){
        if((a[0].compare("history"))==0){
        //calling printinghistory function to print the previous commands
            printinghistory();
            return 1;
        }
        else if((a[0].compare("exit"))==0){
        //exiting the shell
            exit(0);
            return 1;
        }
        else{
        // returning zero if there are mistakes in the command
            return 0;
        }
    }
    else{
    //returning zero if the size is more than one
        return 0;
    }
}

//checking for the append command command in the input

int detectingappend(vector<string> a)
{
    for(int i=0; i<a.size();i++){
        if((a[i].compare(">>"))==0 || (a[i].compare(">"))==0){
        //returning 1 if >>  or > is there otherwise zero
            return 1;
        }
    }
    return 0;
}

//checking for all the internal commands

int internalcommands(vector<string> a)
{
    int value=0;
    //changing the all strings into the pointers to a char as exec fumctiond only take char pointers
    char *args[a.size()+1];
    for(int i=0;i<a.size();i++){
        args[i] = new char[a[i].size()];
        strcpy(args[i], a[i].c_str());
    }
    args[a.size()]=nullptr;

    //intiating a child process which will execute the exec functions
    //because exec functions replace the total running program but we need to run the shell after that also

    if(fork()==0){
    //passing the commands to the execvp to execute it
        value = execvp(args[0],args);
    }
    wait(nullptr);

    if(value==0){
    //checking for whether the command is executed or not
    //if not returining zero
        return 1;
    }
    else{
        return 0;
    }
}

//checking for the redirection commands in the given command

int redirection(vector<string> a)
{
    //checking for the executable file
    if(a[0][0]=='.' && a[0][1]=='/'){

    //removing the ./ command to pass the rest of the commands the execv function
        a[0].erase(a[0].begin());
        a[0].erase(a[0].begin());

        //checking for the input redirection operation
        if((a[1].compare("<"))==0 && a.size()==3){

        //removing the redirection operators
            a.erase(a.begin()+1);

            char *args[a.size()+1];
            for(int i=0;i<a.size();i++){
                args[i] = new char[a[i].size()];
                strcpy(args[i], a[i].c_str());
            }
            args[a.size()]=nullptr;

            //creating a child process to execute the redirecction command

                if(fork()==0){
                        int file2 = open(args[1],O_RDONLY ,0777);
                        dup2(file2,STDIN_FILENO);
                        execv(args[0],args);
                        close(file2);
                }
                wait(nullptr);
                cout<<endl;
                return 1;

        }
        //checking for the input and output redirection
        else if((a[1].compare("<"))==0 && (a[3].compare(">"))==0){

            a.erase(a.begin()+1);
            a.erase(a.begin()+2);

            char *args[a.size()+1];
            for(int i=0;i<a.size();i++){
                args[i] = new char[a[i].size()];
                strcpy(args[i], a[i].c_str());
            }
            args[a.size()]=nullptr;

            //creating a child process to execute the redirection commands

            if(fork()==0){
                    int file2 = open(args[1],O_RDONLY ,0777);
                    int file = open(args[2],O_WRONLY | O_CREAT , 0777);
                    dup2(file,STDOUT_FILENO);
                    dup2(file2,STDIN_FILENO);
                    execv(args[0],args);
                    close(file);
                    close(file2);
            }
            wait(nullptr);

        }
        else{
            return 0;
        }
        return 1;
    }
    return 0;
}

//checking for the | command if it detects then it will return 1 otherwise 0

int detecting_pipe(vector<string> a)
{
    //checking for the | command
    for(int i=0;i<a.size();i++){
        if((a[i].compare("|"))==0){
            return 1;
        }
    }
    return 0;
}

//seperating the commands seperated by the pipe

int piping(vector<string> a )
{
    if(detecting_pipe(a)){
        int pipe_index;
        //changing the strings into the char pointers
        for(int i=0;i<a.size();i++){
            if(a[i].compare("|")==0){
                pipe_index = i;break;
            }
        }
        //storing the commands in a seperate char pointers so that one will be executed after the other by child process

        char *args[pipe_index+1] , *args1[a.size()-pipe_index];
        for(int i=0;i<a.size();i++){
                if(i<pipe_index){
                args[i] = new char[a[i].size()];
                strcpy(args[i], a[i].c_str());
                }
                else if(i>pipe_index){
                args1[i-pipe_index-1] = new char[a[i].size()];
                strcpy(args1[i-pipe_index-1], a[i].c_str());
                }
        }
        args[pipe_index]=nullptr;
        args[a.size()-pipe_index-1]=nullptr;

        //creating two file descriptors to redirect the standard input and output

        int fd[2],i;

        pipe(fd);

        int pid1,pid2;

        //this child process first execute the command before the pipe and output will be redirected to the second command after pipe
        pid1=fork();


        if(pid1==0){
            dup2(fd[1],1);
            close(fd[0]);
            close(fd[1]);
            if(execvp(args[0],args)<0){
                return 0;
            }
            execvp(args[0],args);
            //exit(0);
        }


        //this child process will execute the second command and now print the respected output on the screen if required
        pid2 = fork();

        if(pid2==0){

            dup2(fd[0],0);
            close(fd[0]);
            close(fd[1]);

            if(execvp(args1[0],args)<0){
                return 0;
            }
            execvp(args1[0],args);

            //exit(0);
        }

        close(fd[0]);
        close(fd[1]);
        waitpid(pid1,NULL,0);
        waitpid(pid2,NULL,0);


        return 1;
    }
    return 0;
}

//redirecting the output to the file mentioned after the append command

int appendcommand(vector<string> a)
{
    //checking whether the append command is there in the given in the commnad or not
    if(detectingappend(a)){
        int append_index;
        //searching the index of the >> in the given command
        for(int i=0;i<a.size();i++){
            if((a[i].compare(">>"))==0 || (a[i].compare(">"))==0 ){
                append_index = i;break;
            }
        }

    //erasing the >> in the command so that we can pass it to the exec system calls
    a.erase(a.begin() + append_index);

        //changing the strings into the respective char pointers
        char *args[append_index+1] , *args1;
        for(int i=0;i<a.size();i++){
                if(i<append_index){
                args[i] = new char[a[i].size()];
                strcpy(args[i], a[i].c_str());
                }
                else {
                    args1 = new char[a[i].size()];
                    strcpy(args1,a[i].c_str());
                }
        }
        args[append_index]=nullptr;

            //creating a child process to execute the given command
            if(fork()==0){
                if(execvp(args[0],args)==0){
                    //creating a file descriptor to the file to where the output should be redirected
                    int file2 = open(args1,O_WRONLY | O_APPEND | O_CREAT,0777);
                    //redirecting the standard output to the specified file
                    dup2(file2,STDOUT_FILENO);
                    //system calls to execute the given command
                    execvp(args[0],args);
                    close(file2);
                    return 1;
                }
                else{
                    return 0;
                }
            }
            wait(nullptr);

        return 1;


    }

    //returning zero if >> not found
    return 0;
}

//checking for the functions related to the environment variables and executing them

int environment(vector<string> a)
{
    //checking whether asking for a already exist variable at that time
    if((a[0].compare("getenv"))==0){

        char* env;
        env = new char[a[1].size()];
        strcpy(env, a[1].c_str());

            if(a.size()==2){
            //checking whether the said variable is there or not
                if(getenv(env)!=nullptr){
                cout<<getenv(env)<<endl;
                }
                else{
                //printing warning message if the variable doesn't exists
                    cout<<"no environment variable exists with that name"<<endl;
                }
            }
            else{
            //giving warning if the command has errors
                cout<<"command is wrong!! recheck it"<<endl;
            }

        return 1;
    }
    //checking whether asking to create a new environment variable or not
    else if((a[0].compare("setenv"))==0){
        if(a.size()==4){
        //checking whether the prototype is correct or not
            if((a[2].compare("="))==0){
                char* env_name,*env_value;
                env_name = new char[a[1].size()];
                env_value = new char[a[3].size()];
                strcpy(env_name, a[1].c_str());
                strcpy(env_value,a[3].c_str());
                setenv(env_name,env_value,1);
            }
            else{
            //giving warning if the prototype is wrong
                cout<<"command is wrong!! recheck it"<<endl;
            }
            return 1;
        }
        else{
        //giving error if the command has errors
            cout<<"command is wrong!! recheck it"<<endl;
        }
        return 1;
    }
    else{
    //returning 0 if above both functions are not matched
        return 0;
    }
}

int main()
{
    //this string stores the input command line
    string commandline;
    //these vectors stores the seperated words of the command line
    vector<string> words,words1;
    //checking for the input taken or not
    int input;
    while(1){
        //calling the function takingcommands to take the input for the shell
        input=takingcommands(commandline);
        //checking if some input entered or not
        if(input==0){
            continue;
        }
        //saving the input into a file
        savinghistory(commandline);
        //seperating the words in the commandline to execute them properly
        seperatingwords(commandline,words);
        //clearing the commandline so that for next input no buffer will be there
        commandline.clear();


        //calling exitcommand function to check for the history and exit commands
        if(exitcommand(words)){
        //if it found and executed properly then clearing the words to make sure that the no buffer is there for the next input
            words.clear();
            continue;
        }

        //calling environment function to execute the commands related to the environment variables
        if(environment(words)){
            //clearing the input
            words.clear();
            continue;
        }

        //calling the redirection function to check for the redirection commands
        if(redirection(words)){
            //clearing the input
            words.clear();
            continue;
        }

        //checking for the append command and executing it by calling the appendcommand
        if(appendcommand(words)){
        //clearing the recent command
            words.clear();
            continue;
        }

        //calling the function piping to check and execute the command related to the pipe
        if(piping(words)){
            //clearing the recent command and comtinuing the process
            words.clear();
            continue;
        }

        //calling the directory function to check for the cd commands and execute them
        if(directory(words)){
            //clearing the input
            words.clear();
            continue;
        }

        //calling the internalcommands function to execute them
        if(internalcommands(words)){
            //if the commamd got executed succesfully then clearing the input
            words.clear();
            continue;
        }


        //which,alias,unalias,logout,shutdown.

        //if the command doesn't matches any of the above cases then printing the appropriate error message
        cout<<"It's not a command"<<endl;
        //clearing the input
        words.clear();
    }
    return 0;
}
