// wangxiaofeng.c

inherit NPC;
#include <ansi.h>;
#include "/d/suzhou/npc/lchj.h"
string ask_diyun();
string ask_shuisheng();
string ask_qiangjie();
int shui_go(object me,object shui);

void create()
{
       set_name("��Х��", ({ "wang xiaofeng", "wang", }));
       set("long", 
       "��ʮ���£�Ӣ�����£�һ��������޳����Σ���һƥ��ͷ���������Ϊ���ɫë���Ŀ���\n");
       set("gender", "����");
       set("nickname", HIW"�彣˫��"NOR);
       set("age", 20);
       set("attitude", "peaceful");
       set("shen_type", 0);
       set("str", 30);
       set("int", 30);
       set("con", 30);
       set("dex", 30);
       set("per", 35);

       set("max_qi", 12000);
       set("max_jing", 4500);
       set("neili", 12000);
       set("max_neili", 12000);
       set("jiali", 150);
       set("combat_exp", 6500000);
       set("shen_type", 1);

       set_skill("force", 400);
       set_skill("huashan-qigong", 400);
       set_skill("dodge", 400);
       set_skill("huashan-shenfa", 400);
       set_skill("strike", 400);
       set_skill("hunyuan-zhang", 400);
       set_skill("parry", 400);
       set_skill("sword", 400);
       set_skill("huashan-jianfa", 400);
       set_skill("literate", 400);

       map_skill("force", "huashan-qigong");
       map_skill("dodge", "huashan-shenfa");
       map_skill("strike", "hunyuan-zhang");
       map_skill("parry", "huashan-jianfa");
       map_skill("sword", "huashan-jianfa");
	   prepare_skill("strike","hunyuan-zhang");
       set("inquiry", ([
              "�仨��ˮ": "�㲻�᲻֪�����������Ĵ�Űɣ����½�ˮ᷾�����Ů���ѵĸ��ס�",
              "Ѫ����ɮ": "����һ��Գ�Ѫ�����棬��ʵ�޶������ҿ�����һ��һ����������",
			"����" : (: ask_diyun :),
			"ʦ��" : (: ask_shuisheng :),
			"����" : (: ask_qiangjie :),


       ]));
		set("chat_chance_combat", 50);

        set("chat_msg_combat", ({
			(: perform_action, "sword.jianzhang" :),
			(: perform_action, "sword.fengyi" :),
			(: perform_action, "sword.lianhuan" :),
			(: exert_function, "juli" :),
			(: exert_function, "yujianshi" :),

		}));

       setup();
       carry_object("/clone/weapon/changjian")->wield();
}

int init()
{
	object shui;
	object me=this_player();
	if (me->query_temp(QUESTDIR3+"askshui"))
	{
		message_vision(HIC"$NԶԶ��ȥ����ǰ���ƺ���һ��������Ů���ڳ��ܣ���Ů��һŭ֮�£��ƺ������ȥ!\n"NOR,me);
		message_vision(HIM"�����е�ȴ�ƺ���ԥ����������$N������˴�������Ҳװ���������µ�����!\n"NOR,me);
		if (!objectp(shui=present("shui sheng",this_object())))
		{
			shui=new("d/xuedao/npc/shuisheng");
			shui->move(environment(me));
		}
		call_out("shui_go",2+random(3),me,shui);

		me->set_temp(QUESTDIR3+"findstory",1);
		me->delete_temp(QUESTDIR3+"askshui");
	}

}
int shui_go(object me,object shui)
{
	
	if (!me) return 0;
	message_vision(YEL"һλ��ɫ���Ժ�ɫ�Ŀ���С�����ƺ�ŭ���������ӣ���$N���������Ͽ񱼶�ȥ.......��\n"NOR,me);
	if (objectp(shui=present("shui sheng",environment(me))))
	{
		destruct(shui);
	}

	return 1;
}

void hunting()
{
   object ob=this_object();
   if (this_player()->query_temp(QUESTDIR3+"wangyouyu"))
    {
      message("vision", HIW"ʦ�ã��ȵ��ң�����ֻ���ö����ᣬ������һ��������һ������Զ�������ˡ�\n"NOR, this_player());
	  this_player()->set_temp(QUESTDIR3+"tofindshui",1);
     }
    destruct(ob);
	return;
}
string ask_diyun()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"findstory"))
	{
		command("say ��������׷ǹʣ�����Ī���������������\n");
		return "�ߣ��ҿ��Ƕ�������������˫�����������ң�\n";
	}
	command("say ��˵�����Ǹ�ͺͷС������������������С�����أ�һ˫�۾��⿴��ʦ���ˣ�һ���Ͳ��Ǻö�����\n");
	command("say ���������Ա߻��и��������϶���һ·��ɫ��\n");
	command("say ���������һ��Ҳ���Ǻû�ɫ��\n");

	me->set_temp(QUESTDIR3+"askwang",1);

	return "�㿴������������ģ�Ҳ����ʲô����\n";
}
string ask_shuisheng()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"askwang"))
	{
		command("say ��������׷ǹʣ�����Ī���������������\n");
		return "�ߣ��ҿ��Ƕ�������������˫�����������ң�\n";
	}
	command("say ��ʦ�������µ�һ���ˣ�\n");
	command("say �Һ����˳�����˫�������ǿɲ��Ǻ��ǵģ�\n");
	command("say �ҷ��Ż�����ʦ����һ��\n");

	me->set_temp(QUESTDIR3+"askwangshui",1);

	return "�ҵ�ʦ����Ư����\n";
}
string ask_qiangjie()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"askwangshui"))
	{
		command("say ��������׷ǹʣ�����Ī���������������\n");
		return "�ߣ��ҿ��Ƕ�������������˫�����������ң�\n";
	}
	command("cry ");
	command("cry "+me->query("id"));
	command("fear ");
	command("say ��Ȼ��ʲô��֪���ˣ��Ҿ͸���˵ʵ���ɣ�\n");
	command("say ���ڷ����Һ���ʦ�ó���һ�ܣ���һŭ֮�¾��뿪�Ҷ������ˣ�\n");
	command("say ���Ƿ�������ȥ�ˣ�\n");
	command("say ����׷���������ʲ����������˭��������������\n");
	command("say ����Ҿͺúý�ѵ���£�ʡ���Ժ�޸����һ�Ҫ������\n");
	command("say ����������Ҳ���ǵ��ģ���Ҫ���ҵ���Ҳһ��Ҫ�����Ұ���\n");

	me->set_temp(QUESTDIR3+"wangyouyu",1);
	call_out("hunting",10+random(10));
	return "������ȥ�������ǲ����أ���\n";
}
