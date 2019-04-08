===========================================================

Simulating Multilevel-FeedBack-Scheduling-Queue-in-C
===========================================================


This application implements Multilevel Feedback Queue in C with two levels:

Level 1 : Fixed priority preemptive Scheduling

Level 2 : Round Robin Scheduling



===========================================================

                    SYSTEM DETAILS

===========================================================


1. Fixed priority preemptive Scheduling (Queue 1)
 * Priority 0 is highest priority.
 * Quantum : 4 unit time
 * Preemptive:
If one process e.g. P1 is scheduled and running , now another process with higher priority comes e.g. P2. New process(high priority)
process P2 preempts currently running process P1 and process P1 will go to second level queue.

2. Round Robin Scheduling (Queue 2)
* Quantum :2 unit time
* All the processes in second level queue will complete their execution according to round robin scheduling.
* Queue 2 will be processed after Queue 1 becomes empty.
* Priority of Queue 2 has lower priority than in Queue 1.


Suppose Queue 1 is empty and currently process from Queue 2 is being executed. Now, If at this time a new process arrives then new process will be part of Queue 1. So, new
process should be scheduled as Queue 1 has higher priority than Queue 2. Again after Queue 1 becomes empty Queue 2 will resume execution.



===========================================================

                      INPUT FORMAT

===========================================================

<Pid> <Burst_Time> <Priority>


===========================================================

                      OUTPUT FORMAT

===========================================================


<Pid> <Burst_Time> <Waiting_Time> <Turn Around_Time>



===========================================================

                      Sample Input :

===========================================================

<2 2 2> <1 1 1> <4 4 4> <3 3 3>


===========================================================

                    Sample Output:

===========================================================

<1 1 0 1> <3 3 1 4> <2 2 4 6> <4 4 6 10>
Order : P1 P3 P2 P4 P4