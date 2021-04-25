#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "linkedlist.h"


int main(void){
    while(1){
        ////////// init //////////
        ROOT* root = linkedlist_init();

        char* data[8];
        char* value[8];
        char key[][8] = {"1A", "2B", "3C", "4D", "5E", "6F", "7G", "8H"};

        for (int i = 0; i < 8; i++){
            data[i] = (char*)malloc(16);
            sprintf(data[i], "%s", key[i]);
            value[i] = (char*)malloc(16);
            sprintf(value[i], "%c%c", key[i][1], key[i][0]);

            ////////// add //////////
            linkedlist_add(root, data[i], (void*)value[i]);
        }

        void* dataout = NULL;
        ////////// get //////////
        int ret = linkedlist_get(root, "8H", &dataout);
        if (ret == LIST_OK){
            printf(">> value: %s\n", (char*)dataout);
        }
        
        ////////// del //////////
        linkedlist_del(root, "1A");
        linkedlist_traverse(root);

        linkedlist_del(root, "8H");
        linkedlist_traverse(root);

        linkedlist_del(root, "3C");
        linkedlist_traverse(root);

        ////////// empty //////////
        linkedlist_empty(&root);
        usleep(100);
        break;
    }


    return 0;
}