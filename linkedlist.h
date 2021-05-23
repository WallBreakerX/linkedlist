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
******************************************************************************
* Copyright (c) 2021—2021 Tinhow Zeng. All rights reserved.
******************************************************************************
*/

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_


//#define DEBUG

#define LIST_OK               0 // 成功
#define LIST_ROOT_IS_NULL    -1 // 根为空
#define LIST_KEY_EXIST       -2 // 键已经存在
#define LIST_KEY_NOTEXIST    -3 // 键不存在


/*
    功能：  创建链表根节点
    
    输入：  空
    
    返回：  链表根节点指针
*/
void* linkedlist_create(void);

/*
    功能：  添加新节点到链表
            从链表尾部添加

    输入：  ROOT* root      链表根节点
            char* key_in    键指针
            void* value_in  数据指针
            以上输入需要由使用者自行申请空间后再传入。

    返回：  LIST_OK     成功
            其他        见上方宏定义
*/
int linkedlist_add(void* root, char* key_in, void* value_in);

/*
    功能：  获取指定key的value指针地址

    输入：  ROOT* root      链表根节点
            char* key_in        键指针
            void** value_out    空value指针的地址 

    输出:   void** value_out    符合要求的key的value指针的地址 

    返回：  LIST_OK     成功
            其他        见上方宏定义
*/
int linkedlist_get(void* root, char* key_in, void** value_out);

/*
    功能：  删除指定key节点

    输入：  ROOT* root      链表根节点
            char* key_in        键指针

    返回：  LIST_OK     成功
            其他        见上方宏定义
*/
int linkedlist_del(void* root, char* key_in);

/*
    功能：  遍历链表，顺序打印出每个节点的地址与key

    输入：  ROOT* root      链表根节点

    返回：  LIST_OK     成功
            其他        见上方宏定义
*/
int linkedlist_traverse(void* root);

/*
    功能：  摧毁链表

    输入：  ROOT* root  链表根节点地址

    返回：  LIST_OK     成功
            其他        见上方宏定义
*/
int linkedlist_destroy(void** root);

#endif