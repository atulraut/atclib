/*
 * Aim  : Queue Using Linux LinkList.
 * Date : August-31-2018
 * File : atclib_queue.c
 * Author : Atul Raut
 */

#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/fs.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/export.h>
#include <linux/types.h>
#include <linux/mutex.h>

#define MAX 4

static struct msg msg_list;

struct msg {
  void *data;
  struct list_head m_list_head;
};

/* Use in non-reentrant context (like kernel work-threads) 
   -ntb_lib_exch_send_sync(ntb_dev, pidx, len, data) - send data array of the passed 
   length over the NTB device using the Cross-Iface library. The method can sleep, so 
   can't be used in the atomic context, 
*/ 

static struct msg *ntb_lib_list_rm(/*spinlock_t *lock,*/
				   struct msg *this_head)
{
  if(this_head) {
    list_del(&this_head->m_list_head);
  }
  return this_head;
}

static struct msg* ntb_lib_deque(struct msg *msg_list)
{
  struct msg *ms = ntb_lib_list_rm(msg_list);
  return ms;
}

static void ntb_lib_list_add(/*spinlock_t *lock,*/ struct list_head *new_msg_list_head,
			     struct list_head *msg_list_head)
{
  //	unsigned long flags;

  //	spin_lock_irqsave(lock, flags);
  list_add_tail((new_msg_list_head), (msg_list_head));
  //	spin_unlock_irqrestore(lock, flags);

}

static int ntb_lib_enque(struct list_head *new_msg_list_head,
		  struct list_head *msg_list_head)
{
  ntb_lib_list_add((new_msg_list_head), (msg_list_head));
  return 0;
}

//void send_msg(ntb, pidx, msg) 
//void ntb_lib_exch_send_sync(int ntb_dev, int pidx, int len, int *data)
static int ntb_lib_exch_send_sync(struct msg *start) { 
  int i, j=0; 
  int *iptr = 0;
  //  struct msg *start = NULL;
    //NULL, *temp = NULL;

  if (NULL == start) {
    pr_err ("[%s] Dequeue Data is NULL Returning L=%d\n", __func__,  __LINE__);
    return -1;
  }
    for (i=0,j=0; i<MAX-1; i++, j+=4) {
      iptr = (start->data)+j;
      pr_err ("[%s] Dequeue Data = [%d] L=%d\n", __func__, *iptr, __LINE__);
    }
  return 0; 
} 

//void at_deliver_work(void *_ptr, void *data, int len) {
static void at_deliver_work(void) {   
  //  struct msg *new_msg = (struct msg *)_ptr;
  struct msg *ms = NULL, *temp_addr = NULL;
  int rc = 1;

  
  list_for_each_entry_safe(ms, temp_addr, &msg_list.m_list_head, m_list_head) {
    temp_addr = ntb_lib_deque(ms);
    if (NULL == temp_addr) {
      //pr_debug("[%s]  FIX IT called. L=%d !\n", __func__, __LINE__);
      break;
    } else {
        rc = ntb_lib_exch_send_sync(temp_addr);
        if (rc < 0)
            pr_debug("[%s]  called. L=%d !\n", __func__, __LINE__);
        else {
	  temp_addr->data = NULL;      
	  kfree(temp_addr->data);
	  kfree(temp_addr);
	  temp_addr = NULL;
      }
    }
  }
}

static struct msg* create_node(void *data, int len) {
  struct msg *new_msg;
  new_msg = kmalloc(sizeof(struct msg), GFP_KERNEL);
  new_msg->data = (int *)kmalloc((sizeof(int) * len), GFP_KERNEL);
  new_msg->data = data;
  return new_msg;
}

static struct msg* alloc_and_init_msg(void *data, int len) {
  /* create node and add to linklist. */ 
  struct msg *nn = create_node(data, len);
  if (NULL == nn)
    return NULL;
  else
    return nn;
}

/* post_msg(ntb, pidx, data, size, can_wait, callback) */
static int post_msg(void *data, int len) {
  struct msg *new_msg;
  new_msg = alloc_and_init_msg(data, len);

  ntb_lib_enque(&(new_msg->m_list_head), &(msg_list.m_list_head));

  /* call to schedule_delayed_work(deliver_work, 0); */
  //  at_deliver_work(new_msg, new_msg->data, 4);
  at_deliver_work();
  return 0;
}

static int __init atclib_init(void)
{
  int data[3] = {1, 2, 3};
  int data1[3] = {4, 5, 6};
  int data2[3] = {7, 8, 9};
  int data3[3] = {10, 11, 12};
  int data4[3] = {13, 14, 15};
  int data5[3] = {16, 17, 18};
  int data6[3] = {19, 20, 21};
  struct msg *ms = NULL;
  int *iptr, i, j;  
  pr_debug("[%s] atclib init called. L=%d !\n", __func__, __LINE__);

  INIT_LIST_HEAD(&msg_list.m_list_head);
	
  /* Enque/Deque Messages */
  post_msg(data, 3);
  post_msg(data1, 3);
  post_msg(data2, 3);
  post_msg(data3, 3);
  post_msg(data4, 3);
  post_msg(data5, 3);
  post_msg(data6, 3);
 
  pr_debug("[%s] : End atclib L=%d !\n", __func__, __LINE__);
  return 0;
}

static void atclib_exit(void)
{
  struct msg *ms = NULL;
  struct msg *temp_addr;
  pr_debug("[%s] : Dieing usb atclib! L=%d \n", __func__, __LINE__);
  /* Deque Messages */  
  list_for_each_entry_safe(ms, temp_addr, &msg_list.m_list_head, m_list_head) {
    list_del(&ms->m_list_head);
    kfree(ms);
    ms = NULL;
  }
}

module_init(atclib_init);
module_exit(atclib_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ATUL RAUT");
MODULE_DESCRIPTION("atclib ntb-ll");
