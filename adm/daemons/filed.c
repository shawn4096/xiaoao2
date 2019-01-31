
#define DEBUGGER "no bady"
#define MAX_SIZE 1300

#define PORT_FILE 55443

#define DEBUG(y) do{ if (find_player(DEBUGGER)) tell_object(find_player(DEBUGGER),y+"\n"); }while (0)

#define JIAMI_C "/cmds/common/jiami.c"

#include <localtime.h>
#include <net/socket.h>
#include <net/socket_errors.h>
#include <mudlib.h>
#include <ansi.h>

//inherit F_DBASE;

nosave string* listnens = ({
	/*
	"127.0.0.1",
	"202.100.222.243", //春秋
	"218.77.186.66",   //辽宁
	"218.25.10.190",   //辽宁二
	"61.243.124.74",   //开发
	"61.129.77.241",   //上海(telcom)
	"221.11.134.1",	   //上海二(netcom)*/
	});
nosave string* sites = ({
	"CQ","LN","SH","SH2",
	});

nosave int Sock;
nosave int persistent;

nosave mapping sockets;
nosave mapping resolve_pending;

nosave string *months;

mapping files;
/*
([
		"/u/ciwei/man.c":([
				"wizard":"ciwei",
				"code":  "喜欢",
				"flag":([
					"NIT":0,
				])
			])
		]);
*/
void set_persistent(int which);
void log_info(string msg);
protected void setup();
void store_client_info(int fd);
void close_connection(int fd);
void write_data(int fb,string str);
string get_file(string site);
string get_data(string name,int part);
int strtoint(string str);

int removebuff(object me,string buffname,int buffvalue,string tempmark,int msg);

int removefightbuff(object me,string buffname,int buffvalue,int count,string skilllist,string tempmark,string msg);

//有两类，1是定时的buff，到时结束(战斗前)
//2是随时检测buff，战斗或者切换技能则消失(战斗中)
//多组buff用|分割字串表示 比如cuff|sword|parry
int addbuff(object me,string buffname,int buffvalue,int bufftime,string tempmark,string msg)
{
	string* bufflist;
	int i;
	if (!objectp(me)) return 0;	
	
	if (me->query_temp(tempmark)) return 0;//避免反复叠加
	
	//单个的buff
	if (strsrch(buffname,"|")==-1)
	{
       // if (me->query_condition("buff_"+buffname)) return 0;//避免反复叠加
	    me->add_temp("apply/"+buffname,buffvalue);//添buff   
	}
	else
	{
		bufflist=explode(buffname,"|");
		for(i=0;i<sizeof(bufflist);i++){
		 
		 me->add_temp("apply/"+bufflist[i],buffvalue);//添buff  
			
		}		
	}	 
	 
	 
	    
     if (tempmark) me->set_temp(tempmark,1);//添加临时标记	
		
	 call_out("removebuff",bufftime,me,buffname,buffvalue,tempmark,msg);
	 return 1;
}

//消除buff
int removebuff(object me,string buffname,int buffvalue,string tempmark,int msg)
{
	string* bufflist;
	int i;
	
	if (!me) return 0;
	
	//单个
	if (strsrch(buffname,"|")==-1)
	{
       // if (me->query_condition("buff_"+buffname)) return 0;//避免反复叠加
	    me->add_temp("apply/"+buffname,-buffvalue);//消除buff   
	}
	//多个
	else
	{
		bufflist=explode(buffname,"|");
		for(i=0;i<sizeof(bufflist);i++){
		 
		 me->add_temp("apply/"+bufflist[i],-buffvalue);//消除buff  
			
		}		
	}
	
	
	if (tempmark) me->delete_temp(tempmark);
	if (msg) message_vision(msg+"\n"NOR, me);	//显示信息
	return 1;
}

//战斗buff
// me, buffname,buffvalue,cout,skillslist,tempmark,msg
int addfightbuff(object me,string buffname,int buffvalue,int count,string skilllist,string tempmark,string msg)
{
	string* bufflist;	
	int i;
	if (!objectp(me)) return 0;	
	if (!me->is_fighting()) return 0;//非战斗不能加
	if (me->query_temp(tempmark)) return 0;//避免反复叠加	
		
	//单个的buff
	if (strsrch(buffname,"|")==-1)
	{
       // if (me->query_condition("buff_"+buffname)) return 0;//避免反复叠加
	    me->add_temp("apply/"+buffname,buffvalue);//添buff   
	}
	else
	{
		bufflist=explode(buffname,"|");
		for(i=0;i<sizeof(bufflist);i++){
		 
		 me->add_temp("apply/"+bufflist[i],buffvalue);//添buff  
			
		}		
	}

    if (tempmark) me->set_temp(tempmark,1);//添加临时标记
   
    call_out("removefightbuff",1,me,buffname,buffvalue,count,skilllist,tempmark,msg);	
	return 1;	
}

int removefightbuff(object me,string buffname,int buffvalue,int count,string skilllist,string tempmark,string msg)
{
	string* bufflist;
	string* sk;
	int i;
	  
	  //技能判断 taiji-quan|cuff
	if (skilllist &&(strsrch(skilllist,"|") !=-1))
	{
		
		sk=explode(skilllist,"|");		
	  if (me->query_skill_mapped(sk[1]) != sk[0]) 
	  {	        
	    count=0;
	  }	 
	}	
	
	if (!me->is_fighting()|| count<1)
	{	
	//单个
	if (strsrch(buffname,"|")==-1)
	{
       // if (me->query_condition("buff_"+buffname)) return 0;//避免反复叠加
	    me->add_temp("apply/"+buffname,-buffvalue);//消除buff   
	}
	//多个
	else
	{
		bufflist=explode(buffname,"|");
		for(i=0;i<sizeof(bufflist);i++){
		 
		 me->add_temp("apply/"+bufflist[i],-buffvalue);//消除buff  
			
		}		
	}
    if (tempmark) me->delete_temp(tempmark);
	if (msg) message_vision(msg+"\n"NOR, me);	//显示信息	
	return 1;
	}
	else
	{
		count--;
		call_out("removefightbuff",1,me,buffname,buffvalue,count,skilllist,tempmark,msg);
	}
}
