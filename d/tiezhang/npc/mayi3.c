//mayi3.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
void create()
{
       set_name("黄令天", ({"huang lingtian","huang","lingtian"}));
       set("title","麻衣长老"); 
       set("nickname",HIY"铁掌四鹰"NOR);
       set("long",
    "他是一个年约六旬的老者，满头花发，两鬓斑白。\n"
    "他两侧的太阳穴高高鼓起，微闭的双目中时而闪过凌厉的眼神，似乎身怀绝技。\n"
       );

       set("gender", "男性");
       set("attitude", "peaceful");
       set("unique", 1);
       set("age", 60);
       set("shen_type", -10);
       set("str", 28);
       set("int", 23);
       set("con", 23);
       set("dex", 28);
       set("per", 20);
      set("max_qi", 8000);
		set("max_jing", 3000);
		set("neili", 8000);
		set("max_neili", 8000);
		set("jiali", 150);
		set("combat_exp", 1600000);
		set("score", 10000);

		set_skill("force", 250);
		set_skill("guiyuan-tunafa", 250);
		set_skill("dodge", 250);
		set_skill("literate", 100);
		set_skill("shuishangpiao", 250);
		set_skill("strike", 250);
		set_skill("tiezhang-zhangfa", 250);
		set_skill("parry", 250);
		set_skill("blade", 250);
		set_skill("liuye-daofa", 250);
		set_skill("tiezhang-xinfa",150);

       map_skill("force", "guiyuan-tunafa");
       map_skill("dodge", "shuishangpiao");
       map_skill("strike", "tiezhang-zhangfa");
       map_skill("parry", "liye-daofa");
       map_skill("blade", "liuye-daofa");
       prepare_skill("strike", "tiezhang-zhangfa");
		
	   create_family("铁掌帮", 15, "长老");
       setup();
       carry_object(__DIR__"obj/mayi")->wear();
       carry_object("clone/weapon/blade")->wield();       
}
void init()
{
       object me, ob;
       mapping fam;

       ::init();

       ob = this_player();
       me = this_object();
       
       if (interactive(ob) 
       && !environment(ob)->query("no_fight")
       && ( (fam = ob->query("family")) && fam["family_name"] != "铁掌帮" ) 
        && (int)ob->query("combat_exp", 1) >= 10000 ) 
       {
               if( !ob->query_temp("warned") ) {
        command("say 站住！你不是铁掌帮弟子，不能在此久留！！");
        command("say 你还是速速离开此地吧，不然老朽可要对你不客气了！！");
        command("hehe");
                       ob->set_temp("warned", 1);
               }
          else if( ob->query_temp("stay") < 3 ) ob->add_temp("stay", 1);
                else {
                       command("say 你活得不耐烦了，竟敢到铁掌帮来撒野！！！\n");
                       remove_call_out("hiting_ob");
                       call_out("hiting_ob", 1, ob);
               }
       }       

}
void attempt_apprentice(object ob)
{
      object me  = this_object();
      mapping fam = ob->query("family");

        if(!fam || fam["family_name"] != "铁掌帮"){
                command("say "+RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return;
                }
        if ((int)ob->query("shen") > -500000) {
                command("hehe");
                command("say 铁掌帮可不收心慈手软的人做弟子，少于500k负神别来烦我。\n");
                return;
                }
        if(fam["master_name"] == "裘千仞"){
                command("haha");
                command("say "+RANK_D->query_respect(ob)+"已是帮主亲传弟子，"+RANK_D->query_self(me)+"怎敢再收你为徒？");
                return;
                }
        if(fam["master_name"] == "上官剑南"){
                command("ah");
                command("say 上官帮主不是早已故世多年了嘛？");
                command("say "+RANK_D->query_respect(ob)+"原来是老帮主关门弟子啊，失敬。"+RANK_D->query_self(me)+"怎敢再收你为徒？");
                return;
                }
        if ((int)ob->query_skill("guiyuan-tunafa", 1) <= 150) {
                command("say 要学更为高深的武功，必须有高深的内功修为,150。");
                command("say " + RANK_D->query_respect(ob)+"是否还应该在归元吐纳法上多下点功夫？");
                return;
                }
                command("say 好吧，我就收下你了。希望你苦练铁掌帮神功，将之发扬光大。\n");
                command("recruit " + ob->query("id"));
                ob->set("is/tiezhang",1);
                ob->set("class","brigand");
}