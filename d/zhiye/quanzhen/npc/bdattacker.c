//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>
inherit FIGHTER;
#include "skill.h"
int clonenpc(object me);
void create()
{
  set_name("���̽��", ({ "jinbing tanzi", "jinbing", "bing", "tanzi" }));
	set("gender", "����");
	set("long", "���˾��Ǵ����ɵ���ԭ��̽�ӣ������������̽����ԭ��ʹ����\n");
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", -1);
	set("unique", 1);

	set_skill("force", 350);
	set_skill("dodge", 350);
	set_skill("parry", 350);
	set_skill("strike", 350);
	set_skill("cuff",350); 
	set_skill("taxue-wuhen",350);
	set_skill("zhentian-quan",350);
	set_skill("kunlun-zhang",350);
	set_skill("xuantian-wuji",350);
	
	map_skill("force","xuantian-wuji");
	map_skill("cuff","zhentian-quan");
	map_skill("strike","kunlun-zhang");
	map_skill("dodge","taxue-wuhen");
	map_skill("parry","zhentian-quan");
	
  prepare_skill("cuff", "zhentian-quan");
  prepare_skill("strike", "kunlun-zhang");
  
	set("combat_exp", 2000000);
	set("max_qi", 35000);
	set("max_jing", 3500);
	set("max_neili", 5000);
	set("eff_jingli",3500);
	set("qi",35000);
	set("jing",3500);
	set("jingli",3500);
	set("neili", 5000);

	setup();  
	if (!random(5))
	   add_money("gold", random(2)+1);
    carry_object("/clone/armor/junfu.c")->wear();

}
int clonenpc(object me)
{
    object ob;  
    int i;    
   

	//me=this_player();
	write("1111");
    ob = this_object();
	//���������Լ�id���ܴ���
    if(!me) return 0;
		write("221");

	if(environment(me)!=environment(ob)) return 0;
    	write("331");


	//if(ob->query_temp("target")!=me->query("id")) return;
	
	
   //	if (!me->query_temp("qzjob/jianxi")) return;
	

	i=me->query("max_pot");
	
	i=i-100;
	if(i<350) i=350;

	//write("1111\n");
	//�����书�����ɱ��
//	if(ob->query("type_speical"))
		//ob->set("party",ob->query("type_speical"));  
  //  else
	//	ob->set("party",str_menpai[random(sizeof(str_menpai))]);  	  
	//���������书
	
	//ob->copy_menpai(({ob->query("party")}),1,random(2),20+random(80));	//����npc�������书��				
	//ob->copy_state();				//�������ɸ���npc ��һЩ״̬
	
	//����npc
	//if (query_temp("qzjx/super"))
	//{
		//i=i+10+random(30);
	//}else i=i; //��ͨnpc
	
	//���������书�ȼ�
	set("long",query("long")+"�������"+me->query("name")+"Ҫ׷ɱ�Ľ��̽��!\n");
	
	//ob->set_skills_level(i);
	
	if(ob->query("type_speical"))
		ob->set("combat_exp",me->query("combat_exp"));
    else
		ob->set("combat_exp",me->query("combat_exp")*2/3); 
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

	ob->set_temp("setok",1);
		//remove_call_out("check");
	//	call_out("check",1, me);
	
	return 1;
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
		tell_object(ob, "�ⲻ����Ҫ׷ɱ�Ľ��̽�ӡ�\n");
		return;
	}
	tell_object(ob,query("name")+RED"�੹�Ц���ϣ�ȫ���ԭ�������������󷨣��Ǿ��������ɣ�\n"NOR);
	::kill_ob(ob);

}

