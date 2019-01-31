// ȫ����������
inherit FBROOM;
#include <ansi.h>

void create()
{

     set("short",HIG"������-����"NOR);
     set("long", @LONG
�˵�����ȫ��������ţ�һ��ߴ���Ʒ������ڰ�ɽ�Ŀ������ϣ�ȫ���
�����µ�ʿ�ڴ˷����������ʴ˴�����������ƣ�����������Ů���Ĺ����
�����ġ�
LONG        );

     set("outdoors","����");    
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
             return notify_fail("��������������ͨ·�ء�\n");	 

	message_vision(HIC"\n$N֪��һ����Ⱥ���������������ſ�ɧ��С��Ů������ͨ���Ĺ�ıؾ�֮·��\n"NOR,me);
	message_vision(HIC"\n\n$Nչ�����ƣ�׼��������·�ڡ�\n"NOR,me);	
	 
	 me->set_temp("qz/shouwei/guard",1);
	 
	 me->set_temp("apply/short", ({HIW"������Ĺ"NOR+" "+me->name()+"("+capitalize(me->query("id"))+")"}));
        
	 message_vision(YEL"��־ƽ��Զ���������ðɣ�"+me->name()+"������������ţ�����ȥ̽��һ����ʵ��\n"NOR,me);
     message_vision(YEL"��־ƽ˵������Щ��ͽ������������һ��ҪС�Ŀ�����\n"NOR,me);
        
		
     me->add_busy(1);      
	 message_vision(HIR"\n\nԶ������һ��Ų�������������,�����в��������ڸ�����\n"NOR,me);		
			
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
        //att->set_name(ob->query("name")+"������", ({ ob->query("id")+"'s attacker"}));
		att->set("long",att->query("long")+"\n���������"+ob->query("name")+"("+ob->query("id")+")"+"Ҫ׷ɱ��������\n");
		
		skills = att->query_skills();
       
		if (mapp(skills))
		{
             sk = keys(skills);
             for (i=0;i<sizeof(sk);i++)
             skills[sk[i]] = lv;
        }
        
		message_vision(HIR"\nֻ��Զ������һƬ�����Ŀ�Ц������˵��С��Ů�����µ�һ���ˣ���һ��Ҫ�ú����ơ���\n"
							+"һ��"+ob->query("name")+"��Ҫ׷�õ�"+att->name()+"�����Ƶ����˹�������$N�ڴ�������������$N�������ҵĹ�����\n\n"NOR,ob);
        
		
		att->move(this_object());		
		att->kill_ob(ob);
		ob->delete_temp("qz/shouwei/askyin");	
        return 1; 
}
