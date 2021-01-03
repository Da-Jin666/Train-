#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>

#define n 5

int len=0;

//�˿���Ϣ
struct passenge                     
{
    char name[10];                 //����
    int  num;                      //����Ʊ��
}lg[n];                           //�ṹ������� 

//��Ʊ��Ϣ
typedef struct train                      
{
    char start_stat[20];          //��ʼվ
    char end_stat[20];            //�յ�վ
    char go_time[16];             //����ʱ�� 
    char go_data[16];             //��������
    char train_num[15];           //������Ϣ
    char all_time[16];            //��;ʱ��
    int  ticket_lea;               //��Ʊ����
}Train;              //�ѽṹ��struct train ���� Train 

typedef Train Item;    //�ְ�Train ���� Item��Ŀ���������ͨ��    ������ֻ��2 ������ ��Ŀ��ָ��  

struct node
{                        //node��һ���ڵ�   �ڵ������Ŀ��ָ�� 
	Item item;
	struct node *next;
};

//ע����Ϣ
void enroll()
{
	char a[100];                   //ע���û���
	char b[100];                   //ע������
	char s[100];                   //�ٴ�ȷ������
	int  len;
	
   	printf("�����������û�����");
	scanf("%s",a);
	
	printf("�������������룺");
			
	reset: scanf("%s",b);     //�õ���if goto��� 

	    len=strlen(b);    //��ȡ���볤�� 
	   
	   if(len>9)
		{
			printf("���볤�ȹ��������������ã�");
	      goto reset;    //if goto ���  
	    }
  	  printf("���ٴ����������õ����룺");
     	scanf("%s",s);
	
	if(strcmp(b,s) == 0)       //�ַ����ȽϺ��� 
	{
		FILE *fp;
		
		fp=fopen("register.txt","at");     //ѡ��׷�ӷ�ʽ�����Դ�����Ϣ
		
		if(fp == NULL)
		{
			printf("�ļ�������!");
			exit(1);                           
		}
		
		fprintf(fp,"%s %s\n",a,b);                    //�ַ���д�뺯������д�����
       
	    printf("\n\t------ע��ɹ�------\n");
		fclose(fp);
	}
	else if(strcmp(b,s) != 0)
	{
		printf("��������������벻һ�£��������������룡\n");
		goto reset;          //if goto ��� 
	}
}

//��½ҳ��
int land()
{
	int  i=0;      //i��Ϊ���ж����볤�� ������ 
	char a[10];                 
	char b[10];                   

	char user_name[10];           
	char user_passwords[10];      

	printf("�����������û�����");
	scanf("%s",user_name);

    printf("�������������룺");

	while(i<9 && (user_passwords[i] = getch()) && user_passwords[i] != '\r')   //������볬�� ���� �������з�������ѭ��
	{
		printf("*");   //�������� 
		i++;
	}
	
	user_passwords[i]=0;   //�ַ���������־ '/0' 
	
	FILE *fp;
	fp=fopen("register.txt","rt");       //�ִ��ļ� 
	
	if(fp==NULL)
	{
		printf("�ļ�������!");
		exit(1);
	}
	
	while(fscanf(fp,"%s %s",a,b)!=EOF)    //���ļ��ж��˺������Ƿ���ȷ 
	{    
		if(strcmp(a,user_name)==0  &&  strcmp(b,user_passwords)==0)   //�ַ����ȽϺ��������Ƿ���ȷ 
		 {
			printf("\n\t--------��½�ɹ�--------\n");
			printf("\t------��ӭ����ϵͳ------\n");
			return 0;
		 } 
	}
	if(1)
	{
		printf("\n��Ϣ�������\n");
	     land();
	}
	fclose(fp);
}

//����Ϣ���浽�ļ� 
void save_inf(struct node *pHead)             //�������е���Ϣ���浽�ƶ��ļ���
{                                         //ͷָ�벻���ƶ� 
    struct node *pTemp;   //��ΪҪһ���ڵ��ƶ� ���Զ���ΪpTemp�ƶ� 
    
	FILE *fp;
    fp=fopen("information.txt","at");    //���ļ� 
    
	if(fp==NULL)
    {
        printf("���ļ�ʧ�ܣ��ļ����ܲ����ڣ�\n");
        exit(1);
    }
                                                           //�������� 
    for(pTemp=pHead ; pTemp != NULL;pTemp=pTemp->next)      //�ڵ���ָ����Ŀ����Ŀ�������ҳ�Ա 
        
		fprintf(fp,"%s %s %s %s %s %s %d\n",pTemp->item.start_stat,pTemp->item.end_stat,
			pTemp->item.go_time,pTemp->item.go_data,pTemp->item.train_num,pTemp->item.all_time,pTemp->item.ticket_lea);
   
    fclose(fp);
} 

//���� 
struct node *add(struct node *pHead)
{
	   struct node *pNew;
	   struct node *current; 
	  
	    pNew=(struct node *)malloc(sizeof(struct node));      //�ٴη�������ڴ�ռ�
        
        pNew->next=pHead;    //�½��ָ��ԭ�����׽ڵ� 
        pHead=pNew;          //ͷָ��ָ���½��
        
        
        //β�巨;
		/*current=pHead;
		while(current->next!=NULL)
		{
			current=current->next;
		} 
		current->next=pNew;
		pNew->next=NULL;
        */
        
        printf("\n��������ʼվ��");
        scanf("%s",pNew->item.start_stat);
        printf("�������յ�վ��");
        scanf("%s",pNew->item.end_stat);
        printf("���������ʱ�䣺");
        scanf("%s",pNew->item.go_time);
        printf("������������ڣ�");
        scanf("%s",pNew->item.go_data);
        printf("�����복����Ϣ��");
        scanf("%s",pNew->item.train_num);
        printf("��������;ʱ�䣺");
        scanf( "%s",pNew->item.all_time);
        printf("��������Ʊ������");
        scanf("%d",&pNew->item.ticket_lea);
		
		current=pHead;
	
		while(current!=NULL){
			printf("%-10s",current->item.start_stat);
        	printf("%-10s",current->item.end_stat);
        	printf("%-12s",current->item.go_time);
        	printf("%-14s",current->item.go_data);
			printf("%-12s",current->item.train_num);
        	printf("%-13s",current->item.all_time);
        	printf("%-d",current->item.ticket_lea);
        	printf("\n");
        	current=current->next;
		}
		 
        return pHead;       //����ͷָ�� 
        
 } 
 

//�����ʾģ��
void output(struct node *pHead)
{
    struct node *pTemp;                 //ѭ�����õ���ʱָ��

	pTemp=pHead;                         //ָ��ĵ��׽���ָ��

    printf("\t******��Ʊ��Ϣ����******\n");
    printf("��ʼվ    �յ�վ    ����ʱ��    ��������     ������Ϣ     ��;ʱ��    ��Ʊ��\n");

    while((pTemp!=NULL))
    {
        printf("%-10s",pTemp->item.start_stat);
        printf("%-10s",pTemp->item.end_stat);
        printf("%-12s",pTemp->item.go_time);
        printf("%-14s",pTemp->item.go_data);
		printf("%-12s",pTemp->item.train_num);
        printf("%-13s",pTemp->item.all_time);
        printf("%-d",pTemp->item.ticket_lea);
        printf("\n");
        pTemp=pTemp->next;              //�ƶ���ʱָ�뵽��һ�����
    }

}

//��ѯ��Ʊ��Ϣ
int inquire(struct node *pHead)
{
	int flag = 0;
    struct node *pTemp; 
    
    char inquire_start[20],inquire_end[20];       //��ѯѡ�����ʼվ���յ�վ
  
    printf("������Ҫ��ѯ��Ʊ����ʼվ���յ�վ��");
    scanf("%s %s",inquire_start,inquire_end);
    
	pTemp=pHead;
    
    while(pTemp!=NULL)
    {
        if((strcmp(pTemp->item.start_stat,inquire_start)==0) && (strcmp(pTemp->item.end_stat,inquire_end)==0))
        {
        	flag = 1;
            printf("\n��Ʊ��Ϣ������£�\n");
            printf("��ʼվ    �յ�վ    ����ʱ��    ��������    ����    ��;ʱ��    ��Ʊ��\n");
            printf("%-10s",pTemp->item.start_stat);
        	printf("%-10s",pTemp->item.end_stat);
        	printf("%-12s",pTemp->item.go_time);
        	printf("%-14s",pTemp->item.go_data);
			printf("%-12s",pTemp->item.train_num);
        	printf("%-13s",pTemp->item.all_time);
        	printf("%-d",pTemp->item.ticket_lea);       
		}
           pTemp=pTemp->next;
           continue;
	}
	
	if(flag == 0)
    {
    	printf("�������\n");
		inquire(pHead);
	}
	return 0;
	} 
	
//��Ʊ	
	int buy(struct node *pHead)
{
    struct node *pTemp; 
    char   choice_start[20],choice_end[20];       /*��Ʊѡ�����ʼ���յ�վ*/
    int    numbers;                                /*��������*/
    char   buy_name[10];                          /*����������*/
    char   wy;
    
    pTemp=pHead; 
    printf("������������Ʊ����ʼվ���յ�վ��Ʊ����");
    scanf("%s %s %d",choice_start,choice_end,&numbers);
  
    while(pTemp!=NULL)
    {
        if((strcmp(pTemp->item.start_stat,choice_start)==0)&&(strcmp(pTemp->item.end_stat,choice_end)==0))      /*�ҵ���ʼ�յ����ͬ��վ*/
        {
            if(numbers<=pTemp->item.ticket_lea)       /*��С����Ʊ�����а���*/
            {
                printf("�ҵ�������Ϣ�ĳ��Σ�\n");
                printf("��ʼվ    �յ�վ    ����ʱ��    ��������    ����    ��;ʱ��    ��Ʊ��\n");
                printf("%-10s",pTemp->item.start_stat);
                printf("%-10s",pTemp->item.end_stat);
                printf("%-11s",pTemp->item.go_time);
                printf("%-12s",pTemp->item.go_data);
                printf("%-10s",pTemp->item.train_num);
                printf("%-13s",pTemp->item.all_time);
                printf("%-d",pTemp->item.ticket_lea);
				printf("\n");
                printf("��������������");
                scanf("%s",buy_name);
                
				printf("���ڰ���Ʊ......\n");
                printf("��ϲ������ɹ���\n");
                
				pTemp->item.ticket_lea=pTemp->item.ticket_lea - numbers;       /*����ɹ����ó���Ʊ������*/
                
				strcpy(lg[len].name,buy_name);
                
				lg[len].num=numbers;
				len++;
				return 0;    /*��Ʊ�ɹ��������˵�*/
            }
            else 
            {
                printf("������Ҫ��Ʊ��������Ʊ���������Ƿ��������Y/y || N/n��?\n");
                getchar();
                scanf("%c",&wy);
                
				if(wy == 'Y' || wy == 'y')
                    buy(pHead);
                else if(wy == 'N' || wy=='n' )
				{
					 printf("ллʹ��,����������أ�\n");
					 getch();
					 return 0;
				}
            }
        }
		else
			pTemp=pTemp->next;
	}
	printf("\n���ź���δ�ҵ�����Ҫ�ĳ��Σ������¶�Ʊ��\n");

	buy(pHead);
	return 0;
}

//��Ʊ
int back(struct node *pHead)
{
	 struct node *pTemp;
   	 int i;
	 char wy;                //�ж�yes or no 
     
	 char back_name[10];     //��Ʊ������
     int back_num;           //��Ʊ��
	 char back_start[20];    //��Ʊ��ʼվ
	 char back_end[20];      //��Ʊ�յ�վ
     
	 printf("������Ҫ��Ʊ����������Ʊ����");
     scanf("%s%d",back_name,&back_num);
	 printf("��������Ʊ����ʼվ���յ�վ��");
	 scanf("%s%s",back_start,back_end);
     pTemp=pHead;
	
	 while(pTemp!=NULL)
	 {
		 if((strcmp(pTemp->item.start_stat,back_start)==0)&&(strcmp(pTemp->item.end_stat,back_end)==0))      /*�ҵ���ʼ�յ����ͬ��վ*/
		 {
			 for(i=0;i<len;i++)
			 {
				 if(strcmp(back_name,lg[i].name)==0)
				 {
					 printf("��Ʊ�ɹ���\n");
                     pTemp->item.ticket_lea=pTemp->item.ticket_lea + back_num;       //����ɹ����ó���Ʊ������
					 return 0;
				 }
                 else
				 {
					 printf("δ�ҵ�������Ʊ���������Ƿ�������Ϣ����������Ʊ(Y/y || N/n)��");
					 getchar();
						scanf("%c",&wy);
                     if(wy=='Y' || wy =='y')
						back(pHead);
					else if(wy=='N' || wy == 'n')
					{
						 printf("ллʹ��,����������أ�\n");
						 getch();
						 return 0;
					}
				 }
			 }
		 }
		else
			pTemp=pTemp->next;
	 }
	printf("\n���ź���δ�ҵ���Ҫ��Ʊ�ĳ��Σ���������Ʊ��\n");
	back(pHead);
	return 0;
}

//���ļ��ж�ȡ��Ϣ
struct node *read_inf() //�Ӵ����ļ��ж�ȡ��Ϣ�����뵥���� 
{
	struct node *head, *r, *train;   //����ṹ��ָ�����  struct node������ 
	                                 //headΪͷ��㣨ͷ���������Ϣ����rΪβ�ڵ㣬 trainΪ��ǰ�ڵ� 
	FILE *fp;

	if((fp=fopen("information.txt","rt"))==NULL)
	{
		printf("���ļ�������������˳�");
		getch();
		exit(1); 
	}
	
	head=(struct node *)malloc(sizeof(struct node));   //��ʼ�� 
	head->next=NULL;
	
	fscanf(fp,"%s %s %s %s %s %s %d",head->item.start_stat,head->item.end_stat,
			head->item.go_time,head->item.go_data,head->item.train_num,head->item.all_time,&head->item.ticket_lea);
	
	r=head;  //r��β�ڵ� 
	while(!feof(fp))     //�ļ�ĩ���� 
	{                        
		train=(struct node *)malloc(sizeof(struct node));        //�������� 
		fscanf(fp,"%s %s %s %s %s %s %d",train->item.start_stat,train->item.end_stat,
			train->item.go_time,train->item.go_data,train->item.train_num,train->item.all_time,&train->item.ticket_lea);
		r->next=train;   //����ڵ� 
		r=train;
	}
	r->next=NULL;
	
	fclose(fp);
	printf("\n�ļ�����Ϣ����ȷ����������������أ�");
	getch();   //��������� 
	system("cls");
	return head; 
}

//������
void meau()
{
    printf("\n");
    printf("\t���������������������������\n");
    printf("\t��==============��ӭʹ�ó�Ʊ����ϵͳ==============��\n");
    printf("\t��~~~~~~~~~~~~~~~1.���복Ʊ��Ϣ~~~~~~~~~~~~~~~~~~~��\n");
    printf("\t��~~~~~~~~~~~~~~~2.��ʾ��Ʊ��Ϣ~~~~~~~~~~~~~~~~~~~��\n");
    printf("\t��~~~~~~~~~~~~~~~3.��ѯ��Ʊ��Ϣ~~~~~~~~~~~~~~~~~~~��\n");
    printf("\t��~~~~~~~~~~~~~~~4.���ӳ�Ʊ��Ϣ~~~~~~~~~~~~~~~~~~~��\n");
    printf("\t��~~~~~~~~~~~~~~~5.ͳ�� �� ����~~~~~~~~~~~~~~~~~~~��\n");
    printf("\t��~~~~~~~~~~~~~~~6. ��     Ʊ~~~~~~~~~~~~~~~~~~~~~��\n");
    printf("\t��~~~~~~~~~~~~~~~7. ��     Ʊ~~~~~~~~~~~~~~~~~~~~~��\n");
    printf("\t��~~~~~~~~~~~~~~~8.�л��˺ŵ�¼~~~~~~~~~~~~~~~~~~~��\n");
    printf("\t��~~~~~~~~~~~~~~~9.�˳�����ϵͳ~~~~~~~~~~~~~~~~~~~��\n");
    printf("\t��================================================��\n");
    printf("\t���������������������������\n");
    printf("��ѡ���ţ�1-9��ѡ���ܽ�����Ӧ�Ĳ�����");
}

//�����ȣ�Ϊ�˸��õ����� 
int listlength(struct node *pHead)   //�ж�����ĳ��� ����֪��ѭ������ 
{
	struct node *current;
	int len=0;
	
	current=pHead;
	while(current!=NULL)
	{
		len++;                   //����һƪ len���� ��ʾ�������ĳ��� 
		current=current->next;
	} 
	return len;
}

//��ͳ���� 
void Sort(struct node *pHead)
{
	int len;
	
	struct node *current;
	
	current=pHead;
	len=listlength(pHead);         //����һ�������Ĺ����ж�����ĳ��� 
	printf("����%d����Ϣ\n", len);
	while(len>1)
	{                       //ð������ 
		while(current->next != NULL)
		{
			if(strcmp(current->item.all_time, current->next->item.all_time)>0)   //�Ƚ�ʱ�� 
			{	
				Item temp;  //����һ���������� 
				
				temp=current->item;
				current->item=current->next->item;
				current->next->item=temp;
				
			}
			current=current->next;
		}
		len--;
		current=pHead;   //ÿ�δ�ͷ��ʼ���� 
	}
	output(pHead);  //��ȥ������� 
	return;
} 

//������
int main()
{
    system("color 4");
    printf("��");sleep(0);
	printf("ӭ");sleep(1); 
	system("color 3");
	printf("ʹ");sleep(0);
	printf("��");sleep(1);
	system("color 2");
	printf("��");sleep(0);
	printf("Ʊ");sleep(1);
	system("color 1");
	printf("��");sleep(0);
	printf("��");sleep(1); 
	system("color 6");
	printf("ϵ");sleep(0);
	printf("ͳ\n");sleep(2);
	printf("\t\t");
	printf("\n");	
	
	system("color 8"); 
	printf("\t\t\t���������½ע��ҳ�����Ժ�.....");
	sleep(3);
	system("cls");
	
    system("color 3");
	
	int x; 
	printf("\t\t1.��½\t\t\t2.ע�Ტ��¼\n");
	printf("��ѡ����ţ�");
	scanf("%d",&x);
	if(x==1)
		land();
	else if(x==2)
	{
		enroll();
		land();
	}
	else
	{
		printf("������Ч�������˳�ϵͳ��\n");
		exit(1);
	}
	
    int choice=8;
	struct node *pHead;                  //����ͷ���
	
    //ѡ����  
    while(choice != 10)
    {  
		meau();
		
		scanf("%d",&choice);

		switch(choice)
        {  
        case 1:system("cls"); pHead=read_inf();  break;         
        case 2:system("cls"); output(pHead);     break;                       
        case 3:system("cls"); inquire(pHead);    break;
        case 4:system("cls"); add(pHead);   save_inf(pHead);        break;
        case 5:system("cls"); Sort(pHead);       break;
        case 6:system("cls"); buy(pHead);        break;
        case 7:system("cls"); back(pHead);       break;
        case 8:land(); break;
        case 9:exit(1);
        default:printf("��������ȷ�ı�ţ�\n");  break;
        }	
    }
}
