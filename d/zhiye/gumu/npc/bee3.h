// bee3.h
// By River 98.08.29
// by sohu@xojh
#include <ansi.h>
void init()
{
	object me,*ob,name1;
	int i;
	//ob = this_player();
	me = this_object();
	ob = all_inventory(environment(me));
    for(i=0; i<sizeof(ob); i++) 
	{
       if( !living(ob[i]) || ob[i]==me ) continue;
       if( !ob[i]->query_temp("ynxj/fengmi") ) continue;
                                
	   //damage = (me->query("neili")-ob[i]->query("neili"))*skill/10;
       //ob[i]->add_busy(1+random(2));
			
       tell_object(ob[i],HIR "�������ǰһ���������죬��ʱΪһȺ�������Χ��\n"NOR);
       write(HIR "һȺ�۷��������죬������ȥ��"+ob[i]->query("name")+HIR"��Χ������\n"NOR);                  
       
		me->set_temp("apply/attack",  random(30));
		me->set_temp("apply/dodge",  random(30)); 
		if (!me->query_temp("skillset1")){
				ob[i]->start_busy(1);
				remove_call_out("dest");
				call_out("dest",100);
				me->set_leader(ob[i]);
				remove_call_out("do_clone");
				call_out("do_clone", 0, me, ob[i]);
		}
		else {
				ob[i]->start_busy(1);
				me->set_leader(ob[i]);
				remove_call_out("dest");
				call_out("dest",100);
				remove_call_out("kill_ob");
				call_out("kill_ob", 0, ob[i]); 
		}
		
	}
	::init();
	
}       

int do_clone(object me, object ob)
{
	int k_qi,k_jing;
	if (!ob) return 0;
	k_qi = (int)ob->query("max_qi");
	k_jing = (int)ob->query("max_jing");
        //k_qi*3/5
	me->set("max_qi",100);
	me->set("eff_qi",100);
	me->set("qi",100);
	me->set("max_jingli",100);
	me->set("eff_jingli",100);
	me->set("jingli",100);
	me->set("max_jing",100);
	me->set("eff_jing",100);
	me->set("jing",100);
	///me->set_name(HIC"���"NOR, ({ ob->query("id")+"'s bee","yu feng", "bee","feng" }) );

	me->set_temp("skillset1",1);   
	me->set_leader(ob);
	remove_call_out("kill_ob");
	call_out("kill_ob", 0, ob); 
	return 1;
}

void dest()
{
	object me;
	me = this_object();
	write("\n"+me->query("name")+"���ĳ��ת������ˡ�\n",me);
	destruct(this_object());
}
