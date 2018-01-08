#include"rbtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include "rbtree.h"

#define SIZE 12
typedef unsigned long long ULL;
void padding ( char ch, int n )
{
    int i;

    for ( i = 0; i < n; i++ )
        putchar ( ch );
}

void print_node ( struct rbtree_node *root, int level )
{

    if ( root == NULL ) 
    {
        padding ( '\t', level );
        puts ( "NIL" );

    }
    else 
    {
        print_node ( root->right, level + 1 );
        padding ( '\t', level );
        if(root->color == RB_BLACK)
        {
            //printf ( "(%llu)\n", *(ULL*)(root->key) );
            printf("(%s) (%d) (%lld) (%lld)\n",(root->key),(root->data->ref),(root->data->paddr),(root->data->head_laddr->laddr));
         //   printf(" (%lld) (%s) (%d) (%lld) (%lld)\n",*(long long*)(root->key),(root->data->hash),(root->data->ref),(root->data->paddr),(root->data->head_laddr->laddr));
        }
        else
        //    printf ( "%llu\n",*(ULL*)(root->key) );
            printf("(%s) %d %lld %lld\n",(root->key),(root->data->ref),(root->data->paddr),(root->data->head_laddr->laddr));
         //    printf(" %lld %s %d %lld %lld\n",*(long long*)(root->key),(root->data->hash),(root->data->ref),(root->data->paddr),(root->data->head_laddr->laddr));
        print_node ( root->left, level + 1 );
    }
}
void print_laddr_node(struct rbtree_node *root,int level)
{
    if ( root == NULL )
    {
        padding ( '\t', level );
        puts ( "NIL" );

    }
    else
    {
        print_laddr_node ( root->right, level + 1 );
        padding ( '\t', level );
        if(root->color == RB_BLACK)
        {
            //printf ( "(%llu)\n", *(ULL*)(root->key) );
            printf(" (%lld) (%s) (%d) (%lld) (%lld)\n",*(long long*)(root->key),(root->data->hash),(root->data->ref),(root->data->paddr),(root->data->head_laddr->laddr));
        }
        else
            //    printf ( "%llu\n",*(ULL*)(root->key) );
            printf(" %lld %s %d %lld %lld\n",*(long long*)(root->key),(root->data->hash),(root->data->ref),(root->data->paddr),(root->data->head_laddr->laddr));
        print_laddr_node ( root->left, level + 1 );
    }
}
void print_paddr_node(struct rbtree_node *root,int level)
{
    if ( root == NULL )
    {
        padding ( '\t', level );
        puts ( "NIL" );

    }
    else
    {
        print_paddr_node ( root->right, level + 1 );
        padding ( '\t', level );
        if(root->color == RB_BLACK)
        {
            //printf ( "(%llu)\n", *(ULL*)(root->key) );
            printf(" (%lld) (%s) (%d) (%lld) (%lld)\n",*(long long*)(root->key),(root->data->hash),(root->data->ref),(root->data->paddr),(root->data->head_laddr->laddr));
        }
        else
            //    printf ( "%llu\n",*(ULL*)(root->key) );
            printf("%lld %s %d %lld %lld\n",*(long long *)(root->key),(root->data->hash),(root->data->ref),(root->data->paddr),(root->data->head_laddr->laddr));
        print_paddr_node ( root->left, level + 1 );
    }
}
void print_tree(struct rbtree* tree)
{
    print_node(tree->root,0);
    printf("-------------------------------------------\n");
}
void print_paddr_tree(struct rbtree * tree){
    print_paddr_node(tree->root,0);
    printf("--------------------------------------------\n");
}
void print_laddr_tree(struct rbtree * tree){
    print_laddr_node(tree->root,0);
    printf("--------------------------------------------\n");
}
int compare(void* key_a,void* key_b)
{
    ULL key_a_real = *(ULL*) (key_a);
    ULL key_b_real = *(ULL*) (key_b);
    if(key_a_real > key_b_real)
    {
        return 1;
    }
    else if(key_a_real == key_b_real)
    {
       return 0;
    }
    else
        return -1;
}


void  process_null_node(struct rbtree_node* node, int nullcount, FILE* stream)
{
        fprintf(stream, "    null%d [shape=hexagon];\n", nullcount);
        fprintf(stream, "    %llu -> null%d;\n",*(ULL*)(node->key), nullcount);
}
void __tree2dot(struct rbtree_node* node,FILE* stream)
{
    static int  null_node_cnt = 0;
    if(node->color == RB_BLACK)
    {
        fprintf(stream,"%llu [shape=box];\n",*(ULL*)(node->key));
    }

    if(node->left)
    {
        
        fprintf(stream,"  %llu -> %llu;\n",*(ULL*)(node->key),*(ULL*)(node->left->key));
        __tree2dot(node->left,stream);
    }
    else
    {
        process_null_node(node,null_node_cnt++,stream);
    }
    if(node->right)
    {
        fprintf(stream,"  %llu -> %llu;\n",*(ULL*)(node->key),*(ULL*)(node->right->key));
        __tree2dot(node->right,stream);
    }
    else
    {
        process_null_node(node,null_node_cnt++,stream);
    }
}
int tree2dot(struct rbtree* tree,char* filename)
{
    assert(tree != NULL && filename != NULL);
    FILE* stream = fopen(filename,"w+");
    if(stream == NULL)
    {
        fprintf(stderr, "open failed \n");
        return -1;
    }

    fprintf(stream,"digraph {\n");
    __tree2dot(tree->root,stream);


    fprintf(stream,"}\n");
    fclose(stream);

    return 0;
    
}
int main()
{
    struct rbtree* hash_tree = rbtree_init(compare);         //hash tree
    struct rbtree* laddr_tree = rbtree_init(compare);   // laddr tree
    struct rbtree* paddr_tree = rbtree_init(compare);      //paddr tree
    int ret_hash = 0;
    int ret_laddr=0;
    int ret_paddr=0;

    if(hash_tree == NULL)
    {
        fprintf(stderr,"malloc tree failed\n");
        return -1;
    }
    if(laddr_tree == NULL){
        fprintf(stderr,"mallloc laddr_tree faild\n");
        return -1;
    }
    if(paddr_tree == NULL){
        fprintf(stderr,"malloc paddr_tree faild\n");
        return -1;
    }

    char str[30];
    strcpy(str,"lhj.txt");
    FILE *fp = fopen(str,"r");
    char line[200];
    //char hash[200];
    char *hash;
    double b_tmie;
    char rw;
    //long long laddr;
    int b_size;
    unsigned long long i = 0;
    ULL  * laddr = malloc(SIZE*sizeof(ULL ));
    if(laddr == NULL)
    {
        fprintf(stderr,"malloc laddr failed\n");
        return -1;
    }

    int flag=0;      //flag=0,hash is the key;flag=1,laddr is the key;flag=2,paddr is the key;
    struct data_node *data_tmp=NULL;
    struct rbtree_node *node =NULL;
    while(fgets(line,200,fp))
    {
        if (strlen(line) < 33)
            continue;
        sscanf(line,"%lf %c %lld %d",&b_tmie,&rw,&laddr[i],&b_size);
        hash=malloc(200*sizeof(char));
        memcpy(hash, line + strlen(line) - 33, 32);
        hash[32] ='\0';
        printf("hash:%s\n",hash);
        printf("addr:%llu\n",laddr[i]);

        data_tmp = rbtree_create_datanode(laddr[i],i,hash);

        struct rbtree_node *hash_node=NULL;
        hash_node = rbtree_create_rbtreenode(data_tmp);          //创建hash node
        ret_hash  = rbtree_insert_hash(hash_tree,hash_node,flag);        //-1 mean alloc node failed,key is the hash
        void *data_hash = rbtree_lookup_hash(hash_tree,hash);
        if(ret_hash == 0)
        {
            printf("%s  hash:%s\n", data_hash, hash);
            assert(strcmp(data_hash,hash)==0);
        }

        struct rbtree_node *laddr_node =NULL;
        laddr_node = rbtree_create_rbtreenode(data_tmp);          //创建laddr node
        ret_laddr = rbtree_insert_laddr(laddr_tree,laddr_node,1);
        void *data_laddr = rbtree_lookup_laddr(laddr_tree,laddr[i]);
        if(ret_laddr == 0)
              assert(*(ULL *)data_laddr == (laddr[i]));

        struct rbtree_node *paddr_node =NULL;
        paddr_node = rbtree_create_rbtreenode(data_tmp);
        ret_paddr = rbtree_insert(paddr_tree,paddr_node,2);
        void *data_paddr = rbtree_lookup_paddr(paddr_tree,&i);
        if(ret_paddr == 0)
            assert(*(ULL *)data_paddr == (i));

        i++;
    }

    print_tree(hash_tree);
    printf("\n");
    char tmp[33];
    strcpy(tmp,"0d63e2242fecfe1ea57e95dc1b3a8f79");
    rbtree_remove(hash_tree,tmp);
    print_tree(hash_tree);

    printf("############################################################\n");
    print_laddr_tree(laddr_tree);
    rbtree_remove_laddr(laddr_tree,49088240);
    print_laddr_tree(laddr_tree);


    printf("############################################################\n");
    print_paddr_tree(paddr_tree);
    rbtree_remove_paddr(paddr_tree,1);
    print_paddr_tree(paddr_tree);


    return 0;
}


