// yu.c 俞莲舟
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_me();
void create()
{
        set_name("俞莲舟", ({ "yu lianzhou", "yu" }));
        set("nickname", "武当二侠");
        set("long", 
                "他就是张三丰的二弟子俞莲舟。\n"
                "他今年五十岁，身材魁梧，气度凝重。\n"
                "虽在武当七侠中排名第二，功夫却是最精。\n");
        set("gender", "男性");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen", 12000);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 28);
        set("unique", 1);
        set("max_qi",45000);
        set("eff_jingli",15000);
        set("max_jing", 15000);
        set("neili",45000);
        set("max_neili", 45000);
        set("jiali", 150);
        set("combat_exp",12500000);

        set_skill("force", 460);
        set_skill("yinyun-ziqi", 460);
        set_skill("dodge",460);
        set_skill("tiyunzong",460);
        set_skill("wudang-quan",460);
        set_skill("cuff",460);
        set_skill("hand",460);
        set_skill("taiji-quan", 460);
        set_skill("juehu-shou",460);
        set_skill("parry", 460);
        set_skill("sword", 460);
        set_skill("taiji-jian", 460);
        set_skill("taoism", 200);
        set_skill("literate", 200);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        map_skill("cuff", "wudang-quan");
        map_skill("hand", "juehu-shou");

        prepare_skill("cuff", "wudang-quan");
        prepare_skill("hand", "juehu-shou");
        set("inquiry", ([
                "绝户手" : (: ask_me :),
               // "虎爪" : (: ask_me :),
               ]));
        create_family("武当派", 2, "弟子");

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
        carry_object("/d/wudang/obj/daolv")->wear();
}

void kill_ob(object me)
{
        set("neili", 5000); 
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
              (: perform_action, "dodge.zong" :),
        }));
        ::kill_ob(me);
}

void attempt_apprentice(object ob)
{
        object me;
        me=this_player();
        if ((int)ob->query("shen") < 1500000) {
                command("say 我武当乃是堂堂名门正派，对弟子要求极严。不足1.5m正神别来找我");
                command("say " + RANK_D->query_respect(ob) + "若能做出" +
                   "几件侠义之事，我就考虑收你。");
                return;
        }
	   if ((int)ob->query_skill("taoism",1) < 180) {
                command("say 你的道学修为不够，只怕你跟我学了虎爪绝户手后出去害人！");
                return;
        }
	   if ((int)ob->query_skill("yinyun-ziqi",1) < 300) {
                command("say 你的氤氲紫气修为不够300，只怕你跟我学了虎爪绝户手后出去害人！");
                return;
        }
	    if (ob->query("gender") != "男性" && ob->query("gender") != "女性") {
                command("say 你阴阳不调，还想跟我学绝户手？");
                return;
        }
        if (present("letters", me)){
        	destruct(present("letters",me));
                command("say 好吧，既然" + RANK_D->query_respect(ob) + "有俞师弟的介绍信，也是" +
                        "我辈中人，今天就收下你吧。");
                command("recruit " + ob->query("id"));
        }
        else
                command("say 我对弟子要求极严。非心地善良者不能学我虎爪绝户手!");
        return;
          
}
string ask_me()
{
  object me;
        me=this_player();
		 if (me->query("family/family_name") != "武当派" || me->query("family/master_id") != "yu lianzhou")
			 return "\n你不是我的弟子，你想干什么？\n";
         if ((int)me->query("shen") < 5000) {
                command("say 我武当乃是堂堂名门正派，对弟子要求极严。");
                command("say " + RANK_D->query_respect(me) + "若能做出" +
                   "几件侠义之事，我就考虑收你。");
                return;
        }
	     if ((int)me->query_skill("taoism",1) < 100) {
                command("say 你的道学修为不够，只怕你跟我学了虎爪绝户手后出去害人！");
                return;
        }
	    if (me->query("gender") != "男性" && me->query("gender") != "女性") {
                command("say 你阴阳不调，还想跟我学绝户手？");
                return;
        }
        
	   //增加时间和经验间隔限制
	   
	    if(me->query("jh_time")&& (time()-me->query("jh_time",1))<86400)
	    {
		   command("shake "+me->query("id"));
		   if(random(2)) return "今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！";
		   else return "学习绝户手也不用急在一时，"+RANK_D->query_respect(me) +"先行休息去吧！";
	    }
		if (me->query("quest/wudang/juehu"))
		{
			command("heng ");
			command("say 你不是已经解开绝户手了么？还来此跟我啰嗦什么？\n");
			return;
		}
        me->set("jh_time",time());
	    //me->set(QUEST_JH+"combat_exp",me->query("combat_exp")); 
		
		if (random(me->query("kar")) > 20)
	     { 
            command("haha");
		    command("pat "+me->query("id"));
		    message_vision(HIY"俞莲舟附耳在你的耳边悄声说了一番道理.....\n"NOR,me);
		    me->set("quest/wudang/juehu",1);
		    command("admire "+me->query("id"));
			return;
		 }	 
		 return "俞莲舟说道，‘看你面带晦气，我心情不好，改日再来吧！’\n";
		
}
int do_kill(string arg)
{
        object ob,me = this_player();

        if (!living(this_object())) return 0;
        if (!arg) return 0;
        if (!(ob = present(arg, environment()))) return 0;
        if (ob == me) return 0;
        if (ob->query("family/family_name") != "武当派") return 0;
        
        command("say 大胆狂徒，竟敢在武当放肆！！！");
        command("stare "+this_player()->query("id"));
        message_vision("俞莲舟哈哈大笑几声！\n", this_player());
        kill_ob(me);
        return 1;
}

void init()
{
        ::init();
        if (query("startroom") != base_name(environment())) return;
        add_action("do_kill", "kill");
        add_action("do_kill","hit");
}
