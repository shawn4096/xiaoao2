// shibowei.c 史伯威

inherit NPC;
int ask_gui();

void create()
{
        set_name("史伯威", ({ "shi bowei","shi", "bowei" }));
        set("nickname", "白额山君");
        set("long", 
        "他就万兽山庄五兄弟的大哥，身材魁梧，面色微黑。\n"
        "据说一身御兽本领出神入化。\n");
        set("gender", "男性");
        set("age", 38);
        set("attitude", "peaceful");
        set("shen", 4500);
        set("str", 25);
        set("int", 18);
        set("con", 25);
        set("dex", 20);
        
        set("max_qi", 18000);
        set("max_jing", 6000);
        set("neili", 9000);
        set("max_neili", 9000);
        set("jiali", 150);
        set("combat_exp", 4500000);
         
    set_skill("force", 390);
    set_skill("hunyuan-yiqi", 390);
    set_skill("dodge", 390);
    set_skill("shaolin-shenfa", 380);
    set_skill("cuff", 390);
    set_skill("jingang-quan", 380);
    set_skill("parry", 390); 
    set_skill("literate", 120);

    map_skill("force", "hunyuan-yiqi");
    map_skill("dodge", "shaolin-shenfa");
    map_skill("cuff", "jingang-quan");
    map_skill("parry", "jingang-quan");
    prepare_skill("cuff", "jingang-quan");

    set("inquiry", ([
                "神雕侠" : "三弟的病全仗他老人家才得以康复。",
                "霍都" : "再要见到那个狗贼，一定要杀了他。",
				"西山一窟鬼" : (: ask_gui :),
              	//"黯然销魂掌"  : (: ask_anranzhang :),
                
    ]) );
        
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 50);
}

int ask_gui()
{
	command("say 您既然是神雕侠派你来的，我是信得过的。\n");
	command("say 西山一窟鬼，他们是七个鬼，无恶不作，跟我们是死仇。\n");
	command("say 我三弟史叔刚的伤就是他们给我造成的，不杀他们誓不为人！\n");
	command("sigh ");
	command("consider");
	this_player()->set_temp("quest/shendiao/大雪风陵渡/askgui",1);
	return 1;

}

int shi_say1()
{
	command("say 既然是神雕侠派您来的，那我就不见外了，请您为我三弟疗伤。\n");
	command("say 我这三弟的伤在经脉，极为难治，属于阴寒之气所致.\n");
	command("say 必须要有九尾灵狐的血才能治疗.\n");
	command("sigh.\n");
	return 1;

}