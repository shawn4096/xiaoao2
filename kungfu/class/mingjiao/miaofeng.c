// miaofeng.c 妙风使
// Modify By River@sj 99.06
#include <ansi.h>
inherit NPC;
int p();
void create()
{
        object ob;
        set_name("妙风使", ({ "miaofeng shi", "miaofeng", "shi"}) );
        set("title", "明教波斯三使");
        set("gender", "男性");
        set("attitude", "friendly");
        set("age",49);
        set("long", "他身材高大，黄须鹰鼻。\n");
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
        set("chat_chance_combat", 35);
        set("chat_msg_combat", ({ (: p :) }));
        set("max_qi",16000);
        set("max_jing",4800);
        set("neili",12000);
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
          command("hehe");     
          ::kill_ob(me);
          if(objectp(ob = present("liuyun shi", environment(this_object())))
            && !ob->is_killing(me->query("id"))){
             message_vision(HIY"长笑声中$n身形晃动，越过妙风使站到$N左边，将$N夹在中间！\n", me, ob);
             if(!ob->is_killing(me->query("id"))) ob->kill_ob(me); 
          }
          if(objectp(ob = present("huiyue shi", environment(this_object())))
            && !ob->is_killing(me->query("id"))){
             message_vision(HIY"长笑声中$n身形晃动，越过妙风使站到$N左边，将$N夹在中间！\n", me, ob);
             if(!ob->is_killing(me->query("id"))) ob->kill_ob(me);  
          }  
       }
       ::kill_ob(me);
}

int p()
{          
      object ob;
      if(random(3) == 2 && objectp(ob = present("liuyun shi", environment(this_object())))){
         command("yun chuangong liuyun shi");
		    command("yun shenghuo");
		   command("yun yinfeng");
		   command("perform dagger.ji");
		   command("perform dagger.duo");
		   command("perform dagger.tisha");
         return 1;
      }
      else{
		     command("yun shenghuo");
		   command("yun yinfeng");
		   command("perform dagger.ji");
		   command("perform dagger.duo");
		   command("perform dagger.tisha");
         command("yun tougu");
         return 1;
      }
}
