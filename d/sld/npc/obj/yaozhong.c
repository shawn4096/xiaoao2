// yaozhong.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "ҩ��" NOR, ({"yao zhong","zhong zi","zhong" ,"zhongzi"})); 
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",
                "����һö������(zhong)��ҩ�����ҩ�֣�");
		set("unit", "ö");
		set("no_sell",1);
		set("5type","��");
		set("location",1);
		//set("8type","Ǭ");
	}
}

void init()
{
	add_action("do_zhong","zhong");
}

int do_zhong(string arg)
{
	object ob,obj;
	object me=this_player();
	object room;

	if(!arg || !objectp(ob=present(arg, me)) || (ob!=this_object()))
		return notify_fail("��Ҫ��ʲô��\n");
	if(!objectp(room=environment(me)) || (room->query("can_zhong")!=1))
		return notify_fail("�㲻����������ҩ��\n");
	if(!objectp(obj=new(__DIR__"yaomiao")))
		return notify_fail("�����ڲ�����ҩ����һ�����ְɡ�\n");
	if (!present("yao chu",me))
		return notify_fail("������û��ҩ�����޷��ٵء�\n");
	if (!present("shui piao",me))
		return notify_fail("������û��ˮư���޷�Ҩˮ��\n");
	if (!present("shui tong",me))
		return notify_fail("������û��ˮͰ���޷�ʢװˮ��\n");
	if (present("yao miao",room))
		return notify_fail("�����Ѿ���ֲҩ���ˡ�\n");
	if (query("owner")!=me->query("id"))
	{
		return notify_fail("�ǲ���������ӣ��㲻��Ϥҩ�ԣ��޷���ֲ��\n");
	}
	if (!me->query_temp("sld/zhongyao/start"))
	{
		return notify_fail("û���������������������ֲҩ�ݣ���\n");
	}
	if (room->query("zhongyao"))
	{
		return notify_fail("�˵ظձ�����ֲ��ҩ�ݣ�������Ҫ������Ϣ��\n");
	}
	if (me->query_temp("sld/zhongyao/zhong"))
	{
		return notify_fail("���Ѿ�����ҩ�ˣ��������ڣ���\n");
	}
	message_vision(HIC"$N��������������С�ĵؽ�ҩ���ó������ó�ͷ�ٿ�������������ȥ��\n"NOR,me);
	//me->set_temp("sld/zhongyao/yaozhong/5type",ob->query("5type"));
	call_out("miao_come",2+random(3),me,ob);
	//destruct(ob);
	ob->move(room);
	me->set_temp("sld/zhongyao/zhong",1);
	call_out("she_come",2+random(3),me);
	return 1;
}

int miao_come(object me,object ob)
{
	object obj,room;
	room=environment(me);
	
	if (!me||!me->query_temp("sld/zhongyao/zhong")) return 0;
	call_out("she_come",3+random(3),me);
	if (!objectp(obj=present("yao miao",room))) 
	{
		obj=new("/d/sld/npc/obj/yaomiao");
		obj->set("5type",ob->query("5type"));
		obj->set("8type",room->query("8type"));
		obj->set("long",obj->query("long")+obj->query("8type")+obj->query("5type")+"�ԡ�\n");
		obj->set("stime",uptime());
		obj->set("jtime",uptime());
		obj->set("name",me->query("name")+"��������Сҩ��");
		obj->set("owner",me->query("id"));
		obj->move(room);
		me->set_temp("sld/zhongyao/yumiao",1);
		message_vision("$N��һöҩ�����������һưˮ�������أ������ﳤ����һ��"HIG"���硣\n"NOR,me);
		me->improve_skill("yaozhi",(int)me->query_int());
		

		destruct(ob);
		return 1;
	}
}

int she_come(object me)
{
		//150�Ժ�Դ������ָ�����
		object she;
		if (!me) return 0;
		
		if (random(me->query("kar"))<25)
		{
			if (me->query("combat_exp")<1500000
			   &&me->query("combat_exp")>100000)
			{
				tell_object(me,RED"ͻȻ����ҩ����дܳ�һ������,һ������ҧȥ��\n"NOR);
				switch(random(2))
				{
							case 0:
								she=new("/d/sld/snake/dushe");
								break;
							case 1:
								she=new("/d/sld/snake/dushe2");
								break;
							case 2:
								she=new("/d/sld/snake/fushe");
								break;
				}
			}else if (me->query("combat_exp")>1500000 )		
			{
			
				switch(random(6))
				{
					case 0:
						she=new("/d/sld/snake/dushe");
						break;
					case 1:
						she=new("/d/sld/snake/dushe2");
						break;
					case 2:
						she=new("/d/sld/snake/fushe");
						break;
					case 3:
						she=new("/d/sld/snake/yinshe");
						break;
					case 4:
						she=new("/d/sld/snake/jinshe");
						break;
					case 5:
						she=new("/d/sld/snake/wubushe");
						break;
				}
			}
			she->set("owner",me->query("id"));
			she->set("combat_exp",me->query("combat_exp"));
			she->add_temp("apply/attack",300);
			she->add_temp("apply/dodge",300);
			she->add_temp("apply/parry",300);
			she->move(environment(me));
			she->follow(me);
			she->kill_ob(me);
		}
		
}