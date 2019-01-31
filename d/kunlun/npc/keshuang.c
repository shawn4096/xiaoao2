// ֣��ˬ.c
#include <ansi.h>
inherit NPC;
int ask_feng();
void create()
{
	object ob;
	set_name("֣��ˬ", ({ "zheng keshuang", "zheng", "keshuang"}));
        set("long", 
"����֣�����ӣ��ֿ�ˬ������ü��Ŀ�㣬һ���˲š�\n"
"ü�����¶��һ�ɹ���ӵܸ�����������������\n");
        set("title","��������");
        set("gender", "����");
        set("age", 24);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 23);
        set("int", 23);
        set("con", 24);
        set("dex", 28);
        set("shen",0);

        set("max_qi", 20000);
        set("max_jing", 5000);
	      set("eff_jingli", 6000);
        set("jiali", 200);
        set("combat_exp", 6800000);
		set("class","bonze");

        set_skill("dodge",400);
        set_skill("literate", 220);
        set_skill("taxue-wuhen",400);
        set_skill("leg",400);
        set_skill("cuff", 400);
        set_skill("zhentian-quan",400);        
        set_skill("force",400);
        set_skill("parry",400);
	    set_skill("sword", 400);
		set_skill("poison", 150);
	    set_skill("xunlei-jian", 400);
		set_skill("xuantian-wuji", 400);
		set_skill("chuanyun-tui", 400);

        map_skill("dodge", "taxue-wuhen");
        map_skill("force", "xuantian-wuji");
		map_skill("parry", "xunlei-jian");
	    map_skill("sword", "xunlei-jian");
	    map_skill("cuff", "zhentian-quan");
	    map_skill("leg", "chuanyun-tui");

	    prepare_skill("cuff", "zhentian-quan"); 
		prepare_skill("leg", "chuanyun-tui"); 

	    set("chat_chance_combat", 45);
		set("chat_msg_combat", ({
  		(: perform_action, "sword.sanqiu" :),
  		(: perform_action, "sword.podi" :),
		(: perform_action, "sword.benlei" :),
		(: exert_function, "wuji" :),			
		}));
		set("inquiry", ([
			"������" : (: ask_feng :),
	
	]));

        setup();
		if(clonep()) {
			ob = unew("/clone/weapon/changjian");
			if(ob) {
			ob->move(this_object());
			ob->wield();
		}
	}
	//carry_object(BINGQI_D("changjian"))->wield();
	carry_object(MISC_D("cloth"))->wear();
}

int ask_feng()
{
	object me;
	me=this_player();
	if (!me->query_temp("quest/kl/baifxf/start"))
	{
		command("say �������Ե�޹ʣ��α����룡\n");
		return 1;
	}
	command("say �����߸�֮��������������ı��Ʋ������ҡ�\n");
	command("say ��Ȼ��ʦ������������(baohu)�ҵģ����Ҿͷ����ˡ�!\n");
	command("say ���˿���������֣���һ��Ҫǧ�����С�ġ�!\n");
	command("say �������ս�پ����������䡣!\n");

	me->delete_temp("quest/kl/baifxf/start");
	me->set_temp("quest/kl/baifxf/askzheng",1);
	return 1;
}
