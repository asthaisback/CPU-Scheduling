#include <stdio.h>
struct Process {
	int process_id;
	int arrival_time;
	int burst_time;
};
void fcfs_scheduling(struct Process processes[], int n) {
	int current_time = 0;
	int total_waiting_time = 0;
	printf("FCFS Scheduling:\n");
	for (int i = 0; i < n; i++) {
		if (processes[i].arrival_time > current_time) {
		current_time = processes[i].arrival_time;
		}
		int waiting_time = current_time - processes[i].arrival_time;
		total_waiting_time += waiting_time;
		printf("Process ID: %d Waiting Time: %d\n", processes[i].process_id, waiting_time);
		current_time += processes[i].burst_time;
	}
	float average_waiting_time = (float)total_waiting_time / n;
	printf("Average Waiting Time: %.2f\n\n", average_waiting_time);
}
void sjn_scheduling(struct Process processes[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (processes[i].burst_time > processes[j].burst_time) {
				struct Process temp = processes[i];
				processes[i] = processes[j];
				processes[j] = temp;
			}
		}
	}
	int current_time = 0;
	int total_waiting_time = 0;
	printf("SJN Scheduling:\n");
	for (int i = 0; i < n; i++) {
		if (processes[i].arrival_time > current_time) {
			current_time = processes[i].arrival_time;
		}
		int waiting_time = current_time - processes[i].arrival_time;
		total_waiting_time += waiting_time;
		printf("Process ID: %d Waiting Time: %d\n", processes[i].process_id, waiting_time);
		current_time += processes[i].burst_time;
	}
	float average_waiting_time = (float)total_waiting_time / n;
	printf("Average Waiting Time: %.2f\n\n", average_waiting_time);
}
void round_robin_scheduling(struct Process processes[], int n, int time_quantum) {
	int current_time = 0;
	int total_waiting_time = 0;
	printf("Round Robin Scheduling (Time Quantum: %d)\n", time_quantum);
	int remaining_burst_time[n];
	for (int i = 0; i < n; i++) {
		remaining_burst_time[i] = processes[i].burst_time;
	}
	while (1) {
		int all_processes_completed = 1;
		for (int i = 0; i < n; i++) {
			if (remaining_burst_time[i] > 0) {
				all_processes_completed = 0;
				if (processes[i].arrival_time <= current_time) {
					if (remaining_burst_time[i] > time_quantum) {
						remaining_burst_time[i] -= time_quantum;
						current_time += time_quantum;
					}
					else {
						int waiting_time = current_time - processes[i].arrival_time;
						total_waiting_time += waiting_time;
						current_time += remaining_burst_time[i];
						remaining_burst_time[i] = 0;
						printf("Process ID: %d Waiting Time: %d\n", processes[i].process_id, waiting_time);
					}
				}
				else {
					current_time++;
				}
			}
		}
		if (all_processes_completed) {
			break;
		}
	}
	float average_waiting_time = (float)total_waiting_time / n;
	printf("Average Waiting Time: %.2f\n", average_waiting_time);
}
int main() {
	struct Process processes[] = {
		{1, 0, 10},
		{2, 4, 6},
		{3, 2, 8},
		{4, 5, 4}
	};
	int n = sizeof(processes) / sizeof(processes[0]);
	int time_quantum = 2;
	fcfsfcfs_scheduling(processes, n);
	sjn_scheduling(processes, n);
	round_robin_scheduling(processes, n, time_quantum);
	return 0;
}
