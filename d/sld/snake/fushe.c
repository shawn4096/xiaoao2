inherit NPC;
#include <ansi.h>

void create()
{
    set_name(HIG"腹蛇"NOR, ({ "fushe", "snake", "she" }) );
    set("race", "野兽");
    set("age", 20);
    set("long", "这是一条有剧毒的腹蛇，乃是神龙岛特产，岛内称其为神龙。\n");
    set("attitude", "peaceful");
	
	set("limbs", ({ "头部", "身体", "七寸", "尾巴" }) );
	set("verbs", ({ "twist", "bite" }) );

	set("combat_exp", 800000);
	
	set_temp("apply/attack", 110);
	set_temp("apply/defense", 110);
	set_temp("apply/damage", 110);
	set_temp("apply/armor", 110);

	setup();
}

void init()
{
      object me;
      object* inv;
      int i;
      mapping myfam;

      ::init();
      me=this_player();
      myfam = (mapping)me->query("family");
	 // if ((int)me->query("xionghuangjiu")) return;

      if(interactive(me) && (!myfam || myfam["family_name"] != "神龙教" || !me->query("xionghuangjiu") ))
      {
         //ob=this_object();
         inv = all_inventory(me);
	     for(i=0; i<sizeof(inv); i++)       
	        if(inv[i]->query("id")=="xiong huang") break;
      	   if(i>=sizeof(inv))      
           {
              remove_call_out("kill_ob");
              call_out("kill_ob", 1, me); 
	          //ob->kill_ob(me);
       	   //me->kill_ob(ob);
	      }
       }
}
void die()
{
        message_vision("$N啪的一声断成两截！$N死了。\n", this_object());
//        ob = new(__DIR__"obj/shedan");
        if (!random(3))
        	new(__DIR__"obj/fushedan")->move(environment(this_object()));
        destruct(this_object());
}


int hit_ob(object me, object victim, int damage)
{
        if (!random(3))
			victim->add_condition("fushe_poison", 1);
        return 0;
}

 