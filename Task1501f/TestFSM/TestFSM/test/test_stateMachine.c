/*
 * test_stateMachine.c
 *
 * Created: 2015-06-17 16:29:39
 * Author: Uek
 *
 * The tests for the state machine assumes the code is 1332, same as in the example in the assignment
 * Note that the tests DO NOT COVER ALL STATE TRANSITIONS!
 */
 
//#include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */
#include <asf.h>
#include "../unity/unity.h"
#include "../src/delayFunctions.h"
#include "../src/stateMachine.h"
#include "test_stateMachine.h"

extern codeLockType SM;			/* The memory area for the state machine */
extern codeLockPtrType instance;	/* A pointer to a state machine of this type */

void test_stateMachineStartsInLockedState(void)
{
	instance->state = OPEN;
	startCodeLock(instance);
	TEST_ASSERT_TRUE(instance->state == Locked);
}

void test_stateGoesToPushOneWhenFirstCorrectButtonIsPressed(void)
{
	instance->state = Locked;
	pushButton1(instance);
	TEST_ASSERT_TRUE(instance->state == PushOne);
	releaseButton(instance);
	TEST_ASSERT_TRUE(instance->state == ReleaseOne);
}

void test_stateGoesToLockedWhenFirstIncorrectButtonIsPressed(void)	/* This test will likely pass since it just requires the SM to stay in the same Locked state */
{
	instance->state = Locked;
	pushButton3(instance);
	TEST_ASSERT_TRUE(instance->state == Locked);
	releaseButton(instance);
	TEST_ASSERT_TRUE(instance->state == Locked);
}

void test_stateGoesToPushTwoWhenSecondCorrectButtonIsPressed(void)
{
	instance->state = ReleaseOne;
	//1
	/* Add code here and choose which button you want to be the correct one*/
	pushButton3(instance);
	TEST_ASSERT_TRUE(instance->state == PushTwo);
	releaseButton(instance);
	TEST_ASSERT_TRUE(instance->state == ReleaseTwo);
}

void test_stateGoesToLockedWhenSecondIncorrectButtonIsPressed(void)
{
	instance->state = ReleaseOne;
	//2
	/*Any of the other buttons but the one that is correct*/
	pushButton2(instance);
	//3
	/*Add test here to see if you are in the correct state*/
	TEST_ASSERT_TRUE(instance->state == Locked );
	releaseButton(instance);
	//4
	/* Add another test to check if you're in the right state after you release*/	
	TEST_ASSERT_TRUE(instance->state==Locked);
}

void test_stateGoesToPushThreeWhenThirdCorrectButtonIsPressed(void)
{
	instance->state = ReleaseTwo;
	pushButton3(instance);
	TEST_ASSERT_TRUE(instance->state == PushThree);
	releaseButton(instance);
	TEST_ASSERT_TRUE(instance->state == ReleaseThree);	
}

void test_stateGoesToLockedWhenThirdIncorrectButtonIsPressed(void)
{
	instance->state = ReleaseTwo;
	pushButton2(instance);
	TEST_ASSERT_TRUE(instance->state == Locked);
	releaseButton(instance);
	TEST_ASSERT_TRUE(instance->state == Locked);
}

void test_stateGoesToOpenWhenFourthCorrectButtonIsPressed(void)
{
	instance->state = ReleaseThree;
	pushButton2(instance);
	TEST_ASSERT_TRUE(instance->state == PushFour);
	releaseButton(instance);
	TEST_ASSERT_TRUE(instance->state == OPEN);
}

void test_stateGoesToLockedWhenFourthIncorrectButtonIsPressed(void)
{
	instance->state = ReleaseTwo;
	pushButton1(instance);
	TEST_ASSERT_TRUE(instance->state == Locked);
	releaseButton(instance);
	TEST_ASSERT_TRUE(instance->state == Locked);
}
