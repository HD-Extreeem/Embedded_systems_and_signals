/*
 * test_stateMachine.h
 *
 * Created: 2015-06-17 16:32:16
 *  Author: Ulrik
 */ 

#ifndef TEST_STATEMACHINE_H_
#define TEST_STATEMACHINE_H_

void test_stateMachineStartsInLockedState(void);

void test_stateGoesToPushOneWhenFirstCorrectButtonIsPressed(void);
void test_stateGoesToLockedWhenFirstIncorrectButtonIsPressed(void);

void test_stateGoesToPushTwoWhenSecondCorrectButtonIsPressed(void);
void test_stateGoesToLockedWhenSecondIncorrectButtonIsPressed(void);

void test_stateGoesToPushThreeWhenThirdCorrectButtonIsPressed(void);
void test_stateGoesToLockedWhenThirdIncorrectButtonIsPressed(void);

void test_stateGoesToOpenWhenFourthCorrectButtonIsPressed(void);
void test_stateGoesToLockedWhenFourthIncorrectButtonIsPressed(void);

#endif /* TEST_STATEMACHINE_H_ */