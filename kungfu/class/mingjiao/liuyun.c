// liuyun.c 流云使
// Modify By River@sj 99.06
#include <ansi.h>
inherit NPC;
int p();
void create()
{
        object ob;
        set_name("流云使", ({ "liuyun shi", "shi", "liuyun"}) );
        set("title", "明教波斯三使");
        set("gender", "男性");
        set("attitude", "friendly");
        set("age",49);
        set("long", "他身材高大，虬髯碧眼。\n");
        set("rank_info/respect","使者");
        set("str", 30);
        set("int", 22);
        set("con", 25);
        set("dex", 26);
        set("per", 20);
        set("unique", 1);
        set("shen_type",0);
        set("combat_exp", 4800000);
        set_skill("dagger",350);
        set_skill("force",350);
        set_skill("parry",350);
        set_skill("cuff",350);
        set_skill("literate",100);
        set_skill("dodge",350);
        set_skill("piaoyi-shenfa",350);
        set_skill("shenghuo-shengong",350);
        set_skill("shenghuo-lingfa",350);
        map_skill("force","shenghuo-shengong");
        map_skill("dodge","piaoyi-shenfa");
        map_skill("dagger","shenghuo-lingfa");
        map_skill("cuff","shenghuo-lingfa");
        map_skill("parry","shenghuo-lingfa");
        prepare_skill("cuff","shenghuo-lingfa");
        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({ (: p :) }));
        set("max_qi",16000);
        set("max_jing",4800);
        set("neili",9000);
        set("max_neili",9000);
        set("jiali",200);
        set("eff_jingli",4800);     
        setup();
        if (clonep()) {
                ob = unew(BINGQI_D("shenghuo-ling"));
                if (!ob) ob = unew(BINGQI_D("tieling"));
                ob->move(this_object());
                ob->wield();        
                carry_object(ARMOR_D("changpao"))->wear();
        }     
}

void kill_ob(object me)
{     
        object ob;
        if(!this_object()->is_killing(me->query("id"))){  
          command("grin");     
          ::kill_ob(me);
          if(objectp(ob = present("miaofeng shi", environment(this_object())))
           && !ob->is_killing(me->query("id"))){
             message_vision(HIY"长笑声中$n身形晃动，越过流云使站到$N左边，将$N夹在中间！\n", me, ob);
             if(!ob->is_killing(me->query("id"))) ob->kill_ob(me); 
          }
          if(objectp(ob = present("huiyue shi", environment(this_object())))
           && !ob->is_killing(me->query("id"))){
             message_vision(HIY"长笑声中$n身形晃动，越过流云使站到$N左边，将$N夹在中间！\n", me, ob);
             if(!ob->is_killing(me->query("id"))) ob->kill_ob(me);  
          }  
        }
        ::kill_ob(me);
}

int p()
{          
        if(this_object()->query_temp("yinfeng")){
           command("yun shenghuo");
		   command("yun yinfeng");
		   command("perform dagger.ji");
		   command("perform dagger.duo");
		   command("perform dagger.tisha");
           return 1;
        }
        else if(random(5) >=2){
           command("yun tougu");
		   command("yun shenghuo");
		   command("yun yinfeng");
		   command("perform dagger.ji");
		   command("perform dagger.duo");
		   command("perform dagger.tisha");
           return 1;
        }
        else return 1;
}

void init()
{
        object ob;
        ::init();        
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        mapping myfam;
        myfam = (mapping)ob->query("family");
        if(myfam && myfam["family_name"] == "明教")
           command("say 见圣火令如教主亲临，"+ob->name()+"你还不下跪？");         
}
