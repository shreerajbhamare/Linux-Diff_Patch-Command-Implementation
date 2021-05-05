# Linux-Diff_Patch-Command-Implementation
<img src="https://github.com/shreerajbhamare/Linux-Diff_Patch-Command-Implementation/blob/main/icon3.png" align="right" />

***Diff*** stands for difference. This command is used to display the differences in the files by comparing the files line by line.The important thing to remember is that diff uses certain special symbols and instructions that are required to make two files identical. It tells you the instructions on how to change the first file to make it match the second file.The **diff command** can display the output in several formats with the normal, context, and unified format being the most common ones. The output includes information about which lines in the files must be changed so that they become identical. If the files match, no output is produced.<br />

**Note :** All Output screenshot of project are provided In **Op** folder uploaded.

---

![Project Image](https://github.com/shreerajbhamare/Linux-Diff_Patch-Command-Implementation/blob/main/diff_working.png)

> ***Diff and Patch*** Linux Command Implementation in C language.

---

### Table of Contents:

- [Description](#description)
- [Specification](#specification)
- [Installation](#installation)
- [Algorithm](#algorithm)
- [References](#references)


---

## Description


***Syntax:***

     diff [options] File1 File2 
     
***Special symbols are :***

* a : add
* c : change
* d : delete


## Specification
***Modes Implemented :***

- Context Mode (-c)
- Unified Mode (-u)
- Non Case sensitive Mode (-i)
- All types of White Space ignorance Mode (-w)
- Ignore Changes in the amount of white space Mode (-b)
- Reporting that files are different Mode (-q)
- Reporting that files are Identical Mode (-s)
- Normal diff Mode (No need of attribute)

***Data Structure Used :***
- Singly Linked List
- Queue
- Stack
- File Handling

***Algorithm :***
- Longest Commom Subsequence
- Memoization

---

## Installation
1. Clone this repository, extract it if you downloaded a .zip or .tar file and cd into the cloned repository.

    * For Example:
    ```bash
    cd A:\Diff_Patch
    ```
2. Type the below command to run the Project.This is my Second Semester **Data structure and Algorithm Project**.Motive of this project is to mimic in-built Linux command using **C programming** language.
   ```bash
   make
   ```
3. Project get built and ***diff.out*** and ***patch.out*** gets generated.To run project for normal diff command on targeted **file1.txt** and **file2.txt** type below command. 

    ```bash
    ./diff file1.txt file2.txt
    ```
 
4. To run same project for **-c, -u, -i, -b, -w, -q** and **-s** attribute on targeted files as **file1.txt** and **file2.txt** type below command accordingly. 

    ```bash
    ./diff -c file1.txt file2.txt
    ./diff -u file1.txt file2.txt
    ./diff -i file1.txt file2.txt
    ./diff -b file1.txt file2.txt
    ./diff -w file1.txt file2.txt
    ./diff -q file1.txt file2.txt
    ./diff -s file1.txt file2.txt
    ```
5.  Type the below commands to run the patching command implementation project on **file1.txt**. After this command, **file1.txt** get exactly converted into **file2.txt**
    ```bash
    ./diff -u file1.txt file2.txt > file.patch
    ./patch file1.txt file.patch
    ./diff -s file1.txt file2.txt
    ```
## Algorithm

***Longest Common Subsequence Algorithm :***


If a set of sequences are given, the longest common subsequence problem is to find a common subsequence of all the sequences that is of maximal length.
The longest common subsequence problem is a classic computer science problem, the basis of data comparison programs such as the diff-utility, and has applications in bioinformatics. It is also widely used by revision control systems, such as SVN and Git, for reconciling multiple changes made to a revision-controlled collection of files.

***Pseudo Code :***

![Project Image](https://github.com/shreerajbhamare/Linux-Diff_Patch-Command-Implementation/blob/main/algo.PNG)

---
## References
- [Diff command man page](https://man7.org/linux/man-pages/man1/diff.1.html)
- [Patch command man page](https://man7.org/linux/man-pages/man1/patch.1p.html)
- [Linux Journal](https://www.linuxjournal.com/article/3991)
- [Diff working](https://www.geeksforgeeks.org/diff-command-linux-examples/)
- [Patch working](https://acloudguru.com/blog/engineering/introduction-using-diff-and-patch#:~:text=The%20commands%20diff%20and%20patch,that%20contains%20only%20the%20differences.)
- [LCS Ovrview](https://www.youtube.com/watch?v=ASoaQq66foQ)
- [Most useful resource(Reasearch paper)](https://www.cs.dartmouth.edu/~doug/diff.pdf)
- [Workflow(Algorithm utility) ](https://epxx.co/artigos/diff_en.html)



---


## Contributor

***Shreeraj Bhamare*** <br />
**MIS - 111903098**<br />
DSA Project , Forth Semester<br />
Second Year, Computer Engineering<br />
College of Engineering, Pune  <br />

