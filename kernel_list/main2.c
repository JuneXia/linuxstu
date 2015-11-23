#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

struct ElemType
{
	int num;
	char *ptr;
	LIST_ENTRY(ElemType) entries;
};

LIST_HEAD(List, ElemType);

static struct List gList;

struct ElemType* LIST_END(struct List *list)
{
	struct ElemType *recv = NULL;
	struct ElemType *elem = NULL;
	LIST_FOREACH(elem, list, entries)
	{
		if (elem && elem->entries.le_next == NULL)
		{
			recv = elem;
		}
	}
	return recv;
}

//void LIST_INSERT_TAIL(struct List *list, struct ElemType *elem, LIST_ENTRY name)
void LIST_INSERT_TAIL(struct List *list, struct ElemType *elem)
{
	struct ElemType *tail = LIST_END(list);
	if (tail)
	{
		LIST_INSERT_AFTER(tail, elem, entries);
	}
	else
	{
		LIST_INSERT_HEAD(list, elem, entries);
	}
}

int main()
{
	LIST_INIT(&gList);

	struct ElemType *elem1 = (struct ElemType *)malloc(sizeof(struct ElemType));
	struct ElemType *elem2 = (struct ElemType *)malloc(sizeof(struct ElemType));
	struct ElemType *elem3 = (struct ElemType *)malloc(sizeof(struct ElemType));
	elem1->num = 11;
	elem2->num = 22;
	elem3->num = 33;

	// insert in the head
	printf("LIST_EMPTY = %d\n", LIST_EMPTY(&gList));
	LIST_INSERT_HEAD(&gList, elem1, entries);
	printf("LIST_EMPTY = %d\n", LIST_EMPTY(&gList));
	LIST_INSERT_HEAD(&gList, elem2, entries);
	printf("LIST_EMPTY = %d\n", LIST_EMPTY(&gList));
	LIST_INSERT_HEAD(&gList, elem3, entries);
	printf("LIST_EMPTY = %d\n", LIST_EMPTY(&gList));

	// insert in the tail 
	//LIST_INSERT_TAIL(&gList, elem1);
	//LIST_INSERT_TAIL(&gList, elem2);
	//LIST_INSERT_TAIL(&gList, elem3);

	struct ElemType *elem;
	for (elem = gList.lh_first; elem; elem = elem->entries.le_next)
	{
		printf("using for, num = %d\n", elem->num);
		if (elem->num == 22)
		{
			//LIST_REMOVE(elem, entries);
			//free(elem);
			//elem->num = 99;
		}
	}

	LIST_FOREACH(elem, &gList, entries)
	{
		printf("using LIST_FOREACH, num = %d\n", elem->num);
		if (elem->num == 22)
		{
			LIST_REMOVE(elem, entries);
			free(elem);
			break;
		}
	}

	elem3->num = 44;
	LIST_FOREACH(elem, &gList, entries)
	{
		printf("using LIST_FOREACH 2, num = %d\n", elem->num);
	}

	return 0;
}
