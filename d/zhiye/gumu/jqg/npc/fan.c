// yiweng.c ��һ��
inherit NPC;
void consider();
void create()
{
       set_name("��һ��", ({ "fan yiweng","fan","yiweng" }) );
       set("gender", "����" );
       set("title","����ȴ�ܼ�");
       set("age", 60);
       set("long", "���ǹ�������Ĵ���ӣ����³���Ʈ�ݣ�\n"+
                   "���������ڵ��ϣ�������΢��С��\n");
       set("attitude", "peaceful");
       set("str", 38);
       set("con", 21);
       set("int", 20);
       set("dex", 35);
       set("per", 15);
       set("unique", 1);

       set("max_qi", 2000);
       set("max_jing", 1800);
       set("neili", 2000);
       set("max_neili", 2000);
       set("eff_jingli",2000);
       set("jiali", 40);
       set("shen", -500);        
       set("combat_exp", 800000);

       set_skill("force", 200);      
       set_skill("dodge", 200);
       set_skill("parry", 200);
       set_skill("guiyuan-tunafa", 200);
       set_skill("literate", 80); 
       set_skill("shuishangpiao", 200);
       set_skill("tiezhang-zhangfa", 200);
       set_skill("strike",200);
       
       map_skill("force", "guiyuan-tunafa");
       map_skill("dodge", "shuishangpiao");
       map_skill("strike", "tiezhang-zhangfa");
       map_skill("parry", "tiezhang-zhangfa");
       prepare_skill("strike", "tiezhang-zhangfa");

       setup();
       carry_object("/clone/armor/cloth")->wear();
}