// Date: YZC 96/01/19

inherit ROOM;
int update_player(object me);
#include <ansi.h>

void create()
{
	set("short", "������һ��");
	set("long", @LONG
����һ�伫Ϊ��ª���������������ܣ����˼�������⣬���ڿյ�����
���������������İڷ��ż��������ҷ��ڵĻƲ����ţ���λ�뷢���׵�
��ɮ�������������Ŀ�붨�������Ǳ���ʮ���޺��������еĵط������پ�
���书�����ڴ������
LONG
	);

	set("exits", ([
//		"south" : __DIR__"zoulang1",
		"north" : __DIR__"banruo2",
	]));

	set("objects",([
		CLASS_D("shaolin") + "/cheng-xin" : 1,
	]));
	set("coor/x",110);
  	set("coor/y",230);
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
	if (!me->query_temp("qys/askchengxin"))
	{
		return notify_fail("������������˲��������������������㣿\n");
	}
	
	if (me->query("quest/sl/qys/pass")) return notify_fail("���Ѿ��⿪����ǧҶ�־�����\n");
		
	if (time()-me->query("quest/sl/qys/time")<86400)
	{
		return notify_fail("�����书����Ҫ����������ڿ췴��Υ���˶���ı��⣡\n");
	}
	if (!arg||arg!="����ǧҶ��")
	{
		return notify_fail("�˼侲���������ּ��ַ����֮�أ������ַ��书�㼯�ڴˡ�ֻ�ܲ����ַ���Ҫ��\n");
	}
	message_vision(CYN"\n\n�㷭�������ַ��ؼ���Ҫ�����������ֵ��似��Ҫ������̾Ϊ��ֹ��\n"NOR, me);
	message_vision(CYN"\������ں�嫵��ַ��о��У���������һ�����Ϸ�����\n"
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
       message_vision(HIC"$N��Ȼ������˫�ۣ�����������ǧҶ��Ҫ�����ɾ���һ��֮���������ַ�Ҫ���Ǻܸߵġ�\n"NOR,me);
	   message_vision(HIC"��һζ��äĿ����Ӳ��Ҳ���ǳ���֮�ƣ������վ�������Ѫ��֮�����������׽��\n"NOR,me);
	   message_vision(HIC"�Ĺ���������˫��֮�ϣ��⹦���վ��������ɵģ��������˴˽ڣ��㽫��������\n"NOR,me);
	   message_vision(HIC"���ž������У���Ȼ�䡰����Ѩ��һʹ���̶����͹�Ѩ��һ�������ѵ����������ֲ��ġ�\n"NOR,me);
	   message_vision(HIC"��Ѫ�����Ȼ��ͨ��\n"NOR,me);

	   message_vision(HIG"��ϲ�㣬����ǧ�����գ�������������ǧҶ�־�����\n"NOR,me);
	  
	   log_file("quest/qianyeshou",sprintf("%s(%s) �����ְ�����һ��������������ǧҶ�ֵľ�Ҫ���޳�����ǧҶ�֡���Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,t,me->query("quest/sl/qys/fail"),me->query("combat_exp"),me));
	  // me->set("title",HIC"����"HIY"��Ӱ������"NOR);
	   me->set("quest/sl/qys/pass",1);
	   me->set("quest/sl/qys/time",time());
	   me->delete_temp("qys");
	   me->start_busy(1);
	   return 1;
	}
	else
	{
		message_vision(HIY"\n$N��Ȼ����֪��������ǧҶ�ֵ��ռ����壬���������ʹ�õľ�������һʱ֮��ȴ��������⡣\n"
						+"����ǧҶ��������û�з��ӳ����������㻹���д������²�����ϰ�ˡ�\n"NOR,me);
	    message_vision(HIR"��������ǧҶ�־���ʧ�ܣ�\n"NOR,me);

		log_file("quest/qianyeshou",sprintf("%8s%-10s�����ְ�����һ������������ǧҶ�ֲ�û�гɹ�������Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,t,me->query("quest/sl/qys/fail"),me->query("combat_exp"),me));
		me->add("quest/sl/qys/fail",1);
		me->set("quest/sl/qys/time",time());
		me->delete_temp("qys");
		me->start_busy(-1);
        return 1;
	}

}