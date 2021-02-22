## Using the Debugger to Analyze Memory

As you have seen in the last section, binary numbers and hex numbers can be used to represent information. A coding scheme such as an ASCII table makes it possible to convert text into binary form. In the following, we will try to look at computer memory and locate information there.

In the following example, we will use the debugger to look for a particular string in computer memory. Depending on your computer operating system and on the compiler you have installed, there might be several debugging tools available to you. In the following video, we will use the gdb debugger to locate the character sequence "UDACITY" in computer memory. The code below creates an array of characters in computer memory (on the stack, which we will learn more about shortly) and prints it to the console:

```c++
#include <stdio.h>

int main()
{
    char str1[]= "UDACITY";
    printf("%s",str1);

    return 0;
}
```

Let us try to locate the string in memory using gdb.

As you have just seen in the video, the binary ASCII codes for the letters in UDACITY could be located in computer memory by using the address of the variable `str1` from the code example above. The output of gdb can also be observed in the following image:



![img](https://video.udacity-data.com/topher/2019/September/5d78129f_8e0935d2-6391-4e89-84fd-7a424a090cff/8e0935d2-6391-4e89-84fd-7a424a090cff.png)



You can clearly see that using hex numbers to display the information is a much shorter and more convenient form for a human programmer than looking at the binary numbers. Note that hex numbers are usually prepended with "0x".

Computer memory is treated as a sequence of cells. This means that we can use the starting address to retrieve the byte of information stored there. The following figure illustrates the principle:



![Computer memory represented as a sequence of cells.](https://video.udacity-data.com/topher/2019/September/5d850ae4_c12-fig2/c12-fig2.png)

Computer memory represented as a sequence of data cells (e.g. 01010101) with their respective memory addresses shown on top.



Let us perform a short experiment using gdb again: By adding 1, 2, 3, … to the address of the string variable `str1`, we can proceed to the next cell until we reach the end of the memory we want to look at.



![img](https://video.udacity-data.com/topher/2019/September/5d781309_340b8883-80b9-4d51-97d3-b67d845d74d4/340b8883-80b9-4d51-97d3-b67d845d74d4.png)



Note that the numbers above represent the string "UDACITY" again. Also note that once we exceed the end of the string, the memory cell has the value 0x00. This means that the experiment has shown that an offset of 1 in a hexadecimal address corresponds to an offset of 8 bits (or 1 byte) in computer memory.