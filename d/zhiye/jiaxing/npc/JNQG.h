#define QUESTDIR "quest/���Ӣ�۴�/"
#define QUESTDIR1 "quest/���Ӣ�۴�/��ѩ����/"

#define QUESTDIR2 "quest/���Ӣ�۴�/�����߹�/"
#define QUESTDIR3 "quest/���Ӣ�۴�/��Į��ɳ/"

#define QUESTDIR4 "quest/���Ӣ�۴�/��������/"

//�趨�����߹ֵ��书�ȼ���Խ��Խǿ
inherit FIGHTER;

void init()
{
    object me, ob;  
    int i;    
    ::init();

    ob = this_object();
    if(!ob->query("kill_id")) return;
	  me=find_player(ob->query("kill_id"));  
   	if(!me) return;
	  if(environment(me)!=environment(ob)) return;
    //�������ɸ���npc ��һЩ״̬
	i=me->query("max_pot");
	
	if(i<350) i=350;
	  
	i=i-100;	
	ob->set_skills_level(i+random(20));
	  
		  if(ob->query("type_speical"))
			  ob->set("combat_exp",me->query("combat_exp"));
		  else 	ob->set("combat_exp",me->query("combat_exp")*2/3); 
		  
		  ob->set("max_neili",me->query("max_neili"));
		  ob->set("max_jingli",me->query("max_jingli"));
		  ob->set("max_qi",me->query("max_qi")*3/2);
		  ob->set("max_jing",me->query("max_jing"));
		  ob->set("neili",query("max_neili")*3/2);
		  ob->set("jingli",query("max_jingli")*3/2);
		  ob->set("eff_jingli",query("max_jingli")*3/2);
		  ob->set("qi",query("max_qi"));
		  ob->set("eff_qi",query("max_qi"));
		  ob->set("jing",query("max_jing")*3/2);
		  ob->set("eff_jing",query("max_jing")*3/2);
		  ob->set_skill("wuxing-zhen",250);
		
}
