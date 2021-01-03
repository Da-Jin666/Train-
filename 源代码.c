#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>

#define n 5

int len=0;

//乘客信息
struct passenge                     
{
    char name[10];                 //姓名
    int  num;                      //所需票量
}lg[n];                           //结构体变量名 

//车票信息
typedef struct train                      
{
    char start_stat[20];          //起始站
    char end_stat[20];            //终点站
    char go_time[16];             //出发时间 
    char go_data[16];             //出发日期
    char train_num[15];           //车次信息
    char all_time[16];            //旅途时间
    int  ticket_lea;               //余票数量
}Train;              //把结构体struct train 叫做 Train 

typedef Train Item;    //又把Train 叫做 Item，目的让链表更通用    链表里只有2 个东西 项目和指针  

struct node
{                        //node是一个节点   节点包括项目和指针 
	Item item;
	struct node *next;
};

//注册信息
void enroll()
{
	char a[100];                   //注册用户名
	char b[100];                   //注册密码
	char s[100];                   //再次确定密码
	int  len;
	
   	printf("请输入您的用户名：");
	scanf("%s",a);
	
	printf("请设置您的密码：");
			
	reset: scanf("%s",b);     //用到了if goto语句 

	    len=strlen(b);    //读取密码长度 
	   
	   if(len>9)
		{
			printf("密码长度过长，请重新设置：");
	      goto reset;    //if goto 语句  
	    }
  	  printf("请再次输入您设置的密码：");
     	scanf("%s",s);
	
	if(strcmp(b,s) == 0)       //字符串比较函数 
	{
		FILE *fp;
		
		fp=fopen("register.txt","at");     //选用追加方式，可以存多个信息
		
		if(fp == NULL)
		{
			printf("文件不存在!");
			exit(1);                           
		}
		
		fprintf(fp,"%s %s\n",a,b);                    //字符串写入函数进行写入操作
       
	    printf("\n\t------注册成功------\n");
		fclose(fp);
	}
	else if(strcmp(b,s) != 0)
	{
		printf("您两次输入的密码不一致，请重新设置密码！\n");
		goto reset;          //if goto 语句 
	}
}

//登陆页面
int land()
{
	int  i=0;      //i是为了判断密码长度 并加密 
	char a[10];                 
	char b[10];                   

	char user_name[10];           
	char user_passwords[10];      

	printf("请输入您的用户名：");
	scanf("%s",user_name);

    printf("请输入您的密码：");

	while(i<9 && (user_passwords[i] = getch()) && user_passwords[i] != '\r')   //如果输入超限 或者 遇到换行符就跳出循环
	{
		printf("*");   //掩饰密码 
		i++;
	}
	
	user_passwords[i]=0;   //字符串结束标志 '/0' 
	
	FILE *fp;
	fp=fopen("register.txt","rt");       //又打开文件 
	
	if(fp==NULL)
	{
		printf("文件不存在!");
		exit(1);
	}
	
	while(fscanf(fp,"%s %s",a,b)!=EOF)    //读文件判断账号密码是否正确 
	{    
		if(strcmp(a,user_name)==0  &&  strcmp(b,user_passwords)==0)   //字符串比较函数，看是否正确 
		 {
			printf("\n\t--------登陆成功--------\n");
			printf("\t------欢迎进入系统------\n");
			return 0;
		 } 
	}
	if(1)
	{
		printf("\n信息输入错误！\n");
	     land();
	}
	fclose(fp);
}

//将信息保存到文件 
void save_inf(struct node *pHead)             //将链表中的信息保存到制定文件中
{                                         //头指针不能移动 
    struct node *pTemp;   //因为要一个节点移动 所以定义为pTemp移动 
    
	FILE *fp;
    fp=fopen("information.txt","at");    //打开文件 
    
	if(fp==NULL)
    {
        printf("打开文件失败，文件可能不存在！\n");
        exit(1);
    }
                                                           //遍历输入 
    for(pTemp=pHead ; pTemp != NULL;pTemp=pTemp->next)      //节点先指向项目，项目里面再找成员 
        
		fprintf(fp,"%s %s %s %s %s %s %d\n",pTemp->item.start_stat,pTemp->item.end_stat,
			pTemp->item.go_time,pTemp->item.go_data,pTemp->item.train_num,pTemp->item.all_time,pTemp->item.ticket_lea);
   
    fclose(fp);
} 

//增加 
struct node *add(struct node *pHead)
{
	   struct node *pNew;
	   struct node *current; 
	  
	    pNew=(struct node *)malloc(sizeof(struct node));      //再次分配结点的内存空间
        
        pNew->next=pHead;    //新结点指向原来的首节点 
        pHead=pNew;          //头指针指向新结点
        
        
        //尾插法;
		/*current=pHead;
		while(current->next!=NULL)
		{
			current=current->next;
		} 
		current->next=pNew;
		pNew->next=NULL;
        */
        
        printf("\n请输入起始站：");
        scanf("%s",pNew->item.start_stat);
        printf("请输入终点站：");
        scanf("%s",pNew->item.end_stat);
        printf("请输入出发时间：");
        scanf("%s",pNew->item.go_time);
        printf("请输入出发日期：");
        scanf("%s",pNew->item.go_data);
        printf("请输入车次信息：");
        scanf("%s",pNew->item.train_num);
        printf("请输入旅途时间：");
        scanf( "%s",pNew->item.all_time);
        printf("请输入余票数量：");
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
		 
        return pHead;       //返回头指针 
        
 } 
 

//输出显示模块
void output(struct node *pHead)
{
    struct node *pTemp;                 //循环所用的临时指针

	pTemp=pHead;                         //指针的到首结点的指针

    printf("\t******车票信息如下******\n");
    printf("起始站    终点站    出发时间    出发日期     车次信息     旅途时间    余票量\n");

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
        pTemp=pTemp->next;              //移动临时指针到下一个结点
    }

}

//查询车票信息
int inquire(struct node *pHead)
{
	int flag = 0;
    struct node *pTemp; 
    
    char inquire_start[20],inquire_end[20];       //查询选择的起始站和终点站
  
    printf("请输入要查询车票的起始站和终点站：");
    scanf("%s %s",inquire_start,inquire_end);
    
	pTemp=pHead;
    
    while(pTemp!=NULL)
    {
        if((strcmp(pTemp->item.start_stat,inquire_start)==0) && (strcmp(pTemp->item.end_stat,inquire_end)==0))
        {
        	flag = 1;
            printf("\n车票信息结果如下：\n");
            printf("起始站    终点站    出发时间    出发日期    车次    旅途时间    余票量\n");
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
    	printf("输入错误！\n");
		inquire(pHead);
	}
	return 0;
	} 
	
//订票	
	int buy(struct node *pHead)
{
    struct node *pTemp; 
    char   choice_start[20],choice_end[20];       /*购票选择的起始和终点站*/
    int    numbers;                                /*购买数量*/
    char   buy_name[10];                          /*购买人姓名*/
    char   wy;
    
    pTemp=pHead; 
    printf("请输入所购买车票的起始站、终点站和票数：");
    scanf("%s %s %d",choice_start,choice_end,&numbers);
  
    while(pTemp!=NULL)
    {
        if((strcmp(pTemp->item.start_stat,choice_start)==0)&&(strcmp(pTemp->item.end_stat,choice_end)==0))      /*找到起始终点均相同的站*/
        {
            if(numbers<=pTemp->item.ticket_lea)       /*若小于余票量进行办理*/
            {
                printf("找到符合信息的车次：\n");
                printf("起始站    终点站    出发时间    出发日期    车次    旅途时间    余票量\n");
                printf("%-10s",pTemp->item.start_stat);
                printf("%-10s",pTemp->item.end_stat);
                printf("%-11s",pTemp->item.go_time);
                printf("%-12s",pTemp->item.go_data);
                printf("%-10s",pTemp->item.train_num);
                printf("%-13s",pTemp->item.all_time);
                printf("%-d",pTemp->item.ticket_lea);
				printf("\n");
                printf("请您输入姓名：");
                scanf("%s",buy_name);
                
				printf("正在办理订票......\n");
                printf("恭喜您办理成功！\n");
                
				pTemp->item.ticket_lea=pTemp->item.ticket_lea - numbers;       /*办理成功，该车次票量减少*/
                
				strcpy(lg[len].name,buy_name);
                
				lg[len].num=numbers;
				len++;
				return 0;    /*订票成功返回主菜单*/
            }
            else 
            {
                printf("您所需要的票数超过余票数，请问是否继续办理（Y/y || N/n）?\n");
                getchar();
                scanf("%c",&wy);
                
				if(wy == 'Y' || wy == 'y')
                    buy(pHead);
                else if(wy == 'N' || wy=='n' )
				{
					 printf("谢谢使用,按任意键返回！\n");
					 getch();
					 return 0;
				}
            }
        }
		else
			pTemp=pTemp->next;
	}
	printf("\n很遗憾，未找到您需要的车次，请重新订票！\n");

	buy(pHead);
	return 0;
}

//退票
int back(struct node *pHead)
{
	 struct node *pTemp;
   	 int i;
	 char wy;                //判断yes or no 
     
	 char back_name[10];     //退票人姓名
     int back_num;           //退票数
	 char back_start[20];    //退票起始站
	 char back_end[20];      //退票终点站
     
	 printf("请输入要退票人姓名和退票数：");
     scanf("%s%d",back_name,&back_num);
	 printf("请输入退票的起始站和终点站：");
	 scanf("%s%s",back_start,back_end);
     pTemp=pHead;
	
	 while(pTemp!=NULL)
	 {
		 if((strcmp(pTemp->item.start_stat,back_start)==0)&&(strcmp(pTemp->item.end_stat,back_end)==0))      /*找到起始终点均相同的站*/
		 {
			 for(i=0;i<len;i++)
			 {
				 if(strcmp(back_name,lg[i].name)==0)
				 {
					 printf("退票成功！\n");
                     pTemp->item.ticket_lea=pTemp->item.ticket_lea + back_num;       //办理成功，该车次票数增加
					 return 0;
				 }
                 else
				 {
					 printf("未找到您定的票，请问您是否重输信息继续进行退票(Y/y || N/n)：");
					 getchar();
						scanf("%c",&wy);
                     if(wy=='Y' || wy =='y')
						back(pHead);
					else if(wy=='N' || wy == 'n')
					{
						 printf("谢谢使用,按任意键返回！\n");
						 getch();
						 return 0;
					}
				 }
			 }
		 }
		else
			pTemp=pTemp->next;
	 }
	printf("\n很遗憾，未找到您要退票的车次，请重新退票！\n");
	back(pHead);
	return 0;
}

//从文件中读取信息
struct node *read_inf() //从磁盘文件中读取信息并存入单链表 
{
	struct node *head, *r, *train;   //定义结构体指针变量  struct node是类型 
	                                 //head为头结点（头结点中有信息），r为尾节点， train为当前节点 
	FILE *fp;

	if((fp=fopen("information.txt","rt"))==NULL)
	{
		printf("读文件出错，按任意键退出");
		getch();
		exit(1); 
	}
	
	head=(struct node *)malloc(sizeof(struct node));   //初始化 
	head->next=NULL;
	
	fscanf(fp,"%s %s %s %s %s %s %d",head->item.start_stat,head->item.end_stat,
			head->item.go_time,head->item.go_data,head->item.train_num,head->item.all_time,&head->item.ticket_lea);
	
	r=head;  //r是尾节点 
	while(!feof(fp))     //文件末结束 
	{                        
		train=(struct node *)malloc(sizeof(struct node));        //建立链表 
		fscanf(fp,"%s %s %s %s %s %s %d",train->item.start_stat,train->item.end_stat,
			train->item.go_time,train->item.go_data,train->item.train_num,train->item.all_time,&train->item.ticket_lea);
		r->next=train;   //链表节点 
		r=train;
	}
	r->next=NULL;
	
	fclose(fp);
	printf("\n文件中信息以正确读出，按任意键返回！");
	getch();   //清除缓冲区 
	system("cls");
	return head; 
}

//主界面
void meau()
{
    printf("\n");
    printf("\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
    printf("\t☆==============欢迎使用车票管理系统==============☆\n");
    printf("\t☆~~~~~~~~~~~~~~~1.存入车票信息~~~~~~~~~~~~~~~~~~~☆\n");
    printf("\t☆~~~~~~~~~~~~~~~2.显示车票信息~~~~~~~~~~~~~~~~~~~☆\n");
    printf("\t☆~~~~~~~~~~~~~~~3.查询车票信息~~~~~~~~~~~~~~~~~~~☆\n");
    printf("\t☆~~~~~~~~~~~~~~~4.增加车票信息~~~~~~~~~~~~~~~~~~~☆\n");
    printf("\t☆~~~~~~~~~~~~~~~5.统计 与 排序~~~~~~~~~~~~~~~~~~~☆\n");
    printf("\t☆~~~~~~~~~~~~~~~6. 订     票~~~~~~~~~~~~~~~~~~~~~☆\n");
    printf("\t☆~~~~~~~~~~~~~~~7. 退     票~~~~~~~~~~~~~~~~~~~~~☆\n");
    printf("\t☆~~~~~~~~~~~~~~~8.切换账号登录~~~~~~~~~~~~~~~~~~~☆\n");
    printf("\t☆~~~~~~~~~~~~~~~9.退出管理系统~~~~~~~~~~~~~~~~~~~☆\n");
    printf("\t☆================================================☆\n");
    printf("\t☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
    printf("请选择编号（1-9）选择功能进行相应的操作：");
}

//链表长度，为了更好的排序 
int listlength(struct node *pHead)   //判断链表的长度 进而知道循环次数 
{
	struct node *current;
	int len=0;
	
	current=pHead;
	while(current!=NULL)
	{
		len++;                   //遍历一篇 len自增 表示最后链表的长度 
		current=current->next;
	} 
	return len;
}

//排统计序 
void Sort(struct node *pHead)
{
	int len;
	
	struct node *current;
	
	current=pHead;
	len=listlength(pHead);         //上面一个函数的功能判断链表的长度 
	printf("共有%d个信息\n", len);
	while(len>1)
	{                       //冒泡排序 
		while(current->next != NULL)
		{
			if(strcmp(current->item.all_time, current->next->item.all_time)>0)   //比较时间 
			{	
				Item temp;  //定义一个交换变量 
				
				temp=current->item;
				current->item=current->next->item;
				current->next->item=temp;
				
			}
			current=current->next;
		}
		len--;
		current=pHead;   //每次从头开始遍历 
	}
	output(pHead);  //进去输出函数 
	return;
} 

//主函数
int main()
{
    system("color 4");
    printf("欢");sleep(0);
	printf("迎");sleep(1); 
	system("color 3");
	printf("使");sleep(0);
	printf("用");sleep(1);
	system("color 2");
	printf("车");sleep(0);
	printf("票");sleep(1);
	system("color 1");
	printf("管");sleep(0);
	printf("理");sleep(1); 
	system("color 6");
	printf("系");sleep(0);
	printf("统\n");sleep(2);
	printf("\t\t");
	printf("\n");	
	
	system("color 8"); 
	printf("\t\t\t即将进入登陆注册页面请稍候.....");
	sleep(3);
	system("cls");
	
    system("color 3");
	
	int x; 
	printf("\t\t1.登陆\t\t\t2.注册并登录\n");
	printf("请选择序号：");
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
		printf("输入无效，即将退出系统！\n");
		exit(1);
	}
	
    int choice=8;
	struct node *pHead;                  //定义头结点
	
    //选择编号  
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
        default:printf("请输入正确的编号！\n");  break;
        }	
    }
}
