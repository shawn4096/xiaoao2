//Create by lsxk@hsbbs 2007/8/20
//�����޸ģ������������vip�������� ���ʵ�����

/*
ʹ�÷������ܣ�
1����������á����������򷵻�1�����򷵻�0.
QUEST_D->questing(����,�Ѷȵ���ϵ��,��ά,������������)

2����������趨:
�ܹ�����������ң�
deny_quest_player----ֻҪ����������id,���ص�ֵ����0,��������
���жϡ�
vip_quest_player ���鲻����

���ַ�ʽ�趨��
A:��/adm/daemons/questd.c���vip_quest_player���������player
��id, ����deny_quest_player���������id. update���¼���������Ч.
B:�ú���������ӣ�
QUEST_D->add_quest_player(���"DENY")--��������ʱ��ӵ�deny����
QUEST_D->add_quest_player(���"VIP")---��������ʱ��ӵ�vip����
QUEST_D->delete_quest_player(���"DENY")--��������ʱ��deny����ɾ��
QUEST_D->delete_quest_player(���"VIP")--��������ʱ��vip����ɾ��
*/

#include <ansi.h>

//�ܾ���quest����б��ͷ����⵷�ҵ��ˡ�
string *deny_quest_player = ({ });

//���ܱ�־
int setquestmark(object me,string questname,int mark);
//����ʱ��
int setquesttime(object me,string questname);

int queryquest(object me,string questname);

int queryquesttime(object me,string questname);

int queryquestfail(object me,string questname);

string *deny_quest_player = ({"zmud",});

//�����б��е�player�����һ����quest�ɹ��ʣ������ɴ��ݵĲ���������
string *vip_quest_player = ({"zmud", });

//��Ӹ�player����Ӧ�������С���arg���Ƶ�deny����vip.
void add_quest_player(object ob, string arg)
{
    int i;
    if(arg=="DENY"){
        for(i=0;i<sizeof(deny_quest_player);i++)
            if(ob->query("id")==deny_quest_player[i])
                return;

        deny_quest_player += ({ob->query("id")});
    }
    else{
        for(i=0;i<sizeof(vip_quest_player);i++)
            if(ob->query("id")==vip_quest_player[i])
                return;

        vip_quest_player += ({ob->query("id")});
    }
    return;
}

//��������ɾ����player����arg���Ƶ�deny����vip.
void delete_quest_player(object ob, string arg)
{
    if(arg=="DENY"){
        deny_quest_player -= ({ob->query("id")});
    }
    else{
        vip_quest_player -= ({ob->query("id")});
    }
    return;
}


//�ⲿ���ýӿ�  //questing(ob,1000,120,1,"jiuyang")
//quest������������Ϊ0���ǲ�����

//����quest���ж�
int questing(object me,int probability,int property,int maxuser,string questname)
{
    int i, mboth,total,oldtotal, j,vip,hidep =0;
	object* ppl;
	string fullquestname;
	
	fullquestname="quest/"+questname+"/pass";
	    //������������
        for(i=0;i<sizeof(deny_quest_player);i++)
            if(me->query("id")==deny_quest_player[i])
                return 0;
			
    if(!objectp(me)) return 0;
	if (queryquesttime(me,questname)) return 0;//ʱ�䲻��ֱ��ʧ��
	if (queryquest(me,questname)) return 1;//�⿪�˾Ͳ��ж���

	
	//�����0��������
	if (maxuser >0 )
	{
		ppl = users();
		i = sizeof(ppl);
	     while(i--) {
		if (userp(ppl[i]) && !wizardp(ppl[i]) && ppl[i]->query(fullquestname))
		j++;
	   }    
	}
	else
		j=-1;//�������޵��ڲ�����
   //�ж�vip
    //�ж�vip
     vip=random(25);
    if (me->query("buyvip")) vip =random(17);
	if (me->query("y-card-vip")) vip =random(20);
	if (me->query("m-card-vip")) vip =random(22);      
   
	   hidep=random(me->query("kar")); 
   	   
    probability=random(probability);
   oldtotal =me->query("str")+ me->query("int")+ me->query("dex")+ me->query("con"); 
   total=random(oldtotal);
   
    //write("\n"+me->query("name")+"��Ʒ���ʣ�"+probability+"quest����������"+j+"vip���ʣ�"+vip+"��Դ��"+hidep+"��ά��"+total+"\n");
	   if ((probability==0) &&  //������Ʒ���������
	        (vip==3) &&       //vip����
			(hidep>28) &&  //�����츳����
			(total>property)  &&//��ά����				
			(j<maxuser) //����quest��������
		   )
		   {
			   //����ͳһ��¼ʱ��ͱ��
			   setquestmark(me,questname,1);
			   //ͳһ��¼��־
 log_file("quest/"+questname+"_log",sprintf("%-18sʧ��%s�κ󣬳ɹ��⿪%s����<����28>��%d(%d)  ��Ʒ<����0>��%d vip��Ʒ<����3>��%d ��ά<����%d>��%d(%d)  ��\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(queryquestfail(me,questname)),questname,
              			hidep,me->query("kar"),probability,vip,property,total,oldtotal), me);
		       return 1;	  
		   }
		   else
		   {
			  setquestmark(me,questname,0);
log_file("quest/"+questname+"_log",sprintf("%-18sʧ��%s�κ�δ�ܽ⿪%s����<����28>��%d(%d)  ��Ʒ<����0>��%d vip��Ʒ<����3>��%d ��ά<����%d>��%d(%d) ��\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(queryquestfail(me,questname)),questname,
              			hidep,me->query("kar"),probability,vip,property,total,oldtotal), me);
			
		   }
    return 0;
}


//��ͨquest�����ж���ά, ��probability�������Ѷȣ�����Խ��Խ��
int easy_questing(object me,int probability,string questname)
{
    int i, j,vip,hidep =0;	
	string fullquestname;	
	fullquestname="quest/"+questname+"/pass";
	    //������������
        for(i=0;i<sizeof(deny_quest_player);i++)
            if(me->query("id")==deny_quest_player[i])
                return 0;
			
    if(!objectp(me)) return 0;
	
	if (queryquesttime(me,questname)) return 0;//ʱ�䲻��ֱ��ʧ��
	
	if (queryquest(me,questname)) return 1;//�⿪�˾Ͳ��ж���
	
   //�ж�vip
     vip=random(25);
    if (me->query("buyvip")) vip =random(10);
	if (me->query("y-card-vip")) vip =random(15);
	if (me->query("m-card-vip")) vip =random(20);       
   
	  hidep=random(me->query("kar")); 
	  probability=random(probability);
   
     if ((probability==0) &&  //������Ʒ���������
	        (vip<=3) &&       //vip����
			(hidep>=20) //�����츳����			
		   )
		   {
			   //����ͳһ��¼ʱ��ͱ��
			   setquestmark(me,questname,1);
			   //ͳһ��¼��־
   log_file("quest/"+questname+"_log",sprintf("%-18sʧ��%s�κ󣬳ɹ��⿪%s����<����20>��%d(%d)  ��Ʒ<����0>��%d vip��Ʒ<С�ڵ���3>��%d ��\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(queryquestfail(me,questname)),questname,
              			hidep,me->query("kar"),probability,vip), me);
		       return 1;	  
		   }
		   else
		   {
			   setquestmark(me,questname,0);
			  log_file("quest/"+questname+"_log",sprintf("%-18sʧ��%s�κ�δ�ܽ⿪%s����<����20>��%d(%d)  ��Ʒ<����0>��%d vip��Ʒ<С�ڵ���3>��%d ��\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(queryquestfail(me,questname)),questname,
              			hidep,me->query("kar"),probability,vip), me);			
		   }  
    return 0;
}

//job������ص�quest
//���ûjob2����job2 name���� ����д-1
//��������֣� ��ʱ�Եĺ������Ե�,��jobtempmark�ǿո�������ʱ���
int job_questing(object me,int probability,string questname,string job1,int job1num,string job2,int job2num,string jobtempmark)
{	
	
	int i, j,vip,hidep,totaljob =0;	
	string fullquestname;	
	fullquestname="quest/"+questname+"/pass";
	    //������������
        for(i=0;i<sizeof(deny_quest_player);i++)
            if(me->query("id")==deny_quest_player[i])
                return 0;			
    if(!objectp(me)) return 0;
	if (queryquest(me,questname)) return 1;//�⿪�˾Ͳ��ж���
	
	
   //�ж�vip
     vip=random(25);
    if (me->query("buyvip")) vip =random(10);
	if (me->query("y-card-vip")) vip =random(15);
	if (me->query("m-card-vip")) vip =random(20);       
   
	  hidep=random(me->query("kar")); 
	  probability=random(probability);
	  
	  //��ȡjob����
	 totaljob=me->query("job_time/"+job1)+me->query("job_time/"+job2);	  
   
     if ((probability==0) &&  //������Ʒ���������
	        (vip<=3) &&       //vip����
			(hidep>=20) && //�����츳����			
			(random(me->query("job_time/"+job1))>job1num) &&  //job1����
			(random(me->query("job_time/"+job2))>job2num) && //job1����
			(totaljob % 50 == 0) //����50
		   )
		   {
			   
			   //�ж�����ʱ��ǻ������� 
			   
			   if (jobtempmark =="")
			   //����ͳһ��¼ʱ��ͱ��
			   {
				  setquestmark(me,questname,1);			   
				   
			   //ͳһ��¼��־
   log_file("quest/"+questname+"_log",sprintf("%-18sʧ��%s�κ󣬳ɹ��⿪%s����<����20>��%d(%d)  ��Ʒ<����0>��%d vip��Ʒ<С�ڵ���3>��%d job1%s��%d job2%s��%d ��\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(queryquestfail(me,questname)),questname,
              			hidep,me->query("kar"),probability,vip,job1,me->query("job_time/"+job1),job2,me->query("job_time/"+job2)), me);
			   }
			   else
			   {			   
						 me->set_temp(jobtempmark,1);			   
			   log_file("quest/"+questname+"_log",sprintf("%-18s�ɹ��⿪%s����<����20>��%d(%d)  ��Ʒ<����0>��%d vip��Ʒ<С�ڵ���3>��%d job1%s��%d job2%s��%d ��\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",jobtempmark,
              			hidep,me->query("kar"),probability,vip,job1,me->query("job_time/"+job1),job2,me->query("job_time/"+job2)), me);
			   }
		       return 1;	  
		   }
		   else
		   {
			    if (jobtempmark =="")  {
					setquestmark(me,questname,0);				
			log_file("quest/"+questname+"_log",sprintf("%-18sʧ��%s�κ�δ�ܽ⿪%s����<����20>��%d(%d)  ��Ʒ<����0>��%d vip��Ʒ<С�ڵ���3>��%d job1%s��%d job2%s��%d ��\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(queryquestfail(me,questname)),questname,
              			hidep,me->query("kar"),probability,vip,job1,me->query("job_time/"+job1),job2,me->query("job_time/"+job2)), me);					
				}					
				else { 
				me->delete_temp(jobtempmark,0);
					log_file("quest/"+questname+"_log",sprintf("%-18sδ�ܽ⿪%s����<����20>��%d(%d)  ��Ʒ<����0>��%d vip��Ʒ<С�ڵ���3>��%d job1%s��%d job2%s��%d ��\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",jobtempmark,
              			hidep,me->query("kar"),probability,vip,job1,me->query("job_time/"+job1),job2,me->query("job_time/"+job2)), me);				
					
				}
		   }  
    return 0;	
}





//����quest��� 1Ϊ�ɹ���0Ϊʧ��
int setquestmark(object me,string questname,int mark)
{
	if(!objectp(me)) return 0;
	if (mark==0)
      me->add("quest/"+questname+"/fail",1);		
  else 
	  me->set("quest/"+questname+"/pass", mark);
 //��¼ʱ��  
  setquesttime(me,questname);
   return 1;
}

//����quest���
int queryquest(object me,string questname)
{
	return me->query("quest/"+questname+"/pass");
}

//����ʧ�ܴ���
int queryquestfail(object me,string questname)
{
	return me->query("quest/"+questname+"/fail");
}

int setmytitle(object me,string etitle,string ctitle)
{
	 if(!objectp(me)) return 0;	 
	 me->set("title",ctitle);
	 me->set("mytitle/quest/"+etitle,ctitle);
	 return 1;
}
int setquesttime(object me,string questname)
{
     if(!objectp(me)) return 0;	
	 me->set("quest/"+questname+"/time",time());
	 return 1;
}
int queryquesttime(object me,string questname)
{
	int time;
     if(!objectp(me)) return 1;	
	 if (!me->query("quest/"+questname+"/time")) return 0;			
	
	  time=time() - me->query("quest/"+questname+"/time");
	  if (time > 86400) return 0;
	  return 1;	 
}
