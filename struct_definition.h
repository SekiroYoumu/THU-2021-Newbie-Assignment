#pragma once
/*1.枚举与结构体的定义汇总*/
enum authentication_enum
{
	GUEST=-1,UNAUTHED, AUTHED, ROOT
};
//用户权限的四个等级，-1对应访客，0对应无权限提交基因组序列，1对应有权限提交基因组序列，2对应管理员
enum month_name_enum
{
	JAN=1,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC
};
enum read_formate
{
	FORMATTED,MANUAL
};//基因组文件的读入格式，0代表格式化文件自动识别，1代表非格式化文件手动读入
typedef struct date_information
{
	int y;
	int m;
	int d;
}date;//日期结构体
typedef struct full_gene_information
{
	int id; //系统内唯一ID（按顺序排列）
	char ID[15];	//DNA序列唯一ID
	char name[200]; //DNA序列名称
	char type[30]; //DNA序列类型
	char seq[40000]; //DNA序列体
	int a, t, c, g, l; //统计信息（l为总长度）
	char source[200];//DNA序列的来源病毒类型
	char locale[200]; //采集地点
	char ins[150]; //测序机构
	char tech[70];//测序技术
	char remark[200]; //其他附加信息
	date submit;
}gene;//完整的DNA序列信息
gene null_gene = { 0,"-1","-1", "-1", "-1", -1,-1,-1,-1,-1,"-1", "-1", "-1", "-1", "-1", -1,-1,-1 };
typedef struct sequence_with_length
{
	char* seq;
	int l;
}seq_len;//定义“带长度的DNA序列”，方便数据传递及开空间
seq_len null_seq = { NULL,-1 };
typedef struct Gene_index_information 
{
	int id;
	char name[200];
	char ID[15];
	char type[30];
	char source[200];//DNA序列的来源病毒类型
	char locale[200]; //采集地点
	char ins[150]; //测序机构
	char tech[70];//测序技术
}index;//在库序列索引
typedef struct user_information
{
	int user_id;
	char password[17];
	char user_name[100];
	int privilege;
}user;//用户信息
typedef struct amino_acid
{
	char name[4];
	int n;
}amino;//氨基酸信息
/*2.全局变量定义汇总*/
int current_id = 0; //当前选中基因的id
int compare_id = 0; //进行LCS,SES等操作时选择
index* roster = NULL;//入库基因数组
user* userlist = NULL;//入库用户数组
user current_user; //当前账户参数
user guest = { -1,"RickAstley","访客",-1 };//访客用户参数
user admin = { 0,"thucfy","admin",2 };//管理员用户参数，重新建立数据库时启用
int sum_user = 0;//当前入库用户总数(不包括管理员账户！）
int sum_roster = 0;//当前入库基因总数
const char not_allowed[10] = "/\\:*?\"<>|";//创建文件不允许的字符，会在录入基因时检查
const char auth_key[20] = "GlobalFirstTieUniv.";//权限开启验证码