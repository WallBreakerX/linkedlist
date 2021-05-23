/*
******************************************************************************
* Copyright (c) 2021—2021 Tinhow Zeng. All rights reserved.
******************************************************************************
* email           : a84987336@outlook.com
* Author          : Tinhow Zeng
* File Name       : linkedlist.h
* Version         : V1.00.00_20210426
* date            : 2021.4.26
* Description     : Dynamic memory management solution

* History         :
        <author>        <version>           <time>      <desc>
        Tinhow Zeng     V1.00.00_20210426   2021.4.26   create
        Tinhow Zeng     V1.00.00_20210523   2021.5.23   optimization
******************************************************************************
* Copyright (c) 2021—2021 Tinhow Zeng. All rights reserved.
******************************************************************************
*/

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_


//#define DEBUG

#define LIST_OK               0 // 成功 OK
#define LIST_ROOT_IS_NULL    -1 // 根为空 root is null
#define LIST_KEY_EXIST       -2 // 键已经存在 key already exist
#define LIST_KEY_NOTEXIST    -3 // 键不存在   key doesn't exist


/*
        功能feature：  
                创建链表根节点 Ceate linkedlist root
    
        输入input：  
                空void
    
        返回return：  
                链表根节点指针 address of linkedlist root
*/
void* linkedlist_create(void);

/*
        功能feature：  
                添加新节点到链表尾 add new node to linkedlist's tail
        输入input：  
                ROOT* root      链表根节点      address of linkedlist root
                char* key_in    键指针          address of key
                void* value_in  数据指针        address of value

        返回return:   
                LIST_OK         成功 OK
                其他other       见上方宏定义 see definiton
*/
int linkedlist_add(void* root, char* key_in, void* value_in);

/*
        功能feature：  
                获取指定key的value指针地址 get specified value of key's address

        输入input：  
                void* root      链表根节点 address of linkedlist root
                char* key_in    键指针     address of specified key

        输出output:   
                void** value_out    符合要求的key的value指针的地址 address of value

        返回return：  
                LIST_OK     成功
                其他        见上方宏定义
*/
int linkedlist_get(void* root, char* key_in, void** value_out);

/*
        功能feature：  删除指定key节点 delete specified key

        输入input：  
                void* root      链表根节点 address of linkedlist root
                char* key_in    键指针     address of specified key

        返回return：  
                LIST_OK     成功
                其他        见上方宏定义
*/
int linkedlist_del(void* root, char* key_in);

/*
        功能feature：  遍历链表，顺序打印出每个节点的地址与key traverse whole linkedlist(only read form node)

        输入input：  
                void* root      链表根节点 address of linkedlist root

        返回return：  
                LIST_OK     成功 OK
                其他        见上方宏定义
*/
int linkedlist_traverse(void* root);

/*
        功能feature:
                摧毁链表 destroy whole linkedlist

        输入input:
                ROOT* root  链表根节点地址 address's address of linkedlist root

        返回return：  
                LIST_OK     成功 OK
                其他        见上方宏定义
*/
int linkedlist_destroy(void** root);

#endif