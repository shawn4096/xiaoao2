#include <ansi.h>
inherit F_MASTER;
inherit NPC;

void create()
{
        set_name("������", ({ "qu feiyan", "feiyan", "qu" }));
	//set("nickname", HIM "�Ƿ�" NOR);
        //set("title", "�������");
	set("long", @LONG
����ŮͯԼĪʮ��������ͣ���һ�����������
Ƥ��ѩ�ף�һ����������ɰ����޲���������ͬ��֮�⡣
LONG);
        set("gender", "Ů��");
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("per", 25);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
		set("age",14);

        set("max_qi", 9800);
        set("max_jing", 5600);
        set("eff_jingli", 5600);
        set("jiali", 50);
        set("combat_exp", 2500000);

        set_skill("hand", 200);
        set_skill("dodge", 200);
		set_skill("force", 200);
        set_skill("parry", 200);
        set_skill("tianmo-gong", 200);
        set_skill("huanmo-wubu", 200);
        set_skill("tianmo-shou", 200);
        set_skill("whip", 200);
        set_skill("wudu-bian", 200);

        set_temp("apply/damage", 25);
        set("combat_exp", 800000);
		map_skill("dodge","huanmo-wubu");
		map_skill("force","tianmo-gong");
		map_skill("parry","wudu-bian");

		map_skill("hand","tianmo-shou");
		map_skill("whip","wudu-bian");
		prepare_skill("hand","tianmo-shou");

		create_family("�������",10,"����");

        setup();
        carry_object("/d/henshan/npc/obj/female-shoe")->wear();
		carry_object("/d/henshan/npc/obj/female1")->wear();

}
void attempt_apprentice(object ob)
{
     if(ob->query("str") < 25 ){
        command("say ��ϰ��ħ����Ҫ�ߵı��������������25���Ҳ����㣡");
        return;
        }
	
	 if(ob->query("shen")>-10000 ){
        command("say �����쳣���ң��Ǽ鼴�������ĳ�̫������С��-10k�������ң���");
        return;
        }
	 if(ob->query("gender") =="����" ){
        command("say �����ֲ��в�Ů�Ļ�ɫ������Ϊʦ����");
        return;
        }
     command("haha");
	 command("say ���Ǻ��棬Ϊ�˹��������̣��Ҿ��������ˡ�");
     command("recruit " + ob->query("id"));
}