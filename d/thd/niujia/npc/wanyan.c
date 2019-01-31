// wanyanhonglie.c

inherit NPC;
#include <ansi.h>
string ask_name();
string ask_help();
#define QUESTDIR1 "quest/ÉäµñÓ¢ĞÛ´«/·çÑ©¾ª±ä/"

void create()
{
       // set_name("ÍêÑÕºéÁÒ", ({"wanyan honglie", "honglie", "wanyan"}));
        set_name("ÖĞÄêÄĞ×Ó", ({"zhongnan nanzi", "nanzi", "man"}));
		set("gender", "ÄĞĞÔ");
       // set("title", HIY"´ó½ğ¹úÕÔÍõÒ¯"NOR);
        set("age", 31);
        set("class", "officer");
	      set("long","[1;31mËû¿´ÆğÀ´ÊÜÁËºÜÖØµÄÉË£¬¿´ÉÏÈ¥¿ìÒª²»ĞĞÁË¡£[0m\n");
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 26);
        set("per", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 26);

        set("qi", 20000);
        set("max_qi", 20000);
        set("jing", 3200);
        set("max_jing", 3200);
        set("neili", 8300);
        set("max_neili", 8300);
        set("jiali", 10);
		
        set("combat_exp", 2500000);
        set("score", 10000);
		set("inquiry", ([
			"name" : (:ask_name:),
			"¾ÈÄã" : (:ask_help:),
			]));

        set_skill("force", 250);
        set_skill("dodge", 240);
        set_skill("parry", 240);
        set_skill("cuff",240);
		set_skill("caoshang-fei",250);
		set_skill("taizu-quan",250);

        set_skill("baduan-jin",250);
		map_skill("force","baduan-jin");
       	map_skill("dodge","caoshang-fei");
       	map_skill("cuff","taizu-quan");
       	map_skill("parry","taizu-quan");

		setup();
        carry_object("/clone/armor/jinduan")->wear();
        carry_object("d/mr/obj/guanxue")->wear();

}

string ask_name()
{
	object me=this_player();
	if (!me->query("quest/ÉäµñÓ¢ĞÛ´«/·çÑ©¾ª±ä/notongyin"))
	{
		return "ÎÒ²»ÏàĞÅÄã£¬ÄãÊÇË­£¿ÓĞÊ²Ã´ÆóÍ¼£¿\n";
	}
	command("say ¼ÈÈ»ÕâÎ»Ó¢ĞÛÈç´ËÏÀ¸ÎÒåµ¨£¬ÎÒ¾ÍÔİÇÒÏàĞÅÄã£¡\n");
	command("say ÎÒÊÇ´ó½ğ¹úÍõÒ¯ÍêÑÕºéÁÒ£¬Çë×³Ê¿¾ÈÎÒ£¬±Ø²»¸ºÄã£¡\n");
	set_name("ÍêÑÕºéÁÒ", ({"wanyan honglie", "honglie", "wanyan"}));
	set("title", HIY"´ó½ğ¹úÕÔÍõÒ¯"NOR);
	me->set_temp("quest/ÉäµñÓ¢ĞÛ´«/·çÑ©¾ª±ä/askwanyanname",1);
	return "Ó¢ĞÛÈôÄÜÒ»Â·»¤ËÍÎÒ»Ø¾©£¬±¾Íõ¶¨µ±ÖØĞ»£¡\n";
}
string ask_help()
{
	object me=this_player();
	if (!me->query("quest/ÉäµñÓ¢ĞÛ´«/·çÑ©¾ª±ä/notongyin"))
	{
		return "¾ÓĞÄØÏ²â£¬ÄÑµÃĞÅÈÎ£¡£¿\n";
	}

	if (!me->query_temp("quest/ÉäµñÓ¢ĞÛ´«/·çÑ©¾ª±ä/askwanyanname"))
	{
		return "ÄãÒ»¿´¾ÍÊÇËØÑø¼°ÆäµÍÏÂ£¬Ò»µãÀñÃ²¶¼Ã»ÓĞ£¡\n";
	}
	message_vision(HIY"$N¸¶ÏÂÉí×Ó£¬ÇÄÉùËµµÀ£¬¡°ËûÃÇÔÚÇ°ÔººÈ¾Æ£¬ÎÒÀ´¾ÈÄã£¬ÄãÒªÅäºÏÎÒ¡±!\n"NOR,me);
	command("say ×³Ê¿¾ÈÎÒ£¬±¾Íõ±Ø²»¸ºÄã£¡\n");
	apply_condition("liuxue",1000);
	apply_condition("neishang",1000);
	me->set_temp("quest/ÉäµñÓ¢ĞÛ´«/·çÑ©¾ª±ä/answerhelpwanyan",1);

	return "Ó¢ĞÛ¼ÈÈ»´ğÓ¦¾ÈÎÒ£¬±¾Íõ¶¨µ±ÖØĞ»£¡\n";
}