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
        set("max_qi", 58000);
        set("max_jing", 8000);
		set("max_jingli", 9000);
        set("neili", 55000);
        set("max_neili", 55000);
        set("jiali", 250);
        
        set("combat_exp", 15600000);
        set("score", 200000);
        set("death_times",380);

        set_skill("force", 550);             // 基本内功
        set_skill("huntian-qigong", 550);    // 混天气功
        set_skill("strike", 550);            // 基本掌法
        set_skill("xianglong-zhang", 550);   // 降龙十八掌
       // set_skill("hand", 550);              // 基本手法
        set_skill("dodge", 550);             // 基本躲闪
        set_skill("xiaoyaoyou", 550);        // 逍遥游
        set_skill("parry", 550);             // 基本招架
        set_skill("stick", 560);             // 基本棍杖
        set_skill("dagou-bang", 560);        // 打狗棒法
        set_skill("begging", 200);           // 叫化绝活
        set_skill("checking", 200);          // 道听途说

        map_skill("force", "huntian-qigong");
        map_skill("strike","xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dagou-bang");
        map_skill("stick", "dagou-bang");
        
        prepare_skill("strike", "xianglong-zhang");

        create_family("丐帮", 17, "前帮主");
        setup();
		call_out("dest", 900, this_object());    
        
                carry_object(ARMOR_D("bainayi"))->wear();
                carry_object(ARMOR_D("shoes"))->wear();
                carry_object("/kungfu/class/gaibang/obj/gb_budai10")->wear();
				carry_object("/clone/weapon/zhubang")->wield();


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
		  tell_object(me,HIR"\n\n那些蜈蚣挣扎一阵，便都给烫死了。\n\n"NOR);
		  tell_object(me,HIY"\n\n洪七公又起了油锅，将蜈蚣去壳炸至微黄之后加上作料拌匀，伸手往锅中提了。\n\n"NOR);
		  tell_object(me,HIY"一条上来放入口中，轻轻嚼了几嚼，两眼微闭，叹了一口气，只觉天下之至乐。\n\n"NOR);
		  tell_object(me,HIY"无逾于此矣。\n\n"NOR);
		  tell_object(me,HIG"\n\n洪七公吃了十多条以后，向你道：我见过不少英雄好汉，杀头流血不皱半点眉。\n\n"NOR);
		  tell_object(me,HIG"头，却没一个敢跟我老叫化吃一条蜈蚣。小娃娃，你敢不敢吃（chi）？。\n\n"NOR);
        
          add_action("do_chi","chi");
        
          return;
}
void dest()
{
	object me,ob;
	ob = this_player();
	me = this_object();

	//write(me->query("name")+"柳眉一蹙道：下次不要再让我遇见你。\n",me);  
	write(me->query("name")+"一个转身，飘身离去。\n",me);  

	destruct(this_object());
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

			tell_object(me,HIC"\n\n你将一条蜈蚣放在口中一嚼。只一嚼将下去，但觉满嘴鲜美，又脆又香，清甜。\n\n"NOR);
			tell_object(me,HIC"甘浓，一生之中从未尝过如此异味，再嚼了几口，一骨碌吞了下去，又去挟第。\n\n"NOR);
			tell_object(me,HIC"二条来吃，连赞：妙极，妙极。\n\n"NOR);
			call_out("feng_out",5,ob,me);
        }
        else 
        return notify_fail(HIW"没有这样东西。\n"NOR);

        return 1;

}
void feng_out(object hong,object me)
{
        object feng;
		object fbroom;
        if (!objectp(feng=present("ouyang feng",environment(me))))
        {
			if (me->query_temp("fbroom")) 
			{
				
			fbroom=me->query_temp("fbroom");			
			feng = new ("/d/huashan/hamasuperquest/feng");
			feng->move(fbroom);
			}
			else
			{
				tell_object(me,HIR"\n\n副本信息丢失，解密无法继续。\n\n"NOR);
				return;
				
			}
						
        }

		tell_object(me,HIR"\n\n二人你抢我夺吃的甚是香甜，只听铎、铎、铎几声响，山角后转出来一人，身。\n\n"NOR);
		tell_object(me,HIR"子颠倒，双手各持石块，撑地而行，正是西毒欧阳锋。欧阳峰二话不说便向洪。\n\n"NOR);
		tell_object(me,HIR"七公发起攻击。招式诡异，边打边喊，“我一见你就生气！纳命来吧！”\n\n"NOR);
        feng->kill_ob(hong);
		//hong->kill_ob(feng);
        call_out("chai_out",10,hong,feng,me);

}



void chai_out(object hong,object feng,object me)
{        
    //feng->remove_all_killer();
	tell_object(me,HIC"\n\n欧阳锋突然收起灵蛇杖，双腿一弯，蹲下身来，阁的一声大叫，运起蛤蟆。\n\n"NOR);
	tell_object(me,HIC"功劲力，双掌齐发，向前推出。这一推实乃他毕生功力之所聚。洪七公猛觉劲。\n\n"NOR);
	tell_object(me,HIC"风罩来，心知不妙，也是双掌向前平推。这一下是以硬接硬，刹那之间，两下。\n\n"NOR);
	tell_object(me,HIC"里竟然凝住不动。\n\n"NOR);
	tell_object(me,HIR"\n\n二人僵持一会，欧阳锋头顶透出一缕缕的白气，渐渐越来越浓，就如蒸笼一般。\n\n"NOR);
	tell_object(me,HIR"洪七公也是全力抵御。你眼见二人脸色大变，心想他二人再拚得一时三刻，非。\n\n"NOR);
	tell_object(me,HIR"同归于尽不可，若是上前拆开（chaikai），自己功力与他们相差太远 ，多半。\n\n"NOR);
	tell_object(me,HIR"分解不开，反而赔上自己一条性命。\n\n"NOR);
    me->set_temp("hschaikai",1);
	  //  add_action("do_chaikai","chaikai");
        //call_out("chaikai_out",8,hong,feng,me);
}

void all_dest(object feng,object hong)
{
        destruct(feng);
        destruct(hong);

}

int hong_say()
{
	object me=this_player();
	command("look "+me->query("id"));
	if (me->query("family/master_master")=="洪七公")
	{
		command("say 我到是谁，原来是我的乖徒儿"+me->query("name")+"啊，既然你来了，正好我传你几招，教训教训这老毒物！\n");

	}
	else {
		command("say 我到是谁，原来是"+me->query("family/master_name")+"偷偷教的好弟子啊！不错，真是不错！\n");
		command("thumb "+me->query("id"));
	}
	command("say 看你这小娃娃还不错，很像我当年那么厚道。\n");
	command("say 这老毒物和我纠缠了一生，我现在内功皆无，你若有心就帮我施展几招厉害招式\n");
	command("say 打狗棒法使出天下无狗！\n");
	command("hehe");
	command("say 你若愿意就输入 answer 愿意 ,若不愿意趁早滚蛋\n");
	add_action("do_answer","answer");

}
int do_answer(string arg)
{
	object me=this_player();
	if (!arg||arg!="愿意")
	{
		command("kick "+me->query("id"));
		return 1;
	}
	message_vision(HIC"$N大声说道，“我愿意”!"NOR,me);
	me->set_temp("wugou/answerok",1);
	return 1;
}
int hong_say2()
{
	object me=this_player();
	command("look "+me->query("id"));
	if (me->query("family/master_master")=="洪七公")
	{
		command("laugh ");
		command("pat "+me->query("id"));
		command("say "+me->query("name")+"乖徒儿啊，你仔细听好了！\n");

	}
	else {
		command("say 来来来！"+me->query("name")+"小娃娃，替我教训教训这条疯狗！\n");
		command("thumb "+me->query("id"));
	}
	command("say 天下无狗第一变「棒回掠地施妙手 ，横打双犬莫回头。」\n");
	command("say 天下无狗第二变「狗急跳墙如何打？ 快击狗臀劈狗尾。」\n");
	command("say 天下无狗第三变「穷巷赶狗有妙招， 棒打狗头定中心。」\n");
	command("say 。。。。。。。。。。。。。。。。。。。。。。。。。」\n");
	message_vision(HIY"\n\n$N认真听$N的招式讲解，对于打狗棒法最终奥秘有了些认知。\n"NOR,me,this_object());
	command("hehe");
	command("say 老毒物，你看我这招如何破解啊？\n");
	command("laugh ");
	//command("");
	//add_action("do_answer","answer");

}
int hong_say3()
{
	object me=this_player();
	command("look "+me->query("id"));
	
	command("laugh ");
	command("say 这就是真正的丐帮打狗棒法最终绝密天下无狗，乖徒儿，你可看清楚了？\n");
	command("say 这棒法乃我丐帮两大神技之一，也是帮主必须修习之武技。\n");
	command("say 乖徒儿，能否领悟就看你的。\n");
	//me->set_temp("");
}