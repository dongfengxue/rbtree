#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"
#include "string.h"

int main(){
    dedup_root=create_rbtree();  //hash为key
    if(dedup_root == NULL)
    {
        fprintf(stderr,"malloc tree failed\n");
        return -1;
    }

    char tname[20];
    strcpy(tname,"webmail_line_10.txt");


    char buffer[200];
    //double time;
     float time;
    int devno, bcount, flags;
    long int blkno;
    double delay;
    int ppn=0;
    char hash[33];
    struct data_node *data_tmp=NULL;
    Node *tree_node_tmp=NULL;

   // FILE *fp = fopen("webmail.1", "r");
    FILE *fp = fopen("cheetah.01", "r");
   // FILE *fp = fopen("webmail_line_10", "r");
    if(fp==NULL)
        printf("open error\n");
    int laddr_ref=0;
    while(fgets(buffer, 200, fp)) {
        sscanf(buffer, "%f %ld %d %d %s\n", &time, &blkno, &bcount, &flags, hash);

        time /= 1000;
        bcount = ((blkno + bcount - 1) / 4 - (blkno) / 4 + 1) * 4;
        blkno /= 4;
        blkno *= 4;

        tree_node_tmp=iterative_rbtree_search_hash(dedup_root, hash);  //hash 为key的tree
        if(tree_node_tmp!=NULL) {             //不为空表示，有相同的hash已经在节点中
            if(search_laddr_in_node(tree_node_tmp->key, blkno))  //逻辑地址一样，找到返回4
                laddr_ref++;
            else {
                tree_node_tmp->key->ref++;                        //hash相同，逻辑地址不同，ref++
                insert_laddr_in_node(tree_node_tmp->key, blkno);
            }
        }
      //  printf("%lld\n",time);
        data_tmp = create_data_node(ppn,blkno, 1, hash);
     //   printf("hash:%s   ",data_tmp->md);
        insert_rbtree_hash(dedup_root, data_tmp);
        ppn++;
    }

    ref_1_num=ref_2_num=ref_3_num=ref_4_num=ref_5_num=ref_high_num=ref_num=0;
    inorder_rbtree(dedup_root);
    printf("ref_1_num=%d,ref_2_num=%d,ref_3_num=%d\n",ref_1_num,ref_2_num,ref_3_num);
    printf("ref_4_num=%d,ref_5_num=%d,ref_high_num=%d\n",ref_4_num,ref_5_num,ref_high_num);
    ref_num=ref_1_num+ref_2_num*2+ref_3_num*3+ref_4_num*4+ref_5_num*5+ref_high_num*6;
    float ref_1_pec=ref_1_num/ref_num;
    float ref_2_pec=ref_2_num/ref_num;
    float ref_3_pec=ref_3_num/ref_num;
    float ref_4_pec=ref_4_num/ref_num;
    float ref_5_pec=ref_5_num/ref_num;
    float ref_high_pec=ref_high_num/ref_num;
    printf("ref_1_pec=%f,ref_2_pec=%f,ref_3_pec=%f\n",ref_1_pec,ref_2_pec,ref_3_pec);
    printf("ref_4_pec=%f,ref_5_pec=%f,ref_high_pec=%f\n",ref_4_pec,ref_5_pec,ref_high_pec);
    printf("ref_num=%d\n",ref_num);
    printf("laddr_ref=%d\n",laddr_ref);

    return 0;
}
