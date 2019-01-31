// ITEM: /d/huashan/obj/ziyin_book_1.c
// Date: Look 99/03/25

inherit ITEM;

void create()
{
    set_name("������ܾ�", ({ "ziyin yin", "book", "ziyin" }));
	set_weight(200);
	set("unit", "��");
	set("long", "����һ��������ܾ������滭���˸��ִ������ŵ����ơ�\n");
//	set("treasure",1);
    set("value", 50);
	set("material", "paper");
	set("skill", ([
			"name":	"ziyin-yin",	// name of the skill
			"exp_required":	5000,	// minimum combat experience required
            "jing_cost": 30+random(25),// jing cost every time study this
			"difficulty":   50, // the base int to learn this skill
			"min_skill":   100, // the base int to learn this skill
			"max_skill":	200	// the maximum level you can learn
		      ]) );
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

	if ( me->query("neili") < 100 )
		return notify_fail("�������������\n");

	if (environment(me)->query("pigging"))
		return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

	if (environment(me)->query("pending"))
		return notify_fail("�˵ز�����ϰ�����������\n");

	if (environment(me)->query("sleep_room"))
		return notify_fail("���Ҳ�����������Ӱ�������Ϣ��\n");
 
	if (environment(me)->query("no_fight"))
		return notify_fail("�˵ز�����ϰ�����������\n");

	if ( me->query("jing") < 40 )
		return notify_fail("��ľ�̫���ˣ������ж������������\n");
	if ( me->query_skill("literate", 1) < 10 )
		return notify_fail("�����д�ֵ�֪ʶ̫���ˣ��Ͻ�ѧ���Ļ�֪ʶ�ɡ�\n");
	if ( me->query_skill("ziyin-yin", 1) > 200 )
		return notify_fail("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
	if ( me->query_skill("ziyin-yin", 1) < 100 )
		return notify_fail("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫����ˣ�û��ѧ���κζ�����\n");
	tell_object(me, "����ϸ�ж��š���������ľ���֮����\n");
	me->receive_damage("jing", random(50) );
	me->improve_skill("ziyin-yin", me->query_int());
	return 1;
}