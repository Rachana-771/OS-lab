#include <stdio.h>

#define MAX_TASKS 10

typedef struct {
    int arrival_time;
    int execution_time;
    int deadline;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Task;

void initializeTasks(Task tasks[], int num_tasks) {
    for (int i = 0; i < num_tasks; i++) {
        printf("Enter arrival time for task %d: ", i + 1);
        scanf("%d", &tasks[i].arrival_time);
        printf("Enter execution time for task %d: ", i + 1);
        scanf("%d", &tasks[i].execution_time);
        printf("Enter deadline for task %d: ", i + 1);
        scanf("%d", &tasks[i].deadline);
        tasks[i].remaining_time = tasks[i].execution_time;
        tasks[i].waiting_time = 0;
        tasks[i].turnaround_time = 0;
    }
}

int findEarliestDeadlineTask(Task tasks[], int num_tasks, int current_time) {
    int earliest_deadline_task = -1;
    for (int i = 0; i < num_tasks; i++) {
        if (tasks[i].remaining_time > 0 && tasks[i].arrival_time <= current_time) {
            if (earliest_deadline_task == -1 || tasks[i].deadline < tasks[earliest_deadline_task].deadline) {
                earliest_deadline_task = i;
            }
        }
    }
    return earliest_deadline_task;
}

int main() {
    int num_tasks;
    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    Task tasks[MAX_TASKS];
    initializeTasks(tasks, num_tasks);

    int current_time = 0;
    int completed_tasks = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("\nEDF CPU Scheduling:\n");
    while (completed_tasks < num_tasks) {
        int current_task = findEarliestDeadlineTask(tasks, num_tasks, current_time);

        if (current_task != -1) {
            printf("Time %d: Running Task %d\n", current_time, current_task + 1);
            tasks[current_task].remaining_time--;

            if (tasks[current_task].remaining_time == 0) {
                completed_tasks++;
                tasks[current_task].turnaround_time = current_time + 1 - tasks[current_task].arrival_time;
                tasks[current_task].waiting_time = tasks[current_task].turnaround_time - tasks[current_task].execution_time;
                total_waiting_time += tasks[current_task].waiting_time;
                total_turnaround_time += tasks[current_task].turnaround_time;
                printf("Time %d: Task %d completed\n", current_time + 1, current_task + 1);
            }
        } else {
            printf("Time %d: CPU idle\n", current_time);
        }

        current_time++;
    }

    double avg_waiting_time = (double)total_waiting_time / num_tasks;
    double avg_turnaround_time = (double)total_turnaround_time / num_tasks;

     printf("\n process\t executiontime\tdeadline\twait_time\tturnaroundtime");
     for(int i=0;i<num_tasks;i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i+1,tasks[i].execution_time,tasks[i].deadline,tasks[i].waiting_time,tasks[i].turnaround_time);
     }

    printf("\nAverage Waiting Time: %.2lf\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2lf\n", avg_turnaround_time);

    return 0;
}
