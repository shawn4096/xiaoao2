// Room: /d/emei/cangjinglou.c
#include <ansi.h>

inherit ROOM;
int do_fan(string arg);
void create()
{
	set("short", "�ؾ�¥");
	set("long", @LONG
�����Ǳ����µĲؾ�¥����¥�������������˺ö���ܣ����ϰ����˾��顣
�����������µ�Сʦ̫����һ�Ǿ����ض��ž��顣
LONG
	);

	set("exits", ([
	    "out" : __DIR__"daxiongdian",
	]));
	set("objects",([
		"/d/emei/obj/fojing1" : 1,
		"/d/emei/obj/fojing2" : 1,
		"/d/emei/npc/daoming" : 1,
	]));
	setup();
}
int valid_leave(object me, string dir)
{
	if (dir == "out" && present("shu", me) && objectp(present("daoming shifu", environment(me))))
		return notify_fail("����Сʦ���ȵ������ؾ�¥���鼮���������\n");

	return ::valid_leave(me, dir);
}
int init()
{
	 add_action("do_fan","fan");

}
int do_fan(string arg)
{
	object me=this_player();
	if (!arg||arg!="����")
		return notify_fail("�����ɲؾ����صأ����ҷ�ʲô��\n");
	
	//if(me->is_fighting()) return 0;
	
	if (me->query("quest/em/zzr/pass"))
	{
		return notify_fail("���Ѿ��⿪����ؾ��ˣ����˶����ɲؾ����صأ����ҷ�ʲô��\n");

	}
	if (time()-me->query("quest/em/zzr/time")<86400)
	{
		return notify_fail("������̫Ƶ����,���������ɻ�!\n");

	}
    if (!me->query_temp("quest/em/zzr/askzhou"))
  		return notify_fail("���˶����صأ��������ҷ�ʲô��\n");


		
		if(me->query("family/family_name")!="������")
			if (!me->query_temp("ryb/jiuyin_askdue"))
				return notify_fail("���˶����ɲؾ����صأ������ɵ����ҷ�ʲô��\n");
	 
		if(me->query("shen")<0)
			return notify_fail("������а����Ȼ������ؾ���ƽ��֮��������\n");

		if(me->query("quest/em/zrr/fail")>=3 && me->query("registered")<3)
			return notify_fail("�Ѿ���δ��ڣ�����ô����û������,�湻���ģ���\n");	
	
		if (me->query_skill("yinlong-bian",1)<450)
			return notify_fail("��������޷�����450�����ɶ�û�У�����Ҳ�״��\n");
		message_vision(HIC"$N�ڲؾ����в��Ϸ��ľ��飬�ƺ����ڲ���ʲô��\n"NOR, me);

	
	
		me->set("quest/em/zzr/time",time());
		me->set("quest/em/zzr/combat_exp",me->query("combat_exp")); 
	
		message_vision(HIY"��Ȼ��$N�ƺ��ҵ���һ�����飬��ʱ��ϲ�����鲻�Խ������ͷ��Ŀ�����\n"NOR,me);
	
		me->start_busy(999);
		remove_call_out("think_ylbf");
		call_out("think_ylbf",1,me);
		return 1;
	
}

int think_ylbf(object me)
{
    int i;
	i=random(10);
	if(me->query_temp("canwu_ylbf")<(10+random(5)))
    {  
	  me->add_temp("canwu_ylbf",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n����ϸ�����������Ľ��������������ڵ���ʽ�˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n��Ȼ�����ƺ�ץס��һЩ����\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n���������״̬������һƬ�������ƺ�Ҫץס�Ǹ������ˣ�..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n������Ķ����������ģ������������ƺ���Щ����.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ��ƺ�����ƿ����..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n��˼άƯ���ڿ��У�����Ӥ����ԡ.������ˬ.\n"NOR);
			break;
		default:tell_object(me,YEL"\n��̾��һ�������������ǲ�����Ч����.\n"NOR);
			break;
	  }     

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  //remove_call_out("think_ssjf");
	  call_out("think_ylbf",3+random(3), me);
	  return 1;

   } 
	else if( i>=8 && random(me->query("kar"))>26)
	{
		tell_object(me,HIC"\n�㰴����������ָ�㣬����Լ���ϰ���ã��������޷��İ����ƺ���Щ�ĵá�\n"NOR);
		tell_object(me,HIY"\n��������޵���ʽ��ͷ��ʼ������һ·�����������������硣Խ��Խ�Ǵ��졣\n"NOR);
        tell_object(me,HIC"\n��Ȼ�䣬�����һ������ǰ�������Ҳ�벻���׵������Ȼ���Ȼ��ͨ���̲�ס������Ц.\n"NOR);		
		
		me->set("quest/em/zzr/pass",1);
		me->set("quest/em/zzr/time",time());
		log_file("quest/ylbfjueji", sprintf("�ɹ���%8s(%8s) ʧ��%d�κ󣬳������������޷��ںϵľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/em/zzr/fail"),i,me->query("combat_exp")) );
		me->delete_temp("canwu_ylbf");
		me->delete_temp("ryb");
	}
	else
	{		
		tell_object(me,HIY"�㷭�����Ȿ������죬��Ȼ������һЩ������˼��������ʽ�����Ƕ����������ᵽ�İ����ȫȻ����Ҫ�졣\n\n"NOR);
		tell_object(me,HIG"������Զ��һ����Թ��̾Ϣ������һ����ɫ��Ӱ��Զ��ƮȻ��ȥ��\n\n"NOR);
		tell_object(me,HIY"��Ȼ�䣬��о�ʧȥ��ʲô��\n���������޷�����ʧ�ܣ�\n\n"NOR);
		log_file("quest/ylbfjueji", sprintf("ʧ�ܣ�%8s(%8s) �����޷����ɽ���ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/em/zzr/fail"),i,me->query("combat_exp")) );
		me->set("quest/em/zzr/time",time());
		me->add("quest/em/zzr/fail",1);
		me->delete_temp("canwu_ylbf");	
		me->delete_temp("ryb");
	}
	me->start_busy(1);
	return 1;

}