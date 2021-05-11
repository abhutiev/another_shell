# another_shell

My shell implementation. I learned UNIX in this project.

Most proud of: parallel opening of pipes, which protects against losses when transmitting through them volumes of information greater than the bandwidth of the channel created by the pipe function.

Implemented with all the features (except multiline) of double and single quotes, escaping, substitution of environment variables, right and left redirects, pipes.

Exit status of commands same as in bash.

Functions implemented as builtins:

◦ echo with option ’-n’

◦ cd with only a relative or absolute path

◦ pwd without any options

◦ export without any options

◦ unset without any options

◦ env without any options and any arguments

◦ exit without any options

Signals ctrl-C, ctrl-D works like in bash. Signal ctrl-\ make shell "forget" already wrotten.

Used functions: malloc, free, write, open, read, close, fork, wait, waitpid, signal, exit, getcwd, chdir, execve, dup, dup2, pipe, opendir, strerror.
Instead of the other functions, my own implementations were used.
