//���¸��� by renlai

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIM"������"NOR);
        set("long", @LONG
���·����ڶ࣬��ģ֮�󣬼�����������·����кô�һ�����֣�����
�������ͭ����¥�����㣬�º��һ��ʮ������������Զ��ɼ���������
Ӱ�´£�ÿһ���ж���������Ѳ�飬���¸��ж���ʮ�����š�
LONG);
        set("outdoors", "����");		
        set("quest",1);
		set("no_sleep_room",1);
		set("no_quit", 1);
		set("exits", ([
		"south" : "/d/cangzhou/nroad2",		
	]));
        
		
   setup();
}
int init()
{
	object me=this_player();	
	if (me->query_temp("was_job/asked")) 
	{		
		add_action("do_yingjiu","yingjiu");			
	}	
}

int do_yingjiu()
{
	object me=this_player();
	object fbroom;
	object *team,*ob;
	int max,i,j;	
	   
	   team = me->query_team();	
	   
	   if (me->query_condition("was_job")<5) 
	   {
		   write("��������,�Ѿ�����˽������µ����ʱ����\n");			  
			  return 1;
	   }
		
		if (team)
		{
			if (me->query_temp("was_job/team")!=team) {
			  write("��Ӹı���,�޷��������¡�\n");
			  
			  return 1;
		  }

          fbroom= new("/u/anger/wasfb");//����fb
          fbroom->set("backroom","/d/was/was");//����·��
		  fbroom->set("short", HIM"�������ײ�-����"NOR);
		  fbroom->set("leader",me);//����ӳ�
		  
          me->set_temp("fbroom",fbroom);//��¼����
          me->set_temp("was_up", 1);		  
		  CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")һ������Ԥ��Ǳ�����¾��ˣ�\n"NOR);
		for (i=0;i<sizeof(team);i++){			
		
		if (team[i]->query_condition("killer")) 
		{ 
	        write("���������ڱ�ͨ��,�޷��������¡�\n");
			break;
			//return 0;
		}		
		if (!present(team[i])){			
			write("�����˲�ȫ����"+team[i]->query("name")+"��ôû��,�޷��������¡�\n");
			break;
			//return 0;
		}
		
		ob = deep_inventory(team[i]);
	         j = sizeof(ob);
	            while (j--)
	               if (ob[j]->is_character()){
					   ob[j]->move("/d/was/was");
		               write("�����ϱ���һ���ˣ��޷����븱����\n");
		                      return 1;
	                       }	
		
		    team[i]->set("job_name", "�´�����");
			message_vision(HIC"$N����һ�ᣬ������ȷʵ���ˣ���ŴӺ��������������롣\n"NOR,team[i]);
			team[i]->move(fbroom);
		
		}	  
		
		return 1;
		}
		
		else 
		{		
		
		if (me->query_condition("killer")) 
		{
             write("���ڱ�ͨ��,�޷��������¡�\n");			
		      return 1;//��ֹͨ�����������		
		}
		
		ob = deep_inventory(me);
	       j = sizeof(ob);
	       while (j--)
	      if (ob[j]->is_character()){
			  ob[j]->move("/d/was/was");
		      write("�����ϱ���һ���ˣ��޷����븱����\n");
		      return 1;
	         }
		  
		 	
          fbroom= new("/u/anger/wasfb");//����fb
          fbroom->set("backroom","/d/was/was");//����·��
          fbroom->set("short", HIM"�������ײ�-����"NOR);		  
		  me->set_temp("fbroom",fbroom);//��¼����
		  me->set_temp("was_up", 1);
		  fbroom->set("leader",me);//����ӳ�
		  CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")����һ�˶������£�\n"NOR);
		  message_vision(HIC"$N����һ�ᣬ������ȷʵ���ˣ������ո��˵���Ȼһ�˴Ӻ�����������롣\n"NOR,me);		  
          me->move(fbroom);	
		  return 1;
		}		  
	
	
}

