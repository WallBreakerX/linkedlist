# 内存管理链表  linkedlist


## 简介
---

- 此链表list提供了一个动态内存管理方案。
    数据在节点中的储存方式为 key : value 形式。


- 本方案不为key, value申请空间，只对key和value进行地址管理与空间释放，
    使用者在添加key和value到list中前需要自行申请malloc空间。

---


## 特点

- 线程安全。
