// Room: /d/shaolin/banruo7.c
// Date: YZC 96/01/19

inherit ROOM;

#include <ansi.h>



void create()
{
	set("short", "�������߲�");
	set("long", @LONG
����һ�伫Ϊ��ª���������������ܣ����˼�������⣬���ڿյ�����
���������������İڷ��ż��������ҷ��ڵĻƲ����ţ���λ�뷢���׵�
��ɮ�������������Ŀ�붨�������Ǳ���ʮ���޺��������еĵط������پ�
���书�����ڴ������
LONG
	);

	set("exits", ([
		"south" : __DIR__"banruo6",
		"north" : __DIR__"banruo8",
	]));

	set("objects",([
		CLASS_D("shaolin") + "/cheng-ling" : 1,
	]));
	set("coor/x",110);
	set("coor/y",290);
	set("coor/z",110);
	setup();
}
void init()
{
	object me=this_player();
	add_action("do_xiuxing","canchan");
}

int do_xiuxing(string arg)
{
	
	int j,t;
	object me=this_player();
	if (me->query("family/family_name")!="������")
	{
		return notify_fail("�㲻�����ֵ��ӣ����������־�����\n");
	}
	if (!me->query_temp("rysxt/askchengling"))
	{
		return notify_fail("������������˲��������������������㣿\n");
	}
	if (time()-me->query("quest/sl/rysxt/tiezhou/time")<86400)
	{
		return notify_fail("�����书����Ҫ����������ڿ췴��Υ���˶���ı��⣡\n");
	}
	if (!arg||arg!="���㹦")
	{
		return notify_fail("�˼侲���������ּ��ȷ����֮�أ������ȷ��书�㼯�ڴˡ�ֻ�ܲ����ȷ���Ҫ��\n");
	}
	message_vision(CYN"\n\n�㷭�������ȷ��ؼ���Ҫ�����������ֵ��似��Ҫ������̾Ϊ��ֹ��\n"NOR, me);
	message_vision(CYN"\������ں�嫵��ȷ��о��У���������һ�����Ϸ�����\n"
			           +"��Щ��ʽ������˵���Ѿ���Ȼ���أ�һʱ֮�侹Ȼ��������\n"
					   +"һʱ�������ǲ��⣬Ϊ�λ�������������\n"NOR,me);
	
	j=random(me->query("kar"));
	
	t=20;
    if(me->query("m-card-vip")) t =  18;
    if(me->query("y-card-vip")) t =  15;
    if(me->query("buyvip"))     t =  10;
	t= random(t);
	
	if (me->query("kar")<31
		&& j>26
		&& t<3)
	{
       message_vision(HIC"$N��Ȼ������˫�ۣ����������㹦Ҫ�����ɾ���һ��֮���������ȷ�Ҫ���Ǻܸߵġ�\n"NOR,me);
	   message_vision(HIC"��һζ��äĿ����Ӳ��Ҳ���ǳ���֮�ƣ������վ�������Ѫ��֮�����������׽��\n"NOR,me);
	   message_vision(HIC"�Ĺ���������˫��֮�ϣ��⹦���վ��������ɵģ��������˴˽ڣ��㽫��������\n"NOR,me);
	   message_vision(HIC"���ž������У���Ȼ�䡰β��Ѩ��һʹ���̶�����ɽѨ��һ�������ѵ����������Ȳ��ġ�\n"NOR,me);
	   message_vision(HIC"��Ѫ�����Ȼ��ͨ��\n"NOR,me);

	   message_vision(HIG"$N��ϲ�㣬����ǧ�����գ�����������Ӱ�����ȵ����㹦������\n"NOR,me);
	  
	   log_file("quest/rysxttiezhou",sprintf("%s(%s) �����ְ����ã����������㹦�ľ�Ҫ���޳������񹦡���Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,t,me->query("quest/sl/rysxt/tiezhou/fail"),me->query("combat_exp"),me));
	   //me->set("title",HIC"������"HIY"��Ӱ�����ȴ���"NOR);
	   me->set("quest/sl/rysxt/tiezhou/pass",1);
	   me->delete_temp("rysxt");
	   me->start_busy(1);
	   return 1;
	}
	else
	{
		message_vision(HIY"\n$N��Ȼ����֪���������ȹ����ռ����壬���������ʹ�õľ�������һʱ֮��ȴ��������⡣\n"
						+"���㹦������û�з��ӳ����������㻹���д������²�����ϰ�ˡ�\n"NOR,me);
	    message_vision(HIR"������Ӱ�����ȵ����㹦ʧ�ܣ�\n"NOR,me);

		log_file("quest/rysxttiezhou",sprintf("%8s%-10s�����ְ����ã��������㹦��û�гɹ�������Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,t,me->query("quest/sl/rysxt/tiezhou/fail"),me->query("combat_exp"),me));
		me->add("quest/sl/rysxt/tiezhou/fail",1);
		me->set("quest/sl/rysxt/tiezhou/time",time());
		me->delete_temp("rysxt");
		me->start_busy(-1);
        return 1;
	}

}



