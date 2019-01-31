
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
	"202.100.222.243", //����
	"218.77.186.66",   //����
	"218.25.10.190",   //������
	"61.243.124.74",   //����
	"61.129.77.241",   //�Ϻ�(telcom)
	"221.11.134.1",	   //�Ϻ���(netcom)*/
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
				"code":  "ϲ��",
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

//�����࣬1�Ƕ�ʱ��buff����ʱ����(ս��ǰ)
//2����ʱ���buff��ս�������л���������ʧ(ս����)
//����buff��|�ָ��ִ���ʾ ����cuff|sword|parry
int addbuff(object me,string buffname,int buffvalue,int bufftime,string tempmark,string msg)
{
	string* bufflist;
	int i;
	if (!objectp(me)) return 0;	
	
	if (me->query_temp(tempmark)) return 0;//���ⷴ������
	
	//������buff
	if (strsrch(buffname,"|")==-1)
	{
       // if (me->query_condition("buff_"+buffname)) return 0;//���ⷴ������
	    me->add_temp("apply/"+buffname,buffvalue);//��buff   
	}
	else
	{
		bufflist=explode(buffname,"|");
		for(i=0;i<sizeof(bufflist);i++){
		 
		 me->add_temp("apply/"+bufflist[i],buffvalue);//��buff  
			
		}		
	}	 
	 
	 
	    
     if (tempmark) me->set_temp(tempmark,1);//�����ʱ���	
		
	 call_out("removebuff",bufftime,me,buffname,buffvalue,tempmark,msg);
	 return 1;
}

//����buff
int removebuff(object me,string buffname,int buffvalue,string tempmark,int msg)
{
	string* bufflist;
	int i;
	
	if (!me) return 0;
	
	//����
	if (strsrch(buffname,"|")==-1)
	{
       // if (me->query_condition("buff_"+buffname)) return 0;//���ⷴ������
	    me->add_temp("apply/"+buffname,-buffvalue);//����buff   
	}
	//���
	else
	{
		bufflist=explode(buffname,"|");
		for(i=0;i<sizeof(bufflist);i++){
		 
		 me->add_temp("apply/"+bufflist[i],-buffvalue);//����buff  
			
		}		
	}
	
	
	if (tempmark) me->delete_temp(tempmark);
	if (msg) message_vision(msg+"\n"NOR, me);	//��ʾ��Ϣ
	return 1;
}

//ս��buff
// me, buffname,buffvalue,cout,skillslist,tempmark,msg
int addfightbuff(object me,string buffname,int buffvalue,int count,string skilllist,string tempmark,string msg)
{
	string* bufflist;	
	int i;
	if (!objectp(me)) return 0;	
	if (!me->is_fighting()) return 0;//��ս�����ܼ�
	if (me->query_temp(tempmark)) return 0;//���ⷴ������	
		
	//������buff
	if (strsrch(buffname,"|")==-1)
	{
       // if (me->query_condition("buff_"+buffname)) return 0;//���ⷴ������
	    me->add_temp("apply/"+buffname,buffvalue);//��buff   
	}
	else
	{
		bufflist=explode(buffname,"|");
		for(i=0;i<sizeof(bufflist);i++){
		 
		 me->add_temp("apply/"+bufflist[i],buffvalue);//��buff  
			
		}		
	}

    if (tempmark) me->set_temp(tempmark,1);//�����ʱ���
   
    call_out("removefightbuff",1,me,buffname,buffvalue,count,skilllist,tempmark,msg);	
	return 1;	
}

int removefightbuff(object me,string buffname,int buffvalue,int count,string skilllist,string tempmark,string msg)
{
	string* bufflist;
	string* sk;
	int i;
	  
	  //�����ж� taiji-quan|cuff
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
	//����
	if (strsrch(buffname,"|")==-1)
	{
       // if (me->query_condition("buff_"+buffname)) return 0;//���ⷴ������
	    me->add_temp("apply/"+buffname,-buffvalue);//����buff   
	}
	//���
	else
	{
		bufflist=explode(buffname,"|");
		for(i=0;i<sizeof(bufflist);i++){
		 
		 me->add_temp("apply/"+bufflist[i],-buffvalue);//����buff  
			
		}		
	}
    if (tempmark) me->delete_temp(tempmark);
	if (msg) message_vision(msg+"\n"NOR, me);	//��ʾ��Ϣ	
	return 1;
	}
	else
	{
		count--;
		call_out("removefightbuff",1,me,buffname,buffvalue,count,skilllist,tempmark,msg);
	}
}
