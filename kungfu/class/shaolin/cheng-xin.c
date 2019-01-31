// Npc: /kungfu/class/shaolin/cheng-xin.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;
#include <ansi.h>

string ask_qys();

void create()
{
	set_name("澄心", ({
		"chengxin luohan",
		"chengxin",
		"fuhu",
		"luohan",
	}));
	set("long",
		"他是一位须发花白的老僧，身穿一袭金边黑布袈裟。他身材瘦高，\n"
		"太阳穴高高鼓起，似乎身怀绝世武功。\n"
	);

	set("nickname", "伏虎罗汉");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 60);
	set("shen", 5000);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("max_qi", 2500);
	set("max_jing", 1000);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 100);
	set("combat_exp", 600000);
    set("unique", 1);

	set_skill("force", 120);
	set_skill("yijin-jing", 120);
	set_skill("dodge", 120);
	set_skill("shaolin-shenfa", 120);
	set_skill("hand", 120);
	set_skill("qianye-shou", 120);
	set_skill("parry", 120);
	set_skill("buddhism", 120);
	set_skill("literate", 120);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("hand", "qianye-shou");
	map_skill("parry", "qianye-shou");

	prepare_skill("hand", "qianye-shou");
	set("inquiry", ([
		"如来千叶手绝技" : (: ask_qys :),
	
	]));

	create_family("少林派", 37, "弟子");

	setup();

        carry_object("/d/shaolin/obj/cheng-cloth")->wear();
}


#include "/kungfu/class/shaolin/cheng.h"

string ask_qys()
{
	mapping fam;
	object me=this_player();

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "少林派")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";

	if (me->query_skill("qianye-shou",1)<450)
		return RANK_D->query_respect(this_player()) +"你的如来千叶手等级不足450级，请继续努力！";

	if (time()-me->query("quest/sl/qys/time")<86400)
	{
		return RANK_D->query_respect(this_player()) +"少林最重顿悟，你来的太频繁了，请继续努力！";

	}
	command("say 这如来千叶手乃是少林七十二绝技手法中的极致。\n");
	command("say 一掌分出，一分为二，二分为四，直到将无穷无尽。\n");
	command("say 我也没有练成，不过当初方正大师在少林和任我行一战，如来千叶手名扬天下。\n");
	command("say 你如果想学就在此认真参禅(cancha 如来千叶手)吧。\n");
	me->set_temp("qys/askchengxin",1);
	return "如来千叶手从不弱于人！你要好好修习。\n";

}