#include <ansi.h>
//inherit F_MASTER;
inherit NPC;
void create()
{
      
	set_name("�Ʋ���", ({ "huang boliu", "huang", "boliu"}));
	set("nickname", "������");        
        set("long", 
		"��һ�����룬ֱ�����أ�����ȴ�����塣��\n");
        set("title","ʥ������");
        set("gender", "����");
        
	set("age", 70);
	set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 23);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
        
        set("max_qi", 2500);
        set("max_jing", 1500);
        set("eff_jingli", 1500);
        set("jiali", 50);
        set("combat_exp", 2700000);
     
        set_skill("parry",270);
        set_skill("dodge",270);
        set_skill("force",270);
        set_skill("strike",270);
        set_skill("literate", 100);      
        set_skill("huanmo-wubu",270);
        set_skill("tianmo-gong",270);
        set_skill("tianmo-zhang",270);

        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
        map_skill("parry", "tianmo-zhang");
        map_skill("strike", "tianmo-zhang");
        prepare_skill("strike", "tianmo-zhang");
        
	      create_family("�������",9,"����");
        setup();
}
/*

void attempt_apprentice(object ob)
{
     if(ob->query("shen") > 0 ){
        command("say �㲻���ĺ����������ĵز������Ҳ����㣡");
        return;
        }
	 if(ob->query("family")){
        command("say ��������ʦ�����˺θɣ�");
        return;
        }
     command("haha");
	 command("say �ðɣ�Ϊ�˹��������̣��Ҿ��������ˡ�");
     command("recruit " + ob->query("id"));
}
*/