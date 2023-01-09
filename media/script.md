
This is a short demonstration of the calculator I have built for my ELEC 3662 mini-project

Here is the calculator. I've mounted the keypad and LCD into pockets that I've milled in a piece of aluminium plate.

On the back I have temporarily fixed the TI launchpad board with adhesive.

this ribbon cable connects the row and column pins of the keypad to port B of the microcontroller.

These four wires carry the LCD Data bits from port C, and these wires carry the other LCD control lines from port A.

The rest of the wires supply power. 

A potentiometer has been added to the top of the LCD to adjust contrast.



Powering on the calculator first displays the logo animation, before presenting the user with a cursor and a blank line to start entering calculations.

The calculator keypad has several modes. By default its in numeric entry mode, with the actions of the keys defined by their primary legends.

In this mode numbers can be entered into the calculation.

    789

There is a decimal point for entering fractional numbers

    789.456

and an exponent button for entering very large or very small numbers in scientific notation.

    789.456E123

There is also a plus / minus key, which can be used to enter negative numbers. If the cursor is already on or past a number or its exponent the button will toggle a minus sign at the beginning of that section of the number.

If I move the cursor over to the main body of the number and use the plus minus key again it now negates the number its self rather than the exponent.

As you can see its possible to move the cursor around

This, and entering mathematical operators is done using operator mode on the keypad.

Operator mode is accessed by holding down the OP key at the top right of the keypad.

In this mode the keys will perform the actions indicated by the legends above the keys, the left and right arrow keys moving the cursor.




In operator mode I can add, subtract, multiply, divide, take powers and calculate square roots.

As you can see my calculator will automatically scroll the display once the input expression becomes too wide

pressing the backspace key removes characters from the expression.

    789.456E123 / 10^123

pressing the enter key computes the expression and displays the result.

Numbers with magnitudes greater than 1 and less than 1 times ten to the 6 are displayed in normal form and numbers outside this range are automatically displayed with scientific notation.

pressing and holding the backspace button clears the input and the calculator is ready for a new expression.




The result of the previous calculation can be used again with the answer variable, like so

    ANS-789

In fact, by adding an operator directly after an expression has been computed the answer variable will be inserted implicitly.

    ANS / 20



Holding down the plus minus key and pressing other keys inserts special functions.

I can add trigonometric functions, inverse trigonometric functions, logarithms and the constants pi and e

There's not enough space for these legends around the keys but their placement is explained in the documentation

The plus minus key can also toggle negation of these functions.




My calculator has a 64 entry history of the expression that have been entered

Using the up arrow steps back through the history, and using the down arrow steps forward.

I can go back through the history to demonstrate some example expressions.




This example demonstrates that my calculator maintains correct operator precedence




This example demonstrates correct nesting of brackets




This example demonstrates iteration using the answer variable




and this example demonstrates a trigonometric expression




