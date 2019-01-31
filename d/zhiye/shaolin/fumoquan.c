// Room: /d/shaolin/fumoquan.c

#include <ansi.h>
inherit ROOM;
int do_kanshou(string arg);

void create()
{
	set("short", "��շ�ħȦ");
	set("long", @LONG
���ô������������ϸ����˸�������һ�˵Ĵ󶴣��и�����¶����ɫɮ
��һ�ǣ��ƺ�ס�����ˡ�������һƬ���ƺ�������и���(cave)�����Ĵ���ͺͺ�ģ�
�ƺ������ܴ����������´�ݲ�����
LONG
	);

	set("exits", ([
		"out" : __DIR__"qyping",
	]));

	set("objects",([
		CLASS_D("shaolin") + "/du-nan" : 1,
		CLASS_D("shaolin") + "/du-e" : 1,
		CLASS_D("shaolin") + "/du-jie" : 1,
	]));
	set("item_desc", ([                    
         "cave": HIC"\n����Ϊ��դ�����⣬���¹�Ѻ��ħ�̴�ħͷлѷ����������Ϊ��ʦ�����׼����\n"NOR,
     ]));

	set("outdoors", "������");
	setup();
}

void init()
{
	mapping mine;
        object ob = this_player();
	mine = ob->query("family");
	
	add_action("do_kanshou","kanshou");

	if( !userp(ob) || wizardp(ob) ) return;
	if (ob->query("family/family_name") == "������" && (ob->query("passdu") || ob->query("pass_xin")))
		return;
	message_vision(HIR "ͻȻ�侢���ݺᣬ��������������������͵ع�����˲�����
����һ����ֱ�ı��У��糤ì����˰������������ֱ���$N��ͷ��
�أ�������Ҫ�����̶�����$NһƳ�䣬����������ɮ�־�������
��֮�У���ȫ���ֱ���$N������$N��������������֮�̺����Ͻ�
ħ�󷨵Ľ�շ�ħȦ��\n\n" NOR, ob);

	if ( mapp(mine)
	&& mine["generation"] > 36
	&& mine["family_name"] == "������"
	&& ob->query("qi") < 200 ){
		message_vision(HIR "$N��һ����ɽ������ľ������У���ʱ���˳�ȥ��\n" NOR, ob);
		ob->move("/d/shaolin/qyping", 1);
		tell_room(environment(ob), ob->name()+"�ӷ�ħȦ���˳�����\n", ob);
	}
}

int valid_leave(object me, string dir)
{

	if( dir == "out" && member_array("puti zi", deep_inventory(me)->query("id")) != -1 ) {
		return notify_fail("�и�����˵�������ܴ����������뿪��ħȦ !\n");
	}
	if( dir == "out" && me->query_temp("ryb/askdue") ) {
		return notify_fail("�ɶ�˵������մ�Ӧ��Ҫ���ҿ���лѷ��Ϊ��Ҫ�뿪��ħȦ !\n");
	}

	me->delete_temp("fighter");
	return ::valid_leave(me, dir);
}

int do_kanshou(string arg)
{
	object me,weapon;
	int t;
	me=this_player();
	weapon=me->query_temp("weapon");
	t=6+random(10);
	
	if (!me->query_temp("ryb/askdue"))
	{
		return notify_fail("���������ɺ��������޹�ΪɶҪ�ڴ˿��� !\n");

	}
	if (arg!="лѷ")
	{
		return notify_fail("�ɶ�˵������ĥĥ����ڷ�ħȦ�и�ʲô !\n");

	}
	if (me->query_skill_mapped("whip")!="riyue-bian"
		||me->query_skill_mapped("parry")!="riyue-bian"
		||weapon->query("skill_type")!="whip")
	{
		return notify_fail("�ɶ�˵��������Ҫ�������±޷��ɺ������������ !\n");

	}
	message_vision(HIC"�ɶ��ʦ˵����$N��Ҫע���ˣ�������������������������,ʱ���Լ��"+chinese_number(t)+"�룡\n"NOR,me);

	call_out("mj_come1",t,me);
	return 1;

}
int mj_come1(object me)
{
	object leng,zhong,zhou,peng,budai;
	if (!objectp(leng=present("leng qian",environment(me))))
	{
		leng=new("kungfu/class/mingjiao/leng");
		leng->move(environment(me));
	}
	if (!objectp(zhong=present("zhang zhong",environment(me))))
	{
		zhong=new("kungfu/class/mingjiao/zhang2");
		zhong->move(environment(me));
	}	
	if (!objectp(peng=present("peng yingyu",environment(me))))
	{
		peng=new("kungfu/class/mingjiao/peng");
		peng->move(environment(me));
	}
	if (!objectp(zhou=present("zhou dian",environment(me))))
	{
		zhou=new("kungfu/class/mingjiao/zhou");
		zhou->move(environment(me));
	}
	if (!objectp(budai=present("shuo bude",environment(me))))
	{
		budai=new("kungfu/class/mingjiao/shuo");
		budai->move(environment(me));
	}

	message_vision(HIR"��ʱ����Ȼ�������ӰٿȻ�����ħȦ���ȵ���������ʥ��Ψ�����̡�����������ɢ����Ҳ��\n��"NOR,me);
	leng->kill_ob(me);
	zhong->kill_ob(me);
	zhou->kill_ob(me);
	peng->kill_ob(me);
	budai->kill_ob(me);
	call_out("mj_come2",10+random(10),me);
		message_vision(HIY"\n\n�ɶ򺰵����㶯��Ҫ��㣬�����������ĸ����������ⱼ��,�������ֱ���ǰ�����˸�Ϊ������\n"NOR,me);

	return 1;
}
int mj_come2(object me)
{
	object yin,zishan,fuwang;
	message_vision(HIY"��Ȼ���˺������������һ𣬷��Ҳ����� �����Ĵ�����Ҳ����\n"NOR,me);
	if (!objectp(yin=present("yin tianzheng",environment(me))))
	{
		yin=new("kungfu/class/mingjiao/yin");
		yin->move(environment(me));
	}
	yin->kill_ob(me);
	if (!objectp(zishan=present("dai qisi",environment(me))))
	{
		zishan=new("kungfu/class/mingjiao/dai");
		zishan->move(environment(me));
	}
	zishan->kill_ob(me);
	if (!objectp(fuwang=present("wei yixiao",environment(me))))
	{
		fuwang=new("kungfu/class/mingjiao/wei2");
		fuwang->move(environment(me));
	}
	fuwang->kill_ob(me);
	message_vision(HBYEL+HIW"\n\n\n�ɶ�̾Ϣһ������ɫ���ǣ������������������������ˣ�����������������֡�����\n"NOR,me);
	call_out("mj_come3",15+random(10),me);
	return 1;
}
int mj_come3(object me)
{
	object yang,fan;
	message_vision(HIY"��Ȼ���˺������������һ𣬷��Ҳ����� ������ң������Ҳ����\n"NOR,me);
	if (!objectp(yang=present("yang xiao",environment(me))))
	{
		yang=new("kungfu/class/mingjiao/yang");
		yang->move(environment(me));
	}
	yang->kill_ob(me);
	if (!objectp(fan=present("fan yao",environment(me))))
	{
		fan=new("kungfu/class/mingjiao/fan");
		fan->move(environment(me));
	}
	fan->kill_ob(me);
	message_vision(HBYEL+HIW"\n\n\n�ɶ�̾Ϣһ������ɫ��Щ���ǣ������������������������ˣ���������Ǹ��������֡�����\n"NOR,me);
	call_out("mj_come4",15+random(10),me);
	return 1;
}
int mj_come4(object me)
{
	object zhang;
	message_vision(HIY"��Ȼ���˺������������һ𣬷��Ҳ����� ���̽������޼���Ҳ����\n"NOR,me);
	if (!objectp(zhang=present("zhang wuji",environment(me))))
	{
		zhang=new("kungfu/class/mingjiao/zhangwuji2");
		zhang->move(environment(me));
	}
	zhang->kill_ob(me);
	me->set_temp("ryb/starttime",time());
	call_out("check_fight",20,me);
	message_vision(HIY"\n\n\n\n\�ɶ򺰵����ٸ���20��ʱ�䣬�����Ͼ�ɱ������������ʧ�ܣ�\n��Ȼ��Ҫ��ʵ�ڳŲ�ס�Ͳ�Ҫ��ǿ�ˣ���ȫ��һ������\n"NOR,me);
	
	return 1;
}

int check_fight(object me)
{
	int time;
	object due;
	//time=time()-me->query_temp("ryb/starttime");
	due=present("du e",environment(me));
	if (!me->is_living()
		||!me
		||!due
		||present("yang xiao",environment(me))
		||present("fan yao",environment(me))
		||present("zhang wuji",environment(me))
		||present("yin tianzheng",environment(me))
		||present("dai qisi",environment(me))
		||present("wei yixiao",environment(me)))
	{
		message_vision(HIW"��ħ���Ȧ���ƣ�лѷΪ���̸��ֽ��ߣ��ػ�лѷ����ʧ�ܣ�\n"NOR,me);
		me->set("quest/sl/ryb/kanshou/time",time());
		me->delete_temp("ryb");
		return 1;
	}
	else {
	    message_vision(HIG"$N��������ս�����ڽ�ħ�̽�ͽɱ�ɾ���ʤ����ɶɶ򽻸��Լ��Ŀ�������\n"NOR,me);
		message_vision(HIY"\n\n�ɶ���̷�ţ������ް����ӷ𡱣��������գ�\n"NOR,me);
		due->do_say();
		me->set("quest/sl/ryb/kanshou/pass",1);
		me->delete_temp("ryb");

		return 1;
	}

}