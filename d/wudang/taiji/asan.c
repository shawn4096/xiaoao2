#include <ansi.h>
inherit NPC;
void create()
{
        set_name("阿三", ({ "a san", "asan", "san" }) );
        set("title", HBRED"铁臂金刚"NOR);
        set("long", "那阿三却是精壮结实，虎虎有威，脸上、手上、项颈之中，\n"+
					 "凡是可见到肌肉处，尽皆盘根虬结，似乎周身都是精力，胀\n"+
					 "得要爆炸出来，他左颊上有颗黑痣，黑痣上生着一丛长毛。\n");
        set("gender", "男性" );
        set("age", 54);
		set("con",25);
        set("dex",25);
        set("unique", 1);
        set("per", 20);
        set("no_get", 1);
        set("max_qi", 30000);
        set("max_jing", 7000);
        set("neili", 20000);
        set("max_neili", 20000);
        set("jiali", 200);
        set("combat_exp", 12500000);
        set("eff_jingli", 7000);

        set_skill("force", 480);
        set_skill("hunyuan-yiqi", 480);
        set_skill("dodge", 480);
        set_skill("shaolin-shenfa", 480);
        set_skill("finger", 500);
        set_skill("jingang-zhi", 520);
        set_skill("parry", 480);
        set_skill("literate", 150);
 
        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "jingang-zhi");
        map_skill("parry", "jingang-zhi");
        prepare_skill("finger", "jingang-zhi");
    	set("chat_chance", 70);
		set("chat_msg_combat", ({
        	(: perform_action, "finger.fumo" :),
        	(: perform_action, "finger.jingangzhi" :),
        	(: perform_action, "finger.pokuai" :),
        }));
        setup();
         carry_object("/d/wudang/obj/white-robe")->wear();/* */
}

int greet_zhang()
{
	command("hi");
	command("say 张真人请!");
	command("say 小人最近也没做过什么事，只是在西北道上曾跟少林派一个名叫空性的和尚过招，\n指力对指力，破了他的龙爪手，随即割下他的首级。");
	command("say 不知道我这功夫能否值得张真人亲自下场指教？");
	command("say 当然，若张真人认为自己低挡不住，只要说声，小的就不跟你比试了。");
	command("say 张真人请!");
	return 1;

}
int greet_yu()
{
	command("heng ");
	command("say 这是妖法邪术，什么太极拳了？!");
	command("say 是金刚指力便怎样？谁教你硬充好汉，不肯说出屠龙刀的所在？这二十年残废的滋味可好受么？。");
	command("say 不错！他是我师弟，他可不叫空相，法名刚相。张真人，我‘金刚门’的般若金刚掌，跟你武当派的掌法比起来怎样？");
	command("say 临阵学武，未免迟了罢？");
	command("say 看招!");
	return 1;

}