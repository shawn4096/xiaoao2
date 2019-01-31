// by iceland

inherit NPC;
inherit F_MASTER;
#include <ansi.h>

#include "cike.h";
int give_lun();
int give_lun2();
string wulun_dazhuan();
string* luns = ({
       BINGQI_D("gold-falun"),
       BINGQI_D("silver-falun"),
       BINGQI_D("bronze-falun"),
       BINGQI_D("iron-falun"),
       BINGQI_D("leaden-falun"),
});


void create()
{
        object weapon;
        set_name("金轮法王", ({ "jinlun fawang", "jinlunfawang","fawang" ,"jinlun"}));
        set("long",@LONG
他身材高瘦，脸颊深陷，双目看似无神，两边太阳穴却高高凸起，面容严肃。
他受封“蒙古国第一国师”，练得一身通天彻地的神功。
LONG
        );
        set("title", HIY "蒙古国第一国师" NOR);
        set("gender", "男性");
        set("class", "huanxi");
        set("age", 65);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 40);
        set("int", 30);
        set("con", 30);
        set("dex", 34);
        set("per", 22);

        set("max_qi", 39500);
        set("max_jing", 6500);
        set("eff_jingli", 7500);
        set("neili", 48000);
        set("max_neili", 48000);
        set("jiali", 250);
        set("combat_exp", 13500000);
        set("score", 28000);
        set("unique", 1);
		set("lx/gree",11);
		set("quest/dls/longxiang/pass",1);
		set("quest/wulun/pass",1);

        set_skill("mizong-fofa", 200);
        set_skill("literate", 200);
        set_skill("force", 530);
        set_skill("longxiang-boruo", 530);
        set_skill("dodge", 500);
        set_skill("yuxue-dunxing", 500);
        set_skill("hammer", 530);
        set_skill("xiangfu-lun", 530);
        set_skill("hand", 500);
        set_skill("dashou-yin",500);
        set_skill("claw", 500);
        set_skill("tianwang-zhua", 500);
        set_skill("parry", 500 );

        map_skill("force", "longxiang-boruo");
        map_skill("dodge", "yuxue-dunxing");
        map_skill("hammer", "xiangfu-lun");
        map_skill("parry", "xiangfu-lun");
        map_skill("hand","dashou-yin");
        map_skill("claw","tianwang-zhua");

        prepare_skill("hand","dashou-yin");
        prepare_skill("claw","tianwang-zhua");

        create_family("大轮寺", 10, "弟子");
        set("inquiry", ([
                "武器" : (: give_lun  :),
			    "五轮大法" : (: wulun_dazhuan  :),
                "兵器" : (: give_lun  :),
                "风火轮" : (: give_lun2  :),
                
       ]));
        set("lun_count",5);
        set("lun_count2",1);
        set("class", "huanxi");
        set("chat_chance", 2);     
        set("chat_msg", ({
		CYN"金轮法王傲然道：第十层龙象般若功我已融会贯通，古往今来，我是第二人！\n"NOR,
		CYN"金轮法王愤愤的道：中原武人不讲规矩，仗着人多，大伙儿来个一拥而上。\n"NOR,
		CYN"金轮法王愤愤的道: 哼，否则凭我一人之力当可取得武林盟主之位。\n"NOR,
	}) );
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: exert_function, "shield jinlun fawang" :),
                (: perform_action, "hammer.wushuai" :), 
	}));
        set_temp("apply/damage", 70);
        set_temp("apply/dodge", 80);
        set_temp("apply/attack", 60);
        set_temp("apply/armor", 60);

        setup();
	if (clonep()){
                weapon = unew(BINGQI_D("gold-falun"));
                if (!weapon) weapon = unew(BINGQI_D("silver-falun"));
                if (!weapon) weapon = unew(BINGQI_D("bronze-falun"));
                if (!weapon) weapon = unew(BINGQI_D("iron-falun"));
                if (!weapon) weapon = unew(BINGQI_D("leaden-falun"));
                weapon->move(this_object());
                weapon->wield();
                carry_object("/d/xueshan/npc/obj/longxiang-jiasha")->wear();       
                add_money("gold",2);
        }
}

void reset()
{
	set("lun_count2", 1);
}

void attempt_apprentice(object ob)
{
       if ((string)ob->query("family/family_name") != "大轮寺") {
                command("say"+ RANK_D->query_respect(ob) +
                        "不是本派弟子，在这里捣什么乱？！");
                return;
        }

        if ((int)ob->query_skill("longxiang-boruo", 1) < 350) {
                command("say 我大轮寺各种武功均和内功相辅相成。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多钻研钻研本门的内功吧。");
                return;
        }
        if( (string)ob->query("gender") == "无性" ){
                command ("say 施主身体残缺，虽说佛祖普渡众生，可是...");
                return;
        }

        if( (int)ob->query_con(1) < 30) {
               command("sigh");
               command("say"+ RANK_D->query_respect(ob) +"你根骨太差，领悟不了高深功夫。");
               command("shake");
               return;
        }

        if (!(int)ob->query_temp("win_deb")){
                command ("say 你还是先找我弟子达而巴试试你的修为吧。\n");
                return;
	} 
        command("say 我也正在找寻一个资质上佳的弟子授我衣钵。你不顾艰辛诚意拜我为师。");
        if (!ob->query("fawang")){
		command("chat* 朗声说道：好！"+ ob->query("name") + RANK_D->query_respect(ob) + "智勇双全，可传我衣钵。\n");
		command("chat* 仰天长笑道：“本座苦觅数年，终于找到传人，百年之后亦无憾矣！”");
	}
	command("recruit " + ob->query("id"));
	ob->set("fawang", 1);
	ob->set("title",  "大轮寺金轮法王座下弟子"  );
}

int give_lun()
{ 
	mapping fam; 
	object me, ob,lun;

	me = this_object();
	ob = this_player();
       
	if (ob->query_temp("give_lun") == 1){
		command("say 你不是刚从我这里拿了轮子吗，你当我白痴啊！");
		return 1;
	}
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "大轮寺"){
		command("say 你与本派素无来往，不知此话从何谈起？");
		return 1;
	}
	if ( objectp(present("iron falun", (ob))))  { 
		command("say 你身上不是已经有轮了吗？");
		return 1;  
	} 
	if ( objectp(present("iron falun", environment(me)))){ 
		command("say 地上不是有只轮子吗？你眼睛瞎啦？？");
		return 1;
	} 
      
	if(query("lun_count") < 1){
		command("say 你来晚了，我这里现在没有轮供你使用。");
		return 1;
	}
	add("lun_count",-1);       
	lun = unew( luns[random(sizeof(luns))] );
	if(clonep(lun)){
		lun->move(ob);
		command("say 好吧，这只法轮你拿回去好好钻研。");
		ob->set_temp("give_lun",1);
		message_vision("$N交给$n一只法轮。\n", me, ob);
		return 1;
	}
	command("say 你来晚了，暂时我身边没有多余的法轮可以给你了。");
	return 1;
}

int give_lun2()
{ 
	mapping fam; 
	object me, ob,lun2;

	me = this_object();
	ob = this_player();
       
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "大轮寺"){
		command("say 你与本派素无来往，不知此话从何谈起？");
		return 1;
	}
	if ((int)ob->query_skill("longxiang-boruo", 1) < 200) {
		command("say 我大轮寺各种武功均和内功相辅相成, 你的内力修为不够，我不放心把本派宝物交给你。");
		return 1;
	}
      
	if(query("lun_count2") < 1){
		command("say 你来晚了，我这里现在没有风火轮供你使用。");
		return 1;
	}
	add("lun_count2",-1);       
	lun2 = unew(BINGQI_D("bestfalun"));
	if( clonep(lun2)){
		lun2->move(ob);
		command("say 好吧，这是本门之宝风火轮，你拿回去好好练功，光大我门。");
		message_vision("$N交给$n一只风火轮。\n", me, ob);
		return 1;
	}
	command("say 你来晚了，风火轮已给你的师兄取走了。");
	return 1;
}

string wulun_dazhuan()
{ 
	mapping fam; 
	object me, ob;
	int i,j,time;

	ob = this_object();
	me = this_player();
       
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "大轮寺"){
		command("say 你与本派素无来往，不知此话从何谈起？");
		return "";
	}
	

	if( me->query("quest/wulun/pass") )
	{
		
		me->set("title",HIC"五轮明王"NOR);
		me->set("mytitle/quest/wlmwtitle",HIC"五轮明王"NOR);
		return RANK_D->query_respect(me) + "，你已经解密了这个超级quest，又何故开此玩笑呢？";
	}
    if( me->query_skill("xiangfu-lun", 1) < 350 )
		return RANK_D->query_respect(me) + "，你的降伏轮造诣不够，还无法领悟我派五轮大转的精要所在！";

	time = time() - me->query("quest/wulun/time");
	if( me->query("quest/wulun/time") && time < 86400 && !wizardp(me) )
		return "嗯？你不是刚来请教过我五轮大法吗？还是再努力段时间吧！";

	//if( me->query_temp("quest/wulun/pass") )
	//	return RANK_D->query_respect(me) + "，我刚才不是已经回答你了吗？";
    
	message_vision(CYN"$N严肃的看着$n，慢慢说道：“我派的五轮大法讲究的是力大轮沉，但又具有千变万化之态、五五归一，最终循环不绝之势，\n"
	"你看好了，我给你演示一遍，看你自己的悟性了。\n"+
	HIY"金轮法王手中五个轮子连续飞掷，疾驰如电，迅捷无比。看的$n眼花缭乱\n"+
		HIR"五个轮子在空中叮当作响，声音嘈杂，似乎夹杂着隐隐的龙象梵唱，你不禁感觉有些头晕.\n"
	HIB"忽然，金轮法王双手不断操控，五个轮子渐渐成合一之态，但威力去更加迅猛。\n"
	HIC"你不禁看得心旌神摇，这五轮大法的威力竟然如此惊人！"NOR, ob, me);

    j = 20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	i=random(j);
	
	command("say 本门五轮大法唯有和龙象般若刚猛之力相配合方能发挥最大威力，这一点你千万要记住。\n");
	command("pat "+me->query("id"));
	if(i<3 && random(me->query("kar")) >= 27 ) //增加难度，成为一门绝技//调下来，让更多的人玩
	{
		tell_object(me,HIY"\n你听了金轮法王的指点，对五轮大法的奥妙颇有心得。\n"NOR);
		tell_object(me,HIG"\n你试图将内息冲到劳宫穴中，突然只觉手三阳经上一股热气直通双手，手中的轮子不禁豁然一轻。\n"
			             +"你下意识地将轮子向斜上方扔去，一阵呜呜之声传来，轮子似乎有神力相助似得，空中划了一个完美的曲线。\n"
						 +"然后又悠然回到你的手中，你终于领悟了这门绝技的运用法门。心中大喜之下，五个轮子陆续被抛了出去。\n"
						 +"一轮下来，先前郁闷之意全消，说不出的畅快受用。龙象般若功第一次通行时甚是艰难，任督两脉既通，道路熟\n"
						 +"了，第二次、第三次时自然而然的飞快运输，顷刻之间，你非常熟练地运使了一十八次。\n"NOR);
		me->set("quest/wulun/pass",1);
		me->set("title",HIC"五轮明王"NOR);
		me->set("mytitle/quest/wlmwtitle",HIC"五轮明王"NOR);
		me->set("quest/wulun/time",time());
		log_file("quest/xiangfulun", sprintf("%8s(%8s) 失败%d次后，学到降伏轮更高绝技,五轮大法完全融会贯通。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/wulun/fail"),i,me->query("combat_exp")) );
		command("haha"+me->query("id"));
		return "恭喜解密五轮大法成功。\n";
		//me->add(QUESTDIR4+"shenzhao",1);//
	}
	else
	{
		log_file("quest/xiangfulun", sprintf("%s(%s) 解密五轮大法失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/wulun/fail"), i,me->query("combat_exp")) );
		tell_object(me,HIY"你听了金轮法王的指点，可是对五轮大转的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/wulun/fail",1);
		me->set("quest/wulun/time",time());
		return "非常遗憾解密五轮大法失败"+me->query("quest/wulun/fail")+"次。\n";
	}
}