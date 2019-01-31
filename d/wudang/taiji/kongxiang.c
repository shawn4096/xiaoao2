// By Spiderii
#include <ansi.h>
inherit NPC;

void create()
{
	set_name("�����ʦ", ({
		"kongxiang dashi",
		"kongxiang",
		"dashi",
	}));
	set("long",
		"����һλ��ɫ�����������ɮ����һϮ��˿�ػ����ġ�����ĸߴ�\n"
		"���ֹ�ϥ��˫Ŀ������գ�ȴ��ʱ���һ�ƾ��⡣\n"
	);


	set("nickname", "�����");
	set("gender", "����");
	set("attitude", "peaceful");
	set("class", "bonze");

	set("age", 40);
	set("shen_type", 1);
	set("str", 35);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 23000);
	set("max_jing", 8000);
	set("neili", 20000);
	set("max_neili", 20000);
	set("jiali", 200);
	set("combat_exp", 10000000);
	set("score", 500000);

	set_skill("force", 480);
	set_skill("hunyuan-yiqi", 480);
	set_skill("dodge", 480);
	set_skill("shaolin-shenfa", 480);
	set_skill("parry", 480);

	set_skill("strike", 480);

	set_skill("banruo-zhang", 480);
	//set_skill("sanhua-zhang", 480);
	set_skill("buddhism", 140);
	set_skill("literate", 140);

	map_skill("force", "yijin-jing");
	map_skill("strike", "banruo-zhang");
	map_skill("dodge", "shaolin-shenfa");

	map_skill("parry", "banruo-zhang");

    prepare_skill("strike", "banruo-zhang");
    set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
		(: perform_action, "strike.chaodu" :),
		(: perform_action, "strike.yipai" :),
		
	}));
	create_family("������", 36, "����");

	setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}
int init()
{
	 object ob;
        
        ::init();
        
        if( interactive(ob = this_player()))
        {
              if (ob->query_temp("mwd/step7") )
              {
				command("chat �������ֵ��ӿ��࣬�������ѣ�Ϊħ����ͽΧ����Σ�ڵ�Ϧ��");

              }
			   // remove_call_out("greeting");
             //   call_out("greeting", 0, ob);
        }

}
int greeting(object ob)
{
		command("chat ����һ·������ʱ����ȣ�������ϸ˵�����׼������˷�����ϸ������");
		command("chat ������֮��������������ˣ������λʦ�ּ�ʱͨ������");
}
int greet2(object ob)
{
		command("cry");
		command("say �����ˣ�ħ����δ������������Σ�ڵ�Ϧ����ɵþ����������ɰ���");
		command("say ������ʱ��ħ����ͽ�Ѿ�Χ�������£���һ·���棬��֪�������ֻ����ڲ����ڣ�");
		command("cry");
		command("cry");
}