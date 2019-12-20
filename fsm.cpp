/**
 * @file fsm.cpp
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
#include "fsm.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
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
 * @brief : function initializes fsm
 * 
 * @param fsm_obj : obj
 * @return int 
 */
int fsm_init(struct fsm_obj_s *obj)
{
    obj->fsm_base = NULL;
    obj->fsm_cur_state = NULL;
    obj->fsm_arg_num = 0;
    obj->fsm_arg_value = NULL;
    return 0;
}

/**
 * @brief : function next state
 * 
 * @param obj : object
 * @return int 
 */
int fsm_next_state(struct fsm_obj_s *obj)
{
	struct fsm_state_t *tmp = obj->fsm_base;
	// check obj->fsm 
	if ((obj->fsm_base == NULL) || (obj->fsm_cur_state_name == NULL))
	{
		return -1;
	}
	while ((tmp->name != obj->fsm_cur_state_name) && (tmp != NULL))
	{
		tmp = tmp->p_next;
	}
	if (tmp == NULL)
	{
		return -1;
	}
	tmp->func_t(obj, obj->fsm_arg_num, obj->fsm_arg_value);
	return 0;
}

int fsm_main(struct fsm_obj_s *obj)
{
	while (!fsm_next_state(obj));
	return 0;
}

/**
 * @brief : function add state
 * 
 * @param obj : object 
 * @param name : name state
 * @param func : pointer function
 * @return int 
 */
int fsm_add(struct fsm_obj_s *obj, char *name, void(*func)(struct fsm_obj_s*, int, void**))
{
	struct fsm_state_t *tmp = obj->fsm_base;
	struct fsm_state_t *new_state = (struct fsm_state_t*)malloc(sizeof(struct fsm_state_t));
	while (tmp->p_next)
	{
		tmp = tmp->p_next;
	}
	new_state->name = name;
	new_state->func_t = func;
	new_state->p_next = NULL;
	tmp->p_next = new_state;
	
	return 0;
}

/**
 * @brief : function remove state 
 * 
 * @param obj : object
 * @param name : name state
 * @return int 
 */
int fsm_remove(struct fsm_obj_s *obj, char *name)
{
	if (!strcmp(name, "default"))
		return -1;
	struct fsm_state_t *to_del;
	struct fsm_state_t *tmp = obj->fsm_base;
	while ((tmp->p_next != NULL) && (strcmp(tmp->p_next->name, name)))
	{
		tmp = tmp->p_next;
	}
	if (tmp == NULL)
	{
		return - 1;
	}
	to_del = tmp->p_next;
	tmp->p_next = tmp->p_next->p_next;
	free(to_del);
	return 0;
}

/**
 * @brief : function 
 * 
 * @param obj 
 * @param name 
 * @param num 
 * @param arg 
 * @return int 
 */
int fsm_to_state(struct fsm_obj_s *obj, char *name, int num, void** arg)
{
	struct fsm_state_t *tmp = obj->fsm_base;

	printf(" %s %s \n",tmp->name, name);
	while ((tmp != NULL) && (strcmp(tmp->name, name) != 0))
	{
		printf(" %s %s \n",tmp->name, name);
		tmp = tmp->p_next;
	}
	
	if (tmp == NULL)
	{
		return -1;
	}

	obj->fsm_cur_state = tmp;
	obj->fsm_cur_state_name = name;
	obj->fsm_arg_num = num;
	obj->fsm_arg_value = arg;
	return 0;
}

int fsm_default(struct fsm_obj_s *obj, void(*func)(struct fsm_obj_s *, int, void **))
{
	obj->fsm_base = (struct fsm_state_t*)malloc(sizeof(struct fsm_state_t));
	obj->fsm_base->name = "default";
	obj->fsm_base->func_t = func;
	obj->fsm_base->p_next = NULL;
	obj->fsm_cur_state = obj->fsm_base;
	obj->fsm_cur_state_name = obj->fsm_base->name;
	return 0;
}

void fsm_terminate(struct fsm_obj_s *obj)
{
	struct fsm_state_t *tmp = obj->fsm_base;
	struct fsm_state_t *to_del = tmp;
	while (tmp)
	{
		to_del = tmp;
		tmp = tmp->p_next;
		free(to_del);
	}
	obj->fsm_cur_state = NULL;
	obj->fsm_cur_state_name = NULL;
	obj->fsm_base = NULL;
}


int test (struct fsm_obj_s *obj, char *name, int num, void** arg)
{
	struct fsm_state_t *tmp = obj->fsm_base;

	while ((tmp != NULL) && (strcmp(tmp->name, name)))
	{
		tmp = tmp->p_next;
	}
	
	if (tmp == NULL)
	{
		return -1;
	}
	
	printf(" ok ");
	obj->fsm_cur_state = tmp;
	//FIXME: khong hieu lam
	obj->fsm_cur_state_name = name;
	obj->fsm_arg_num = num;
	obj->fsm_arg_value = arg;
	return 0;
}

/******************************** End of file *********************************/
