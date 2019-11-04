/**
 * @file main.cpp
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-28
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include <stdio.h>
#include "fsm.h"
#include <windows.h>
// #include <unistd.h>
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

/**
 * @brief 
 * 
 * @param obj 
 * @param num 
 * @param arg 
 */
void default_func(struct fsm_obj_s *obj, int num, void **arg)
{
	// state default
	// printf("%d\n", num);
	printf("%s\n", obj->fsm_cur_state_name);
	fsm_to_state(obj, "step2", 0, NULL);
	//test(obj, "step1", 0, NULL);
	//Sleep(1000);
}

/**
 * @brief 
 * 
 * @param obj 
 * @param num 
 * @param arg 
 */
void step1(struct fsm_obj_s *obj, int num, void **arg)
{
	// state step 1
	// printf("%d\n", num);
	printf("%s\n", obj->fsm_cur_state_name);
	fsm_to_state(obj, "default", 0, NULL);
	//Sleep(1000);
}

/**
 * @brief 
 * 
 * @param obj 
 * @param num 
 * @param arg 
 */
void step2(struct fsm_obj_s *obj, int num, void **arg)
{
	// printf("%d\n", num);
	printf("%s\n", obj->fsm_cur_state_name);
	fsm_to_state(obj, "step1", 0, NULL);
	//Sleep(1000);
}

/**
 * @brief 
 * 
 * @return int 
 */
int main()
{
	struct fsm_obj_s obj;

	fsm_init(&obj);
    printf("start !! \n");
	fsm_default(&obj, default_func);
	fsm_add(&obj, "step1", step1);
	fsm_add(&obj, "step2", step2);
	fsm_main(&obj);

    return 0;
}

/******************************** End of file *********************************/
