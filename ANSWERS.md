**1. List all of the main states a process may be in at any point in time on a standard Unix system. Briefly explain what each of these states means.**

- New (Create): In this step, process is about to be created but not yet created, it is the program which is present in secondary memory that will be picked up by OS to create the process.
- Ready – New -> Ready to run. After creation of a process, the process enters the ready state i.e. the process is loaded into the main memory. The process here is ready to run and is waiting to get the CPU time for its execution. Processes that are ready for execution by the CPU are maintained in a queue for ready processes.
- Run – The process is chosen by CPU for execution and the instructions within the process are executed by any one of the available CPU cores.
- Blocked or wait – Whenever the process requests access to I/O or needs an input from user or needs access to a critical region(the lock for which is already acquired) it enters the blocked or wait state. The process continues to wait in the main memory and does not require CPU. Once the I/O operation is completed the process goes to ready state.
- Terminated or completed – Process is killed as well as PCB is deleted.
- Suspend ready – Process that were initially in ready state but were swapped out of main memory(refer Virtual Memory topic) and placed onto external storage by scheduler are said to be in suspend ready state. The process will transition back to ready state whenever the process is again brought onto the main memory.
- Suspend wait or suspend blocked – Similar to suspend ready but uses the process which was performing I/O operation and lack of main memory caused them to move to secondary memory. When work is finished it may go to suspend ready.

**2. What is a zombie process?**

A process which has finished the execution but still has entry in the process table to report to its parent process.

**3. How does a zombie process get created? How does one get destroyed?**

- When a child process gets created using `fork()`, it immediately becomes a zombie before being removed from the process table.
- The process can be destroyed by calling the `exit(0)` or `exit(1)`. Syncronously, the parent can use the `wait(NULL)` to wait for the zombie to be destroyed before continuing to execute the parent code.

**4. What are some of the benefits of working in a compiled language versus a non-compiled language? More specifically, what benefits are there to be had from taking the extra time to compile our code?**

- Compiled Language - creates a file with expressed instructions for the specific machine. The following benifits are:
  - Faster performance by directly using the native code of the target machine
  - Opportunity to apply quite powerful optimisations during the compile stage
- Non-Compiled Language (also known as Interpreted Language) - Uses a 3rd party interpreter program to compile the language using its own pre-defined functions that are called based upon the recognization the native machine. The following benifits are:
  - Easier to implement (writing good compilers is very hard!!)
  - No need to run a compilation stage: can execute code directly "on the fly"
  - Can be more convenient for dynamic languages

Sources:

- https://en.wikipedia.org/wiki/Process_state
- https://www.geeksforgeeks.org/operating-systems-states-process/
- https://www.tutorialspoint.com/operating_system/os_processes.htm
- https://en.wikipedia.org/wiki/Zombie_process
- https://www.howtogeek.com/119815/htg-explains-what-is-a-zombie-process-on-linux/
- https://www.geeksforgeeks.org/zombie-and-orphan-processes-in-c/
- https://stackoverflow.com/questions/3265357/compiled-vs-interpreted-languages
