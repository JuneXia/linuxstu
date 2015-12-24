#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
struct ElemType2
{
	int num;
	char *ptr;
	LIST_ENTRY(ElemType2) entries;
};

LIST_HEAD(List2, ElemType2);

static struct List2 gList2;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
	LIST_INIT(&gList2);

	struct ElemType *elem1 = (struct ElemType *)malloc(sizeof(struct ElemType));
	struct ElemType *elem2 = (struct ElemType *)malloc(sizeof(struct ElemType));
	struct ElemType *elem3 = (struct ElemType *)malloc(sizeof(struct ElemType));
	elem1->num = 11;
	elem2->num = 22;
	elem3->num = 33;

	struct ElemType2 *elem21 = (struct ElemType2 *)malloc(sizeof(struct ElemType2));
	struct ElemType2 *elem22 = (struct ElemType2 *)malloc(sizeof(struct ElemType2));
	struct ElemType2 *elem23 = (struct ElemType2 *)malloc(sizeof(struct ElemType2));
	elem21->num = 211;
	elem22->num = 222;
	elem23->num = 233;

	// insert in the head
	LIST_INSERT_HEAD(&gList, elem1, entries);
	LIST_INSERT_HEAD(&gList, elem2, entries);
	LIST_INSERT_HEAD(&gList, elem3, entries);

	LIST_INSERT_HEAD(&gList2, elem21, entries);
	LIST_INSERT_HEAD(&gList2, elem22, entries);
	LIST_INSERT_HEAD(&gList2, elem23, entries);

	struct ElemType *element;
	struct ElemType2 *element2;
/*
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
*/
//	elem3->num = 44;

	struct ElemType *ele;
	struct ElemType2 *ele2;


	for (element = gList.lh_first; element; element = element->entries.le_next)
	{
		printf("using for 1, num = %d\n", element->num);
		if (element->num == 22)
		{
			//LIST_REMOVE(element, entries);
			//free(element);
			ele = element;
		}
	}

	for (element2 = gList2.lh_first; element2; element2 = element2->entries.le_next)
	{
		printf("using for 2, num = %d\n", element2->num);
		if (element2->num == 222)
		{
			//LIST_REMOVE(element2, entries);
			//free(element2);
			ele2 = element2;
		}
	}


	LIST_REMOVE(ele, entries);
	LIST_REMOVE(ele2, entries);


	LIST_FOREACH(element, &gList, entries)
	{
		printf("using LIST_FOREACH 1, num = %d\n", element->num);
	}

	LIST_FOREACH(element2, &gList2, entries)
	{
		printf("using LIST_FOREACH 2, num = %d\n", element2->num);
	}

	return 0;
}
