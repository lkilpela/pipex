# Command not found

1. Invalid cmd1				
./pipex infile "xxx" "wc" outfile
< infile "xxx" | "wc" > outfile
2. Invalid cmd2			
./pipex infile "wc" "xxx" outfile 
< infile wc | xxx > outfile
3. Invalid cmd1, invalid cmd2 (PATH)	
./pipex infile "xxx" "/xxx/xxx" outfile  -> invalid cmd1 is command not found
< infile xxx | /xxx/xxx > outfile
pipex: command not found: xxx
pipex: command not found: /xxx/xxx
4. Null string cmd1
./pipex infile " " "wc" outfile 
< infile    | wc > outfile
5. Empty cmd2				
./pipex infile "wc" "        " outfile
< infile wc |          > outfile
6. Null string cmd1, empty cmd2
./pipex infile " " "       " outfile
< infile   |         > outfile

# FULL PATH
1. No PATH envp	, cm1 path		
./pipex infile "/bin/ls" "wc" outfile
< infile /bin/ls | wc > outfile
2. No PATH envp, cmd1 path, cmd1 path	
./pipex infile "/bin/ls" "/bin/cat" outfile
< infile /bin/ls | /bin/cat > outfile

# unset PATH
echo $PATH
OLD_PATH=$PATH
unset PATH
export PATH=$OLD_PATH

1. PATH envp does not exist		
./pipex infile " ls"  "wc" outfile
< infile  ls | wc outfile

# No such file or directory

1. Infile does not exist			
./pipex noinfile "ls" "wc" outfile
< noinfile ls | wc > outfile
2. Infile does not exist, invalid cmd1
./pipex noinfile "xxx" "wc" outfile
< noinfile "xxx" | "wc" > outfile
3. Cmd1 is folder, valid cmd2		
./pipex infile "./libft/" "ls" outfile
< infile ./libft/ | ls > outfile
4. Valid cmd1, cmd2 is folder		
./pipex infile "ls" "./libft/"  outfile
< infile ls | ./libft/ > outfile
5. Invalid cmd1 or cmd2 path		
./pipex infile "/xxx/xxx" "wc" outfile
< infile /xxx/xxx | wc > outfile

# Permission

< infile grep Now | wc > outfile
Permission denied (check in setup_command) 

Infile no read permission
Outfile no write permissionclear
No exec permission cmd1
No exec permission cmd2

# Bad arguments, invalid options

1. Bad args cmd1, valid cmd2		
./pipex infile "ls -?" "grep c" outfile
< infile ls -? | grep c > outfile
2. Bad args cmd1, bad args cmd2	
./pipex infile "ls -?" "wc -9001" outfile
< infile ls -? | wc -9001 > outfile


