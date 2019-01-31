// lagoon.c ��ʯ
// By Looklove for a Game
// Last change at 2k/5/27 by Looklove
// 2002.4.18 update

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",HIC"��ʯ"NOR);
	set("long", @LONG
���ǰ�������ͻ����һ���ʯ���������ƽ�����������ٿ���������
����ʮ�ˡ������ĺ�ˮһ�δγ������������г���Ĵ�������ֻ��֪���ĺ���
���������Ͽգ����˴��ų�����ڸ����Ľ�ʯ�ϡ�һ˿�������Ʋ����赭д��
Ĩ��Զ��������У��·�һ��ˮī����ż���м�ֻ�������С���ˮ��Ӻ�ˮ
�����������������ߵĽ�ʯ�ϡ�
LONG
	);
	set("outdoors","����");
	set("exits",([
		"westdown" : __DIR__"island5",
		"eastup" : __DIR__"lagoon1",
	]));
	set("objects", ([
                MISC_D("beike") : 1,
	]));
	setup();
}

void init()
{
	add_action("do_fish","fish");
	add_action("do_fish","diaoyu");
	add_action("do_nosleep","sleep");
	add_action("do_shou","shouxian");
	add_action("do_nosay","say");
}

int do_fish()
{
	object me = this_player();

	if (me->is_busy()) return notify_fail("��������æ���أ�\n");

	if (me->query("mud_age") / 4 >= me->query("combat_exp"))
		return notify_fail("�㻹�Ƕ໨��ʱ�������ɣ�����书�ķ��ˡ�\n");

	if (me->query("potential") >= me->query("max_pot"))
		return notify_fail("�����������˶�����Ǳ�ܷ����������ɡ�\n");

	if (present("yu",  environment(me)))
		return notify_fail("�����Ѿ���ô�����ˣ���Ҫ�������ﰡ��\n");

	if (!present("yu gan", me))
		return notify_fail("��Ԩ���㣬�����˶�������û����ͣ�������ô��������\n");

	if (me->query("jingli") < 200 )
		return notify_fail("�����̫���ˣ����Ǹ����ٵ��ɡ�\n");

	if (me->query_temp("gb/fish"))
		return notify_fail("�����߰ɣ�����ҧ����Ĺ��ء�\n");

	if (present("hai gui", me) && (random(me->query("jingli"))<500)) {
		tell_object(me,HIG"�������������Ҫ���߳�ȥ��һֻ�󺣹���������������"+
			"����Ľ���ҧ��һ�ڡ����۵�����������\n"NOR);
		me->receive_wound("qi", 100+random(100), "������ҧ");
		me->start_busy(5);
		return 1;
	}

	tell_object(me,"�㽫������ڹ��ϣ�һ�����е���ͣ�����˦�˳�ȥ��\n");
	me->receive_damage("jingli", 20);
	me->start_busy(2);

	if (!random(4)) {
		tell_object(me,HIC"��ͻȻ�����������һ���������Ϲ��ˣ�������(shouxian)����\n"NOR);
		me->set_temp("gb/fish",1);
	} else tell_object(me,"ֻ����Ưһ����һ��С��������Ե��ˡ��㽫�չ�ק��������\n");
	return 1;
}

int do_shou()
{
	object me = this_player();
	object ob,ob1,ob2;
	int i;

	ob = present("yu gan",me);
	ob2 = present("yu",me);

	if (!ob) return notify_fail("�������أ�\n");

	if (!me->query_temp("gb/fish"))
		return notify_fail("��˦�;������ߣ��и��ԣ�\n");

	if (me->is_busy())
		return notify_fail("�𼱣���������\n");

	if (me->query("jingli") < 200 )
		return notify_fail("�����̫���ˣ����Ǹ����ٵ��ɡ�\n");
	me->delete_temp("gb/fish");

	if (random(me->query("str")) < 10 && !random(5)) {
		tell_object(me,HIY"ͻȻ��ĸ����Ҷ��������������������㡣\n"
			"������ק���᲻�����֣���������˴��ͳ����˺��\n"NOR);
		destruct(ob);
		if (random(me->query("kar"))>2 && random(10)>3) {
			tell_object(me,HIG"��һ�١����١����ò��������ϰ���������δ����ڴ�ڴ��Ŵ�����\n"NOR);
			me->set("water", me->max_water_capacity()+200);
		} else me->unconcious();
		return 1;
	}
	me->receive_damage("jingli", 100+random(50));
	me->start_busy(1);
	if (ob2 && (random(me->query_str(1)) <20)) {
		tell_object(me,HIC"��������͵Ĺ���һ��������ֱ��ֱĽ���ˮ�\n"NOR);
		destruct(ob2);
		return 1;
	}
	if ( random(me->query_int(1)) > 10)
	if (me->add("potential",5+random(5)) > me->query("max_pot"))
		me->set("potential", me->query("max_pot"));
	if (random(me->query_str(1)) > 30 && random(me->query("kar")) < 10){
		tell_object(me,"���������ͣ����ž��һ�����ˡ�\n");
		me->delete_temp("find/yugan");
		destruct(ob);
		new("/d/gb/obj/yugan2")->move(me);
		return 1;
	}
	if (random(me->query("kar")) < 10 && !random(5)) {
		tell_object(me,HIG"����������ק�����������ֹ��������һֻ�Ʋ�Ь��\n"
			"�������ƿڴ������������ĸ����˵����Ӳ�Ь������\n"NOR);
		return 1;
	}

	i = 1+random(7);

	if( i == 2 ) {	// gui
		if( me->query("diaogui") < 1000 ) {
			me->add("diaogui",1);
			if( me->query("diaogui") >= 15 ) me->set("diaogui",time());
		}
		else if( (time()-me->query("diaogui")) < 86400 ) {	// 24 hour
			if( !random(6) ) {
				tell_object(me,HIG"����������ק�����������ֹ��������һֻ�Ʋ�Ь��\n"
					"�������ƿڴ������������ĸ����˵����Ӳ�Ь������\n"NOR);
				return 1;
			}
		}
		else me->set("diaogui",1);
	}

	tell_object(me,HIG"�������ؽ�һ��������ק��������\n"NOR);
	ob1=new("/d/gb/obj/fish"+i);	
	if(!ob1->move(me)) ob1->move(this_object());
	return 1;
}

int do_nosleep()
{
	object me = this_player();
	tell_object(me,"���ﺣ��ܴ�С�����������ĵ���ĵط�˯�ɡ�\n");
	return 1;
}

int do_nosay(string arg)
{
	int times;
	object me = this_player();

	times = me->query_temp("diaoyu_say");

	me->add_temp("diaoyu_say", 1);
	if( random(times)>10 ){
		switch(random(4)){
			case 3:
				tell_object(me,HIG"һ�����ˮ�淭��������Զ����\n"NOR);
				break;
			case 2:
				tell_object(me,HIG"һȺС������ű�������ȥ��������������\n"NOR);
				break;
			case 1:
				tell_object(me,HIG"һȺ��·��������ţ�������Զ����\n"NOR);
				break;
			default:
				tell_object(me,HIG"ֻ����Զ��ˮ����ͨһ�������㷺����һƬˮ����\n"NOR);
				break;
		}
		me->delete_temp("diaoyu_say");
	}
	return COMMAND_DIR"std/say"->mail(me, arg);
}