#include <ansi.h>
inherit NPC;
void create()
{
        set_name("����", ({ "a da", "ada" }) );
        set("title", HBRED"�˱���ħ"NOR);
        set("long", "�������������е������������ϴ���������ݳ����������ƣ���ü������\m�ƺ��ղŸ���ʹŹ��һ�٣�Ҫ��Ȼ�������������Ӷ�Ů��\n����ֻҪ�����������飬������Ҫ������������\n");
        set("gender", "����" );
        set("age", 54);
		set("con",25);
        set("dex",25);
        set("unique", 1);
        set("per", 20);
        set("no_get", 1);
        set("max_qi", 30000);
        set("max_jing", 7000);
        set("neili", 20000);
        set("max_neili", 20000);
        set("jiali", 200);
        set("combat_exp", 13500000);
        set("eff_jingli", 7000);

        set_skill("force", 480);
        set_skill("hunyuan-yiqi", 480);
        set_skill("dodge", 480);
        set_skill("shaolin-shenfa", 480);
        set_skill("finger", 500);
        set_skill("jingang-zhi", 520);
        set_skill("parry", 480);
        set_skill("literate", 150);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "jingang-zhi");
        map_skill("parry", "jingang-zhi");
        prepare_skill("finger", "jingang-zhi");
    	set("chat_chance", 60);
    	set("chat_msg_combat", ({
        	(: perform_action, "finger.fumo" :),
        	(: perform_action, "finger.jingangzhi" :),
        	(: perform_action, "finger.lianhuan" :),
        }));
        setup();
        carry_object("/d/wudang/obj/white-robe")->wear();/**/
}
int greet_ada()
{
	command("heng ");
	command("say ��Ҳ�á����ڵ���Ⱥ���ǡ�!");
	command("say ���������������ȥ����˵�����������粻��ؤ��ĳ����ˡ�");
	command("say �˱��񽣷������Ѿ����ˡ�");
	command("say ����ѧ�䣬δ����˰գ�");
	command("say �����ˣ�����!");
	return 1;

}