// NPC: lu.c ³�н�
// Lklv 2001.9.28 update
// By Spiderii@ty srf,tjf������ask job��tj.
#include <ansi.h>
inherit NPC;
int say_huang1();
int say_huang2();
//#include "gb_lujob.h"
void create()
{
	set_name("³�н�", ({"lu youjiao", "lu", "youjiao"}));
	set("title", HIW"ؤ��Ŵ�����"NOR);
	set("nickname", "�ư���ͷ");
	set("gender", "����");
	set("age", 45);
	set("long", "����ؤ�����������壬���¹������䣬��ú��߹������ء�\n");

        set("attitude", "peaceful");
        set("str", 25);
        set("int", 12);
        set("con", 25);
        set("dex", 20);
        set("unique", 1);
        set("no_bark",1);
        set("job_npc",1);
        set("no_get","³�нŶ�����˵̫���ˡ�\n");

        set("qi", 13500);
        set("eff_jingli", 8000);
        set("max_qi", 13500);
        set("jing", 8000);
        set("max_jing", 8000);
        set("eff_jing", 8000);
        set("neili", 24200);
        set("max_neili", 24200);
        set("jiali", 200);

        set("combat_exp", 9400000);
        set("score", 20000);

	    set_skill("force", 450); // �����ڹ�
        set_skill("huntian-qigong", 450); // ��������
        set_skill("strike",450); // ����ȭ��
        set_skill("xianglong-zhang", 450); // ����ʮ����
        set_skill("dodge", 450); // ��������
        set_skill("xiaoyaoyou", 450); // ��ң��
        set_skill("parry", 450); // �����м�
        set_skill("literate", 100);
        set_skill("stick", 450); // ��������
        set_skill("begging", 200);

        map_skill("force", "huntian-qigong");
        map_skill("strike", "xianglong-zhang");
        map_skill("parry","xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");

        prepare_skill("strike", "xianglong-zhang");

    	set("chat_msg_combat", ({
        	(: perform_action, "strike.xiao" :),
        	(: perform_action, "strike.feilong" :),
        	(: exert_function, "huntian" :),
        }));
        create_family("ؤ��", 18, "�Ŵ�����");
        set("inquiry", ([
               // "����ͼ��" : (:ask_me:),
               // "��Ч����" : (:ask_job:),
               // "����": (: ask_num :),
                //"����": (: ask_gift :),

                "���߹�": "����ƽ�������������������׽�һ��Ľ������߹�����\n",
        ]));
        set("count",1);
        setup();
        carry_object(ARMOR_D("bainayi"))->wear();
        carry_object(ARMOR_D("caoxie"))->wear();

       // carry_object("d/gb/obj/gb_budai9")->wear();
}

int say_huang1()
{
	command("say �ư������㿴�������Ӿ��ǱȽ��ż���һʱ֮��Ҳѧ���ᡣ\n");
	command("say ����������ϰ�����ܷ�ѧ�ᣡ\n");
	return 1;

}
int say_huang2()
{
	command("blush ");
	command("sigh ");
	command("say �����˼�������ˣ���������ȼ�������Ȼ����������ĥ��\n ");
	command("say �������ᡣ\n");
	return 1;
}