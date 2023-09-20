#include "systemcalls.h"

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

/*
 * TODO  add your code here
 *  Call the system() function with the command set in the cmd
 *   and return a boolean true if the system() call completed with success
 *   or false() if it returned a failure
*/
	int returnCode = system(cmd);

	// checking if the command was executed successfully
    if (returnCode == 0) {
        return true;
    }
    else
        return false;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    //printf("Code begins here with count = %d\n", count);
    
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
        //printf("%s \n", command[i]);
    }
    command[count] = NULL;


    pid_t pid;
	int status;
    //int ret;

	pid = fork();
	//printf("pid returned: %d\n", pid);

	if (pid == -1) {
        perror("fork()");
		return false;
	}
	else if (pid == 0) {
        printf("-----> Executing CHILD execv(%s,%s,%s,%s)\n",
                command[0],
                command[1],
                command[2],
                command[3]);
		//execv(command[0], &command[1]);
		execv(command[0], command);
        //printf("----->  ERR returned %d\n",ret);
        perror("execv()");
        return false;
    } else {
    
        printf("-----> Executing PARENT\n");
        
        if (waitpid(pid, &status, WCONTINUED) == -1) {
            perror("waitpid()");
            return false;
        }
        else if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status); 
            
            printf("WIFEXITED=%d\n",WIFEXITED(status));
            printf("Exit status of the child was %d\n", exit_status);
            printf("Test should %s\n",exit_status==0?"PASS":"FAIL");
            
            printf("WEXITSTATUS=%d\n",WEXITSTATUS(status));
            printf("WIFCONTINUED=%d\n",WIFCONTINUED(status));
            printf("WIFSIGNALED=%d\n",WIFSIGNALED(status));
            printf("WIFSTOPPED=%d\n",WIFSTOPPED(status));
            printf("WSTOPSIG=%d\n",WSTOPSIG(status));
            printf("WTERMSIG=%d\n",WTERMSIG(status));
            if ( exit_status == 0)
                return true;
            else
                return false;
        }
        
        return false;
    }

}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    pid_t pid;
	int status;
    //int ret;

	pid = fork();
	//printf("pid returned: %d\n", pid);

	if (pid == -1) {
        perror("fork()");
		return false;
	}
	else if (pid == 0) {
        int fd = open(outputfile, O_WRONLY|O_TRUNC|O_CREAT, 0644);
    
        if (fd < 0) { 
            perror("open"); 
            return false;
        }
        
        if (dup2(fd, 1) < 0) { 
            perror("dup2");
            abort();
        }
        
        close(fd);
        execv(command[0], command);
        perror("execv()");
        return false;

    } else {
        
        if (waitpid(pid, &status, WCONTINUED) == -1) {
            perror("waitpid()");
            return false;
        }
        if ( WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if(exit_status!= 0)
                return false;
                
            return true;
        }
    
        return false;
    }


/*
 * TODO
 *   Call execv, but first using https://stackoverflow.com/a/13784315/1446624 as a refernce,
 *   redirect standard out to a file specified by outputfile.
 *   The rest of the behaviour is same as do_exec()
 *
*/

    va_end(args);

    return true;
}
