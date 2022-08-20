#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
#include "bt-5.0.1/inc/btree.h"

#define WORD_LENGHT 255
#define MEANING_LENGHT 10000

void separate_mean(char mean[MEANING_LENGHT]);
int convert_text_to_bt(char *file);
int file_exists(char *pathname);

void menu(){
    printf("\n\n\n\n\t\t\t===========MeNu===============\n");
    printf("\t\t\t+%4s1.Nhap de tra tu.%6s +\n"," ", " ");
    printf("\t\t\t+%4s2.Thoat chuong trinh.%2s +\n"," "," ");
    printf("\t\t\t==============================\n");
    printf("...........Lua chon cua ban: ");

}
void menu1(){
    printf("\n\n\n\n\t\t\t===========MENU================\n");
    printf("\t\t\t+%4s1.Xoa khoi tu dien.%5s +\n"," ", " ");
    printf("\t\t\t+%4s2.Update nghia cua tu.%3s+\n"," ", " ");
    printf("\t\t\t+%4s3.Quay lai.%13s +\n"," "," ");
    printf("\t\t\t===============================\n");
    printf("...........Lua chon cua ban: ");

}
void menu2(){
    printf("\n\n\n\n\t\t\t===========MENU================\n");
    printf("\t\t\t+%4s1.Them vao tu dien.%5s +\n"," ", " ");
    printf("\t\t\t+%4s2.Quay lai.%13s +\n"," "," ");
    printf("\t\t\t===============================\n");
    printf("...........Lua chon cua ban: ");

}


int main()
{
    BTA *data;
    btinit();//khoi tao cay btree
    //Khoi tao lan dau
    if (!file_exists("resource.dat")) {       
        convert_text_to_bt("AnhViet.txt");
    }
    data = btopn("resource.dat", 0, 0);

    int scan, chon1, chon2;

    char anh[WORD_LENGHT];
    char viet[MEANING_LENGHT];
    int size;
    
    do
    {
        menu();
        scanf("%d",&scan);
        __fpurge(stdin);
        while (scan != 1 && scan != 2)
        {
            printf("Nhap sai!!!(chi duoc nhap 1 hoac 2), moi nhap lai: ");
            scanf("%d", &scan);
            __fpurge(stdin);
        }
        switch(scan)
        {
            case 1: 
                printf("Nhap tu tieng anh: ");
                __fpurge(stdin);
                fgets(anh,WORD_LENGHT,stdin);
                anh[strlen(anh)-1] = 0;
                if(btsel(data,anh,viet,MEANING_LENGHT * sizeof(char),&size) == 0)
                {
                    printf("Nghia cua tu %s la :\n %s\n", anh, viet);
                    do
                    {
                        menu1();
                        scanf("%d",&chon1);
                        __fpurge(stdin);
                        while (chon1 != 1 && chon1 != 2 && chon1 !=3)
                        {
                            printf("Nhap sai!!!(chi duoc nhap tu 1 den 3), moi nhap lai: ");
                             scanf("%d", &chon1);
                             __fpurge(stdin);
                        }
                        switch(chon1)
                        {
                            case 1: 
                                if(btdel(data,anh) == 0)
                                {
                                    printf("Xoa thanh cong.\n");
                                }else{
                                    printf("Xoa that bai.\n");
                                }
                                break;
                            case 2:
                                printf("Nhap nghia cua tu %s : ", anh);
                                __fpurge(stdin);
                                fgets(viet, MEANING_LENGHT,stdin);
                                viet[strlen(viet)-1] = 0;
                                if(btupd(data,anh,viet,MEANING_LENGHT) == 0)
                                {
                                    printf("Update thanh cong.\n");
                                }else
                                {
                                    printf("Update that bai.\n");
                                }
                                break;
                            case 3:
                               // printf("\t\t\tCam on!\n");
                                break;
                        }
     
                    }while(chon1 != 3);  
                }else
                {
                    printf("\t\tKhong tim thay tu nay.\n");
                    do
                    {
                        menu2();
                        scanf("%d",&chon2);
                        __fpurge(stdin);
                        while (chon2 != 1 && chon2 != 2)
                        {
                            printf("Nhap sai!!!(chi duoc nhap 1 hoac 2), moi nhap lai: ");
                            scanf("%d", &chon2);
                            __fpurge(stdin);
                        }
                        switch(chon2)
                        {
                            case 1: 
                                printf("Nhap nghia cua tu %s : ", anh);
                                __fpurge(stdin);
                                fgets(viet, MEANING_LENGHT,stdin);
                                viet[strlen(viet)-1] = 0;
                                if(btins(data,anh,viet,10000*sizeof(char)) == 0)
                                {
                                    printf("Them vao thanh cong.\n");
                                }else{
                                    printf("Them vao that bai.\n");
                                }
                                break;
            
                            case 2:
                               // printf("\t\t\tCam on!\n");
                                break;
                        }
     
                    }while(chon2 != 2);  

                }

                break;
            case 2:
                printf("\t\t\tCam on ban da su dung phan mem!\n");
                break;
        }
     
    }while(scan != 2);  

    btcls(data);
    return 0;    
}

void separate_mean(char mean[MEANING_LENGHT])
{
    int m = 0;
    int n = 1;
    while (mean[n] != '\0')
    {
        if (mean[n] == '\\' && mean[n + 1] == 'n')
        {
            mean[m++] = '\n';
            n += 2;
        }
        else
        {
            if (m != n)
                mean[m++] = mean[n++];
            else
            {
                n++;
                m++;
            }
        }
    }
    mean[m] = '\0';
}

int convert_text_to_bt(char *file)
{
    FILE *data;
    if ((data = fopen(file, "r")) == NULL)
    {
        printf("Khong mo duoc file\n");
        return 0;
    }

    BTA *convert;
    convert = btcrt("resource.dat", 0, 0);  //?

    char word[WORD_LENGHT], mean[MEANING_LENGHT];
    int line;   //?

    while (fscanf(data, "%[^\t]", word) == 1)
    {
        fgets(mean, MEANING_LENGHT, data);
        line++;
        separate_mean(mean);
        btins(convert, word, mean, strlen(mean) + 1);
    }
    
    printf("%d lines.\n", line);
    btcls(convert);
    fclose(data);
    return 1;
}

int file_exists(char *pathname)
{
    FILE* f;

    f = fopen(pathname,"r");
    if (f == NULL) {
        return FALSE;
    }
    else {
        fclose(f);
    }
    return TRUE;
}
