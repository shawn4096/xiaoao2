// Modify By River 98/12
#include <ansi.h>
inherit NPC;
void gohome(object ob);

void create()
{
        set_name("����ɢ��", ({ "yuxu sanren", "yuxu", "sanren" }));
        set("title", "���������");
        set("long", "����һ��������ã��������������Դ�Щ���\n");
        set("gender", "Ů��");
        set("rank_info/respect", "����");
        set("age", 37);
        set("attitude","friendly");
        set("str", 30);
        set("dex", 35);
        set("con", 17);
        set("int", 25);
        set("unique", 1);
        set_skill("unarmed", 350);
        set_skill("force", 350);
        set_skill("qiantian-yiyang",350);
        set_skill("dodge", 380);
        set_skill("whip",380);
        set_skill("qingxu-bian", 380);
        set_skill("tianlong-xiang",380);
        map_skill("whip", "qingxu-bian");
        map_skill("force", "qiantian-yiyang");
        map_skill("dodge", "tianlong-xiang");
        
        set("combat_exp", 4500000);
        set("max_qi", 9000);
        set("max_jing", 4000);
        set("neili", 9000);
        set("eff_jingli",4000);
        set("max_neili", 9000);
        setup();
        carry_object(__DIR__"obj/fuchen")->wield();
        carry_object(__DIR__"obj/greenrobe")->wear();		

}

//��npc�ؼ� by renlai
void gohome(object ob)
{
	if(!ob) return;
     ob->return_home();	
}
