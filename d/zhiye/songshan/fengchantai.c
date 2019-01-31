//Room fengchantai.c ����̨

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"����̨"NOR);
	set("long", @LONG
����̨Ϊ����ʯ������ÿ���ʯ����ü���ƽ�������������ʵ�Ϊ�˼���
�븣����֪��ʹ�����񹤡�ʯ��ʼ���ɴ˾޹�������̨���ǿ���������ǧ�˵�
�㳡�������ڴˣ������������ܷ塢С�ܷ塢˫���塢���������������ڵ�
����ɽ��������������Ÿ�����³��δ�ˡ��ľ��䡣
LONG);
	set("exits", ([
	    "southdown" : __DIR__"peitian-fang",
	]));
	set("objects", ([
		CLASS_D("songshan") + "/zuo" : 1,
	      __DIR__"npc/ssdizi" : 3,
	]));
	set("outdoors", "��ɽ");
   	setup();
}

void init()
{
	object me = this_player();
	if ( me->query("songshan_points")){
		me->add("job_time/��ɽ", me->query("songshan_points"));
		me->delete("songshan_points");
	}
	add_action("do_enter","guan");
	add_action("do_qs","qi");
        add_action("do_jieti","jieti");
        add_action("do_decide","decide");
}

int do_enter(string arg)
{
	object me;

	me = this_player();
	if( !arg || arg=="" ) return 0;
	if( arg=="ri" ) {
		if (me->is_busy() || me->is_fighting())
			return notify_fail("����æ���ء�\n");
		if (me->query("family/family_name")=="��ɽ��") {
		       	message("vision",me->name()+"�������·�������շ����˹�ȥ��\n",environment(me),({me}) );
		       	me->move("/d/songshan/guanrifeng");
		       	message("vision",me->name() + "�ӷ���̨���˹�����\n",environment(me), ({me}) );
		       	return 1;
	   	}
     		return notify_fail("�Ǳ�̫���ô��㲻��ɹ����\n");
	}
}
//��ɽ��ʯ����
int do_qs(string arg)
{
	object me,ob;
	int gold;
	me = this_player();
	ob = present("shi kuai",me);
	gold=10;
	if( !arg || arg=="" ) return notify_fail("��Ҫ��ʲô��\n");

	if(!ob) return notify_fail("������Ҫʯ�ϣ���Ҫ��ʲô������\n");

	if(!me->query_temp("ss_qs/taked")) return notify_fail("�㻹ûȥ��ʯͷ�ذɣ�\n");
	if (arg!="shikuai"&&arg!="ʯ��") return notify_fail("��Ҫ��ʯͷ��ʲô��");
	/*
		shen = me->query("max_pot")/2 + random(200);
		exp = me->query("max_pot")/2+random(20);
		exp = me->add_exp_combat(exp,this_object(),"��ɽ��ʯ");
		pot = exp/5+random(exp/10);

		//me->add("combat_exp",exp);
		if (me->add("potential",pot) > me->query("max_pot"))
			me->set("potential", me->query("max_pot"));
		me->add("shen",-shen);

		me->improve_skill("hanbing-zhenqi",me->query("int"));*/
	if (me->query("quest/ss/rumen/pass")
		&&me->query("family/family_name")=="��ɽ��"
		&&me->query_skill("hanbing-zhenqi",1)<100)
	{
		tell_object(me,"����Ȼ�����䣬��Ȼһ�������ɵ��ﱬ��������������Ϊ�ƺ���������Щ��\n");
		me->improve_skill("hanbing-zhenqi",2*me->query("int"));
	}
	//me->set("job_name","��ɽ��ʯ");


	me->add_condition("job_busy", 2+random(2));
	me->delete_temp("ss_qs");
	destruct(ob);
	message_vision("$N��һ��ʯͷ���ڷ���̨�����һ���ϡ�\n",me);
	//me->apply_condition("ssjob/qishi",1);
	if (me->query("combat_exp")<200000)
	{
		tell_object(me,"������Զ����������������ΰ�ʯͷ�������ú�ϸ�ģ������ӣ��Һܿ����㡣��\n");
		TASKREWARD_D->get_reward(me,"��ɽ��ʯ",-1,0,0,1,0,0,0,"����");  
	}else{
		tell_object(me,"�����úøɣ��Һܿ����㣡\n");
		me->add("potential",10+random(10));
		me->add("shen",-100);
	}
	me->add("party/gongji",1+random(3));
//	tell_object(me,"������"++);
	if (random(me->query("job_time/��ɽ��ʯ"))>200
		&&!me->query("quest/ss/rumen/pass")
		&&random(me->query("kar"))>25 )
	{			
		message_vision(HIG"������Զ����$N���������ҹ۲���þ��ˣ��Ǹ������ӣ������Ը��͵���ʤ��������Ϊʦ����\n"NOR,me);
		me->set("quest/ss/rumen/pass",1);
	}	
	/*	me->add("job_time/��ɽ��ʯ",1);
		tell_object(me,HIW" ��õ��ˣ�\n" +
	    	chinese_number(exp) + "��ʵս����\n"+
	    	chinese_number(pot) + "��Ǳ�ܺ�\n"+
	    	chinese_number(shen)+ "����\n"NOR);*/
		return 1;
	
}
