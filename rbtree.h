#ifndef __RBTREE_H__
#define __RBTREE_H__

enum rb_color
{
    RB_BLACK,
    RB_RED,
};
struct l_addr{
    long long laddr;
    struct l_addr *next;   //logical address
};
struct data_node{
    int ref;
    void *hash;
    long long paddr;   //ÎïÀíµØÖ·
    struct l_addr *head_laddr;
}data_node;
typedef struct rbtree_node
{
    struct rbtree_node* parent;
    struct rbtree_node* left;
    struct rbtree_node* right;
    enum rb_color color;
    void *key;
    //void *data;
   // int ref;
    struct data_node* data;
    //struct l_addr* addr;
}rbtree_node;


typedef int (*rbtree_cmp_fn_t)(void *key_a,  void *key_b);
typedef struct rbtree
{
    struct rbtree_node* root;
    rbtree_cmp_fn_t compare; 
}rbtree;

struct rbtree* rbtree_init(rbtree_cmp_fn_t fn);
int  rbtree_insert(struct rbtree *tree, struct rbtree_node *node,void *key,void* data,int flag);
//int  rbtree_insert(struct rbtree *tree, void *key,void* data);
struct rbtree_node* rbtree_creat_datanode(void *laddr,long long paddr,void* hash);
//struct rbtree_node* rbtree_createnode(void *key, void* data);
void*  rbtree_lookup(struct rbtree* tree,void *key);
int  rbtree_remove(struct rbtree* tree,void *key);
#endif
