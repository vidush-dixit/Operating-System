#include <stdio.h>
#include <stdlib.h>

struct Process
{
	int Num;                                                                            //Process(Object) Number
	int Pid;                                                                            //Process Id
	int Priority;                                                                       //Process Priority
	int B_time;                                                                         //Process Burst Time
	int W_time;                                                                         //Process Waiting Time
	int TaT;                                                                            //Process Turn Around Time
};

// For Swapping the values
void swap(struct Process *xp, struct Process *yp)
{
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//Bubble Sort for Sorting the Items
void bubbleSort(struct Process arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)
       for (j = 0; j < n-i-1; j++)
       {
           if (arr[j].Priority > arr[j+1].Priority)
              swap(&arr[j], &arr[j+1]);
       }

}

// Function to find the waiting time for all processes
void findWaitingTime(struct Process proc[], int n)
{
    // waiting time for first process is 0
    proc[0].W_time = 0;

    // calculating waiting time
    for (int  i = 1; i < n ; i++ )
        proc[i].W_time =  proc[i-1].B_time + proc[i-1].W_time;
}

// Function to find the waiting time for all processes
void findRoundWaitingTime(struct Process proc[],int n, int curr_time, int quantum,int *Ghant,int n2)
{
    // Make a copy of burst times to store remaining burst times.
    int rem_bt[n],j = 0;
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] =  proc[i].B_time;

    int t = curr_time; // Current time

    // Keep traversing processes in round robin manner until all of them are finished.
    while (1)
    {
        int done = 1;

        // Traverse all processes one by one repeatedly
        for (int i = 0 ; i < n; i++)
        {
            // If burst time of a process is greater than 0, then only need to process further
            if (rem_bt[i] > 0)
            {
                done = 0; // There is a pending process

                if (rem_bt[i] > quantum)
                {
                    // Increase the value of t i.e. shows how much time a process has been processed
                    t += quantum;

                    // Decrease the burst_time of current process by quantum
                    rem_bt[i] -= quantum;
                }

                // If burst time is smaller than or equal to quantum. Last cycle for this process
                else
                {
                    // Increase the value of t i.e. shows how much time a process has been processed
                    t = t + rem_bt[i];

                    // Waiting time is current time minus time used by this process
                    proc[i].W_time = t - proc[i].B_time;

                    // As the process gets fully executed make its remaining burst time = 0
                    rem_bt[i] = 0;
                }
               Ghant[j+n2] = proc[i].Pid;j++;
            }
        }

        // If all processes are done
        if (done == 1)
          break;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(struct Process proc[], int n)
{
    // calculating turnaround time by adding "B_time[i] + W_time[i]"
    for (int  i = 0; i < n ; i++)
        proc[i].TaT = proc[i].B_time + proc[i].W_time;
}

//Function to calculate average time
void findavgTime(struct Process proc[], int n)
{
    int total_wt = 0, total_tat = 0;

    //Function to find turn around time for all processes
    findTurnAroundTime(proc, n);

    // Calculate total waiting time and total turn around time
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + proc[i].W_time;
        total_tat = total_tat + proc[i].TaT;
        printf("    %d\t\t%d\t\t%d\t\t%d\n",proc[i].Pid,proc[i].B_time,proc[i].W_time,proc[i].TaT);
    }

//    printf("\nAverage waiting time = %f",((float)total_wt / (float)n));
//    printf("\nAverage turn around time = %f",((float)total_tat / (float)n));
}

void priorityScheduling(struct Process proc[], int n,int *Ghant)
{
    // Sort processes by priority
    bubbleSort(proc,n);
    for(int i=0;i<n;i++)
        Ghant[i] = proc[i].Pid;

    //Display processes along with all details
    printf("\nProcesses | Burst time | Waiting time | Turn around time\n");

    findavgTime(proc, n);
}

int main()
{
	int i=0,j=0,n;
	int q1_Size, q2_Size, quantum = 2,sum_Burst = 0;

	printf("Enter the number of Processes : ");
	scanf("%d",&n);

	struct Process P_Input[n];
	struct Process Q_Input[n];
	q1_Size = 0;
	q2_Size = n;

	printf("Pid | Burst_time | Priority \n");
    for(int i=0;i< q2_Size;i++)
	{
	    scanf("%d%d%d",&Q_Input[i].Pid,&Q_Input[i].B_time,&Q_Input[i].Priority);
	    Q_Input[i].Num = i+1;
    }

    // To Differentiate 2 Queues based on Input
    for(int i=1;i<q2_Size;i++)
	{
	    if(Q_Input[i].Priority<Q_Input[i-1].Priority)
        {
            P_Input[q1_Size].Num = Q_Input[i].Num;
            P_Input[q1_Size].Pid = Q_Input[i].Pid;
            P_Input[q1_Size].B_time = Q_Input[i].B_time;
            P_Input[q1_Size].Priority = Q_Input[i].Priority;
            for(int j=i;j<q2_Size;j++)
            {
                Q_Input[j].Num = Q_Input[j+1].Num;
                Q_Input[j].Pid = Q_Input[j+1].Pid;
                Q_Input[j].B_time = Q_Input[j+1].B_time;
                Q_Input[j].Priority = Q_Input[j+1].Priority;
            }
            q2_Size--;
            q1_Size++;
        }
    }

    printf("\nQueue 1 with Size(%d): \n",q1_Size);
    for(int i=0;i<q1_Size;i++)
        printf("%d ",P_Input[i].Priority);
    printf("\nQueue 2 with Size(%d): \n",q2_Size);
    for(int i=0;i<q2_Size;i++)
        printf("%d ",Q_Input[i].Priority);

    for(int i=0;i<q2_Size;i++)
        sum_Burst += Q_Input[i].B_time;
    sum_Burst = (sum_Burst/quantum)+1;
    sum_Burst += q1_Size;
    int Ghant[sum_Burst];

    //Function to find waiting time of all processes
    findWaitingTime(P_Input, q1_Size);
    priorityScheduling(P_Input, q1_Size,Ghant);
    // Function to find waiting time of all processes
    findRoundWaitingTime(Q_Input, q2_Size, P_Input[q1_Size-1].W_time + P_Input[q1_Size-1].B_time, quantum,Ghant,q1_Size);
    findavgTime(Q_Input, q2_Size);

    printf("\nOrder in which processes gets executed \n");
    for(int j=0;j<sum_Burst-1;j++)
        printf("P%d ",Ghant[j]);
}
