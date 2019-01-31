// huodu.c 霍都
// by sohu
// 狂风迅雷功

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name(HIW"霍都"NOR, ({ "huo du", "huodu" ,"huo","du"}));
	set("long",@LONG
他是金轮法王的小弟子，得到法王亲传传授，一声功夫极为了得，他
眉清目秀，一看就是极其聪明技巧之辈，身穿青色长衫，手执一柄玉扇
轻轻摇晃，显得甚是潇洒，但性格巧诈凉薄。
LONG
	);
	set("title",  "大轮寺第十二代弟子" );
	set("nickname","蒙古小王爷");
	set("gender", "男性");
	set("age", 39);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 23);
	set("int", 38);
	set("con", 24);
	set("dex", 24);
	set("max_qi", 19000);
	set("eff_jing", 5000);
	set("max_jing", 5000);
	set("eff_jingli", 5000);
	set("max_jingli", 5000);

	set("neili", 20000);
	set("max_neili", 20000);
	set("jiali", 200);
	set("combat_exp", 8200000);
	set("score", 30000);
	//set("unique", 1);

	set_skill("mizong-fofa", 200);
	set_skill("literate", 200);
	set_skill("force", 450);
	set_skill("longxiang-boruo", 450);
	set_skill("dodge", 450);
	set_skill("yuxue-dunxing", 450);
	set_skill("hand", 450);
	set_skill("dashou-yin", 450);
	set_skill("claw", 450);
	set_skill("tianwang-zhua", 450);
	set_skill("wushang-dali",450);
	set_skill("staff",450);
	set_skill("parry", 450 );
	set_skill("brush",450);
	set_skill("kuangfeng-xunlei", 450 );

	map_skill("force", "longxiang-boruo");
	map_skill("dodge", "yuxue-dunxing");
	map_skill("hand", "dashou-yin");
	map_skill("parry", "kuangfeng-xunlei");
	map_skill("claw", "tianwang-zhua");
	map_skill("brush", "kuangfeng-xunlei");

	prepare_skill("hand","dashou-yin");
	prepare_skill("claw","tianwang-zhua");
    set("inquiry", ([
               // "武器" : (: give_lun  :),
			   // "五轮大法" : (: wulun_dazhuan  :),
              //  "兵器" : (: give_lun  :),
            //    "风火轮" : (: give_lun2  :),
                
       ]));
	create_family("大轮寺", 11, "弟子");
	set("class", "mizong");
    set("chat_chance_combat", 60);
    set("chat_msg_combat", ({
                (: exert_function, "longxiang" :),
                (: perform_action, "brush.kuangfeng" :), 
				(: perform_action, "brush.xunleigong" :), 
	}));
	setup();
	carry_object("/d/xueshan/npc/obj/qinxiu-jiasha")->wear();
	carry_object("/clone/weapon/brush/baiyushan")->wield();
	add_money("silver",50);
}

void attempt_apprentice(object ob)
{
	if ((string)ob->query("family/family_name") != "大轮寺") {
		 command("say"+ RANK_D->query_respect(ob) +
			"不是本寺弟子，在这里捣什么乱？！");
		return;
	}

	if ((int)ob->query_skill("mizong-fofa", 1) < 150) {
	       command("say 密宗佛法是各项武功之本，不足150，你再勤加修炼吧。");
		command("say"+ RANK_D->query_respect(ob) +
			"再熬几个通宵，多多钻研钻研本门的心法吧。");
		return;
	}

	if ((string)ob->query("class") != "mizong") {
		message_vision("霍都看了看你头顶，又摸了摸自己的光头。",this_player());
		command("say 你还没出家，不能表示你是真心侍奉金刚佛，我不能收你。");
		command("say 这位" + RANK_D->query_respect(ob) +
			"如能早下决心，献身侍奉我佛再来找我吧。");
		return;
	}
	if ((int)ob->query_skill("longxiang-boruo", 1) < 220) {
	    command("say 龙象波若功是大轮寺各项武功之本，不足220，你再勤加修炼吧。");
		command("say"+ RANK_D->query_respect(ob) +
			"再熬几个通宵，多多钻研钻研本门的心法吧。");
		return;
	}
	if ((int)ob->query_skill("dashou-yin", 1) < 220) {
	    command("say 大手印是各项武功之本，不足220，你再勤加修炼吧。");
		command("say"+ RANK_D->query_respect(ob) +
			"再熬几个通宵，多多钻研钻研本门的心法吧。");
		return;
	}
	command("say 好吧，你以后就是我的弟子了，可要刻苦勤修，不能偷懒呀。");
	command("recruit " + ob->query("id"));
	ob->set("title",   "大轮寺第十二代弟子"  );
}
