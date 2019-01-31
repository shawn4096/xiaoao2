// liuchengfeng.c

inherit NPC;
#include <ansi.h>;
#include "lhlsnpc.h"

#include "/d/suzhou/npc/lchj.h"
string ask_diyun();

void create()
{
       set_name("���з�", ({ "liu chengfeng", "liu" }));
       set("long", 
       "�����������桰�仨��ˮ���е�������\n"
       "��������н��ϣ��������壬���з�һ��̫����������������ϱ���\n");
       set("gender", "����");
       set("nickname", HIY"���ƽ�"NOR);
       set("age", 41);
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
       set("combat_exp", 9800000);
       set("shen_type", 1);

       set_skill("force", 450);
       set_skill("yinyun-ziqi", 450);
       set_skill("dodge", 450);
       set_skill("tiyunzong", 450);
       set_skill("cuff", 450);
       set_skill("taiji-quan", 450);
       set_skill("parry", 450);
       set_skill("sword", 450);
       set_skill("taiji-jian", 450);
       set_skill("literate", 170);

       map_skill("force", "yinyun-ziqi");
       map_skill("dodge", "tiyunzong");
       map_skill("cuff", "taiji-quan");
       map_skill("parry", "taiji-jian");
       map_skill("sword", "taiji-jian");
	   prepare_skill("cuff", "taiji-quan");
		set("inquiry", ([
		"����" : (: ask_diyun :),
		"name": "���������Ҿ������ƽ����з磬����ʲô���飿",
		//"�仨��ˮ" : (: ask_lhls :),
		//"": (: ask_qiyu :),
		])); 

       set("chat_chance", 70);
       set("chat_msg", ({
              "���˷��Ȼ������Х�����仨������ˮ�������������棬ԶԶ���˳�ȥ��\n",
	}));
		set("chat_chance_combat", 70);

      set("chat_msg_combat", ({
			(: perform_action, "sword.chan" :),
			(: perform_action, "sword.lian" :),
			(: perform_action, "sword.sanhuan" :),
			(: perform_action, "sword.raozhi" :),
			
			(: perform_action, "cuff.dongjing" :),
			(: perform_action, "cuff.luanhuan" :),

		}));
       setup();
       carry_object("/clone/weapon/mujian")->wield();
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
	if (!me->query_temp(QUESTDIR3+"askhua"))
	{
		command("say ��������׷ǹʣ�����Ī���������������\n");
		return "�ߣ�\n";
	}
	command("say ��˵�����Ǹ�ͺͷС�������������������أ����������ĵ�˵������ȥ��������\n");
	command("say ������˵��С�Ӱ����İ��ĵ��Ӵ��ˣ������������ĵܵ�Ů�������ǿɶ�\n");
	me->set_temp(QUESTDIR3+"askliu",1);
	return "��С�ӿ�������������ģ�Ҳ����ʲô����\n";
}
