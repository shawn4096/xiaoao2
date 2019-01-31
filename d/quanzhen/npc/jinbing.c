//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>
inherit FIGHTER;
#include "skill.h"
void copy_name(object ob);
void create()
{
  set_name("���", ({ "jin bing", "bing" }));
	set("gender", "����");
	set("long", "���˾������պ����ɵ���ԭ�ĺ��»�������������������ʹ����\n");
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", -1);
	set("unique", 1);

	set_skill("force", 300);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("strike", 300);
	set_skill("cuff",300); 
	set_skill("taxue-wuhen",300);
	set_skill("zhentian-quan",300);
	set_skill("kunlun-zhang",300);
	set_skill("xuantian-wuji",300);
	
	map_skill("force","xuantian-wuji");
	map_skill("cuff","zhentian-quan");
	map_skill("strike","kunlun-zhang");
	map_skill("dodge","taxue-wuhen");
	map_skill("parry","zhentian-quan");
	
  prepare_skill("cuff", "zhentian-quan");
  prepare_skill("strike", "kunlun-zhang");
  
	set("combat_exp", 2000000);
	set("max_qi", 30000);
	set("max_jing", 3000);
	set("max_neili", 5000);
	set("eff_jingli",3000);
	set("qi",30000);
	set("jing",3000);
	set("jingli",3000);
	set("neili", 5000);

	setup();  
	if (!random(3))
	   add_money("gold", random(2)+1);
    carry_object("/clone/armor/junfu.c")->wear();

}
void init()
{
    object me, ob,ling;  
    int i;    
    ::init();

	me=this_player();
    ob = this_object();
	//���������Լ�id���ܴ���
    if(!me) return;
	
	if(environment(me)!=environment(ob)) return;
    

	if(ob->query_temp("target")!=me->query("id")) return;
	
	
   	if (!me->query_temp("qzjob/jianxi")) return;
	

	i=me->query("max_pot");
	if(i<350) i=350;
	
	i=i-100;	
	
	//�����书�����ɱ��
	if(ob->query("type_speical"))
		ob->set("party",ob->query("type_speical"));  
    else
		ob->set("party",str_menpai[random(sizeof(str_menpai))]);  	  
	//���������书
	ob->copy_menpai(({ob->query("party")}),1,random(2),20+random(80));	//����npc�������书��				
	ob->copy_state();				//�������ɸ���npc ��һЩ״̬
	
	//����npc
	if (query_temp("qzjx/super"))
	{
		i=i+10+random(30);
	}else i=i; //��ͨnpc
	
	//���������书�ȼ�
	set("long",query("long")+"�������"+me->query("name")+"Ҫ׷ɱ�Ľ����ϸ!\n");
	
	ob->set_skills_level(i);
	
	if(ob->query("type_speical"))
		ob->set("combat_exp",me->query("combat_exp")*5/4);
    else
		ob->set("combat_exp",me->query("combat_exp")); 
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
	//ob->set_skill("wuxing-zhen",290);
	//�Զ�������applycondition���
	
	//�ж�
	if (interactive(me)
		&& objectp(ling=present("chongyang ling",me))
		&& ling->query("owner")==me->query("id")
		&& me->query_temp("qzjob/jianxi")
		&& ob->query_temp("target")==me->query("id"))
	{
		//copy_name(me);
		message_vision(YEL"$n��Ȼһ�ѽ�$N���ϵ�"+ling->query("name")+YEL"͵�ߣ�Ȼ���������֣�ԭ��������Ҫ׷ɱ�Ľ����϶��\n"NOR,me,ob);
		copy_name(ob);
		
		ling->move(ob);
		ling->set_temp("target",ob->query("id"));
		
		ob->set_temp("setok",1);
		remove_call_out("check");
		call_out("check",2, me);

	}
}

void check(object ob)
{

	if (!query_temp("setok")) return;

	if (ob->query("id") != query_temp("target")) 
	{
		ob->remove_enemy(this_object());
		ob->remove_killer(this_object());
		this_object()->remove_enemy(ob );
		this_object()->remove_killer(ob );
		tell_object(ob, "�ⲻ����־ƽ����׷ɱ�ļ�ϸ��\n");
		return;
	}
	tell_object(ob,query("name")+RED"�੹�Ц���ϣ���Ȼ�����ˣ��Ǿ��������ɣ�\n"NOR);
	::kill_ob(ob);

}



//�������
void die()
{
	object me,ob,ling;
	ob=this_object();
	

	me = ob->query_temp("last_damage_from");
	
	if(objectp(present(me,environment(ob))))
	{
	  	me->set_temp("qzjob/killover",1);
		
		if (objectp(ling=present("chongyang ling",ob)))
		{
			ling->set_temp("killer",me->query("id"));
			ling->set("long",ling->query("long")+"\n��ɹ�ɱ���˽����ϸ:"+ob->query("name"));
			if (ob->query_temp("qzjx/super"))
				ling->set_temp("super",1);
		}
	}

	::die();
}
//�����һ������
void copy_name(object ob)
{
	mapping name;
	int i;

	i = random(3)+ 1;

	name = RNAME_D->get_random_name(i);

	if (!ob) return;
		
	set_name(name["name"], name["id"]);		
    //����npc����ʾ����
	if ( ob->query_temp("qzjob/superjx"))
	{		
		message_vision(CYN"\n$N�����������֣����һ�������������������в����գ�"+name["name"]+"��Ҳ��\n"NOR, this_object());
	}

}	