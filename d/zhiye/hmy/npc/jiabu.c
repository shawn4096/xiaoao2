// jiabu.c
#include <ansi.h>
#include <wanted.h>
inherit NPC;
inherit F_MASTER;

string give_pass();

string *unknow = ({
	"���Ǻ��ˣ�����ϵú�ľ�£�",
	"�пڣ���Ȼ��ܶ�����Ȩ��֪��",
	"��֪��",
});

void create()
{
        set_name("�ֲ�", ({ "jia bu", "jia", "bu"}));
	set("nickname", "��������");
        set("long",
"����һ��������Ҳ�ƻƣ�����̫��Ѩ�߸߹��𣬱������һ�Ⱥ������ơ�\n");
        set("title",HIY"�������  "HIC"�����ó���"NOR);
        set("gender", "����");
	set("age", 40);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 23);
	set("int", 23);
	set("con", 24);
	set("dex", 28);

        set("max_qi", 3600);
        set("max_jing", 3600);
        set("eff_jingli", 3600);
        set("jiali", 200);
        set("combat_exp", 1500000);

        set_skill("parry",400);
		set_skill("tianmo-jue",200);
        set_skill("dodge",400);
        set_skill("force",400);
        set_skill("strike",400);
        set_skill("cuff",400);
        set_skill("blade",400);
        set_skill("literate", 220);
        set_skill("huanmo-wubu",400);
        set_skill("tianmo-gong",400);
        set_skill("tianmo-zhang",400);
        set_skill("tianmo-dao",400);        

        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
        map_skill("parry", "tianmo-zhang");
        map_skill("strike", "tianmo-zhang");
        map_skill("blade", "tianmo-dao");        
        prepare_skill("strike", "tianmo-zhang");

	set("inquiry", ([
		"�п�" : (: give_pass :)
	]));
	create_family("�������", 7, "����");	
        setup();

	carry_object(MISC_D("cloth"))->wear();
}

string give_pass()
{
	object me = this_object();
	object ob;

	ob = environment(me);
	if (ob == load_object("/d/hmy/shimen.c"))
	if (!is_wanted(this_player()) && random(3) == 1)
			return "���յ��п��ǣ�"+ob->query("pass");
	return unknow[random(sizeof(unknow))];
}

void attempt_apprentice(object ob)
{
     if(ob->query("shen") > 0){
        command("say �㲻���ĺ����������ĵز������Ҳ����㣡");
        return;
        }
	  if(ob->query_skill("tianmo-gong",1) < 300){
        command("say �����ħ���������㻹������ȥ�Һ��ʵ�ʦ��ȥ�ɣ�");
        return;
        }
     command("haha");
	 command("say �ðɣ�Ϊ�˹��������̣��Ҿ��������ˡ�");
	 ob->set("class","riyue");
     command("recruit " + ob->query("id"));
}
