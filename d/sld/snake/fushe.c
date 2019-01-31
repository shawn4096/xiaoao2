inherit NPC;
#include <ansi.h>

void create()
{
    set_name(HIG"����"NOR, ({ "fushe", "snake", "she" }) );
    set("race", "Ұ��");
    set("age", 20);
    set("long", "����һ���о綾�ĸ��ߣ������������ز������ڳ���Ϊ������\n");
    set("attitude", "peaceful");
	
	set("limbs", ({ "ͷ��", "����", "�ߴ�", "β��" }) );
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

      if(interactive(me) && (!myfam || myfam["family_name"] != "������" || !me->query("xionghuangjiu") ))
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
        message_vision("$Nž��һ���ϳ����أ�$N���ˡ�\n", this_object());
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

 