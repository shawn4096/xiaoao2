// shuisheng.c

inherit NPC;
#include <ansi.h>;
string ask_diyun();
string ask_laozu();
string ask_dachang();
#include "/d/suzhou/npc/lchj.h"

void create()
{
       set_name("ˮ��", ({ "shui sheng", "shui", "sheng" }));
       set("long", 
       "����ʮ��������ͣ�����ƮƮ����ò�������������������һ�����ƵĴ󻨣���òȴ��Ϊ������\n");
       set("gender", "Ů��");
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
              "�仨��ˮ": "�㲻�᲻֪�����������Ĵ�Űɣ����½�ˮ᷾����ҵĸ��ס�",
              "Ѫ����ɮ": "����һ��Գ�Ѫ�����棬��ʵ�޶������ҿ�����һ��һ����������",
		   	  "����" : (: ask_diyun :),
			 "Ѫ������" : (: ask_laozu :),
			 "������" : (: ask_dachang :),

       ]));
		set("chat_chance_combat", 40);

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
void init( )
{
        call_out("hunting",300);
}

void hunting()
{
   object ob=this_object();
   if (this_player())
    {
      message("vision", HIW"ֻ���ö����ᣬ������һ��������һ������Զ�������ˡ�\n"NOR, this_player());
     }
    destruct(ob);
}

string ask_diyun()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"tofindshui"))
	{
		command("say ��������׷ǹʣ�����Ī���������������\n");
		return "�ߣ��ҿ��Ƕ�������������˫�����������ң�\n";
	}
	command("say ���Ƕ����ˣ�����������������һλ���ˣ�\n");
	command("say ������������¸���������һλ����������ӣ�\n");
	command("say ǰһ���ӣ��Ҿ��Ǳ�Ѫ������ûץס�ˣ�Ҫ���������Ҹ����ͻ�ˣ�\n");

	me->set_temp(QUESTDIR3+"shuisay1",1);

	return "����һ�����Ķ��ǵĴ�ս��Ѫ��������һλ�ǳ�а���������\n";
}
string ask_laozu()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"shuisay1"))
	{
		command("say ��������׷ǹʣ�����Ī���������������\n");
		return "�ߣ��ҿ��Ƕ�������������˫�����������ң�\n";
	}
	command("cry ");
	command("cry "+me->query("id"));

	command("say Ѫ��������ҵĸ��׺�������λ����ȫɱ�ˣ�\n");
	command("say ̫�׺��ˣ�\n");
	command("say �����˵���һֱ�����ң������Ҹ����ͻ�ˣ�\n");
	command("say ��һֱ�����ҵ����ں���������һֱ���͸м�����\n");
	command("say ������Ϊ������һ�������멣�Ҳ��֪����������û�У���\n");

	me->set_temp(QUESTDIR3+"shuisay2",1);

	return "��ѩ���캮�ض�����������Ҳ������ů�͵㣡\n";
}
string ask_dachang()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"shuisay2"))
	{
		command("say ��������׷ǹʣ�����Ī���������������\n");
		return "�ߣ��ҿ��Ƕ�������������˫�����������ң�\n";
	}
	command("blush ");
	command("blush "+me->query("id"));
	command("say �ҵ�ʱ��ѩ���ж�����ëΪ��������һ�������멣�\n");
	command("say ��ʱ��æ�ŵ�һ��ɽ��������֪�����յ���û�У�\n");
	command("say �Ҽǵ��Ǹ�ɽ���ڴ�ѩɽ����������һ����ս����æ���벻�������Ķ�ȥ�ˣ�\n");
	command("say ��������������ҵ��Ǽ���멲��͸��Ҿ�лл�㣡\n");
	command("say ��֪����һ��Ե�ݻ��ǳ�ޣ�\n");

	me->set_temp(QUESTDIR3+"tofinddachang",1);
	//if (present("shui sheng",environment(me)))
		//call_out("hunting",10+random(10));
	return "Ҳ��֪��������ѩ��ɽ�����䲻�䣿��\n";
}



int accept_object(object me, object obj)
{
		int i;
        if ((string)obj->query("id")=="niaoyu dachang"
			&&me->query_temp(QUESTDIR3+"tofinddachang")) 
		{
			message("vision",me->name()+"��ˮ��һ�������멡�\n",environment(me),({me}));
			
			//if(obj->query("owner")!=me->query("id")) return notify_fail (CYN"ˮ���ƺ�����˴�������һ����\nˮ�϶�"+me->name()+"��ʾ���ĸ�л��\n"NOR);  
			
			command("ah "+me->query("id"));
			command("say ��λ"+RANK_D->query_respect(me)+"Ӧ���ǵ��ƴ������Ѱɡ�");
			command("smile "+me->query("id"));
			command("say ��Ȼ�ǵ��ƴ������ѣ���ô�Ҿ͸�����һ��С���ܡ�\n");
			command("say ���������Ǿ��Ķ�Թ���˱����⣬��ǣ����һ�Ž������վ��ľ����񹦡�\n");
			command("say ��������������Ǳ��أ������ֺ��������ȴ�������վ��񹦡�\n");
			command("say �����������㷢�ִ�멵��Ǹ��ط����ۼ������ƴ����δ�չ������ܵ��˵ġ�\n");
			command("say �����Ը�⣬�Ҿʹ���һ��ȥ�������ƴ�����ֳ������ش�ͻ�Ƶĵط���\n");
			command("say ����ô���ĳ�����Ե��˵�������Ķ�ȥ���������Լ��Ļ�Ե��\n");
			command("say ����ȥ�Ķ����ң������͵���\n");

			me->set_temp(QUESTDIR3+"shuitellstory",1);
			if (present("shui sheng",environment(me)))
				call_out("hunting",5+random(4));

			command("rumor "+"��Ե�ɺ�֮�£�"+me->query("name")+"֪�������վ�������ƾ���С����Ϣ��\n");
			return 1;
		}
      
		return 0;
}