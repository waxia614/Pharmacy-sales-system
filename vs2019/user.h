#ifndef _USER_H_
#define _USER_H_
/*������������*/
#define ALERT_COUNT 20

/*����������ֵ*/
#define EXPIRED_DAYS 30

/*�ַ�������*/
#define STR_LEN 256
/*ҩƷ�ṹ��*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct _tDrugInfo {
    char a[STR_LEN];               /*ҩƷ���*/
    char b[STR_LEN];             /*ҩƷ����*/
    char c[STR_LEN];    /*��������*/
    char d[STR_LEN];  /*������*/
    char e[STR_LEN];         /*����*/
    double f;                 /*����*/
    double g;                /*�ۼ�*/
    int h;                      /*����*/
    int i;                      /*���*/
    struct _tDrugInfo* j;        /*��һ���ڵ�*/
} DrugInfo, * pDrugInfo;

void first();                                                                                        /*��ʼ����*/
void zhuce();                                                                                        /*ע�����*/
void denglu();                                                                                       /*��¼����*/

void formatDate(time_t tt, char* buf);                                                               /*������ת�����ı�*/
int isLeapYear(int year);                                                                            /*�ж��Ƿ�����*/
int checkDate(int yyyy, int mm, int dd);                                                             /*������ڣ�yyyy-mm-dd��*/
void inputDate(char date[]);                                                                         /*��������*/
int salesCount(pDrugInfo drug);                                                                      /*��������*/         
double salesAmount(pDrugInfo drug);                                                                  /*�������۶�*/
double countProfit(pDrugInfo drug);                                                                  /*��������*/
const char* alertDrug(pDrugInfo drug);                                                               /*��������*/
pDrugInfo addDrugInfoNode(pDrugInfo head, pDrugInfo node);                                       /*���ҩƷ�ڵ㣬���������׽ڵ�ָ��*/
pDrugInfo removeDrugInfoNode(pDrugInfo head, pDrugInfo node);                                    /*ɾ��ҩƷ�ڵ㣬���������׽ڵ�ָ��*/
pDrugInfo findDrugInfoNodeByID(pDrugInfo head, char* id);                                        /*ͨ��ҩƷ��Ų���ҩƷ�ڵ�*/
pDrugInfo findDrugInfoNodeByName(pDrugInfo head, char* name);                                    /*ͨ��ҩƷ���Ʋ���ҩƷ�ڵ�*/
pDrugInfo findDrugInfoNodeByCategory(pDrugInfo head, char* category);                            /*ͨ��ҩƷ�������ҩƷ�ڵ�*/
pDrugInfo findDrugInfoNodeByOutPrice(pDrugInfo head, double outprice);                           /*ͨ���ۼ۲���ҩƷ�ڵ�*/
pDrugInfo findDrugInfoNodeByStock(pDrugInfo head, int min, int max);                             /*ͨ��������ҩƷ�ڵ�*/
pDrugInfo findDrugInfoNodeByFuzzy(pDrugInfo head, char* keyword);                                /*ͨ���ؼ���ģ������ҩƷ�ڵ�*/
void swapDrugInfoNode(pDrugInfo lhs, pDrugInfo rhs);                                                 /*��������ҩƷ�ڵ�*/
void sortDrugInfoNodeByID(pDrugInfo head);                                                           /*ͨ��ҩƷ�������*/
void sortDrugInfoNodeByName(pDrugInfo head);                                                         /*ͨ��ҩƷ��������*/
void sortDrugInfoNodeByOutPrice(pDrugInfo head);                                                     /*ͨ���ۼ�����*/
void sortDrugInfoNodeByCount(pDrugInfo head);                                                        /*ͨ����������*/
void sortDrugInfoNodeBySales(pDrugInfo head);                                                        /*ͨ����������*/
int countDrugInfoNode(pDrugInfo head);                                                               /*����ҩƷ�ڵ���*/
void saveDrugInfoFile(const pDrugInfo _L);                                                           /*��ҩƷ��Ϣ�洢���ļ�*/
pDrugInfo loadDrugInfoFile();                                                                        /*���ļ��м����û���Ϣ*/
void clearDrugInfoList(pDrugInfo head);                                                          /*����ҩƷ�б������ڴ�*/
void showDrugTitle();                                                                                /*��ʾҩƷ����*/
void showDrug(pDrugInfo drug);                                                                       /*��ʾҩƷ��Ϣ*/
void showDrugList(pDrugInfo head);                                                                   /*��ʾҩƷ�б���Ϣ*/
void editDrug(pDrugInfo drug);                                                                       /*�༭ҩƷ��Ϣ*/
void showDrugListOption(pDrugInfo head);                                                             /*��ʾҩƷ�嵥ѡ��*/
void createDrugOption(pDrugInfo* head);                                                              /*���ҩƷѡ��*/
void updateDrugOption(pDrugInfo head);                                                               /*�޸�ҩƷѡ��*/
void removeDrugOption(pDrugInfo* head);                                                              /*ɾ��ҩƷѡ��*/
void searchDrugByIDOption(pDrugInfo head);                                                           /*��ҩƷ��Ų�ѯҩƷѡ��*/
void searchDrugByNameOption(pDrugInfo head);                                                         /*��ҩƷ���Ʋ�ѯҩƷѡ��*/
void searchDrugByOutPriceOption(pDrugInfo head);                                                     /*���ۼ۲�ѯҩƷѡ��*/
void searchDrugByStockOption(pDrugInfo head);                                                        /*������ѯҩƷѡ��*/
void searchDrugByFuzzyOption(pDrugInfo head);                                                        /*���ؼ���ģ����ѯѡ��*/
void searchDrugsOption(pDrugInfo head);                                                              /*����ҩƷ*/
void inStorageByIDOption(pDrugInfo head);                                                            /*����*/
void outStorageByIDOption(pDrugInfo head);                                                           /*����*/
void expiredDrup(pDrugInfo head);                                                                    /*��ʾ������Ʒ*/
void menu(pDrugInfo* head);                                                                          /*���˵�*/

#endif
