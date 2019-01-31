// ITEM: /d/huashan/npc/obj/zixia.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ITEM;

void create()
{
    set_name(MAG"��ϼ�ؼ�"NOR, ({ "zixia miji", "miji", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_get", "�������������뿪�Ƕ���\n");
		set("no_drop", 1);
		set("no_give", 1);
		set("no_stealing", 1);
		set("long", "'��ɽ�Ź�����ϼ��һ'������һ�Ừɽ�ɵ���ϼ���ؼ���\n");
        set("unique", 1);
		set("treasure",1);
		set("value", 500);
		set("material", "paper");
		set("skill", ([
            "name": "zixia-gong",   // name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	40,	// jing cost every time study this
			"difficulty":	30,	// the base int to learn this skill
			"max_skill":	350	// the maximum level you can learn
		]) );
	}
	setup();
}
void init()
{
	if (environment() == this_player())
		add_action("do_du", "read");
}

int do_du(string arg)
{
	object me = this_player();
       int lv;
	if (!id(arg)) 
		return notify_fail("��Ҫ��ʲô��\n");

	if ( me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");

	if ( !me->query("quest/huashan/zixia/pass") )
		return notify_fail("������ô�õ�����ϼ�ؼ����İ���\n");

	if ( query("owner") != me )
		return notify_fail("������ô�õ�����ϼ�ؼ����İ���\n");

	if ( me->query("neili") < 1500 )
		return notify_fail("�������������\n");

	if (environment(me)->query("pigging"))
		return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

	if (environment(me)->query("pending"))
		return notify_fail("�˵ز�����ϰ����ϼ�ؼ�����\n");

	if (environment(me)->query("sleep_room"))
		return notify_fail("���Ҳ�����������Ӱ�������Ϣ��\n");
 
	if (environment(me)->query("no_fight"))
		return notify_fail("�˵ز�����ϰ����ϼ�ؼ�����\n");

	if ( me->query("jing") < 40 )
		return notify_fail("��ľ�̫���ˣ������ж�����ϼ�ؼ�����\n");

	if ( me->query_skill("zixia-gong", 1) > 250 )
		return notify_fail("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
	
	tell_object(me, "����ϸ�ж��š���ϼ�ؼ����ľ���֮����\n");
	me->receive_damage("jing", random(30) );
	me->improve_skill("zixia-gong", me->query_int());
	return 1;
}