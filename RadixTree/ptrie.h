/*
 * Copyright (c) 2013-2015, Dalian Futures Information Technology Co., Ltd.
 *
 * Xiaoye Meng <mengxiaoye at dce dot com dot cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef PTRIE_INCLUDED
#define PTRIE_INCLUDED

struct value_struct
{
	void *value;
	struct value_struct *next;
};

struct node
{
	char key[300];
	struct value_struct *value_head;
	long value_num;
	int is_real;
	int is_root;
	long child_num;
	struct node *parent;
	struct node **child;
};

struct radix_tree
{
	long size;
	struct node *head;
	pthread_mutex_t lock;
	pthread_rwlock_t rwlock;
};

extern struct radix_tree *radix_new(void);
extern void radix_free(struct radix_tree *rt);
extern void node_free(struct node *p);
extern int getNumberOfMatchingCharacters(char *key, struct node *p);
extern struct node *radix_match(char *prefix, struct node *p, struct node *head);
extern void radix_insert(char *key, struct node *p);
extern struct node *radix_find(char *prefix, struct node *p);
extern void radix_delete(char *key, struct node *p);
extern void visit(char *key, struct node *p);
extern void mergeNodes(struct node *n_parent, struct node *n_child);
extern int radix_contain(char *prefix, struct node *p);
extern void radix_show(struct node *p, int level);
extern void insert_value(char* key, void *value, struct node *p);
extern void radix_block_insert(char *key, const char *sep, struct node *p);

#endif /* PTRIE_INCLUDED */

