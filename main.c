#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <locale.h>
#define Dosya_Yolu "C:/Users/Acer/Desktop/Universite/"
void etiketBul(FILE *dosya,FILE *tutma, FILE *tut, FILE *etiket)
{
    DIR *directory;
    DIR *directory1;
    struct dirent *entry;
    struct dirent *entry1;
    directory = opendir(Dosya_Yolu);
    wchar_t ch;
    char ch1[100];

    int i=0;
    tutma = fopen("tutma.txt","w+");
    tut = fopen("tut.txt","w+");



    while ((entry = readdir(directory))!=NULL)
    {
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0 )
            continue;
        //if(strstr(entry->d_name,".txt")==NULL)
        // continue;
        char path_[100]= {0};

        strcat(path_,Dosya_Yolu);
        strcat(path_, entry->d_name);
        strcat(path_,"/");
        directory1=opendir(path_);

        while((entry1=readdir(directory1))!=NULL)

        {


            char path1_[100]= {0};
            strcat(path1_,path_);
            if(strcmp(entry1->d_name,".")==0 || strcmp(entry1->d_name,"..")==0 )
                continue;
            if(strstr(entry1->d_name,".txt")==NULL)
                continue;
            strcat(path1_, entry1->d_name);
            if((dosya=fopen(path1_,"r"))!=NULL)
            {

                while(!feof(dosya))
                {
                    ch = fgetc(dosya);

                    if(ch=='[')
                    {
                        ch=fgetc(dosya);
                        if(ch=='[')
                        {
                            ch=fgetc(dosya);
                            while(ch!=']')
                            {

                                fprintf(tutma,"%c",ch);
                                fprintf(tut,"%c",ch);
                                ch = fgetc(dosya);

                            }

                            printf(" ");
                            fprintf(tutma,"\n");
                            fprintf(tut,"\n");


                        }
                    }




                }



            }
        }

    }

    closedir(directory);
    fclose(tutma);
    fclose(tut);
    tutma = fopen("tutma.txt","r");
    etiket = fopen("etiket.txt","w+");

    fflush(stdin);
    while(!feof(tutma))
    {
        char tut1[1000]= {0};
        fgets(tut1,512,tutma);
    int a=0;

     fseek(etiket,0,SEEK_SET);
        char tut3[1000]= {0};
        while(fgets(tut3,512,etiket)!=NULL)
        {






            if((strstr(tut1,tut3))!=NULL )
            {
                a=1;
                continue;
            }

        }
        if(a==0)
        {
            fprintf(etiket,"%s",tut1);
        }
}
fclose(tutma);
fclose(tut);
fclose(etiket);

}


void yetimBul(FILE *dosya, FILE *yetim, FILE *yetim1,FILE *etiket)
{
    DIR *directory;
    DIR *directory1;
    struct dirent *entry;
    struct dirent *entry1;
    directory = opendir(Dosya_Yolu);
    yetim1 = fopen("yetim1.txt","w+");
    wchar_t ch1;


    while ((entry = readdir(directory))!=NULL)
    {
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0 )
            continue;
        //if(strstr(entry->d_name,".txt")==NULL)
        // continue;
        char path_[100]= {0};

        strcat(path_,Dosya_Yolu);
        strcat(path_, entry->d_name);
        strcat(path_,"/");
        directory1=opendir(path_);
        while((entry1=readdir(directory1))!=NULL)
        {
            char path1_[100]= {0};
            strcat(path1_,path_);
            if(strcmp(entry1->d_name,".")==0 || strcmp(entry1->d_name,"..")==0 )
                continue;
            if(strstr(entry1->d_name,".txt")==NULL)
                continue;
            char yetimtut[100]= {0};
            strcpy(yetimtut, entry1->d_name);
            strcat(path1_, yetimtut);
            yetim = fopen("yetim.txt","w+");

            fprintf(yetim,"%s ",yetimtut);
            fseek(yetim,0,SEEK_SET);
            while(!feof(yetim))
            {
                ch1=fgetc(yetim);

                if(ch1=='.')
                    break;

                else
                {
                    fprintf(yetim1,"%c",ch1);

                }


            }
            fprintf(yetim1,"\n");




        }
    }
    closedir(directory);

    fclose(yetim);
    fclose(yetim1);

    etiket = fopen("etiket.txt","r+");
    yetim1 = fopen("yetim1.txt","r+");
    int m=0;
    int n=0;


    printf("Yetim etiketler listesi: \n");
    while(!feof(etiket))
    {

        wchar_t yetimTut1[100]= {0};
        fgets(yetimTut1,"%s",etiket);
        fseek(yetim1,0,SEEK_SET);


        while(!feof(yetim1))
        {

            char yetimTut2[100]= {0};
            fgets(yetimTut2,"%s",yetim1);
            n++;
            if(strstr(yetimTut1,yetimTut2)!=NULL)
            {
                continue;
            }
            else if(strstr(yetimTut1,yetimTut2)==NULL)
            {
                m++;
            }
        }


        if(m==n-1)
        {
             printf("%s",yetimTut1);
        }
         m=0;
         n=0;
    }
        printf("------------------------------ \n");
        printf("                           Istenen etiketler listesi: \n");
        fseek(yetim1,0,SEEK_SET);
         while(!feof(yetim1))
    {

        wchar_t yetimTut1[100]= {0};
        fgets(yetimTut1,"%s",yetim1);
        fseek(etiket,0,SEEK_SET);


        while(!feof(etiket))
        {

            char yetimTut2[100]= {0};
            fgets(yetimTut2,"%s",etiket);
            n++;
            if(strstr(yetimTut1,yetimTut2)!=NULL)
            {
                continue;
            }
            else if(strstr(yetimTut1,yetimTut2)==NULL)
            {
                m++;
            }
        }
        if(m==n-1)
        {
             printf("%s",yetimTut1);
        }
         m=0;
         n=0;

    }




    fclose(etiket);
    fclose(yetim1);
}




void Arama(FILE *dosya)
{

    DIR *directory;
    DIR *directory1;
    struct dirent *entry;
    struct dirent *entry1;
    char yazi[50][20];
    directory = opendir(Dosya_Yolu);
    wchar_t kelime[200];
    wchar_t a[100];
    int num=0;
    int adet=0;
    int line_num = 1;


    printf("Aranacak Kelimeyi giriniz: ");
    fflush(stdin);
    gets(a);
    int uzunluk = strlen(a);



    while ((entry = readdir(directory))!=NULL)
    {
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0 )
            continue;
        if(strstr(entry->d_name,".")!=NULL)
            continue;
        char path_[100]= {0};

        strcat(path_,Dosya_Yolu);
        strcat(path_, entry->d_name);
        strcat(path_,"/");
        directory1=opendir(path_);
        while((entry1=readdir(directory1))!=NULL)
        {
            char path1_[100]= {0};
            strcat(path1_,path_);
            if(strcmp(entry1->d_name,".")==0 || strcmp(entry1->d_name,"..")==0 )
                continue;
            if(strstr(entry1->d_name,".txt")==NULL)
                continue;
            strcat(path1_, entry1->d_name);
            if((dosya=fopen(path1_,"r"))!=NULL)
            {
                while ( fgets(kelime,512,dosya)!=NULL)
                {



                    if(strstr(kelime, a)!=NULL)
                    {
                        num++;
                        adet++;

                        printf("%d. Satirda Bulundu.\n", line_num);




                    }
                    line_num++;


                }
                printf("%s içinde %d tane var\n",path1_,adet);
                adet=0;
                line_num=1;


            }

            int i=0;

        }







    }
    closedir(directory);


}
void Guncelleme(FILE *dosya,FILE *kontrolF)
{
    DIR *directory;
    DIR *directory1;
    struct dirent *entry;
    struct dirent *entry1;
    char ch;
    directory = opendir(Dosya_Yolu);
    wchar_t degistirilecek[100]= {0};
    wchar_t degistir[100]= {0};
    wchar_t degistirTut[100]= {0};
    wchar_t degistirTut1[100]= {0};
    kontrolF = fopen("C:/Users/Acer/Desktop/Universit/kontrol.txt","w+");
    printf("Değiştirilecek Etiketi Yazınız\n");
    fflush(stdin);
    gets(degistirilecek);
    printf("Etiketin Değişeceği Kelimeyi Yazınız\n");
    gets(degistir);
    printf("%s-%s",degistirilecek,degistir);




    while ((entry = readdir(directory))!=NULL)
    {
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0 )
            continue;
        //if(strstr(entry->d_name,".txt")==NULL)
        // continue;
        char path_[100]= {0};

        strcat(path_,Dosya_Yolu);
        strcat(path_, entry->d_name);
        strcat(path_,"/");
        directory1=opendir(path_);
        while((entry1=readdir(directory1))!=NULL)
        {
            char path1_[100]= {0};
            strcat(path1_,path_);
            if(strcmp(entry1->d_name,".")==0 || strcmp(entry1->d_name,"..")==0 )
                continue;
            if(strstr(entry1->d_name,".txt")==NULL)
                continue;
            strcat(path1_, entry1->d_name);

            if((dosya=fopen(path1_,"r"))!=NULL)
            {
                while(!feof(dosya))
                {
                    fgets(degistirTut,"%s",dosya);
                    if(strstr(degistirTut,degistirilecek)!=NULL)
                    {

                        printf("%s",degistir);
                        fprintf(kontrolF,"%s ",degistir);
                    }
                    else if(strstr(degistirTut,degistirilecek)==NULL)
                    {
                        fprintf(kontrolF,"%s ",degistirTut);
                    }
                }
                //fclose(path1_);
                //fclose("C:/Users/Acer/Desktop/Universit/kontrol.txt");
                //remove(path1_);
                //rename("C:/Users/Acer/Desktop/Universit/kontrol.txt",path1_);
            }



        }

    }
}

void OutputText(FILE *dosya, FILE *tutma, FILE *output, FILE *tut)
{
    DIR *directory;
    DIR *directory1;
    struct dirent *entry;
    struct dirent *entry1;
    directory = opendir(Dosya_Yolu);
    wchar_t ch;
    char ch1[100];

    int i=0;
    tutma = fopen("tutma.txt","w+");
    tut = fopen("tut.txt","w+");



    while ((entry = readdir(directory))!=NULL)
    {
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0 )
            continue;
        //if(strstr(entry->d_name,".txt")==NULL)
        // continue;
        char path_[100]= {0};

        strcat(path_,Dosya_Yolu);
        strcat(path_, entry->d_name);
        strcat(path_,"/");
        directory1=opendir(path_);

        while((entry1=readdir(directory1))!=NULL)

        {


            char path1_[100]= {0};
            strcat(path1_,path_);
            if(strcmp(entry1->d_name,".")==0 || strcmp(entry1->d_name,"..")==0 )
                continue;
            if(strstr(entry1->d_name,".txt")==NULL)
                continue;
            strcat(path1_, entry1->d_name);
            if((dosya=fopen(path1_,"r"))!=NULL)
            {

                while(!feof(dosya))
                {
                    ch = fgetc(dosya);

                    if(ch=='[')
                    {
                        ch=fgetc(dosya);
                        if(ch=='[')
                        {
                            ch=fgetc(dosya);
                            while(ch!=']')
                            {

                                fprintf(tutma,"%c",ch);
                                fprintf(tut,"%c",ch);
                                ch = fgetc(dosya);

                            }

                            printf(" ");
                            fprintf(tutma,"\n");
                            fprintf(tut,"\n");


                        }
                    }




                }



            }
        }

    }

    closedir(directory);
    fclose(tutma);
    fclose(tut);
    tutma = fopen("tutma.txt","r");

    output = fopen("output.txt","w+");
    int tane=0;
    int a=0;

    fflush(stdin);
    while(!feof(tutma))
    {
        char tut1[1000]= {0};
        fgets(tut1,512,tutma);

        tut = fopen("tut.txt","r");

        while(!feof(tut))
        {
            char tut2[1000]= {0};
            fgets(tut2,512,tut);

            if(strstr(tut1,tut2)!=NULL && tut1!=NULL)
            {


                tane++;
            }







        }

        fseek(output,0,SEEK_SET);
        char tut3[1000]= {0};
        while(fgets(tut3,512,output)!=NULL)
        {






            if((strstr(tut1,tut3))!=NULL || 'tut3'==tane)
            {
                a=1;
                continue;
            }

        }
        if(a==0)
        {
            fprintf(output,"%s %d \n",tut1,tane-1);
        }







        tane = 0;
        a=0;

    }
    fclose(tutma);
    fclose(tut);
    fclose(output);

    remove("tutma.txt");
    remove("tut.txt");

    printf("-------------------------------- \n");
    output=fopen("output.txt","r");
    while(!feof(output))
    {
        char yazdir[100]= {0};
        fgets(yazdir,512,output);
        printf("Etiket: %s ",yazdir);
        fgets(yazdir,512,output);
        printf("Adet: %s ",yazdir);

    }





}



int main()
{


    FILE *dosya;
    FILE *tutma;
    FILE *output;
    FILE *tut;
    FILE *kontrolF;
    FILE *yetim;
    FILE *yetim1;
    FILE *etiket;
    int deger;
    char c;


    char fileName[255];
    const char *ss;



 while(1)
 {
    etiketBul(dosya,tutma,tut,etiket); // Her aramadan önce istenen ve yetim etiketler listelensin diye while içine koydum.
    yetimBul(dosya,yetim,yetim1,etiket); // Fonksiyonu çalıştırdıktan sonra eğer arama gibi şeyleri çalıştırdıysanız biraz üstte kalacaktır teşekkürler.

    printf("---------------------------------------------\n");
    printf("Bir Deðer giriniz:\n");
    printf("1-)Arama\n2-)Güncelleme\n3-)Output olustur\n0-)Exit\n");
    scanf("%d",&deger);


    switch(deger)
    {
    case 1:
        Arama(dosya);
        break;


    case 2:
        Guncelleme(dosya,kontrolF);
        break;


    case 3:
        OutputText(dosya,tutma,output,tut);
        break;

    case 0:
           exit(0);
    }
 }













    return 0;
}
