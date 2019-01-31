// fei.c 嵩山派第三代弟子 费彬
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
string ask_guanri();

void create()
{
        set_name("费彬", ({ "fei bin", "fei", "bin" }));
        set("nickname", HIY"大嵩阳手"NOR);
        set("long", "这人四十来岁，中等身材，瘦削异常，上唇留了两撇鼠须，是嵩山
派掌门左冷禅的第四师弟费彬、一套大嵩阳手武林中赫赫有名。\n");
        set("gender", "男性");
        set("age", 49);
        set("per", 18);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 25);
        set("int", 23);
        set("con", 26);
        set("dex", 26);
        set("unique", 1);

        set("max_qi", 13000);
        set("max_jing", 6000);
        set("eff_jingli", 6000);
        set("jiali", 250);
        set("combat_exp", 65000000);
        set("shen", -1400000);

		set_skill("literate", 200);
		set_skill("force", 400);
		set_skill("parry", 460);
		set_skill("sword", 400);
		set_skill("dodge", 400);
		set_skill("hand", 460);
		set_skill("zhongyuefeng", 400);
		set_skill("songyang-shou", 460);
		set_skill("hanbing-zhenqi", 400);
		set_skill("songshan-jian", 400);
		set_skill("songyang-jue", 200);

		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songyang-shou");
		map_skill("sword", "songshan-jian");
		prepare_skill("hand", "songyang-shou");
		create_family("嵩山派", 3, "弟子");
		set("chat_chance", 25);
		set("chat_msg", ({
			(: random_move :)
		}) );
		set("chat_chance_combat", 80);
		set("chat_msg_combat", ({
			(: perform_action, "hand.yinyang" :),
			(: perform_action, "hand.junji" :),
			(: perform_action, "hand.tuota" :),
			(: perform_action, "hand.xianhe" :),
			(: exert_function, "hanbing" :),
			(: exert_function, "juhan" :),
		 }));
		set("inquiry", ([
			"嵩山派" : "我们嵩山派是五岳剑派之首！\n",
			"五岳剑派" : "我们五岳剑派在武林之中势力巨大，可与少林、武当抗衡。\n",
			"左冷禅" : "他就是我们的掌门人，功夫深不可测。\n",
			 "观日峰" : (: ask_guanri :),
			//"飞舞绝技" : (: ask_feiwu :),

		]) );
			setup();
			carry_object(ARMOR_D("changpao1"))->wear();
}
string ask_guanri()
{
	object me=this_player();
	if (me->query("family/family_name")!="嵩山派")
	{
		command("say 你不是我嵩山弟子，来此作甚？");
		return "哼！";
	}
	if (me->query_skill("songshan-jian",1)<200)
	{
		command("say 你嵩山剑法不足200，来此作甚？");
		return "哼！";
	}
	if (!me->query("quest/ss/dichuan"))
	{
		command("say 你非我嵩山嫡传弟子，来此作甚？");
		return "哼！";
	}
	command("say 我大嵩山有一处隐蔽的美景之地，非嵩山弟子不得进入。\n");
	command("say 哪儿就是我大嵩山的观日峰。\n");
	command("say 据掌门讲他当初就是在此处观摩松涛而顿悟飞舞绝技。\n");
	command("say 看你是不错的人才，我就告诉你这些，你自己去领悟去吧。\n");
	me->set_temp("feiwu/askfei",1);
	return "";

}
