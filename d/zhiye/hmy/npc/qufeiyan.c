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

        set_skill("hand", 220);
		//set_skill("sword", 200);

        set_skill("dodge", 220);
		set_skill("force", 220);
        set_skill("parry", 220);
        set_skill("tianmo-gong", 220);
        set_skill("huanmo-wubu", 220);
        set_skill("tianmo-shou", 220);
        set_skill("sword", 220);
        set_skill("qingxin-jian", 220);

        set_temp("apply/damage", 25);
        //set("combat_exp", 1800000);
		map_skill("dodge","huanmo-wubu");
		map_skill("force","tianmo-gong");
		map_skill("parry","qingxin-jian");

		map_skill("hand","tianmo-shou");
		map_skill("sword","qingxin-jian");
		prepare_skill("hand","tianmo-shou");

		create_family("�������",10,"����");

        setup();
        carry_object("/d/henshan/npc/obj/female-shoe")->wear();
		carry_object("/d/henshan/npc/obj/female1")->wear();
		carry_object("/clone/weapon/duanjian")->wield();

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