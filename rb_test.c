#include"rbtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

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
            printf("(%s) (%d) (%llu)\n",(root->key),(root->ref),*(ULL *)(root->data));
        }
        else
        //    printf ( "%llu\n",*(ULL*)(root->key) );
            printf("%s (%d) (%llu)\n",(root->key),(root->ref),*(ULL *)(root->data));
        print_node ( root->left, level + 1 );
    }
}

void print_tree(struct rbtree* tree)
{
    print_node(tree->root,0);
    printf("-------------------------------------------\n");
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
    struct rbtree* tree = rbtree_init(compare);
    int ret = 0;
    if(tree == NULL)
    {
        fprintf(stderr,"malloc tree failed\n");
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
        ret  = rbtree_insert(tree,hash,&laddr[i]);        //-1 mean alloc node failed,
        //-2 mean existed node with same key
        void * data = rbtree_lookup(tree,hash);
        if(ret == 0)
        	  assert(data == &laddr[i]);
        i++;
    }
    print_tree(tree);

    return 0;
}


