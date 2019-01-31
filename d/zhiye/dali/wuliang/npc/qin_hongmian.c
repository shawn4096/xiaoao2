// NPC qin_hongmian.c �غ���
// By sohu@xojh 2014
#include <ansi.h>

inherit NPC;
string ask_duan();
int qin(object me);

void create()
{
        set_name("�غ���", ({ "qin hongmian", "qin", "hongmian"}));
        set("title",HIB"���޵�"NOR);
        //set("nickname","��ҹ��");        
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
        
        set("long","�⸾��ԼĪ��ʮ������������ͣ���ɫ���㣬üĿ����ϡ��ľ�����������ơ�\n");
        set("combat_exp", 4200000);
        set("shen", 800); 

        set_skill("parry", 380);
        set_skill("dodge", 380);
        set_skill("force", 380);
        set_skill("strike", 380);
		set_skill("blade", 400);
		set_skill("xiuluo-dao", 400);
        set_skill("qiantian-yiyang", 380);        
        set_skill("tianlong-xiang", 380);
        set_skill("qingyan-zhang", 380);

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
            "������" : (: ask_duan :),
        ]));

        setup();
		carry_object("/clone/weapon/blade")->wield();
        carry_object(__DIR__"obj/lvshan")->wear();
}
string ask_duan()
{
		object me=this_player();
		if (!me->query_temp("yyzhi/helpqhm")) return "�ߣ������������������������������Ҿ�ɱһ�Σ�\n";
		
		command("angry ");
		command("shout ���������û���ĵģ�");
	
		command("say ��ʲô�¸Ͻ�˵�������Һ����ˣ� ");
		command("say �������˲�������������������ô������˭��ȥ��˭��");
		command("say .........��");
		command("say .........��");
		message_vision(HIY"\n\n\n\n������ʱ��Ľ��ź���߶���غ�������ȷ��$N�Ƕ������������������ˡ�\n"NOR,me);

		message_vision(HIY"\n\n\n\n\��ʱ��Ҳ���Ʋ�ס�Լ����������������������\n"NOR,me);
		message_vision(HIY"\n\n\n\n\������������������\n"NOR,me);
		message_vision(HIY"\n\n\n\n\���ʱ���Ժ��غ��������ȶ���������ʼ������˵���µ���������ȥ����\n"NOR,me);
		if (me->query_temp("yyzhi/helpgbb"))
		{		
			me->set_temp("yyzhi/askqin",1);
			message_vision(HIC"\n\n\��֪�����غ�������ص��Լ��ഺ����������ֳ�������������ɡ�����\n"NOR,me);
			return "��̾һ�����ƺ�����������£����ƺ����в���\n";
		}
		me->set_temp("yyzhi/askqin",1);
		call_out("qin",2,me);
		return "�ѵ���ʲô���ˣ�\n";

}
int qin(object me)
{
	//object me=this_player();
	command("hammer ");
	command("heng ");
	command("say ���Ȼ���������ˣ���Ϊʲô���Լ�����\n");
	message_vision(HIC"�غ��޳������ã�˵��������ȷ��"+HIR+"(answer ȷ��)"+HIC"���������������ҵ�ô��\n��"NOR,me);
	//add_action("do_answer","answer");
	return 1;

}