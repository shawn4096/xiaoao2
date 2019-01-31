// Room: /d/huashan/hole2.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ROOM;
int do_han(string arg);
void create()
{

	set("short", "ʯ��");
	set("long",@long
����һ����ɽ����ʯ���ϵ�һ�������۵�ʯ������ɽ�ɸ����ߺͰ����߾�
�����ڴˡ���ɽ�ɵ���һ������ܹ��������ǣ�����ܹ��������书��Ȼ�õ�
���ǵĴ���ָ�㡣
long);
	set("exits",([
	"out" : __DIR__"song",
]));
	set("objects",([
	__DIR__"npc/gao" : 1,
	__DIR__"npc/ai" : 1,
]));
	setup();
}

void init()
{
    if (this_player()->query_temp("jianzong/bijian")|| this_player()->query("quest/huashan")=="����")
    { 
		add_action("do_han","han");
		add_action("do_han","yell");
    }
   

}

int do_han(string arg)
{
    int i;
	object feng,cong,cheng;
	string ms;
	object me=this_player();
	i=me->query("kar");
	if (!arg||arg!="����ǰ��")
      return notify_fail("��ɽҰ��ģ��㲻�º���ĸ�ǣ�\n");
  
    ms=me->query("family/master_id");
	//write(ms);
	
    if (me->query("quest/huashan")=="����")
	{	
		switch (ms)
		{
			case "cheng buyou":
				 if (!present("cheng buyou",environment(me)))
				 {
					cheng=new("/d/huashan/npc/sword/chengbuyu.c");
					cheng->move("/d/huashan/hole2");
					message_vision(HIC"�ɲ����������һ�������������\n"NOR,me);
					return 1;
				  }
			break;
			case "feng buping":
		          if (!present("feng buping",environment(me)))
				  {
					feng=new("/d/huashan/npc/sword/fengbuping.c");
					feng->move("/d/huashan/hole2");
					message_vision(HIC"�ⲻƽ�������һ�������������\n"NOR,me);
					return 1;
				  }
			break;
			
		}

		//return notify_fail("��\n");
	}
	if (!me->query_temp("jianzong/bijian"))
		  return notify_fail("�ٺ���������ˣ�\n");
	if (time()-me->query("hs/jianzong/time")<86400)
		  return notify_fail("������̫�ڿ��ˣ�\n");
	if (i>30)
	{
		log_file("quest/bugzuobi",sprintf("%s(%s)�ڽ��ܻ�ɽ���ڷ�֧�������������ɡ���Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("hs/wushuang/fail"),me->query("combat_exp"),me));
		return 1;
	}
	if (me->query_temp("jianzong/bijian")&& i>26 || me->query("quest/huashan")=="����")
	{
		  message_vision(HIC"˭�ҵ����ڴ˴���������\n����һ����ȣ�������Ӱ��Ȼ�������$N����ǰ��\n"NOR,me);
		  
		  if (!present("feng buping",environment(me)))
          {
			feng=new("/d/huashan/npc/sword/fengbuping.c");
			feng->move("/d/huashan/hole2");
			
          }else feng=present("feng buping",environment(me));
		  if (!present("chong buqi",environment(me)))
          {
			cong=new("/d/huashan/npc/sword/chongbuqi.c");
			cong->move("/d/huashan/hole2");
			cong->set_temp("jiali",60);
         }else cong=present("chong buqi",environment(me));
         
		 if (!present("cheng buyou",environment(me)))
         {
			cheng=new("/d/huashan/npc/sword/chengbuyu.c");
			cheng->move("/d/huashan/hole2");
         }else cheng=present("cheng buyu",environment(me));
        
			message_vision(HIW"$N�ɹ�Ѱ�ҵ���ɽ���ڵ����䲢���԰�ʦ��\n", me);
			tell_object(me, BYEL"��ϲ�㣬��ɹ��⿪��ɽ��������,����û��������ӳɽ�����\n"NOR);
			log_file("quest/jianzong",sprintf("%s(%s)�ɹ��ҵ����ڷ�֧������ʼ׼����ϰ���ھ�������Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),i,me->query("hs/jianzong/fail"),me->query("combat_exp"),me));
			me->add_skill("sword",10+random(10));
			me->set("quest/huashan","����");
			me->set("title","��ɽ�ɽ����״�����");
			me->delete_temp("jianzong/bijian");
			return 1;
			
    } else {
			message_vision(HIY"$N���˰��죬�չȴ����ص����˼����ޡ�\n"NOR,me);
			message_vision(HIC"���ܽ��ڷ�֧ʧ�ܡ�\n"NOR,me);
			log_file("quest/jianzong",sprintf("%s(%s)���ܽ��ڷ�֧ʧ�ܡ���Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),i,me->query("hs/jianzong/fail"),me->query("combat_exp"),me));
			me->add("hs/jianzong/fail",1);
            me->set("hs/jianzong/time",time());
			me->delete_temp("jianzong/bijian");
            return 1;
		}


}
