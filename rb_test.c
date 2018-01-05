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
            printf("(%s) (%d) (%lld)\n",(root->key),(root->data->ref),(root->data->paddr));
           // printf("(%s) (%d) (%llu)\n",(root->key),(root->data->ref),*(ULL *)(root->data->ref));
        }
        else
        //    printf ( "%llu\n",*(ULL*)(root->key) );
            printf("(%s) %d %lld\n",(root->key),(root->data->ref),(root->data->paddr));
         //   printf("%s (%d) (%llu)\n",(root->key),(root->data->ref),*(ULL *)(root->data->ref));
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
            printf("key:(%s) (%d) (%s)\n",(root->key),(root->data->ref),(root->data->hash));
        }
        else
            //    printf ( "%llu\n",*(ULL*)(root->key) );
            printf("key:%s (%d) (%s)\n",(root->key),(root->data->ref),(root->data->hash));
        print_laddr_node ( root->left, level + 1 );
    }
}
void print_tree(struct rbtree* tree)
{
    print_node(tree->root,0);
    printf("-------------------------------------------\n");
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

  //  int i = 0;
    ULL  * array = malloc(SIZE*sizeof(ULL ));
    if(array == NULL)
    {
        fprintf(stderr,"malloc failed\n");
        return -1;
    }
/*
 //   srand(time(NULL));
    char tmp[100]="lhjd";
    char tmp1[100]="opie";
    for(i = 0;i<SIZE;i++)
    {
        array[i] = rand()%1000;
        ret  = rbtree_insert(tree,&array[i],&array[i]);//-1 mean alloc node failed, 
                                                     //-2 mean existed node with same key
        printf("&array[i]:%x\n",&array[i]);
        void * data = rbtree_lookup(tree,&array[i]);
        if(ret == 0)
            assert(data == &array[i]);
    }
    ret=rbtree_insert(tree,tmp,tmp);
    ret=rbtree_insert(tree,tmp1,tmp1);
    print_tree(tree);
    tree2dot(tree,"tree.dot");
*/
    char str[30];
    //scanf("%s",str);
    strcpy(str,"lhj.txt");
    FILE *fp = fopen(str,"r");
    char line[200];
    //char hash[200];
    char *hash;
    double b_tmie;
    char rw;
    //long long laddr;
    int b_size;
    int i = 0;
    ULL  * laddr = malloc(SIZE*sizeof(ULL ));
    if(laddr == NULL)
    {
        fprintf(stderr,"malloc laddr failed\n");
        return -1;
    }
    void * tmp;
    int flag=0;      //flag=0,hash is the key;flag=1,laddr is the key;flag=2,paddr is the key;
    struct rbtree_node *data_tmp=NULL;
    while(fgets(line,200,fp))
    {
        // printf("strlen is %d\n", strlen(line));
        if (strlen(line) < 33)
            continue;
        sscanf(line,"%lf %c %lld %d",&b_tmie,&rw,&laddr[i],&b_size);
        hash=malloc(200*sizeof(char));
        memcpy(hash, line + strlen(line) - 33, 32);
        hash[32] ='\0';
        printf("hash:%s\n",hash);
        printf("addr:%llu\n",laddr[i]);
        //printf("addr:%x\n",&laddr[i]);
       // struct rbtree_node * node = rbtree_createnode(hash,&laddr[i]);
      //  ret_laddr = rbtree_insert(laddr_tree,&laddr[i],hash);
        data_tmp = rbtree_creat_datanode(&laddr[i],i,hash);
        ret_hash  = rbtree_insert(hash_tree,data_tmp,hash,&laddr[i],flag);        //-1 mean alloc node failed,key is the hash
                                                                     //-2 mean existed node with same key
       // printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
       // printf("hash:%s\n",hash);
       // printf("addr:%llu\n",laddr[i]);
       // ret_laddr = rbtree_insert(laddr_tree,&laddr[i],hash);  //laddr is the key

      //  void * data = rbtree_lookup(hash_tree,hash);
     //   if(ret_hash == 0)
     //   	  assert(data == &laddr[i]);
        void *data =rbtree_lookup(laddr_tree,&laddr[i]);
        if(ret_laddr == 0)
   //             assert(data == hash);
        i++;
        tmp=hash;
    }
    print_tree(hash_tree);

    printf("############################################################\n");
  //  print_laddr_tree(laddr_tree);
   // rbtree_remove(hash_tree,tmp);
  //  print_laddr_tree(laddr_tree);
    return 0;
}


