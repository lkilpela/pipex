Command not found

Invalid cmd1				./pipex infile “xxx” “wc” outfile 	
Invalid cmd2				./pipex infile “wc” “xxx” outfile 
Invalid cmd1, invalid cmd2 (PATH)	./pipex infile “xxx” “/xxx/xxx” outfile  -> invalid cmd1 is command not found
Null string cmd1			./pipex infile “ ” “wc” outfile 
Empty cmd2				./pipex infile “wc” “        ” outfile 
Null string cmd1, empty cmd2	./pipex infile “ ” “       ” outfile 

No such file or directory

Infile does not exist			./pipex noinfile “ls” “wc” outfile
Infile does not exist, invalid cmd1	./pipex noinfile “xxx” “wc” outfile
Cmd1 is folder, valid cmd2		./pipex infile “./libft/” “ls” outfile
Valid cmd1, cmd2 is folder		./pipex infile “ls” “./libft/” outfile
Invalid cmd1 or cmd2 path		./pipex infile “/xxx/xxx” “wc” outfile
PATH envp does not exist		./pipex infile “ ls” “wc” outfile
No PATH envp	, cm1 path		./pipex infile “/bin/ls” “wc” outfile
No PATH envp, cmd1 path, cmd1 path	./pipex infile “/bin/ls” “/bin/cat” outfile

Permission denied (check in setup_command)

Infile no read permission
Outfile no write permission
No exec permission cmd1
No exec permission cmd2

Bad arguments, invalid options

Bad args cmd1, valid cmd2		./pipex infile “ls -?” “grep c” outfile
Bad args cmd1, bad args cmd2	./pipex infile “ls -?” “wc -9001” outfile
