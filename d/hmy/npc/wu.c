// wu.c

#include <ansi.h>
inherit F_MASTER;
inherit NPC;

void create()
{
        set_name("���Ӣ", ({ "wu baiying", "wu", "baiying"}));
        set("long", "��Ů�Ӽ���΢�ڣ�˫�ۼ�С��������ᡣ\n");
        set("nickname","ͩ��˫��");
        set("title",HIY"�������  "HIW"�׻��ö���"NOR);
        set("gender", "Ů��");
        set("age", 30);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);

        set("max_qi", 2800);
        set("max_jing", 1300);
        set("eff_jingli", 1500);
        set("jiali", 50);
        set("combat_exp", 900000);
       
		set_skill("force",220);
        set_skill("dodge",220);
        set_skill("huanmo-wubu",220);   
		set_skill("tianmo-gong",220);
        set_skill("literate", 120);
        set_skill("parry",220);
	    set_skill("tianmo-dao", 220);
	    set_skill("blade", 220);
	    set_skill("strike", 220);
		set_skill("tianmo-jue", 220);
	    set_skill("tianmo-zhang", 220);

        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
	map_skill("blade", "tianmo-dao");
	map_skill("parry", "tianmo-dao");
	map_skill("strike", "tianmo-zhang");
	prepare_skill("hand", "tianmo-zhang");
	create_family("�������",9,"����");


        setup();

	carry_object(BINGQI_D("blade"))->wield();
	carry_object(MISC_D("cloth"))->wear();       
}
void attempt_apprentice(object ob)
{
     if(ob->query("shen") > -10000 ){
        command("say �㲻���ĺ����������ĵز������Ҳ����㣡");
        return;
        }
	 if (ob->query_skill("tianmo-gong",1) <100)
	 {
		command("say �����ħ����̫��Ҳ����㣡");
        return;
	 }
     command("haha");
	 command("say �ðɣ�Ϊ�˹��������̣��Ҿ��������ˡ�");
     command("recruit " + ob->query("id"));
}