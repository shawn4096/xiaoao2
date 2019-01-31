// 全真守卫副本
inherit FBROOM;
#include <ansi.h>

void create()
{

     set("short",HIG"中天门-副本"NOR);
     set("long", @LONG
此地已是全真的中天门，一块高大的牌坊耸立于半山的开阔地上，全真教
的俗事道士于此发符传道，故此处已是香火缭绕，不少善男信女诚心供奉，修
道宁心。
LONG        );

     set("outdoors","副本");    
     set("backroom","/d/gumu/ztm");
	 set("quest",1);
	 set("no_sleep_room",1);
	 set("no_quit", 1);
   setup();
}
#include "fuben.h";

void init()
{
	object me = this_player();		
	
	
	add_action("do_leave","leavefb");
	add_action("do_shouwei","shouwei");	
	
	if (wizardp(me))	{
		     add_action("do_dismiss","dismiss");
	  }
	
    	
	remove_call_out("fuben_reset");
	call_out("fuben_reset", 100);
	
}


int do_dismiss()
{
	        set("over",1);
	        fuben_reset();
			return 1;
}

int do_shouwei()
{
	object me=this_player();    
	
	 if (me->query_temp("qz/shouwei/guard"))
             return notify_fail("你正在守卫这条通路呢。\n");	 

	message_vision(HIC"\n$N知道一会那群江湖无赖将来此门口骚扰小龙女，这是通向古墓的必经之路。\n"NOR,me);
	message_vision(HIC"\n\n$N展开架势，准备守卫此路口。\n"NOR,me);	
	 
	 me->set_temp("qz/shouwei/guard",1);
	 
	 me->set_temp("apply/short", ({HIW"守卫古墓"NOR+" "+me->name()+"("+capitalize(me->query("id"))+")"}));
        
	 message_vision(YEL"尹志平在远处喊道：好吧，"+me->name()+"，你在这儿守着，我先去探查一下虚实。\n"NOR,me);
     message_vision(YEL"尹志平说道：这些歹徒都是淫贼，你一定要小心看护。\n"NOR,me);
        
		
     me->add_busy(1);      
	 message_vision(HIR"\n\n远处传来一阵脚步声，甚是喧嚣,看来有不少人正在赶来。\n"NOR,me);		
			
	call_out("do_attack",15+random(10),me,1+random(3));	
	 
			return 1;
      
}


int do_attack(object ob,int count)
{
        mapping skills;
        string *sk;
        int exp,i,lv;
        object att;		
     
		if(!ob || !ob->query_temp("qz/shouwei/guard") || environment(ob) !=this_object())
        {
			set("over",1);
			fuben_reset();
			return 0;
		}
      
        exp = ob->query("combat_exp");
		
		switch (count)
		{
			case 1:
				lv = ob->query("max_pot") - 100;
				break;
			case 2:
				lv = ob->query("max_pot") - 90 - random(10);
				break;
			case 3:
				lv = ob->query("max_pot") - 80 - random(10);
				break;
			default:
				lv = ob->query("max_pot") - 80 - random(15);
				break;
		}
      
		att = new("/d/quanzhen/npc/attacker");
        
		att->set("qi",(int)ob->query("qi"));
        att->set("max_qi", (int)ob->query("max_qi") );
        att->set("eff_qi", (int)ob->query("max_qi") );
       
		att->set("jing",(int)ob->query("jing"));
        att->set("max_jing",(int)ob->query("max_jing"));
        att->set("eff_jing",(int)ob->query("max_jing"));
        
		att->set("neili",(int)ob->query("max_neili") );
        att->set("max_neili",(int)ob->query("max_neili") );
        
		att->set("jingli",(int)ob->query("jingli"));
        att->set("max_jingli",(int)ob->query("max_jingli") );
        att->set("eff_jingli",(int)ob->query("eff_jingli"));
        
		att->set("combat_exp", exp*count/2);
		
		att->set("target",ob->query("id"));
        //att->set_name(ob->query("name")+"的淫贼", ({ ob->query("id")+"'s attacker"}));
		att->set("long",att->query("long")+"\n这个淫贼是"+ob->query("name")+"("+ob->query("id")+")"+"要追杀的淫贼！\n");
		
		skills = att->query_skills();
       
		if (mapp(skills))
		{
             sk = keys(skills);
             for (i=0;i<sizeof(sk);i++)
             skills[sk[i]] = lv;
        }
        
		message_vision(HIR"\n只听远处传来一片淫荡的狂笑，“据说这小龙女乃天下第一美人，我一定要好好瞧瞧。”\n"
							+"一名"+ob->query("name")+"所要追拿的"+att->name()+"晃悠悠的走了过来，见$N在此守卫，立即对$N发起猛烈的攻击！\n\n"NOR,ob);
        
		
		att->move(this_object());		
		att->kill_ob(ob);
		ob->delete_temp("qz/shouwei/askyin");	
        return 1; 
}
