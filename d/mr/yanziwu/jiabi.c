// /u/beyond/mr/jiabi.c
// this is made by beyond
// update 1997.6.20
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short",HIW"�б�"NOR);
	set("long",@long
������ܺ����һ���бڣ�Ҫ�����ƿ���ܵĺ��档���п��ܳ�ȥ��
��ܱ��������һЩ�����ؼ�������Ľ�ݺ��ĵ�������֮�������ڡ�����
���һ��ǽ�ϣ������һ��ͼ��������ȥ����һ����������ͼ��picture����
long);
	set("exits",([
             "north" : __DIR__"hssg",
	]));
	set("item_desc",([
		"picture" : "���ͼ����Ľ�ݺ��ĵ��Ӳ���Ľ���ķ��ľ���ͼ����Ľ�ݵ��ӵ��ڴ������о�(yanjiu)��\n"
	]));
	setup();
}

void init()
{
	
	add_action("do_push", "push");
	add_action("do_read", "yanjiu");
}

int do_push(string arg)
{
	object me;
	me = this_player();

	if (arg !="shujia") 
		return notify_fail("��Ҫ��ʲô��\n");
	if( arg=="shujia"){
		write("������һ����ܣ����������һ�ơ�\n");
		message("vision", me->name() + "����һ��ͻȻ�����ˡ�\n", environment(me), ({me}) );
		me->move(__DIR__"shufang");
		message("vision", me->name() + "���˹�����\n", environment(me), ({me}) );
	}
	return 1;
}

int get_object(object ob)
{
        if(userp(ob))
        return 1;
        return 0;
}

int valid_leave(object me, string dir)
{
	mapping myfam;
	object *obj;
     
	myfam = (mapping)me->query("family");
     
	if ( myfam && myfam["family_name"] != "����Ľ��" &&dir=="north") {
		return notify_fail("һλĽ�ݼҶ���Ȼ�����������˳�������ס����˵�����ô���ʩˮ����������\n˵�꣬��λ�Ҷ�����һ�Σ����˻ذ�����\n");
	}
     
	obj = filter_array(deep_inventory(me),(:get_object:));
	if( sizeof(obj) && dir=="north" ){
		tell_object(me,"��һ��С�ģ����ż����ˡ�\n");
		obj[0]->move(environment(me));
		me->unconcious();
		return 0;
	}
	return ::valid_leave(me, dir);
}
int do_read(string arg)
{
	object me=this_player();	
	if (!arg||arg!="picture") 
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
		return notify_fail("�����д��֪ʶ̫���ˣ��Ͻ�ѧ���Ļ�֪ʶ�ɡ�\n");
	if ( me->query_skill("douzhuan-xingyi", 1) < 100 )
		return notify_fail("��Ķ�ת������100������������������Ƥë������Ҳ���򲻳�ʲô��������\n");
	if ( me->query_skill("murong-xinfa", 1) > 200 )
		return notify_fail("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
	tell_object(me, "����ϸ�ж���ǽ�ϵġ�Ľ���ķ����ľ���֮����\n");
	if ( me->query_skill("murong-xinfa", 1) > 150 )
	{
		me->receive_damage("jing", 10+random(50) );
		me->improve_skill("murong-xinfa", (int)me->query_int()/4);
	}else if (me->query_skill("murong-xinfa", 1) > 100)
	{
		me->receive_damage("jing", random(50) );
		me->improve_skill("murong-xinfa", (int)me->query_int()/3);
	}
	return 1;
}