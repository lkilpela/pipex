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

7. No PATH envp	, cm1 path		
./pipex infile "/bin/ls" "wc" outfile
< infile "/bin/ls" | "wc" > outfile

8. No PATH envp, cmd1 path, cmd1 path	
./pipex infile "/bin/ls" "/bin/cat" outfile
< infile "/bin/ls" | "/bin/cat" > outfile


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
6. PATH envp does not exist		
./pipex infile " ls"  "wc" outfile
< infile  ls | wc outfile


< infile "grep Now" | "wc -w" > outfile
Permission denied (check in setup_command) 

Infile no read permission
Outfile no write permission
No exec permission cmd1
No exec permission cmd2

Bad arguments, invalid options

Bad args cmd1, valid cmd2		./pipex infile "ls -?" "grep c" outfile
Bad args cmd1, bad args cmd2	./pipex infile "ls -?" "wc -9001" outfile


The next tests will use the following command:
./pipex "infile" "cat" "hostname" "test-xx.txt"
< infile cat | hostname > outfile.txt
OK.

./pipex "infile" "grep Now" "head -2" "test-xx.txt"
< infile grep Now | head -2 > outfile.txt

./pipex "infile" "grep Now" "wc -w" "test-xx.txt"
< infile grep Now | wc -w > outfile.txt


./pipex "infile" "grep Now" "cat" "test-xx.txt"
< infile grep Now | cat > outfile.txt
then:
./pipex "infile" "wc -w" "cat" "test-xx.txt"
< infile wc -w | cat > outfile.txt

./pipex "infile" "notexisting" "wc" "test-xx.txt"
(notexisting is a command that is not supposed to exist)
< infile notexisting | wc > outfile.txt


./pipex "infile" "cat" "notexisting" "test-xx.txt"
< infile cat | notexisting > outfile.txt

./pipex "infile" "grep Now" "/bin/cat" "test-xx.txt"
< infile grep Now | /bin/cat > outfile.txt

./pipex "infile" "grep 'Deep Thought'" "/bin/cat" "test-xx.txt"
< infile grep "Deep Thought" | /bin/cat > outfile.txt


./pipex "/dev/urandom" "cat" "head -1" "test-xx.txt"
< /dev/urandom cat | head -1 > outfile.txt
31: The program does not timeout        

./pipex pipex.h "sleep 10000" "ls" "test-xx.txt"
< pipex.h sleep 10000 | ls > outfile.txt    
  
./pipex pipex.h "ls" "sleep 10000" "test-xx.txt"
< pipex.h ls | sleep 10000 > outfile.txt  

./pipex pipex.h "   " "" "test-xx.txt"
< pipex.h "   " | "" > outfile.txt 

./pipex pipex.h "   ls -w " "cat" "test-xx.txt"
< pipex.h      ls -w | cat > outfile.txt 

./pipex pipex.h "   " "       " "test-xx.txt"
< pipex.h "   " | "       " > outfile.txt 

Unset PATH.

./pipex pipex.h libft libft "test-xx.txt"
< pipex.h libft | libft > outfile.txt 

./pipex pipex.h ./libft libft "test-xx.txt"
< pipex.h ./libft | libft > outfile.txt

./pipex pipex.h "/hello/kim/echo ha" cat "test-xx.txt"
< pipex.h /hello/kim/echo ha | cat > outfile.txt 

CHECK PERMISSION
./pipex pipex.c ./a.out cat "test-xx.txt"
< pipex.c ./a.out cat > outfile.txt 

./pipex a.out cat cat "test-xx.txt"
< a.out cat | cat > outfile.txt 
