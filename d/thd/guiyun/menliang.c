//��������
//menliang.c ������ڵ��߷��䣬��Ӱ��������ͼ by sohu@xojh
#include <ansi.h>
inherit ROOM;
int do_jump(string arg);
int story1(object me);
int story2(object me);
int do_look(string arg);
void create()
{
	set("short","����");
	set("long",@LONG������������������������ϵ�һ�����������ȸ��ʣ��ƹ�谵��
ʵ���ǲ���ĺõط�������������ȥ��ȴ��������͸���ƹ⣬һλ��ΪƯ��������
��Ů��һȺѾ����Χ����һ��
LONG
);
	/*  set("object",([
	__DIR__"obj/luchenfen.c" :     1,
	]));  
	set("exits",([
		"east" : __DIR__"zoulang2",
		"south" : __DIR__"houting",
        "north" : __DIR__"wofang1",
	]) );*/
	set("no_clean_up",0);
	set("indoors", "����ׯ");
	setup();
}
void init()
{
	//�����ж�
	
	if (this_player()->query_temp("slbw/askguo3"))
	{ 
		add_action("do_look","toukan");
		}
	add_action("do_jump","jump");
	add_action("do_jump","tiao");
	
}

int do_look(string arg)
{
	object me = this_player();

	if (me->is_busy() || me->is_fighting())	return notify_fail("����æ���أ�\n");
	
	if (arg == "����"||arg == "indoors"||arg == "����" )
	{
		message_vision(HIC"$N����ָ���ƴ����ϴ�ֽ�������ڿ�ȥ��\n"NOR, me);
		call_out("story1",5,this_player());
		return 1;
	}
	return 0; 
}

int do_jump(string arg)
{
	object me = this_player();

	if (me->is_busy() || me->is_fighting())	return notify_fail("����æ���أ�\n");
	
	if (arg == "down" )
	{
		message_vision(HIC"$N������������Ծ��������\n"NOR, me);
		me->move("/d/thd/guiyun/zoulang3");
		return 1;
	}
	return 0; 
}

int story1(object me)
{
    
    message_vision(HIG"\n�Ȳ���С���ʱ����ֻ����ǽ�⿦��һ��΢�죬$N��������֮��ֻ��Χǽ��Ծ��������Ӱ������������������ؤ��\n"
	+"��ؤ�ߵ�¥�£������������ڣ�һ��Ѿ�߽ҿ�������˵��������ؤ���Ӣ�۵���ô���������ա�����\n"
		   +"����һ��������ϵ���ؤ˵�������������裬�����ҵ�ʦֶ�����������ˡ���\n"
		   +"\n\n�̴�С�������ԭ������ǰ�������硣ؤ����λӢ���������壬���������������СŮ�ӽ��յü���λ�𷶣��������ҡ���������\n"
		   +"\n�����ֵ����������뵽���÷���Ъ�ޣ��⼸λ��ʹҲ������ȥ���������жԸ��ǿ�ͽ�ķ��ӡ����̴�С�����������Ȼ���յ�΢��\n"
		   +"����Ҫ��ǰ��һ���е������������ȥ����\n"
		   +"\n\n�������������Ǻ����������Ͻ����������������ã���Ҷ���һ���ˣ�����αط���ô�˴ˣ����̴�С�㱾���ƺ�ԾԾ���ԣ���������\n"
		   +"��ô˵�ˣ�����Υ�֣����˸���˵��������ôһ��ȫ������ǰ���������ˡ���˵�գ�����Ѿ��ӯӯ��¥��ȥ��\n"
		   +HIW"\n\n�����ߵ�С�㴲�ߣ��ҿ��屻��ЬҲ���ѣ�������ľ�����������ı���֮�ϣ��������˵���������¥ȥ���ʹ����������ţ�����\n"
		   +"�Һ�����ɶ��֡��������˴�Ӧ�˶�ȥ���������ϳ񱻣�����ɴ�ʣ�Ϩ����򣬷�������ԡ�\n", me);
		   call_out("story2",5,this_player());
    return 1;

}
int story2(object me)
{

    message_vision(HIY"\n\nԼĪ����һ�����Σ�����ǰ�浱���еĸ��򡰵��ơ����ơ����������Ĵ�����������š��ġ���һ������԰��Ͷ��һ��ʯ������\n"
	                  +"����Ƭ�̣�Χǽ��ܽ����ˣ���Ծ��¥�������˻����ӣ�����С�㴲ǰ���漴�ִ�Ϩ���ۡ���������һ��֮�ʣ��������˵���ò��\n"
		              +"\n\nԭ������ŷ������ЩŮ����װ�������µ�Ů���ӡ�����Ů�����ߵ���ǰ���ҿ����ӣ����񱻶�ͷ�����������ϣ�����§ס��\n"
		              +"��������Ů�����ſ�һֻ�󲼴���̧������������У��鶯���ӣ��ѰѴ����ս�����Ů������ͷ���Ŵ�װ�˵��ַ������쳣����\n"
		              +"����һ�������˵ģ��ڰ�֮����̶��ͣ�ȫû���졣����Ů���Ӹ�ִ����һ�ǡ�̧�𲼴���Ծ��¥ȥ��\n"
	                  , this_player());
    me->delete_temp("slbw/askguo6");
	me->delete_temp("slbw/tiaoliang");
	me->set_temp("slbw/askcheng",1);
    return 1;

}
