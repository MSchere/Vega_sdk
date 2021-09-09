/**
 * \file	edroombp_4_8_impr_wrapper.h
 * \brief
 *
 * \author	Alberto Carrasco Gallardo, <acarrasco@srg.aut.uah.es>
 * \author	Santiago Carmona Meco, <scarmona@srg.aut.uah.es>
 *
 * \internal
 * Created: 	07-may-2014
 * Compiler: 	gcc/g++
 * Company:  Space Research Group, Universidad de Alcalá.
 * Copyright: Copryright (c) 2014, Alberto Carrasco Gallardo
 * Copyright: Copyright (c) 2014, Santiago Carmona Meco
 *
 * For further information, please visit http://srg.aut.uah.es
 *
 */

#ifndef EDROOMBP_4_8_IMPR_WRAPPER_H_
#define EDROOMBP_4_8_IMPR_WRAPPER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <public/edroom_types_iface_v1.h>

/**
 *  @addtogroup ICUSW_SERVICE_MODULES ICUSw Service Modules
 *  @{
 */
/**
 *  @addtogroup EDROOMSL EDROOM SERVICE LIBRARY
 *  @{
 */
/**
 *  @defgroup EDROOMBP_WRAPPER EDROOMBP C WRAPPER RTEMS
 *  @{
 */
/*				PR_KERNEL FUNCTIONALITY		*/
/**
 * \brief	This function initializes the system. Basically it stablishes the
 * 			Time of Day for RTEMS and capture the initial time value in the
 * 			memory pointed by the parameter start_time.
 * @param[out] start_time	Memory to store the initial time value in seconds and
 * 			microseconds.
 */
void edroombp_system_init(void * start_time);

/*				PR_TASK FUNCTIONALITY		*/
/**
 * 	\brief	Create a task with a given initial priority and stack size.
 * @param[in] initial_priority	the initial priority for the task.
 * @param[in] stack_size	The size of the minimum stack needed by the task.
 * @param[out] id	identifier to return the task id.
 * @return	status of the call.
 */
uint32_t edroombp_task_create(uint32_t initial_priority, size_t stack_size, uint32_t *id);
/**
 * \brief	Put a task in the ready state.
 * @param[in] id	the identifier of the task.
 * @param[in] entry_point	the entry point of the task's code.
 * @param[in] argument	the argument(if any) for the task code.
 */
void edroombp_task_start(uint32_t id, void *entry_point, uint32_t argument);
/**
 * \brief	delete a task
 * @param[in] id	the identifier of the task to delete.
 */
void edroombp_task_delete(uint32_t id);
/**
 * \brief	Associate a variable to a task. The variable shall be refreshed
 * 			when there is a context switch to the task.
 * @param[in] task	the pointer to the variable.
 */
void edroombp_task_variable_add(void ** task);
/**
 * \brief	Get the current priority of a task.
 * @param[in] id	the task identifier.
 * @param[out] old_priority	the old priority shall be returned.
 */
void edroombp_task_get_current_priority(uint32_t id, uint32_t *old_priority);
/**
 * \brief	change the priority of a task.
 * @param[in] priority	the new priority.
 * @param[in] task_id	the task identifier.
 */
void edroombp_task_change_priority(uint32_t priority, uint32_t task_id);

/*			PR_TIME	FUNCTIONALITY				*/
/**
 * \brief	Get the current time.
 * @param[out] time_val	memory to store the value in seconds and microseconds.
 */
void edroombp_get_time(void * time_val);
/**
 * \brief	Wait for a number of clock ticks.
 * @param[in] ticks the number of ticks to wait.
 */
void edroombp_wait_ticks(uint32_t ticks);

/*				SEMAPHORE FUNCTIONALITY			*/
/**
 * \brief	Create a semaphore.
 * @param[in] count	the count, in case is a counting semaphore.
 * @param[in] priority_ceiling	the priority ceiling of the semaphore.
 * @param[out] semId	memory for returning the semaphore identifier.
 */
void edroombp_semaphore_create(uint32_t count, uint32_t priority_ceiling, uint32_t *semId);
/**
 * \brief	release a semaphore.
 * @param[in] semId	the semaphore identifier.
 */
void edroombp_semaphore_release(uint32_t semId);
/**
 * \brief	Catch a semaphore.
 * @param[in] semId	the semaphore identifier.
 */
void edroombp_semaphore_catch(uint32_t semId);
/**
 * \brief	try to catch a semaphore withOUT waiting in case it is already
 * 			catch.
 * @param[in] semId the semaphore identifier.
 * @return	1 if the semaphore was successfully catch, 0 otherwise.
 */
int32_t edroombp_semaphore_try_catch(uint32_t semId);
/**
 * \brief	try to catch a semaphore with a wait of "interval" clock ticks if it
 * 			is already catch.
 * @param[in] semId	the semaphore identifier.
 * @param[in] interval	the maximum number of clock ticks to wait.
 * @return true or false.
 */
bool_t edroombp_semaphore_timed_catch(uint32_t semId, uint32_t interval);
/**
 * \brief	Delete a semaphore.
 * @param[in] semId	the semaphore identifier.
 */
void edroombp_semaphore_delete(uint32_t semId);
/**
 * \brief	Create a mutex.
 * @param[out] mutex_id	memory to return the mutex identifier.
 * @param[in] is_prio_ceiling	boolean to create the mutex with or without
 * 			priority ceiling.
 * @param[out] prio_type the type of priority with which the mutex is created.
 * @param[in] prio_ceiling the priority ceiling of the mutex.
 */
void edroombp_mutex_create(uint32_t *mutex_id, bool_t is_prio_ceiling,
									uint32_t * prio_type, uint32_t prio_ceiling);

/*				PR_IRQMANAGER FUNCTIONALITY			*/
/**
 * \brief	disable all irqs.
 */
void edroombp_disable_irqs(void);
/**
 * \brief	enable all irqs.
 */
void edroombp_enable_irqs(void);
/**
 * \brief	install a handler for an irq.
 * @param[in] handler	the pointer to the handler.
 * @param[in] vector_num	the irq number.
 */
void edroombp_install_handler(void * handler, uint8_t vector_num);
/**
 * \brief	deinstall a handler for a given IRQ.
 * @param[in] vector_num	the irq number.
 */
void edroombp_deinstall_handler(uint8_t vector_num);
/**
 * \brief	disable a single irq.
 * @param[in] irq_num	the irq number.
 */
void edroombp_disable_irq(uint8_t irq_num);
/**
 * \brief	enable a single irq.
 * @param[in] irq_num	the irq number.
 */
void edroombp_enable_irq(uint8_t irq_num);

/*				IRQ_EVENT FUNCTIONALITY				*/
/**
 * \brief	release an event
 * @param[in] caller_task_id	the identifier of the caller task.
 * @param[in] irq_event	the irq event number.
 */
void edroombp_event_signal(uint32_t caller_task_id, uint32_t irq_event);
/**
 * \brief	catch an event.
 * @param[out] caller_task_id	the identifier of the caller.(probably removable)
 * @param[in] irq_event	the irq event number.
 */
void edroombp_event_catch(uint32_t * caller_task_id, uint32_t irq_event);
/**
 * \brief	try to catch an event during a given number of clock ticks.
 * @param[out] caller_task_id	the identifier of the caller task.
 * @param[in] irq_event	the irq event number.
 * @param[in] ticks	the maximum number of ticks to wait.
 * @return true or false.
 */
bool_t edroombp_event_timed_catch(uint32_t * caller_task_id,
											uint32_t irq_event, uint32_t ticks);
/**
 * \brief	try to catch an event
 * @param caller_task_id	the identifier of the caller task.
 * @param irq_event	irq_event	the irq event number.
 * @return true or false.
 */
bool_t edroombp_event_try_catch(uint32_t * caller_task_id, uint32_t irq_event);

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* EDROOMBP_4_8_IMPR_WRAPPER_H_ */
