// xieyan.c
//by kingso 2010 08 ������ϵ��

#include <ansi.h>

inherit NPC;



void create()
{
        object ob;
		seteuid(getuid());
        set_name("����", ({ "min rou", "minrou" }));
        set("long", @LONG
����Ů�����ڰ����ϣ��������ޱߴ��˶�컨��������ϵ��һ���ɺ�Ʈ��
���������ɥ������Ϲ���һ�����ʳ���,��������ׯׯ�����ˣ����ɷ�ʯ
�岢�ơ��ڰ�˫������Ϊ����۵���,��Ϊ���������ţ�������ᣬ����ƮƮ
����������
LONG );
        set("title","����۵���");
		set("nickname", HIC "����ׯׯ������" NOR);
        set("gender", "Ů��");
        set("age", 41);
        set("shen_type", 1);
        set("attitude", "friendly");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("qi", 25000);
        set("max_qi", 25000);
		set("eff_qi", 25000);

        set("jing", 6500);
        set("max_jing", 6500);
		set("eff_jing", 6500);

        set("neili", 20000);
        set("max_neili", 20000);
        set("max_jingli", 8000);
        set("jingli", 8000);
        set("eff_jingli", 8000);
        set("jiali", 200);

        set("combat_exp", 10500000);

        set_skill("force", 460);
        set_skill("sword", 500);
        set_skill("dodge", 460);
        set_skill("parry", 460);
        set_skill("strike", 460);
        set_skill("xuantian-wuji", 460);
        set_skill("taxue-wuhen", 460);
        set_skill("shangqing-jian", 460);
		set_skill("kunlun-zhang", 460);

        map_skill("force", "xuantian-wuji");
        map_skill("dodge", "taxue-wuhen");
        map_skill("strike", "kunlun-zhang");
        map_skill("parry", "shangqing-jian");
        map_skill("sword", "shangqing-jian");

        prepare_skill("strike", "kunlun-zhang");
        set("chat_chance_combat", 80);
     
		set("chat_msg_combat", ({
		(: exert_function, "wuji" :),
		(: perform_action, "dodge.taxue" :),
		(: perform_action, "sword.qingfeng" :),
		//(: perform_action, "leg.ruying" :),
	}));


        set("inquiry", ([
             //   "��������" : (: ask_me :),
               // "����"     : (: ask_me :),
               // "����"     : (: ask_me :),
              //  "����"     : (: ask_me :),
             //   "������"   : "��ö���������Ѿ��ջ�,����һöʧ�佭��������������࣬�����ȥ�Գ�֮���￴����",
              //  "ʯ����"   : "�������Ǹ��׳ջ�û��ô��",
        ]));
        setup();
  	    carry_object("/clone/weapon/changjian")->wield();
  	 //   ob=new("/clone/weapon/changjian");
		//ob->wield();

        carry_object("/clone/armor/cloth")->wear();
}
