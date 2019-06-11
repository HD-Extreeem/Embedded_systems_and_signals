/*
 * taskLock.h
 *
 * Created: 2016-12-14 08:30:35
 *  Author: Leo & Hadi
 */ 


#ifndef LOCKTASK_H_
#define LOCKTASK_H_


#define TASK_CODELOCK_STACK_SIZE (2048/sizeof(portSTACK_TYPE))
#define TASK_CODELOCK_STACK_PRIORITY (2)
void task_codeLock(void *pvParam);

#endif /* LOCKTASK_H_ */