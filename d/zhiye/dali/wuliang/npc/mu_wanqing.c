// NPC :mu_wanqing.c ľ����
// By sohu@xojh 2014
#include <ansi.h>

inherit NPC;
void create()
{
        set_name("ľ����", ({ "mu wanqing", "mu", "wanqing"}));
        set("title",HIB"���޵�"NOR);
        set("nickname","����Ů��");        
        set("gender", "Ů��" );
        set("age", 36);
        set("str", 17);
        set("con", 23);
        set("dex", 26);
        set("int", 25);
        set("per", 25);
   		set("attitude", "friendly");

        set("max_qi", 10000);
        set("max_jing", 8000);
        set("eff_jingli", 8000);
        set("neili", 8000);
		set("qi", 10000);	
        set("max_neili", 8000);      
        set("unique", 1);
        
        set("long","��С����ԼĪʮ������������ͣ���Ȼ���ɺ�ɴ�������β�ס��������ɫ��üĿ��������Թ��\n");
        set("combat_exp", 4200000);
        set("shen", 800); 

        set_skill("parry", 350);
        set_skill("dodge", 350);
        set_skill("force", 350);
        set_skill("strike", 350);
		set_skill("blade", 350);
		set_skill("xiuluo-dao", 350);
        set_skill("qiantian-yiyang", 350);        
        set_skill("tianlong-xiang", 350);
        set_skill("qingyan-zhang", 350);

        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "xiuluo-dao");
        map_skill("strike", "qingyan-zhang");
        map_skill("force", "qiantian-yiyang");
        prepare_skill("strike","qingyan-zhang");
		set("chat_chance_combat", 60);
		set("chat_msg_combat",({
			(: perform_action, "blade.xiuluo" :),
			(: perform_action, "strike.qingyan" :),
			(: perform_action, "strike.piaomiao" :),
			(: exert_function, "qi" :)
		}));
        set("inquiry", ([            
//            "������" : (: ask_duan :),
        ]));

        setup();
		carry_object("/clone/weapon/blade")->wield();
        carry_object(__DIR__"obj/lvshan")->wear();
}

int accept_object(object who, object obj)
{
	object ob=this_object();
	if (!ob || ob->is_fighting()) return 0;
		
	if (who->query_temp("yyzhi/second/fightover") && obj->query("id")=="yu zhuozi")
	{
		who->delete_temp("yyzhi/muzhuo");
		write(HIY"ľ������˵α����������ƺ�����ĺøд�����\n"NOR);
		message_vision(HIC"$N���������͸���$n��\n"NOR,who,ob);
		command("say ��֪���ˣ��ǳ�лл��ľȻ���\n");
		obj->move(this_object());
		destruct(obj);
		who->delete_temp("yyzhi/second/fightover");
		who->set_temp("yyzhi/second/helpmuover",1);		
		return 1;
	}

}