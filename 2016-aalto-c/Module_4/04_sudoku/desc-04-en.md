title: Bit Sudoku
task_id: 04_sudoku
points: 2


**Objective:** Practice binary operations, in a two-dimensional array.

This exercise comes with an 8x8 table that consists of values 0 and 1
(of *char* type). Each row and each column in the table represents an
8-bit value that you will need to calculate. The table index 0
represents the least significant bit, and table index 7 is the most
significant bit.

The task template comes with three given functions: '**allocTable**'
dynamically allocates the 8x8 table and returns a pointer to
it. '**releaseTable**' frees the memory allocated for the
table. '**printTable**' prints the table content to the screen,
including the 8-bit values on each row and column that the table
represents. In the printout the least significant bits are on the
right and bottom of the table, and the 8-bit values are shown as
hexadecimal. You can use the printTable function to test your code,
and '*main.c*' has a small program towards that (see the code for
details).

Despite the task name, there is no game logic involved with the
current exercise template. Feel free to enhance *main.c*, for example,
to check that each row and column have equal number of bits set.

a) Calculate row and column
------------------------------

Implement the functions '**calculateRow**' and '**calculateColumn**' that
calculate the 8-bit number the given row or column represents, and
return the number. The function *printTable()* uses these functions in
its implementation, so it will not work before these functions are
properly implemented. The row number is indicated as the first-order index
of the table and the column is indicated as the second index. The
numbering of rows and columns goes from 0 to 7.

You will need to implement both *calculateRow()* and
*calculateColumn()* to gain a point from this task.

b) Set column or row
-----------------------

Implement the functions '**setRow**' and '**setColumn**' that set the bits
on a given row or column based on the 8-bit number given as a
parameter. Rows are the first-order index of the two-dimensional
array, and columns are the second-order index.

You will need to implement both *setRow()* and *setColumn()* functions
to gain a point from this task.

Below is a sample printout made by *printTable()* after *calculateRow()*
and *calculateColumn()* have been implemented.

<pre>
  0  0  0  1  0  0  0  1 11
  0  0  0  0  0  0  0  0 00
  0  0  0  0  0  0  0  0 00
  0  0  0  0  0  0  0  0 00
  1  1  1  1  0  0  0  0 f0
  0  0  0  0  1  1  1  1 0f
  0  1  0  1  0  1  0  1 55
  0  0  0  0  0  0  0  0 00
 08 0a 08 8a 04 06 04 86</pre>
