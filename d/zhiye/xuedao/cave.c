// nroad6.c
// Modified by Java Apr.27 1998
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",RED"大厅"NOR);
        set("long",@LONG
这是一间血刀门山洞大厅，极为隐秘。乃是门中高手在大雪山中
历经数年挖掘而成，洞中甚是开阔，能感受到微微空气流动，显然已
经和外部挖通所致洞中四周摆放了数张椅子，正中央是一把血红色高
背大椅，上面铺了血红色的一张毛毯，甚是恐怖。
LONG );
        set("exits",([
                "north"   : __DIR__"shitang",
                "west" : __DIR__"xiuxishi",
			    "east" : __DIR__"lingwushi",
			    "south" : __DIR__"shandong3",


        ]));
        set("objects",([
             /*  "/clone/weapon/miandao" : 1,
				
				"/clone/weapon/xinyuedao" : 1,*/
			//	"/clone/weapon/blade" : 1,

        ]));
        //	set("no_clean_up", 0);
       // set("outdoors", "xuedao");
        setup();
       //        replace_program(ROOM);
}

//神照经3起始标志为 玩家身上需要保护 szj/wait_baohu

void init()
{
        object me=this_player();
		object oba;
	//add_action("do_watch", "mianbi");
        add_action("do_baohu", "baohu");
	    add_action("do_qiang", "qiang");
		if (me->query_temp("szj/wait_baohu"))
		{
			oba=new(__DIR__"npc/shuisheng.c");
		    oba->move(environment(me));
		    message_vision(HIC"\n水笙慌慌张张地跑了进来，面色苍白，气喘吁吁。\n一边跑，一边不住向后看，似乎后面有人正在追赶似得。\n"NOR, me);
			call_out("shuisheng",3,me);
		}
}
void shuisheng(object me)
{
        object obb,room;
		if (!present("xuedao laozu",environment(me)))
        {
			room=load_object("/d/xueshan/xuegu");
			if (obb=present("xuedao laozu",room))
			{
				message_vision(HIY"\n血刀老祖忽然从洞外跃进来，色迷迷地对水笙笑道，本佛爷这次捉了个极品小妞。\n"NOR,me);
				obb->move(environment(me));
			}
			else
			{
              obb=new("/d/xueshan/npc/laozu.c");
		      obb->move(environment(me));
		      message_vision(HIY"\n屋外传来一阵淫笑，一个色眯眯的老和尚看似甚是悠闲，随后跨进门来。\n"NOR,me);
			}
        }
}

int do_baohu(string arg)
{
	object me = this_player(),ob,weapon;
	
	if (!me->query_temp("szj/wait_baohu")) return 0;
	if (arg != "shui sheng") return 0;
	me->delete_temp("szj/wait_baohu");
	ob = present("xuedao laozu", this_object());
	weapon=ob->query_temp("weapon");
	message_vision(HIW"$N叫道：“别再杀人了！”说完扑将上去，手中树枝击在$n腕上。\n"NOR, me, ob);
	message_vision(HIC"若在平时，$n焉能给$N击中？但这时衰颓之余，功力不到原来的半成，手指一松，"+weapon->query("name")+HIC"脱手落地。\n"NOR, me, ob);
	weapon->move(environment(me));
	me->set_temp("szj/baohu", 1);
	me->set_temp("szj/wait_qiang", 1);
	return 1;
}
int do_qiang(string arg)
{
	object me = this_player(), ob;
	if (!me->query_temp("szj/wait_qiang")) return 0;
	if (arg != "dao" && arg !="blade") return 0;
	me->delete_temp("szj/wait_qiang");
	ob = present("xuedao laozu", this_object());
	message_vision(HIW"$N和$n同时俯身去抢兵刃。$N手掌在下，先按到了刀柄。\n"NOR, me, ob);
	message_vision(HIC"$n提起双手，便往$N颈中扼去。$N一阵窒息，放开了血刀，伸手撑持。\n"NOR, me, ob);
	message_vision(HIC"$n知道自己力气无多，这一下若不将$N扼死，自己便命丧$N手。\n"NOR, me, ob);
	message_vision(HIC"$N头颈被血刀僧扼住，呼吸越来越艰难，胸口如欲迸裂。\n\n"NOR, me, ob);
	me->start_busy(100);
	call_out("story3", 2, me, ob);
	return 1;
}


void story3(object me, object ob)
{
	if (me->query_skill("shenzhao-jing", 1) < 200) {
		call_out("finish", 1, me, ob);
		return;
	}
	tell_object(me, HIR"你肺中积聚着的一股浊气数度上冲，要从口鼻中呼了出来，但喉头的要道被阻，这股气冲到喉头，又回了下去。\n"NOR);
	tell_object(me, HIR"一股浊气在你体内左冲右突，始终找不到出路。\n"NOR);
	tell_object(me, HIR"你只感全身难受困苦已达极点，心中只叫：“我快要死了，我快要死了！”\n\n"NOR);
	call_out("story4", 2, me, ob);
}

void story4(object me, object ob)
{
	object obj;
	int lev = me->query_skill("shenzhao-jing", 1);
	if (random(150 + lev/2) > 350 && random(10)> 8 && random(me->query("kar"))> 27)
	{
	tell_object(me, HIW"突然之间，你只觉胸腹间剧烈刺痛，体内这股气越胀越大，越来越热，犹如满镬蒸气
没有出口，直要裂腹而爆，蓦地里前阴后阴之间的“会阴穴”上似乎被热气穿破了一个小
孔，登时觉得有丝丝热气从“会阴穴”通到脊椎末端的“长强穴”去。人身“会阴”“长
强”两穴相距不过数寸，但“会阴”属于任脉，“长强”却是督脉，两脉的内息决不相通。
你体内的内息加上无法宣泄的一股巨大浊气，交迸撞激，竟在危急中自行强冲猛攻，替你
打通了任脉和督脉的大难关。这内息一通入“长强穴”，登时自腰俞、阳关、命门、悬枢
诸穴，一路沿着脊椎上升，走的都是背上督任各个要穴，然后是脊中、中枢、筋缩、至阳、
灵台、神道、身柱、陶道、大椎、痖门、风府、脑户、强间、后顶、而至顶门的“百会穴”。\n"NOR);
	
	 tell_object(me, HIY"这股内息冲到百会穴中，只觉颜面上一阵清凉，一股凉气从额头、鼻梁、口唇下来，通到
了唇下的“承浆穴”。这承浆穴已属任脉，这一来自督返任。任脉诸穴都在人体正面，这
股清凉的内息一路下行，自廉泉、天突而至璇玑、华盖、紫宫、玉堂、膻中、中庭、鸠尾、
巨阙、经上、中、下三脘，而至水分、神厥、气海、石门、关元、中极、曲骨诸穴，又回
到了“会阴穴”。如此一个周天行将下来，郁闷之意全消，说不出的畅快受用。内息第一
次通行时甚是艰难，任督两脉既通，道路熟了，第二次、第三次时自然而然的飞快运转，
顷刻之间，连走了一十八次。\n\n"NOR);
	message("channel:rumor", MAG"【谣言】某人："+me->query("name")+"机缘巧合，运使神照经打通了任督二脉，达到了神照经心法的最高境界！\n"NOR, users());
	message_vision(HIC"$N体内的劲力愈来愈强，心中却仍是十分害怕，只求挣扎脱身，双手乱抓乱舞，始终碰
不到$n身上，左脚向后乱撑几下，突然一脚踹在$n的小腹丹田之上。\n\n"NOR, me, ob);
	ob->unconcious();
	me->start_busy(1);
	me->set("quest/szj/pass",3);
	
	obj = present("shui sheng", this_object());
	if (!obj) return;
	message_vision(HIY"$N说道：姑娘你走吧，否则$n醒来一定不会放过你的。\n"NOR, me, ob);
	message_vision(HIY"$n冷哼一声：你也不是好人，我以后不会放过你的！\n"NOR, me, obj);
	message_vision(HIY"$n说完哭着向外面跑去。\n\n"NOR, me, obj);
	destruct(obj);
  }
    call_out("finish", 1, me, ob);
		return;
	
}

void finish(object me, object ob)
{
	object obj = present("shui sheng", this_object());
	if (!obj) return;
	message_vision(HIY"$n冷哼一声，小崽子自不量力，看在你给老子找女人的分上饶你不死。\n"NOR, me, ob);
	message_vision(HIY"可是这个小妞咱可不能放过，否则等她力气恢复了，肯定会杀了我们两个。\n"NOR, me, ob);
	message_vision(HIY"$n挥刀砍向水笙，水笙躲避不及，鲜血从喉咙口直流出来。\n"NOR, me, ob);
	obj->die();
	me->start_busy(1);
	me->unconcious();
}
