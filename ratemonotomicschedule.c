#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;math.h&gt;
#include &lt;stdbool.h&gt;
#define MAX_PROCESS 10
int num_of_process = 3, count, remain, time_quantum;
int execution_time[MAX_PROCESS], period[MAX_PROCESS],
remain_time[MAX_PROCESS], deadline[MAX_PROCESS],
remain_deadline[MAX_PROCESS];
int burst_time[MAX_PROCESS], wait_time[MAX_PROCESS],
completion_time[MAX_PROCESS], arrival_time[MAX_PROCESS];
void get_process_info(int selected_algo)
{
printf(&quot;Enter total number of processes (maximum %d): &quot;,
MAX_PROCESS);
scanf(&quot;%d&quot;, &amp;num_of_process);
if (num_of_process &lt; 1)
{
printf(&quot;Do you really want to schedule %d processes? -_-&quot;,
num_of_process);
exit(0);
}
if (selected_algo == 2)
{
printf(&quot;\nEnter Time Quantum: &quot;);
scanf(&quot;%d&quot;, &amp;time_quantum);
if (time_quantum &lt; 1)
{

printf(&quot;Invalid Input: Time quantum should be greater than 0\n&quot;);
exit(0);
}
}
for (int i = 0; i &lt; num_of_process; i++)
{
printf(&quot;\nProcess %d:\n&quot;, i + 1);
if (selected_algo == 1)
{
printf(&quot;==&gt; Burst time: &quot;);
scanf(&quot;%d&quot;, &amp;burst_time[i]);
}
else if (selected_algo == 2)
{
printf(&quot;=&gt; Arrival Time: &quot;);
scanf(&quot;%d&quot;, &amp;arrival_time[i]);
printf(&quot;=&gt; Burst Time: &quot;);
scanf(&quot;%d&quot;, &amp;burst_time[i]);
remain_time[i] = burst_time[i];
}
else if (selected_algo &gt; 2)
{
printf(&quot;==&gt; Execution time: &quot;);
scanf(&quot;%d&quot;, &amp;execution_time[i]);
remain_time[i] = execution_time[i];
if (selected_algo == 4)
{
printf(&quot;==&gt; Deadline: &quot;);
scanf(&quot;%d&quot;, &amp;deadline[i]);
}
else
{
printf(&quot;==&gt; Period: &quot;);
scanf(&quot;%d&quot;, &amp;period[i]);
}
}

}
}
// get maximum of three numbers
int max(int a, int b, int c)
{
int max;
if (a &gt;= b &amp;&amp; a &gt;= c)
max = a;
else if (b &gt;= a &amp;&amp; b &gt;= c)
max = b;
else if (c &gt;= a &amp;&amp; c &gt;= b)
max = c;
return max;
}
// calculating the observation time for scheduling timeline
int get_observation_time(int selected_algo)
{
if (selected_algo &lt; 3)
{
int sum = 0;
for (int i = 0; i &lt; num_of_process; i++)
{
sum += burst_time[i];
}
return sum;
}
else if (selected_algo == 3)
{
return max(period[0], period[1], period[2]);
}
else if (selected_algo == 4)
{
return max(deadline[0], deadline[1], deadline[2]);
}
}

// print scheduling sequence
void print_schedule(int process_list[], int cycles)
{
printf(&quot;\nScheduling:\n\n&quot;);
printf(&quot;Time: &quot;);
for (int i = 0; i &lt; cycles; i++)
{
if (i &lt; 10)
printf(&quot;| 0%d &quot;, i);
else
printf(&quot;| %d &quot;, i);
}
printf(&quot;|\n&quot;);
for (int i = 0; i &lt; num_of_process; i++)
{
printf(&quot;P[%d]: &quot;, i + 1);
for (int j = 0; j &lt; cycles; j++)
{
if (process_list[j] == i + 1)
printf(&quot;|####&quot;);
else
printf(&quot;| &quot;);
}
printf(&quot;|\n&quot;);
}
}
void rate_monotonic(int time)
{
int process_list[100] = {0}, min = 999, next_process = 0;
float utilization = 0;
for (int i = 0; i &lt; num_of_process; i++)
{
utilization += (1.0 * execution_time[i]) / period[i];
}

int n = num_of_process;
if (utilization &gt; n * (pow(2, 1.0 / n) - 1))
{
printf(&quot;\nGiven problem is not schedulable under the said
scheduling algorithm.\n&quot;);
exit(0);
}

for (int i = 0; i &lt; time; i++)
{
min = 1000;
for (int j = 0; j &lt; num_of_process; j++)
{
if (remain_time[j] &gt; 0)
{
if (min &gt; period[j])
{
min = period[j];
next_process = j;
}
}
}
if (remain_time[next_process] &gt; 0)
{
process_list[i] = next_process + 1; // +1 for catering 0 array index.
remain_time[next_process] -= 1;
}
for (int k = 0; k &lt; num_of_process; k++)
{
if ((i + 1) % period[k] == 0)
{
remain_time[k] = execution_time[k];
next_process = k;
}

}
}
print_schedule(process_list, time);
}

int main(int argc, char *argv[])
{
int option = 0;
printf(&quot;3. Rate Monotonic Scheduling\n&quot;);
printf(&quot;Select &gt; &quot;);
scanf(&quot;%d&quot;, &amp;option);
printf(&quot;-----------------------------\n&quot;);
get_process_info(option); // collecting processes detail
int observation_time = get_observation_time(option);

if (option == 3)
rate_monotonic(observation_time);
return 0;
}
