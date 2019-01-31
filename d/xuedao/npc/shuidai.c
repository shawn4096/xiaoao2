// shuidai.c

inherit NPC;
#include <ansi.h>;
#include "lhlsnpc.h"
#include "/d/suzhou/npc/lchj.h"
string ask_diyun();


void create()
{
       set_name("ˮ�", ({ "shui dai", "shui" }));
       set("long", 
       "�����������桰�仨��ˮ���е����ġ�\n"
       "��������н��ϣ��������壬ˮ��主�׶��ϣ�����ȴ������ɫ��\n");
       set("gender", "����");
       set("nickname", HIC"���½�"NOR);
       set("age", 39);
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
       set("jiali", 180);
       set("combat_exp", 9800000);
       set("shen_type", 1);
       set("huashan", "����");

       set_skill("force", 480);
       set_skill("huashan-qigong", 480);
       set_skill("dodge", 480);
       set_skill("huashan-shenfa", 480);
       set_skill("strike", 480);
       set_skill("hunyuan-zhang", 480);
       set_skill("parry", 480);
       set_skill("sword", 480);
       set_skill("huashan-jianfa", 480);
       set_skill("literate", 180);

       map_skill("force", "huashan-qigong");
       map_skill("dodge", "huashan-shenfa");
       map_skill("strike", "hunyuan-zhang");
       map_skill("parry", "huashan-jianfa");
       map_skill("sword", "huashan-jianfa");
       prepare_skill("strike", "hunyuan-zhang");
   
	   set("chat_chance", 20);
		set("inquiry", ([
		"����" : (: ask_diyun :),
		"name": "���������Ҿ������½�ˮᷣ�����ʲô���飿",
		//"�仨��ˮ" : (: ask_lhls :),
		//"": (: ask_qiyu :),
		])); 

       set("chat_msg", ({
              "ˮ᷼���������Х����磺���仨��ˮ�������������ƾ�����ԶԶ������\n",
	}));
	set("chat_chance_combat", 100);

        set("chat_msg_combat", ({
			(: perform_action, "sword.jianzhang" :),
			(: perform_action, "sword.fengyi" :),
			(: perform_action, "sword.lianhuan" :),
			(: perform_action, "sword.shijiushi" :),
			(: perform_action, "sword.luomu" :),
			(: perform_action, "sword.kuaijian" :),
			(: exert_function, "juli" :),
			(: exert_function, "yujianshi" :),

		}));
       setup();
       carry_object("/clone/weapon/changjian")->wield();
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
	if (!me->query_temp(QUESTDIR3+"askliu"))
	{

		command("say ��������׷ǹʣ�����Ī���������������\n");
		return "�ߣ�\n";
	}
	command("say ��Ȼ�����������������ҵģ��Ҿ͸���˵����С��!\n");

	command("say ��˵�����Ǹ�ͺͷС�������������������أ����������ĵ�˵������ȥ��������\n");
	command("say ������˵��С�Ӱ����İ��ĵ��Ӵ��ˣ��������ҵ�Ů��ˮ�ϣ����ǿɶ�\n");
	command("say ��ץס��һ�����������ң�������Ҳ����\n");
	command("say ��Ů���������������һ����������Ҳ��֪����Ů�������䣡\n");
	
	me->set_temp(QUESTDIR3+"askshui",1);
	return "�����Ƿ���������������Ů��һ��Ҫ֪ͨ�ң����²�ʤ�м���\n";
}