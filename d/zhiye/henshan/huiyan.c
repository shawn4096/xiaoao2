inherit ROOM;
#include <ansi.h>

int qcdz_come(object me);
int linghu_come(object me);

int do_answer(string arg);

void create()
{
	set("short", "����¥");
        set("long", @LONG
�����Ǻ�������¥���Ǳ������ľ�¥��������ʱ�Ѿ�ʮ��æµ
�ľ�¥����ȴ�е�������һ�������ʮ�İ��º��ӣ���������������
������һ�ѿ쵶���Ա�ȴ����һ��С��ã������Ǽ����֮ɫ����
òȴʮ��������
LONG );
	set("exits", ([
	       "down" : __DIR__"shop",
	]));
	set("objects", ([
	        __DIR__"npc/tian"   : 1,
	        __DIR__"npc/yilin"  : 1,
	]));

       ////set("no_clean_up", 0);

	//set("coor/x", -10);
	//set("coor/y", -120);
	//set("coor/z", 10);
	setup();
	//replace_program(ROOM);
}

void init()
{
	add_action("do_answer","answer");

}
int do_answer(string arg)
{
	object me=this_player();
	if (!arg) return notify_fail("��Ҫ�ش�ʲô��\n");
	if (arg=="yes" && me->query_temp("kuaidao/askyilin"))
	{
		message_vision(HIG"�ﲮ��˵��������Ȼ$N�д��ľ����ҿ�����������㻹��������ޡ���\n"NOR,me);
		me->set_temp("kuaidao/answeryes",1);
		call_out("qcdz_come",3+random(5),me);
		me->delete_temp("kuaidao/askyilin");
	}
	if (arg=="yes" && me->query_temp("kuaidao/asklhc"))
	{
		message_vision(HIY"�ﲮ��˵��������Ȼ$N�д��ľ����Ҷ���������塱��\n"NOR,me);
		me->set_temp("kuaidao/answerlhcyes",1);
		call_out("linghu_come",3+random(5),me);
		me->delete_temp("kuaidao/asklhc");
	}

	return 1;
	
}

int qcdz_come(object me)
{
	object tian,renying,renxiong,renjie,renhao;
	if (!objectp(tian=present("tian boguang",this_object())))
	  return notify_fail("�ﲮ�ⲻ�ڴ˵أ�\n");
	message_vision(HIR"\n\n����¥�����˺ȵ������Ǹ�������˴󵨣���Ȼ������������ɣ�\n"NOR,me);
	
	if (!objectp(renjie=present("yu renjie",this_object())))
	{
		renjie=new("d/henshan/npc/huiyan/yurenjie");
		renjie->move(environment(this_object()));
	}
	renjie->kill_ob(tian);
	if (!objectp(renxiong=present("hong renxiong",environment(this_object()))))
	{
		renxiong=new("d/henshan/npc/huiyan/hongrenxiong");
		renxiong->move(environment(this_object()));
	}
	if (!objectp(renying=present("hou renying",environment(this_object()))))
	{
		renying=new("d/henshan/npc/huiyan/hou renying");
		renying->move(environment(this_object()));
	}
	if (!objectp(renhao=present("yu renhao",environment(this_object()))))
	{
		renhao=new("d/henshan/npc/huiyan/yurenhao");
		renhao->move(environment(this_object()));
	}
	renxiong->kill_ob(tian);
//	me->kill_ob(renxiong);
	renhao->kill_ob(tian);
	renying->kill_ob(tian);
	if (objectp(tian))
		call_out("taishan_come",1,me,tian);
	else return notify_fail("�ﲮ���Ѿ�������ɵ���ɱ��������ʧ�ܣ�\n");
	return 1;
}
int taishan_come(object me,object tian)
{
	object yuling;
	if (!objectp(yuling=present("yuling zi",environment(this_object()))))
	{
		yuling=new("d/taishan/npc/yulingzi");
		yuling->move(environment(this_object()));
		
	}
	message_vision(HIR"��ʱ��̩ɽ���������Ӻ�Ȼ����������Ȼ�ﲮ�����������������ﲢ�����ϰ�����\n"NOR,me);
	yuling->kill_ob(tian);

	return 1;
}

int linghu_come(object me)
{
	//environment()
	object linghu,tian;
	if (!objectp(tian=present("tian boguang",this_object())))
		return notify_fail("�ﲮ�ⲻ�ڴ˵�,���ܹ��̽�����\n");
	
	message_vision(HIY"������ʱ����Ȼ����¥�����˺�����˭����������µڶ����ѵ����·��������ͷô����\n"NOR,me);

	message_vision(HIR"\n\nһ����Ӱһ���������ȵ������ﲮ�⣬�����������´������书��һ�ġ�é�޽�����ô��\n"NOR,me);
	
	if (!objectp(linghu=present("linghu chong",environment(this_object()))))
	{
		linghu=new("d/huashan/npc/linghuchong");
		linghu->move(environment(this_object()));
	}
	linghu->kill_ob(tian);
	tian->kill_ob(linghu);
	//me->kill_ob(linghu);
	return 1;
}