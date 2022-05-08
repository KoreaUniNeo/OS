#include "message_buffer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int shmid;
void *memory_segment=NULL;

int init_buffer(MessageBuffer **buffer) {

    if((shmid = shmget(KEY, sizeof(int), IPC_CREAT|0666))==-1) return -1;
    if((memory_segment = shmat(shmid, NULL,0))==(void*)-1) return -1;
    *buffer = (MessageBuffer*)memory_segment;
    (*buffer)->is_empty = 1;
    printf("init buffer\n");
    return 0;
}

int attach_buffer(MessageBuffer **buffer) {
    /*---------------------------------------*/
    /* TODO 2 : attach buffer                */
    /* do not consider "no buffer situation" */
    if((shmid = shmget(KEY, sizeof(int), IPC_CREAT|0666))==-1) return -1;
    if((memory_segment = shmat(shmid, NULL,0))==(void*)-1) return -1;
    *buffer = (MessageBuffer*) memory_segment;
    /* TODO 2 : END                          */
    /*---------------------------------------*/

    printf("attach buffer\n");
    printf("\n");
    return 0;
}

int detach_buffer() {
    if (shmdt(memory_segment) == -1) {
        printf("shmdt error!\n\n");
        return -1;
    }

    printf("detach buffer\n\n");
    return 0;
}

int destroy_buffer() {
    if(shmctl(shmid, IPC_RMID, NULL) == -1) {
        printf("shmctl error!\n\n");
        return -1;
    }

    printf("destroy shared_memory\n\n");
    return 0;
}

int produce(MessageBuffer **buffer, int sender_id, int data, int account_id) {

    /*---------------------------------------*/
    /* TODO 3 : produce message              */
    int value = 0 ;
    value = (*buffer)->messages[account_id].data + data;
    if(value<0){
        printf("잔고가 부족합니다.")
    }
    else{
        (*buffer)->is_empty = 0;
        (*buffer)->messages[account_id].data = value;
        (*buffer)->messages[account_id].sender_id = sender_id;
    }
    /* TODO 3 : END                          */
    /*---------------------------------------*/

    printf("produce message\n");

    return 0;
}

int consume(MessageBuffer **buffer, Message **message) {
    if((*buffer)->is_empty)
        return -1;

    /*---------------------------------------*/
    /* TODO 4 : consume message              */
    else{
        **message.data = (*buffer)->messages[(*buffer)->account_id].data;
        **message.sender_id = (*buffer)->messages[(*buffer)->account_id].sender_id;
        (*buffer)->is_empty = 1;
    }

    /* TODO 4 : END                          */
    /*---------------------------------------*/

    return 0;
}
