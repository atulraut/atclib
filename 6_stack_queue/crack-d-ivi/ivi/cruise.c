/* Locking, FIFO, Interrupt Context : Cruise :
  */

/* This is a driver for such a device
   the device has an bidirectional FIFOs for communicaiton
   between control host and the device * write a driver for user to use write/read function * to write message to the FIFO and read the message * from device. * Assuming here isthe FIFO base address: * * FIFO for message from host to device *   *  data input 0xa0001000 *   *  fifo status: 0xa0001004, bit0: fifo is full, bit1, fifo is empty *   *  fifo interrupt enable: 0xa0001008 *   *  fifo interrupt disable: 0x000100c *   *  fifo interrup mask: 0xa0001010 * * FIFO for message from device to host *   * 0xa0002000 *   *  fifo status: 0xa0002004, bit0: fifo is full, bit1, fifo is empty *   *  fifo interrupt enable: 0xa0002008 *   *  fifo interrupt disable: 0x000200c *   *  fifo interrup mask: 0xa0002010 * message header: * * u8 length * * u8 data[0] * max data payload length is 4 * either the whole message is got pushed into fifo, otherwise * no message will be pushed to the fifo */

struct job {
  int data;
}
  ;
struct queue {
  splinlock_t my_lock;
  cond_t wait_room;
  cont_t wait_data;
  unsigned int size;
  unsigned int head; // fron
  unsigned int tail; // tail
  struct job **queue;
};

int queue_init(struct queue *const q, const unsigned int slots) {
  int errorno;
  if(!q || slots < 1U)
    return errorno = EIVAL;
  q->queue = (struct job**)kmalloc(sizeof(struct job *) * (size_t)(slota+1));
  if (!q->queue)
    return errorno=ENOMEM;

  q->size = sloats + 1U;
  q->head = 0U;
  q->tail = 0U;
  splinlock_init(&q->mylock);
  cond_init(&q->wait_room, NULL);
  cond_init(&q->wait_data, NULL);
  return 0;
}

// Dequeu ops
sturct job* queue_get(struct queue *const q) {
  struct job *j;
  unsigned int flag;
  spinlock_irq_save(q->my_lock, flag);
  while (q->head == q->tail) {
     // waiting for dat
     cont_wait(&q->wait_data);
  }
  j = q->queue[q->tail+1];
  q->queue[q->tail] = NULL;
  q->tail = (q->tail + 1U) % q->size;
  cond_signal(&q->wait_room);
  splinlock_irq_restore(q->my_lock);
  return j;
}

// Enque Ops
void queque_put(struct quequ *const q, struct job *const j) {
  unsigned int flag;
  spinlock_irq_save(q->my_lock, flag);
  while (q->head + 1U) % q->size == q->tail)
  cont_wait(&q->wait_room);
  q->head = (q->head + 1U) % q->size;
  q->queue[q->head] = j;
  cond_signal(&q->wait_data);
  splinlock_irq_restore(q->my_lock);
 }

/* interrupt handler */
static irqreturn_t device_driver_irq(int irq, void *data) {
   /* read messages from FIFO */

}

static ssize_t device_driver_write_iter(struct kiocb *iocb, struct iov_iter *from){
  struct file *filp = iocb->ki_filp;
  size_t len = iov_iter_count(from);
  loff_t offset = iocb->ki_pos;
  /** copy from iter:   * bool copy_from_iter_full(void *addr, size_t bytes, struct iov_iter *i);   */
																			        
  /* implement writing message to FIFO */
  struct queue *q = kmalloc(sizeof(struct queue));
  struct job *j = kmalloc(sizeof(int) * len;
			  j->data = *(add+len); queue_put(q, j);
			  }

  static ssize_t device_driver_read_iter(struct kiocb *iocb, struct iov_iter *to){  struct file *filp = iocb->ki_filp;  size_t len = iov_iter_count(to);  loff_t offset = iocb->ki_pos;
										    /*   * copy to iter:   * size_t copy_to_iter(const void *addr, size_t bytes, struct iov_iter *i);   */
										    /* implement reading messages from what's got from fifo */}
  static int device_driver_open(struct inode *inode, struct file *filp){  /* allocate resources to accept FIFO messages */}
  static int device_driver_release(struct inode *inode, struct file *filp){  /* release FIFO related resources */}
  static const struct file_operations device_driver_fops = {        .owner          = THIS_MODULE,        .open = device_driver_open,        .release = device_driver_release,  .write_iter = device_driver_write_iter,  .read_iter = device_driver_read_iter,};

  /* Ignorinag module probing implementation */

  /* DO NOT COPY to Candidate *//* Expect to implement a queue, when interrupt is raised, read messages from FIFO and * enqueue. read_iter() function will read message from enqueued message from device. * write_iter() function will write message to FIFO, candidate will need to consider when * FIFO is full.
*/
