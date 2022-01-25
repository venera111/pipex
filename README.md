# pipex

```
./pipex file1 cmd1 cmd2 file2
< file1 cmd1 | cmd2 > file2
```
Examples
```
./pipex infile "ls -l" "wc -l" outfile
./pipex infile "grep a1" "wc -w" outfile
< infile grep a1 | wc -w > outfile
```

### Resources
Unix Processes in C: [CodeVault](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)
