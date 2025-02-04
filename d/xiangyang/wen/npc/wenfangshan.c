// /d/city/npc/wenfangshan

inherit NPC;

int qingjiao(string arg);
 
void create()
{
	set_name("温方山", ({ "wen fangshan", "wen", "fangshan" }));
	set("title", "温家五老");
	set("long", 
	"他就是温家五老的老三温方山。\n"
	"一个五十来岁的老者，圆圆的脸上，流露着阴险的神情。\n");
	set("gender", "男性");
	set("age", 52);
	set("attitude", "friendly");
	set("shen", -9000);
	set("str", 30);
	set("int", 30);
	set("con", 25);
	set("dex", 27);
        
	set("max_qi", 5000);
	set("eff_jingli", 3800);
	set("max_jing", 3800);
	set("neili", 5000);
	set("jingli", 3800); 
	set("max_neili", 5000);
	set("jiali", 100);
	set("combat_exp", 2700000);
         

	set_skill("force", 300);
	set_skill("yijin-jing", 300);
	set_skill("dodge", 300);

	set_skill("shaolin-shenfa", 300);
	set_skill("cuff", 300);
	set_skill("wenjia-daofa", 300);
	set_skill("parry", 300);
	set_skill("blade", 300);
	set_skill("wenjia-quan", 300);
	set_skill("literate", 110);

        map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("cuff", "wenjia-quan");
	map_skill("parry", "wenjia-quan");
	map_skill("blade", "wenjia-daofa");
	prepare_skill("cuff", "wenjia-quan");
	prepare_skill("cuff", "wenjia-quan"); 
 
	set("inquiry", ([
		"五行阵" : (: qingjiao :),
	]));
 
	setup(); 
	carry_object(ARMOR_D("cloth"))->wear();
}

int qingjiao(string arg)
{
	object me = this_player();
	int lvl = me->query_skill("wuxing-zhen", 1);

	if (!living(me)) return 0;
	if (!living(this_object())) return notify_fail("你先把他弄醒再说吧！\n");
	if( me->query("combat_exp") < 800000) {
		command("say 你的经验太差，恐怕无法领会我家传绝技。\n");
		return 1;
	}
	if( me->query_skill("force",1) < 160) {
		command("say 你的基本内功级别太差，恐怕无法领会我家传绝技。\n");
		return 1;
	}
	if( me->query("potential")<= 0) {
		command("say 今天我已经教你很多了，你还是改天再来吧。\n");
		return 1;
	}
	if (lvl < 200) {
		message_vision("$N向$n请教有关五行阵的奥妙。\n", me, this_object());
		me->receive_damage("jing", 30);
		write("你听了温方山的指点，对五行阵法的奥妙似乎有些心得。\n");
		me->add("potential",-(random(3)+2));
		if( me->query("potential") < 0)
			me->set("potential",0);
		me->improve_skill("wuxing-zhen", 20+random(me->query_int()));
		return 1;
	}
	command( "say 我已经没有什么可以教你的了。");
	return 1;
}
