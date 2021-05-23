/*
******************************************************************************
* Copyright (c) 2021—2021 Tinhow Zeng. All rights reserved.
******************************************************************************
* email           : a84987336@outlook.com
* Author          : Tinhow Zeng
* File Name       : linkedlist.c
* Version         : V1.00.00_20210426
* date            : 2021.4.26
* Description     : Dynamic memory management solution

* History         :
    <author>        <version>           <time>      <desc>
    Tinhow Zeng     V1.00.00_20210426   2021.4.26   create
******************************************************************************
* Copyright (c) 2021—2021 Tinhow Zeng. All rights reserved.
******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "linkedlist.h"

typedef struct linkedlist_node
{
    char* key;
    void* value;
    struct linkedlist_node* next;
}NODE;

typedef struct linkedlist_root
{
    int listlen;
    pthread_mutex_t *lock;
    struct linkedlist_node* node_root;
}ROOT;

NODE* create_node(char* key, void* value){
    NODE* node = (NODE*)malloc(sizeof(NODE));
    #ifdef DEBUG
    printf("> create node:     %d\n", node);
    #endif
    node->key = key;
    node->value = value;
    node->next = NULL;
    
    return node;
}

void free_node(NODE* node){
    if (node == NULL)
        return;
    #ifdef DEBUG
    printf("<<< free:%d\n", node);
    #endif
    free(node->key);
    free(node->value);
    free(node);
    node = NULL;
}
void free_root(ROOT* root){
    if (root == NULL)
        return;
    #ifdef DEBUG
    printf("<<< free:%d\n", root);
    #endif
    free(root);
}

void* linkedlist_create(void){
    ROOT* Root = (ROOT*)malloc(sizeof(ROOT));
    Root->listlen = 0;
    Root->lock = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(Root->lock, NULL);
    Root->node_root = NULL;
    
    return (void*)Root;
}

int linkedlist_add(void* root, char* key_in, void* value_in){
    // lock
    if (root == NULL){
        return LIST_ROOT_IS_NULL;
    }
    ROOT* Root = root;
    pthread_mutex_lock(Root->lock);
    if ((Root->listlen == 0) && (Root->node_root == NULL)){ // 如果list为空，直接添加到node_root，然后退出
        NODE* new_node = create_node(key_in, value_in);
        Root->node_root = new_node;
        Root->listlen += 1;

        pthread_mutex_unlock(Root->lock);
        return LIST_OK;
    }
    NODE* node = Root->node_root;
    NODE* lastnode = node;
    while(1){
        if (node == NULL){
            break;
        }
        if (strcmp(node->key, key_in) == 0){ // 存在相同的key，退出
            pthread_mutex_unlock(Root->lock);
            return LIST_KEY_EXIST;
        }
        lastnode = node;    // 保存当前node
        node = node->next;  // 当前node后移
    }
    lastnode->next = create_node(key_in, value_in);
    Root->listlen += 1;

    pthread_mutex_unlock(Root->lock);
    return LIST_OK;
}

int linkedlist_get(void* root, char* key_in, void** value_out){
    if (root == NULL){
        return LIST_ROOT_IS_NULL;
    }
    ROOT* Root = root;
    pthread_mutex_lock(Root->lock);
    NODE* node = Root->node_root;
    while(1){
        if (node == NULL){
            break;
        }
        else {
            #ifdef DEBUG
            printf("|||   node addr:      %d, key: %s, vlaue: %s\n", node, node->key, node->value);
            #endif
            if (strcmp(node->key, key_in) == 0){
                (*value_out) = node->value;
                pthread_mutex_unlock(Root->lock);
                return LIST_OK;
            }
            node = node->next;
        }
    }

    pthread_mutex_unlock(Root->lock);
    return LIST_KEY_NOTEXIST;
}

int linkedlist_traverse(void* root){
    // lock
    if (root == NULL){
        return LIST_ROOT_IS_NULL;
    }
    ROOT* Root = root;
    pthread_mutex_lock(Root->lock);
    NODE* node = Root->node_root;
    while(1){
        if (node == NULL){
            break;
        }
        else {
            printf(">>> node addr: %d, key: %s\n", node, node->key);
            node = node->next;
        }
    }
    pthread_mutex_unlock(Root->lock);
    printf(">>>>>> traverse over <<<<<<\n");
    return LIST_OK;

}

int linkedlist_destroy(void** root){
    // lock
    if (root == NULL){
        // unlock
        return LIST_ROOT_IS_NULL;
    }

    ROOT** Root = (ROOT**)root;
    pthread_mutex_lock((*Root)->lock);
    NODE* node = (*Root)->node_root;
    
    while(1){
        if (node == NULL){
            break;
        }
        else{
            NODE* next = node->next;
            free_node(node);
            node = next;
        }
    }
    pthread_mutex_t *list_lock = (*Root)->lock;
    free_root((*Root));
    (*Root) = NULL;
    pthread_mutex_unlock(list_lock);
    pthread_mutex_destroy(list_lock);
    free(list_lock);

    return LIST_OK;
}

int linkedlist_del(void* root, char* key_in){
    // lock
    if (root == NULL){
        // unlock
        return LIST_ROOT_IS_NULL;
    }
    ROOT* Root = root;
    pthread_mutex_lock(Root->lock);

    
    NODE* node = Root->node_root;
    NODE* lastnode = NULL;
    while(1){
        if (node == NULL){
            break;
        }
        else {
            if (strcmp(node->key, key_in) == 0){
                #ifdef DEBUG
                printf("\n>>> DEL node: %d, key: %s\n\n", node, node->key);
                #endif
                if (node == Root->node_root){ // 当删除的Node为第一个Node时
                    Root->node_root = node->next;
                    Root->listlen -= 1;
                    free_node(node);
                }
                else{ // 当删除的Node在第一个Node之后
                    lastnode->next = node->next;
                    Root->listlen -= 1;
                    free_node(node);
                }
                pthread_mutex_unlock(Root->lock);
                return LIST_OK;
            }
            lastnode = node;
            node = node->next;
        }
    }

    pthread_mutex_unlock(Root->lock);
    return LIST_KEY_NOTEXIST;
}
