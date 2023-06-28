# 42cursus-minishell ([Subject](/.github/en.subject.pdf))

## Description

The objective of this project is for you to create a simple shell.

## Features

- Working history.
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- Implemented redirections:
  - \< redirect input.
  - \> redirect output.
  - \<< should be given a delimiter, then reads the input until a line containing the delimiter is seen. However, it doesn't update the history!
  - \>> redirect output in append mode.
- Implemented pipes (| character).
- Handles environment variables.
- Handles $? which expands to the exit status of the most recently executed foreground pipeline.
- Handles ctrl-C, ctrl-D and ctrl-\.
- In interactive mode:
  - ctrl-C displays a new prompt on a new line.
  - ctrl-D exits the shell.
  - ctrl-\ does nothing.
- echo with option -n
- cd with only a relative or absolute path
- pwd with no options
- export with no options
- unset with no options
- env with no options or arguments
- exit with no options
