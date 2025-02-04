//蛤蟆功最终Quest by server
//by spiderii@ty 鉴于HAMA1的难度提高。这里取消3次机会的限制。exp每增加1M从新得到一次机会！
//限制reboot注册ID。难度再次降低，server很变态。蛤蟆1很难弄了。蛤蟆3还那么难。tsk
#include <ansi.h>;
inherit NPC;
inherit F_MASTER;
int do_chi(string arg);
int do_chaikai();

void create()
{
	set_name("洪七公", ({"hong qigong", "hong", "qigong"}));
	set("nickname", "九指神丐");
	set("gender", "男性");
	set("age", 75);
	set("long", 
"他一张长方脸，颌下微须，粗手大脚，身上衣服东一块西一块的打满了补丁，
却洗得干干净净，背上负着个朱红漆的大葫芦。\n");
	set("attitude", "peaceful");

	set("str", 35);
	set("int", 24);
	set("con", 30);
	set("dex", 30);

	set("rank", 10);
	set("max_qi", 4000);
	set("max_jing", 3000);
	set("neili", 5500);
	set("max_neili", 5500);
	set("jiali", 0);

	set("combat_exp", 3600000);
	set("score", 200000);
	set("death_times",180);

	set_skill("force", 400);             // 基本内功
	set_skill("huntian-qigong", 400);    // 混天气功
	set_skill("strike", 400);            // 基本掌法
	set_skill("xianglong-zhang", 400);   // 降龙十八掌
	set_skill("hand", 360);              // 基本手法
	set_skill("dodge", 400);             // 基本躲闪
	set_skill("xiaoyaoyou", 400);        // 逍遥游
	set_skill("parry", 400);             // 基本招架
	set_skill("stick", 400);             // 基本棍杖
	set_skill("dagou-bang", 400);        // 打狗棒法
	set_skill("begging", 200);           // 叫化绝活
	set_skill("checking", 200);          // 道听途说

	map_skill("force", "huntian-qigong");
	map_skill("strike","xianglong-zhang");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("parry", "dagou-bang");
	map_skill("stick", "dagou-bang");

	prepare_skill("strike", "xianglong-zhang");

	create_family("丐帮", 17, "帮主");
	setup();

	carry_object(ARMOR_D("bainayi"))->wear();
	carry_object(ARMOR_D("shoes"))->wear();
	carry_object("/kungfu/class/gaibang/obj/gb_budai10")->wear();

}
void init()
{
	object ob;

	ob = this_player();
	if (interactive(ob) && !is_fighting() && !ob->query("questwg"))
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}
void greeting(object me)
{
	tell_object(me,HIW"洪七公对你道:伤心事暂且不提，先填饱肚子再说 。\n\n"NOR);
	tell_object(me,HIW"洪七公支起铁锅烧了一锅雪水，又从一块大岩石边的泥土中挖出一只死公鸡来。\n\n"NOR);
	tell_object(me,HIW"死公鸡在雪光掩映下瞧得分明，只见鸡身上咬满了百来条七八寸长的大蜈蚣，红黑。\n\n"NOR);
	tell_object(me,HIW"相间，花纹斑斓，都在蠕蠕而动。洪七公拉住蜈蚣尾巴，一条条的抛在锅里。\n\n"NOR);
	tell_object(me,HIW"那些蜈蚣挣扎一阵，便都给烫死了。\n\n"NOR);
	tell_object(me,HIW"洪七公又起了油锅，将蜈蚣去壳炸至微黄之后加上作料拌匀，伸手往锅中提了。\n\n"NOR);
	tell_object(me,HIW"一条上来放入口中，轻轻嚼了几嚼，两眼微闭，叹了一口气，只觉天下之至乐。\n\n"NOR);
	tell_object(me,HIW"无逾于此矣。\n\n"NOR);
	tell_object(me,HIW"洪七公吃了十多条以后，向你道：我见过不少英雄好汉，杀头流血不皱半点眉。\n\n"NOR);
	tell_object(me,HIW"头，却没一个敢跟我老叫化吃一条蜈蚣。小娃娃，你敢不敢吃（chi）？。\n\n"NOR);

	add_action("do_chi","chi");
	return;
}

int do_chi(string arg)
{
	object me=this_player();
	object ob=this_object();
	if (!arg)
	return notify_fail(HIW"你要吃什么。\n"NOR);
	if (arg == "wugong")
	{
		remove_action("do_chi","chi");

		tell_object(me,HIW"你将一条蜈蚣放在口中一嚼。只一嚼将下去，但觉满嘴鲜美，又脆又香，清甜。\n\n"NOR);
		tell_object(me,HIW"甘浓，一生之中从未尝过如此异味，再嚼了几口，一骨碌吞了下去，又去挟第。\n\n"NOR);
		tell_object(me,HIW"二条来吃，连赞：妙极，妙极。\n\n"NOR);
		call_out("feng_out",5,ob,me);
	}
	else 
		return notify_fail(HIW"没有这样东西。\n"NOR);

	return 1;

}
void feng_out(object hong,object me)
{
	object feng;
	feng = new ("/d/huashan/hamasuperquest/feng");
	feng->move("/d/huashan/hamasuperquest/jueding5");

	tell_object(me,HIW"二人你抢我夺吃的甚是香甜，只听铎、铎、铎几声响，山角后转出来一人，身。\n\n"NOR);
	tell_object(me,HIW"子颠倒，双手各持石块，撑地而行，正是西毒欧阳锋。欧阳峰二话不说便向洪。\n\n"NOR);
	tell_object(me,HIW"七公发起攻击。\n\n"NOR);
	feng->kill_ob(hong);
	call_out("chai_out",10,hong,feng,me);

}

void chai_out(object hong,object feng,object me)
{
	feng->remove_all_killer();

	tell_object(me,HIW"欧阳锋突然收起灵蛇杖，双腿一弯，蹲下身来，阁的一声大叫，运起蛤蟆。\n\n"NOR);
	tell_object(me,HIW"功劲力，双掌齐发，向前推出。这一推实乃他毕生功力之所聚。洪七公猛觉劲。\n\n"NOR);
	tell_object(me,HIW"风罩来，心知不妙，也是双掌向前平推。这一下是以硬接硬，刹那之间，两下。\n\n"NOR);
	tell_object(me,HIW"里竟然凝住不动。\n\n"NOR);
	tell_object(me,HIW"二人僵持一会，欧阳锋头顶透出一缕缕的白气，渐渐越来越浓，就如蒸笼一般。\n\n"NOR);
	tell_object(me,HIW"洪七公也是全力抵御。你眼见二人脸色大变，心想他二人再拚得一时三刻，非。\n\n"NOR);
	tell_object(me,HIW"同归于尽不可，若是上前拆开（chaikai），自己功力与他们相差太远 ，多半。\n\n"NOR);
	tell_object(me,HIW"分解不开，反而赔上自己一条性命。\n\n"NOR);
	add_action("do_chaikai","chaikai");
	call_out("chaikai_out",8,hong,feng,me);
}

int do_chaikai()
{
	object* ppl;
	object me = this_player();
	object hong = this_object();
	object feng;
	int i, time, total, j, h = 0;

	ppl = users();
	i = me->query("combat_exp") - 500000;
	i /= 500000;
	time = time() - me->query("quest/hama/time");
	feng = present("ouyang feng", environment(me));
	j = sizeof(ppl);

	while(j--){
		if( userp(ppl[j])&& !wizardp(ppl[j])&&!ppl[j]->query("no_pk")&& ppl[j]->query("oyf/hamagong")>2 )
		h++;
	}

	if (me->query_skill("hamagong", 1) > 350 &&
	me->query("oyf_son") && 
	me->query("oyf/hamagong") == 2 &&
	random((int)me->query("kar")) > 25 && 
	random(me->query("con")) > 22 && 
	me->query("max_neili") > 7500  &&
	me->query("neili") > 15000  &&
	me->query("combat_exp") > 2000000)
	{
		tell_object(me,HIC"你见大事不好，慌忙的四处张望。\n\n"NOR);
		tell_object(me,HIC"你折了一根树干，走到二人之间盘膝坐下，运功护住全身，一咬牙，伸树干往二。\n\n"NOR);
		tell_object(me,HIC"人之间挑去。这一挑居然毫不费力，二人的内力从树干上传来，被你运内力一挡。\n\n"NOR);
		tell_object(me,HIC"立即卸去。原来强弩之末不能穿鲁缟，北丐西毒虽然俱是当世之雄，但互耗多时。\n\n"NOR);
		tell_object(me,HIC"均已精力无多。\n"NOR,me);
        
		tell_object(me,HIG"只间你义父和洪老前辈弹出一丈多远，面容煞白,你义父不信洪七公的武功会强过他，直嚷着还要继续比武。\n\n"NOR);
		tell_object(me,HIG"三两句话激得洪七公要教你「打狗棒法」，再由你去演练给义父见识。\n\n"NOR);
		tell_object(me,HIG"欧阳锋看过之后，立即教给你过破解之道，并让他演练给洪七公看。洪七公见棍法遭破解，随即又教了新的招式…。\n\n"NOR);
		tell_object(me,HIG"如此一来一往历经了两个时辰，欧阳锋已接连破了洪七公三十多招，你则从中坐收渔人之利。\n\n"NOR);
		tell_object(me,HIG"洪七公把你叫到身边，讲解他的「天下无狗」，你义父冥思半晌说道:为父把生平绝学最后一试传授与你，方可以破解这「天下无狗」。\n\n"NOR);
		tell_object(me,HIG"洪七公见欧阳锋破解了他的「天下无狗」，激动得强撑着挨到欧阳锋跟前，出人意表的美言他几句。\n\n"NOR);
		tell_object(me,HIG"欧阳锋被这突如其来的举动一激，登时想起自己就是西毒欧阳锋，而眼前则正是老仇家北丐洪七公。\n\n"NOR);
		tell_object(me,HIG"二老会心相拥并狂笑…。\n\n"NOR);
		tell_object(me,HIM"你从洪七公和欧阳峰的战斗中获益菲浅。\n"NOR,me);
		tell_object(me,HIM"你成功领会义父的蛤蟆功,你的功夫提高了！\n"NOR,me);
		me->add("combat_exp",(30000+random(20000)));
		me->add("oyf/hamagong",1);
		me->set("title",HIW"白驼山庄"BLU"西毒"HIW"传人"NOR);
		log_file("quest/hamagong", sprintf("%8s%-10s学会终极逆转九阴，并得到奖励。\n", me->name(1), "("+me->query("id")+")" ), me);

		tell_object(me,HIR"欧阳锋和洪七公两人突然同时委顿在地，双目紧闭，面如死灰，一动也不动了。\n\n"NOR);
		tell_object(me,HIR"原来二人已耗尽内力而死。立于两座新坟之前不由感叹。\n\n"NOR);
		tell_object(me,HIR"义父和洪老老前辈居然由自己这无名小卒安葬于如此荒岭，真乃造化弄人。\n\n"NOR);
		tell_object(me,HIR"人死了，天大的功名利禄又有何用呢? \n\n"NOR);
		tell_object(me,HIR"北丐西毒数十年来反覆恶斗，互不相下，岂知竟同。\n\n"NOR);
		tell_object(me,HIR"时在华山绝顶归天,你只有黯然下山。\n\n"NOR);
		me->move("/d/huashan/sheshen");
		destruct(feng);
		destruct(hong);
	}
	else 
	{
		tell_object(me,HIC"你折了一根树干，走到二人之间盘膝坐下，运功护住全身，一咬牙，伸树干往。\n\n"NOR);
		tell_object(me,HIC"二人之间挑去，你只觉一股大力从树干上传来，五脏六腑有如翻江倒海般，你。\n\n"NOR);
		tell_object(me,HIC"象断了线的风筝般直坠入山下。\n\n"NOR);
		me->add("quest/hama/super",1);
		me->set("quest/hama/time", time());

		me->unconcious();
		destruct(feng);
		destruct(hong);
		if(random(me->query_kar()) < 15) {
			me->set_temp("last_damage_from", "坠入山下");
			me->die();
		}
	}    
	return 1;
}

void all_dest(object feng,object hong)
{
	destruct(feng);
	destruct(hong);
}
