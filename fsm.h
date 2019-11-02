/**
 * @file fsm.h
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-28
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
#ifndef __FSM_H__
#define __FSM_H__

struct fsm_obj_s;

struct fsm_state_t
{
    // name of state
    char *name;
    // pointer function
    void(*func_t)(struct fsm_obj_s*, int, void**);

    // next state
    struct fsm_state_t *p_next;
};

struct fsm_obj_s
{
    // state default
    struct fsm_state_t *fsm_base;
    // state current
    struct fsm_state_t *fsm_cur_state;
    // name state current
    char *fsm_cur_state_name;

    int fsm_arg_num;

    void** fsm_arg_value;

};

int fsm_init(struct fsm_obj_s *obj);

int fsm_add(struct fsm_obj_s *obj, char *name, void(*func)(struct fsm_obj_s*, int, void**));

int fsm_next_state(struct fsm_obj_s *obj);

int fsm_remove(struct fsm_obj_s *obj, char *name);

int fsm_main(struct fsm_obj_s *obj);

int fsm_to_state(struct fsm_obj_s *obj, char *name, int num, void** arg);

int fsm_default(struct fsm_obj_s *obj, void(*func)(struct fsm_obj_s *, int, void**));

void fsm_terminate(struct fsm_obj_s *obj);

#endif /* __FSM_H__ */

/******************************** End of file *********************************/
