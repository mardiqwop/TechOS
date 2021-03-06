//
// Created by Russell on 10/1/2017.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "queue.h"
#include "help.h"

/**
 * You have two queues or four queues.
 * You must have a Ready queue that holds all PCBs that are in the ready state.
 * The PCBs in this queue should be stored in priority order, with the highest priority
 * at the head of the queue. You must have a Blocked queue that holds all PCBs in the blocked
 * state. The PCBs in this queue should be stored in FIFO order.
 *
 * You may also crete separate queues for suspended PCBs. This would be the two
 * additional queues previously mentioned: A Suspended Ready queue and a Suspended Blocked queue.
 *
 */

struct queue ready_queue;   // Holds all processes in the ready state, sorted by priority.
struct queue blocked_queue; // Holds all processes in the blocked state, sorted FIFO.
struct queue suspended_ready_queue;
struct queue suspended_blocked_queue;

/***
 * Initializes all queues for use.
 */
void initQueues(struct queue* q) {
    ready_queue.count = 0;
    ready_queue.head = NULL;
    ready_queue.tail = NULL;
    blocked_queue.count = 0;
    blocked_queue.head = NULL;
    blocked_queue.tail = NULL;
    suspended_ready_queue.count = 0;
    suspended_ready_queue.head = NULL;
    suspended_ready_queue.tail = NULL;
    suspended_blocked_queue.count = 0;
    suspended_blocked_queue.head = NULL;
    suspended_blocked_queue.tail = NULL;
}


/**
 * Allocates memory for a new PCB.
 * Returns either a pointer to the new PCB or NULL if there is an error during allocation.
 */
pcb* AllocatePCB() {
    pcb* alloc_process = malloc(sizeof(pcb));
    return alloc_process;
}

/**
 * Frees all memory asscoated with a given PCB.
 * Take a pointer to the PCB as a Parameter.
 */
int FreePCB(pcb* process) {
    free(process);
    return 0;
}

/**
 * Calls AllocatePCB() to create an empty PCB.
 * After, the PCB information should be initialized, state to ready and not suspended.
 * Three params: Process name, process class, and process priority
 * Returns pointer to pcb or null if an error occurs
 */
pcb* SetupPCB(char* process_name, int priority, char* file_name) {
    pcb* new_pcb = AllocatePCB();

    if(strlen(process_name)>8){
        printf("\nERROR: The name of this process is larger than 8 characters.");
        return NULL;
    }
    if(priority > 9 || priority < 0){
        printf("\nERROR: The priority isn't between 0 and 9.");
        return NULL;
    }
    strcpy(new_pcb->process_name, process_name);
    strcpy(new_pcb->file_name, file_name);
    new_pcb->priority = priority;
    new_pcb->running_state = READY;
    new_pcb->suspension_state = NOTSUSPENDED;
    new_pcb->offset = 0;
    return new_pcb;
}


pcb* FindInQueue(char* name, struct queue* q){
    pcb* find_pcb;

    find_pcb = q->head;
    if(find_pcb == NULL){
	return NULL;
    }
    do {

        if(strcmp(name, find_pcb->process_name) == 0) {
            return find_pcb;
        }
        find_pcb = find_pcb->next_pcb;
    } while(find_pcb != NULL);
    return NULL;
}

/**
 * Searches all queues for a process with a given name.
 * Can be used to make sure a process name is unique.
 * @return - Pointer to the found pcb or NULL if not found.
 */
pcb* FindPCB(char* name){

    pcb* result;
    result = FindInQueue(name, &ready_queue);
    if(result != NULL)
        return result;
    result = FindInQueue(name, &suspended_ready_queue);
    if(result != NULL)
        return result;
    result = FindInQueue(name, &blocked_queue);
    if(result != NULL)
        return result;
    result = FindInQueue(name, &suspended_blocked_queue);
    return result;
}

/**
 * Inserts a PCB into the appropriate queue.
 * Ready queue is a priority queue.
 * Blocked queue is a FIFO queue.
 * @param process - pcb to be inserted.
 * @param suspended - flag indicating if it should go in the suspended
 * or normal queues. 1 inidicates suspended, 0 indicates normal
 */
void InsertPCB(pcb* process) {
    if (FindPCB(process->process_name) != NULL) {
        printf("\nERROR: Process Exists! Process not added.");
        return;
    }

    // Set which ready queue or which blocked queue we should insert into
    struct queue *target_ready_queue = (process -> suspension_state == SUSPENDED) ? &suspended_ready_queue : &ready_queue;
    struct queue *target_blocked_queue = (process -> suspension_state == SUSPENDED) ? &suspended_blocked_queue : &blocked_queue;

    // BLOCKED QUEUE
    if (process->running_state == BLOCKED) {
        if (target_blocked_queue->count != 0) {
            target_blocked_queue->tail->next_pcb = process;
            target_blocked_queue->tail = process;
            target_blocked_queue->count++;
            //printf("\nInserted %s into blocked queue.", process->process_name);
            return;
        }
        else {
            target_blocked_queue->head = process;
            target_blocked_queue->tail = process;
	        process->next_pcb = NULL;
            target_blocked_queue->count++;
            //printf("\nInserted %s into blocked queue.", process->process_name);
            return;
        }

    // READY QUEUE
    }
    else {

        /* If the queue is empty */
        if(target_ready_queue->count == 0){
            target_ready_queue->head = process;
            target_ready_queue->tail = process;
            process -> next_pcb = NULL;
            target_ready_queue->count++;
            //printf("\nInserted %s into ready queue.", process->process_name);
            return;
        }
        /* If the queue isn't empty */
        /* Highest Priority */
        if (process->priority >= target_ready_queue->head->priority){
            process->next_pcb = target_ready_queue->head;
            target_ready_queue->head = process;
            target_ready_queue->count++;
            //printf("\nInserted %s into ready queue.", process->process_name);
            return;
        }

        /* Higher Priority */
        pcb* temp_pcb = target_ready_queue->head;
        pcb* prev_temp_pcb = target_ready_queue->head;
        while (temp_pcb->next_pcb != NULL){
            prev_temp_pcb = temp_pcb;
            temp_pcb = temp_pcb->next_pcb;
            if (process->priority >= temp_pcb->priority) {
                prev_temp_pcb->next_pcb = process;
                process->next_pcb = temp_pcb;
                target_ready_queue->count++;
                //printf("\nInserted %s into ready queue.", process->process_name);
                return;
            }
        }

        /* Lowest Priority */
        temp_pcb->next_pcb = process;
        target_ready_queue->tail = process;
        process->next_pcb = NULL;
        target_ready_queue->count++;
        //printf("\nInserted %s into ready queue.", process->process_name);
        return;
    }
}


/**
 * Removes a PCB from the queue in which it is currently stored.
 * Should not free the memory associated with the pcb.
 * @return success or error code.
 * @param process - process to be removed
 */
int RemovePCB(pcb* process){

    // Set which ready queue or which blocked queue we should remove from
    struct queue *target_ready_queue = (process -> suspension_state == SUSPENDED) ? &suspended_ready_queue : &ready_queue;
    struct queue *target_blocked_queue = (process -> suspension_state == SUSPENDED) ? &suspended_blocked_queue : &blocked_queue;

    pcb* index;
    if (target_blocked_queue->head == process){
        target_blocked_queue->head = process->next_pcb;
        process->next_pcb = NULL;
        target_blocked_queue->count--;
        if(target_blocked_queue->tail == process) {
            target_blocked_queue->tail = NULL;
        }
	    return 1;
    }
    index = target_blocked_queue->head;
    while(index != NULL && index->next_pcb != NULL){
        if (index->next_pcb == process) {
            if (target_blocked_queue->tail == process) {
                target_blocked_queue->tail = index->next_pcb;
            }
            index->next_pcb->next_pcb = process->next_pcb;
            process->next_pcb = NULL;
            target_blocked_queue->count--;
            return 1;
        }
	index = index->next_pcb;
    }
    index = target_ready_queue->head;
    // case when the process is at the head
    if(target_ready_queue->head == process){
	if(target_ready_queue->tail == process){
	    target_ready_queue->tail = NULL;
	}
	target_ready_queue->head = process->next_pcb;
	process->next_pcb = NULL;
	target_ready_queue->count--;
	return 1;
    }

    while(index != NULL && index->next_pcb != NULL){
        if (index->next_pcb == process) {
            if (target_ready_queue->tail == process) {
                target_ready_queue->tail = index;
            }
            index->next_pcb = process->next_pcb;
            process->next_pcb = NULL;
            target_ready_queue->count--;
            return 1;
        }
	index = index->next_pcb;
    }
    //printf("\nERROR: Did not find process to be removed.");
    return 0;
}

/**
 * R3
 * Loading a Process
 *  Creates a PCB
 *  Sets up the PCB
 *  Sets the priority of the PCB
 *  Sets the data of the PCB (file path and offset)
 *  Inserts the PCB into the queue
 * Check that the process isn't already loaded, the priority is valid,
 * and the file exists. Otherwise appropriate error message should be given.
 */
pcb* LoadProcess(char* process_name, int priority, char* file_name){
    // pcb* SetupPCB(char* process_name, unsigned char process_class, int priority)

    // Check that the process isn't already loaded

    if (FindPCB(process_name) != NULL){
        printf("\nError: Process %s already exists.", process_name);
        return NULL;
    }

    if (priority < 0 || priority > 9){
        printf("\nError: Priority out of range.");
        return NULL;
    }

    if (access(file_name, F_OK) == -1){
        printf("\nError: File does not exist.");
        return NULL;
    }

    pcb* new_pcb = SetupPCB(process_name, priority, file_name);
    InsertPCB(new_pcb);
    return new_pcb;
}

void printQueue(struct queue *q){
    pcb* index = q -> head;
    while(index != NULL) {
        printf("\n-------------");
        printPCB(index);
        printf("\n-------------");
        index = index->next_pcb;
    }
    printf("\n");
}


void printPCB(pcb* process){
    printf(MAGENTACOLOR);
    printf("\nProcess name: %s", process->process_name);
    printf("\nProcess file: %s", process->file_name);
    printf("\nRunning state: %s", process->running_state == SUSPENDED ? "Not Suspended" : "Suspended");
    printf("\nPriority:  %d", process->priority);
    printf(DEFAULTCOLOR);
}

void printReadyProcesses(){
    printf("\nReady processes:");
    printQueue(&ready_queue);
    printf("\nSuspended Ready Processes:");
    printQueue(&suspended_ready_queue);
}

void printBlockedProcesses(){
    printf("\nBlocked processes:");
    printQueue(&blocked_queue);
    printf("\nSuspended Blocked Processes:");
    printQueue(&suspended_blocked_queue);
}

void printAllProcesses(){
    printReadyProcesses();
    printBlockedProcesses();
}

/**
 * Returns the pcb at the front of the ready queue
 */
pcb* GetNextReadyNotSuspended(){
    return ready_queue.head;
}

pcb* GetNextReadySuspended(){
    return suspended_ready_queue.head;
}

/**
 *Returns the pcb at the front of the blocked queue
 */
pcb* GetNextBlockedNotSuspended(){
    return blocked_queue.head;
}

pcb* GetNextBlockedSuspended(){
    return suspended_blocked_queue.head;
}
