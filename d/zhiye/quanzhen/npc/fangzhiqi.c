#include <ansi.h>

inherit NPC;
string ask_yanlian();

void create()
{
        set_name("��־��", ({"fang zhiqi", "fang"}));
        set("gender", "����");
        set("age", 24);
        set("class", "taoist");
        set("long",
                "������ȫ��̵����������еĺ��֣��𴦻��Ķ����ӡ�\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 26);
        set("int", 25);
        set("con", 25);
        set("dex", 26);
        set("qi", 4500);
        set("max_qi", 4500);
        set("jing", 3000);
        set("max_jing", 3000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 160);
        set("level", 8);
        set("combat_exp", 4800000);
		set("jingli", 4000);
        set("max_jingli", 4000);
        set("eff_jing", 4000);

        set("eff_jingli", 4000);
		set("eff_jing", 3000);
		set("quest/qz/xtg/daojue/pass",1);
		set("quest/qz/jyg/shangtianti/pass",1);
		set("quest/quanzhen/sword/lianhuan",1);

        set_skill("force", 350);
        set_skill("xiantian-gong", 350);
        set_skill("sword", 360);
        set_skill("quanzhen-jianfa", 360);
        set_skill("dodge", 350);
        set_skill("jinyan-gong", 350);
        set_skill("parry", 350);
        set_skill("leg", 350);
        set_skill("yuanyang-lianhuantui", 350);
        set_skill("literate",160);
        set_skill("taoism",200);
        set_skill("tiangang-beidouzhen",350);
        set_skill("strike",350);
        set_skill("haotian-zhang", 350);
        set_skill("tiangang-beidouzhen", 350);
        set_skill("jinguan-yusuojue", 350);

		map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("leg", "yuanyang-lianhuantui");
        map_skill("strike", "haotian-zhang");

		prepare_skill("strike", "haotian-zhang");
		prepare_skill("leg", "yuanyang-lianhuantui");
        create_family("ȫ���", 3, "����");

 
        set("inquiry", ([
                "ȫ���" :  "��ȫ��������µ����������ڡ�\n",
				"�������������" :  (:ask_yanlian:),  
        ]) );
       set("chat_chance_combat", 40);
		set("chat_msg_combat", ({
			(: perform_action, "sword.ding" :),
			(: perform_action, "sword.sanqing" :),
			(: perform_action, "sword.lian" :),
			(: exert_function, "daojue" :),
			(: perform_action, "dodge.yanwu" :),
		}));
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

string ask_yanlian()
{
	object me;
	me=this_player();
	if (!me->query_temp("lianzhen/zhao"))
	{
		return "û�²�Ҫ�������ң�\n";
	}
	if (me->query_temp("lianzhen/fang"))
	{
		
		return "�㲻�Ǻ�����һ����?";
	}
	command("say �õģ���Ȼ��ʦ������һ���������������͵���\n");
	me->set_temp("lianzhen/fang",1);
	call_out("go_jiaochang",2+random(3));
	return "�����������ȫ�澫�����ڣ�\n";
}
int go_jiaochang()
{
	object room;
	room=load_object("/d/quanzhen/dajiaochang");
	
	command("say ��Ҫȥ��У����������,�����ۣ�\n");
	if (!present("fang zhiqi",room))
		this_object()->move("/d/quanzhen/dajiaochang");
	return 1;
}