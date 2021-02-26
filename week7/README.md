<h2> Substitute Function </h2>

2/26/2021

<h3>Week 7: 
The "sub" program will take input from the user via stdin, and for every pair of
command line arguments, it will replace every instance of the first character
in the input with the second, writing the result to stdout.</h3>

<h3>Requirements:</h3>
<p>The program must use the "fork" command to create a child process, and the labor
must be divided between the parent and child. Also, using  "pipe" command to pass characters between the parent and child processes.</p>

<p>For example, "./sub e z l t"
If the user passes the string "hello world" to stdin, then the result, "hztto wortd", is written to stdout</p>
