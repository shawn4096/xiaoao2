// yaozhong.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "药种" NOR, ({"yao zhong","zhong zi","zhong" ,"zhongzi"})); 
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",
                "这是一枚可以种(zhong)在药圃里的药种，");
		set("unit", "枚");
		set("no_sell",1);
		set("5type","土");
		set("location",1);
		//set("8type","乾");
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
		return notify_fail("你要种什么？\n");
	if(!objectp(room=environment(me)) || (room->query("can_zhong")!=1))
		return notify_fail("你不能在这里种药。\n");
	if(!objectp(obj=new(__DIR__"yaomiao")))
		return notify_fail("你现在不能种药，等一会再种吧。\n");
	if (!present("yao chu",me))
		return notify_fail("你身上没有药锄，无法刨地。\n");
	if (!present("shui piao",me))
		return notify_fail("你身上没有水瓢，无法舀水。\n");
	if (!present("shui tong",me))
		return notify_fail("你身上没有水桶，无法盛装水。\n");
	if (present("yao miao",room))
		return notify_fail("地上已经种植药苗了。\n");
	if (query("owner")!=me->query("id"))
	{
		return notify_fail("那不是你的种子，你不熟悉药性，无法种植！\n");
	}
	if (!me->query_temp("sld/zhongyao/start"))
	{
		return notify_fail("没有神龙岛特许，焉能随便种植药草？！\n");
	}
	if (room->query("zhongyao"))
	{
		return notify_fail("此地刚被人种植过药草，土地需要休养生息！\n");
	}
	if (me->query_temp("sld/zhongyao/zhong"))
	{
		return notify_fail("你已经在种药了，别乱折腾？！\n");
	}
	message_vision(HIC"$N检查下这个地壤，小心地将药种拿出来，用锄头刨开土壤，埋了下去！\n"NOR,me);
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
		obj->set("long",obj->query("long")+obj->query("8type")+obj->query("5type")+"性。\n");
		obj->set("stime",uptime());
		obj->set("jtime",uptime());
		obj->set("name",me->query("name")+"培育的幼小药苗");
		obj->set("owner",me->query("id"));
		obj->move(room);
		me->set_temp("sld/zhongyao/yumiao",1);
		message_vision("$N把一枚药种埋到土里，浇了一瓢水，慢慢地，从土里长出了一株"HIG"幼苗。\n"NOR,me);
		me->improve_skill("yaozhi",(int)me->query_int());
		

		destruct(ob);
		return 1;
	}
}

int she_come(object me)
{
		//150以后福源低则出现干扰项
		object she;
		if (!me) return 0;
		
		if (random(me->query("kar"))<25)
		{
			if (me->query("combat_exp")<1500000
			   &&me->query("combat_exp")>100000)
			{
				tell_object(me,RED"突然，从药囿丛中窜出一条怪蛇,一口向你咬去！\n"NOR);
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