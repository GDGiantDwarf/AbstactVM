# B-SYN-400-MPL-4-1-abstractVM-noe.sellam
This is the AbstractVM epitech project.<br/>
There were essentially two requierements.<br/>
First, creating a stack of numbers, that can be of different sizes (int8, int 16, int 32, float, double and BigDecimal (which was to be simulated using strings))<br/>
Second, taking commands from stdin, that have effects on the stack.<br/>
those commands are:<br/>
  push V (to add V to the stack)<br/>
  pop (to remove the top element of the stack)<br/>
  store V (to take an element from the stack and add it to register V)<br/>
  load V (to take element V from the register and put it on the stack)<br/>
  mul / div / add / sub / mod (respectively, multiplies, divides, adds, substracts or computes the modulo of the top two element, removes them from the stack, and puts the new value on the stack (using the precision of the largest of the two operands))<br/>
      (for non-commutative operations, the operand on top was used as secondary operand, such that with the stack "2, 4", using sub would compute 4-2 = 2)<br/>
  dump (dumps the stack on stdout)<br/>
  assert V (verifies that V equals the top element of the stack, the program must throw otherwise) (usefull to avoid division by zero, since second operand is on top of the stack)<br/>
  print (first, asserts that the element on top is of int8 precision (and throws otherwise). then, prints to stdout the appropriate character accordint to the ascii table (the value 48 would print out '0', for instace))<br/>
  exit (quits the program, the program must throw is no exit instruction is given before EOF)<br/>
