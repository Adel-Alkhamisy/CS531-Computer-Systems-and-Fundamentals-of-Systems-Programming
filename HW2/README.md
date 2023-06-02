Title: Homework 2 in CS531 on Spring 2022 at GMU

Introduction/Description:
The majority of machines connected to the internet have 32 bit IPv4 addresses. IPv4 addresses are typically expressed in dotted decimal notation since reading these addresses would be challenging using binary or hexadecimal notation. For representational purposes, the address's 32 bits can be broken down into four octets (bytes), each of which can be expressed as a decimal integer ranging from 0 to 255. These four octets can then be concatenated to form a character string with a full stop (ASCII 46) in between them. The location of the computer on the network is indicated by the address's first two elements.

Computers are frequently referred to by an alias or nickname. The "CS531_Inet.txt" file contains a list of Internet addresses that this software processes. "CS531_Inet.txt" will have addresses and aliases on each line.

The address_t structure type that this program constructs has components for each of the four numbers that make up an IPv4 address as well as a fifth component for storing a related alias (key field) that can include up to 10 characters. Address/alias pairs from the "CS531_Inet.txt" file are read into a singly linked list of address_t structures, which will include all of the addresses. The linked list may be unsorted for this exercise.
The user will see the following menu options after creating the linked list:

1) Add address
2) Lookup address
3) Update address
4) Delete address
5) Display list
6) Display aliases for location 
7) Save to file
8) Quit

 usage: 
- Click on HW2.c - Click on Download raw file 
- Move the file from the Download folder to a specific folder of your choice i.e. /Users/username/Desktop/HW2.c; replace username with your username on your computer. 
- Open the terminal and navigate to the folder that contains the HW2.c file. This will depend on your operating system. On Windows, you can use Command Prompt or PowerShell. On macOS and Linux, you can use Terminal. i.e. cd /path/to/your/directory that contains HW2.c 
- Compile the C File: Use the gcc command followed by the name of your C file, then -o, and finally the name you want for your output file. The -o option allows you to specify the output file name. i.e. gcc HW2.c -o anyNameOfYourChoice 
- then use ./anyNameOfYourChoice 
- Then the program will be running and you can test it as you like.
