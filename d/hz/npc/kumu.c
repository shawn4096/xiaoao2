// kumu.c ��ľ
// Created by sohu@xojh

inherit NPC;
#include <ansi.h>
string ask_duan();

void create()
{
   set_name("��ľ��ʦ",({"kumu dashi","kumu","dashi"}));
   set("gender","����");
   set("long","���������֣���ľ��ʦ�����ô˴�ü��Ŀ�����ǰ���!\n");
   set("shen",80000);
   set("combat_exp",4500000);
   //set("nickname","����������");
   set("title","����������");
   
   set("age",30);
   set("pur",12);
   set("kar",20);
   set("per",25);
   set("str",30);
	 set("int",25);
	 set("con",20);
	 set("dex",30);
	 set("max_qi", 13000);
	 set("max_jing", 5000);
	 set("eff_jingli", 5000);
	 set("neili", 15000);
	 set("max_neili", 15000);
	 set("jiali", 100);

   set_skill("dodge",400);
   set_skill("force",400);
   set_skill("parry",400);
   set_skill("sword",400);
   set_skill("cuff",400);
   //set_skill("stealing",380);
   set_skill("luohan-quan",400);
   set_skill("literate",200);
   set_skill("shaolin-shenfa",350);
   map_skill("dodge","shaolin-shenfa");
   map_skill("cuff","luohan-quan");
	prepare_skill("cuff","luohan-quan");
   setup();
       set("inquiry", ([
                //"ȫ���" :  "��ȫ��������µ�����������,�����������������ú����������������ʰ�㣡\n",			      
                "�����" : (: ask_duan :),
			  //  "��Ƽ" : (: ask_liping :),
               //	"���й���" : (: ask_gongji :),
                 
        ]) );
   add_money("silver",70);
	carry_object("d/jiaxing/obj/cloth")->wear();
	carry_object("d/menggu/npc/obj/zheshan");
}


string ask_duan()
{
	object me,kumu;
	me=this_player();
	if (!me->query_temp("quest/���Ӣ�۴�/�����߹�/findkumu"))
	{
		command("say �����ӷ��������գ�\n");

		return "�α���˴󶯸λ��������գ�\n";
	}
	if (me->query_temp("quest/���Ӣ�۴�/�����߹�/askkumu"))
	{
		command("say �����ӷ��������գ�\n");

		return "�Ҳ��Ǹ���˵����ô���������룿\n";
	}
	message_vision(HIG"\n$N��������Լ������Ů����������ȷ��������ľ����һζ�ĵ������ϣ�Ҳ��ŭ������!\n"NOR,me);
	message_vision(HIW"\n����Ѱ����Ҳû�����κο���֮����\n"NOR,me);
	message_vision(HIG"\n��ʱ������Լ���⴫��Ů����ŭ������������������\n"NOR,me);
	message_vision(HIY"\n�㼱æ׷�˳�ȥ����Զ��һ��������˷��򼲳۶�ȥ���漴չ���Ṧ׷Ѱ��ȥ��\n"NOR,me);
	
	me->set_temp("quest/���Ӣ�۴�/�����߹�/askkumu",1);
	return "\n����������������\n";
}
