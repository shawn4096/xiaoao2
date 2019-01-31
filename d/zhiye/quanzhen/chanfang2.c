#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������ȫ������������ԡ��������ĵط���Ϊ�˷�����
�������ζ�û�аڷţ������ڵ��¶��˼���С���š������ڴ�
�ز���������Ҫ�ķ��ĳ�����
LONG);
        set("exits", ([
                "east" : __DIR__"chanfang3",
                "west" : __DIR__"chanfang1",
                "south" : __DIR__"liangong",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
int init()
{

	add_action("do_sit","sit");
	add_action("do_stand","stand");
	add_action("do_canwu","canwu");
	
}
int do_sit()
{
	object me;
	me=this_player();
	if (me->query_temp("marks/sit"))
	{
		return notify_fail("���Ѿ������ˣ�\n");
	}
	message_vision(HIY"$N�����ߵ�һ������ǰ���������죬��ϥ����������\n"NOR,me);
	me->set_temp("marks/sit",1);
	return 1;

}
int do_stand()
{
	object me;
	me=this_player();
	if (!me->query_temp("marks/sit"))
	{
		return notify_fail("�������û�����£���̸վ��������\n");
	}
	message_vision(HIY"$N�������˸�����������һ��������վ��������\n"NOR,me);
	me->delete_temp("marks/sit");
	return 1;

}
int do_canwu(string arg)
{
	object me,*obj;
	int i,j,x,skill;
	me=this_player();
	obj = users();
	x = sizeof(obj);
	
	while(x--) {
		  if ( obj[x]->query_temp("canwu_yusuo")
			  && obj[x]->query_temp("marks/sit")
			  && obj[x]!=me
			  && environment(me)==environment(obj[x]))
			 {
				  message_vision(HIY"$N��ͼ��������������ȴ����"+obj[x]->query("name") +HIY"�Ѿ����Ķ���������ֻ�������˳����⣡\n"NOR,me);	
				  me->move("d/quanzhen/liangong");
				  return 1;
			}
			
	}
	
	
	i=(int)me->query("yusuo/degree")+1;
	skill=(int)me->query_skill("jinguan-yusuojue", 1);
	
	if (!arg||!(arg=="���������"||arg=="���������ʮ�ľ�"))
	{
		return notify_fail("��Ҫ�ڴ˵ز���ʲô��\n");
	}
	if (!me->query_temp("marks/sit"))
	{
		return notify_fail("��վ�Ų���\n");
	}
	if (!present("yusuo jingyao",me))
	{
		return notify_fail("�����ϲ��޽����������Ҫ���޴Ӷ��գ��޷�����\n");
	}
	
	if ((skill/100)<i) return notify_fail("�������������������̫�٣�Ŀǰ�޷�����\n");
	
	
	if (me->query_temp("canwu_yusuo"))
	{
		return notify_fail("�����ڲ�����������ʮ�ľ���\n");
	}
	if (me->is_busy())
	{
		return notify_fail("������æµ�У�\n");
	}
	if (time()-me->query("quest/qz/jgysj/pass/time")<86400)
	{
		return notify_fail("������Ҫ��кͻ�Ե��̫Ƶ�������ã�\n");
	}
	if (me->query("yusuo/degree")>8)
	{
		return notify_fail("���Ѿ��Խ���������������ھ��ؾ��磬�����ڻ��ͨ��\n");
	}
	if (!me->query("quest/qz/dichuan"))
	{
		return notify_fail("��Ǻ��ĵ��ӣ��޷�����\n");
	}

	if (me->query("party/gongji")<500)
	{
		return notify_fail("������ɹ�������500��Ҫ�ú�Ŭ����\n");
	}
	

	me->query("party/gongji",-500);
	
	tell_object(me,HIC"����ϥ�������������죬���ջ��еġ����������ʮ�ľ�����������������\n"NOR);
	
	me->set_temp("canwu_yusuo",1);
	me->start_busy(999);
	call_out("yusuo_thinking",1,me);
	return 1;
}
int yusuo_thinking(object me)
{
   int i,j;
   if (!me) return 0;
   i=(int)me->query("yusuo/degree");
   
   if(me->query_temp("canwu_yusuo")<(55+random(5)))
   { 
	  me->add_temp("canwu_yusuo",1);
      if(random(2)) tell_object(me,HIG"\n��һ�߷������еġ����������ʮ�ľ���Ҫ��һ�߲���������أ�����ӡ֤��\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬�����һ�����ƺ����Щ����...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��һƬƽ�͡�\n"NOR, ({}));
	  remove_call_out("yusuo_thinking");
	  call_out("yusuo_thinking",3+random(3), me);
   }
   else
   {  
	  me->delete_temp("canwu_yusuo");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  j= random(j);
 	
		tell_object(me,HIG"\n�������ʦ����ָ�㣬�Խ��������ʮ�ľ������������ƺ���Щ�ĵá�\n"NOR);
		 //����30+300Ϊ����
		if(j<5 
			&& me->query("kar")<31
			&& random(me->query_int(1))>(50+i)
			&& random(me->query("kar"))>(17+i))
		 {
			
			tell_object(me,CYN"\n\n��ֻ��һ�������Ƶ�����˲�������ζ���������һȦ�����һ��Сѭ��! \n"NOR);
			me->add("yusuo/degree",1);
			tell_object(me,HBYEL+HIW"\n\n��ϲ��˳����������������"+chinese_number(i+1)+"�ؾ���! \n"NOR);
			me->start_busy(1);
			me->delete_temp("canwu_yusuo");
			log_file("quest/qzyusuo", sprintf("%8s(%8s) ʧ��%d�κ�������������ʮ�ľ�������%d�ؾ��硣jȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/qz/jgysj/pass/fail"),me->query("yusuo/degree"),j,me->query("combat_exp")) );
		 }
		 else
		 {
			me->add("quest/qz/jgysj/pass/fail",1);
			me->set("quest/qz/jgysj/pass/time",time());
			
			tell_object(me,HIY"\n\n�������죬��Ȼ֪������������İ��أ����Ƕ�����ڻ��ͨ����������ȫȻ����Ҫ�졣\n\n"NOR);
			tell_object(me,HBBLU+HIW"\n\n���ܽ��������ʧ�ܣ��ٽ�������\n\n"NOR);
			me->start_busy(1);
			me->delete_temp("canwu_yusuo");
			log_file("quest/qzyusuo", sprintf("%8s(%8s) ���������%d�ؾ���ʱ������ʧ��%d�Ρ�jȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/qz/jgysj/pass/fail"),me->query("yusuo/degree"),j,me->query("combat_exp")) );
		  }

		return 1;
  }

}

int valid_leave(object me, string dir)
{	   

		
		if (dir =="south" && me->query_temp("marks/sit") ) 
		{		   	   
				
				return notify_fail("�����ڵ�����δ����������ж�����\n");
				
		}
		
        return ::valid_leave(me, dir);
}
