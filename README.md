<h1 align="center">
	🚰 PIPEX
</h1>

<p align="center">
	<b><i>Reproduction of a Unix pipe command (|) in C</i></b><br>
</p>

<p align="center">
    <img alt="score" src="https://img.shields.io/badge/score-0%2F100-brightgreen" />
<p align="center">
    <img alt="solo" src="https://img.shields.io/badge/solo-yellow" />
    <img alt="estimated time" src="https://img.shields.io/badge/estimation-50%20hours-blue" />
    <img alt="XP earned" src="https://img.shields.io/badge/XP-1142-orange" />
<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/lkilpela/pipex?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/lkilpela/pipex?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/lkilpela/pipex?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/lkilpela/pipex?color=green" />
</p>

## 🚰 About The Project

`pipex` is a system programming project developed as part of the Hive Helsinki curriculum. 

Feature:

- Simulates the behavior of the Unix pipe command.
- Executes two commands in a pipeline and redirects the input and output to files.
- Handles errors and provides appropriate error messages.

This project was completed as a **solo project**. It provided an opportunity to learn about process creation, inter-process communication, and file redirection in C.

### 👀 Visualization

Here's a simple diagram to visualize how Pipex works:

> infile --> [ cmd1 ] --> | pipe | --> [ cmd2 ] --> outfile

1. The program reads from infile.
2. The output of cmd1 is piped into cmd2.
3. The output of cmd2 is written to outfile.

#### Process Flow

```
Main Process
|
|--- pipe(fd)
|--- fork()
|
|--- Child Process
|    |
|    |--- dup2(pipefd[1], STDOUT)
|    |--- close(pipefd[0])
|    |--- close(pipefd[1])
|    |--- execve(command path, command, envp)
|
|--- Parent Process
|    |
|    |--- dup2(pipefd[0], STDIN)
|    |--- close(pipefd[1])
|    |--- close(pipefd[0])
|____________________________________________________________
Parent Process (Main Process)            |
|                                        |  
|--- dup2(outfile, STDOUT)               | > for last command
|--- execve(command path, command, envp) |

```
## 🏁 Getting Started

### Prerequisites

- `gcc` or `clang`
- `make`

### 🛠️ Installation & Setup

1. Clone the repository: 
```
git clone https://github.com/lkilpela/pipex.git
```
2. Navigate into the project directory: `cd pipex`
3. Compile the project: `make`

#### Libft as a Git Subtree

`libft` is included in this repository as a git subtree.

- To update the libft subtree with the latest changes from its upstream repository, you can use the following command:
```
git subtree pull --prefix=lib/libft https://github.com/lkilpela/libft.git main --squash
```

### 🚀 How to Use

1. Run the program with the following syntax: `./pipex file1 cmd1 cmd2 file2`
   - `file1` is the filename of the input file
   - `cmd1` is the first command to execute
   - `cmd2` is the second command to execute
   - `file2` is the filename of the output file

For example, you could run: `./pipex infile "grep a1" "wc -w" outfile`

## 📝 Evaluation Requirements

The `pipex` project was evaluated based on the following criteria:

1. **Functionality**: The program must correctly mimic the behavior of the Unix `pipe` command, taking in two commands and two files as arguments, and correctly executing the commands in a pipeline with the appropriate file redirections.

2. **Error Handling**: The program must handle errors gracefully and provide appropriate error messages. This includes handling invalid commands, non-existent files, and incorrect number of arguments.

3. **Code Quality**: The code must be clear, concise, and efficient. It should be well-organized and easy to read. Proper use of functions, variables, and other programming constructs is expected.

4. **Compiling**: The project must compile without any errors or warnings using the provided Makefile.

5. **Memory Management**: The program must manage memory correctly, with no memory leaks.

### 🧑‍💻 Peer Evaluations (3/3)

Here are some of the comments received during the peer evaluation of the `pipex` project:

> **Peer 1**: "..."

> **Peer 2**: "..."

> **Peer 3**: "..."

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/lkilpela/so_long/blob/main/docs/LICENSE) file for details.

