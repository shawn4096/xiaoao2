// gmd.c  ������
// Modify By River@SJ 99.06
// ���Χ������������ by renlai
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{ 
       set("short",HIR"������"NOR);
       set("long", "
    ����������̹����������ߵ�����Ϳɿ��������ʺ�ɫ���֡����̣����֣�\n"+
"ؤ�������������Ḷ̌��������������ɣ���ؤ�����������ɡ���������\n"+
"��˹�̴ܽ�����ԭ���аٶ������ʷ�ˡ�����ʼ�ն��Է�Ԫ����������ȥ��\n"+
"��������Ϊ���ѵ���ּ������������̫�����½�������ݹݬ���룬��ʹ����\n"+
"�����ɳ�Ϊħ�̡�������һ���ɫ����Ĵ��졣���������䳡���ϱ��Ǿ�ľ��\n"+
"�����ڵء�\n\n"HIR"\t\t\t��    ��    ��\n\n"NOR);
	set("exits", ([
		"northup" : __DIR__"wu3",
		"southdown" : __DIR__"muqi",			
	]));
	set("objects",([
                "kungfu/class/mingjiao/yin" : 1,
                CLASS_D("mingjiao") + "/wulu" : 1,
                __DIR__"npc/m-dizi" : 2,
	]));
        set("outdoors", "���̹�����");
        set("valid_startroom", 1);
        set("coor/x",-290);
	set("coor/y",170);
	set("coor/z",110);
	set("coor/x",-290);
	set("coor/y",170);
	set("coor/z",110);
	setup();        
        call_other("/clone/board/mingjiao_b","???");
}

int init()
{
	object me=this_player();	
	if (me->query_temp("gmd_job/asked")) 
	{
        set("long", "
    ����������̹����������ߵ�����Ϳɿ��������ʺ�ɫ���֡����̣����֣�\n"+
"ؤ�������������Ḷ̌��������������ɣ���ؤ�����������ɡ���������\n"+
"��˹�̴ܽ�����ԭ���аٶ������ʷ�ˡ�����ʼ�ն��Է�Ԫ����������ȥ��\n"+
"��������Ϊ���ѵ���ּ������������̫�����½�������ݹݬ���룬��ʹ����\n"+
"�����ɳ�Ϊħ�̡�������һ���ɫ����Ĵ��졣���������䳡���ϱ��Ǿ�ľ��\n"+
"�����ڵء���ʱ���������Ѿ��ۼ�������Ⱥ�ۣ���ʱ׼��Χ��(weigong)��������\n\n"HIR"\t\t\t��    ��    ��\n\n"NOR);		
		add_action("do_weigong","weigong");			
	}	
}

int do_weigong()
{
	object me=this_player();
	object fbroom;
	object *team,*ob;
	int max,i,j;	
	   
	   team = me->query_team();	
	   
	   if (me->query_condition("gmd_job")<5) 
	   {
		   write("��������,�Ѿ�����˽��������������ʱ����\n");			  
			  return 1;
	   }
		
		if (team)
		{
			if (me->query_temp("gmd_job/team")!=team) {
			  write("��Ӹı���,�޷������������\n");
			  
			  return 1;
		  }

          fbroom= new("/u/anger/gmdfb");//����fb
          fbroom->set("backroom","/d/mingjiao/gmd");//����·��
		  fbroom->set("short", HIM"������-����"NOR);
		  fbroom->set("leader",me);//����ӳ�
		  
          me->set_temp("fbroom",fbroom);//��¼����
          me->set_temp("gmd_up", 1);		  
		  CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")һ������Ԥ��Χ������������ʥ��\n"NOR);
		for (i=0;i<sizeof(team);i++){			
		
		if (team[i]->query_condition("killer")) 
		{ 
	        write("���������ڱ�ͨ��,�޷������������\n");
			break;
			//return 0;
		}		
		if (!present(team[i])){			
			write("�����˲�ȫ����"+team[i]->query("name")+"��ôû��,�޷������������\n");
			break;
			//return 0;
		}
		
		ob = deep_inventory(team[i]);
	         j = sizeof(ob);
	            while (j--)
	               if (ob[j]->is_character()){
					   ob[j]->move("/d/mingjiao/gmd");
		               write("�����ϱ���һ���ˣ��޷����븱����\n");
		                      return 1;
	                       }	
		
		    team[i]->set("job_name", "Χ��������");
			message_vision(HIC"$N�������޼ɵ���һ�ѷ�����������ϳ��롣\n"NOR,team[i]);
			team[i]->move(fbroom);
		
		}	  
		
		return 1;
		}
		
		else 
		{		
		
		if (me->query_condition("killer")) 
		{
             write("���ڱ�ͨ��,�޷������������\n");			
		      return 1;//��ֹͨ�����������		
		}
		
		ob = deep_inventory(me);
	       j = sizeof(ob);
	       while (j--)
	      if (ob[j]->is_character()){
			  ob[j]->move("/d/mingjiao/gmd");
		      write("�����ϱ���һ���ˣ��޷����븱����\n");
		      return 1;
	         }
		  
		 	
          fbroom= new("/u/anger/gmdfb");//����fb
          fbroom->set("backroom","/d/mingjiao/gmd");//����·��
          fbroom->set("short", HIM"������-����"NOR);		  
		  me->set_temp("fbroom",fbroom);//��¼����
		  me->set_temp("gmd_up", 1);
		  fbroom->set("leader",me);//����ӳ�
		  CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1)+"("+me->query("id")+")����һ�˶�����������\n"NOR);
		  message_vision(HIC"$N�����ո��˵���Ȼһ��ֱ����������\n"NOR,me);		  
          me->move(fbroom);	
		  return 1;
		}	
	
}
