#ifndef __RBTREE_H__
#define __RBTREE_H__

enum rb_color
{
    RB_BLACK,
    RB_RED,
};
struct l_addr{
    unsigned long long laddr;
    struct l_addr *next;   //logical address
};
struct data_node{
    int ref;
    char hash[33];
    unsigned long long paddr;   //ÎïÀíµØÖ·
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
typedef int (*rbtree_cmp_addr)(unsigned long long key_a, unsigned long long key_b);
typedef struct rbtree
{
    struct rbtree_node* root;
    rbtree_cmp_fn_t compare;
}rbtree;

struct rbtree* rbtree_init(rbtree_cmp_fn_t fn);
int  rbtree_insert(struct rbtree *tree, struct rbtree_node *node,int flag);
int  rbtree_insert_hash(struct rbtree *tree, struct rbtree_node *node,int flag);
int  rbtree_insert_laddr(struct rbtree *tree, struct rbtree_node *node,int flag);
//int  rbtree_insert(struct rbtree *tree, void *key,void* data);
struct data_node* rbtree_create_datanode(unsigned long long laddr,unsigned long long paddr,char hash[]);
struct rbtree_node* rbtree_create_rbtreenode(struct data_node* data);
//struct data_node* rbtree_create_datanode(unsigned long long laddr,unsigned long long paddr,void* hash);
//struct rbtree_node* rbtree_createnode(void *key, void* data);
void*  rbtree_lookup(struct rbtree* tree,void *key);
void*  rbtree_lookup_hash(struct rbtree* tree,char key[]);
void*  rbtree_lookup_laddr(struct rbtree* tree,unsigned long long key);
void*  rbtree_lookup_paddr(struct rbtree* tree,void *key);
int  rbtree_remove(struct rbtree* tree,void *key);
int  rbtree_remove_laddr(struct rbtree* tree, unsigned long long key);
int rbtree_remove_paddr(struct rbtree* tree, unsigned long long key);
#endif
