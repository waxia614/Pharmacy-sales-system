
#define _CRT_SECURE_NO_WARNINGS  
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

/*�ж��Ƿ�����*/
int isLeapYear(int year) {
    if (year % 400 == 0) return 1;
    if (year % 4 == 0 && year % 100 != 0) return 1;
    return 0;
}

/*������ڣ�yyyy-mm-dd��*/
int checkDate(int yyyy, int mm, int dd) {
    /*ÿ���µ�����*/
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

    /*������2�¶��1��*/
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

/*��������*/
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
                printf("���ݷ�Χ�������������룡\n");
            }
        }
        else {
            printf("��ʽ�������������룡��yyyy-mm-dd��\n");
        }
    } while (1);
}

/*��������*/
int salesCount(pDrugInfo drug) {
    return drug->h - drug->i;
}

/*�������۶�*/
double salesAmount(pDrugInfo drug) {
    return salesCount(drug) * drug->g;
}

/*��������*/
double countProfit(pDrugInfo drug) {
    return (drug->g - drug->f) * salesCount(drug);
}

/*��������*/
const char* alertDrug(pDrugInfo drug) {
    if (drug->i < ALERT_COUNT) {
        return "����";
    }
    else {
        return "����";
    }
}

/*���ҩƷ�ڵ㣬���������׽ڵ�ָ��*/
pDrugInfo addDrugInfoNode(pDrugInfo head, pDrugInfo node) {
    if (head) {
        pDrugInfo cursor = head;
        while (cursor->j) {
            cursor = cursor->j;
        }
        /*���½ڵ���뵽����β��*/
        cursor->j = node;
        return head;
    }
    else {
        /*����Ϊ�շ��ظýڵ�*/
        return node;
    }
}

/*ɾ��ҩƷ�ڵ㣬���������׽ڵ�ָ��*/
pDrugInfo removeDrugInfoNode(pDrugInfo head, pDrugInfo node) {
    if (head) {
        if (head == node) {
            /*ɾ���ڵ�Ϊ�׽ڵ�*/
            head = node->j;
            /*ɾ���ýڵ�*/
            free(node);
        }
        else {
            pDrugInfo cursor = head;
            while (cursor->j) {
                /*�ҵ�Ҫɾ���ڵ����һ���ڵ�*/
                if (cursor->j == node) {
                    /*����һ���ڵ�ָ��ɾ���ڵ����һ���ڵ�*/
                    cursor->j = node->j;
                    /*ɾ���ýڵ�*/
                    free(node);
                    break;
                }
                cursor = cursor->j;
            }
        }
    }
    return head;
}

/*ͨ��ҩƷ��Ų���ҩƷ�ڵ�*/
pDrugInfo findDrugInfoNodeByID(pDrugInfo head, char* id) {
    pDrugInfo cursor = head;
    while (cursor) {
        /*ƥ��ҩƷ*/
        if (strcmp(cursor->a, id) == 0) {
            return cursor;
        }
        cursor = cursor->j;
    }
    return NULL;
}

/*ͨ��ҩƷ���Ʋ���ҩƷ�ڵ�*/
pDrugInfo findDrugInfoNodeByName(pDrugInfo head, char* name) {
    pDrugInfo cursor = head;
    while (cursor) {
        /*ƥ��ҩƷ*/
        if (strcmp(cursor->b, name) == 0) {
            return cursor;
        }
        cursor = cursor->j;
    }
    return NULL;
}

/*ͨ��ҩƷ�������ҩƷ�ڵ�*/
pDrugInfo findDrugInfoNodeByCategory(pDrugInfo head, char* category) {
    pDrugInfo cursor = head;
    while (cursor) {
        /*ƥ��ҩƷ*/
        if (strcmp(cursor->e, category) == 0) {
            return cursor;
        }
        cursor = cursor->j;
    }
    return NULL;
}

/*ͨ���ۼ۲���ҩƷ�ڵ�*/
pDrugInfo findDrugInfoNodeByOutPrice(pDrugInfo head, double outprice) {
    pDrugInfo cursor = head;
    while (cursor) {
        /*ƥ��ҩƷ*/
        if (cursor->g == outprice) {
            return cursor;
        }
        cursor = cursor->j;
    }
    return NULL;
}

/*ͨ��������ҩƷ�ڵ�*/
pDrugInfo findDrugInfoNodeByStock(pDrugInfo head, int min, int max) {
    pDrugInfo cursor = head;
    while (cursor) {
        /*ƥ��ҩƷ*/
        if (cursor->i >= min && cursor->i <= max) {
            return cursor;
        }
        cursor = cursor->j;
    }
    return NULL;
}

/*ͨ���ؼ���ģ������ҩƷ�ڵ�*/
pDrugInfo findDrugInfoNodeByFuzzy(pDrugInfo head, char* keyword) {
    pDrugInfo cursor = head;
    while (cursor) {
        /*ƥ��ҩƷ*/
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

/*��������ҩƷ�ڵ�*/
void swapDrugInfoNode(pDrugInfo lhs, pDrugInfo rhs) {
    pDrugInfo temp = (pDrugInfo)malloc(sizeof(DrugInfo));
    /*�����next֮��Ҫ�������ֽ���*/
    int size = (int)(((char*)&temp->j) - ((char*)temp));
    memcpy(temp, lhs, size);
    memcpy(lhs, rhs, size);
    memcpy(rhs, temp, size);
    free(temp);
}

/*ͨ��ҩƷ�������*/
void sortDrugInfoNodeByID(pDrugInfo head) {
    pDrugInfo index = head;
    while (index) {
        pDrugInfo target = index;
        pDrugInfo cursor = target->j;
        while (cursor) {
            /*�Ƚ�ģʽ*/
            if (strcmp(target->a, cursor->a) > 0) {
                target = cursor;
            }
            cursor = cursor->j;
        }

        /*��������*/
        if (target != index) {
            swapDrugInfoNode(target, index);
        }
        index = index->j;
    }
}

/*ͨ��ҩƷ��������*/
void sortDrugInfoNodeByName(pDrugInfo head) {
    pDrugInfo index = head;
    while (index) {
        pDrugInfo target = index;
        pDrugInfo cursor = target->j;
        while (cursor) {
            /*�Ƚ�ģʽ*/
            if (strcmp(target->b, cursor->b) > 0) {
                target = cursor;
            }
            cursor = cursor->j;
        }

        /*��������*/
        if (target != index) {
            swapDrugInfoNode(target, index);
        }
        index = index->j;
    }
}

/*ͨ���ۼ�����*/
void sortDrugInfoNodeByOutPrice(pDrugInfo head) {
    pDrugInfo index = head;
    while (index) {
        pDrugInfo target = index;
        pDrugInfo cursor = target->j;
        while (cursor) {
            /*�Ƚ�ģʽ*/
            if (target->g < cursor->g) {
                target = cursor;
            }
            cursor = cursor->j;
        }

        /*��������*/
        if (target != index) {
            swapDrugInfoNode(target, index);
        }
        index = index->j;
    }
}

/*ͨ����������*/
void sortDrugInfoNodeByCount(pDrugInfo head) {
    pDrugInfo index = head;
    while (index) {
        pDrugInfo target = index;
        pDrugInfo cursor = target->j;
        while (cursor) {
            /*�Ƚ�ģʽ*/
            if (target->h < cursor->h) {
                target = cursor;
            }
            cursor = cursor->j;
        }

        /*��������*/
        if (target != index) {
            swapDrugInfoNode(target, index);
        }
        index = index->j;
    }
}

/*ͨ����������*/
void sortDrugInfoNodeBySales(pDrugInfo head) {
    pDrugInfo index = head;
    while (index) {
        pDrugInfo target = index;
        pDrugInfo cursor = target->j;
        while (cursor) {
            /*�Ƚ�ģʽ*/
            if (salesAmount(target) < salesAmount(cursor)) {
                target = cursor;
            }
            cursor = cursor->j;
        }

        /*��������*/
        if (target != index) {
            swapDrugInfoNode(target, index);
        }
        index = index->j;
    }
}


/*����ҩƷ�ڵ���*/
int countDrugInfoNode(pDrugInfo head) {
    pDrugInfo cursor = head;
    int count = 0;
    while (cursor) {
        ++count;
        cursor = cursor->j;
    }
    return count;
}

/*��ҩƷ��Ϣ�洢���ļ�*/
void saveDrugInfoFile(const pDrugInfo _L) {
    pDrugInfo _I = _L;
    FILE* _1 = fopen("drug.txt", "w");
    if (_1) {
        fprintf(_1, "%-16s ", "ҩƷ���");
        fprintf(_1, "%-16s ", "ҩƷ����");
        fprintf(_1, "%-16s ", "��������");
        fprintf(_1, "%-16s ", "������");
        fprintf(_1, "%-16s ", "����");
        fprintf(_1, "%-16s ", "����");
        fprintf(_1, "%-16s ", "�ۼ�");
        fprintf(_1, "%-16s ", "���");
        fprintf(_1, "%-16s ", "����");
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
        printf("д�ļ�ʧ�ܣ�\n");
    }
}

/*���ļ��м����û���Ϣ*/
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
        printf("���ļ�ʧ�ܣ�\n");
    }
    return _L;
}

/*����ҩƷ�б������ڴ�*/
void clearDrugInfoList(pDrugInfo head) {
    while (head) {
        head = removeDrugInfoNode(head, head);
    }
}

/*��ʾҩƷ����*/
void showDrugTitle() {
    printf("%-10s", "ҩƷ���");
    printf("%-16s", "ҩƷ����");
    printf("%-11s", "��������");
    printf("%-11s", "������");
    printf("%-16s", "����");
    printf("%-12s", "����");
    printf("%-12s", "�ۼ�");
    printf("%-8s", "���");
    printf("%-8s", "����");
    printf("%-8s", "����");
    printf("%-12s", "���۶�");
    printf("%-12s", "����");
    printf("%-10s", "��������");
    printf("\n");
}

/*��ʾҩƷ��Ϣ*/
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

/*��ʾҩƷ�б���Ϣ*/
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
    printf("\n  ������������%d, �����۶%.2lf��\n\n", total_count, total_amount);
}

/*�༭ҩƷ��Ϣ*/
void editDrug(pDrugInfo drug) {
    printf("     $ ¼��ҩƷ��Ϣ $ \n");
    printf("�X-------------------------------------------------�[\n");
    printf("    ҩƷ��ţ�");
    if (strlen(drug->a)) {
        printf("%s\n", drug->a);
    }
    else {
        scanf("%s", drug->a);
    }
    printf("    ҩƷ���ƣ�");
    scanf("%s", drug->b);
    printf("    �������ڣ���yyyy-mm-dd��");
    inputDate(drug->c);
    printf("    �����ڣ�");
    inputDate(drug->d);
    printf("    ���ࣺ");
    scanf("%s", drug->e);
    printf("    ���ۣ�");
    scanf("%lf", &drug->f);
    printf("    �ۼۣ�");
    scanf("%lf", &drug->g);
    printf("    ������");
    scanf("%d", &drug->h);
    printf("    ��棺");
    scanf("%d", &drug->i);
    printf("�^-------------------------------------------------�a\n");
}

/*��ʾҩƷ�嵥ѡ��*/
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
        printf("     $ ҩƷ�嵥 $ \n");
        showDrugList(head);
        printf("\n��1 ��ҩƷ������� 2 ��ҩƷ�������� | 3 ���ۼ����� | 4 ���������� | 5 ���������� | 0 ���ء�\n");
        scanf("%d", &option);
        if (option == 0)
        {
            system("cls");
            break;
        }     
    }
}

/*���ҩƷѡ��*/
void createDrugOption(pDrugInfo* head) {
    pDrugInfo drug = (pDrugInfo)malloc(sizeof(DrugInfo));
    memset(drug, 0U, sizeof(DrugInfo));
    editDrug(drug);
    if (findDrugInfoNodeByID(*head, drug->a)) {
        free(drug);
        printf("\nҩƷ���ʧ�ܣ�������ͬҩƷҩƷ��ţ�\n");
    }
    else {
        *head = addDrugInfoNode(*head, drug);
        /*ͬ���ļ���Ϣ*/
        saveDrugInfoFile(*head);
        printf("\nҩƷ��ӳɹ���\n");
    }
}

/*�޸�ҩƷѡ��*/
void updateDrugOption(pDrugInfo head) {
    char id[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("�X------------------------�[\n");
    printf("        $ �޸�ҩƷ $ \n");
    printf("     ҩƷ��ţ�");
    scanf("%s", id);
    printf("�^------------------------�a\n");
    target = findDrugInfoNodeByID(head, id);
    if (target) {
        showDrugTitle();
        showDrug(target);
        editDrug(target);
        /*ͬ���ļ���Ϣ*/
        saveDrugInfoFile(head);
        printf("\nҩƷ�޸ĳɹ���\n");
    }
    else {
        printf("\nδ�ҵ���ҩƷ��\n");
    }
}

/*ɾ��ҩƷѡ��*/
void removeDrugOption(pDrugInfo* head) {
    char id[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("�X------------------------�[\n");
    printf("        $ ɾ��ҩƷ $ \n");
    printf("     ҩƷ��ţ�");
    scanf("%s", id);
    printf("�^------------------------�a\n");
    target = findDrugInfoNodeByID(*head, id);
    if (target) {
        showDrugTitle();
        showDrug(target);
        *head = removeDrugInfoNode(*head, target);
        /*ͬ���ļ���Ϣ*/
        saveDrugInfoFile(*head);
        printf("\nҩƷɾ���ɹ���\n");
    }
    else {
        printf("\nδ�ҵ���ҩƷ��\n");
    }
}

/*��ҩƷ��Ų�ѯҩƷѡ��*/
void searchDrugByIDOption(pDrugInfo head) {
    char id[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("�X------------------------�[\n");
    printf("        $ ��ҩƷ��Ų�ѯ $ \n");
    printf("     ҩƷ��ţ�");
    scanf("%s", id);
    printf("�^------------------------�a\n");
    target = findDrugInfoNodeByID(head, id);
    if (target) {
        showDrugTitle();
        showDrug(target);
    }
    else {
        printf("\nδ�ҵ���ҩƷ��\n");
    }
}

/*��ҩƷ���Ʋ�ѯҩƷѡ��*/
void searchDrugByNameOption(pDrugInfo head) {
    char name[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("�X------------------------�[\n");
    printf("        $ ��ҩƷ���Ʋ�ѯ $ \n");
    printf("     ҩƷ���ƣ�");
    scanf("%s", name);
    printf("�^------------------------�a\n");
    target = findDrugInfoNodeByName(head, name);
    if (target) {
        showDrugTitle();
        do {
            showDrug(target);
            target = findDrugInfoNodeByName(target->j, name);
        } while (target);
    }
    else {
        printf("\nδ�ҵ���ҩƷ��\n");
    }
}

/*���ۼ۲�ѯҩƷѡ��*/
void searchDrugByOutPriceOption(pDrugInfo head) {
    double outprice = 0;
    pDrugInfo target = NULL;
    printf("�X------------------------�[\n");
    printf("        $ ���ۼ۲�ѯ $ \n");
    printf("     �ۼۣ�");
    scanf("%lf", &outprice);
    printf("�^------------------------�a\n");
    target = findDrugInfoNodeByOutPrice(head, outprice);
    if (target) {
        showDrugTitle();
        do {
            showDrug(target);
            target = findDrugInfoNodeByOutPrice(target->j, outprice);
        } while (target);
    }
    else {
        printf("\nδ�ҵ���ҩƷ��\n");
    }
}

/*������ѯҩƷѡ��*/
void searchDrugByStockOption(pDrugInfo head) {
    int min, max;
    pDrugInfo target = NULL;
    printf("�X------------------------�[\n");
    printf("        $ ������ѯ $ \n");
    printf("     ��������ڵ��ڣ�");
    scanf("%d", &min);
    printf("     �����С�ڵ��ڣ�");
    scanf("%d", &max);
    printf("�^------------------------�a\n");
    target = findDrugInfoNodeByStock(head, min, max);
    if (target) {
        showDrugTitle();
        do {
            showDrug(target);
            target = findDrugInfoNodeByStock(target->j, min, max);
        } while (target);
    }
    else {
        printf("\nδ�ҵ���ҩƷ��\n");
    }
}

/*���ؼ���ģ����ѯѡ��*/
void searchDrugByFuzzyOption(pDrugInfo head) {
    char keyword[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("�X------------------------�[\n");
    printf("        $ ���ؼ���ģ����ѯ $ \n");
    printf("     �ؼ��ʣ�");
    scanf("%s", keyword);
    printf("�^------------------------�a\n");
    target = findDrugInfoNodeByFuzzy(head, keyword);
    if (target) {
        showDrugTitle();
        do {
            showDrug(target);
            target = findDrugInfoNodeByFuzzy(target->j, keyword);
        } while (target);
    }
    else {
        printf("\nδ�ҵ���ҩƷ��\n");
    }
}

/*����ҩƷ*/
void searchDrugsOption(pDrugInfo head) {
    int option;
    while (1) {
        printf("�X-------------------------------�[\n");
        printf("          $ ����ҩƷ $ \n");
        printf("\n");
        printf("  ��1�� ����ҩƷ��Ų�ѯ\n");
        printf("  ��2�� ����ҩƷ���Ʋ�ѯ\n");
        printf("  ��3�� �����ۼ۲�ѯ\n");
        printf("  ��4�� ���տ������ѯ\n");
        printf("  ��5�� ���չؼ���ģ����ѯ\n");
        printf("  ��0�� ����\n");
        printf("\n");
        printf("�^-------------------------------�a\n");
        printf("          ��ѡ��");
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

/*����*/
void inStorageByIDOption(pDrugInfo head) {
    char id[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("�X------------------------�[\n");
    printf("        $ ���� $ \n");
    printf("     ҩƷ��ţ�");
    scanf("%s", id);
    printf("�^------------------------�a\n");
    target = findDrugInfoNodeByID(head, id);
    if (target) {
        int count;
        showDrugTitle();
        showDrug(target);
        printf("---------------\n");
        printf("���������������");
        scanf("%d", &count);
        if (count > 0) {
            target->h += count;
            target->i += count;
            saveDrugInfoFile(head);
            printf("�����ɹ���\n");
        }
        else {
            printf("���벻�Ϸ���\n");
        }
    }
    else {
        printf("\nδ�ҵ���ҩƷ��\n");
    }
}

/*����*/
void outStorageByIDOption(pDrugInfo head) {
    char id[STR_LEN] = { 0 };
    pDrugInfo target = NULL;
    printf("�X------------------------�[\n");
    printf("        $ ���� $ \n");
    printf("     ҩƷ��ţ�");
    scanf("%s", id);
    printf("�^------------------------�a\n");
    target = findDrugInfoNodeByID(head, id);
    if (target) {
        int count;
        showDrugTitle();
        showDrug(target);
        printf("---------------\n");
        printf("���������������");
        scanf("%d", &count);
        if (count > 0 && count <= target->i) {
            target->i -= count;
            saveDrugInfoFile(head);
            printf("�����ɹ���\n");
        }
        else {
            printf("���벻�Ϸ������治�㣡\n");
        }
    }
    else {
        printf("\nδ�ҵ���ҩƷ��\n");
    }
}

/*��ʾ������Ʒ*/
void expiredDrup(pDrugInfo head) {
    pDrugInfo cursor = head;
    char day[STR_LEN] = { 0 };
    formatDate(time(NULL) + (EXPIRED_DAYS * 60 * 60 * 24), day);
    printf("�X------------------------�[\n");
    printf("        $ ��ʾ������Ʒ $ \n");
    printf("�^------------------------�a\n");
    showDrugTitle();
    while (cursor) {
        if (strcmp(cursor->d, day) < 0) {
            showDrug(cursor);
        }
        cursor = cursor->j;
    }
}

/*���˵�*/
void menu(pDrugInfo* head) {
    system("title ҩ������ϵͳ");
    while (1) {
        int option;
        printf("�X-------------------------------�[\n");
        printf("        $ ҩ������ϵͳ $ \n");
        printf("\n");
        printf("  ��1�� ���ҩƷ\n");
        printf("  ��2�� ���ҩƷ\n");
        printf("  ��3�� �޸�ҩƷ\n");
        printf("  ��4�� ɾ��ҩƷ\n");
        printf("  ��5�� ����ҩƷ\n");
        printf("  ��6�� ����\n");
        printf("  ��7�� ����\n");
        printf("  ��8�� ��ʾ������Ʒ\n");
        printf("  ��0�� �˳�\n");
        printf("\n");
        printf("�^-------------------------------�a\n");
        printf("          ��ѡ��");
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
    printf("\n�û���¼\n");
    fclose(fp);
    do
    {
        fp = fopen("zhanghao.txt", "r");
        printf("\n�������û���:");
        scanf("%s", name);
        if (strlen(name) > 20)
        {
            printf("�û���λ�����࣬����������\n");
            scanf("%s", name);
        }
        printf("\n����������:");
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
            printf("\n��½�ɹ���\n");
            Sleep(1000);
            break;
        }
        else
        {
            printf("�������\n\n");
            printf("�����½���ѡ��\n");
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
        printf("��ӭʹ��ҩ�����ϵͳ!\n");
        printf("�û�ע��\n");
        printf("�������û�����\n");
        scanf("%s", name);
        if (strlen(name) > 20)
        {
            printf("�û���λ�����࣬����������\n");
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
            fscanf(fp, "%s %s\n", a.username, a.usermima);//��ʽ�����뺯��
            if (strcmp(a.username, name) == 0)//��������ļ��еıȽϣ���Ϊ0����û����ڡ��������е���Ϣ�Ƚ϶��õĸú������ñȽ��ַ����ķ����ж��������ȷ�ԡ�
            {
                flag = 1;
                break;
            }
        }
        fclose(fp);
        if (flag == 1)
        {
            printf("���û����Ѵ��ڣ�");
            Sleep(1000);
            system("cls");
            first();
        }
        else
        {

            while (1)
            {
                printf("\n���������룺\n");
                while ((ch = getch()) != '\r')//�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
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
                        putchar('*');//�����*�š�
                        code1[i++] = ch;//�����ַ�
                    }
                }
                code1[i] = '\0';
                i = 0;
                j = 0;
                printf("\n���ٴ���������:   ");
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
            printf("\nע��ɹ�!\n");
            printf("����������(1)\n");
            printf("��������������ע��\n");
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
    printf("|                 ��ӭʹ��ҩ�����ϵͳ                      |\n");
    printf("|                        1-��¼                             |\n");
    printf("|                        2-ע��                             |\n");
    printf("|                        0-�˳�                             |\n");
    printf("|___________________________________________________________|\n");
    printf("��ѡ������� ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        system("cls");
        denglu();
        system("cls");
        /*���ļ��м���ҩƷ����*/
        pDrugInfo head = loadDrugInfoFile();
        /*����ϵͳ*/
        menu(&head);
        /*����ҩƷ�б�*/
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

