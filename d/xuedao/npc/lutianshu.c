// lutianshu.c

inherit NPC;
#include <ansi.h>
#include "lhlsnpc.h"
string ask_diyun();
#include "/d/suzhou/npc/lchj.h"
void create()
{
       set_name("½����", ({ "lu tianshu", "lu" }));
       set("long", 
       "�����������桰�仨��ˮ���е��ϴ�\n"
       "��������н��ϣ��������壬½�������������ƣ�����������\n");
       set("gender", "����");
       set("nickname", HIG"����½��"NOR);
       set("age", 51);
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

       set_skill("force", 480);
       set_skill("yijin-jing", 480);
       set_skill("dodge", 480);
       set_skill("shaolin-shenfa", 480);
       set_skill("taizu-quan", 480);
       set_skill("parry", 480);
       set_skill("blade", 480);
       set_skill("xiuluo-dao", 480);
       set_skill("literate", 220);

       map_skill("force", "yijin-jing");
       map_skill("dodge", "shaolin-shenfa");
	   map_skill("cuff", "taizu-quan");

       map_skill("parry", "xiuluo-dao");
       map_skill("blade", "xiuluo-dao");
	   prepare_skill("cuff","taizu-quan");

       set("chat_chance", 20);
       set("chat_msg", ({
              "½��������������������Х�����䡫������ˮ������Х���ۻ룬ԶԶȺɽ��Ӧ������\n",
	   }));
	   set("chat_chance_combat", 60);
		set("inquiry", ([
		"����" : (: ask_diyun :),
		"name": "���������Ҿ��������½���㣬����ʲô���飿",
		//"�仨��ˮ" : (: ask_lhls :),
		//"": (: ask_qiyu :),
	])); 
		set("chat_chance_combat", 70);

      set("chat_msg_combat", ({
			(: perform_action, "blade.xiuluo" :),
			(: exert_function, "jingang" :),
			(: perform_action, "cuff.hengsao" :),

		}));
       setup();
       carry_object("/clone/weapon/gangdao")->wield();
}

string ask_diyun()
{
	object me;
	me=this_player();
	if (me->query_temp(QUESTDIR3+"jingjieok")||me->query(QUESTDIR3+"jingjieok"))
	{	
		command("say ��˵�����Ǹ�ͺͷС�������������������أ��������Ҷ���˵������ȥ��������\n");
		command("say ������˵��С�Ӱ����İ��ĵ��Ӵ��ˣ������������ĵܵ�Ů�������ǿɶ�\n");
		me->set_temp(QUESTDIR3+"asklu",1);
		return "��С�ӿ�������������ģ�Ҳ����ʲô����\n";

	}
	command("say Ī���������������\n");
	return "�ߣ�\n";
}		
