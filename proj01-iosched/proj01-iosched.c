
/*
 * Team #8
 * - Jacob Cray
 * - Rodney Keeling
 * - Torben Rasmussen
 * - Helen Shin
 */

/*
 * elevator noop
 */
#include <linux/blkdev.h>
#include <linux/elevator.h>
#include <linux/bio.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/init.h>

struct proj01_data {
	struct list_head queue;
};

static void proj01_merged_requests(struct request_queue *q, struct request *rq,
				 struct request *next)
{
	list_del_init(&next->queuelist);
}

static int proj01_dispatch(struct request_queue *q, int force)
{
	struct proj01_data *nd = q->elevator->elevator_data;

	if (!list_empty(&nd->queue)) {
		struct request *rq;
		rq = list_entry(nd->queue.next, struct request, queuelist);
		list_del_init(&rq->queuelist);
		elv_dispatch_sort(q, rq);
		return 1;
	}
	return 0;
}

static void proj01_add_request(struct request_queue *q, struct request *rq)
{
	struct proj01_data *nd = q->elevator->elevator_data;

	list_add_tail(&rq->queuelist, &nd->queue);
}

static int proj01_queue_empty(struct request_queue *q)
{
	struct proj01_data *nd = q->elevator->elevator_data;

	return list_empty(&nd->queue);
}

static struct request *
proj01_former_request(struct request_queue *q, struct request *rq)
{
	struct proj01_data *nd = q->elevator->elevator_data;

	if (rq->queuelist.prev == &nd->queue)
		return NULL;
	return list_entry(rq->queuelist.prev, struct request, queuelist);
}

static struct request *
proj01_latter_request(struct request_queue *q, struct request *rq)
{
	struct proj01_data *nd = q->elevator->elevator_data;

	if (rq->queuelist.next == &nd->queue)
		return NULL;
	return list_entry(rq->queuelist.next, struct request, queuelist);
}

static void *proj01_init_queue(struct request_queue *q)
{
	struct proj01_data *nd;

	nd = kmalloc_node(sizeof(*nd), GFP_KERNEL, q->node);
	if (!nd)
		return NULL;
	INIT_LIST_HEAD(&nd->queue);
	return nd;
}

static void proj01_exit_queue(struct elevator_queue *e)
{
	struct proj01_data *nd = e->elevator_data;

	BUG_ON(!list_empty(&nd->queue));
	kfree(nd);
}

static struct elevator_type elevator_proj01 = {
	.ops = {
		.elevator_merge_req_fn		= proj01_merged_requests,
		.elevator_dispatch_fn		= proj01_dispatch,
		.elevator_add_req_fn		= proj01_add_request,
		.elevator_queue_empty_fn	= proj01_queue_empty,
		.elevator_former_req_fn		= proj01_former_request,
		.elevator_latter_req_fn		= proj01_latter_request,
		.elevator_init_fn		= proj01_init_queue,
		.elevator_exit_fn		= proj01_exit_queue,
	},
	.elevator_name = "team08",
	.elevator_owner = THIS_MODULE,
};

static int __init proj01_init(void)
{
	elv_register(&elevator_proj01);

	return 0;
}

static void __exit proj01_exit(void)
{
	elv_unregister(&elevator_proj01);
}

module_init(proj01_init);
module_exit(proj01_exit);


MODULE_AUTHOR("Jacob Cray, Rodney Keeling, Torben Rasmussen, Helen Shin");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("proj01 IO scheduler");
