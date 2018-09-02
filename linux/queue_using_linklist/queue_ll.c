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
				   struct list_head *this_head)
{
  struct msg *ms;
  //	struct ntb_queue_entry *entry;
  //	unsigned long flags;

  //	spin_lock_irqsave(lock, flags);
  if (list_empty(this_head)) {
    pr_err ("[%s] Empty List! L=%d \n", __func__, __LINE__);
    ms = NULL;
    goto out;
  }
  ms = list_first_entry(this_head, struct msg, m_list_head);
  if (NULL != ms)
    list_del(&ms->m_list_head);

  //out:
  //	spin_unlock_irqrestore(lock, flags);

  return ms;
 out:
  return NULL; 
}


static struct msg* ntb_lib_deque( struct list_head *msg_list)
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

int ntb_lib_enque(struct list_head *new_msg_list_head,
		  struct list_head *msg_list_head)
{
  ntb_lib_list_add((new_msg_list_head), (msg_list_head));
  return 0;
}

//void send_msg(ntb, pidx, msg) 
//void ntb_lib_exch_send_sync(int ntb_dev, int pidx, int len, int *data)
int ntb_lib_exch_send_sync(void *_ptr, void *data, int len) { 
  int i, j=0; 
  int *iptr = 0;
  struct msg *start = NULL, *temp = NULL;
  
  list_for_each_entry_safe(start, temp,  &msg_list.m_list_head, m_list_head) {
    for (i=0,j=0; i<len-1; i++, j+=4) {
      iptr = (start->data)+j;
      pr_err ("[%s] Enqueue Data = [%d] L=%d\n", __func__, *iptr, __LINE__);
    }
  }
	
  /*
    status = 0; 

    cmd = spad_read(ntb, pidx, CMD_SPAD = 0); 

    read_lock(cmd_lock); 

    if (get_seq(cmd_cache) != get_ack(cmd)) 
    status = -EAGAIN; 

    read_unlock(cmd_lock); 

    if (status) 
    return status; 

    peer_spad_write(ntb, pidx, 1, to_u32(msg->data[3])); 
    peer_spad_write(ntb, pidx, 2, to_u32(msg->data[3 + 4])); 
    ... 

    write_lock(cmd_lock); 
    cmd_cache = seq_invert_clear_data(cmd_cache) | three_bytes_to_u32(msg->data); 
    peer_spad_write(ntb, pidx, CMD_SPAD, cmd_cache); 
    write_unlock(cmd_lock); 

    peer_db_set(CMD_DB); 
  */
  return 0; 
} 

void at_deliver_work(void *_ptr, void *data, int len) { 
  struct msg *new_msg = (struct msg *)_ptr;
  int rc = 1;
  //  for_each_port_index(pidx) { 
  //    for_each_msg_safe(ntb, pidx, msg) { 
  //      spin_lock(queue(ntb, pidx).lock); 
  //      dequeue(ntb, pidx, msg); 
  //      spin_unlock(queue(ntb, pidx).lock); 

  rc = ntb_lib_exch_send_sync(new_msg, data, len); 
  //      if (!rc) //{ 
  //	kfree(data); 
  //    free(nn->head);
  //      } else { 
  //	spin_lock(queue(ntb, pidx).lock); 
  //	enqueue(ntb, pidx, msg); 
  //	spin_unlock(queue(ntb, pidx).lock); 
  //      } 
  //   } 
  //  } 

  //  if (queues aren't empty) 
  //        schedule_delayed_work(deliver_work, CMD_DELAY); 
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
  at_deliver_work(new_msg, new_msg->data, 4);

  return 0;
}

static int __init atclib_init(void)
{
  int data[3] = {15, 25, 35};
  int data2[3] = {45, 55, 65};
  struct msg *ms = NULL;
  int *iptr, i, j;  
  pr_debug("[%s] atclib init called. L=%d !\n", __func__, __LINE__);

  INIT_LIST_HEAD(&msg_list.m_list_head);
	
  /* Enque Messages */
  pr_debug("[%s] : atclib Enque data Started. L=%d!\n", __func__, __LINE__);
  post_msg(data, 3);
  post_msg(data2, 3);

  /* Deque Messages */
  pr_debug("[%s] : atclib Dequeue data Started. L=%d !\n", __func__, __LINE__);
  while ((ms = ntb_lib_deque(&msg_list.m_list_head))) {
    for (i=0,j=0; i<3; i++, j+=4) {
      iptr = (ms->data)+j;
      pr_err ("[%s] Dequeue Data = [%d] L=%d \n",  __func__, *iptr, __LINE__);
    }
    if(ms->data) {
	    ms->data = NULL;
    	    kfree(ms->data);
	    kfree(ms);
    }
    ms = NULL;
  }
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
