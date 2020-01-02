# saol (simple array-oriented language)
## "Hello world!" programm
  ```
  @|(Hello world!)(-!)
  ```

## picking  
  + `saol` -- standard interpreter
  + `isi` -- interactive interpreter
  + `ssp` -- simple standard preprocessor

## Overview
  + `(` / `)` -- take everything in parentheses as a whole works like quotation marks in other languages (`(word1 word2)` - will be read as "word1 word2")
  + `:` -- initialize the current selected element with a value (`:12` - now element 0 stores the value 12). If `il` is specified as an argument, the element will be initialized with the length of the interval (see the description of the `[` & `]` commands).
  + `^` -- go to the item with the number (`^123` - now 123 is the current work item)
  + `>` / `<` -- move right / left in the array (`>>` - move the current work item pointer 2 items forward)
  + `_!` -- display the value of the current item (`:123(_!)` - displays the value of element 123 on the screen)
  + `~ (text)` --  a comment whose text is placed in brackets (`~ (comment)`)
  + `|` -- fills the array from the current position with elements (`|6 8 2` - the numbers 6, 8, 2 will be added to the array)
  + `-!` -- displays the values of all array elements (`^0|6 8 12(-!)` - displays 6, 8, 12 if the array was initially empty)
  + `;` -- reports that the data entered is a number (`;:12` - writes 12 to the currently selected element, and reports that it is a number)
  + `@` -- indicates that the input data is characters (`@:A` - writes the letter 'A' to the currently selected element)
  + `+` -- returns the sum of all array elements in element 2047 (`;|12 56 9+^2047(_!)` - displays the sum of 12, 56, and 9)
  + `'` -- returns the difference of all array elements in element 2047 (`;|12 56 9'^2047(_!)` - will represent the difference between 12, 56, and 9)
  + `*` -- returns the product of all array elements in element 2047 (`;|12 56 9*^2047(_!)` - displays the product 12, 56, and 9)
  + `/` -- returns the quotient of all array elements in element 2047 (`;|12 56 9/^2047(_!)` - displays private 12, 56, and 9)
  + `#` -- filling an array with specific values (`;#0` - fills the array with zeros)
  + `[` / `]` -- limit the scope of commands (`[0]2(-!)` - displays the values of elements from 0 to 2)
  + `:-` -- copy the value of the current item to the selected one (`:123(:-)2` - now element 2 stores the value 123)
  + `!-` -- copies the inverted value from the current work item to the selected one (`:123(!-)2` - now element 2 stores 0)
  + `&` -- returns the conjunction of all array elements in element 2047 (`|1 2 3&` - in element 2047, 1 will be returned)
  + `\` -- returns the disjunction of all array elements in element 2047 (`|1 2 0\` - in element 2047, 1 will be returned)
  + `?~` -- predicative execution tool, if the result of the previous operation is true, then all subsequent commands will be executed, if it is not, then all subsequent operations will be skipped, analogous to `if` in other languages (`|1 2 3+(?~)^0|(true)@(-!)` - will display "true", because 1+2+3 not equal to 0)
  + `?!` -- inverts the result of the previous operation, similar to `else` in other languages (`|0 0 0+(?~)^0|(true)@(-!)(?!)|(false)@(-!)` - will output "false" as 0+0+0 early 0)
  + `|~` -- iterator, performs some action on all elements of the array (`(|~)(_! )` - displays the values of all elements of the array, in fact analog ( -!), it is important that operations that must be performed iteratively are enclosed in brackets and end with a space)
  + `<->` -- exchanges values between the current work item and the selected one (`^2047(<->)2` - the values of elements 2047 and 2 will be reversed)

## Some remarks  
  + some commands must be surrounded by parentheses, as follows: `(_!)`, `(-!)`, `(:-)`, `(!-)`, `(?~)`, `(?!)`, `(|~)`, `(<->)`
  + specifically for saol, I wrote a preprocessor called ssp (standard SAOL preprocessor), it runs separately from the main interpreter, and has the following features:
    + `.link <file_1> <file_2> ... <file_n>` -- connecting third-party files
	+ `.macro <name> <expr>` -- creates a macro named name, the next time it is encountered, expr will be substituted for it
	+ `.prog` -- end of the preprocessor command block and start of the program (in version 1.3 and higher it is not necessary)

### Template for using a preprocessor in a program
  ```
  .link...
  .macro...
  .prog

  ~ your programm
  ```

### Important notes
  + Macro names in the program must be surrounded by spaces
    ```
	.macro foo bar
	.prog
	^ foo : bar
	```
  + If the macro value contains spaces, use `{} `to combine expressions. Thanks to this, you can write a macro that will generate another macro.
    ```
    .macro gen {.macro foo bar}
    .prog
    gen
    ```

## Installation and use
### Installation
to install, you will need:
  + C compiler (gcc, clang)
  + git
  + make

###### typical installation scenario
  ```
  git clone https://github.com/Centrix14/saol
  cd saol
  make saol
  make isi
  make ssp
  ```

### use
  ```
  ./saol my_programm.spf // for simple interpretation
  ./ssp my_programm.spf out.saol // for preprocessing my_programm.saol in out.saol
  ./isi // to call an interactive interpreter
  ```
