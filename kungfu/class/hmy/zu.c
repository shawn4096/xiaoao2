// zu.c

#include <ansi.h>
inherit F_MASTER;
inherit NPC;

void create()
{
	set_name("��ǧ��", ({ "zu qianqiu", "zu",}));
        set("nickname","�ƺ�����");
		set("title","ʥ������");
        set("long", 
"ֻ������Ƥ���ƣ�˫Ŀ�������������м���
���ӣ������������ȴͦ�Ÿ�����ӡ�\n");
        set("age", 80);        
        set("gender", "����");
        set("attitude", "peaceful");
        set("shen", -10000);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);

        set("max_qi", 6800);
		set("qi", 6800);
		set("jing", 5300);
        set("max_jing", 5300);
        set("neili", 7000);
        set("max_neili", 7000);
		set("eff_jingli", 4700);
		set("jingli", 4700);
        set("jiali", 50);
        set("combat_exp", 200000);
        set("shen", -2000);

		set_temp("apply/attack", 140);
		set_temp("apply/defence", 140);

        set_skill("tianmo-zhang",250);
		set_skill("strike", 250);
        set_skill("dodge",250);
		set_skill("huanmo-wubu", 250);
		set_skill("parry", 250);
		set_skill("force", 250);
		set_skill("literate", 100);
		set_skill("tianmo-gong", 250);

        map_skill("strike", "tianmo-zhang");
        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
		map_skill("parry", "tianmo-zhang");
		prepare_skill("strike", "tianmo-zhang");
		create_family("�������",9,"����");

        setup();
		carry_object("/clone/misc/cloth")->wear();
}
void attempt_apprentice(object ob)
{
     if(ob->query("str") < 25 ){
        command("say ����ħ����Ҫ�ߵı��������������25���Ҳ����㣡");
        return;
        }
	 if(!ob->query("family") || ob->query("family/family_name")!="�������" ){
        command("say ��������ʦ�����˺θɣ�");
        return;
        }
	/* if(ob->query("gender") =="Ů��" ){
        command("say Ů���Ӻ����鷳���ҿ��㻹��ȥѰ��������˿�������˵����������Ů���ӣ���");
        return;
        }*/
	if(ob->query("gender") =="����" ){
        command("say �����ֲ��в�Ů�Ļ�ɫ������Ϊʦ����");
        return;
        }
     command("haha");
	 command("say �ðɣ�Ϊ�˹��������̣��Ҿ��������ˡ�");
     command("recruit " + ob->query("id"));
}