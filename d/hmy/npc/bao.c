// bao.c
#include <ansi.h>
inherit F_MASTER;

inherit NPC;

void create()
{
	set_name("�����", ({ "bao dachu", "bao", "dachu"}));
        set("long", "һ��������������ߣ�����ò�������������������յĸ��֡�\n");
        set("title",HIY"�������  "RED"��ȸ������"NOR);
        set("gender", "����");
        
	    set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 27);
        set("int", 27);
        set("con", 27);
        set("dex", 30);
        
        set("max_qi", 3000);
        set("max_jing", 2200);
	      set("eff_jingli", 2200);
	      set("max_neili", 4000);
        set("jiali", 50);
        set("combat_exp", 2700000);

        set_skill("parry", 400);
		set_skill("tianmo-jue", 200);
        set_skill("dodge", 400);
        set_skill("force", 400);
        set_skill("strike", 400);
        set_skill("literate", 200);
        set_skill("huanmo-wubu",400);
	    set_skill("tianmo-gong", 400);
	    set_skill("tianmo-zhang", 400);
     
        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
	      map_skill("parry", "tianmo-zhang");
	      map_skill("strike", "tianmo-zhang");
	      prepare_skill("strike", "tianmo-zhang");
	      create_family("�������", 9, "����");

        setup();

	carry_object(MISC_D("cloth"))->wear();          
}

void attempt_apprentice(object ob)
{
     if(ob->query("shen") >-50000){
        command("say �㲻���ĺ����������ĵز������Ҳ����㣡");
        return;
        }
	 if(ob->query_skill("tianmo-gong",1)<150){
        command("say �����ħ��������������Ҫ����Ŭ����");
        return;
	 }
     if(ob->query_skill("tianmo-jue",1)<150){
        command("say �����ħ����������Ҫ����Ŭ����");
        return;
	 }
	 
     command("haha");
	 command("say �ðɣ�Ϊ�˹��������̣��Ҿ��������ˡ�");
     command("recruit " + ob->query("id"));
}
