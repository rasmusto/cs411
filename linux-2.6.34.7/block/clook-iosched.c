/*
 * CS 411 Team 08
 * C-Look I/O Scheduler
 * Team members:
 * Jake Cray
 * Torben Rasmussen 
 * Helen Shin
 * Rodney Keeling
*/
/*
 * Changed noop_data to include the read/write head location
 * Changed noop_init to initialize head location to 0
 * Changes that need to be made: Convert all functions to clook_...
 * Modify dispatch function
 * Modify how add requests are handled
 *      Search through list, and insert new link in proper spot. Should be O(n) for search and add.
 * Modify dispatch
 *      Should be O(1), Rob suggested keeping track of current position and setting prev of curr to be dispatched I believe
 *      Use elevator_dispatch_add_tail or something like that instead of elevator_dispatch_sort -- dont care about sector order
 *      Needs to run as quickly as possible
 *      former/latter
 *          former - should return request to be dispatched when acessed from the current arg/node
 *          latter - return next request to handle
 */
/*
 * elevator clook
 */
#include <linux/blkdev.h>
#include <linux/elevator.h>
#include <linux/bio.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/init.h>

struct clook_data {
	struct list_head queue;
    long head_loc; // Location of the head
};

static void noop_merged_requests(struct request_queue *q, struct request *rq,
				 struct request *next)
{
	list_del_init(&next->queuelist);
}

static int noop_dispatch(struct request_queue *q, int force)
{
	struct noop_data *nd = q->elevator->elevator_data;

	if (!list_empty(&nd->queue)) {
		struct request *rq;
		rq = list_entry(nd->queue.next, struct request, queuelist);
		list_del_init(&rq->queuelist);
		elv_dispatch_sort(q, rq);
		return 1;
	}
	return 0;
}

static void noop_add_request(struct request_queue *q, struct request *rq)
{
	struct noop_data *nd = q->elevator->elevator_data;

	list_add_tail(&rq->queuelist, &nd->queue);
}

static int noop_queue_empty(struct request_queue *q)
{
	struct noop_data *nd = q->elevator->elevator_data;

	return list_empty(&nd->queue);
}

static struct request *
noop_former_request(struct request_queue *q, struct request *rq)
{
	struct noop_data *nd = q->elevator->elevator_data;

	if (rq->queuelist.prev == &nd->queue)
		return NULL;
	return list_entry(rq->queuelist.prev, struct request, queuelist);
}

static struct request *
noop_latter_request(struct request_queue *q, struct request *rq)
{
	struct noop_data *nd = q->elevator->elevator_data;

	if (rq->queuelist.next == &nd->queue)
		return NULL;
	return list_entry(rq->queuelist.next, struct request, queuelist);
}

static void *clook_init_queue(struct request_queue *q)
{
	struct clook_data *cd;
	cd = kmalloc_node(sizeof(*cd), GFP_KERNEL, q->node);
	if (!cd)
		return NULL;
	INIT_LIST_HEAD(&cd->queue);
    cd->head_loc = 0; //init head location as 0
	return cd;
}

static void noop_exit_queue(struct elevator_queue *e)
{
	struct noop_data *nd = e->elevator_data;

	BUG_ON(!list_empty(&nd->queue));
	kfree(nd);
}

static struct elevator_type elevator_noop = {
	.ops = {
		.elevator_merge_req_fn		= noop_merged_requests,
		.elevator_dispatch_fn		= noop_dispatch,
		.elevator_add_req_fn		= noop_add_request,
		.elevator_queue_empty_fn	= noop_queue_empty,
		.elevator_former_req_fn		= noop_former_request,
		.elevator_latter_req_fn		= noop_latter_request,
		.elevator_init_fn		= noop_init_queue,
		.elevator_exit_fn		= noop_exit_queue,
	},
	.elevator_name = "noop",
	.elevator_owner = THIS_MODULE,
};

static int __init noop_init(void)
{
	elv_register(&elevator_noop);

	return 0;
}

static void __exit noop_exit(void)
{
	elv_unregister(&elevator_noop);
}

module_init(noop_init);
module_exit(noop_exit);


MODULE_AUTHOR("Jens Axboe");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("No-op IO scheduler");
