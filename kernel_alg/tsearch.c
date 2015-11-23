#include <stdio.h>
#include <search.h>
struct opEntry {
	int num;
	const char *name;
};

static int compare(const void *pa, const void *pb)
{
	const struct opEntry *op1 = pa;
	const struct opEntry *op2 = pb;
	int rc = strncmp(op1->name, op2->name, 32);
	printf("rc = %d\n", rc);
	return rc;
}

void main()
{
	static const struct opEntry oplist[] = {
	{
	.num = 1,
	.name = "aaab",
	},

	{
	.num = 2,
	.name = "aaad",
	},

	};

	int count = sizeof(oplist) / sizeof(struct opEntry);
	printf("count = %d\n", count);
	static void *root = NULL;
	int i;
	for (i = 0; i < count; i++)
	{
		struct opEntry **rc = (struct opEntry **)tsearch(&oplist[i], &root, compare);
		printf("main, rc = %p, (*rc)->name = %s\n", rc, (*rc)->name);
		if (rc == NULL)
			break;
	}
}
