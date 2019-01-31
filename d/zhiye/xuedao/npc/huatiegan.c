// huatiegan.c

inherit NPC;
#include <ansi.h>
#include "lhlsnpc.h"
#include "/d/suzhou/npc/lchj.h"
string ask_diyun();

void create()
{
       set_name("������", ({ "hua tiegan", "hua" }));
       set("long", 
       "�����������桰�仨��ˮ���е��϶���\n"
       "��������н��ϣ��������壬������һ����ƽǹ���ų���ƽ�޵С���������Ϊ��ȴ��զ�ġ�\n");
       set("gender", "����");
       set("nickname", HIR"��ƽ�޵�"NOR);
       set("age", 45);
       set("attitude", "peaceful");
       set("shen_type", 0);
       set("str", 35);
       set("int", 38);
       set("con", 35);
       set("dex", 35);

       set("max_qi", 12000);
       set("max_jing", 5000);
       set("neili", 12000);
       set("max_neili", 12000);
       set("jiali", 130);
       set("combat_exp", 9700000);
       set("shen_type", 0);

       set_skill("force", 450);
       set_skill("huntian-qigong", 450);
       set_skill("dodge", 450);
       set_skill("xiaoyaoyou", 450);
       set_skill("hand", 450);
       set_skill("suohou-shou", 100);
       set_skill("parry", 450);
       set_skill("spear", 450);
       set_skill("zhong-qiang", 450);
       set_skill("literate", 140);
      
       map_skill("force", "huntian-qigong");
       map_skill("dodge", "xiaoyaoyou");
       map_skill("hand", "suohou-shou");
       map_skill("spear", "zhong-qiang");
       map_skill("parry", "zhong-qiang");
       prepare_skill("hand", "suohou-shou");

       set("chat_chance", 20);
       set("chat_msg", ({
              "�����ɻ�������������Х���糱ӿ�������仨������ˮ���������˶�����\n",
       }));
		set("inquiry", ([
		"����" : (: ask_diyun :),
		"name": "���������Ҿ�����ƽǹ�����ɣ�����ʲô���飿",
		//"�仨��ˮ" : (: ask_lhls :),
		//"": (: ask_qiyu :),
		])); 

	   set("chat_chance_combat", 70);
       set("chat_msg_combat", ({
			(: perform_action, "spear.huimaqiang" :),
			(: perform_action, "spear.fanzhuan" :),
			(: exert_function, "huntian" :),
			(: perform_action, "hand.suohou" :),
			(: perform_action, "hand.qinna" :),

		}));
       setup();
       carry_object("/clone/weapon/changqiang")->wield();
}


void die()
{
	object me,ob;
	object lastob = query_temp("last_damage_from");
	
	//�����ж�ɱ���Լ����ǲ����Լ���������
	me = this_object();	
	if (me->query_temp("target")) 
		ob = find_player(me->query_temp("target"));
	else destruct(me);
	
	if (!ob) {
		//command("say Ī�������ȥҲ��");	
		//write(me), "\n"+me->query("name")+"��һ����������ת��������Ͳ����ˡ�\n");	
		destruct(me);
		return;
	}
	if (ob!=lastob) 
	{
      command("say ������Թ�޳𣬺ο�׷ɱ���ҡ�");	
	  return;//����
     }
	
	::die();
}



string ask_diyun()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"asklu"))
	{
		command("say ��������׷ǹʣ�����Ī���������������\n");
		return "�ߣ�\n";
	}
	command("say ��˵�����Ǹ�ͺͷС�������������������أ�������������˵������ȥ��������\n");
	command("say ������˵��С�Ӱ����İ��ĵ��Ӵ��ˣ������������ĵܵ�Ů�������ǿɶ�\n");
	me->set_temp(QUESTDIR3+"askhua",1);
	return "��С�ӿ�������������ģ�Ҳ����ʲô����\n";
}
