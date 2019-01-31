// ssdizi.c  ��ɽ����

#include <ansi.h>
inherit NPC;
//int do_kick(string arg);
string *first_name = ({ "��","Ǯ","��","��","��","��","֣","��","��","��", "��","��",
"��","��","��","��","��","��","��","��","��","��","��","��","ʩ","��"});
string *first_name_id = ({ "zhao","qian","sun","li","zhou","wu","zheng","wang","zhang","chen", "liu","lin",
"feng","wei","jiang","shen","han","yang","zhu","qin","you","xu","he","lv","shi","yu" });
string *name_words = ({ "˳","��","��","��","��","��","��","־","��", "Т","��","��","��","��",
"��","��","ʢ","ʤ","��","��","��","ͬ","��", "��","��","��","¡","��","��","��","��","��","��",
"��","��","��","��","��","��","��" });
string *name_words_id = ({ "shun","chang","zhen","fa","cai","jun","liang","zhi","zhong", "xiao","xiong","yi","tian","jin",
"hui","chang","sheng","sheng","jin","an","fu","tong","man", "fu","wang","long","long","xiang","dong","guo","yi","shou","yang",
"teng","yin","luo","hua","an","chang","jue" });

void create()
{
	string name , name_word;
	int i, j, k;

       i = random(sizeof(first_name));
       name = first_name[i];

       j = random(sizeof(name_words));
       name += name_words[j];
       name_word = name_words_id[j];

       if( random(10) > 5 ){
       	       k = random(sizeof(name_words));
               name += name_words[k];
               name_word = name_word + name_words_id[k];
       }

       set_name(name, ({ first_name_id[i]+" "+name_word, first_name_id[i], name_word }) );
       
	   i = random(3)+1;

       set("gender", "����" );
       set("shen_type", 1);
       set("age", 25);
       set("per", 12+random(15));
       set("str", 25);
       set("con", 15);
       set("int", 20);
       set("dex", 20);
       set("combat_exp", 10000*i);
       set("attitude", "peaceful");
       set("max_qi", 500);
       set("max_jing", 300);
       set("eff_jingli", 500);


       set_skill("force", 20*i);
       set_skill("huashan-qigong", 20*i);
       set_skill("dodge", 20*i);
       set_skill("huashan-shenfa", 20*i);
       set_skill("strike", 20*i);
       set_skill("hunyuan-zhang", 20*i);
       set_skill("parry", 20*i);
	   set_skill("poyu-quan", 20*i);
       set_skill("cuff", 20*i);

       set_skill("sword", 20*i);
       set_skill("huashan-jianfa", 20*i);
       set_skill("literate", 200);
       map_skill("force", "huashan-qigong");
       map_skill("dodge", "huashan-shenfa");
       map_skill("strike", "hunyuan-zhang");
       map_skill("parry", "huashan-jianfa");
       map_skill("sword", "huashan-jianfa");
       prepare_skill("strike", "hunyuan-zhang");
       create_family("��ɽ��", 5, "����");
       setup();
       carry_object(BINGQI_D("changjian"))->wield();
       carry_object(ARMOR_D("changpao1"))->wear();
}
int do_copy(object ob,int i)
{
	int skill,j;
	object me=this_object();
	skill=ob->query("max_pot")-100;
	if (i==1)
	{
		skill=skill+random(10);
		j=i+0.1;
	}
	if (i==2) 
	{
		skill=skill+20+random(10);
		j=i+0.2;
	}
	if (i==3) {
		skill=skill+40+random(10);
		j=i+0.4;
	}
	if (random(2))
		me->set("huashan","����");
	else me->set("huashan","����");

	me->set("jiali",100);

	me->set("combat_exp",ob->query("combat_exp")*j);
	me->set("max_jingli",ob->query("max_jingli")*j);
	me->set("jingli",ob->query("max_jingli")*j);

	me->set("max_neili",ob->query("max_neili")*j);
	me->set("neili",ob->query("max_neili")*j);

	me->set("max_qi",ob->query("max_qi")*j);
	me->set("max_jing",ob->query("max_jing")*j);
	me->set("eff_jing",ob->query("max_jing")*j);
	me->set("eff_jingli",ob->query("max_jing")*j);
	me->set("eff_qi",ob->query("max_qi")*j);
	       set_skill("force", skill);
       set_skill("huashan-qigong", skill);
       set_skill("dodge", skill);
       set_skill("huashan-shenfa", skill);
       set_skill("strike", skill);
       set_skill("hunyuan-zhang", skill);
       set_skill("parry", skill);
	   set_skill("poyu-quan", skill);
       set_skill("cuff", skill);

       set_skill("sword", skill);
       set_skill("huashan-jianfa", skill);
       set_skill("literate", 200);
       map_skill("force", "huashan-qigong");
       map_skill("dodge", "huashan-shenfa");
       map_skill("strike", "hunyuan-zhang");
       map_skill("parry", "huashan-jianfa");
       map_skill("sword", "huashan-jianfa");
       prepare_skill("strike", "hunyuan-zhang");

	   me->set("chat_chance_combat", 40);
	   me->set("chat_msg_combat", ({
               			(: perform_action, "sword.shijiushi" :),
						(: perform_action, "sword.fengyi" :),
						(: perform_action, "sword.jianzhang" :),
						(: perform_action, "sword.lianhuan" :),
						(: perform_action, "sword.cangsong" :),
						(: perform_action, "sword.luomu" :),
						(: exert_function, "juli" :),
						(: exert_function, "yujianshi" :),

              		}) );
}
void init()
{
	//object ob;
	::init();
	add_action("do_kick","kick");   

}

int do_kick(string arg)
{
	object me,ob;
	me=this_player();
	
	if (!arg||!objectp(ob=present(arg,environment(me))))
	{
		write("����ſ�������һ�ţ�\n");
		return 1;
	}
	message_vision(HIY"$N����$n��ƨ��һ�����˹�ȥ�������������ʦ��һ������α���ӡ���\n"NOR,me,ob);
	if (environment(ob)->query("no_fight"))
	{
		ob->random_move();

	}
	return  1;
}