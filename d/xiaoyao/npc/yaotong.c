//yaotong.c
//Сҩͯ

inherit NPC;
#include <ansi.h>;


void create()
{
        set_name("Сҩͯ", ({ "xiao yaotong", "yaotong", "xiao"}));
        set("title", "��ң�ɵ��������");
        set("gender", "����" );
        set("age", 102);
        set("str", 50);
        set("int", 25);
        set("con", 30);
        set("dex", 30);
        set("per", 30);
        set("long", 
		"һλ����ѦĽ���ڴ���ҩ��Сҩͯ��ר�Ÿ�������ɵ��ӷ��Ÿ���ҩ��.\n");
        set("combat_exp", 150000);
        set("shen_type", 1);

        set("attitude", "peaceful");
        set("max_qi", 3500);
        set("max_jing", 2000);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 20);
        
        set_skill("force", 120);
        set_skill("zhemei-shou", 120);
       

        map_skill("hand","zhemei-shou");
		setup();
}