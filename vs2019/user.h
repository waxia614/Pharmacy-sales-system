#ifndef _USER_H_
#define _USER_H_
/*补货提醒数量*/
#define ALERT_COUNT 20

/*临期天数阈值*/
#define EXPIRED_DAYS 30

/*字符串长度*/
#define STR_LEN 256
/*药品结构体*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct _tDrugInfo {
    char a[STR_LEN];               /*药品编号*/
    char b[STR_LEN];             /*药品名称*/
    char c[STR_LEN];    /*生产日期*/
    char d[STR_LEN];  /*保质期*/
    char e[STR_LEN];         /*分类*/
    double f;                 /*进价*/
    double g;                /*售价*/
    int h;                      /*总量*/
    int i;                      /*库存*/
    struct _tDrugInfo* j;        /*下一个节点*/
} DrugInfo, * pDrugInfo;

void first();                                                                                        /*初始界面*/
void zhuce();                                                                                        /*注册界面*/
void denglu();                                                                                       /*登录界面*/

void formatDate(time_t tt, char* buf);                                                               /*将日期转换成文本*/
int isLeapYear(int year);                                                                            /*判断是否闰年*/
int checkDate(int yyyy, int mm, int dd);                                                             /*检测日期（yyyy-mm-dd）*/
void inputDate(char date[]);                                                                         /*输入日期*/
int salesCount(pDrugInfo drug);                                                                      /*计算销量*/         
double salesAmount(pDrugInfo drug);                                                                  /*计算销售额*/
double countProfit(pDrugInfo drug);                                                                  /*计算利润*/
const char* alertDrug(pDrugInfo drug);                                                               /*补货提醒*/
pDrugInfo addDrugInfoNode(pDrugInfo head, pDrugInfo node);                                       /*添加药品节点，返回链表首节点指针*/
pDrugInfo removeDrugInfoNode(pDrugInfo head, pDrugInfo node);                                    /*删除药品节点，返回链表首节点指针*/
pDrugInfo findDrugInfoNodeByID(pDrugInfo head, char* id);                                        /*通过药品编号查找药品节点*/
pDrugInfo findDrugInfoNodeByName(pDrugInfo head, char* name);                                    /*通过药品名称查找药品节点*/
pDrugInfo findDrugInfoNodeByCategory(pDrugInfo head, char* category);                            /*通过药品分类查找药品节点*/
pDrugInfo findDrugInfoNodeByOutPrice(pDrugInfo head, double outprice);                           /*通过售价查找药品节点*/
pDrugInfo findDrugInfoNodeByStock(pDrugInfo head, int min, int max);                             /*通过库存查找药品节点*/
pDrugInfo findDrugInfoNodeByFuzzy(pDrugInfo head, char* keyword);                                /*通过关键词模糊查找药品节点*/
void swapDrugInfoNode(pDrugInfo lhs, pDrugInfo rhs);                                                 /*交换两个药品节点*/
void sortDrugInfoNodeByID(pDrugInfo head);                                                           /*通过药品编号排序*/
void sortDrugInfoNodeByName(pDrugInfo head);                                                         /*通过药品名称排序*/
void sortDrugInfoNodeByOutPrice(pDrugInfo head);                                                     /*通过售价排序*/
void sortDrugInfoNodeByCount(pDrugInfo head);                                                        /*通过总量排序*/
void sortDrugInfoNodeBySales(pDrugInfo head);                                                        /*通过销量排序*/
int countDrugInfoNode(pDrugInfo head);                                                               /*计算药品节点数*/
void saveDrugInfoFile(const pDrugInfo _L);                                                           /*将药品信息存储到文件*/
pDrugInfo loadDrugInfoFile();                                                                        /*从文件中加载用户信息*/
void clearDrugInfoList(pDrugInfo head);                                                          /*清理药品列表，回收内存*/
void showDrugTitle();                                                                                /*显示药品标题*/
void showDrug(pDrugInfo drug);                                                                       /*显示药品信息*/
void showDrugList(pDrugInfo head);                                                                   /*显示药品列表信息*/
void editDrug(pDrugInfo drug);                                                                       /*编辑药品信息*/
void showDrugListOption(pDrugInfo head);                                                             /*显示药品清单选项*/
void createDrugOption(pDrugInfo* head);                                                              /*添加药品选项*/
void updateDrugOption(pDrugInfo head);                                                               /*修改药品选项*/
void removeDrugOption(pDrugInfo* head);                                                              /*删除药品选项*/
void searchDrugByIDOption(pDrugInfo head);                                                           /*按药品编号查询药品选项*/
void searchDrugByNameOption(pDrugInfo head);                                                         /*按药品名称查询药品选项*/
void searchDrugByOutPriceOption(pDrugInfo head);                                                     /*按售价查询药品选项*/
void searchDrugByStockOption(pDrugInfo head);                                                        /*按库存查询药品选项*/
void searchDrugByFuzzyOption(pDrugInfo head);                                                        /*按关键词模糊查询选项*/
void searchDrugsOption(pDrugInfo head);                                                              /*搜索药品*/
void inStorageByIDOption(pDrugInfo head);                                                            /*进货*/
void outStorageByIDOption(pDrugInfo head);                                                           /*出售*/
void expiredDrup(pDrugInfo head);                                                                    /*显示临期商品*/
void menu(pDrugInfo* head);                                                                          /*主菜单*/

#endif
