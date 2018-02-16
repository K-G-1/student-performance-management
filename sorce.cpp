/**
 * Date: 2018/2/16
 * Author:K.G.
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h> //sleep()头文件


#define file "data.txt"
#define LEN sizeof(struct  student)
#define FORMAT "%-8d%-15s%5.1f%12.1f%10.1f%9.2f\n"
#define DATA stu[i].num,stu[i].name,stu[i].elec,stu[i].expe,stu[i].requ,stu[i].sum


struct student{
    int num;/*number*/
    char name[15];/*name*/
    double elec;/*elective*/
    double expe;/*experiment*/
    double requ;/*required*/
    double sum;/*sum grade*/
};

struct student stu[50];

void menu();    /*manu function*/
void in();      /*input students'grade's informations*/
void show();    /*show students'informations*/
void modify();  /*modify record*/
void del();     /*delete students'grade's informations*/
void search();  /*search record */
void order();/*paixu*/
/**
 * main function
 * @Author   KG
 * @DateTime 2018-02-16
 */
int main()
{
    int in_put_num;
    menu();
    scanf("%d",&in_put_num);
    while(1){
        switch(in_put_num){
            case 0:
                in();
                break;
            case 1:
                show();
                break;
            case 2:
                modify();
                break;
            case 3:
                del();
                break;
            case 4:
                search();
                break;
            case 5:
                order();
                break;
            default:
                printf("error input");
                break;
        }
        if(getchar() == '\n')
            getchar();
        menu();
        scanf("%d",&in_put_num);
    }
    return 0;
}


void menu()
{
    system("clear");
    printf("\n");
    printf("\t\t|--------------------STUDENT---------------|-------------|\n");
    printf("\t\t|\t0.input record                     |             |\n");
    printf("\t\t|\t1.show record                      |             |\n");
    printf("\t\t|\t2.modity record                    |             |\n");
    printf("\t\t|\t3.delete record                    |             |\n");
    printf("\t\t|\t4.search record                    |             |\n");
    printf("\t\t|\t5.order record                     |             |\n");
    printf("\t\t|------------------------------------------|-------------|\n\n");
    printf("\t\tchoose(0-5):");
}

void in()
{
    FILE *fp=NULL;/*define the file pointer*/
    int m =0;
    int i =0;
    char ch ;

    system("clear");

    if ((fp = fopen(file, "a+")) == NULL)/*open the file*/
    {
        printf("can not open.\n");
        return;
    }
    while (!feof(fp)) {
        if (fread(&stu[m], LEN, 1, fp) == 1)
            m++;/* records'sum*/
    }
    fclose(fp);
    if (m == 0)
        printf("NO record!\n");

    if ((fp = fopen(file, "wb")) == NULL) {
        printf("can not open\n");
        return;
    }
    for (i = 0; i < m; i++)
        fwrite(&stu[i], LEN, 1, fp);/*write the record in the file*/


    printf("please input (Y/N):");
    scanf("%c",&ch);
    if(ch == '\n')
        scanf("%c",&ch);
    printf("%c\n", ch);

    while (ch == 'Y'|| ch == 'y')/*whether input new record*/
    {
        printf("number:");
        scanf("%d", &stu[m].num);/*input student' number*/
        for (i = 0; i < m; i++)
            if (stu[i].num == stu[m].num) {
                printf("the number is existing ,press any to continue!");
                if(getchar() == '\n')
                    getchar();
                fclose(fp);
                return;
            }

        printf("name:");
        scanf("%s", stu[m].name);/*input student's name*/
        printf("elective:");
        scanf("%lf", &stu[m].elec);/*input student's elective subject*/
        printf("experiment:");
        scanf("%lf", &stu[m].expe);/*input student's experiment */
        printf("required course:");
        scanf("%lf", &stu[m].requ);/*input student's required course*/
        stu[m].sum = stu[m].elec + stu[m].expe + stu[m].requ;/*compute the sum*/


        if (fwrite(&stu[m], LEN, 1, fp) != 1)/*put the new record into the file*/
        {
            printf("can not save!");
            getchar();
        } else {
            printf("%s  saved!\n", stu[m].name);
            m++;
        }

        printf("continue ?(Y/N)");/*if continue*/
        scanf("%c", &ch);
        if(ch == '\n')
            scanf("%c", &ch);
    }
    fclose(fp);
    printf("OK!\n");

}


void show()
{
    FILE * fp;
    int i, m = 0;
    fp = fopen(file, "rb");
    while (!feof(fp)) {
        if (fread(&stu[m], LEN, 1, fp) == 1)
            m++;
    }
    fclose(fp);
    printf("number  name        elective  experiment  required      sum\t\n");
    for (i = 0; i < m; i++) {
        printf(FORMAT,DATA);/*将信息按指定格式打印*/
    }
}

void modify()
{
    FILE *fp=NULL;
    int i, j, m = 0, snum;
    int find_flag = 0;
    if ((fp = fopen(file, "r+")) == NULL) {
        printf("can not open\n");
        return;
    }
    while (!feof(fp))
        if (fread(&stu[m], LEN, 1, fp) == 1)
            m++;
    if (m == 0) {
        printf("no record!\n");
        fclose(fp);
        return;
    }
    show();
    printf(
            "please input the number of the student which do you want to modify!\n");
    printf("modify number:");
    scanf("%d", &snum);

    for (i = 0; i < m; i++)
        if (stu[i].num == snum)/*if having change*/
        {
            find_flag = 1;
            break;
        }
            
    if(find_flag == 0)
    {
        printf("%s\n","NO found" );
        return;
    }
        
    // printf("%s\n","到此为止");
    printf("find the student !you can modify!\n");
    printf("name:");
    scanf("%s", stu[i].name);
    printf("elective:");
    scanf("%lf", &stu[i].elec);
    printf("experiment:");
    scanf("%lf", &stu[i].expe);
    printf("required course:");
    scanf("%lf", &stu[i].requ);
    printf("modify successfully!");
    stu[i].sum = stu[i].elec + stu[i].expe + stu[i].requ;
    if ((fp = fopen(file, "wb")) == NULL) {
        printf("can not open\n");
        return;
    }
    for (j = 0; j < m; j++){
        if (fwrite(&stu[j], LEN, 1, fp) != 1) {
            printf("can not save!\n");
            getchar();
        }
    }
        
    fclose(fp);

}


void del()
{
    FILE *fp=NULL;
    int i, j, m = 0, snum;
    int find_flag = 0;
    char ch;
    if ((fp = fopen(file, "r+")) == NULL) {
        printf("can not open\n");
        return;
    }
    while (!feof(fp))
        if (fread(&stu[m], LEN, 1, fp) == 1)
            m++;
    if (m == 0) {
        printf("no record!\n");
        fclose(fp);
        return;
    }
    show();

    printf(
            "please input the number of the student which do you want to del!\n");
    printf("del number:");
    scanf("%d", &snum);

    for (i = 0; i < m; i++)
        if (stu[i].num == snum)/*if having change*/
        {
            find_flag = 1;
            break;
        }
            
    if(find_flag == 0)
    {
        printf("%s\n","NO found" );
        return;
    }

    printf("find the student ,delete?(Y/N)");
    scanf("%s", &ch);
    if(ch == '\n')
      scanf("%s", &ch);
    
    if (strcmp(&ch, "Y") == 0 || strcmp(&ch, "y") == 0)/*if go to delete*/
        for (j = i; j < m; j++)
            stu[j] = stu[j + 1];/*transform  records*/
    m--;/*record 自减*/
    if ((fp = fopen(file, "wb")) == NULL) {
        printf("can not open \n");
        return;
    }
    for (j = 0; j < m; j++)/*write to the file again*/
        if (fwrite(&stu[j], LEN, 1, fp) != 1) {
            printf("can nor save!\n");
            getchar();
        }
    fclose(fp);
    printf("delete successfully!\n");  

}

void search()
{
    FILE *fp=NULL;
    int snum, i, m = 0;
    char ch;
    if ((fp = fopen(file, "rb")) == NULL) {
        printf("can not open\n");
        return;
    }
    while (!feof(fp))
        if (fread(&stu[m], LEN, 1, fp) == 1)
            m++;
    fclose(fp);
    if (m == 0) {
        printf("no record!\n");
        return;
    }
    printf("please input the number:");
    scanf("%d", &snum);

    for (i = 0; i < m; i++)
        if (stu[i].num == snum)/*check if the input number exist*/
        {
            printf("find the student ,show?(Y/N)");
            scanf("%c", &ch);
            if(ch == '\n')
                scanf("%c", &ch);
           
            if (ch == 'Y'||ch == 'y') {
                printf(
                        "number  name       elective   experiment  required   sum\t\n");
                printf(FORMAT, DATA);/* IN SOME WAY OUT THE RESURT*/
                break;
            }
        }
    if (i == m)
        printf("can not find the student !\n");
}

void order()
{
    FILE *fp=NULL;
    struct student t;
    int i = 0, j = 0, m = 0;
    if ((fp = fopen(file, "r+")) == NULL) {
        printf("can not open!\n");
        return;
    }
    while (!feof(fp))
        if (fread(&stu[m], LEN, 1, fp) == 1)
            m++;
    fclose(fp);
    if (m == 0) {
        printf("no record!\n");
        return;
    }
    if ((fp = fopen(file, "wb")) == NULL) {
        printf("can not open\n");
        return;
    }

    for (i = 0; i < m - 1; i++)
        for (j = i + 1; j < m; j++)/*成绩顺序交换*/
            if (stu[i].sum < stu[j].sum) {
                t = stu[i];
                stu[i] = stu[j];
                stu[j] = t;
            }
    if ((fp = fopen(file, "wb")) == NULL) {
        printf("can not open\n");
        return;
    }
    for (i = 0; i < m; i++)/*输入重排内容*/
        if (fwrite(&stu[i], LEN, 1, fp) != 1) {
            printf("%s can not save !\n",stu[i].name);
            getchar();
        }
    fclose(fp);
    printf("save successfully\n");
}
