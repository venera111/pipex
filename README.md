# pipex

### Mandatory part
Your objective is to code the Pipex program.
It should be executed in this way:
```
./pipex file1 cmd1 cmd2 file2
```
The execution of the pipex program should do the same as the next shell command:
```
< file1 cmd1 | cmd2 > file2
```
Just in case: file1 and file2 are file names, cmd1 and cmd2 are shell commands with
their parameters.

Examples
```
./pipex infile "ls -l" "wc -l" outfile
./pipex infile "grep a1" "wc -w" outfile
< infile grep a1 | wc -w > outfile
```

### Resources
Unix Processes in C: [CodeVault](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)
