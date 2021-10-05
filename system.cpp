#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define SIZE 10
typedef struct Order{
	int Table_ID;
	int Dish_ID[10];
	int Dish_Num;
	struct Order *nextPtr;
}ORDER;
typedef struct Table{
	int Table_ID;//���ӱ��
	int Capacity;//������������ɵ�����
	int Table_State;//1.�������� 0.��������
}TABLE;
typedef struct Dish {
	int Dish_ID;  //�˵ı��
	char Dish_Name[30];  //����
	float Dish_Price;  //�۸�
}DISH;
//struct


TABLE table_menu[5] = {{1,4,0},{2,5,0},{3,6,0},{4,7,0},{5,8,0}};//������Ϣ
DISH DishMenu[10] = {{ 1, "�л�������", 4.000000 },{ 2, "��������", 66.000000 },{ 3, "��������", 4.000000 },
                         { 4, "��������", 33.000000 },{ 5, "������Ѽ", 108.000000 },{ 6, "����Ծ����", 666.000000 },
                         { 7, "�Ͼ��л���", 77.000000 },{ 8, "�ײ�������", 10.000000 },{ 9, "��ϲ����", 88.000000 },
                         { 10, "��������", 20.000000 }};//��Ʒ����Ϣ
int GLOBAL = 1;
//��ʼ��
//global variables

int Highpopular(int dishpopular[], size_t size);
int Pass_Word(int ke);//������֤
void List_Management(int key);//ͬ��
void ListMenu(void);//��Ŀ��������ӡ
void Dish_Menu(void);//��Ʒ�������ӡ
void CreateBill(ORDER** headPtrPtr,int tableNum,int a[],int dishNum);//�����ڵ㲢��������
ORDER *search(ORDER** headPtrPtr,int choice);//�����Ų��ҽڵ�
void deleted(ORDER** headPtrPtr,ORDER** aPtr);//ɾ���ڵ�
//function declare


int main(void){
	system("color f4");
	ORDER *headPtr=NULL;
	int i,j;//counter
	//һЩָ��ͼ�����������
	while(1){
		puts("*********************");
		puts("    ��������ϵͳ");
		puts("*********************");
		puts("1.���");
		puts("2.�ͻ�����");
		puts("3.��Ŀ����");
		puts("4.�͹�ͳ��");
		puts("5.�˳�");
		int choice;
		puts("��ѡ��");
		scanf("%d", &choice);//���˵������ӡ


		switch(choice){
			case 1:{
				printf("����������������1-8��\n");
				int num;//���Ͳ͵�����
				scanf("%d",&num);
				while(num <=0 || num >= 9){
					printf("������������ԣ�\n");
					scanf("%d",&num);
				}
				int i;//counter
				int tableNum;
				for(i = 0;i< 5;i++){
					if(num<= table_menu[i].Capacity && table_menu[i].Table_State == 0){
						printf("�����������ѿ��Ե�%d�����ò�\n",i+1);
						tableNum=i+1;//tableNum
						table_menu[i].Table_State = 1;
						break;
					}
				}//���ŷ���


				Dish_Menu();//��Ʒ�������ӡ

				FILE * cfPtr;
           		 if((cfPtr = fopen("client.txt", "a")) == NULL){
              		  puts("File couldn't be opened");
            	}
				else{


				int choice = -1;
				int a[10]={0};
				int dishNum=0;
			    for(i=0;choice != 0;i++){
			        printf("������˵ı�ţ���0��������:");
			        scanf("%d", &choice);
			        if(choice < 0 || choice > 10){
			            printf("����������������룡\n");
			        }
			        if(choice == 0){
			        	break;
					}
			        if(choice >= 0 && choice <= 10){
			        	fprintf(cfPtr, "%d ", DishMenu[choice - 1].Dish_ID);
			            a[i]=choice;
			            dishNum++;
			        }
			    }//���

				CreateBill(&headPtr,tableNum,a,dishNum);//�����ڵ㲢��������
				fclose(cfPtr);
				}
				break;
			}
			case 2:{
				printf("����������˵Ĳ�����(1-5)\n");
				int choice;
				scanf("%d",&choice);
				ORDER *aPtr;
				aPtr=search(&headPtr,choice);//�����Ų��ҽڵ�
				if(!aPtr){
					break;
				}
				int total=0;

				printf("���			����			�۸�\n");
				for(i=0;i<=9;i++){
					for(j=0;j<=9;j++){
						if(aPtr->Dish_ID[i]==DishMenu[j].Dish_ID){
						printf("%d			%s			%f",DishMenu[j].Dish_ID,DishMenu[j].Dish_Name,DishMenu[j].Dish_Price);
						printf("\n");
						total=total+DishMenu[j].Dish_Price;
						}
					}
				}
				printf("��һ������%d����\n",aPtr->Dish_Num);
				printf("����%dԪ\n",total);
				printf("�뽻��\n");
				float money,change;
				int judge=0;
				while(judge==0){
					scanf("%f",&money);
					if(money>=total){
						change=money-total;
						printf("����%.6fԪ\n",change);
						judge=1;
						FILE * CFptr;
						time_t timer;
						timer = time(NULL);
           				if((CFptr = fopen("accountbook.txt", "a")) == NULL){
              				  puts("File couldn't be opened");
            			}
						else{
							fprintf(CFptr, "%d\t%s\n", total, ctime(&timer));
						}
						fclose(CFptr);
					}
					else{
						printf("��˵����԰����ͣ�\n");
					}
				}

				//��ӡ�˵�

				deleted(&headPtr,&aPtr);//ɾ���ڵ�
				table_menu[choice-1].Table_State = 0;//���ӳ�ʼ��
				break;
			}
			case 3:{
				int mima ;
				FILE *fpp;
				if((fpp = fopen("keyword.txt","r")) ==NULL){
					fclose(fpp);
					fopen("keyword.txt", "w");
					fpp = fopen("keyword.txt", "w");
					fprintf(fpp, "%d", 123456);
				}
				else{
					fscanf(fpp,"%d",&mima);
				}
				fclose(fpp);
				List_Management(mima);
				if(GLOBAL == 2){
					break;
				}
				if(GLOBAL == 1){

					int CHOICE;
					scanf("%d",&CHOICE);
					while (CHOICE != 3){
						if(CHOICE == 1){
							int newmima;
							printf("�������µ�����\n");
							scanf("%d",&newmima);
							FILE *fppp;
							if((fppp = fopen("keyword.txt","w")) ==NULL){
								puts("�޷����ļ�\n");
							}
							else{
								fprintf(fppp,"%d",newmima);
							}
							fclose(fppp);
							system("pause");
							break;
						}
						if(CHOICE == 2){
							printf("��ӭ������Ŀ����ϵͳ,�����ʵ�����\n");
							puts("���ѽ��\t����ʱ��\n");
							FILE * cfPTR;
							char str[25];
							int i = 0, j = 0;
							int pay;
	           				if((cfPTR = fopen("accountbook.txt", "r")) == NULL){
	              		  		puts("File couldn't be opened");
	            			}
							else{
								fscanf(cfPTR, "%d", &pay);
								while(!feof(cfPTR)){
									i = 0;
									j = 0;
									fscanf(cfPTR, "%d\n", &pay);
									while(i <= 5 && j < 25){
										fscanf(cfPTR, "%c", &str[j]);
										j++;
										if(str[j] == ' '){
											i++;
										}
									}
									fscanf(cfPTR, "\n\n");
									i = 0;
									j = 0;
									printf("%d\t", pay);
									while(i <= 5 && j < 25){
										printf("%c", str[j]);
										j++;
										if(str[j] == ' '){
											i++;
										}
									}
									printf("\n");
								}
								break;
							}
							fclose(cfPTR);
							break;
						}
						if(CHOICE == 3){
							system("pause");
							exit(0);
							printf("���˳���Ŀ����ϵͳ\n");
						}
					}
				}
				break;
			}
			case 4:{
				FILE * CFPTR;
        	int num, k, l;
        	int dishpopular[10] = {0};
           	if((CFPTR = fopen("client.txt", "r")) == NULL){
           		 puts("File couldn't be opened");
          	}
         	else{
			 	fscanf(CFPTR, "%d", &num);
            	while(!feof(CFPTR)){
            		dishpopular[num - 1]++;
            		fscanf(CFPTR, "%d", &num);
            	}
            	fclose(CFPTR);
            	puts("�˵��ܻ�ӭ�̶����£�\n");
				for(k = 1; k <= 10; k++){
					printf("%d�ˣ�", k);
					for(l = 0; l < dishpopular[k- 1]; l++){
						printf("* ");
					}
					printf("\n");
          		}
          		printf("�Ƚ��ܻ�ӭ���ĸ����ǣ�\n");
          		int temp, k;
          		for(k = 1; k < 5; k++){
					temp = Highpopular(dishpopular, SIZE);
					printf("%s\n", DishMenu[temp].Dish_Name);
					dishpopular[temp] = 0;
				}
				fclose(CFPTR);
			}

			break;
			}
			case 5:{
				system("pause");
				exit(0)5;
				break;
			}
			default:
		 	printf("����������������룡\n");
		 	system("pause");
			break;
		}
		system("pause");//�������˵�
		system("cls");//����
	}
	system("pause");
	return 0;
}
//main function


void Dish_Menu(void)
{
    int i;
	printf("**********��ӭѡ�������************\n");
	puts("�˱��	����		�˵���");
	for (i = 0; i < 10; i++) {
        printf("%d\t%s\t%f\n", DishMenu[i].Dish_ID, DishMenu[i].Dish_Name, DishMenu[i].Dish_Price);
    }
}
//��Ʒ����ӡ����

void CreateBill(ORDER** headPtrPtr,int tableNum,int a[],int dishNum){
	ORDER *Ptr=(ORDER*)malloc(sizeof(ORDER));
	Ptr->Table_ID=tableNum;
	Ptr->nextPtr=NULL;
	Ptr->Dish_Num=dishNum;
	int i;
	for(i=0;i<=dishNum-1;i++){
		Ptr->Dish_ID[i]=a[i];
	}

	ORDER *lastPtr= *headPtrPtr;
	if(lastPtr){
		while(lastPtr->nextPtr){
			lastPtr=lastPtr->nextPtr;
		}
		lastPtr->nextPtr=Ptr;
	}
	else{
		*headPtrPtr=Ptr;
	}

}
//�����ڵ㴴��������������룩

ORDER *search(ORDER** headPtrPtr,int choice){
	ORDER *Ptr = NULL;
	int a=0,i;
	for(Ptr= *headPtrPtr;Ptr;Ptr=Ptr->nextPtr){
		if(Ptr->Table_ID==choice){
			a=1;
			break;
		}
	}
	if(!a){
		printf("NOT FOUND 404\n");
	}
	return Ptr;
}//�����Ų��ҽڵ�

void ListMenu(void){
	puts("***************************");
	puts("   ��ӭ������Ŀ����ϵͳ    ");
	puts("***************************");
	puts("1.�޸�����");
	puts("2.�鿴�˱�");
	puts("3.����");
	puts("��ѡ��:");
}

int Pass_Word(int key){
	int a;
	scanf("%d",&a);
	if(a == key){
		return 1;
	}
	else{
		return 0;
	}
}

void List_Management(int key){
	printf("���������루��ʼ����Ϊ123456��\n");
	int b;
	b = Pass_Word(key);
	if(b == 1){
		ListMenu();
		GLOBAL = 1;
	}
	if(b != 1){
		printf("����������������룬���������λ��᣺\n");
		Pass_Word(key);
		if(b == 1){
			ListMenu();
		}
		if(b != 1){
			printf("����������������룬������һ�λ��᣺\n");
			Pass_Word(key);
			if(b == 1){
				ListMenu();
			}
			if(b != 1){
				printf("������󣬼������أ�");
				GLOBAL = 2;
				return;
			}
		}
	}
	return;
}

int Highpopular(int dishpopular[], size_t size){
	int i, max;
	max = 0;
	for(i = 0; i < 9; ++i){
		if(dishpopular[i] < dishpopular[i + 1]){
			max = i + 1;
		}
	}
	return max;
}

void deleted(ORDER** headPtrPtr,ORDER** aPtrPtr){
	ORDER *Ptr,*lastPtr;
	int a=0;
	for(Ptr= *headPtrPtr,lastPtr=NULL;Ptr;lastPtr=Ptr,Ptr=Ptr->nextPtr){
		if(Ptr== *aPtrPtr){
			if(lastPtr){
			lastPtr->nextPtr=Ptr->nextPtr;
			free(Ptr);
			a=1;
			break;
			}
			else{
				*headPtrPtr=Ptr->nextPtr;
				free(Ptr);
				a=1;
				break;
			}
		}
	}
}//ɾ���ڵ�
