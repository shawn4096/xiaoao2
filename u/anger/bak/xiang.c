// xiang.c ������
// Finish by action@SJ 2009.1.6
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_jiuwen();

void create()
{
        set_name("������", ({ "xiang wentian", "xiang", "wentian"}));
        set("long", "ֻ������ò���ݣ����θߴ������������һ�Ի��׳��룬������ǰ��\n"+
		"���ϸ���һ���������ٿ�������ʱ��ȴ���䵶��\n");
        set("title",HIY"������� "HIW"������ʹ"NOR);
        set("gender", "����");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);

        set("max_qi", 4000);
        set("max_jing", 5200);
        set("eff_jingli", 5500);
        set("jiali", 200);
        set("combat_exp", 9400000);

        set_skill("strike", 460);
        set_skill("blade", 220);
        set_skill("club", 460);
        set_skill("parry", 460);
        set_skill("dodge", 460);
        set_skill("force", 460);
        set_skill("literate", 160);

        set_skill("tianmo-gun",460);
        set_skill("tianmo-zhang",460);
        set_skill("tianmo-dao",200);
        set_skill("huanmo-wubu",460);
        set_skill("tianmo-gong",460);
        set_skill("tianmo-jue",200);

        map_skill("force", "tianmo-gong");
        map_skill("parry", "tianmo-gun");
        map_skill("blade", "tianmo-dao");
        map_skill("club", "tianmo-gun");
        map_skill("dodge", "huanmo-wubu");
        map_skill("strike", "tianmo-zhang");

        prepare_skill("strike", "tianmo-zhang");
        set("inquiry", ([
                 //"����" : (: ask_mimi :),
		         "����" : (: ask_jiuwen:),
			     //"��Գ��ħ" : (: ask_jinyuan:),
        ]));
        set("chat_chance", 3);
        set("chat_msg", ({
		        "����������ƺ�������һ��ڣ��������þƣ���\n",
					"�ߺߣ�÷ׯ����....�Ķ�����������ʲô�����أ���\n",
					"�������С���е���˼����\n",
					"��ϧ��������ʮ����Χ����ɽ��һȥ���أ����׷�����ʲô�£�����\n",
					"�Ҵ����µĺ����似��ʧ���٣������������϶��ĺ��аԵ�����\n",
        }));
        create_family("�������", 6, "����");
        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
                (: perform_action, "club.luanwu" :),
				(: perform_action, "club.zhenfeng" :),
                (: exert_function, "tianmo" :),
        }));
		
        setup();

        carry_object(MISC_D("cloth"))->wear();  
        carry_object(BINGQI_D("club"))->wield();      
}

void attempt_apprentice(object ob)
{
     if(ob->query_skill("tianmo-gong",1) < 350 ||
      ob->query_skill("tianmo-zhang",1) < 350 ||
        ob->query_skill("tianmo-dao",1) < 350){
        command("say ����书��������죬�ٻ�ȥ�����ɡ�");
        return;
        }
     command("say �ã��������б�����Ƚ��������������㻹��������������ˡ�");
     command("recruit " + ob->query("id"));
     ob->set("title","������̹�����ʹ��������");
}


int ask_jiuwen()
{
     object me=this_player();
     if (me->query("family/family_name")!="�������")
         return notify_fail("�㲻������̵�������Ϲ����������\n");

	 if (me->query_skill("tianmo-gong",1)<449)
		 return notify_fail("�����ħ����̫��������450�����Ǻú�����ȥ�ɡ�");
     
	
		
		 command("say �������ν����ᵽ��ʮ����Χ����ɽ֮ս�ۣ���֪Ϊ�ξ�Ȼȫ��ʧ�١�\n");
		 command("think ");
		 command("say ��ʱ�������Ӣ�۱�������Գ��ħ�ų˷硢�ų����ֵܣ�һ����ħ������ɨ���¡�\n");
		 command("say ���д�����ħ���ɳ��ϵĴ�����ħ���������𽭺���\n");
		 command("sigh ");
		 command("say ˭Ҫ���ܰ����ҵ���ľ��Ҿ͸��������ࡣ\n");
		 command("heng ");
		 me->set_temp("hssb/askxiang",1);
		 return 1;
		 //command("");
		//�漴 ѡ����Ҫ���Ȼ�������˾͸�����ȥ��ɽ����
}

int accept_object(object who, object obj)
{
	object me;
	obj =present("heimu ling", who);
	me = this_player();
    if (!me->query_temp("hssb/askxiang")) {
	    command("say ��ŪЩ���߰���Ķ�����Ū�ң�\n");	
		return 1;
    }

	if (me->query_temp("hostage/linggived")&& obj->query("id")=="heimu ling")
	{
		//me->set_temp("hostage/job_1",2);
		
		me->delete_temp("hostage/linggived");
		write(HIY"�����콫����ľ���������з�����ȥ�Ŀ��š�\n"NOR);
        write(CYN"���������Ķ���������������������ϲ���ǡ�\n"NOR);
		
		command("say ��Ȼ�������ҵ�������ľ����ҾͰ������Ϣ�����㡣\n");
		command("say ʮ����Χ����ɽһȥ���أ��һ����������˶Է��ļ�ơ�\n");
		command("say Ҳ��˵�������ȥ��ɽ��ɽ����ת��ת��˵������ʲô���˵ķ��֡�\n");
		command("say ���������������������죬�ҿ��㻹����Ե�ĺá����²���ǿ��\n");
		me->set_temp("hssb/juejiasked",1);
		destruct(obj);
		return 1;
	}else {
        command("say ��Ϲ����ʲô��\n");
	    return 0;
	}

}