//daxiong.c

inherit ROOM;
#include <ansi.h>
int do_tiao(string arg);

void create()
{
	set("short", HIY"���۱���"NOR);
	set("long", @LONG
�����������µĴ��۱��������䣬�����ļ䡣���й�������������
�����Ҹ������⡢������λ������һȺɮ�����Է����о��������ҷ��黨΢
Ц����̬�����˶ٸ���Ȼ�𾴡�������ÿ�����Ƿ��ɴ�ʦ�ټ�����Ⱥɮ
����֮����
LONG
	);
        set("no_fight",1);
       	
		set("exits", ([
		 "south" : __DIR__ "pingtai",
                 "north" : __DIR__ "stoneroad1",
       ]));

	
	set("coor/x",50);
  set("coor/y",300);
   set("coor/z",120);
   setup();
}
void init()
{
    object me=this_player();
	if (me->query_temp("klbs/askhe")
		&&me->query_temp("kl/baihe/fightwei")
		&&me->query_temp("kl/baihe/fightpan")
		&&me->query_temp("kl/baihe/fightfang"))
	{
		message_vision(YEL"$N��������ÿ�ռ�����Ϊ������񣬵���û������˸ߴ������Ħ�������̲�ס���¹�ĳ嶯��\n"NOR,me);
		message_vision(YEL"$N�����º��̲�ס����һ��������������������ºô��������ʦ���������Ͱ��������ҿ����ִ���ж�ϡ��ƽ������\n"NOR,me);
		message_vision(HIC"$N��ͷ���������������֮�ߣ������Ժúÿ���һ������������ɮ��\n"NOR,me);
		message_vision(HIC"$N������������ɮ������״̬�����ɵ����е�����֡�\n"NOR,me);
		//me->delete_temp("kl/baihe/fightwei");
		//me->delete_temp("kl/baihe/fightfang");
		//me->delete_temp("kl/baihe/fightpan");
		//me->delete_temp("klbs/askhe");

		add_action("do_tiao","tiao");

	}
	
}
int do_tiao(string arg)
{
	object me=this_player();
    if (arg !="shenxiang" && arg !="����")
		return notify_fail("���۱�����һ����ʥ�ĵط�����������ϴ�������ʲô��");
	if (me->query_skill("dodge",1)<350 || me->query_dex()<60)
	     return notify_fail("������ܸߣ�����������\n");
	tell_object(me,HIC+me->query("name")+"����Ծ��ವ�һ��������������֮�ϡ�\n"NOR);
	
	me->set_temp("kl/baihe/jump",1);
	me->move("d/shaolin/shenxiang");
	return 1;


}

