// Npc: /kungfu/class/shaolin/xuan-ku.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

string ask_me();
int ask_ranmu();
int ask_shoudao();

void create()
{
        object ob;
        set_name("玄苦大师", ({
                "xuanku dashi",
                "xuanku",
                "dashi",
        }));
        set("long",
                "他是一位白须白眉的老僧，身穿一袭银丝棕黄袈裟。他身材瘦高，\n"
                "脸上满布皱纹，手臂处青筋绽露，似乎久经风霜。\n"
        );


        set("nickname", "罗汉堂首座");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");
        
        set("age", 70);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 38000);
        set("max_jing", 8000);
        set("neili", 35000);
        set("max_neili", 35000);
        set("jiali", 200);
        set("combat_exp", 12000000);
        set("score", 500000);

        set_skill("force", 500);
        set_skill("yijin-jing", 500);
		set_skill("ranmu-daofa", 500);

        set_skill("dodge", 500);
        set_skill("shaolin-shenfa", 500);
        set_skill("parry", 500);
        set_skill("cuff", 500);
        set_skill("club", 500);
        set_skill("blade", 500);
        set_skill("sword", 500);
        set_skill("luohan-quan", 500);
		set_skill("ruying-suixingtui", 500);
		set_skill("leg", 500);
		set_skill("hand", 500);
		set_skill("qianye-shou", 500);
        set_skill("weituo-chu", 500);
        set_skill("xiuluo-dao", 500);
        set_skill("fumo-jian", 500);
        set_skill("buddhism", 200);
        set_skill("literate", 150);
        set_skill("zui-gun",500);
        map_skill("force", "yijin-jing");
		map_skill("dodge", "shaolin-shenfa");
		map_skill("parry", "luohan-quan");
        map_skill("cuff", "luohan-quan");
        map_skill("club", "weituo-chu");
        map_skill("blade", "ranmu-daofa");
        map_skill("sword", "fumo-jian");
		 map_skill("leg", "ruying-suixingtui");
        map_skill("hand", "qianye-shou");


        prepare_skill("hand", "qianye-shou");
        prepare_skill("leg", "ruying-suixingtui");
        create_family("少林派", 36, "弟子");
        set("chat_chance_combat", 70);
	    set("chat_msg_combat", ({
			(: perform_action, "leg.ruying" :),
			(: perform_action, "hand.qianshou" :),
			(: exert_function, "jingang" :),
	    }));
        set("inquiry", ([
                "十八罗汉阵"       : (: ask_me :),
			    "燃木手刀绝技"       : (: ask_shoudao :),
			    "燃木绝技"       : (: ask_ranmu :),

                "罗汉大阵"         : (: ask_me :)
        ]));

        setup();
	if (clonep()) {
                ob = unew(BINGQI_D("blade/jinnao"));
		if (ob) {
			destruct(ob);
                        ob = unew(BINGQI_D("blade/jinnao2"));
		}
              if (!ob) ob = unew(BINGQI_D("blade"));
		ob->move(this_object());
		ob->wield();
		carry_object("/d/shaolin/obj/xuan-cloth")->wear();
	}
}

#include "/kungfu/class/shaolin/xuan-ku.h"

int ask_shoudao()
{
	object me=this_player();
	if (me->query("family/family_name")!="少林派")
	{
		command("say 你不是我少林弟子，来此作甚！\n");
		return 1;
	}
	if (me->query_skill("ranmu-daofa",1)<450)
	{
		command("say 你燃木刀法功力不足450级，还请继续努力！\n");
		return 1;
	}
	if (me->query_skill("blade",1)<450)
	{
		command("say 你基本刀法功力不足450级，还请继续努力！\n");
		return 1;
	}
	if (me->query_skill("xiuluo-dao",1)<450)
	{
		command("say 燃木刀法需要伏魔的功法，你修罗刀法功力不足450级，还请继续努力！\n");
		return 1;
	}
	if (me->query_skill("cibei-dao",1)<450)
	{
		command("say 燃木刀法蕴含佛家慈悲真意，你慈悲刀功力不足450级，还请继续努力！\n");
		return 1;
	}
	if (time()-me->query("quest/sl/rmdf/shoudao/time")<86400)
	{
		command("say 你来的太频繁了，要知道佛家讲究的是顿悟！\n");
		return 1;
	}
	if (me->query("quest/sl/rmdf/shoudao/pass"))
	{
		command("say 你的燃木手刀绝技已经修成，不必麻烦鸠摩智了！\n");
		me->set("title",HIY"少林寺"HIR"燃木刀法传人"NOR);
		me->set("mytitle/quest/rmdtitle",HIY"少林寺"HIR"燃木刀法传人"NOR);
		return 1;
	}

	command("say 燃木刀法是少林七十二绝世中刀法的极致,能练成这门刀法足以纵横江湖。\n");
	command("say 我也不过是刚刚练成到第七境界而已，如果能修炼到最高第九境界，则。\n");
	command("say 仅凭双手的劲气，就足以发出刀气，以气伤人于无形。\n");
	command("say 这种功夫非功力深厚不可达到。\n");
	command("say 你若修炼易筋经神功大成，也可以做到以气驭刀。\n");
	command("say 当然也有一种捷径，就是刀气运转之法。\n");
	command("consider ");
    command("say 想当初大轮寺高僧鸠摩智凭借一身功力施展我少林七十二绝技，其中就曾演练过这燃木刀法\n");
	command("say 老衲当时看其空手施展燃木刀法，以掌化刀，刀气纵横，虽然不是我少林内功，但招式错不了！\n");
	command("say 这法门我想是一定错不了的，你若感兴趣我就修书一封，你去大轮寺与大轮明王讨教一番。\n");
	command("say 说不定有一番收获。\n");
	command("hehe ");
	command("say 大轮明王佛法无边，已经大彻大悟，你去请教，我想能有一番收获。\n");
	command("say 这门武功和基本刀法与富源休戚相关，你切要多多练习方有奇效。\n");

	me->set_temp("rmdf/askku",1);
	return 1;
}

int ask_ranmu()
{
	object me=this_player();
	if (me->query("family/family_name")!="少林派")
	{
		command("say 你不是我少林弟子，来此作甚！\n");
		return 1;
	}
	if (me->query_skill("ranmu-daofa",1)<250)
	{
		command("say 你燃木刀法功力不足250级，还请继续努力！\n");
		return 1;
	}
	if (me->query("quest/sl/rmdf/ranmu/pass"))
	{
		command("say 你的燃木绝技已经修成，不必继续劈柴了！\n");
		return 1;
	}
	if (me->query_skill("blade",1)<250)
	{
		command("say 你基本刀法功力不足250级，还请继续努力！\n");
		return 1;
	}
	if (me->query_skill("xiuluo-dao",1)<250)
	{
		command("say 燃木刀法需要伏魔的功法，你修罗刀法功力不足450级，还请继续努力！\n");
		return 1;
	}
	if (me->query_skill("cibei-dao",1)<250)
	{
		command("say 燃木刀法蕴含佛家慈悲真意，你慈悲刀功力不足450级，还请继续努力！\n");
		return 1;
	}
	if (time()-me->query("quest/sl/rmdf/ranmu/time")<86400)
	{
		command("say 你来的太频繁了，要知道佛家讲究的是顿悟！\n");
		return 1;
	}

	command("say 燃木刀法是少林七十二绝世中刀法的极致,能练成这门刀法足以纵横江湖。\n");
	command("say 我也不过是刚刚练成到第七境界而已，如果能修炼到最高第九境界，则。\n");
	command("say 仅凭双手的劲气，就足以发出刀气，以气伤人于无形。\n");
	command("say 这种功夫非功力极其难练，尤其是基本功的修炼，非意志坚韧之辈不可达到。\n");
	command("say 你若想将燃木刀再上一个台阶，就去般若堂六部找澄信。\n");
	command("say 他会帮你学习这门武功进阶的。\n");

	me->set_temp("rmdf/askkuranmu",1);
	return 1;
}