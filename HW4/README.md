The int system(const char *comm) function from the C library is used to run commands and subprocesses. It is specified in the header file stdlib.h.
Parameters:
comm -- The requested command is contained in this string of characters.
Value Returned:
If there is an error, -1 is returned; otherwise, the command's return status is displayed.
Assignment:
Implement a user-defined system function you created:
(const char *comm) int cs531_system
Incorporate the following macros and functions into your program:
signal()/sigaction(), fork(), execlp(), dup(), wait(), WEXITSTATUS(), WTERMSIG(), WSTOPSIG(), and WIFCONTINUED()
Use system() sparingly.
cs531_system():
While the child process is active, the parent process must disregard SIGINT and SIGQUIT. When SIGKILL occurs, the child process must react. 
