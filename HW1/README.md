Title: Homework 1 in CS531 on Spring 2022 at GMU

 Introduction/Description:
The user interface will ask you to enter ten different character strings using the keyboard. A strlen() value between 2 and 25 inclusive is required for each character string; otherwise, an error notice is shown and the user is questioned again. The program sorts this collection of 10 character strings (based on strcmp()) and then prints all ten strings again in the user-specified ascending OR descending order. The character strings with the lowest and highest ascii values, as determined by strcmp(), are then printed and labeled. The following characters CANNOT be used in character strings: '!', '@', '#', '$', '%', '', '(', or ')'.
checking for errors such as empty strings, duplicate strings, For the sort specification, use a character other than 'A' or 'D'.
Outside of main(), it includes the following user-defined routines.
• void inputStings() //Ask for 10 character strings from the user. 
• void checkStringLen() // Verify that the string length is within [2..25].
• int checkLegalCharacters() // Verify that there are no illegal characters such as "!," "@," "#," "$," "%," "," "(," or ")."
• void checkDuplicate() //Check that no strings are duplicated.
• rising voidSort and display the output using the char sortOrder function.

The program can be compiled using gcc, and it easily reads using vi.



