#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>

#define N 600
#define M 2*N-1 
int count = 0;

typedef struct Huffmantree//��������
{
    char data;//Ҫ������ַ�
    int weight;//���Ȩֵ
    int parent;
    int lchild;
    int rchild;
}HuffmanTree[M];

typedef struct Huffmancode //����������
{
    char data;//������Ӧ���ַ�
    char bits[N];//�ֽ�
}HuffmanCode[N];

typedef struct str//�ַ�����
{
    char data;//�ַ�
    char num;//����Ƶ��
}str;

HuffmanTree ht;
HuffmanCode hc;

void setColor();	//������ɫ 
void menu();		//ѡ�� 
void write();		//д���ļ� 
void statistics();	//д���ļ� 
void Code();		//���������� 
void Print();		//��ӡ�������� 
void Decode();		//���������� 
void CrtHuffmanTree(HuffmanTree ht,str *s);
void CrtHuffmanCode(HuffmanTree ht,HuffmanCode hc);
void select(HuffmanTree ht,int i,int *s1,int *s2);
void CodeToFile(HuffmanCode hc,int n);

void setColor()
{	
	int c;
	printf("\t\t����Ϊ��ѡ�񱳾�ɫ��������ɫ��\n\n");
	printf("\t\t\t1.ϵͳĬ��\n"); 
	printf("\t\t\t2.�׵׺���\n"); 
	printf("\t\t\t3.�ҵ׺���\n"); 
	printf("\t\t\t4.���׺���\n\n"); 
	printf("\t\t��������ѡ�����ţ�"); 
	scanf("%d",&c);
	switch(c)
	{
		case 1:break;
		case 2:system("color F0"); break;
		case 3:system("color 70"); break;
		case 4:system("color B0"); break;
		default:printf("\n\t\t�������������������!\n\n");
		setColor();
	}
	system("cls");
	menu();
}

void menu(void)
{
	printf("\t\t-----------------������������----------------------\n"); 
	printf("\t\t-----------------1.д���ļ�------------------------\n"); 
	printf("\t\t-----------------2.ͳ���ļ����ַ����ֵ�Ƶ��--------\n");
	printf("\t\t-----------------3.����������----------------------\n"); 
	printf("\t\t-----------------4.��ӡ��������--------------------\n");
	printf("\t\t-----------------5.����������----------------------\n"); 
	printf("\t\t-----------------0.�˳�----------------------------\n"); 
	printf("\t\t����������ѡ��");
	int choose;
	scanf("%d",&choose);
	switch(choose)
	{
		case 0:exit(0);
		case 1:write();break;
		case 2:statistics();break; 
		case 3:Code();break;
		case 4:Print();break;
		case 5:Decode();break;
		default:printf("\n\t\t������������������룡\n");
				printf("\t\t�밴�����������\n\n");getchar();getchar();
				system("cls");
				menu(); 
	 } 
	 printf("\t\t�밴�����������") ;
	 getchar();getchar();
	 system("cls");
	 menu();
}

void write()
{
	FILE *fp;
	char ch;
	if((fp = fopen("Haffman.souce","w")) == NULL){
		printf("��������\n");
		exit(1); 
	}
	ch = getchar();
	printf("\t\t������Ҫ�������ַ���(��#����)��");
	ch = getchar();
	while(ch != '#'){
		fputc(ch,fp);
		ch = getchar(); 
	}
	fclose(fp);
	printf("\n");
} 
void statistics()
{
	FILE *fp;
	char ch;
	str s1[128],s2[128];
	
	for(int i=0;i<128;i++){
		s1[i].data = 0;
		s1[i].num = 0;
		s2[i].data = 0;
		s2[i].num = 0;
	}
	if((fp = fopen("Haffman.souce","r")) == NULL){
		printf("\n�ļ���ʧ�ܣ�\n");
		exit(1); 
	}
	
	printf("\n\t\t��ȡ�����ַ���Ϊ��");
	ch = fgetc(fp);
	while(!feof(fp)){
		printf("%c",ch);
		s1[ch].data = ch;
		s1[ch].num ++;
		ch = fgetc(fp);
	}
	fclose(fp);
	count=1;
	for (int i=1;i<128;i++){
		if(s1[i].num!=0){
			s2[count].data = s1[i].data;
			s2[count].num = s1[i].num;
			count++;
		}
	}
	count-=1;
	printf("\n\n\t\t�ļ����ַ����ֵ�Ƶ��:\n\n");
	for(int i=1;i<=count;i++)
    {
        printf("\t\t\t%c : %d\n",s2[i].data,s2[i].num);
    }
    printf("\t\t����%d�в�ͬ���ַ���",count);
    
    CrtHuffmanTree(ht,s2);
} 
void Code()
{
    CrtHuffmanCode(ht,hc);
    CodeToFile(hc,count);
} 
//������������	 
void CrtHuffmanTree(HuffmanTree ht,str *s)	
{
	//��ʼ��ǰn��Ԫ�س�Ϊ���ڵ� 
	for(int i=1;i<=count;i++){
		ht[i].data = s[i].data;
        printf("%c ",ht[i].data);
		ht[i].weight = s[i].num;
		ht[i].parent = 0;
		ht[i].lchild = 0;
		ht[i].rchild = 0;
	}
	printf("\n\n");
	//��ʼ����n-1����Ԫ�� 
	int m = 2*count-1;
	for(int i=count+1;i<=m;i++){
		ht[i].data = 0;
		ht[i].weight = 0;
		ht[i].parent = 0;
		ht[i].lchild = 0;
		ht[i].rchild = 0;
	}
	//�ӵ�n+1��Ԫ�ؿ�ʼ�����½�� 
	int s1,s2;
	for(int i=count+1;i<=m;i++){
		//��ht��ǰi-1����ѡ˫��Ϊ0��Ȩֵ��С�������ڵ�s1,s2 
		select(ht,i-1,&s1,&s2);
		//�����½�㣬��Ȩֵ 
		ht[i].weight = ht[s1].weight + ht[s2].weight;
		ht[i].lchild = s1;
		ht[i].rchild = s2;
		ht[s1].parent = i;
		ht[s2].parent = i;
	}
}

void select(HuffmanTree ht,int n,int *s1,int *s2)
{
	int i,j;
	for(i=1;i<=n;i++){
		if(ht[i].parent == 0){
			*s1 = i;
			break;
		}
	}
	for(j=i+1;j<=n;j++){
		if(ht[j].parent == 0){
			*s2 = j;
			break;
		}
	}
	for(i=1;i<=n;i++){
		if((ht[i].weight<ht[*s1].weight)&&(ht[i].parent==0)&&(*s2!=i))
			*s1 = i;
	}
	for(j=1;j<=n;j++){
		if((ht[j].weight<ht[*s2].weight)&&(ht[j].parent==0)&&(*s1!=j))
			*s2 = j;
	}
	if(ht[*s1].weight>ht[*s2].weight){
		int temp = *s1;
		*s1 = *s2;
		*s2 = temp;
	}
}
//���������� 
void CrtHuffmanCode(HuffmanTree ht,HuffmanCode hc)
{
	int c,p;
	char *cd;
	int start;
	
	cd = (char *)malloc(count*sizeof(char));
	cd[count-1] = '\0';
	
	for(int i=1;i<=count;i++){
		start = count-1;
		c=i;
		p=ht[i].parent;
		
		hc[i].data = ht[i].data;
		
		while(p!=0){
			--start;
			if(ht[p].lchild == c)	cd[start]='0';
			else cd[start] = '1';
			c = p;
		    p = ht[p].parent;
		}
		strcpy(hc[i].bits,&cd[start]);
	} 
	printf("\n\t\tÿ���ַ���Ӧ�ı�������:\n");
	printf("\t\t���        ����       ����\n");
    for(int i=1;i<=count;i++)
        printf("\t\t%-3d          %c         %s    \n",i,hc[i].data,hc[i].bits);
}
 
//�ѱ�����д���ļ� 
void CodeToFile(HuffmanCode hc,int n)
{
	FILE *fp1,*fp2;
	char ch;
	
	if((fp1 = fopen("Haffman.souce","r")) == NULL){
        printf("�ļ���ʧ��");
        getchar();
        exit(1);
	}
	if((fp2 = fopen("Haffman.code","w")) == NULL){
        printf("�ļ���ʧ��");
        getchar();
        exit(1);
	}
	
	ch = fgetc(fp1);
	printf("\t\t��������Ϊ��");
	while(ch!=EOF){
		for(int i=1;i<=count;i++){
			if(ch == hc[i].data){
				fputs(hc[i].bits,fp2);
		        printf("%s",hc[i].bits);	
			}
		}
		ch = fgetc(fp1); 
	}
	printf("\n");
	fclose(fp1);
	fclose(fp2);
 } 

void Print()
{
	system("CLS"); 	
	printf("\n\t\t�����Ĺ�������Ϊ��\n");
	printf("\n\t\tnum\tdata\tweight\tparent\tLchild\tRchild\n");
	for(int i=1;i<=2*count-1;i++)
	{
		printf("\n\t\t%d\t%c\t%d\t%d\t%d\t%d",i,ht[i].data,ht[i].weight,ht[i].parent,ht[i].lchild,ht[i].rchild);
	}
	printf("\n");
} 
void Decode()
{

	FILE  *fp1,*fp2;
	int p;
	char ch; 
	
	if((fp1 = fopen("Haffman.code","r")) == NULL){
        printf("�ļ���ʧ��");
        exit(1);
	}
	if((fp2 = fopen("Haffman.decode","w")) == NULL){
        printf("�ļ���ʧ��");
        exit(1);
	}
	
	p = 2*count-1;
	printf("\n\t\t��������Ϊ��  ");
	ch = fgetc(fp1);
	while(!feof(fp1)){
		if(ch == '0')
			p = ht[p].lchild;
		else if(ch == '1')
			p = ht[p].rchild;
		if(ht[p].data != 0){
			printf("%c",ht[p].data);
	        fputc(ht[p].data,fp2); 
	        p = 2*count-1;
		}
		ch = fgetc(fp1);
	}
	printf("\n");
	fclose(fp1);
	fclose(fp2);
	
	int i,j=1;
	char s1[N],s2[N];
	
	if((fp1 = fopen("Haffman.souce","r")) == NULL){
		 printf("\n���ļ�ʧ�ܣ�\n");
		 exit(1);
	}
	if((fp2 = fopen("Haffman.decode","r")) == NULL){
		 printf("\n���ļ�ʧ�ܣ�\n");
		 exit(1);
	}
	for(i = 1; (s2[i]=fgetc(fp2)) != EOF;i++){
	}
	printf("\n\t\tԴ�ļ�����Ϊ��");
	for(i = 1; (s1[i]=fgetc(fp1)) != EOF;i++){
		printf("%c",s1[i]);
	}
	printf("\n");
    while( j < count){
    	if(s1[j] == s2[j]){
    		j++;
		}
		else{
			printf("%d",j);
			printf("\n\t\t����ʧ�ܣ�\n");
			break;
		} 
	}
	if(j == count){
		printf("\n\t\t��������һ�£�����ɹ���\n"); 
	}	
	fclose(fp1);
	fclose(fp2);
}

void test() {
	FILE *fp;
	char ch;
	str s1[128],s2[128];
	
	for(int i=0;i<128;i++){
		s1[i].data = 0;
		s1[i].num = 0;
		s2[i].data = 0;
		s2[i].num = 0;
	}
	if((fp = fopen("Haffman.souce","r")) == NULL){
		exit(1); 
	}
	
	ch = fgetc(fp);
	while(!feof(fp)){
		s1[ch].data = ch;
		s1[ch].num ++;
		ch = fgetc(fp);
	}
	fclose(fp);
	count=1;
	for (int i=1;i<128;i++){
		if(s1[i].num!=0){
			s2[count].data = s1[i].data;
			s2[count].num = s1[i].num;
			count++;
		}
	}
	count-=1;
	for(int i=1;i<=count;i++){
		ht[i].data = s2[i].data;
		ht[i].weight = s2[i].num;
		ht[i].parent = 0;
		ht[i].lchild = 0;
		ht[i].rchild = 0;
	}
	printf("\n\n");
	//��ʼ����n-1����Ԫ�� 
	int m = 2*count-1;
	for(int i=count+1;i<=m;i++){
		ht[i].data = 0;
		ht[i].weight = 0;
		ht[i].parent = 0;
		ht[i].lchild = 0;
		ht[i].rchild = 0;
	}
	//�ӵ�n+1��Ԫ�ؿ�ʼ�����½�� 
	int s3,s4;
	for(int i=count+1;i<=m;i++){
		//��ht��ǰi-1����ѡ˫��Ϊ0��Ȩֵ��С�������ڵ�s1,s2 
		select(ht,i-1,&s3,&s4);
		//�����½�㣬��Ȩֵ 
		ht[i].weight = ht[s3].weight + ht[s4].weight;
		ht[i].lchild = s3;
		ht[i].rchild = s4;
		ht[s3].parent = i;
		ht[s4].parent = i;
	}
}

int main(void)
{
	test();
	setColor();
}                             
