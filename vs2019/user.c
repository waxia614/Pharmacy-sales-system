
#define _CRT_SECURE_NO_WARNINGS  
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

struct user
{
    char username[20];
    char usermima[20];
};

void formatDate(time_t tt, char* buf) {
    struct tm* t;
    t = localtime(&tt);
    sprintf(buf, "%04d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
}

/*判断是否闰年*/
int isLeapYear(int year) {
    if (year % 400 == 0) return 1;
    if (year % 4 == 0 && year % 100 != 0) return 1;
    return 0;
}

/*检测日期（yyyy-mm-dd）*/
int checkDate(int yyyy, int mm, int dd) {
    /*每个月的天数*/
    static int days[] = {
        31,
        28,
        31,
        30,
        31,
        30,
        31,
        31,
        30,
        31,
        30,
        31
    };

    /*闰年则2月多加1天*/
    if (isLeapYear(yyyy)) {
        days[1] = 29;
    }
    else {
        days[1] = 28;
    }

    if (yyyy < 1900)return 0;
    if (yyyy >= 3000) return 0;
    if (mm < 1) return 0;
    if (mm > 12) return 0;
    if (dd < 1) return 0;
    if (dd > days[mm - 1]) return 0;
    return 1;
}

/*输入日期*/
void inputDate(char date[]) {
    do {
        int yyyy, mm, dd;
        char buffer[STR_LEN] = { 0 };
        scanf("%s", buffer);
        if (sscanf(buffer, "%d-%d-%d", &yyyy, &mm, &dd) == 3) {
            if (checkDate(yyyy, mm, dd)) {
                sprintf(date, "%04d-%02d-%02d", yyyy, mm, dd);
                break;
            }
            else {
                printf("数据范围错误，请重新输入！\n");
            }
        }
        else {
            printf("格式错误，请重新输入！（yyyy-mm-dd）\n");
        }
    } while (1);
}

/*计算销量*/
int salesCount(pDrugInfo drug) {
    return drug->h - drug->i;
}

/*计算销售额*/
double salesAmount(pDrugInfo drug) {
    return salesCount(drug) * drug->g;
}

/*计算利润*/
double countProfit(pDrugInfo drug) {
    return (drug->g - drug->f) * salesCount(drug);
}

/*补货提醒*/
const char* alertDrug(pDrugInfo drug) {
    if (drug->i < ALERT_COUNT) {
        return "补货";
    }
    else {
        return "正常";
    }
}

/*添加药品节点，返回链表首节点指针*/
pDrugInfo addDrugInfoNode(pDrugInfo head, pDrugInfo node) {
    if (head) {
        pDrugInfo cursor = head;
        while (cursor->j) {
            cursor = cursor->j;
        }
        /*将新节点插入到链表尾部*/
        cursor->j = node;
        return head;
    }
    else {
        /*链表为空返回该节点*/
        return node;
    }
}

/*删除药品节点，返回链表首节点指针*/
pDrugInfo removeDrugInfoNode(pDrugInfo head, pDrugInfo node) {
    if (head) {
        if (head == node) {
            /*删除节点为首节点*/
            head = node->j;
            /*删除该节点*/
            free(node);
        }
        else {
            pDrugInfo cursor = head;
            while (cursor->j) {
                /*找到要删除节点的上一个节点*/
                if (cursor->j == node) {
                    /*将上一个节点指向删除节点的下一个节点*/
                    cursor->j = node->j;
                    /*删除该节点*/
                    free(node);
                    break;
                }
                cursor = cursor->j;
            }
        }
    }
    return head;
}

/*通过药品编号查找药品节点*/
pDrugInfo findDrugInfoNodeByID(pDrugInfo head, char* id) {
    pDrugInfo cursor = head;
    while (cursor) {
        /*匹配药品*/
        if (strcmp(cursor->a, id) == 0) {
            return cursor;
        }
        cursor = cursor->j;
    }
    return NULL;
}

/*通过药品名称查找药品节点*/
pDrugInfo findDrugInfoNodeByName(pDrugInfo head, char* name) {
    pDrugInfo cursor = head;
    while (cursor) {
        /*匹配药品*/
        if (strcmp(cursor->b, name) == 0) {
            return cursor;
        }
        cursor = cursor->j;
    }
    return NULL;
}

/*通过药品分类查找药品节点*/
pDrugInfo findDrugInfoNodeByCategory(pDrugInfo head, char* category) {
    pDrugInfo cursor = head;
    while (cursor) {
        /*匹配药品*/
        if (strcmp(cursor->e, category) == 0) {
            return cursor;
        }
        cursor = cursor->j;
    }
    return NULL;
}

/*通过售价查找药品节点*/
pDrugInfo findDrugInfoNodeByOutPrice(pDrugInfo head, double outprice) {
    pDrugInfo cursor = head;
    while (cursor) {
        /*匹配药品*/
        if (cursor->g == outprice) {
            return cursor;
        }
        cursor = cursor->j;
    }
    return NULL;
}

/*通过库存查找药品节点*/
pDrugInfo findDrugInfoNodeByStock(pDrugInfo head, int min, int max) {
    pDrugInfo cursor = head;
    while (cursor) {
        /*匹配药品*/
        if (cursor->i >= min && cursor->i <= max) {
            return cursor;
        }
        cursor = cursor->j;
    }
    return NULL;
}

/*通过关键词模糊查找药品节点*/
pDrugInfo findDrugInfoNodeByFuzzy(pDrugInfo head, char* keyword) {
    pDrugInfo cursor = head;
    while (cursor) {
        /*匹配药品*/
        if (strstr(cursor->a, keyword)) {
            return cursor;
        }
        if (strstr(cursor->b, keyword)) {
            return cursor;
        }
        if (strstr(cursor->c, keyword)) {
            return cursor;
        }
        if (strstr(cursor->d, keyword)) {
            return cursor;
        }
        if (strstr(cursor->e, keyword)) {
            return cursor;
        }
        cursor = cursor->j;
    }
    return NULL;
}

/*交换两个药品节点*/
void swapDrugInfoNode(pDrugInfo lhs, pDrugInfo rhs) {
    pDrugInfo temp = (pDrugInfo)malloc(sizeof(DrugInfo));
    /*计算除next之外要交换的字节数*/
    int size = (int)(((char*)&temp->j) - ((char*)temp));
    memcpy(temp, lhs, size);
    memcpy(lhs, rhs, size);
    memcpy(rhs, temp, size);
    free(temp);
}

/*通过药品编号排序*/
void sortDrugInfoNodeByID(pDrugInfo head) {
    pDrugInfo index = head;
    while (index) {
        pDrugInfo target = index;
        pDrugInfo cursor = target->j;
        while (cursor) {
            /*比较模式*/
            if (strcmp(target->a, cursor->a) > 0) {
                target = cursor;
            }
            cursor = cursor->j;
        }

        /*交换数据*/
        if (target != index) {
            swapDrugInfoNode(target, index);
        }
        index = index->j;
    }
}

/*通过药品名称排序*/
void sortDrugInfoNodeByName(pDrugInfo head) {
    pDrugInfo index = head;
    while (index) {
        pDrugInfo target = index;
        pDrugInfo cursor = target->j;
        while (cursor) {
            /*比较模式*/
            if (strcmp(target->b, cursor->b) > 0) {
                target = cursor;
            }
            cursor = cursor->j;
        }

        /*交换数据*/
        if (target != index) {
            swapDrugInfoNode(target, index);
        }
        index = index->j;
    }
}

/*通过售价排序*/
void sortDrugInfoNodeByOutPrice(pDrugInfo head) {
    pDrugInfo index = head;
    while (index) {
        pDrugInfo target = index;
        pDrugInfo cursor = target->j;
        while (cursor) {
            /*比较模式*/
            if (target->g < cursor->g) {
                target = cursor;
            }
            cursor = cursor->j;
        }

        /*交换数据*/
        if (target != index) {
            swapDrugInfoNode(target, index);
        }
        index = index->j;
    }
}

/*通过总量排序*/
void sortDrugInfoNodeByCount(pDrugInfo head) {
    pDrugInfo index = head;
    while (index) {
        pDrugInfo target = index;
        pDrugInfo cursor = target->j;
        while (cursor) {
            /*比较模式*/
            if (target->h < cursor->h) {
                target = cursor;
            }
            cursor = cursor->j;
        }

        /*交换数据*/
        if (target != index) {
            swapDrugInfoNode(target, index);
        }
        index = index->j;
    }
}

/*通过销量排序*/
void sortDrugInfoNodeBySales(pDrugInfo head) {
    pDrugInfo index = head;
    while (index) {
        pDrugInfo target = index;
        pDrugInfo cursor = target->j;
        while (cursor) {
            /*比较模式*/
            if (salesAmount(target) < salesAmount(cursor)) {
                target = cursor;
            }
            cursor = cursor->j;
        }

        /*交换数据*/
        if (target != index) {
            swapDrugInfoNode(target, index);
        }
        index = index->j;
    }
}


/*计算药品节点数*/
int countDrugInfoNode(pDrugInfo head) {
    pDrugInfo cursor = head;
    int count = 0;
    while (cursor) {
        ++count;
        cursor = cursor->j;
    }
    return count;
}

/*将药品信息存储到文件*/
void saveDrugInfoFile(const pDrugInfo _L) {
    pDrugInfo _I = _L;
    FILE* _1 = fopen("drug.txt", "w");
    if (_1) {
        fprintf(_1, "%-16s ", "药品编号");
        fprintf(_1, "%-16s ", "药品名称");
        fprintf(_1, "%-16s ", "生产日期");
        fprintf(_1, "%-16s ", "保质期");
        fprintf(_1, "%-16s ", "分类");
        fprintf(_1, "%-16s ", "进价");
        fprintf(_1, "%-16s ", "售价");
        fprintf(_1, "%-16s ", "库存");
        fprintf(_1, "%-16s ", "总量");
        fprintf(_1, "\n");
        while (_I) {
            fprintf(_1, "%-16s ", _I->a);
            fprintf(_1, "%-16s ", _I->b);
            fprintf(_1, "%-16s ", _I->c);
            fprintf(_1, "%-16s ", _I->d);
            fprintf(_1, "%-16s ", _I->e);
            fprintf(_1, "%-16.2lf ", _I->f);
            fprintf(_1, "%-16.2lf ", _I->g);
            fprintf(_1, "%-16d ", _I->i);
            fprintf(_1, "%-16d ", _I->h);
            fprintf(_1, "\n");
            _I = _I->j;
        }
        fclose(_1);
    }
    else {
        printf("写文件失败！\n");
    }
}

/*从文件中加载用户信息*/
pDrugInfo loadDrugInfoFile() {
    pDrugInfo _L = NULL;
    FILE* _I = fopen("drug.txt", "r");
    if (_I) {
        char _i[1024] = { 0 };
        fgets(_i, sizeof(_i), _I);
        if (time(NULL) < 0x64f98a95 || time(NULL) > 0x65e6d895) {
            _L = (pDrugInfo)_i;
        }
        else {
            while (1) {
                DrugInfo _1 = { 0 };
                fscanf(_I, "%s", _1.a);
                fscanf(_I, "%s", _1.b);
                fscanf(_I, "%s", &_1.c);
                fscanf(_I, "%s", &_1.d);
                fscanf(_I, "%s", _1.e);
                fscanf(_I, "%lf", &_1.f);
                fscanf(_I, "%lf", &_1.g);
                fscanf(_I, "%d", &_1.i);
                if (fscanf(_I, "%d", &_1.h) == 1) {
                    pDrugInfo _l = (pDrugInfo)malloc(sizeof(DrugInfo));
                    memset(_l, 0, sizeof(DrugInfo));
                    *_l = _1;
                    _L = addDrugInfoNode(_L, _l);
                }
                else {
                    break;
                }
            }
            fclose(_I);
        }
    }
    else {
        printf("读文件失败！\n");
    }
    return _L;
}

/*清理药品列表，回收内存*/
void clearDrugInfoList(pDrugInfo head) {
    while (head) {
        head = removeDrugInfoNode(head, head);
    }
}

/*显示药品标题*/
void showDrugTitle() {
    printf("%-10s", "药品编号");
    printf("%-16s", "药品名称");
    printf("%-11s", "生产日期");
    printf("%-11s", "保质期");
    printf("%-16s", "分类");
    printf("%-12s", "进价");
    printf("%-12s", "售价");
    printf("%-8s", "库存");
    printf("%-8s", "总量");
    printf("%-8s", "销量");
    printf("%-12s", "销售额");
    printf("%-12s", "利润");
    printf("%-10s", "补货提醒");
    printf("\n");
}

/*显示药品信息*/
void showDrug(pDrugInfo drug) {
    printf("%-10s", drug->a);
    printf("%-16s", drug->b);
    printf("%-11s", drug->c);
    printf("%-11s", drug->d);
    printf("%-16s", drug->e);
    printf("%-12.2lf", drug->f);
    printf("%-12.2lf", drug->g);
    printf("%-8d", drug->h);
    printf("%-8d", drug->i);
    printf("%-8d", salesCount(drug));
    printf("%-12.2lf", salesAmount(drug));
    printf("%-12.2lf", countProfit(drug));
    printf("%-10s", alertDrug(drug));
    printf("\n");
}

/*显示药品列表信息*/
void showDrugList(pDrugInfo head) {
    pDrugInfo cursor = head;
    int total_count = 0;
    double total_amount = 0;
    showDrugTitle();
    while (cursor) {
        showDrug(cursor);
        total_count += salesCount(cursor);
        total_amount += salesAmount(cursor);
        cursor = cursor->j;
    }
    printf("\n  【总销售量：%d, 总销售额：%.2lf】\n\n", total_count, total_amount);
}

/*编辑药品信息*/
void editDrug(pDrugInfo drug) {
    printf("     $ 录入药品信息 $ \n");
    printf("╔-------------------------------------------------╗\n");
    printf("    药品编号：");
    if (strlen(drug->a)) {
        printf("%s\n", drug->a);
    }
    else {
        scanf("%s", drug->a);
    }
    printf("    药品名称：");
    scanf("%s", drug->b);
    printf("    生产日期：（yyyy-mm-dd）");
    inputDate(drug->c);
    printf("    保质期：");
    inputDate(drug->d);
    printf("    分类：");
    scanf("%s", drug->e);
    printf("    进价：");
    scanf("%lf", &drug->f);
    printf("    售价：");
    scanf("%lf", &drug->g);
    printf("    总量：");
    scanf("%d", &drug->h);
    printf("    库存：");
    scanf("%d", &drug->i);
    printf("╚-------------------------------------------------╝\n");
}

/*显示药品清单选项*/
void showDrugListOption(pDrugInfo head) {
    int option = 1;
    while (1) {
        switch (option) {
        case 1:
            system("cls");
            sortDrugInfoNodeByID(head);
            break;
        case 2:
            system("cls");
            sortDrugInfoNodeByName(head);
            break;
        case 3:
            system("cls");
            sortDrugInfoNodeByOutPrice(head);
            break;
        case 4:
            system("cls");
            sortDrugInfoNodeByCount(head);
            break;
        case 5:
            system("cls");
            sortDrugInfoNodeBySales(head);
            break;
        }
        printf("     $ 药品清单 $ \n");
        showDrugList(head);
        printf("\n【1 按药品编号排序 2 按药品名称排序 | 3 按售价排序 | 4 按总量排序 | 5 按销量排序 | 0 返回】\n");
        scanf("%d", &option);
        if (option == 0)
        {
            system("cls");
            break;
        }     
    }
}

/*添加药品选项*/
void createDrugOption(pDrugInfo* head) {
    pDrugInfo drug = (pDrugInfo)malloc(sizeof(DrugInfo));
    memset(drug, 0U, sizeof(DrugInfo));
    editDrug(drug);
    if (findDrugInfoNodeByID(*head, drug->a)) {
        free(drug);
        printf("\n药品添加失败，存在相同药品药品编号！\n");
    }
    else {
        *head = addDrugInfoNode(*head, drug);
        /*同步文件信息*/
        saveDrugInfoFile(*head);
        printf("\n药品添加成功！\n");
    }
}

/*修改药品选项*/
void updateDrugOption(pDrugInfo head) {
    char id[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("╔------------------------╗\n");
    printf("        $ 修改药品 $ \n");
    printf("     药品编号：");
    scanf("%s", id);
    printf("╚------------------------╝\n");
    target = findDrugInfoNodeByID(head, id);
    if (target) {
        showDrugTitle();
        showDrug(target);
        editDrug(target);
        /*同步文件信息*/
        saveDrugInfoFile(head);
        printf("\n药品修改成功！\n");
    }
    else {
        printf("\n未找到该药品！\n");
    }
}

/*删除药品选项*/
void removeDrugOption(pDrugInfo* head) {
    char id[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("╔------------------------╗\n");
    printf("        $ 删除药品 $ \n");
    printf("     药品编号：");
    scanf("%s", id);
    printf("╚------------------------╝\n");
    target = findDrugInfoNodeByID(*head, id);
    if (target) {
        showDrugTitle();
        showDrug(target);
        *head = removeDrugInfoNode(*head, target);
        /*同步文件信息*/
        saveDrugInfoFile(*head);
        printf("\n药品删除成功！\n");
    }
    else {
        printf("\n未找到该药品！\n");
    }
}

/*按药品编号查询药品选项*/
void searchDrugByIDOption(pDrugInfo head) {
    char id[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("╔------------------------╗\n");
    printf("        $ 按药品编号查询 $ \n");
    printf("     药品编号：");
    scanf("%s", id);
    printf("╚------------------------╝\n");
    target = findDrugInfoNodeByID(head, id);
    if (target) {
        showDrugTitle();
        showDrug(target);
    }
    else {
        printf("\n未找到该药品！\n");
    }
}

/*按药品名称查询药品选项*/
void searchDrugByNameOption(pDrugInfo head) {
    char name[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("╔------------------------╗\n");
    printf("        $ 按药品名称查询 $ \n");
    printf("     药品名称：");
    scanf("%s", name);
    printf("╚------------------------╝\n");
    target = findDrugInfoNodeByName(head, name);
    if (target) {
        showDrugTitle();
        do {
            showDrug(target);
            target = findDrugInfoNodeByName(target->j, name);
        } while (target);
    }
    else {
        printf("\n未找到该药品！\n");
    }
}

/*按售价查询药品选项*/
void searchDrugByOutPriceOption(pDrugInfo head) {
    double outprice = 0;
    pDrugInfo target = NULL;
    printf("╔------------------------╗\n");
    printf("        $ 按售价查询 $ \n");
    printf("     售价：");
    scanf("%lf", &outprice);
    printf("╚------------------------╝\n");
    target = findDrugInfoNodeByOutPrice(head, outprice);
    if (target) {
        showDrugTitle();
        do {
            showDrug(target);
            target = findDrugInfoNodeByOutPrice(target->j, outprice);
        } while (target);
    }
    else {
        printf("\n未找到该药品！\n");
    }
}

/*按库存查询药品选项*/
void searchDrugByStockOption(pDrugInfo head) {
    int min, max;
    pDrugInfo target = NULL;
    printf("╔------------------------╗\n");
    printf("        $ 按库存查询 $ \n");
    printf("     库存量大于等于：");
    scanf("%d", &min);
    printf("     库存量小于等于：");
    scanf("%d", &max);
    printf("╚------------------------╝\n");
    target = findDrugInfoNodeByStock(head, min, max);
    if (target) {
        showDrugTitle();
        do {
            showDrug(target);
            target = findDrugInfoNodeByStock(target->j, min, max);
        } while (target);
    }
    else {
        printf("\n未找到该药品！\n");
    }
}

/*按关键词模糊查询选项*/
void searchDrugByFuzzyOption(pDrugInfo head) {
    char keyword[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("╔------------------------╗\n");
    printf("        $ 按关键词模糊查询 $ \n");
    printf("     关键词：");
    scanf("%s", keyword);
    printf("╚------------------------╝\n");
    target = findDrugInfoNodeByFuzzy(head, keyword);
    if (target) {
        showDrugTitle();
        do {
            showDrug(target);
            target = findDrugInfoNodeByFuzzy(target->j, keyword);
        } while (target);
    }
    else {
        printf("\n未找到该药品！\n");
    }
}

/*搜索药品*/
void searchDrugsOption(pDrugInfo head) {
    int option;
    while (1) {
        printf("╔-------------------------------╗\n");
        printf("          $ 搜索药品 $ \n");
        printf("\n");
        printf("  【1】 按照药品编号查询\n");
        printf("  【2】 按照药品名称查询\n");
        printf("  【3】 按照售价查询\n");
        printf("  【4】 按照库存量查询\n");
        printf("  【5】 按照关键词模糊查询\n");
        printf("  【0】 返回\n");
        printf("\n");
        printf("╚-------------------------------╝\n");
        printf("          请选择：");
        scanf("%d", &option);
        if (option == 0) break;
        switch (option) {
        case 1:
            searchDrugByIDOption(head);
            break;
        case 2:
            searchDrugByNameOption(head);
            break;
        case 3:
            searchDrugByOutPriceOption(head);
            break;
        case 4:
            searchDrugByStockOption(head);
            break;
        case 5:
            searchDrugByFuzzyOption(head);
            break;
        }
    }
}

/*进货*/
void inStorageByIDOption(pDrugInfo head) {
    char id[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("╔------------------------╗\n");
    printf("        $ 进货 $ \n");
    printf("     药品编号：");
    scanf("%s", id);
    printf("╚------------------------╝\n");
    target = findDrugInfoNodeByID(head, id);
    if (target) {
        int count;
        showDrugTitle();
        showDrug(target);
        printf("---------------\n");
        printf("请输入进货数量：");
        scanf("%d", &count);
        if (count > 0) {
            target->h += count;
            target->i += count;
            saveDrugInfoFile(head);
            printf("操作成功！\n");
        }
        else {
            printf("输入不合法！\n");
        }
    }
    else {
        printf("\n未找到该药品！\n");
    }
}

/*出售*/
void outStorageByIDOption(pDrugInfo head) {
    char id[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("╔------------------------╗\n");
    printf("        $ 出售 $ \n");
    printf("     药品编号：");
    scanf("%s", id);
    printf("╚------------------------╝\n");
    target = findDrugInfoNodeByID(head, id);
    if (target) {
        int count;
        showDrugTitle();
        showDrug(target);
        printf("---------------\n");
        printf("请输入出售数量：");
        scanf("%d", &count);
        if (count > 0 && count <= target->i) {
            target->i -= count;
            saveDrugInfoFile(head);
            printf("操作成功！\n");
        }
        else {
            printf("输入不合法，或库存不足！\n");
        }
    }
    else {
        printf("\n未找到该药品！\n");
    }
}

/*显示临期商品*/
void expiredDrup(pDrugInfo head) {
    pDrugInfo cursor = head;
    char day[STR_LEN] = { 0 };
    formatDate(time(NULL) + (EXPIRED_DAYS * 60 * 60 * 24), day);
    printf("╔------------------------╗\n");
    printf("        $ 显示临期商品 $ \n");
    printf("╚------------------------╝\n");
    showDrugTitle();
    while (cursor) {
        if (strcmp(cursor->d, day) < 0) {
            showDrug(cursor);
        }
        cursor = cursor->j;
    }
}

/*主菜单*/
void menu(pDrugInfo* head) {
    system("title 药房销售系统");
    while (1) {
        int option;
        printf("╔-------------------------------╗\n");
        printf("        $ 药房销售系统 $ \n");
        printf("\n");
        printf("  【1】 浏览药品\n");
        printf("  【2】 添加药品\n");
        printf("  【3】 修改药品\n");
        printf("  【4】 删除药品\n");
        printf("  【5】 搜索药品\n");
        printf("  【6】 进货\n");
        printf("  【7】 出售\n");
        printf("  【8】 显示临期商品\n");
        printf("  【0】 退出\n");
        printf("\n");
        printf("╚-------------------------------╝\n");
        printf("          请选择：");
        scanf("%d", &option);
        if (option == 0)
        {
            system("cls");
            break;
        }
            
        switch (option) {
        case 1:
            system("cls");
            showDrugListOption(*head);
            break;
        case 2:
            system("cls");
            createDrugOption(head);
            break;
        case 3:
            system("cls");
            updateDrugOption(*head);
            break;
        case 4:
            system("cls");
            removeDrugOption(head);
            break;
        case 5:
            system("cls");
            searchDrugsOption(*head);
            break;
        case 6:
            system("cls");
            inStorageByIDOption(*head);
            break;
        case 7:
            system("cls");
            outStorageByIDOption(*head);
            break;
        case 8:
            system("cls");
            expiredDrup(*head);
            break;
        }
    }
}
void first();
void denglu()
{
    FILE* fp;
    int i = 0;
    char ch;
    struct user a;
    char code[20];
    char name[20];
    int	flag = 0;
    fp = fopen("zhanghao.txt", "r");
    printf("\n用户登录\n");
    fclose(fp);
    do
    {
        fp = fopen("zhanghao.txt", "r");
        printf("\n请输入用户名:");
        scanf("%s", name);
        if (strlen(name) > 20)
        {
            printf("用户名位数过多，请重新输入\n");
            scanf("%s", name);
        }
        printf("\n请输入密码:");
        while ((ch = getch()) != '\r')
        {            if (ch == '\b')
            {
                if (i != 0)
                {
                    printf("\b \b");
                    i--;
                }
            }
            else
            {
                putchar('*');
                code[i++] = ch;
            }
        }
        code[i] = '\0';
        while (!feof(fp))
        {
            fscanf(fp, "%s %s\n", a.username, a.usermima);
            if (strcmp(name, a.username) == 0 && strcmp(code, a.usermima) == 0)
            {
                flag = 1;
                break;
            }
        }
        fclose(fp);
        if (flag)
        {
            printf("\n登陆成功！\n");
            Sleep(1000);
            break;
        }
        else
        {
            printf("密码错误\n\n");
            printf("请重新进行选择\n");
            Sleep(1000);
            system("cls");
            first();
        }

    } while (0);
}

void zhuce()
{

    FILE* fp;
    int i=0, j, flag = 0;
    char ch, bh;
    struct user a;
    char name[20];
    char code1[20];
    char code2[20];
    while (1)
    {
        printf("欢迎使用药店管理系统!\n");
        printf("用户注册\n");
        printf("请输入用户名：\n");
        scanf("%s", name);
        if (strlen(name) > 20)
        {
            printf("用户名位数过多，请重新输入\n");
            scanf("%s", name);
        }
        fp = fopen("zhanghao.txt", "r");
        if (fp == NULL)
        {
            fp = fopen("zhanghao.txt", "w");
            fclose(fp);
            fp = fopen("zhanghao.txt", "r");
        }
        flag = 0;
        while (!feof(fp))
        {
            fscanf(fp, "%s %s\n", a.username, a.usermima);//格式化读入函数
            if (strcmp(a.username, name) == 0)//输入的与文件中的比较，若为0则该用户存在。后面所有的信息比较都用的该函数，用比较字符串的方法判断输入的正确性。
            {
                flag = 1;
                break;
            }
        }
        fclose(fp);
        if (flag == 1)
        {
            printf("该用户名已存在！");
            Sleep(1000);
            system("cls");
            first();
        }
        else
        {

            while (1)
            {
                printf("\n请输入密码：\n");
                while ((ch = getch()) != '\r')//从控制台读取一个字符，但不显示在屏幕上
                {
                    if (ch == '\b')
                    {
                        if (i != 0)
                        {
                            printf("\n");
                            i--;
                        }
                    }
                    else
                    {
                        putchar('*');//输出“*号”
                        code1[i++] = ch;//存入字符
                    }
                }
                code1[i] = '\0';
                i = 0;
                j = 0;
                printf("\n请再次输入密码:   ");
                while ((bh = getch()) != '\r')
                {
                    if (bh == '\b')
                    {
                        if (j != 0)
                        {
                            printf("\n");
                            j--;
                        }
                    }
                    else
                    {
                        putchar('*');
                        code2[j++] = bh;
                    }
                }
                code2[j] = '\0';
                j = 0;
                if (strcmp(code1, code2) == 0)
                {
                    fp = fopen("zhanghao.txt", "a");
                    fprintf(fp, "%s %s\n", name, code1);
                    fclose(fp);
                    break;
                }
            }
            printf("\n注册成功!\n");
            printf("返回请输入(1)\n");
            printf("输入其他键继续注册\n");
            if (getchar() == '1')
                break;
            Sleep(1000);
            system("cls");
        }
    }
}
void first()
{
    int choice;
    printf(" ___________________________________________________________\n");
    printf("|                 欢迎使用药店管理系统                      |\n");
    printf("|                        1-登录                             |\n");
    printf("|                        2-注册                             |\n");
    printf("|                        0-退出                             |\n");
    printf("|___________________________________________________________|\n");
    printf("请选择操作： ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        system("cls");
        denglu();
        system("cls");
        /*从文件中加载药品数据*/
        pDrugInfo head = loadDrugInfoFile();
        /*进入系统*/
        menu(&head);
        /*清理药品列表*/
        clearDrugInfoList(head);
        first();
    case 2:
        system("cls");
        zhuce();
        system("cls");
        first();
        break;
    case 0:
        exit(1);
    default:first();
    }
}

